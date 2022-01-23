#include <can_header.h>

#if CHECK_VERSION(3, 0, 4)
//  CHECK_VERSION(2, 3, 3)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 3)
//  CHECK_VERSION(1, 7, 1)

static int16 sem_sys=-1024;

static void canopen_timer(void)   // 3.0.1 renamed
{
	CAN_CRITICAL_BEGIN    // For the threaded timer
	led_control();
	sem_sys++;
	if (sem_sys == 0) {
		control_sync();
		#if CAN_APPLICATION_MODE == MASTER
			can_client_control();
			#if CAN_NMT_MODE == MASTER
			manage_master_ecp();
			#elif CAN_NMT_MODE == SLAVE
			manage_slave_ecp();
			#endif
		#elif CAN_APPLICATION_MODE == SLAVE
			can_server_control();
			#if CAN_NMT_MODE == MASTER
			manage_master_ecp();
			#elif CAN_NMT_MODE == SLAVE
			manage_slave_ecp();
			#endif
			#if CAN_OBJECT_EMCY == TRUE
			control_emcy_inhibit();
			#endif
		#elif CAN_APPLICATION_MODE == TEST
			manage_master_ecp();
			manage_slave_ecp();
			can_client_control();
			can_server_control();
			#if CAN_OBJECT_EMCY == TRUE
			control_emcy_inhibit();
			#endif
		#endif
		control_pdo();
		push_all_can_data();
		#if CAN_APPLICATION_MODE == TEST
		can_read_handler(0);
		#endif
	#if CAN_OBJECT_EMCY == TRUE
	} else if (sem_sys == 1) {		// 2.3.1 moved here
		can_timer_overlap();		// 2.3.1 moved here
	#endif
	}
	sem_sys--;
	CAN_CRITICAL_END    // For the threaded timer
	#if CAN_PROTOCOL_BLOCK == TRUE && (CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST)
	if (sem_sys == -1) can_server_upload_block();
	// 2.2.1 commented
	// The code may be used ONLY with the re-entrant timer
	// for time-guaranteed upload block protocol response
	// The function is also called from canopen_monitor(), but software jitter is possible
	#endif
}
// The CANopen timer signal handler function canopen_timer()
// may be activated with non self-blocked high priority timer.

static void can_reset_other(void)
{
	can_init_recv_canids();
	can_init_sync();
	can_init_pdo();
	can_init_led_indication();
#if CAN_OBJECT_EMCY == TRUE
	can_init_emcy();
#endif
#if CAN_OBJECT_TIME == TRUE
	can_init_time();
#endif
#if CAN_NMT_MODE == SLAVE
	can_init_ecp();
#endif
#if CAN_APPLICATION_MODE == MASTER
	can_init_sdo_client();
	master_init_manstan_communication();
#elif CAN_APPLICATION_MODE == SLAVE
	can_init_sdo_server();
	#if CAN_PROTOCOL_LSS == TRUE
	can_init_lss();
	#endif
	slave_init_manstan_communication();
#elif CAN_APPLICATION_MODE == TEST
	can_init_sdo_client();
	can_init_sdo_server();
	master_init_manstan_communication();
	slave_init_manstan_communication();
#endif
}

#if CAN_APPLICATION_MODE != TEST

int16 set_controller_bitrate(unsigned8 br_index)
{
	if (CiStop(can_netchan) < 0) return CAN_ERRET_CI_STOP;
	if (br_index == CIA_BITRATE_INDEX_1000) {
		if (CiSetBaud(can_netchan, BCI_1M) < 0) return CAN_ERRET_CI_BITRATE;
	} else if (br_index == CIA_BITRATE_INDEX_800) {
		if (CiSetBaud(can_netchan, BCI_800K) < 0) return CAN_ERRET_CI_BITRATE;
	} else if (br_index == CIA_BITRATE_INDEX_500) {
		if (CiSetBaud(can_netchan, BCI_500K) < 0) return CAN_ERRET_CI_BITRATE;
	} else if (br_index == CIA_BITRATE_INDEX_250) {
		if (CiSetBaud(can_netchan, BCI_250K) < 0) return CAN_ERRET_CI_BITRATE;
	} else if (br_index == CIA_BITRATE_INDEX_125) {
		if (CiSetBaud(can_netchan, BCI_125K) < 0) return CAN_ERRET_CI_BITRATE;
	} else if (br_index == CIA_BITRATE_INDEX_50) {
		if (CiSetBaud(can_netchan, BCI_50K) < 0) return CAN_ERRET_CI_BITRATE;
	} else if (br_index == CIA_BITRATE_INDEX_20) {
		if (CiSetBaud(can_netchan, BCI_20K) < 0) return CAN_ERRET_CI_BITRATE;
	} else if (br_index == CIA_BITRATE_INDEX_10) {
		if (CiSetBaud(can_netchan, BCI_10K) < 0) return CAN_ERRET_CI_BITRATE;
	} else return CAN_ERRET_BITRATE;		// 2.2.1
	if (CiStart(can_netchan) < 0) return CAN_ERRET_CI_START;
	return CAN_RETOK;
}

