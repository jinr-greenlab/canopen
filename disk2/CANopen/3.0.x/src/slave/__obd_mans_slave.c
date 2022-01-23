#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 0)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 0)

#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

#if CAN_SLAVE_DEVICE_CLASS == CAN_DEVICE_TEST
	#include "__obdms_slave_test.h"
#endif

#endif

#endif
