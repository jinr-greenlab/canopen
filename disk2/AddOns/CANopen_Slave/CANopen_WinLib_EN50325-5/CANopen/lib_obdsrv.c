#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 2)

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
	if (index >= CAN_INDEX_SRDO_COMM_MIN && index <= CAN_INDEX_SRDO_COMM_MAX) {
		return CAN_CLASS_SR_COMM;		// 3.0.1
	}
	if (index >= CAN_INDEX_SRDO_MAP_MIN && index <= CAN_INDEX_SRDO_MAP_MAX) {
		return CAN_CLASS_SR_MAP;		// 3.0.1
	}
	if (index == CAN_INDEX_SR_GFC) return CAN_CLASS_SR_CONFIG;		// 3.0.1
	if (index >= CAN_INDEX_SR_PARAM_MIN && index <= CAN_INDEX_SR_PARAM_MAX) {
		return CAN_CLASS_SR_CONFIG;		// 3.0.1
	}
	if ( (index >= CAN_INDEX_RCVPDO_COMM_MIN && index <= CAN_INDEX_RCVPDO_COMM_MAX) ||
	      (index >= CAN_INDEX_TRNPDO_COMM_MIN && index <= CAN_INDEX_TRNPDO_COMM_MAX) ) {
		return CAN_CLASS_PDO_COMM;
	}
	if ( (index >= CAN_INDEX_RCVPDO_MAP_MIN && index <= CAN_INDEX_RCVPDO_MAP_MAX) ||
	      (index >= CAN_INDEX_TRNPDO_MAP_MIN && index <= CAN_INDEX_TRNPDO_MAP_MAX) ) {
		return CAN_CLASS_PDO_MAP;
	}
	if (index >= CAN_INDEX_NETWORKS_MIN && index <= CAN_INDEX_NETWORKS_MAX) {
		return CAN_CLASS_NETWORKS;		// 3.0.1
	}
	if (index == CAN_INDEX_DEVICE_TYPE || index == CAN_INDEX_IDENTITY ||
		index == CAN_INDEX_MAN_DEV_NAME || index == CAN_INDEX_MAN_HARD_VER ||
		index == CAN_INDEX_MAN_SOFT_VER || index == CAN_INDEX_MAN_STATUS) {
		return CAN_CLASS_DEVICE;
	}
	if (index == CAN_INDEX_STORE || index == CAN_INDEX_RE_STORE) {
		return CAN_CLASS_RE_STORE;
	}
	if (index == CAN_INDEX_TIME_COBID) {
		return CAN_CLASS_TIME;
	}
	if (index == CAN_INDEX_EMCY_COBID || index == CAN_INDEX_EMCY_INHIBIT) {
		return CAN_CLASS_EMCY;
	}
	if (index == CAN_INDEX_ERR_BEHAVIOUR) {
		return CAN_CLASS_ERR_BEHAVIOUR;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int32 server_get_object_size(canindex index, cansubind subind)
{
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_get_standev_objsize(index, subind);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_get_manspec_objsize(index, subind);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return get_deftype_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_ERROR) return get_err_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_ECP) return get_ecpslave_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_SYNC) return get_sync_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_SERVER_SDO) return get_sdo_server_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_PDO_COMM) return get_pdo_comm_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_PDO_MAP) return get_pdo_map_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_DEVICE) return get_dev_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_RE_STORE) return get_re_store_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_TIME) return get_time_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_EMCY) return get_emcy_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return get_err_behaviour_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_SR_COMM) return get_srdo_comm_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_SR_MAP) return get_srdo_map_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_SR_CONFIG) return get_sr_config_bytes_objsize(index, subind);
	if (objclass == CAN_CLASS_NETWORKS) return get_can_networks_bytes_objsize(index, subind);
	return CAN_ERRET_OBD_NOOBJECT;
}

