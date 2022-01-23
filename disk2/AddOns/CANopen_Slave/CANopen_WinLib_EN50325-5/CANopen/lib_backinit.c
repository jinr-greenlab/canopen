#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 4)

static int16 sem_sys=-1024;
static unsigned8 flag_netproc;		// Networks processed flag
static unsigned8 netmask_free;		// Free CAN networks mask

static void canopen_timer(void)		// 3.0.1 renamed
{
	CAN_CRITICAL_BEGIN    // For the threaded timer
	led_control();
	sem_sys++;
	if (sem_sys == 0) {
		application_timer_routine();
		control_sync();
		manage_slave_ecp();
		control_emcy_inhibit();
		can_server_control();
		control_pdo();
		control_srdo();
		push_all_can_data();
	} else if (sem_sys == 1) {
		can_timer_overlap();
	}
	sem_sys--;
	CAN_CRITICAL_END    // For the threaded timer
}
// The CANopen timer signal handler function canopen_timer()
// may be activated with non self-blocked high priority timer.

static void can_reset_other(void)
{
	can_init_recv_canids();
	can_init_sync();
	can_init_pdo();
	can_init_srdo();
	can_init_led_indication();
	can_init_emcy();
	can_init_time();
	can_init_ecp();
	can_init_sdo_server();
	slave_init_standev_communication();
	slave_init_manspec_communication();
}

static void process_networks(void)
{
	unsigned8 chan, mask;

	if (flag_netproc == FALSE) return;
	if (can_netchan > CAN_CHANNEL_MAX) return;
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (chan != can_netchan) {
			if (netmask_work & mask) {
				CiStop(chan);
				CiClose(chan);
			}
		}
		mask <<= 1;
	}
	netmask_work = 1 << can_netchan;
	CiSetCB(can_netchan, CIEV_CANERR, consume_controller_error);
	red_led_off();			// Switching off leds
	green_led_off();		// of the unused networks
	flag_netproc = FALSE;
}

static void find_free_networks(void)
{
	unsigned8 chan, mask;

	netmask_free = CAN_MASK_NETWORKS;
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_free & mask) {
			if (CiOpen(chan, 0) < 0) {
				netmask_free &= ~mask;
			} else {
				CiClose(chan);		// Only free channels closed
			}
		}
		mask <<= 1;
	}
}

static void can_init_controller(void)
{
  void (*hdl)(canev);
	unsigned8 chan, mask;
	unsigned8 brind;
	int16 cfr;

	flag_netproc = FALSE;
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_work & mask) {
			CiStop(chan);
			CiClose(chan);
		}
		mask <<= 1;
	}
	netmask_work = 0;
	can_netchan = CAN_CHANNEL_DUMMY;
	find_free_networks();    // All free channels closed
	if (netmask_free == 0) return;
	brind = get_bit_rate_index();
	netmask_work = netmask_free;
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_work & mask) {
			cfr = CiOpen(chan, CIO_CAN11);
			if (cfr >= 0) CiSetWriteTout(chan, 0);    // NO timeout
			if (cfr >= 0) {
				     if (chan == 0) hdl = can_read_handler_0;
				else if (chan == 1) hdl = can_read_handler_1;
				else if (chan == 2) hdl = can_read_handler_2;
				else if (chan == 3) hdl = can_read_handler_3;
				else if (chan == 4) hdl = can_read_handler_4;
				else if (chan == 5) hdl = can_read_handler_5;
				else if (chan == 6) hdl = can_read_handler_6;
				else if (chan == 7) hdl = can_read_handler_7;
        cfr = CiSetCB(chan, CIEV_RC, hdl);
			}
			if (cfr >= 0) {
				if (brind == CIA_BITRATE_INDEX_1000) {
					cfr = CiSetBaud(chan, BCI_1M);
				} else if (brind == CIA_BITRATE_INDEX_800) {
					cfr = CiSetBaud(chan, BCI_800K);
				} else if (brind == CIA_BITRATE_INDEX_500) {
					cfr = CiSetBaud(chan, BCI_500K);
				} else if (brind == CIA_BITRATE_INDEX_250) {
					cfr = CiSetBaud(chan, BCI_250K);
				} else if (brind == CIA_BITRATE_INDEX_125) {
					cfr = CiSetBaud(chan, BCI_125K);
				} else if (brind == CIA_BITRATE_INDEX_50) {
					cfr = CiSetBaud(chan, BCI_50K);
				} else if (brind == CIA_BITRATE_INDEX_20) {
					cfr = CiSetBaud(chan, BCI_20K);
				} else if (brind == CIA_BITRATE_INDEX_10) {
					cfr = CiSetBaud(chan, BCI_10K);
				} else cfr = -1;
			}
			if (cfr < 0) {
				netmask_work &= ~mask;
				CiClose(chan);
			}
		}
		mask <<= 1;
	}
	if (netmask_work == 0) return;
	cifunc_start();
	flag_netproc = TRUE;
}

