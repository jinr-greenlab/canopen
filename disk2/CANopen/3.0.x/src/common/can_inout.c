#include <can_header.h>

#if CHECK_VERSION(3, 0, 3)
//  CHECK_VERSION(2, 3, 3)
//  CHECK_VERSION(2, 2, 2)
//  CHECK_VERSION(2, 1, 2)
//  CHECK_VERSION(2, 0, 2)
//  CHECK_VERSION(1, 7, 1)

static struct cancache cancache[CAN_WRITECACHE_SIZE];
static int16 sem_canrecv, flag_canrecv;
static int16 sem_cantrans, flag_cantrans, sem_overflow;
static unsigned8 datalink_mode;

void push_all_can_data(void)
{
	unsigned16 cnt;

	CAN_CRITICAL_BEGIN
	do {
		flag_cantrans = 0;
		sem_cantrans++;
		if (sem_cantrans == 0) {
			CAN_CRITICAL_END
			for (cnt = 0; cnt < CAN_WRITECACHE_SIZE; cnt++) {
				if (flag_cantrans != 0) break;
				if (cancache[cnt].capture != 255) continue;		// 2.2.2
				#if CAN_APPLICATION_MODE == TEST
				if (write_can_test_driver(can_netchan, &cancache[cnt].cf, 1) <= 0) break;
				#else
				if (datalink_mode != OFF) {
					if (CiWrite(can_netchan, &cancache[cnt].cf, 1) <= 0) break;
				}
				#endif
				cancache[cnt].capture = 0;
				cancache[cnt].busy = -1;
			}
			CAN_CRITICAL_BEGIN
		}
		sem_cantrans--;
	} while (flag_cantrans != 0);
	flag_cantrans = 1;
	CAN_CRITICAL_END
}

int16 send_can_data(canframe *cf)		// 3.0.1 API changed
{
	unsigned16 cnt, wrac, cabeg;

#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE
	if (lss_state != LSS_OFF) {
		if (cf->id != CAN_CANID_LSS_SLAVE) return CAN_ERRET_LSS_CANID;
	} else
#endif
	if (cf->id < CAN_CANID_NMT_ERROR_MIN || cf->id > CAN_CANID_NMT_ERROR_MAX) {
		if (node_state == CAN_NODE_STATE_INITIALISING || 
			node_state == CAN_NODE_STATE_STOPPED) {
			return CAN_ERRET_NODE_STATE;
		}
	}
	if (cf->id <= CAN_ID_PRIORITY_0) cabeg = 0;		  // 3.0.1 priority conditions changed
	else if (cf->id <= CAN_ID_PRIORITY_1) cabeg = 1;
	else if (cf->id <= CAN_ID_PRIORITY_2) cabeg = 2;
	else cabeg = 4;
	#if CAN_PROTOCOL_BLOCK == TRUE
	if ( (cf->id >= CAN_CANID_SDO_SC_MIN && cf->id <= CAN_CANID_SDO_SC_MAX) ||
		 (cf->id >= CAN_CANID_SDO_CS_MIN && cf->id <= CAN_CANID_SDO_CS_MAX) ) {
		 cabeg = CAN_WRITECACHE_SIZE - 1;		// To keep SDO block frames sequence in cache
	}
	#endif
	wrac = CAN_WRITECACHE_ATTEMPTS;
	do {
		CAN_CRITICAL_BEGIN
		sem_cantrans++;
		CAN_CRITICAL_END
		for (cnt = cabeg; cnt < CAN_WRITECACHE_SIZE; cnt++) {
			CAN_CRITICAL_BEGIN
			cancache[cnt].busy++;
			if (cancache[cnt].busy == 0) {
				CAN_CRITICAL_END
				if (cancache[cnt].capture == 0) {
					cancache[cnt].capture = 1;
					cancache[cnt].cf = *cf;
					cancache[cnt].capture = 255;	// 2.2.2
					CAN_CRITICAL_BEGIN
					sem_cantrans--;
					CAN_CRITICAL_END
					push_all_can_data();
					return CAN_RETOK;
				}
			} else {
				cancache[cnt].busy--;
				CAN_CRITICAL_END
			}
		}
		CAN_CRITICAL_BEGIN
		sem_cantrans--;
		CAN_CRITICAL_END
		if (sem_cantrans != -1) break;
		push_all_can_data();
		can_sleep(CAN_WRITECACHE_DELAY);
		wrac--;
	} while (wrac > 0);
	CAN_CRITICAL_BEGIN
	sem_overflow++;
	if (sem_overflow == 0) {
		CAN_CRITICAL_END
		can_cache_overflow(node_state);
		CAN_CRITICAL_BEGIN
	}
	sem_overflow--;
	CAN_CRITICAL_END
	return CAN_ERRET_COMM_SEND;
}

