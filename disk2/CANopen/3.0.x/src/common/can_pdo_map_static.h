static struct mappar {
	unsigned8 nrec;
	unsigned32 map[CAN_NOF_MAP_BYTEG];
} pdomap[NOF_PDO_MAPPED];

static int16 find_pdo_map_entry(canindex index, int16 *entry)	// 2.2.1 some changes
{
	if (index >= CAN_INDEX_RCVPDO_MAP_MIN && index < CAN_INDEX_RCVPDO_MAP_MIN+CAN_NOF_PDO_RECEIVE) {
		*entry = index - CAN_INDEX_RCVPDO_MAP_MIN;
	} else if (index >= CAN_INDEX_TRNPDO_MAP_MIN && index < CAN_INDEX_TRNPDO_MAP_MIN+CAN_NOF_PDO_TRANSMIT) {
		*entry = index - CAN_INDEX_TRNPDO_MAP_MIN + CAN_NOF_PDO_RECEIVE;
	} else {
		*entry = -1;
		return CAN_ERRET_OBD_NOOBJECT;
	}
	if (pdomap[*entry].nrec == 0) return CAN_ERRET_PDO_MAP_DEACT;
	return CAN_RETOK;
}

static int16 pdo_map_bytes_objsize(cansubind subind)
{
	if (subind == 0) return sizeof(unsigned8);
	if (subind <= CAN_NOF_MAP_BYTEG) return sizeof(unsigned32);
	return CAN_ERRET_OBD_NOSUBIND;
}

int16 check_pdo_map_object(canindex index)		// 2.2.1
{
	int16 entry;

	return find_pdo_map_entry(index, &entry);
}

int16 get_pdo_map_bytes_objsize(canindex index, cansubind subind)	// 2.2.1 some changes
{
	if (check_pdo_map_object(index) == CAN_ERRET_OBD_NOOBJECT) {
		return CAN_ERRET_OBD_NOOBJECT;
	}
	return pdo_map_bytes_objsize(subind);
}

int16 see_pdo_map_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_pdo_map_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_MASK_ACCESS_RO;
}

int16 get_pdo_map_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_pdo_map_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_DEFTYPE_UNSIGNED8;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_pdo_map_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, entry;
	canbyte *bpnt;

	find_pdo_map_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = pdo_map_bytes_objsize(subind);
	if (size <= 0) return size;
	if (subind == 0) bpnt = (canbyte*)&(pdomap[entry].nrec);
	else bpnt = (canbyte*)&(pdomap[entry].map[subind-1]);
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_pdo_map_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 entry;

	find_pdo_map_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	return CAN_ERRET_OBD_READONLY;
}

int16 map_pdo(canindex index, canframe *cf)
{
	int16 entry, fnr;
	unsigned16 len, cnt;
	unsigned8 nur;				// 3.0.1
	canindex mapind;
	cansubind mapsub;

	fnr = check_pdo_comm_object(index);		// 2.2.1
	if (fnr != CAN_RETOK) return fnr;
	fnr = find_pdo_map_entry((canindex)(index+0x200), &entry);
	if (fnr != CAN_RETOK) return fnr;
	cf->len = 0;
	nur = pdomap[entry].nrec;
	for (cnt = 0; cnt < nur; cnt++) {
		mapind = (pdomap[entry].map[cnt] & MASK_PDOMAP_INDEX) >> 16;
		mapsub = (pdomap[entry].map[cnt] & MASK_PDOMAP_SUBIND) >> 8;
		len = 1 + ((pdomap[entry].map[cnt] & MASK_PDOMAP_LENGTH) - 1) / CAN_SIZEOF_FACTOR;
		if ((cf->len + len) > CAN_DATALEN_MAXIMUM) return CAN_ERRET_PDO_ERRMAP;
		fnr = server_read_obd_network(mapind, mapsub, &cf->data[cf->len]);
		if (fnr != CAN_RETOK) return fnr;
		cf->len += len;
	}
	return CAN_RETOK;
}

int16 activate_pdo(canindex index, canframe *cf)
{
	int16 entry, fnr;
	unsigned16 pdoelm, cnt;		// 2.3.1
	unsigned8 nur;				// 3.0.1
	canindex mapind;
	cansubind mapsub;

	fnr = check_pdo_comm_object(index);		// 2.2.1
	if (fnr != CAN_RETOK) return fnr;
	fnr = find_pdo_map_entry((canindex)(index+0x200), &entry);
	if (fnr != CAN_RETOK) return fnr;
	nur = pdomap[entry].nrec;
	pdoelm = 0;
	for (cnt = 0; cnt < nur; cnt++) {
		pdoelm += 1 + ((pdomap[entry].map[cnt] & MASK_PDOMAP_LENGTH) - 1) / CAN_SIZEOF_FACTOR;
		if (pdoelm > cf->len) {
			#if CAN_OBJECT_EMCY == TRUE
			produce_emcy_default(CAN_EMCY_PDOLENERR);
			#endif
			return CAN_ERRET_PDO_ERRMAP;
		}
	}
	pdoelm = 0;
	for (cnt = 0; cnt < nur; cnt++) {
		mapind = (pdomap[entry].map[cnt] & MASK_PDOMAP_INDEX) >> 16;
		mapsub = (pdomap[entry].map[cnt] & MASK_PDOMAP_SUBIND) >> 8;
		fnr = server_write_obd_network(mapind, mapsub, &cf->data[pdoelm]);
		if (fnr != CAN_RETOK) return fnr;
		pdo_activated_slave(mapind, mapsub);
		pdoelm += 1 + ((pdomap[entry].map[cnt] & MASK_PDOMAP_LENGTH) - 1) / CAN_SIZEOF_FACTOR;
	}
	set_pdo_recv_event_timer(index);
	return CAN_RETOK;
}

void can_init_pdo_map(void)
{
	unsigned16 entry, cnt;

	for (entry = 0; entry < NOF_PDO_MAPPED; entry++) {
		pdomap[entry].nrec = 0;
		for (cnt = 0; cnt < CAN_NOF_MAP_BYTEG; cnt++) pdomap[entry].map[cnt] = 0;
	}
	#include "pdomapping/__map__static.h"
}
