#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 0)

#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE

static struct lssaddress lssaddr;
static struct lssidentify lssident;
static unsigned8 lss_nodeid, lss_bitindex, lssfs_pos;
static unsigned32 serial_num;

static void reset_lssaddr(void)
{
	lssaddr.vendorid = 0;
	lssaddr.prodcode = 0;
	lssaddr.revnum = 0;
	lssaddr.serial = 0;
}

static void reset_lssidentify(void)
{
	lssident.vendorid = 0;
	lssident.prodcode = 0;
	lssident.revnum_low = 0;
	lssident.revnum_high = 0;
	lssident.serial_low = 0;
	lssident.serial_high = 0;
}

static void lss_response(unsigned8 cs)
{
	canframe tx;

	CLEAR_FRAME(&tx);
	tx.id = CAN_CANID_LSS_SLAVE;
	tx.len = CAN_DATALEN_LSS;
	tx.data[0] = cs;
	send_can_data(&tx);
}

static void process_fastscan(canframe *cf)
{
	unsigned32 idnumber, idlss, maskid;
	unsigned8 bitcheck, lsssub, lssnext;

	bitcheck = cf->data[5];
	if (bitcheck == LSSFS_BITCHECK_RESET) {
		lssfs_pos = 0;
		lss_response(LSS_CS_IDENTIFY_SLAVE);
		return;
	}
	if (lssfs_pos == LSSFS_POS_OFF) return;
	if (bitcheck > LSSFS_BITCHECK_MAX) {
		lssfs_pos = LSSFS_POS_OFF;
		return;
	}
	idnumber = canframe_to_u32(&cf->data[1]);
	lsssub = cf->data[6];
	lssnext = cf->data[7];
	if (lsssub != lssfs_pos) {
		lssfs_pos = LSSFS_POS_OFF;
		return;
	}
	if (lsssub == LSSFS_POS_VENDORID) idlss = CAN_VENDOR_ID;
	else if (lsssub == LSSFS_POS_PRODCODE) idlss = CAN_PROD_CODE;
	else if (lsssub == LSSFS_POS_REVNUM) idlss = CAN_REV_NUM;
	else if (lsssub == LSSFS_POS_SERIAL) idlss = serial_num;
	else {
		lssfs_pos = LSSFS_POS_OFF;
		return;
	}
	if (lssnext != lsssub) {
		if (idnumber != idlss) {
			lssfs_pos = LSSFS_POS_OFF;
		} else if (lssnext < lsssub) {
			lssfs_pos = LSSFS_POS_OFF;
			lss_state = LSS_CONFIGURATION;
			lss_response(LSS_CS_IDENTIFY_SLAVE);
		} else {
			lssfs_pos = lssnext;
			lss_response(LSS_CS_IDENTIFY_SLAVE);
		}
		return;
	}
	if (bitcheck < 31) {
		maskid = 0xFFFFFFFF << (bitcheck+1);
		if ((idnumber & maskid) != (idlss & maskid)) {
			lssfs_pos = LSSFS_POS_OFF;
			return;
		}
	}
	if ((idlss & (1 << bitcheck)) == 0) {
		lss_response(LSS_CS_IDENTIFY_SLAVE);
	}
}

static void process_waiting(canframe *cf)
{
	canframe tx;

	if (cf->data[0] == LSS_CS_SWSEL_VENDORID) {
		reset_lssaddr();
		lssaddr.vendorid = canframe_to_u32(&cf->data[1]);
	} else if (cf->data[0] == LSS_CS_SWSEL_PRODCODE) {
		lssaddr.prodcode = canframe_to_u32(&cf->data[1]);
	} else if (cf->data[0] == LSS_CS_SWSEL_REVNUM) {
		lssaddr.revnum = canframe_to_u32(&cf->data[1]);
	} else if (cf->data[0] == LSS_CS_SWSEL_SERIAL) {
		lssaddr.serial = canframe_to_u32(&cf->data[1]);
		if ( (lssaddr.vendorid == CAN_VENDOR_ID) && (lssaddr.prodcode == CAN_PROD_CODE) && 
			 (lssaddr.revnum == CAN_REV_NUM) && (lssaddr.serial == serial_num) ) {
			CLEAR_FRAME(&tx);
			tx.id = CAN_CANID_LSS_SLAVE;
			tx.len = CAN_DATALEN_LSS;
			tx.data[0] = LSS_CS_SWSEL_RESPONSE;
			if (send_can_data(&tx) == CAN_RETOK) lss_state = LSS_CONFIGURATION;
		}
	} else if (cf->data[0] == LSS_CS_FASTSCAN) {
		if (node_id == CAN_LSS_NODEID) process_fastscan(cf);
	}
}

