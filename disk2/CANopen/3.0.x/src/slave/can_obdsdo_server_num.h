static struct objsdo {
	unsigned32 cs;
	unsigned32 sc;
	unsigned8 id;
} sdo[CAN_NOF_SDO_SERVER];

static int16 find_sdo_server_entry(canindex index, int16 *entry)
{
	if (index < CAN_INDEX_SERVER_SDO_MIN || index >= CAN_INDEX_SERVER_SDO_MIN+CAN_NOF_SDO_SERVER) {
		*entry = -1;
		return CAN_ERRET_OBD_NOOBJECT;
	}
	*entry = index - CAN_INDEX_SERVER_SDO_MIN;
	if ( (sdo[*entry].cs & CAN_MASK_COBID_INVALID) == 0 && (sdo[*entry].sc & CAN_MASK_COBID_INVALID) == 0 ) {
		return CAN_RETOK;
	} 
	return CAN_ERRET_SDO_INVALID;
}

int16 find_sdo_server_send_canid(canindex index, canlink *canid)
{
	int16 entry, fnr;

	fnr = find_sdo_server_entry(index, &entry);
	if (fnr != CAN_RETOK) return fnr;
	*canid = sdo[entry].sc & CAN_MASK_CANID;
	return CAN_RETOK;
}

static int16 sdo_server_bytes_objsize(canindex index, cansubind subind)
{
	if (subind == 0) return sizeof(unsigned8);
	if (subind == 1) return sizeof(sdo[0].cs);
	if (subind == 2) return sizeof(sdo[0].sc);
	if (subind == 3) {
		if (index != CAN_INDEX_SERVER_SDO_DEFAULT) return sizeof(sdo[0].id);
	}
	return CAN_ERRET_OBD_NOSUBIND;
}

int16 get_sdo_server_bytes_objsize(canindex index, cansubind subind)
{
	int16 entry;

	find_sdo_server_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	return sdo_server_bytes_objsize(index, subind);
}

int16 see_sdo_server_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_sdo_server_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_SERVER_SDO_DEFAULT || subind == 0) return CAN_MASK_ACCESS_RO;
	return CAN_MASK_ACCESS_RW;
}

int16 get_sdo_server_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_sdo_server_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0 || subind == 3) return CAN_DEFTYPE_UNSIGNED8;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_sdo_server_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, entry;
	canbyte *bpnt;

	find_sdo_server_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = sdo_server_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) {
		if (index == CAN_INDEX_SERVER_SDO_DEFAULT) *data = 2;
		else *data = 3;
		return CAN_RETOK;
	}
	if (subind == 1) bpnt = (canbyte*)&(sdo[entry].cs);
	else if (subind == 2) bpnt = (canbyte*)&(sdo[entry].sc);
	else bpnt = (canbyte*)&(sdo[entry].id);
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_sdo_server_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, entry, fnr;
	unsigned32 buf;
	canbyte *bpnt;

	fnr = find_sdo_server_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = sdo_server_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_SERVER_SDO_DEFAULT || subind == 0) {
		return CAN_ERRET_OBD_READONLY;
	}
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
	buf &= (CAN_MASK_COBID_INVALID | MASK_SDO_COBID_DYNAMIC | CAN_MASK_IDSIZE | CAN_MASK_CANID);
	if (subind == 1) sdo[entry].cs = buf;
	else if (subind == 2) sdo[entry].sc = buf;
	if (find_sdo_server_entry(index, &entry) == CAN_RETOK) {
		fnr = correct_recv_canid(index, (canlink)sdo[entry].cs);
		if (fnr != CAN_RETOK) sdo[entry].cs |= CAN_MASK_COBID_INVALID;
	} else {
		fnr = correct_recv_canid(index, CAN_CANID_DUMMY);
	}
	return fnr;
}

void can_init_sdo_server (void)
{
	unsigned16 cnt;
	cannode node;

	node = node_id;
	if (node_id < CAN_NODE_ID_MIN || node_id > CAN_NODE_ID_MAX) node = 0;
	sdo[0].cs = CAN_CANID_SDO_CS_BASE + node;
	sdo[0].sc = CAN_CANID_SDO_SC_BASE + node;
	sdo[0].id = 0;
	correct_recv_canid((canindex)CAN_INDEX_SERVER_SDO_MIN, (canlink)sdo[0].cs);
	for (cnt = 1; cnt < CAN_NOF_SDO_SERVER; cnt++) {
		sdo[cnt].cs = CAN_MASK_COBID_INVALID | (CAN_CANID_SDO_CS_BASE + node + cnt);
		sdo[cnt].sc = CAN_MASK_COBID_INVALID | (CAN_CANID_SDO_SC_BASE + node + cnt);
		sdo[cnt].id = 0;
	}
}