static int16 can_init_controller(void)
{
	if (CiStop(can_netchan) < 0) return CAN_ERRET_CI_STOP;
	if (CiClose(can_netchan) < 0) return CAN_ERRET_CI_CLOSE;
	#if CAN_ID_MODE == CANID11
	if (CiOpen(can_netchan, CIO_CAN11) < 0) return CAN_ERRET_CI_OPEN;
	#elif CAN_ID_MODE == CANID29
	if (CiOpen(can_netchan, CIO_CAN29) < 0) return CAN_ERRET_CI_OPEN;
	#endif
	if (CiSetWriteTout(can_netchan, 0) < 0) return CAN_ERRET_CI_WTOUT;	// NO timeout
	#if CAN_FRAME_READ_MODE == SIGNAL
	if (CiSetCB(can_netchan, CIEV_RC, can_read_handler) < 0) return CAN_ERRET_CI_HANDLER;
	#endif
	if (CiSetCB(can_netchan, CIEV_CANERR, consume_controller_error) < 0) return CAN_ERRET_CI_HANDLER;
	bitrate_index = get_bit_rate_index();
	return set_controller_bitrate(bitrate_index);
}

#endif

int16 can_reset_communication(void)
{
	#if CAN_APPLICATION_MODE != TEST
	int16 fnr;
	#endif

	sem_sys -= 1024;
	node_state = CAN_NODE_STATE_INITIALISING;
	#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE
	lss_state = LSS_OFF;
	#endif
	#if CAN_APPLICATION_MODE != TEST
	if (CiStop(can_netchan) < 0) return CAN_ERRET_CI_STOP;
	#endif
	node_id = get_node_id();
	#if CAN_APPLICATION_MODE == MASTER
		if (node_id > CAN_NODE_ID_MAX) return CAN_ERRET_NODEID;
	#elif CAN_APPLICATION_MODE == SLAVE
		#if CAN_PROTOCOL_LSS == TRUE
		if (node_id == CAN_LSS_NODEID) {
			lss_state = LSS_WAITING;
		} else
		#endif
		if (node_id < CAN_NODE_ID_MIN || node_id > CAN_NODE_ID_MAX) {
			return CAN_ERRET_NODEID;
		}
	#endif
	can_init_io();
	#if CAN_APPLICATION_MODE != TEST
		fnr = can_init_controller();		// 2.3.3 moved here due to CAN acceptance filter reset
		if (fnr != CAN_RETOK) return fnr;
	#endif
	can_reset_other();		// CAN acceptance filter is being formed
	#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		clear_error_register(CAN_ERRBIT_COMM);
	#endif
	#if CAN_APPLICATION_MODE == TEST
		can_init_nmt_master();
		enter_pre_operational();
	#else
		#if CAN_NMT_MODE == MASTER
		can_init_nmt_master();
		#endif
		#if CAN_APPLICATION_MODE == SLAVE && CAN_OBJECT_RE_STORE == TRUE
		can_process_saved(CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2);
		#endif
		#if CAN_NMT_MODE == MASTER
		start_can_master();
		#elif CAN_NMT_MODE == SLAVE
		enter_pre_operational();
		#endif
	#endif
	sem_sys += 1024;
	return CAN_RETOK;
}