static void process_configuration(canframe *cf)
{
	canframe tx;
	int32 swd;
	int16 fnr;

	CLEAR_FRAME(&tx);
	tx.id = CAN_CANID_LSS_SLAVE;
	tx.len = CAN_DATALEN_LSS;
	if (cf->data[0] == LSS_CS_CONFIG_NODEID) {
		tx.data[0] = LSS_CS_CONFIG_NODEID;
		if ((check_node_id(cf->data[1]) == CAN_RETOK) || (cf->data[1] == CAN_LSS_NODEID)) {
			if (send_can_data(&tx) == CAN_RETOK) lss_nodeid = cf->data[1];
		} else {
			tx.data[1] = 1;
			send_can_data(&tx);
		}
	} else if (cf->data[0] == LSS_CS_CONFIG_TIMING) {
		tx.data[0] = LSS_CS_CONFIG_TIMING;
		if (cf->data[1] != CIA_BITRATE_TABLE) {
			tx.data[1] = 1;
			send_can_data(&tx);
			return;
		}
		if (check_bitrate_index(cf->data[2]) == CAN_RETOK) { 
			if (send_can_data(&tx) == CAN_RETOK) lss_bitindex = cf->data[2];
		} else {
			tx.data[1] = 1;
			send_can_data(&tx);
		}
	} else if (cf->data[0] == LSS_CS_ACTIVATE_TIMING) {
		swd = 1000 * canframe_to_u16(&cf->data[1]);
		push_all_can_data();
		can_set_datalink_layer(OFF);
		push_all_can_data();
		can_sleep(swd);
		set_controller_bitrate(lss_bitindex);
		can_sleep(swd);
		can_set_datalink_layer(ON);
	} else if (cf->data[0] == LSS_CS_STORE_CONFIG) {
		tx.data[0] = LSS_CS_STORE_CONFIG;
		fnr = put_flash_nodeid(lss_nodeid);
		if (fnr == CAN_RETOK) fnr = put_flash_bitrate_index(lss_bitindex);
		if (fnr == CAN_RETOK) {
			node_id = lss_nodeid;
			bitrate_index = lss_bitindex;
		} else {
			tx.data[1] = 2;
		}
		send_can_data(&tx);
	} else if (cf->data[0] == LSS_CS_INQUIRE_VENDORID) {
		tx.data[0] = LSS_CS_INQUIRE_VENDORID;
		u32_to_canframe(CAN_VENDOR_ID, &tx.data[1]);
		send_can_data(&tx);
	} else if (cf->data[0] == LSS_CS_INQUIRE_PRODCODE) {
		tx.data[0] = LSS_CS_INQUIRE_PRODCODE;
		u32_to_canframe(CAN_PROD_CODE, &tx.data[1]);
		send_can_data(&tx);
	} else if (cf->data[0] == LSS_CS_INQUIRE_REVNUM) {
		tx.data[0] = LSS_CS_INQUIRE_REVNUM;
		u32_to_canframe(CAN_REV_NUM, &tx.data[1]);
		send_can_data(&tx);
	} else if (cf->data[0] == LSS_CS_INQUIRE_SERIAL) {
		tx.data[0] = LSS_CS_INQUIRE_SERIAL;
		u32_to_canframe(serial_num, &tx.data[1]);
		send_can_data(&tx);
	} else if (cf->data[0] == LSS_CS_INQUIRE_NODEID) {
		tx.data[0] = LSS_CS_INQUIRE_NODEID;
		tx.data[1] = node_id;
		send_can_data(&tx);
	}
}

void lss_slave_process(canframe *cf)
{
	if (cf->data[0] == LSS_CS_SWITCH_GLOBAL) {
		if (cf->data[1] == LSS_MODE_SWITCH_WAITING) lss_state = LSS_WAITING;
		else if (cf->data[1] == LSS_MODE_SWITCH_CONFIGURATION) lss_state = LSS_CONFIGURATION;
		return;
	}
	if (cf->data[0] == LSS_CS_IDENTIFY_VENDORID) {
		reset_lssidentify();
		lssident.vendorid = canframe_to_u32(&cf->data[1]);
		return;
	}
	if (cf->data[0] == LSS_CS_IDENTIFY_PRODCODE) {
		lssident.prodcode = canframe_to_u32(&cf->data[1]);
		return;
	}
	if (cf->data[0] == LSS_CS_IDENTIFY_REVNUM_LOW) {
		lssident.revnum_low = canframe_to_u32(&cf->data[1]);
		return;
	} 
	if (cf->data[0] == LSS_CS_IDENTIFY_REVNUM_HIGH) {
		lssident.revnum_high = canframe_to_u32(&cf->data[1]);
		return;
	}
	if (cf->data[0] == LSS_CS_IDENTIFY_SERIAL_LOW) {
		lssident.serial_low = canframe_to_u32(&cf->data[1]);
		return;
	}
	if (cf->data[0] == LSS_CS_IDENTIFY_SERIAL_HIGH) {
		lssident.serial_high = canframe_to_u32(&cf->data[1]);
		if ( (lssident.vendorid == CAN_VENDOR_ID) && (lssident.prodcode == CAN_PROD_CODE) && 
			 (CAN_REV_NUM >= lssident.revnum_low) && (CAN_REV_NUM <= lssident.revnum_high) && 
			 (serial_num >= lssident.serial_low) && (serial_num <= lssident.serial_high) ) {
			lss_response(LSS_CS_IDENTIFY_SLAVE);
		}
		return;
	}
	if (cf->data[0] == LSS_CS_IDENTIFY_NONCONF_REQ) {
		if (node_id == CAN_LSS_NODEID) {
			lss_response(LSS_CS_IDENTIFY_NONCONF_RESP);
		}
		return;
	}
	if (lss_state == LSS_WAITING) process_waiting(cf);
	else if (lss_state == LSS_CONFIGURATION) process_configuration(cf);
}

void can_init_lss(void)
{
	reset_lssaddr();
	reset_lssidentify();
	lss_nodeid = CAN_LSS_NODEID;
	lss_bitindex = CIA_BITRATE_INDEX_500;
	lssfs_pos = LSSFS_POS_OFF;
	serial_num = get_serial_number();
	correct_recv_canid(CAN_INDEX_DUMMY, CAN_CANID_DUMMY);
}

#endif

#endif
