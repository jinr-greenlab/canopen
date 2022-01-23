#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 0)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 0)

#if CAN_APPLICATION_MODE == MASTER && CAN_SLAVE_DEVICE_CLASS != CAN_DEVICE_TEST

int32 node_get_manstan_objsize(cannode node, canindex index, cansubind subind, int16 unit)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return get_deftype_objsize(index, subind, unit);
	}
	return CAN_ERRET_OBD_INVNODE;
}

canbyte *node_get_manstan_objpointer(cannode node, canindex index, cansubind subind)
{
	return NULL;
}

int16 node_see_manstan_access(cannode node, canindex index, cansubind subind)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return see_deftype_access(index, subind);
	}
	return CAN_ERRET_OBD_INVNODE;
}

int16 node_get_manstan_objtype(cannode node, canindex index, cansubind subind)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return get_deftype_objtype(index, subind);
	}
	return CAN_ERRET_OBD_INVNODE;
}

int16 node_read_manstan_objdict(cannode node, canindex index, cansubind subind, canbyte *data)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return read_deftype_objdict(index, subind, data);
	}
	return CAN_ERRET_OBD_INVNODE;
}

int16 node_write_manstan_objdict(cannode node, canindex index, cansubind subind, canbyte *data)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return write_deftype_objdict(index, subind, data);
	}
	return CAN_ERRET_OBD_INVNODE;
}

void master_init_manstan_application(void)
{
}

void master_init_manstan_communication(void)
{
}

#endif

#endif
