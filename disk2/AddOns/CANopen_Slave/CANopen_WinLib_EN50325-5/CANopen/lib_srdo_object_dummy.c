#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 1)

int16 get_srdo_comm_bytes_objsize(canindex index, cansubind subind)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_srdo_comm_access(canindex index, cansubind subind)
{
	return 0;
}

int16 get_srdo_comm_objtype(canindex index, cansubind subind)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 read_srdo_comm_objdict(canindex index, cansubind subind, canbyte *data)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 write_srdo_comm_objdict(canindex index, cansubind subind, canbyte *data)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 get_srdo_map_bytes_objsize(canindex index, cansubind subind)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_srdo_map_access(canindex index, cansubind subind)
{
	return 0;
}

int16 get_srdo_map_objtype(canindex index, cansubind subind)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 read_srdo_map_objdict(canindex index, cansubind subind, canbyte *data)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 write_srdo_map_objdict(canindex index, cansubind subind, canbyte *data)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 get_sr_config_bytes_objsize(canindex index, cansubind subind)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_sr_config_access(canindex index, cansubind subind)
{
	return 0;
}

int16 get_sr_config_objtype(canindex index, cansubind subind)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 read_sr_config_objdict(canindex index, cansubind subind, canbyte *data)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 write_sr_config_objdict(canindex index, cansubind subind, canbyte *data)
{
	return CAN_ERRET_OBD_NOOBJECT;
}

void produce_sr_gfc(void)
{
}

void consume_sr_gfc(void)
{
}

void control_srdo(void)		// Called from the CANopen timer
{
}

void receive_can_srdo(canindex index, canframe *cf)
{
}

void run_sr_operations(void)	// Called from the start_node()
{
}

unsigned8 get_sr_runstatus(void)
{
	return OFF;
}

void can_init_srdo(void)
{
}

#endif