int16 can_reset_node(void)		// 3.0.1 some changes
{
	int16 fnr;

	sem_sys = -1024;
	node_state = CAN_NODE_STATE_INITIALISING;
	#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE
	lss_state = LSS_OFF;
	#endif
	can_cancel_system_timer();
	#if CAN_APPLICATION_MODE != TEST
	fnr = CiStop(can_netchan);	// to disable CAN interrupts before
	#endif
	CAN_CRITICAL_INIT		// 2.3.2 called separately
	#if CAN_APPLICATION_MODE != TEST
	if (fnr < 0) return CAN_ERRET_CI_STOP;
	#endif
	#if CAN_OBJECT_RE_STORE == TRUE || CAN_OBJECT_LSS == TRUE
		#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		fnr = check_init_flash();
		if (fnr != CAN_RETOK) return fnr;
		#endif
	#endif
	node_id = get_node_id();
	#if CAN_APPLICATION_MODE == MASTER
		if (node_id > CAN_NODE_ID_MAX) return CAN_ERRET_NODEID;
	#elif CAN_APPLICATION_MODE == SLAVE
		#if CAN_PROTOCOL_LSS == TRUE
		if (node_id == CAN_LSS_NODEID) {
			lss_state = LSS_WAITING;
		} else
		#endif
		if (node_id < CAN_NODE_ID_MIN || node_id > CAN_NODE_ID_MAX) {
			return CAN_ERRET_NODEID;
		}
	#endif
	#if !(CAN_APPLICATION_MODE == SLAVE && CAN_PROTOCOL_BLOCK == FALSE && CAN_NOF_SDO_SERVER == 1)
	can_init_malloc();
	#endif
	#if CAN_PROTOCOL_BLOCK == TRUE || CAN_OBJECT_RE_STORE == TRUE
	can_init_crc();
	#endif
	#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		can_init_error();
	#endif
	#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE
		#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		can_init_err_behaviour();
		#endif
	#endif
	#if CAN_OBJECT_RE_STORE == TRUE
		#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		can_init_re_store();
		#endif
	#endif
	#if CAN_APPLICATION_MODE == MASTER
		can_init_client();
		master_init_manstan_application();
	#elif CAN_APPLICATION_MODE == SLAVE
		can_init_server();
		slave_init_manstan_application();
	#elif CAN_APPLICATION_MODE == TEST
		can_init_server();
		can_init_client();
		master_init_manstan_application();
		slave_init_manstan_application();
	#endif
	can_init_system_timer(canopen_timer);		// 2.3.1 API changed. Before can_init_controller() for Windows only
	can_init_io();			// 3.0.2 moved here to init sem_canrecv
	#if CAN_APPLICATION_MODE != TEST
		fnr = can_init_controller();		// 2.3.3 moved here due to CAN acceptance filter reset
		if (fnr != CAN_RETOK) return fnr;
	#endif
	can_reset_other();		// CAN acceptance filter is being formed
	#if CAN_APPLICATION_MODE == TEST
		can_init_nmt_master();
		enter_pre_operational();
	#else
		#if CAN_NMT_MODE == MASTER
		can_init_nmt_master();
		#endif
		#if CAN_APPLICATION_MODE == SLAVE && CAN_OBJECT_RE_STORE == TRUE
		can_process_saved(CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2 | CAN_MASK_LOAD_APPL);
		#endif
		#if CAN_NMT_MODE == MASTER
		start_can_master();
		#elif CAN_NMT_MODE == SLAVE
		enter_pre_operational();
		#endif
	#endif
	sem_sys = -1;
	return CAN_RETOK;
}

int16 start_can_device(unsigned8 net)
{
	CAN_CRITICAL_INIT   // 2.3.2 called separately
	can_netchan = net;
	#if CAN_APPLICATION_MODE != TEST
	if (CiInit() < 0) return CAN_ERRET_CI_INIT;
	if (CiOpen(can_netchan, 0) < 0) return CAN_ERRET_CI_OPEN;
	enable_can_transmitter();
	#endif
	return can_reset_node();
}

int16 stop_can_device(void)   // 3.0.4 return conditions changed
{
	sem_sys = -1024;
	node_state = CAN_NODE_STATE_INITIALISING;
	can_set_datalink_layer(OFF);
	disable_can_transmitter();
	can_cancel_system_timer();
	#if CAN_APPLICATION_MODE != TEST
	CiStop(can_netchan);
	CiClose(can_netchan);
	#endif
	return CAN_RETOK;
}

void canopen_monitor(void)   // 2.2.1 renamed
{
	#if CAN_FRAME_READ_MODE == POLL
	can_read_handler(0);
	#endif
	#if CAN_NMT_MODE == SLAVE
	nmt_slave_control();
	#endif
	#if CAN_PROTOCOL_BLOCK == TRUE && (CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST)
	can_server_upload_block();
	#endif
}

#endif
