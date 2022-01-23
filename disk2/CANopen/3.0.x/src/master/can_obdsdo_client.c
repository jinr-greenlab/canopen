#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 0)

#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST

#define MASK_SDO_COBID_DYNAMIC		0x40000000	// SDO COBID value assigned statically or dynamically

static struct objsdo {
	unsigned32 cs;
	unsigned32 sc;
	unsigned8 id;
} sdo[CAN_NOF_NODES];

static int16 find_sdo_client_entry(canindex index, int16 *entry)
{
	if (index < CAN_INDEX_CLIENT_SDO_MIN || index >= CAN_INDEX_CLIENT_SDO_MIN+CAN_NOF_NODES) {
		*entry = -1;
		return CAN_ERRET_OBD_NOOBJECT;
	}
	*entry = index - CAN_INDEX_CLIENT_SDO_MIN;
	if ( (sdo[*entry].cs & CAN_MASK_COBID_INVALID) == 0 && (sdo[*entry].sc & CAN_MASK_COBID_INVALID) == 0 ) {
		return CAN_RETOK;
	}
	return CAN_ERRET_SDO_INVALID;
}

int16 find_sdo_client_send_canid(canindex index, canlink *canid)
{
	int16 entry, fnr;

	fnr = find_sdo_client_entry(index, &entry);
	if (fnr != CAN_RETOK) return fnr;
	*canid = sdo[entry].cs & CAN_MASK_CANID;
	return CAN_RETOK;
}

static int16 sdo_client_bytes_objsize(cansubind subind)
{
	switch (subind) {
		case 0:	return sizeof(unsigned8);
		case 1:	return sizeof(sdo[0].cs);
		case 2:	return sizeof(sdo[0].sc);
		case 3:	return sizeof(sdo[0].id);
	}
	return CAN_ERRET_OBD_NOSUBIND;
}

int16 get_sdo_client_bytes_objsize(canindex index, cansubind subind)
{
	int16 entry;

	find_sdo_client_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	return sdo_client_bytes_objsize(subind);
}

int16 read_sdo_client_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, entry;
	canbyte *bpnt;

	find_sdo_client_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = sdo_client_bytes_objsize(subind);
	if (size <= 0) return size;
	if (subind == 0) {
		*data = 3;
		return CAN_RETOK;
	}
	if (subind == 1) bpnt = (canbyte*)&(sdo[entry].cs);
	else if (subind == 2) bpnt = (canbyte*)&(sdo[entry].sc);
	else bpnt = (canbyte*)&(sdo[entry].id);
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_sdo_client_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, entry, fnr;
	unsigned32 buf;
	canbyte *bpnt;

	fnr = find_sdo_client_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = sdo_client_bytes_objsize(subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_ERRET_OBD_READONLY;
	bpnt = (canbyte*)&buf; buf = 0;
	#if CAN_BYTE_ORDER == REVERSE
		bpnt += (sizeof(buf) - size);	// 2.3.1
	#endif
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (subind == 3) {
		if (buf < CAN_NODE_ID_MIN || buf > CAN_NODE_ID_MAX) return CAN_ERRET_OBD_VALRANGE;
		sdo[entry].id = (unsigned8)buf;
		return CAN_RETOK;
	}
	if (fnr == CAN_RETOK && (buf & CAN_MASK_COBID_INVALID) == 0) return CAN_ERRET_OBD_OBJACCESS;
	if (CAN_ID_MODE == CANID11 && (buf & CAN_MASK_IDSIZE) != 0) return CAN_ERRET_OBD_VALRANGE;
	if (check_sdo_canid(index, subind, (canlink)buf) == RESTRICTED) return CAN_ERRET_OBD_VALRANGE;	// 2.2.1
	buf &= (CAN_MASK_COBID_INVALID | MASK_SDO_COBID_DYNAMIC | CAN_MASK_IDSIZE | CAN_MASK_CANID);	// 2.3.1
	if (subind == 1) sdo[entry].cs = buf;
	else if (subind == 2) sdo[entry].sc = buf;
	if (find_sdo_client_entry(index, &entry) == CAN_RETOK) {
		fnr = correct_recv_canid(index, (canlink)sdo[entry].sc);
		if (fnr != CAN_RETOK) sdo[entry].sc |= CAN_MASK_COBID_INVALID;
	} else {
		fnr = correct_recv_canid(index, CAN_CANID_DUMMY);
	}
	return fnr;
}

void can_init_sdo_client (void)
{
	unsigned16 cnt;

	for (cnt = 0; cnt < CAN_NOF_NODES; cnt++) {
		sdo[cnt].cs = CAN_MASK_COBID_INVALID | (CAN_CANID_SDO_CS_BASE+cnt+1);
		sdo[cnt].sc = CAN_MASK_COBID_INVALID | (CAN_CANID_SDO_SC_BASE+cnt+1);
		sdo[cnt].id = (unsigned8)(cnt+1);
	}
}

#endif

#endif
