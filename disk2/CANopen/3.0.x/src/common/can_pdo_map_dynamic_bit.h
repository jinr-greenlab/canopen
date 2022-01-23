static struct mappar {
	unsigned8 nmax;
	unsigned8 nrec;
	unsigned32 *pointer;
} pdomap[NOF_PDO_MAPPED];

#include "pdomapping/can_mappdo_main.h"

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
	if (pdomap[*entry].nmax == 0) {
		*entry = -1;
		return CAN_ERRET_OBD_NOOBJECT;
	}
	if (pdomap[*entry].nrec == 0) return CAN_ERRET_PDO_MAP_DEACT;
	return CAN_RETOK;
}

static int16 pdo_map_bytes_objsize(int16 entry, cansubind subind)
{
	if (subind == 0) return sizeof(unsigned8);
	if (subind <= pdomap[entry].nmax) return sizeof(unsigned32);
	return CAN_ERRET_OBD_NOSUBIND;
}

int16 check_pdo_map_object(canindex index)		// 2.2.1
{
	int16 entry;

	return find_pdo_map_entry(index, &entry);
}

int16 get_pdo_map_bytes_objsize(canindex index, cansubind subind)
{
	int16 entry;

	find_pdo_map_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	return pdo_map_bytes_objsize(entry, subind);
}

int16 see_pdo_map_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_pdo_map_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_MASK_ACCESS_RW;
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
	size = pdo_map_bytes_objsize(entry, subind);
	if (size <= 0) return size;
	if (subind == 0) bpnt = (canbyte*)&(pdomap[entry].nrec);
	else bpnt = (canbyte*)(pdomap[entry].pointer + subind-1);
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

static int32 test_pdo_map(cannode node, canindex index, unsigned32 map)
{
	canindex mapind;
	cansubind mapsub;
	int32 size;
	int16 accs;

	mapind = (map & MASK_PDOMAP_INDEX) >> 16;
	mapsub = (map & MASK_PDOMAP_SUBIND) >> 8;
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	accs = node_see_manstan_access(node, mapind, mapsub);
	#elif CAN_APPLICATION_MODE == SLAVE
	accs = server_see_access(mapind, mapsub);
	#endif
	if (accs < 0) return CAN_ERRET_PDO_NOMAP;
	if ((accs & CAN_MASK_ACCESS_PDO) == 0) return CAN_ERRET_PDO_NOMAP;
	if ((accs & CAN_MASK_ACCESS_RO) == 0) {
		if (index >= CAN_INDEX_TRNPDO_MAP_MIN && index <= CAN_INDEX_TRNPDO_MAP_MAX) {
			return CAN_ERRET_PDO_NOMAP;
		}
	}
	if ((accs & CAN_MASK_ACCESS_WO) == 0) {
		if (index >= CAN_INDEX_RCVPDO_MAP_MIN && index <= CAN_INDEX_RCVPDO_MAP_MAX) {
			return CAN_ERRET_PDO_NOMAP;
		}
	}
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	size = node_get_manstan_objsize(node, mapind, mapsub, BITS);
	#elif CAN_APPLICATION_MODE == SLAVE
	size = server_get_object_size(mapind, mapsub, BITS);
	#endif
	if (size <= 0) return CAN_ERRET_PDO_NOMAP;
	if (size > CAN_NOF_PDOBIT_MAX || (map & MASK_PDOMAP_LENGTH) != (unsigned32)size) {
		return CAN_ERRET_PDO_ERRMAP;
	}
	return size;
}

int16 write_pdo_map_objdict(canindex index, cansubind subind, canbyte *data)	// 3.0.1 some changes
{
	cannode node;
	int16 entry;
	int32 size, cnt;
	unsigned16 len;
	unsigned32 buf;
	canbyte *bpnt;

	find_pdo_map_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = pdo_map_bytes_objsize(entry, subind);
	if (size <= 0) return (int16)size;
	node = 0;
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	size = get_pdo_node((canindex)(index-0x200), &node);
	if (size < 0) return (int16)size;
	#endif
	if (subind == 0) {
		if (*data == 0) {
			pdomap[entry].nrec = 0;
			return set_pdo_state((canindex)(index-0x200), NOT_VALID);
		} else {
			if (pdomap[entry].nrec != 0) return CAN_ERRET_OBD_OBJACCESS;
			if (*data > pdomap[entry].nmax) return CAN_ERRET_PDO_ERRMAP;
			len = 0;
			for (cnt = 0; cnt < *data; cnt++) {
				size = test_pdo_map(node, index, *(pdomap[entry].pointer + cnt));
				if (size < 0) return (int16)size;
				len += (unsigned16)size;
				if (len > CAN_NOF_PDOBIT_MAX) return CAN_ERRET_PDO_ERRMAP;
			}
			pdomap[entry].nrec = *data;
			return CAN_RETOK;
		}
	} else {
		if (pdomap[entry].nrec != 0) return CAN_ERRET_OBD_OBJACCESS;
		bpnt = (canbyte*)&buf;
		size = sizeof(unsigned32);
		FROM_CANOPEN_TO_OBJECT_DICTIONARY
		size = test_pdo_map(node, index, buf);
		if (size < 0) return (int16)size;
		*(pdomap[entry].pointer + subind-1) = buf;
		return CAN_RETOK;
	}
}