static void receive_can_data(canframe *cf)
{
	canindex index;

	if ((cf->flags & CAN_FLAG_EFF) != 0) return;
	if (cf->len > CAN_DATALEN_MAXIMUM) cf->len = CAN_DATALEN_MAXIMUM;
	cf->id &= CAN_MASK_CANID;
#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE
	if (lss_state != LSS_OFF) {
		if (cf->id == CAN_CANID_LSS_MASTER) {
			if (cf->len != CAN_DATALEN_LSS) return;		// 2.2.2
			lss_slave_process(cf);
		} else if (cf->id == CAN_CANID_NMT) {
			if (cf->len != CAN_DATALEN_NMT_MC) return;	// 2.2.2
		#if CAN_NMT_MODE == SLAVE		// 3.0.3
			if (cf->data[0] == CAN_NMT_RESET_NODE || cf->data[0] == CAN_NMT_RESET_COMMUNICATION) {
				if (node_id >= CAN_NODE_ID_MIN && node_id <= CAN_NODE_ID_MAX) nmt_slave_process(cf);
			}
		#endif

		}
		return;
	}
#endif
	if (node_state == CAN_NODE_STATE_INITIALISING) return;
	if ((cf->flags & CAN_FLAG_RTR) != 0) {
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		if (cf->id == (unsigned32)(node_id + CAN_CANID_NMT_ERROR_BASE)) {
			if (cf->len != CAN_DATALEN_ECP) return;		// 2.2.2
			node_guard_slave();
			return;
		}
#endif
		if (node_state != CAN_NODE_STATE_OPERATIONAL) return;
		find_pdo_rtr_tran_index((canlink)cf->id, &index);
		if (index >= CAN_INDEX_TRNPDO_COMM_MIN && index <= CAN_INDEX_TRNPDO_COMM_MAX) {
			transmit_rtr_pdo(index);
		}
		return;
	}
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (cf->id == CAN_CANID_NMT) {
		if (cf->len != CAN_DATALEN_NMT_MC) return;	// 2.2.2
		nmt_slave_process(cf);
		return;
	}
#endif
#if CAN_NMT_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	if (cf->id >= CAN_CANID_NMT_ERROR_MIN && cf->id <= CAN_CANID_NMT_ERROR_MAX) {
		if (cf->len != CAN_DATALEN_ECP) return;		// 2.2.2
		consume_nmt(cf);
		return;
	}
#endif
	if (node_state == CAN_NODE_STATE_STOPPED) return;
#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
#if CAN_OBJECT_EMCY == TRUE
	if (cf->id >= CAN_CANID_EMCY_MIN && cf->id <= CAN_CANID_EMCY_MAX) {
		if (cf->len != CAN_DATALEN_EMCY) return;	// 2.2.2
		consume_emcy(cf);
		return;
	}
#endif
#endif
	index = find_comm_recv_index((canlink)cf->id);
	if (index == CAN_INDEX_DUMMY) return;		// 3.0.1
	if (index == CAN_INDEX_SYNC_COBID) {
		sync_received(cf);
		return;
	}
#if CAN_OBJECT_TIME == TRUE
	if (index == CAN_INDEX_TIME_COBID) {
		if (cf->len != CAN_DATALEN_TIME) return;	// 2.2.2
		consume_time(cf);
		return;
	}
#endif
	if (index >= CAN_INDEX_RCVPDO_COMM_MIN && index <= CAN_INDEX_RCVPDO_COMM_MAX) {
		receive_can_pdo(index, cf);
		return;
	}
#if CAN_APPLICATION_MODE == MASTER
	if (index >= CAN_INDEX_CLIENT_SDO_MIN && index <= CAN_INDEX_CLIENT_SDO_MAX) {
		if (cf->len != CAN_DATALEN_SDO) return;		// 2.2.2
		receive_can_sdo(index, cf);
		return;
	}
#elif CAN_APPLICATION_MODE == SLAVE
	if (index >= CAN_INDEX_SERVER_SDO_MIN && index <= CAN_INDEX_SERVER_SDO_MAX) {
		if (cf->len != CAN_DATALEN_SDO) return;		// 2.2.2
		receive_can_sdo(index, cf);
		return;
	}
#elif CAN_APPLICATION_MODE == TEST
	if ( (index >= CAN_INDEX_SERVER_SDO_MIN && index <= CAN_INDEX_SERVER_SDO_MAX) ||
		 (index >= CAN_INDEX_CLIENT_SDO_MIN && index <= CAN_INDEX_CLIENT_SDO_MAX) ) {
		if (cf->len != CAN_DATALEN_SDO) return;		// 2.2.2
		receive_can_sdo(index, cf);
		return;
	}
#endif
}

static void can_network_read(void)
{
	canframe cf;

#if CAN_APPLICATION_MODE == TEST
	while (read_can_test_driver(can_netchan, &cf, 1) > 0) receive_can_data(&cf);
#else
	while (CiRead(can_netchan, &cf, 1) > 0) receive_can_data(&cf);
#endif
}

void can_read_handler(canev ev)
{
	CAN_CRITICAL_BEGIN
	do {
		flag_canrecv = 0;
		sem_canrecv++;
		if (sem_canrecv == 0) {
			CAN_CRITICAL_END
			can_network_read();
			CAN_CRITICAL_BEGIN
		}
		sem_canrecv--;
	} while (flag_canrecv != 0);
	flag_canrecv = 1;
	CAN_CRITICAL_END
}

void can_set_datalink_layer(unsigned8 mode)
{
	datalink_mode = mode;
}

void can_init_io(void)
{
	unsigned16 cnt;

	sem_canrecv = -1;
	sem_cantrans = 0;
	for (cnt = 0; cnt < CAN_WRITECACHE_SIZE; cnt++) {
		cancache[cnt].capture = 0;
		cancache[cnt].busy = -1;
	}
	sem_cantrans = -1;
	sem_overflow = -1;
	datalink_mode = ON;
}

#endif
