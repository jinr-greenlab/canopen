static struct recvcanid {
	canlink canid;
	canindex index;
} cob[CAN_NOF_RECV_CANIDS];

#if CAN_HARD_ACCEPTANCE_FILTER == AFSINGLE

static int16 set_accept_filter(void)
{
#if CAN_APPLICATION_MODE == SLAVE && CAN_NMT_MODE == SLAVE && CAN_ID_MODE == CANID11
	unsigned16 cnt;
	unsigned32 mask_or;
	cannode node;

	if (CiStop(can_netchan) < 0) return CAN_ERRET_CI_STOP;
#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE
	if (lss_state != LSS_OFF) {		// 2.3.3, 2.3.4 filter set corrected for the CAN_CANID_NMT
		if (CiSetFilter(can_netchan, 0, (~CAN_CANID_LSS_MASTER & CAN_MASK_CANID)) < 0) return CAN_ERRET_CI_FILTER;
		if (CiStart(can_netchan) < 0) return CAN_ERRET_CI_START;
		return CAN_RETOK;
	}
#endif
	node = node_id;
	if (node_id < CAN_NODE_ID_MIN || node_id > CAN_NODE_ID_MAX) node = 0;
	mask_or = CAN_CANID_NMT_ERROR_BASE + node;
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) mask_or |= cob[cnt].canid;
	if (CiSetFilter(can_netchan, 0, (~mask_or & CAN_MASK_CANID)) < 0) return CAN_ERRET_CI_FILTER;
	if (CiStart(can_netchan) < 0) return CAN_ERRET_CI_START;
#endif
	return CAN_RETOK;
}

#elif CAN_HARD_ACCEPTANCE_FILTER == AFDUAL

static int16 set_accept_filter(void)
{
#if CAN_APPLICATION_MODE == SLAVE && CAN_NMT_MODE == SLAVE && CAN_ID_MODE == CANID11
	unsigned16 cnt;
	unsigned32 mask_zn, mask_or, mask_and;
	cannode node;

	if (CiStop(can_netchan) < 0) return CAN_ERRET_CI_STOP;
#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE
	if (lss_state != LSS_OFF) {		// 2.3.3 filter set corrected for the CAN_CANID_NMT
		if (CiSetDualFilter(can_netchan, CAN_CANID_NMT, CAN_MASK_CANID, CAN_CANID_LSS_MASTER, CAN_MASK_CANID) < 0) return CAN_ERRET_CI_FILTER;
		if (CiStart(can_netchan) < 0) return CAN_ERRET_CI_START;
		return CAN_RETOK;
	}
#endif
	node = node_id;
	if (node_id < CAN_NODE_ID_MIN || node_id > CAN_NODE_ID_MAX) node = 0;
	mask_zn = 0;
	mask_or = CAN_CANID_NMT_ERROR_BASE + node;
	mask_and = mask_or;
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		if ((cob[cnt].canid & CAN_MASK_CANID_NODE) == 0) {
			mask_zn |= cob[cnt].canid;
		} else {
			mask_or |= cob[cnt].canid;
			mask_and &= cob[cnt].canid;
		}
	}
	if (CiSetDualFilter(can_netchan, \
					0, (~mask_zn & CAN_MASK_CANID), \
					mask_or, (~(mask_or ^ mask_and) & CAN_MASK_CANID)) < 0) {
		return CAN_ERRET_CI_FILTER;
	}
	if (CiStart(can_netchan) < 0) return CAN_ERRET_CI_START;
#endif
	return CAN_RETOK;
}

#endif

int16 correct_recv_canid(canindex index, canlink canid)
{
	unsigned16 cnt;

#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE
	if (lss_state != LSS_OFF) return set_accept_filter();
#endif
	if (index == CAN_INDEX_DUMMY) return CAN_RETOK;
	canid &= CAN_MASK_CANID;
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		if (index == cob[cnt].index) {
			cob[cnt].canid = canid;
			if (canid == CAN_CANID_DUMMY) cob[cnt].index = CAN_INDEX_DUMMY;
			return set_accept_filter();
		}
	}
	if (canid == CAN_CANID_DUMMY) return CAN_RETOK;
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		if (cob[cnt].index == CAN_INDEX_DUMMY) {
			cob[cnt].index = index;
			cob[cnt].canid = canid;
			return set_accept_filter();
		}
	}
	return CAN_ERRET_OUTOFMEM;
}

canindex find_comm_recv_index(canlink canid)	// 3.0.1 API changed
{
	unsigned16 cnt;
	canindex index;

	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		index = cob[cnt].index;
		if (index >= CAN_INDEX_TRNPDO_COMM_MIN && index <= CAN_INDEX_TRNPDO_COMM_MAX) continue;		// 3.0.2 TPDO RTR discarded
		if (canid == cob[cnt].canid) return index;
	}
	return CAN_INDEX_DUMMY;
}

void can_init_recv_canids(void)
{
	unsigned16 cnt;

	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		cob[cnt].canid = CAN_CANID_DUMMY;
		cob[cnt].index = CAN_INDEX_DUMMY;
	}
}
