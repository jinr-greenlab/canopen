static canindex idx[CAN_CANID_CONFIG_MAX+1];

int16 correct_recv_canid(canindex index, canlink canid)
{
	unsigned16 cnt;

	if (index == CAN_INDEX_DUMMY) return CAN_RETOK;
	canid &= CAN_MASK_CANID;
	if (canid > CAN_CANID_CONFIG_MAX) return CAN_ERRET_OUTOFMEM;
	if (node_state != CAN_NODE_STATE_INITIALISING) {
		for (cnt = 0; cnt <= CAN_CANID_CONFIG_MAX; cnt++) if (index == idx[cnt]) idx[cnt] = CAN_INDEX_DUMMY;
	}
	if (canid != CAN_CANID_DUMMY) idx[canid] = index;
	return CAN_RETOK;
}

canindex find_comm_recv_index(canlink canid)	// 3.0.1 API changed
{
	if (canid > CAN_CANID_CONFIG_MAX) return CAN_INDEX_DUMMY;
	// 3.0.2 TPDO RTR discarded
	if (idx[canid] >= CAN_INDEX_TRNPDO_COMM_MIN && idx[canid] <= CAN_INDEX_TRNPDO_COMM_MAX) return CAN_INDEX_DUMMY;
	return idx[canid];
}

void can_init_recv_canids(void)
{
	unsigned16 cnt;

	for (cnt = 0; cnt <= CAN_CANID_CONFIG_MAX; cnt++) idx[cnt] = CAN_INDEX_DUMMY;
}