int32 server_put_object_size(canindex index, cansubind subind, int32 size)
{
	// Ðut object size for the variable data size objects
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_put_manspec_objsize(index, subind, size);
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 server_see_access(canindex index, cansubind subind)
{
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_see_standev_access(index, subind);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_see_manspec_access(index, subind);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return see_deftype_access(index, subind);
	if (objclass == CAN_CLASS_ERROR) return see_err_access(index, subind);
	if (objclass == CAN_CLASS_ECP) return see_ecpslave_access(index, subind);
	if (objclass == CAN_CLASS_SYNC) return see_sync_access(index, subind);
	if (objclass == CAN_CLASS_SERVER_SDO) return see_sdo_server_access(index, subind);
	if (objclass == CAN_CLASS_PDO_COMM) return see_pdo_comm_access(index, subind);
	if (objclass == CAN_CLASS_PDO_MAP) return see_pdo_map_access(index, subind);
	if (objclass == CAN_CLASS_DEVICE) return see_dev_access(index, subind);
	if (objclass == CAN_CLASS_RE_STORE) return see_re_store_access(index, subind);
	if (objclass == CAN_CLASS_TIME) return see_time_access(index, subind);
	if (objclass == CAN_CLASS_EMCY) return see_emcy_access(index, subind);
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return see_err_behaviour_access(index, subind);
	if (objclass == CAN_CLASS_SR_COMM) return see_srdo_comm_access(index, subind);
	if (objclass == CAN_CLASS_SR_MAP) return see_srdo_map_access(index, subind);
	if (objclass == CAN_CLASS_SR_CONFIG) return see_sr_config_access(index, subind);
	if (objclass == CAN_CLASS_NETWORKS) return see_can_networks_access(index, subind);
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 server_get_object_type(canindex index, cansubind subind)
{
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_get_standev_objtype(index, subind);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_get_manspec_objtype(index, subind);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return get_deftype_objtype(index, subind);
	if (objclass == CAN_CLASS_ERROR) return get_err_objtype(index, subind);
	if (objclass == CAN_CLASS_ECP) return get_ecpslave_objtype(index, subind);
	if (objclass == CAN_CLASS_SYNC) return get_sync_objtype(index, subind);
	if (objclass == CAN_CLASS_SERVER_SDO) return get_sdo_server_objtype(index, subind);
	if (objclass == CAN_CLASS_PDO_COMM) return get_pdo_comm_objtype(index, subind);
	if (objclass == CAN_CLASS_PDO_MAP) return get_pdo_map_objtype(index, subind);
	if (objclass == CAN_CLASS_DEVICE) return get_dev_objtype(index, subind);
	if (objclass == CAN_CLASS_RE_STORE) return get_re_store_objtype(index, subind);
	if (objclass == CAN_CLASS_TIME) return get_time_objtype(index, subind);
	if (objclass == CAN_CLASS_EMCY) return get_emcy_objtype(index, subind);
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return get_err_behaviour_objtype(index, subind);
	if (objclass == CAN_CLASS_SR_COMM) return get_srdo_comm_objtype(index, subind);
	if (objclass == CAN_CLASS_SR_MAP) return get_srdo_map_objtype(index, subind);
	if (objclass == CAN_CLASS_SR_CONFIG) return get_sr_config_objtype(index, subind);
	if (objclass == CAN_CLASS_NETWORKS) return get_can_networks_objtype(index, subind);
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 server_read_object_dictionary(canindex index, cansubind subind, canbyte *data)
{
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_read_standev_objdict(index, subind, data);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_read_manspec_objdict(index, subind, data);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return read_deftype_objdict(index, subind, data);
	if (objclass == CAN_CLASS_ERROR) return read_err_objdict(index, subind, data);
	if (objclass == CAN_CLASS_ECP) return read_ecpslave_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SYNC) return read_sync_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SERVER_SDO) return read_sdo_server_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_COMM) return read_pdo_comm_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_MAP) return read_pdo_map_objdict(index, subind, data);
	if (objclass == CAN_CLASS_DEVICE) return read_dev_objdict(index, subind, data);
	if (objclass == CAN_CLASS_RE_STORE) return read_re_store_objdict(index, subind, data);
	if (objclass == CAN_CLASS_TIME) return read_time_objdict(index, subind, data);
	if (objclass == CAN_CLASS_EMCY) return read_emcy_objdict(index, subind, data);
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return read_err_behaviour_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SR_COMM) return read_srdo_comm_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SR_MAP) return read_srdo_map_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SR_CONFIG) return read_sr_config_objdict(index, subind, data);
	if (objclass == CAN_CLASS_NETWORKS) return read_can_networks_objdict(index, subind, data);
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 server_write_object_dictionary(canindex index, cansubind subind, canbyte *data)
{
	int16 objclass;

	if (index >= CAN_INDEX_STANDEV_BEGIN && index <= CAN_INDEX_STANDEV_END) {
		return server_write_standev_objdict(index, subind, data);
	}
	if (index >= CAN_INDEX_MANSPEC_BEGIN && index <= CAN_INDEX_MANSPEC_END) {
		return server_write_manspec_objdict(index, subind, data);
	}
	objclass = server_get_object_class(index);
	if (objclass == CAN_CLASS_DEFTYPE) return write_deftype_objdict(index, subind, data);
	if (objclass == CAN_CLASS_ERROR) return write_err_objdict(index, subind, data);
	if (objclass == CAN_CLASS_ECP) return write_ecpslave_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SYNC) return write_sync_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SERVER_SDO) return write_sdo_server_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_COMM) return write_pdo_comm_objdict(index, subind, data);
	if (objclass == CAN_CLASS_PDO_MAP) return write_pdo_map_objdict(index, subind, data);
	if (objclass == CAN_CLASS_DEVICE) return write_dev_objdict(index, subind, data);
	if (objclass == CAN_CLASS_RE_STORE) return write_re_store_objdict(index, subind, data);
	if (objclass == CAN_CLASS_TIME) return write_time_objdict(index, subind, data);
	if (objclass == CAN_CLASS_EMCY) return write_emcy_objdict(index, subind, data);
	if (objclass == CAN_CLASS_ERR_BEHAVIOUR) return write_err_behaviour_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SR_COMM) return write_srdo_comm_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SR_MAP) return write_srdo_map_objdict(index, subind, data);
	if (objclass == CAN_CLASS_SR_CONFIG) return write_sr_config_objdict(index, subind, data);
	if (objclass == CAN_CLASS_NETWORKS) return write_can_networks_objdict(index, subind, data);
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 server_read_obd_u32(canindex index, cansubind subind, unsigned32 *du32)
{
	return server_read_object_dictionary(index, subind, (canbyte*)du32);
}

int16 server_write_obd_u32(canindex index, cansubind subind, unsigned32 du32)
{
	return server_write_object_dictionary(index, subind, (canbyte*)&du32);
}

#endif
