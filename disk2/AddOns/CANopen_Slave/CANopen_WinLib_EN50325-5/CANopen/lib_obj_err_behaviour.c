#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 1)

static unsigned8 err_behaviour[CAN_NOF_ERRBEH_SUBIND];

int16 get_err_behaviour_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_ERR_BEHAVIOUR) {
		if (subind <= CAN_NOF_ERRBEH_SUBIND) return sizeof(unsigned8);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_err_behaviour_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_err_behaviour_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_MASK_ACCESS_RO;
	return CAN_MASK_ACCESS_RW;
}

int16 get_err_behaviour_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_err_behaviour_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_DEFTYPE_UNSIGNED8;
}

int16 read_err_behaviour_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size;

	size = get_err_behaviour_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) *data = CAN_NOF_ERRBEH_SUBIND;
	else *data = err_behaviour[subind-1];
	return CAN_RETOK;
}

int16 write_err_behaviour_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size;

	size = get_err_behaviour_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_ERRET_OBD_READONLY;
	if (*data > 2) return CAN_ERRET_OBD_VALRANGE;
	err_behaviour[subind-1] = *data;
	return CAN_RETOK;
}

static void oper_pre_oper(void)
{
	if (node_state == CAN_NODE_STATE_OPERATIONAL) enter_pre_operational();
}

void process_serious_error(cansubind subind)	// 3.0.1 moved to this module
{
	unsigned8 erb;

	if (subind == 0 || subind > CAN_NOF_ERRBEH_SUBIND) {
		oper_pre_oper();
	} else {
		erb = err_behaviour[subind-1];
		if (erb == 0) oper_pre_oper();
		else if (erb == 2) stop_node();
	}
	enter_error_state();
}

void can_init_err_behaviour(void)
{
	unsigned16 cnt;

	for (cnt = 0; cnt < CAN_NOF_ERRBEH_SUBIND; cnt++) err_behaviour[cnt] = 0;
}

#endif
