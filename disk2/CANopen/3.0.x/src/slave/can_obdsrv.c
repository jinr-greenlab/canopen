#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 2)
//  CHECK_VERSION(1, 7, 2)

#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

static int16 server_get_object_class(canindex index)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return CAN_CLASS_DEFTYPE;
	}
	if (index == CAN_INDEX_ERROR_REG || index == CAN_INDEX_PREDEF_ERROR) {
		return CAN_CLASS_ERROR;
	}
	if (index == CAN_INDEX_PROD_HBT ||
		index == CAN_INDEX_GUARD_TIME || index == CAN_INDEX_LIFETIME_FACTOR) {
		return CAN_CLASS_ECP;
	}
	if (index == CAN_INDEX_SYNC_COBID || index == CAN_INDEX_SYNC_PERIOD ||
		index == CAN_INDEX_SYNC_WINDOW || index == CAN_INDEX_SYNC_OVERFLOW) {
		return CAN_CLASS_SYNC;
	}
	if (index >= CAN_INDEX_SERVER_SDO_MIN && index <= CAN_INDEX_SERVER_SDO_MAX) {
		return CAN_CLASS_SERVER_SDO;
	}
	if ( (index >= CAN_INDEX_RCVPDO_COMM_MIN && index <= CAN_INDEX_RCVPDO_COMM_MAX) ||
	      (index >= CAN_INDEX_TRNPDO_COMM_MIN && index <= CAN_INDEX_TRNPDO_COMM_MAX) ) {
		return CAN_CLASS_PDO_COMM;
	}
	if ( (index >= CAN_INDEX_RCVPDO_MAP_MIN && index <= CAN_INDEX_RCVPDO_MAP_MAX) ||
	      (index >= CAN_INDEX_TRNPDO_MAP_MIN && index <= CAN_INDEX_TRNPDO_MAP_MAX) ) {
		return CAN_CLASS_PDO_MAP;
	}
	if (index == CAN_INDEX_DEVICE_TYPE || index == CAN_INDEX_IDENTITY ||
		index == CAN_INDEX_MAN_DEV_NAME || index == CAN_INDEX_MAN_HARD_VER ||
		index == CAN_INDEX_MAN_SOFT_VER || index == CAN_INDEX_MAN_STATUS) {
		return CAN_CLASS_DEVICE;
	}
#if CAN_OBJECT_RE_STORE == TRUE
	if (index == CAN_INDEX_STORE || index == CAN_INDEX_RE_STORE) {
		return CAN_CLASS_RE_STORE;
	}
#endif
#if CAN_OBJECT_TIME == TRUE
	if (index == CAN_INDEX_TIME_COBID) {
		return CAN_CLASS_TIME;
	}
#endif
#if CAN_OBJECT_EMCY == TRUE
	if (index == CAN_INDEX_EMCY_COBID || index == CAN_INDEX_EMCY_INHIBIT) {
		return CAN_CLASS_EMCY;
	}
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (index == CAN_INDEX_ERR_BEHAVIOUR) {
		return CAN_CLASS_ERR_BEHAVIOUR;
	}
#endif
#endif
	return CAN_ERRET_OBD_NOOBJECT;
}

int32 server_get_object_size(canindex index, cansubind subind, int16 unit)
{
	int32 size;
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_get_manstan_objsize(index, subind, unit);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_get_manstan_objsize(index, subind, unit);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return get_deftype_objsize(index, subind, unit);
	if (objclass == CAN_CLASS_ERROR) size = get_err_bytes_objsize(index, subind);
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	else if (objclass == CAN_CLASS_ECP) size = get_ecpslave_bytes_objsize(index, subind);
#elif CAN_NMT_MODE == MASTER
	else if (objclass == CAN_CLASS_ECP) size = get_ecpmaster_bytes_objsize(index, subind);
#endif
	else if (objclass == CAN_CLASS_SYNC) size = get_sync_bytes_objsize(index, subind);
	else if (objclass == CAN_CLASS_SERVER_SDO) size = get_sdo_server_bytes_objsize(index, subind);
	else if (objclass == CAN_CLASS_PDO_COMM) size = get_pdo_comm_bytes_objsize(index, subind);
	else if (objclass == CAN_CLASS_PDO_MAP) size = get_pdo_map_bytes_objsize(index, subind);
	else if (objclass == CAN_CLASS_DEVICE) size = get_dev_bytes_objsize(index, subind);
#if CAN_OBJECT_RE_STORE == TRUE
	else if (objclass == CAN_CLASS_RE_STORE) size = get_re_store_bytes_objsize(index, subind);
#endif
#if CAN_OBJECT_TIME == TRUE
	else if (objclass == CAN_CLASS_TIME) size = get_time_bytes_objsize(index, subind);
#endif
#if CAN_OBJECT_EMCY == TRUE
	else if (objclass == CAN_CLASS_EMCY) size = get_emcy_bytes_objsize(index, subind);
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	else if (objclass == CAN_CLASS_ERR_BEHAVIOUR) size = get_err_behaviour_bytes_objsize(index, subind);
#endif
#endif
	else size = CAN_ERRET_OBD_NOOBJECT;
	if (size < 0 || unit == BYTES) return size;
	return size * CAN_SIZEOF_FACTOR;
}

