#include <can_header.h>

#if CHECK_VERSION(3, 0, 1)
//  CHECK_VERSION(2, 3, 2)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 2)
//  CHECK_VERSION(1, 7, 0)

#if CAN_OBJECT_EMCY == TRUE

#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

static unsigned32 cobidemcy;
static unsigned16 inhemcy;
static unsigned32 inhcnt;

int16 get_emcy_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_EMCY_COBID) {
		if (subind == 0) return sizeof(cobidemcy);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	if (index == CAN_INDEX_EMCY_INHIBIT) {
		if (subind == 0) return sizeof(inhemcy);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_emcy_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_emcy_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_MASK_ACCESS_RW;
}

int16 get_emcy_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_emcy_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_EMCY_INHIBIT) return CAN_DEFTYPE_UNSIGNED16;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_emcy_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;

	size = get_emcy_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_EMCY_COBID) bpnt = (canbyte*)&cobidemcy;
	else bpnt = (canbyte*)&inhemcy;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_emcy_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	unsigned32 buf;
	canbyte *bpnt;

	size = get_emcy_bytes_objsize(index, subind);
	if (size <= 0) return size;
	bpnt = (canbyte*)&buf; buf = 0;
	#if CAN_BYTE_ORDER == REVERSE
		bpnt += (sizeof(buf) - size);	// 2.3.1
	#endif
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (index == CAN_INDEX_EMCY_COBID) {
		if ( (cobidemcy & CAN_MASK_COBID_INVALID) == 0 && (buf & CAN_MASK_COBID_INVALID) == 0 ) {
			return CAN_ERRET_OBD_OBJACCESS;
		}
		if (CAN_ID_MODE == CANID11 && (buf & CAN_MASK_IDSIZE) != 0) return CAN_ERRET_OBD_VALRANGE;
		if (check_canid_restricted((canlink)buf) == RESTRICTED) return CAN_ERRET_OBD_VALRANGE;	// 2.2.1
		buf &= (CAN_MASK_COBID_INVALID | CAN_MASK_IDSIZE | CAN_MASK_CANID);
		cobidemcy = buf;
	} else {
		inhemcy = (unsigned16)buf;
	}
	return CAN_RETOK;
}

void control_emcy_inhibit(void)
{
	if (inhcnt > 0) inhcnt--;
}

int16 produce_emcy(unsigned16 errorcode, unsigned16 addinf, canbyte *mserr)
{
	canframe cf;

	set_error_field(errorcode, addinf);
	if ( (cobidemcy & CAN_MASK_COBID_INVALID) != 0) return CAN_ERRET_EMCY_INVALID;
	if (inhcnt != 0) return CAN_ERRET_EMCY_INHIBIT;
	inhcnt = (unsigned32)inhemcy * 100 / CAN_TIMERUSEC;
	CLEAR_FRAME(&cf);
	cf.id = cobidemcy & CAN_MASK_CANID;
	u16_to_canframe(errorcode, &cf.data[0]);
	cf.data[2] = read_error_register();
	cf.data[3] = *mserr; mserr++;
	cf.data[4] = *mserr; mserr++;
	cf.data[5] = *mserr; mserr++;
	cf.data[6] = *mserr; mserr++;
	cf.data[7] = *mserr;
	cf.len = CAN_DATALEN_EMCY;
	return send_can_data(&cf);
}

int16 produce_emcy_default(unsigned16 errorcode)
{
	canbyte mserr[5];

	mserr[0] = 0; mserr[1] = 0; mserr[2] = 0; mserr[3] = 0; mserr[4] = 0;
	return produce_emcy(errorcode, 0, mserr);
}

void can_init_emcy(void)
{
	cannode node;

	node = node_id;
	if (node_id < CAN_NODE_ID_MIN || node_id > CAN_NODE_ID_MAX) node = 0;
	cobidemcy = CAN_CANID_EMCY_BASE + node;
	inhemcy = CAN_EMCY_INHIBIT_100MCS;
	inhcnt = 0;
}

#elif CAN_APPLICATION_MODE == MASTER

int16 produce_emcy_default(unsigned16 errorcode)
{
	master_emcy(errorcode);
	return CAN_RETOK;
}

void can_init_emcy(void)
{
}

#endif

#endif

#endif
