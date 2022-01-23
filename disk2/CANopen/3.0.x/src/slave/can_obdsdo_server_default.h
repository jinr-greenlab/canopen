static struct objsdo {
	unsigned32 cs;
	unsigned32 sc;
} sdo;

int16 find_sdo_server_send_canid(canindex index, canlink *canid)
{
	if (index != CAN_INDEX_SERVER_SDO_DEFAULT) return CAN_ERRET_OBD_NOOBJECT;
	*canid = sdo.sc & CAN_MASK_CANID;
	return CAN_RETOK;
}

int16 get_sdo_server_bytes_objsize(canindex index, cansubind subind)
{
	if (index != CAN_INDEX_SERVER_SDO_DEFAULT) return CAN_ERRET_OBD_NOOBJECT;
	switch (subind) {
		case 0:	return sizeof(unsigned8);
		case 1:	return sizeof(sdo.cs);
		case 2:	return sizeof(sdo.sc);
	}
	return CAN_ERRET_OBD_NOSUBIND;
}

int16 see_sdo_server_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_sdo_server_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_MASK_ACCESS_RO;
}

int16 get_sdo_server_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_sdo_server_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_DEFTYPE_UNSIGNED8;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_sdo_server_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;

	size = get_sdo_server_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) {
		*data = 2;
		return CAN_RETOK;
	}
	if (subind == 1) bpnt = (canbyte*)&sdo.cs;
	else bpnt = (canbyte*)&sdo.sc;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_sdo_server_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size;

	size = get_sdo_server_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_ERRET_OBD_READONLY;
}

void can_init_sdo_server (void)
{
	cannode node;

	node = node_id;
	if (node_id < CAN_NODE_ID_MIN || node_id > CAN_NODE_ID_MAX) node = 0;
	sdo.cs = CAN_CANID_SDO_CS_BASE + node;
	sdo.sc = CAN_CANID_SDO_SC_BASE + node;
	correct_recv_canid(CAN_INDEX_SERVER_SDO_DEFAULT, (canlink)sdo.cs);
}
