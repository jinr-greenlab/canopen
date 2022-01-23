#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 2)

#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST

int16 node_read_manstan_objdict_network(cannode node, canindex index, cansubind subind, canbyte *data)
{
#if CAN_BYTE_ORDER == NORMAL
	return node_read_manstan_objdict(node, index, subind, data);
#else
	int16 type, fnr;
	canbyte locd[8];

	type = node_get_manstan_objtype(node, index, subind);
	if (type < 0) return type;
	if (type == CAN_DEFTYPE_INTEGER16 || type == CAN_DEFTYPE_UNSIGNED16 ||
		type == CAN_DEFTYPE_INTEGER32 || type == CAN_DEFTYPE_UNSIGNED32 ||
		type == CAN_DEFTYPE_INTEGER64 || type == CAN_DEFTYPE_UNSIGNED64 ||
		type == CAN_DEFTYPE_REAL32 || type == CAN_DEFTYPE_REAL64) {
		fnr = node_read_manstan_objdict(node, index, subind, locd);
		if (fnr != CAN_RETOK) return fnr;
		if (type == CAN_DEFTYPE_REAL64 ||
		     type == CAN_DEFTYPE_INTEGER64 || type == CAN_DEFTYPE_UNSIGNED64) {
			*data = locd[7]; data++;
			*data = locd[6]; data++;
			*data = locd[5]; data++;
			*data = locd[4]; data++;
			*data = locd[3]; data++;
			*data = locd[2]; data++;
		} else if (type == CAN_DEFTYPE_INTEGER32 || type == CAN_DEFTYPE_UNSIGNED32 ||
	     		type == CAN_DEFTYPE_REAL32) {
			*data = locd[3]; data++;
			*data = locd[2]; data++;
		}
		*data = locd[1]; data++;
		*data = locd[0];
		return CAN_RETOK;
	}
	return node_read_manstan_objdict(node, index, subind, data);
#endif
}

int16 node_write_manstan_objdict_network(cannode node, canindex index, cansubind subind, canbyte *data)
{
#if CAN_BYTE_ORDER == NORMAL
	return node_write_manstan_objdict(node, index, subind, data);
#else
	int16 type;
	canbyte locd[8];

	type = node_get_manstan_objtype(node, index, subind);
	if (type < 0) return type;
	if (type == CAN_DEFTYPE_INTEGER16 || type == CAN_DEFTYPE_UNSIGNED16 ||
		type == CAN_DEFTYPE_INTEGER32 || type == CAN_DEFTYPE_UNSIGNED32 ||
		type == CAN_DEFTYPE_INTEGER64 || type == CAN_DEFTYPE_UNSIGNED64 ||
		type == CAN_DEFTYPE_REAL32 || type == CAN_DEFTYPE_REAL64) {
		if (type == CAN_DEFTYPE_REAL64 ||
		     type == CAN_DEFTYPE_INTEGER64 || type == CAN_DEFTYPE_UNSIGNED64) {
			locd[7] = *data; data++;
			locd[6] = *data; data++;
			locd[5] = *data; data++;
			locd[4] = *data; data++;
			locd[3] = *data; data++;
			locd[2] = *data; data++;
		} else if (type == CAN_DEFTYPE_INTEGER32 || type == CAN_DEFTYPE_UNSIGNED32 ||
	     		type == CAN_DEFTYPE_REAL32) {
			locd[3] = *data; data++;
			locd[2] = *data; data++;
		}
		locd[1] = *data; data++;
		locd[0] = *data;
		return node_write_manstan_objdict(node, index, subind, locd);
	}
	return node_write_manstan_objdict(node, index, subind, data);
#endif
}

static int16 client_get_object_class(canindex index)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return CAN_CLASS_DEFTYPE;
	}
	if (index == CAN_INDEX_CONS_HBT ||
	     index == CAN_INDEX_GUARD_TIME || index == CAN_INDEX_LIFETIME_FACTOR) {
		return CAN_CLASS_ECP;
	}
	if (index == CAN_INDEX_SYNC_COBID || index == CAN_INDEX_SYNC_PERIOD ||
		index == CAN_INDEX_SYNC_WINDOW || index == CAN_INDEX_SYNC_OVERFLOW) {
		return CAN_CLASS_SYNC;
	}
	if (index >= CAN_INDEX_CLIENT_SDO_MIN && index <= CAN_INDEX_CLIENT_SDO_MAX) {
		return CAN_CLASS_CLIENT_SDO;
	}
	if ( (index >= CAN_INDEX_RCVPDO_COMM_MIN && index <= CAN_INDEX_RCVPDO_COMM_MAX) ||
	      (index >= CAN_INDEX_TRNPDO_COMM_MIN && index <= CAN_INDEX_TRNPDO_COMM_MAX) ) {
		return CAN_CLASS_PDO_COMM;
	}
	if ( (index >= CAN_INDEX_RCVPDO_MAP_MIN && index <= CAN_INDEX_RCVPDO_MAP_MAX) ||
	      (index >= CAN_INDEX_TRNPDO_MAP_MIN && index <= CAN_INDEX_TRNPDO_MAP_MAX) ) {
		return CAN_CLASS_PDO_MAP;
	}
#if CAN_OBJECT_TIME == TRUE
	if (index == CAN_INDEX_TIME_COBID) {
		return CAN_CLASS_TIME;
	}
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE && CAN_NMT_MODE == SLAVE
	if (index == CAN_INDEX_ERR_BEHAVIOUR) {
		return CAN_CLASS_ERR_BEHAVIOUR;
	}
