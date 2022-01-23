#include <can_header.h>

#define CAN_TIMERUSEC_MIN	100	// Minimum CANopen timer period in microseconds.

#ifdef CAN_OS_LINUX
	#include "can_system_linux.h"
#endif

#ifdef CAN_OS_WIN32
	#include "can_system_windows.h"
#endif