unsigned8 get_netmask_free(void)
{
	return netmask_free;
}

int16 cifunc_start(void)
{
	unsigned8 chan, mask;
	int16 fnr;

	if (netmask_work == 0) return CAN_ERRET_CI_NETWORKS;
	fnr = CAN_RETOK;
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_work & mask) {
			if (CiStart(chan) < 0) fnr = CAN_ERRET_CI_START;
		}
		mask <<= 1;
	}
	return fnr;
}

int16 cifunc_stop(void)
{
	unsigned8 chan, mask;
	int16 fnr;

	if (netmask_work == 0) return CAN_ERRET_CI_NETWORKS;
	fnr = CAN_RETOK;
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_work & mask) {
			if (CiStop(chan) < 0) fnr = CAN_ERRET_CI_STOP;
		}
		mask <<= 1;
	}
	return fnr;
}

int16 can_reset_communication(void)
{
	sem_sys -= 1024;
	node_state = CAN_NODE_STATE_INITIALISING;
	if (cifunc_stop() == CAN_ERRET_CI_STOP) return CAN_ERRET_CI_STOP;
	node_id = get_node_id();
	if (node_id < CAN_NODE_ID_MIN || node_id > CAN_NODE_ID_MAX) return CAN_ERRET_NODEID;
	can_init_io();
	can_init_controller();
	if (netmask_work == 0) return CAN_ERRET_CI_NETWORKS;
	can_reset_other();		// CAN acceptance filter is being formed
	clear_error_register(CAN_ERRBIT_COMM);
	can_process_saved(CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2);
	enter_pre_operational();
	sem_sys += 1024;
	return CAN_RETOK;
}

int16 can_reset_node(void)
{
	int16 fnr;

	sem_sys = -1024;
	node_state = CAN_NODE_STATE_INITIALISING;
	stop_hardware();
	can_cancel_system_timer();
	fnr = cifunc_stop();	// to disable CAN interrupts before
	CAN_CRITICAL_INIT		// 2.3.2 called separately
	if (fnr == CAN_ERRET_CI_STOP) return CAN_ERRET_CI_STOP;
	fnr = check_init_flash();
	if (fnr != CAN_RETOK) return fnr;
	node_id = get_node_id();
	if (node_id < CAN_NODE_ID_MIN || node_id > CAN_NODE_ID_MAX) return CAN_ERRET_NODEID;
	can_init_crc();
	can_init_error();
	can_init_err_behaviour();
	can_init_re_store();
	can_init_server();
	slave_init_standev_application();
	slave_init_manspec_application();
	can_init_io();			// 3.0.2 moved here to init sem_canrecv
	can_init_system_timer(canopen_timer);		// Before can_init_controller() for Windows only
	can_init_controller();
	if (netmask_work == 0) return CAN_ERRET_CI_NETWORKS;
	can_reset_other();		// CAN acceptance filter is being formed
	can_process_saved(CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2 | CAN_MASK_LOAD_APPL);
	start_hardware();
	enter_pre_operational();
	sem_sys = -1;
	return CAN_RETOK;
}

int16 start_can_device(void)
{
	CAN_CRITICAL_INIT		// 2.3.2 called separately
	netmask_free = 0;
	netmask_work = 0;
	can_netchan = CAN_CHANNEL_DUMMY;
	flag_netproc = FALSE;
	if (CiInit() < 0) return CAN_ERRET_CI_INIT;
	find_free_networks();
	if (netmask_free == 0) return CAN_ERRET_CI_NETWORKS;
	enable_can_transmitter();
	application_init_device_routine();
	return can_reset_node();
}

int16 stop_can_device(void)    // 3.0.3 some changes
{
	unsigned8 chan, mask;

	sem_sys = -1024;
	node_state = CAN_NODE_STATE_INITIALISING;
	can_set_datalink_layer(OFF);
	disable_can_transmitter();
	stop_hardware();
	can_cancel_system_timer();
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_work & mask) {
			CiStop(chan);
			CiClose(chan);
		}
		mask <<= 1;
	}
	netmask_free = 0;
	netmask_work = 0;
	can_netchan = CAN_CHANNEL_DUMMY;
	flag_netproc = FALSE;
	return CAN_RETOK;
}

void canopen_monitor(void)	// 2.2.1 renamed
{
	nmt_slave_control();
	process_networks();
	application_monitor_routine();
}

#endif