#endif
	return CAN_ERRET_OBD_NOOBJECT;
}

int32 client_get_object_size(canindex index, cansubind subind, int16 unit)
{
	int32 size;
	int16 objclass;

	objclass = client_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return get_deftype_objsize(index, subind, unit);
#if CAN_NMT_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ECP) size = get_ecpmaster_bytes_objsize(index, subind);
#elif CAN_NMT_MODE == SLAVE
	if (objclass == CAN_CLASS_ECP) size = get_ecpslave_bytes_objsize(index, subind);
#endif
	else if (objclass == CAN_CLASS_SYNC) size = get_sync_bytes_objsize(index, subind);
	else if (objclass == CAN_CLASS_CLIENT_SDO) size = get_sdo_client_bytes_objsize(index, subind);
	else if (objclass == CAN_CLASS_PDO_COMM) size = get_pdo_comm_bytes_objsize(index, subind);
	else if (objclass == CAN_CLASS_PDO_MAP) size = get_pdo_map_bytes_objsize(index, subind);
#if CAN_OBJECT_TIME == TRUE
	else if (objclass == CAN_CLASS_TIME) size = get_time_bytes_objsize(index, subind);
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE && CAN_NMT_MODE == SLAVE
	else if (objclass == CAN_CLASS_ERR_BEHAVIOUR) size = get_err_behaviour_bytes_objsize(index, subind);
#endif
	else size = CAN_ERRET_OBD_NOOBJECT;
	if (size < 0 || unit == BYTES) return size;
	return size * CAN_SIZEOF_FACTOR;
}

int16 client_see_access(canindex index, cansubind subind)
{
	int16 objclass;

	objclass = client_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return see_deftype_access(index, subind);
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 client_read_object_dictionary(canindex index, cansubind subind, canbyte *data)
{
	int16 objclass;

	objclass = client_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return read_deftype_objdict(index, subind, data);
#if CAN_NMT_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ECP) return read_ecpmaster_objdict(index, subind, data);
#elif CAN_NMT_MODE == SLAVE
	if (objclass == CAN_CLASS_ECP) return read_ecpslave_objdict(index, subind, data);
#endif
	if (objclass == CAN_CLASS_SYNC) return read_sync_objdict(index, subind, data);
	if (objclass == CAN_CLASS_CLIENT_SDO) return read_sdo_client_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_COMM) return read_pdo_comm_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_MAP) return read_pdo_map_objdict(index, subind, data);
#if CAN_OBJECT_TIME == TRUE
	if (objclass == CAN_CLASS_TIME) return read_time_objdict(index, subind, data);
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE && CAN_NMT_MODE == SLAVE
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return read_err_behaviour_objdict(index, subind, data);
#endif
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 client_write_object_dictionary(canindex index, cansubind subind, canbyte *data)
{
	int16 objclass;

	objclass = client_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return write_deftype_objdict(index, subind, data);
#if CAN_NMT_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ECP) return write_ecpmaster_objdict(index, subind, data);
#elif CAN_NMT_MODE == SLAVE
	if (objclass == CAN_CLASS_ECP) return write_ecpslave_objdict(index, subind, data);
#endif
	if (objclass == CAN_CLASS_SYNC) return write_sync_objdict(index, subind, data);
	if (objclass == CAN_CLASS_CLIENT_SDO) return write_sdo_client_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_COMM) return write_pdo_comm_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_MAP) return write_pdo_map_objdict(index, subind, data);
#if CAN_OBJECT_TIME == TRUE
	if (objclass == CAN_CLASS_TIME) return write_time_objdict(index, subind, data);
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE && CAN_NMT_MODE == SLAVE
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return write_err_behaviour_objdict(index, subind, data);
#endif
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 client_read_obd_u32(cannode node, canindex index, cansubind subind, unsigned32 *du32)
{
#if CAN_BYTE_ORDER == NORMAL
	if (node == 0) return client_read_object_dictionary(index, subind, (canbyte*)du32);
	return node_read_manstan_objdict(node, index, subind, (canbyte*)du32);
#else
	int32 size;

	if (node == 0) {
		size = client_get_object_size(index, subind, BYTES);
		if (size <= 0) return size;
		return client_read_object_dictionary(index, subind, (sizeof(unsigned32) - size + (canbyte*)du32));
	} else {
		size = node_get_manstan_objsize(node, index, subind, BYTES);
		if (size <= 0) return size;
		return node_read_manstan_objdict(node, index, subind, (sizeof(unsigned32) - size + (canbyte*)du32));
	}
#endif
}
// 2.3.1 updated to handle reverse byte order

int16 client_write_obd_u32(cannode node, canindex index, cansubind subind, unsigned32 du32)
{
#if CAN_BYTE_ORDER == NORMAL
	if (node == 0) return client_write_object_dictionary(index, subind, (canbyte*)&du32);
	return node_write_manstan_objdict(node, index, subind, (canbyte*)&du32);
#else
	int32 size;

	if (node == 0) {
		size = client_get_object_size(index, subind, BYTES);
		if (size <= 0) return size;
		return client_write_object_dictionary(index, subind, (sizeof(unsigned32) - size + (canbyte*)&du32));
	} else {
		size = node_get_manstan_objsize(node, index, subind, BYTES);
		if (size <= 0) return size;
		return node_write_manstan_objdict(node, index, subind, (sizeof(unsigned32) - size + (canbyte*)&du32));
	}
#endif
}
// 2.3.1 updated to handle reverse byte order

#endif

#endif