static void size_mask(unsigned32 *data, int16 bitlen)
{
	unsigned16 cnt, ind;
	unsigned32 lm[2];

	lm[1] = 0;
	if (bitlen <= 32) {
		lm[0] = 0;
		ind = 0;
	} else {
		lm[0] = 0xFFFFFFFF;
		ind = 1;
		bitlen -= 32;
	}
	for (cnt = 0; cnt < bitlen; cnt++) lm[ind] = (lm[ind] << 1) | 1;
	data[0] &= lm[0];
	data[1] &= lm[1];
}

int16 map_pdo(canindex index, canframe *cf)		// 3.0.1 some changes
{
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	cannode node;
	#endif
	int16 entry, fnr;
	int32 size;
	unsigned16 cnt, begfrb, nextfrb;
	canindex mapind;
	cansubind mapsub;
	canbyte *bpnt;
	unsigned32 bin[2];
	unsigned32 bout[2];

	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	fnr = get_pdo_node(index, &node);
	if (fnr != CAN_RETOK) return fnr;
	#endif
	fnr = check_pdo_comm_object(index);		// 2.2.1
	if (fnr != CAN_RETOK) return fnr;
	fnr = find_pdo_map_entry((canindex)(index+0x200), &entry);
	if (fnr != CAN_RETOK) return fnr;
	begfrb = 0;
	nextfrb = 0;
	bout[0]=0;
	bout[1]=0;
	bpnt = (canbyte*)bout;
	for (cnt = 0; cnt < pdomap[entry].nrec; cnt++) {
		mapind = ( *(pdomap[entry].pointer + cnt) & MASK_PDOMAP_INDEX) >> 16;
		mapsub = ( *(pdomap[entry].pointer + cnt) & MASK_PDOMAP_SUBIND) >> 8;
		bin[0]=0;
		bin[1]=0;
		#if CAN_APPLICATION_MODE == MASTER
		size = node_get_manstan_objsize(node, mapind, mapsub, BITS);
		#elif CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		size = server_get_object_size(mapind, mapsub, BITS);
		#endif
		if (size <= 0) return (int16)size;
		if ((unsigned32)size != (*(pdomap[entry].pointer + cnt) & MASK_PDOMAP_LENGTH)) return CAN_ERRET_PDO_ERRMAP;
		nextfrb += (unsigned16)size;
		if (nextfrb > CAN_NOF_PDOBIT_MAX) return CAN_ERRET_PDO_ERRMAP;
		#if CAN_APPLICATION_MODE == MASTER
		fnr = node_read_manstan_objdict_network(node, mapind, mapsub, (canbyte*)bin);
		#elif CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		fnr = server_read_obd_network(mapind, mapsub, (canbyte*)bin);
		#endif
		if (fnr != CAN_RETOK) return fnr;
		size_mask(bin, (int16)size);
		if (begfrb == 0) {
			bout[0] = bin[0];
			bout[1] = bin[1];
		} else if (begfrb >= 32) {
			bout[1] |= (bin[0] << (begfrb-32));
		} else if (nextfrb <= 32) {
			bout[0] |= (bin[0] << begfrb);
		} else {
			bout[0] |= (bin[0] << begfrb);
			bout[1] |= (bin[1] << begfrb) | (bin[0] >> (32-begfrb));
		}
		begfrb = nextfrb;
	}
	if (nextfrb == 0) cf->len = 0;
	else cf->len = (unsigned8)(1 + ((nextfrb-1) / CAN_SIZEOF_FACTOR));
	if (cf->len > CAN_DATALEN_MAXIMUM) return CAN_ERRET_PDO_ERRMAP;
	for (cnt = 0; cnt < cf->len; cnt++) {
		cf->data[cnt] = *bpnt; bpnt++;
	}
	return CAN_RETOK;
}

