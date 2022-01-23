#include <can_header.h>

#if CHECK_VERSION(3, 0, 1)
//  CHECK_VERSION(2, 3, 4)
//  CHECK_VERSION(2, 2, 0)
//  CHECK_VERSION(2, 1, 3)
//  CHECK_VERSION(2, 0, 3)
//  CHECK_VERSION(1, 7, 1)

#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

#if CAN_SLAVE_DEVICE_CLASS == CAN_DEVICE_TEST
	#include "__can_device_test.h"
#endif

#endif

#endif
