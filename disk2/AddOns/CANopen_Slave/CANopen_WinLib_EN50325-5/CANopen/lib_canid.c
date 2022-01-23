#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 2)

static struct recvcanid {
	canlink canid;
	canindex index;
} cob[CAN_NOF_RECV_CANIDS];

#if CAN_HARD_ACCEPTANCE_FILTER == AFSINGLE

static int16 cifunc_set_filter(_u32 acode0, _u32 amask0)
{
	unsigned8 chan, mask;
	int16 fnr;

	if (netmask_work == 0) return CAN_ERRET_CI_NETWORKS;
	fnr = CAN_RETOK;
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_work & mask) {
			if (CiSetFilter(chan, acode0, amask0) < 0) fnr = CAN_ERRET_CI_FILTER;
		}
		mask <<= 1;
	}
	return fnr;
}

static int16 set_acceptance_filter(void)
{
	unsigned16 cnt;
	unsigned32 mask_or;

	if (cifunc_stop() != CAN_RETOK) return CAN_ERRET_CI_STOP;
	mask_or = CAN_CANID_NMT_ERROR_BASE + node_id;
	mask_or |= CAN_CANID_GFC;
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) mask_or |= cob[cnt].canid;
	if (cifunc_set_filter(0, (~mask_or & CAN_MASK_CANID)) != CAN_RETOK) return CAN_ERRET_CI_FILTER;
	if (cifunc_start() != CAN_RETOK) return CAN_ERRET_CI_START;
	return CAN_RETOK;
}

#elif CAN_HARD_ACCEPTANCE_FILTER == AFDUAL

static int16 cifunc_set_filter(_u32 acode0, _u32 amask0, _u32 acode1, _u32 amask1)
{
	unsigned8 chan, mask;
	int16 fnr;

	if (netmask_work == 0) return CAN_ERRET_CI_NETWORKS;
	fnr = CAN_RETOK;
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_work & mask) {
			if (CiSetDualFilter(chan, acode0, amask0, acode1, amask1) < 0) fnr = CAN_ERRET_CI_FILTER;
		}
		mask <<= 1;
	}
	return fnr;
}

static int16 set_acceptance_filter(void)
{
	unsigned16 cnt;
	unsigned32 mask_zn, mask_or, mask_and;

	if (cifunc_stop() != CAN_RETOK) return CAN_ERRET_CI_STOP;
	mask_zn = CAN_CANID_GFC;
	mask_or = CAN_CANID_NMT_ERROR_BASE + node_id;
	mask_and = mask_or;
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		if ((cob[cnt].canid & CAN_MASK_CANID_NODE) == 0) {
			mask_zn |= cob[cnt].canid;
		} else {
			mask_or |= cob[cnt].canid;
			mask_and &= cob[cnt].canid;
		}
	}
	if (cifunc_set_filter(0, (~mask_zn & CAN_MASK_CANID), \
						mask_or, (~(mask_or ^ mask_and) & CAN_MASK_CANID)) != CAN_RETOK) {
		return CAN_ERRET_CI_FILTER;
	}
	if (cifunc_start() != CAN_RETOK) return CAN_ERRET_CI_START;
	return CAN_RETOK;
}

#elif CAN_HARD_ACCEPTANCE_FILTER == AFTRIPLE
// 3.0.0 triple acceptance filter implemented for EN50325-5
// GFC, odd and even ID filters for EN50325-5 are maintained separately

static int16 cifunc_set_filter(_u32 acode0, _u32 amask0, _u32 acode1, _u32 amask1, _u32 acode_odd, _u32 amask_odd, _u32 acode_even, _u32 amask_even)
{
	unsigned8 chan, mask;
	int16 fnr;

	if (netmask_work == 0) return CAN_ERRET_CI_NETWORKS;
	fnr = CAN_RETOK;
	mask = 1;
	for (chan = 0; chan <= CAN_CHANNEL_MAX; chan++) {
		if (netmask_work & mask) {
			if (CiSetFilter_zero(chan, acode0, amask0) < 0) fnr = CAN_ERRET_CI_FILTER;
			if (CiSetFilter_node(chan, acode1, amask1) < 0) fnr = CAN_ERRET_CI_FILTER;
			if (CiSetFilter_gfc(chan, CAN_CANID_GFC, CAN_MASK_CANID) < 0) fnr = CAN_ERRET_CI_FILTER;
			if (CiSetFilter_odd(chan, acode_odd, amask_odd) < 0) fnr = CAN_ERRET_CI_FILTER;
			if (CiSetFilter_even(chan, acode_even, amask_even) < 0) fnr = CAN_ERRET_CI_FILTER;
		}
		mask <<= 1;
	}
	return fnr;
}

