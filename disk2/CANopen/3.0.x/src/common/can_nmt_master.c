#include <can_header.h>

#if CHECK_VERSION(3, 0, 1)
//  CHECK_VERSION(2, 3, 2)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 0)

#if CAN_NMT_MODE == MASTER || CAN_APPLICATION_MODE == TEST

#define MASK_NODEID		0x00FF0000	// Heartbeat node ID mask
#define MASK_HBT		0x0000FFFF	// Heartbeat time mask

static struct nmtmaster {
	cannode node;
	unsigned16 hbt;
	unsigned32 beattot;
	unsigned32 beatcnt;
	unsigned16 guardtime;
	unsigned8  litif;
	unsigned8  toggle;
	unsigned32 guardtot;
	unsigned32 guardcnt;
	unsigned32 lifetot;
	unsigned32 lifecnt;
	unsigned8  error_flag;
} nmt[CAN_NOF_NODES];

static void request_nodeguard(cannode node)
{
	canframe cf;

	CLEAR_FRAME(&cf);
	cf.id = node + CAN_CANID_NMT_ERROR_BASE;
	cf.len = CAN_DATALEN_ECP;
	cf.flags = CAN_FLAG_RTR;
	send_can_data(&cf);
}

static void start_ecp_master(unsigned16 elm)	// 2.2.1 some changes
{
	nmt[elm].lifetot = 0;
	nmt[elm].guardtot = 0;
	nmt[elm].beattot = 0;
	nmt[elm].lifecnt = 0xFFFFFFFF;
	nmt[elm].guardcnt = 0xFFFFFFFF;
	nmt[elm].beatcnt = 0xFFFFFFFF;
	nmt[elm].error_flag = RESOLVED;
	if (nmt[elm].hbt > 0) {
		nmt[elm].beattot = 1 + (unsigned32)nmt[elm].hbt * 1000 / CAN_TIMERUSEC;
	}
	if (nmt[elm].guardtime > 0) {
		nmt[elm].guardtot = (unsigned32)nmt[elm].guardtime * 1000 / CAN_TIMERUSEC;
		if (nmt[elm].guardtot == 0) nmt[elm].guardtot = 1;
		nmt[elm].lifetot = nmt[elm].guardtot * nmt[elm].litif;
		nmt[elm].guardcnt = 1;
		nmt[elm].lifecnt = nmt[elm].lifetot;
	}
}

void nmt_master_command(unsigned8 cs, cannode node)
{
	canframe cf;

	CLEAR_FRAME (&cf);
	cf.id = CAN_CANID_NMT;
	cf.data[0] = cs;
	cf.data[1] = node;
	cf.len = CAN_DATALEN_NMT_MC;
	send_can_data(&cf);
}

int16 get_ecpmaster_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_CONS_HBT) {
		if (subind == 0) return sizeof(unsigned8);
		if (subind <= CAN_NOF_NODES) return sizeof(unsigned32);
		return CAN_ERRET_OBD_NOSUBIND;
	} else if (index == CAN_INDEX_GUARD_TIME) {
		if (subind == 0) return sizeof(unsigned8);
		if (subind <= CAN_NOF_NODES) return sizeof(unsigned16);
		return CAN_ERRET_OBD_NOSUBIND;
	} else if (index == CAN_INDEX_LIFETIME_FACTOR) {
		if (subind == 0) return sizeof(unsigned8);
		if (subind <= CAN_NOF_NODES) return sizeof(unsigned8);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_ecpmaster_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_ecpmaster_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_MASK_ACCESS_RW;
}

int16 get_ecpmaster_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_ecpmaster_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_LIFETIME_FACTOR) return CAN_DEFTYPE_UNSIGNED8;
	if (index == CAN_INDEX_GUARD_TIME) return CAN_DEFTYPE_UNSIGNED16;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_ecpmaster_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	unsigned32 buf;
	canbyte *bpnt;

	size = get_ecpmaster_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) {
		*data = CAN_NOF_NODES;		// 2.3.1
	} else {
		subind -= 1;
		if (index == CAN_INDEX_CONS_HBT) {
			buf = ((unsigned32)nmt[subind].node << 16) | nmt[subind].hbt;
			bpnt = (canbyte*)&buf;
		} else if (index == CAN_INDEX_GUARD_TIME) {
			bpnt = (canbyte*)&nmt[subind].guardtime;
		} else {
			bpnt = (canbyte*)&nmt[subind].litif;
		}
		OBJECT_DICTIONARY_TO_CANOPEN
	}
	return CAN_RETOK;
}

