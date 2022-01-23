#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 4)

static struct cancache cancache[CAN_WRITECACHE_SIZE];
static int16 sem_canrecv, flag_canrecv;
static int16 sem_cantrans, flag_cantrans, sem_overflow;
static unsigned8 datalink_mode;

static int16 cifunc_write(canframe *cf)		// 3.0.1
{
	unsigned8 chan, mask;

	// Active channel selected
	if (can_netchan <= CAN_CHANNEL_MAX) {
		return CiWrite(can_netchan, cf, 1);
	}

  // Active channel NOT selected yet
  // Starting with the highest channel
  mask = 0x01 << CAN_CHANNEL_MAX;   // 3.0.3
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_work & mask) {
			CiWrite(CAN_CHANNEL_MAX-chan, cf, 1);
			can_sleep(1000);	// for Windows
		}
		mask >>= 1;
	}
	return 1;	// Always O'K
}

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
				if (datalink_mode != OFF) {
					if (cifunc_write(&cancache[cnt].cf) <= 0) break;
				}
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
	unsigned16 cnt, wrac, cabeg, caend;

	if (cf->id < CAN_CANID_NMT_ERROR_MIN || cf->id > CAN_CANID_NMT_ERROR_MAX) {
		if (node_state == CAN_NODE_STATE_INITIALISING || 
			node_state == CAN_NODE_STATE_STOPPED) {
			return CAN_ERRET_NODE_STATE;
		}
	}
	if (cf->id >= CAN_CANID_SRDO_MIN && cf->id <= CAN_CANID_SRDO_MAX) {
		cabeg = 0;		// 3.0.1 dedicated buffer 
		caend = 0;		// to keep SRDO frames sequence in cache
	} else {
		if (cf->id <= CAN_ID_PRIORITY_0) cabeg = 1;		  // 3.0.1 priority conditions changed
		else if (cf->id <= CAN_ID_PRIORITY_1) cabeg = 2;
		else if (cf->id <= CAN_ID_PRIORITY_2) cabeg = 3;
		else cabeg = 5;
		caend = CAN_WRITECACHE_SIZE - 1;
	}
	wrac = CAN_WRITECACHE_ATTEMPTS;
	do {
		CAN_CRITICAL_BEGIN
		sem_cantrans++;
		CAN_CRITICAL_END
		for (cnt = cabeg; cnt <= caend; cnt++) {
			CAN_CRITICAL_BEGIN
			cancache[cnt].busy++;
			if (cancache[cnt].busy == 0) {
				CAN_CRITICAL_END
				if (cancache[cnt].capture == 0) {
					cancache[cnt].capture = 1;
					cancache[cnt].cf = *cf;
					cancache[cnt].capture = 255;		// 2.2.2
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
		#if CAN_DATALINK_OUTOFF == TRUE
		datalink_mode = OFF;
		#else
		can_cache_overflow(node_state);
		#endif
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
	if (node_state == CAN_NODE_STATE_INITIALISING) return;
	if (cf->len > CAN_DATALEN_MAXIMUM) cf->len = CAN_DATALEN_MAXIMUM;
	cf->id &= CAN_MASK_CANID;
	if ((cf->flags & CAN_FLAG_RTR) != 0) {
		if (cf->id == (unsigned32)(node_id + CAN_CANID_NMT_ERROR_BASE)) {
			if (cf->len != CAN_DATALEN_ECP) return;		// 2.2.2
			node_guard_slave();
			return;
		}
		if (node_state != CAN_NODE_STATE_OPERATIONAL) return;
		find_pdo_rtr_tran_index((canlink)cf->id, &index);
		if (index >= CAN_INDEX_TRNPDO_COMM_MIN && index <= CAN_INDEX_TRNPDO_COMM_MAX) {
			transmit_rtr_pdo(index);
		}
		return;
	}
	if (cf->id == CAN_CANID_NMT) {
		if (cf->len != CAN_DATALEN_NMT_MC) return;		// 2.2.2
		nmt_slave_process(cf);
		return;
	}
	if (node_state == CAN_NODE_STATE_STOPPED) return;
	if (cf->id == CAN_CANID_GFC) {
		if (cf->len != CAN_DATALEN_GFC) return;
		consume_sr_gfc();
		return;
	}
	index = find_comm_recv_index((canlink)cf->id);
	if (index == CAN_INDEX_DUMMY) return;		// 3.0.1
	if (index == CAN_INDEX_SYNC_COBID) {
		sync_received(cf);
		return;
	}
	if (index >= CAN_INDEX_SRDO_COMM_MIN && index <= CAN_INDEX_SRDO_COMM_MAX) {
		receive_can_srdo(index, cf);
		return;
	}
	if (index == CAN_INDEX_TIME_COBID) {
		if (cf->len != CAN_DATALEN_TIME) return;	// 2.2.2
		consume_time(cf);
		return;
	}
	if (index >= CAN_INDEX_RCVPDO_COMM_MIN && index <= CAN_INDEX_RCVPDO_COMM_MAX) {
		receive_can_pdo(index, cf);
		return;
	}
	if (index == CAN_INDEX_SERVER_SDO_DEFAULT) {
		if (cf->len != CAN_DATALEN_SDO) return;		// 2.2.2
		receive_can_sdo(cf);
		return;
	}
}

static void can_read_handler(unsigned8 chan)   // 3.0.4 more robust code
{
	canframe cf;

	CAN_CRITICAL_BEGIN
	do {
		flag_canrecv = 0;
		sem_canrecv++;
		if (sem_canrecv == 0) {
			CAN_CRITICAL_END
			if (can_netchan > CAN_CHANNEL_MAX) can_netchan = chan;
			while (CiRead(can_netchan, &cf, 1) > 0) receive_can_data(&cf);
			CAN_CRITICAL_BEGIN
		}
		sem_canrecv--;
	} while (flag_canrecv != 0);
	flag_canrecv = 1;
	CAN_CRITICAL_END
}

void can_read_handler_0(canev ev)		// CAN controller channel 0
{
	can_read_handler(0);
}

void can_read_handler_1(canev ev)		// CAN controller channel 1
{
	can_read_handler(1);
}

void can_read_handler_2(canev ev)		// CAN controller channel 2
{
	can_read_handler(2);
}

void can_read_handler_3(canev ev)		// CAN controller channel 3
{
	can_read_handler(3);
}

void can_read_handler_4(canev ev)		// CAN controller channel 4
{
	can_read_handler(4);
}

void can_read_handler_5(canev ev)		// CAN controller channel 5
{
	can_read_handler(5);
}

void can_read_handler_6(canev ev)		// CAN controller channel 6
{
	can_read_handler(6);
}

void can_read_handler_7(canev ev)		// CAN controller channel 7
{
	can_read_handler(7);
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
