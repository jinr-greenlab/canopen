#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 1)

static unsigned8 nmt_cs;

static unsigned16 prodhbt;
static unsigned32 beattot;
static unsigned32 beatcnt;

static unsigned16 guardtime;
static unsigned8  litif;
static unsigned8  toggle;
static unsigned32 lifetot;
static unsigned32 lifecnt;

static unsigned8  error_flag;

static unsigned32 bootup_cnt;
static unsigned32 operational_cnt;

static void send_node_state(unsigned8 tgl)
{
	canframe cf;

	CLEAR_FRAME(&cf);
	cf.id = CAN_CANID_NMT_ERROR_BASE + node_id;
	cf.data[0] = (node_state & 0x7F) | tgl;
	cf.len = CAN_DATALEN_ECP;
	send_can_data(&cf);
}

static void produce_bootup(void)	// 2.2.2
{
	canframe cf;

	node_state = CAN_NODE_STATE_PRE_OPERATIONAL;
	CLEAR_FRAME(&cf);
	cf.id = CAN_CANID_NMT_ERROR_BASE + node_id;
	cf.data[0] = CAN_NODE_STATE_INITIALISING & 0x7F;
	cf.len = CAN_DATALEN_ECP;
	send_can_data(&cf);
	set_led_green_blinking();
	if (CAN_OPERATIONAL_DELAY != 0) operational_cnt = 1 + CAN_OPERATIONAL_DELAY / CAN_TIMERUSEC;
}

static void start_ecp_slave(void)	// 2.2.2 some changes
{
	lifetot = 0;
	beattot = 0;
	lifecnt = 0xFFFFFFFF;	// 2.2.2 - starts with the first RTR or full count
	beatcnt = 0xFFFFFFFF;
	error_flag = RESOLVED;
	if (prodhbt > 0) {
		beattot = (unsigned32)prodhbt * 1000 / CAN_TIMERUSEC;
		if (beattot == 0) beattot = 1;
		beatcnt = beattot;
	}
	if (guardtime > 0) {
		lifetot = (unsigned32)litif * (1 + (unsigned32)guardtime * 1000 / CAN_TIMERUSEC);
	}
}

void start_node(void)
{
	node_state = CAN_NODE_STATE_OPERATIONAL;
	exit_error_state();
	run_sr_operations();
	set_led_green_on();
}

void stop_node(void)
{
	node_state = CAN_NODE_STATE_STOPPED;
	reset_sync_counter();
	enter_error_state();
	set_led_green_single_flash();
}

void enter_pre_operational(void)
{
	if (node_state == CAN_NODE_STATE_INITIALISING) {
		if (CAN_BOOTUP_DELAY == 0) produce_bootup();
		else bootup_cnt = 1 + CAN_BOOTUP_DELAY / CAN_TIMERUSEC;
		return;
	}
	node_state = CAN_NODE_STATE_PRE_OPERATIONAL;
	set_led_green_blinking();
}

void nmt_slave_process(canframe *cf)	// 3.0.1 EN50325-5 related changes
{
	if (cf->data[1] != 0 && cf->data[1] != node_id) return;
	if (get_sr_runstatus() == ON) {
		if ((cf->data[0] != CAN_NMT_START_REMOTE_NODE) &&
			(cf->data[0] != CAN_NMT_ENTER_PRE_OPERATIONAL)) {
			return;
		}
	}
	nmt_cs = cf->data[0];
	set_led_green_off();
	set_led_red_off();
	if (nmt_cs == CAN_NMT_RESET_NODE || nmt_cs == CAN_NMT_RESET_COMMUNICATION) {
		can_set_datalink_layer(OFF);
		node_state = CAN_NODE_STATE_INITIALISING;
	} else {
		can_set_datalink_layer(ON);
		if (nmt_cs == CAN_NMT_START_REMOTE_NODE) start_node();
		else if (nmt_cs == CAN_NMT_STOP_REMOTE_NODE) stop_node();
		else if (nmt_cs == CAN_NMT_ENTER_PRE_OPERATIONAL) enter_pre_operational();
	}
}

void nmt_slave_control(void)
{
	if (nmt_cs == CAN_NMT_RESET_NODE) {
		nmt_cs = CAN_NMT_CS_DUMMY;
		can_reset_node();
	} else if (nmt_cs == CAN_NMT_RESET_COMMUNICATION) {
		nmt_cs = CAN_NMT_CS_DUMMY;
		can_reset_communication();
	}
}

int16 get_ecpslave_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_PROD_HBT || index == CAN_INDEX_GUARD_TIME) {
		if (subind == 0) return sizeof(unsigned16);
		return CAN_ERRET_OBD_NOSUBIND;
	} else if (index == CAN_INDEX_LIFETIME_FACTOR) {
		if (subind == 0) return sizeof(unsigned8);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_ecpslave_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_ecpslave_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_MASK_ACCESS_RW;
}

int16 get_ecpslave_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_ecpslave_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_LIFETIME_FACTOR) return CAN_DEFTYPE_UNSIGNED8;
	return CAN_DEFTYPE_UNSIGNED16;
}

int16 read_ecpslave_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;

	size = get_ecpslave_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_PROD_HBT) bpnt = (canbyte*)&prodhbt;
	else if (index == CAN_INDEX_GUARD_TIME) bpnt = (canbyte*)&guardtime;
	else bpnt = (canbyte*)&litif;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_ecpslave_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;

	size = get_ecpslave_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_PROD_HBT) bpnt = (canbyte*)&prodhbt;
	else if (index == CAN_INDEX_GUARD_TIME) bpnt = (canbyte*)&guardtime;
	else bpnt = (canbyte*)&litif;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	start_ecp_slave();
	return CAN_RETOK;
}

void node_guard_slave(void)		// 2.2.2 some changes
{
	if (beattot != 0) return;
	send_node_state(toggle);
	toggle ^= 0x80;
	if (lifetot != 0) {
		lifecnt = lifetot;
		if (error_flag == OCCURRED) {
			error_flag = RESOLVED;
			life_guarding_resolved();
		}
	}
}

void manage_slave_ecp(void)
{
	if (bootup_cnt > 0) {
		bootup_cnt--;
		if (bootup_cnt == 0) produce_bootup();
	}
	if (node_state == CAN_NODE_STATE_INITIALISING) return;
	if (operational_cnt > 0) {
		operational_cnt--;
		if (operational_cnt == 0) start_node();
	}
	if (beattot != 0) {
		if (beatcnt > 0) {
			beatcnt--;
			if (beatcnt == 0) {
				beatcnt = beattot;
				send_node_state(0);
			}
		}
	} else if (lifetot != 0) {
		if (lifecnt > 0) {
			lifecnt--;
			if (lifecnt == 0) {		// 2.2.2 - NON-periodic, counting NOT resumed with error
				error_flag = OCCURRED;
				process_serious_error(CAN_SUBIND_ERRBEH_COMM);
				life_guarding_event();
			}
		}
	}
}

void can_init_ecp(void)
{
	nmt_cs = CAN_NMT_CS_DUMMY;
	prodhbt = CAN_HBT_PRODUCER_MS;
	bootup_cnt = 0;
	operational_cnt = 0;
	toggle = 0;
	guardtime = 0;
	litif = 0;
	start_ecp_slave();
}

#endif
