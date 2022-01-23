#include <can_header.h>

#if CHECK_VERSION(3, 0, 3)
//  CHECK_VERSION(2, 3, 2)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 2)
//  CHECK_VERSION(1, 7, 1)

#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

#if CAN_PROTOCOL_BLOCK == FALSE && CAN_NOF_SDO_SERVER == 1
#include "can_server_min.h"
#else
#include "can_server_standard.h"
#endif

#endif

#endif
