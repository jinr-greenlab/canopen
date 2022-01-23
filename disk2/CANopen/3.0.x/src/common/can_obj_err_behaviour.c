#include <can_header.h>

#if CHECK_VERSION(3, 0, 2)
//  CHECK_VERSION(2, 3, 0)
//  CHECK_VERSION(2, 2, 0)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 0)

#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE

#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

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
#if CAN_OBJECT_ERR_BEHAVIOUR == TRUE
	unsigned8 erb;

	#if CAN_APPLICATION_MODE == MASTER
	if (client_read_object_dictionary(CAN_INDEX_ERR_BEHAVIOUR, subind, &erb) == CAN_RETOK) {
		if (erb == 0) oper_pre_oper();
		else if (erb == 2) stop_node();
	} else oper_pre_oper();
	#else
	if (server_read_object_dictionary(CAN_INDEX_ERR_BEHAVIOUR, subind, &erb) == CAN_RETOK) {
		if (erb == 0) oper_pre_oper();
		else if (erb == 2) stop_node();
	} else oper_pre_oper();
	#endif
#else
	oper_pre_oper();
#endif
}

void can_init_err_behaviour(void)
{
	unsigned16 cnt;

	for (cnt = 0; cnt < CAN_NOF_ERRBEH_SUBIND; cnt++) err_behaviour[cnt] = 0;
}

#endif

#endif

#endif
