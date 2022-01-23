#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 1)

#define MASK_TIME_CONSUME		0x80000000	// Consume time message mask
#define MASK_TIME_PRODUCE		0x40000000	// Produce time message mask
#define MASK_TIME_VALID			(MASK_TIME_CONSUME | MASK_TIME_PRODUCE)

static unsigned32 cobidtime;

int16 get_time_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_TIME_COBID) {
		if (subind == 0) return sizeof(cobidtime);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_time_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_time_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_MASK_ACCESS_RW;
}

int16 get_time_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_time_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_time_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;

	size = get_time_bytes_objsize(index, subind);
	if (size <= 0) return size;
	bpnt = (canbyte*)&cobidtime;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_time_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, fnr;
	unsigned32 buf;
	canbyte *bpnt;

	size = get_time_bytes_objsize(index, subind);
	if (size <= 0) return size;
	bpnt = (canbyte*)&buf; buf = 0;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if ( (cobidtime & MASK_TIME_VALID) != 0 && (buf & MASK_TIME_VALID) != 0 ) {
		return CAN_ERRET_OBD_OBJACCESS;
	}
	if (CAN_ID_MODE == CANID11 && (buf & CAN_MASK_IDSIZE) != 0) return CAN_ERRET_OBD_VALRANGE;
	if (check_canid_restricted((canlink)buf) == RESTRICTED) return CAN_ERRET_OBD_VALRANGE;	// 2.2.1
	buf &= (MASK_TIME_CONSUME | MASK_TIME_PRODUCE | CAN_MASK_IDSIZE | CAN_MASK_CANID);
	if (buf & MASK_TIME_PRODUCE) return CAN_ERRET_OBD_VALRANGE;
	if ( (buf & MASK_TIME_CONSUME) == 0) {
		fnr = correct_recv_canid(CAN_INDEX_TIME_COBID, CAN_CANID_DUMMY);
	} else {
		fnr = correct_recv_canid(CAN_INDEX_TIME_COBID, (canlink)buf);
	}
	if (fnr == CAN_RETOK) cobidtime = buf;
	return fnr;
}

void can_init_time(void)
{
	cobidtime = CAN_CANID_TIME;
}

#endif
