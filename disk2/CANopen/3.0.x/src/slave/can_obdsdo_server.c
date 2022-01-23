#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 1)

#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

#define MASK_SDO_COBID_DYNAMIC		0x40000000	// SDO COBID value assigned statically or dynamically

#if CAN_NOF_SDO_SERVER == 1
#include "can_obdsdo_server_default.h"
#else
#include "can_obdsdo_server_num.h"
#endif

#endif

#endif