canbyte *server_get_object_pointer(canindex index, cansubind subind)
{
	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_get_manstan_objpointer(index, subind);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_get_manstan_objpointer(index, subind);
	}
	return NULL;
}

int16 server_see_access(canindex index, cansubind subind)
{
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_see_manstan_access(index, subind);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_see_manstan_access(index, subind);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return see_deftype_access(index, subind);
	if (objclass == CAN_CLASS_ERROR) return see_err_access(index, subind);
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ECP) return see_ecpslave_access(index, subind);
#elif CAN_NMT_MODE == MASTER
	if (objclass == CAN_CLASS_ECP) return see_ecpmaster_access(index, subind);
#endif
	if (objclass == CAN_CLASS_SYNC) return see_sync_access(index, subind);
	if (objclass == CAN_CLASS_SERVER_SDO) return see_sdo_server_access(index, subind);
	if (objclass == CAN_CLASS_PDO_COMM) return see_pdo_comm_access(index, subind);
	if (objclass == CAN_CLASS_PDO_MAP) return see_pdo_map_access(index, subind);
	if (objclass == CAN_CLASS_DEVICE) return see_dev_access(index, subind);
#if CAN_OBJECT_RE_STORE == TRUE
	if (objclass == CAN_CLASS_RE_STORE) return see_re_store_access(index, subind);
#endif
#if CAN_OBJECT_TIME == TRUE
	if (objclass == CAN_CLASS_TIME) return see_time_access(index, subind);
#endif
#if CAN_OBJECT_EMCY == TRUE
	if (objclass == CAN_CLASS_EMCY) return see_emcy_access(index, subind);
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return see_err_behaviour_access(index, subind);
#endif
#endif
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 server_get_object_type(canindex index, cansubind subind)
{
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_get_manstan_objtype(index, subind);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_get_manstan_objtype(index, subind);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return get_deftype_objtype(index, subind);
	if (objclass == CAN_CLASS_ERROR) return get_err_objtype(index, subind);
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ECP) return get_ecpslave_objtype(index, subind);
#elif CAN_NMT_MODE == MASTER
	if (objclass == CAN_CLASS_ECP) return get_ecpmaster_objtype(index, subind);
#endif
	if (objclass == CAN_CLASS_SYNC) return get_sync_objtype(index, subind);
	if (objclass == CAN_CLASS_SERVER_SDO) return get_sdo_server_objtype(index, subind);
	if (objclass == CAN_CLASS_PDO_COMM) return get_pdo_comm_objtype(index, subind);
	if (objclass == CAN_CLASS_PDO_MAP) return get_pdo_map_objtype(index, subind);
	if (objclass == CAN_CLASS_DEVICE) return get_dev_objtype(index, subind);
#if CAN_OBJECT_RE_STORE == TRUE
	if (objclass == CAN_CLASS_RE_STORE) return get_re_store_objtype(index, subind);
#endif
#if CAN_OBJECT_TIME == TRUE
	if (objclass == CAN_CLASS_TIME) return get_time_objtype(index, subind);
#endif
#if CAN_OBJECT_EMCY == TRUE
	if (objclass == CAN_CLASS_EMCY) return get_emcy_objtype(index, subind);
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return get_err_behaviour_objtype(index, subind);
#endif
#endif
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 server_read_object_dictionary(canindex index, cansubind subind, canbyte *data)
{
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_read_manstan_objdict(index, subind, data);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_read_manstan_objdict(index, subind, data);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return read_deftype_objdict(index, subind, data);
	if (objclass == CAN_CLASS_ERROR) return read_err_objdict(index, subind, data);
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ECP) return read_ecpslave_objdict(index, subind, data);
#elif CAN_NMT_MODE == MASTER
	if (objclass == CAN_CLASS_ECP) return read_ecpmaster_objdict(index, subind, data);