int16 activate_pdo(canindex index, canframe *cf)	// 3.0.1 some changes
{
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	cannode node;
	#endif
	int16 entry, fnr;
	int32 size;
	unsigned16 cnt, begfrb, nextfrb;
	canindex mapind;
	cansubind mapsub;
	canbyte *bpnt;
	unsigned32 bin[2];
	unsigned32 bout[2];

	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	fnr = get_pdo_node(index, &node);
	if (fnr != CAN_RETOK) return fnr;
	#endif
	fnr = check_pdo_comm_object(index);		// 2.2.1
	if (fnr != CAN_RETOK) return fnr;
	fnr = find_pdo_map_entry((canindex)(index+0x200), &entry);
	if (fnr != CAN_RETOK) return fnr;
	nextfrb = 0;
	for (cnt = 0; cnt < pdomap[entry].nrec; cnt++) {
		mapind = ( *(pdomap[entry].pointer + cnt) & MASK_PDOMAP_INDEX) >> 16;
		mapsub = ( *(pdomap[entry].pointer + cnt) & MASK_PDOMAP_SUBIND) >> 8;
		#if CAN_APPLICATION_MODE == MASTER
		size = node_get_manstan_objsize(node, mapind, mapsub, BITS);
		#elif CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		size = server_get_object_size(mapind, mapsub, BITS);
		#endif
		if (size <= 0) return (int16)size;
		if ((unsigned32)size != (*(pdomap[entry].pointer + cnt) & MASK_PDOMAP_LENGTH)) return CAN_ERRET_PDO_ERRMAP;
		nextfrb += (unsigned16)size;
		if (nextfrb > CAN_SIZEOF_FACTOR * cf->len) {
			#if CAN_OBJECT_EMCY == TRUE
			produce_emcy_default(CAN_EMCY_PDOLENERR);
			#endif
			return CAN_ERRET_PDO_ERRMAP;
		}
	}
	bin[0]=0;
	bin[1]=0;
	bpnt = (canbyte*)bin;
	for (cnt = 0; cnt < cf->len; cnt++) {
		*bpnt = cf->data[cnt]; bpnt++;
	}
	begfrb = 0;
	nextfrb = 0;
	for (cnt = 0; cnt < pdomap[entry].nrec; cnt++) {
		mapind = ( *(pdomap[entry].pointer + cnt) & MASK_PDOMAP_INDEX) >> 16;
		mapsub = ( *(pdomap[entry].pointer + cnt) & MASK_PDOMAP_SUBIND) >> 8;
		bout[0]=0;
		bout[1]=0;
		#if CAN_APPLICATION_MODE == MASTER
		size = node_get_manstan_objsize(node, mapind, mapsub, BITS);
		#elif CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
		size = server_get_object_size(mapind, mapsub, BITS);
		#endif
		if (size <= 0) return (int16)size;
		nextfrb += (unsigned16)size;
		if (begfrb == 0) {
			bout[0] = bin[0];
			bout[1] = bin[1];
		} else if (begfrb >= 32) {
			bout[0] = (bin[1] >> (begfrb-32));
		} else if (nextfrb <= 32) {
			bout[0] = (bin[0] >> begfrb);
		} else {
			bout[0] = (bin[0] >> begfrb) | (bin[1] << (32-begfrb));
			bout[1] = (bin[1] >> begfrb);
		}
		size_mask(bout, (int16)size);
		#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
		fnr = node_write_manstan_objdict_network(node, mapind, mapsub, (canbyte*)bout);
		#elif CAN_APPLICATION_MODE == SLAVE
		fnr = server_write_obd_network(mapind, mapsub, (canbyte*)bout);
		#endif
		if (fnr != CAN_RETOK) return fnr;
		#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
		pdo_activated_master(node, mapind, mapsub);
		#elif CAN_APPLICATION_MODE == SLAVE
		pdo_activated_slave(mapind, mapsub);
		#endif
		begfrb = nextfrb;
	}
	set_pdo_recv_event_timer(index);
	return CAN_RETOK;
}

void can_init_pdo_map(void)
{
	unsigned16 entry, cnt;

	for (entry = 0; entry < NOF_PDO_MAPPED; entry++) {
		pdomap[entry].nmax = 0;
		pdomap[entry].nrec = 0;
		pdomap[entry].pointer = NULL;
	}
	define_pdo_map();
	for (entry = 0; entry < NOF_PDO_MAPPED; entry++) {
		for (cnt = 0; cnt < pdomap[entry].nmax; cnt++) *(pdomap[entry].pointer + cnt) = 0;
	}
}
