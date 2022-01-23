#include <can_header.h>

#if CAN_APPLICATION_MODE == MASTER

static void monitor(void)
{
	canopen_monitor();
	#if CAN_SLAVE_DEVICE_CLASS == CAN_DEVICE_TEST
	test_monitor();
	#endif
	can_sleep(10*CAN_SLEEP_ONE_MILLISEC);
	// Sleep is used ONLY to lower CPU load in OS related applications
	// NOT needed for microcontroller applications
}

int main(int argc, char **argv)
{
	if (argc <= 1) return CAN_ERRET_MAIN;
	if (start_can_device((unsigned8)atoi(argv[1])) != CAN_RETOK) return CAN_ERRET_MAIN;
	#if CAN_SLAVE_DEVICE_CLASS == CAN_DEVICE_TEST
	start_test_application();
	#endif
	while (TRUE) monitor();
	if (stop_can_device() != CAN_RETOK) return CAN_ERRET_MAIN;
	return CAN_RETURN_MAIN;
}

#elif CAN_APPLICATION_MODE == SLAVE

static void monitor(void)
{
	canopen_monitor();
	can_sleep(10*CAN_SLEEP_ONE_MILLISEC);
	// Sleep is used ONLY to lower CPU load in OS related applications
	// NOT needed for microcontroller applications
}

int main(void)
{
	if (start_can_device(CAN_NETWORK_CONTROLLER) != CAN_RETOK) return CAN_ERRET_MAIN;
	while (TRUE) monitor();
	if (stop_can_device() != CAN_RETOK) return CAN_ERRET_MAIN;
	return CAN_RETURN_MAIN;
}

#elif CAN_APPLICATION_MODE == TEST

static void monitor(void)
{
	canopen_monitor();
	test_monitor();
	can_sleep(10*CAN_SLEEP_ONE_MILLISEC);
	// Sleep is used ONLY to lower CPU load in OS related applications
	// NOT needed for microcontroller applications
}

int main(void)
{
	if (start_can_device(CAN_NETWORK_CONTROLLER) != CAN_RETOK) return CAN_ERRET_MAIN;
	start_test_application();
	while (TRUE) monitor();
	if (stop_can_device() != CAN_RETOK) return CAN_ERRET_MAIN;
	return CAN_RETURN_MAIN;
}

#endif