static int16 set_acceptance_filter(void)
{
	unsigned16 cnt;
	unsigned32 mask_zn, mask_or, mask_and;		// Broadcast and pre-defined connection set CAN-IDs
	unsigned32 mask_or_odd, mask_and_odd;		// Other CAN-IDs, odd (EN50325-5)
	unsigned32 mask_or_even, mask_and_even;		// Other CAN-IDs, even (EN50325-5)
	canlink id;

	if (cifunc_stop() != CAN_RETOK) return CAN_ERRET_CI_STOP;
	mask_zn = 0;	// GFC filtered separately
	mask_or = CAN_CANID_NMT_ERROR_BASE + node_id;
	mask_and = mask_or;
	mask_or_odd = 0;
	mask_and_odd = 0;
	mask_or_even = 0;
	mask_and_even = 0;
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		id = cob[cnt].canid;
		if ((id & CAN_MASK_CANID_NODE) == 0) {
			mask_zn |= id;
		} else if ((id & CAN_MASK_CANID_NODE) == node_id) {
			mask_or |= id;
			mask_and &= id;
		} else {		// EN50325-5
			if (id & 1) {
				if (mask_or_odd == 0) {
					mask_or_odd = id;
					mask_and_odd = mask_or_odd;
				} else {
					mask_or_odd |= id;
					mask_and_odd &= id;
				}
			} else {
				if (mask_or_even == 0) {
					mask_or_even = id;
					mask_and_even = mask_or_even;
				} else {
					mask_or_even |= id;
					mask_and_even &= id;
				}
			}
		}
	}
	if (cifunc_set_filter(0, (~mask_zn & CAN_MASK_CANID), \
						mask_or, (~(mask_or ^ mask_and) & CAN_MASK_CANID), \
						mask_or_odd, (~(mask_or_odd ^ mask_and_odd) & CAN_MASK_CANID), \
						mask_or_even, (~(mask_or_even ^ mask_and_even) & CAN_MASK_CANID)) != CAN_RETOK) {
		return CAN_ERRET_CI_FILTER;
	}
	if (cifunc_start() != CAN_RETOK) return CAN_ERRET_CI_START;
	return CAN_RETOK;
}

#endif

int16 correct_recv_canid(canindex index, canlink canid)
{
	unsigned16 cnt;

	if (index == CAN_INDEX_DUMMY) return CAN_RETOK;
	canid &= CAN_MASK_CANID;
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		if (index == cob[cnt].index) {
			cob[cnt].index = CAN_INDEX_DUMMY;
			cob[cnt].canid = CAN_CANID_DUMMY;
		}
	}
	if (canid == CAN_CANID_DUMMY) {
		return set_acceptance_filter();
	}
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		if (cob[cnt].index == CAN_INDEX_DUMMY) {
			cob[cnt].index = index;
			cob[cnt].canid = canid;
			return set_acceptance_filter();
		}
	}
	return CAN_ERRET_OUTOFMEM;
}

int16 correct_double_canid(canindex index, canlink canid_1, canlink canid_2)
{
	unsigned16 cnt;

	if (index == CAN_INDEX_DUMMY) return CAN_RETOK;
	canid_1 &= CAN_MASK_CANID;
	canid_2 &= CAN_MASK_CANID;
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		if (index == cob[cnt].index) {
			cob[cnt].index = CAN_INDEX_DUMMY;
			cob[cnt].canid = CAN_CANID_DUMMY;
		}
	}
	if (canid_1 == CAN_CANID_DUMMY || canid_2 == CAN_CANID_DUMMY) {
		return set_acceptance_filter();
	}
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		if (cob[cnt].index == CAN_INDEX_DUMMY) {
			cob[cnt].index = index;
			cob[cnt].canid = canid_1;
			break;
		}
	}
	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		if (cob[cnt].index == CAN_INDEX_DUMMY) {
			cob[cnt].index = index;
			cob[cnt].canid = canid_2;
			return set_acceptance_filter();
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

unsigned8 check_canid_restricted(canlink canid)		// 2.2.1
{
	canid &= CAN_MASK_CANID;
	if (canid == 0x000) return RESTRICTED;
	if (canid >= 0x001 && canid <= 0x07F) return RESTRICTED;
	if (canid >= 0x101 && canid <= 0x180) return RESTRICTED;
	if (canid >= 0x581 && canid <= 0x5FF) return RESTRICTED;
	if (canid >= 0x601 && canid <= 0x67F) return RESTRICTED;
	if (canid >= 0x6E0 && canid <= 0x6FF) return RESTRICTED;
	if (canid >= 0x701 && canid <= 0x77F) return RESTRICTED;
	if (canid >= 0x780 && canid <= 0x7FF) return RESTRICTED;
	return UN_RESTRICTED;
}

void can_init_recv_canids(void)
{
	unsigned16 cnt;

	for (cnt = 0; cnt < CAN_NOF_RECV_CANIDS; cnt++) {
		cob[cnt].canid = CAN_CANID_DUMMY;
		cob[cnt].index = CAN_INDEX_DUMMY;
	}
}

#endif
