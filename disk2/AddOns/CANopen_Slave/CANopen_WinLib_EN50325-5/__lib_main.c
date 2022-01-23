#include <lib_header.h>

static void monitor(void)
{

//	ci_propagate_sigs();
//  Propagate CAN driver signals for pure polling or signal/polling mode.
//  For the RX signal mode CAN receive frame re-entrant interrupts
//  may be enabled within the CiRead(...) driver function.

	canopen_monitor();

	can_sleep(10*CAN_SLEEP_ONE_MILLISEC);
// Sleep is used ONLY to lower CPU load in OS related applications
// NOT needed for microcontroller applications
}

int main(void)
{
	if (start_can_device() != CAN_RETOK) return CAN_ERRET_MAIN;
	while (TRUE) monitor();
	if (stop_can_device() != CAN_RETOK) return CAN_ERRET_MAIN;
	return CAN_RETURN_MAIN;
}