int16 write_ecpmaster_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	unsigned16 hbt;
	unsigned32 buf;
	cannode node;
	canbyte *bpnt;

	size = get_ecpmaster_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_ERRET_OBD_READONLY;
	subind -= 1;
	if (index == CAN_INDEX_CONS_HBT) {
		bpnt = (canbyte*)&buf; buf = 0;
	} else if (index == CAN_INDEX_GUARD_TIME) {
		bpnt = (canbyte*)&nmt[subind].guardtime;
	} else {
		bpnt = (canbyte*)&nmt[subind].litif;
	}
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (index == CAN_INDEX_CONS_HBT) {
		hbt = buf & MASK_HBT;
		node = (cannode)((buf & MASK_NODEID) >> 16);
		for (cnt = 0; cnt < CAN_NOF_NODES; cnt++) {
			if (cnt == subind) continue;
			if (nmt[cnt].node == node) {
				if (nmt[cnt].hbt != 0) return CAN_ERRET_OBD_PARINCOMP;
				nmt[cnt].guardtime = 0;
				nmt[cnt].litif = 0;
				start_ecp_master(cnt);
			}
		}
		nmt[subind].node = node;
		nmt[subind].hbt = hbt;
	}
	start_ecp_master(subind);
	return CAN_RETOK;
}

void consume_nmt(canframe *cf)
{
	unsigned16 cnt;
	cannode node;

	node = (cannode)(cf->id - CAN_CANID_NMT_ERROR_BASE);
	if (cf->data[0] == CAN_NODE_STATE_INITIALISING) bootup_event(node);
	else node_state_event(node, cf->data[0] & 0x7F);
	for (cnt = 0; cnt < CAN_NOF_NODES; cnt++) {
		if (nmt[cnt].node != node) continue;
		if (nmt[cnt].beattot != 0) {
			nmt[cnt].beatcnt = nmt[cnt].beattot;
			if (nmt[cnt].error_flag == OCCURRED) {
				nmt[cnt].error_flag = RESOLVED;
				heartbeat_resolved(nmt[cnt].node);
			}
			break;
		} else if (nmt[cnt].lifetot != 0) {
			if ((cf->data[0] & 0x80) == nmt[cnt].toggle) {
				nmt[cnt].toggle ^= 0x80;
				nmt[cnt].lifecnt = nmt[cnt].lifetot;
				if (nmt[cnt].error_flag == OCCURRED) {
					nmt[cnt].error_flag = RESOLVED;
					node_guarding_resolved(nmt[cnt].node);
				}
			}
			break;
		}
	}
}

void manage_master_ecp(void)	// 2.2.1 some changes
{
	unsigned16 cnt;

	for (cnt = 0; cnt < CAN_NOF_NODES; cnt++) {
		if (nmt[cnt].beattot != 0) {
			if (nmt[cnt].beatcnt > 0) {
				nmt[cnt].beatcnt--;
				if (nmt[cnt].beatcnt == 0) {	// 2.2.1 - NON-periodic, counting NOT resumed with error
					nmt[cnt].error_flag = OCCURRED;
					heartbeat_event(nmt[cnt].node);
				}
			}
		} else if (nmt[cnt].lifetot != 0) {
			if (nmt[cnt].guardcnt > 0) {
				nmt[cnt].guardcnt--;
				if (nmt[cnt].guardcnt == 0) {
					nmt[cnt].guardcnt = nmt[cnt].guardtot;
					request_nodeguard(nmt[cnt].node);
				}
			}
			if (nmt[cnt].lifecnt > 0) {
				nmt[cnt].lifecnt--;
				if (nmt[cnt].lifecnt == 0) {	// 2.2.1 - NON-periodic, counting NOT resumed with error
					nmt[cnt].error_flag = OCCURRED;
					node_guarding_event(nmt[cnt].node);
				}
			}
		}
	}
}

void start_can_master(void)
{
	unsigned16 cnt;

	node_state = CAN_NODE_STATE_OPERATIONAL;
	for (cnt = 0; cnt < CAN_NOF_PDO_RECEIVE; cnt++) {
		set_pdo_state((canindex)(CAN_INDEX_RCVPDO_COMM_MIN + cnt), VALID);
	}
	for (cnt = 0; cnt < CAN_NOF_PDO_TRANSMIT; cnt++) {
		set_pdo_state((canindex)(CAN_INDEX_TRNPDO_COMM_MIN + cnt), VALID);
	}
}

void can_init_nmt_master(void)
{
	unsigned16 cnt;

	for (cnt = 0; cnt < CAN_NOF_NODES; cnt++) {
		nmt[cnt].node = (cannode)(cnt+1);
		nmt[cnt].hbt = CAN_HBT_CONSUMER_MS;
		nmt[cnt].guardtime = 0;
		nmt[cnt].litif = 0;
		nmt[cnt].toggle = 0;
		start_ecp_master(cnt);
	}
}

#endif

#endif
