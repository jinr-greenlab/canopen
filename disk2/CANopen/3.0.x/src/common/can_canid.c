#include <can_header.h>

#if CHECK_VERSION(3, 0, 2)
//  CHECK_VERSION(2, 3, 4)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 2)
//  CHECK_VERSION(1, 7, 0)

#if (CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST) && CAN_MASTER_RECVCANID_METHOD == STATIC && CAN_ID_MODE == CANID11
#include "can_canid_static.h"
#else
#include "can_canid_dynamic.h"
#endif

unsigned8 check_sdo_canid(canindex index, cansubind subind, canlink canid)		// 2.2.1
{
	canid &= CAN_MASK_CANID;
	if (index >= CAN_INDEX_SERVER_SDO_MIN && index <= CAN_INDEX_SERVER_SDO_MAX) {
		if (index == CAN_INDEX_SERVER_SDO_DEFAULT) return RESTRICTED;
		if (canid == CAN_CANID_SDO_CS_BASE + node_id) return RESTRICTED;
		if (canid == CAN_CANID_SDO_SC_BASE + node_id) return RESTRICTED;
	}
	if (subind == 1) {
		if (canid < CAN_CANID_SDO_CS_MIN || canid > CAN_CANID_SDO_CS_MAX) return RESTRICTED;
	} else if (subind == 2) {
		if (canid < CAN_CANID_SDO_SC_MIN || canid > CAN_CANID_SDO_SC_MAX) return RESTRICTED;
	}
	return UN_RESTRICTED;
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

#endif