#endif
	if (objclass == CAN_CLASS_SYNC) return read_sync_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SERVER_SDO) return read_sdo_server_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_COMM) return read_pdo_comm_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_MAP) return read_pdo_map_objdict(index, subind, data);
	if (objclass == CAN_CLASS_DEVICE) return read_dev_objdict(index, subind, data);
#if CAN_OBJECT_RE_STORE == TRUE
	if (objclass == CAN_CLASS_RE_STORE) return read_re_store_objdict(index, subind, data);
#endif
#if CAN_OBJECT_TIME == TRUE
	if (objclass == CAN_CLASS_TIME) return read_time_objdict(index, subind, data);
#endif
#if CAN_OBJECT_EMCY == TRUE
	if (objclass == CAN_CLASS_EMCY) return read_emcy_objdict(index, subind, data);
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return read_err_behaviour_objdict(index, subind, data);
#endif
#endif
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 server_write_object_dictionary(canindex index, cansubind subind, canbyte *data)
{
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_write_manstan_objdict(index, subind, data);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_write_manstan_objdict(index, subind, data);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return write_deftype_objdict(index, subind, data);
	if (objclass == CAN_CLASS_ERROR) return write_err_objdict(index, subind, data);
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ECP) return write_ecpslave_objdict(index, subind, data);
#elif CAN_NMT_MODE == MASTER
	if (objclass == CAN_CLASS_ECP) return write_ecpmaster_objdict(index, subind, data);
#endif
	if (objclass == CAN_CLASS_SYNC) return write_sync_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SERVER_SDO) return write_sdo_server_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_COMM) return write_pdo_comm_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_MAP) return write_pdo_map_objdict(index, subind, data);
	if (objclass == CAN_CLASS_DEVICE) return write_dev_objdict(index, subind, data);
#if CAN_OBJECT_RE_STORE == TRUE
	if (objclass == CAN_CLASS_RE_STORE) return write_re_store_objdict(index, subind, data);
#endif
#if CAN_OBJECT_TIME == TRUE
	if (objclass == CAN_CLASS_TIME) return write_time_objdict(index, subind, data);
#endif
#if CAN_OBJECT_EMCY == TRUE
	if (objclass == CAN_CLASS_EMCY) return write_emcy_objdict(index, subind, data);
#endif
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE
#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return write_err_behaviour_objdict(index, subind, data);
#endif
#endif
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 server_read_obd_network(canindex index, cansubind subind, canbyte *data)
{
#if CAN_BYTE_ORDER == NORMAL
	return server_read_object_dictionary(index, subind, data);
#else
	int16 type, fnr;
	canbyte locd[8];

	type = server_get_object_type(index, subind);
	if (type < 0) return type;
	if (type == CAN_DEFTYPE_INTEGER16 || type == CAN_DEFTYPE_UNSIGNED16 ||
		type == CAN_DEFTYPE_INTEGER32 || type == CAN_DEFTYPE_UNSIGNED32 ||
		type == CAN_DEFTYPE_INTEGER64 || type == CAN_DEFTYPE_UNSIGNED64 ||
		type == CAN_DEFTYPE_REAL32 || type == CAN_DEFTYPE_REAL64) {
		fnr = server_read_object_dictionary(index, subind, locd);
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
	return server_read_object_dictionary(index, subind, data);
#endif
}

int16 server_write_obd_network(canindex index, cansubind subind, canbyte *data)
{
#if CAN_BYTE_ORDER == NORMAL
	return server_write_object_dictionary(index, subind, data);
#else
	int16 type;
	canbyte locd[8];

	type = server_get_object_type(index, subind);
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
		return server_write_object_dictionary(index, subind, locd);
	}
	return server_write_object_dictionary(index, subind, data);
#endif
}

int16 server_read_obd_u32(canindex index, cansubind subind, unsigned32 *du32)
{
#if CAN_BYTE_ORDER == NORMAL
	return server_read_object_dictionary(index, subind, (canbyte*)du32);
#else
	int32 size;

	size = server_get_object_size(index, subind, BYTES);
	if (size <= 0) return size;
	return server_read_object_dictionary(index, subind, (sizeof(unsigned32) - size + (canbyte*)du32));
#endif
}
// 2.3.1 updated to handle reverse byte order

int16 server_write_obd_u32(canindex index, cansubind subind, unsigned32 du32)
{
#if CAN_BYTE_ORDER == NORMAL
	return server_write_object_dictionary(index, subind, (canbyte*)&du32);
#else
	int32 size;

	size = server_get_object_size(index, subind, BYTES);
	if (size <= 0) return size;
	return server_write_object_dictionary(index, subind, (sizeof(unsigned32) - size + (canbyte*)&du32));
#endif
}
// 2.3.1 updated to handle reverse byte order

#endif

#endif
