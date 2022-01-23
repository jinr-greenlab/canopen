#ifndef __DS401_GENHEAD_H__
#define __DS401_GENHEAD_H__

// *** The application version. ***
// All modules major and minor versions must be equal to the listed ones
// and releases not less then the listed ones.

#define MAJ_VERS_APPL		2	// Major application software version
#define MIN_VERS_APPL		1	// Minor application software version
#define RELEASE_APPL		0	// The application software release


/******************************************************************/

#define R2DIO_IO					1
#define R2AIO_8INP					2
#define R2AIO_8OUT					3
#define R2AIO_4INP_2OUT				4

#define PLATFORM_WINDOWS			1
#define PLATFORM_STM32				2
#define PLATFORM_MILANDR			3

#define APPLICATION_REGULAR			1
#define APPLICATION_TEST			2

#define TESTMODE_TIMER				1
#define TESTMODE_LOOPBACK			2

#define HARDWARE_SW					1
#define VIRTUAL_SW					2

/******************************************************************/


#include <lib_commonhead.h>

#include "__DS401_defines_windows.h"
#include "__DS401_structures.h"

#include "DS401_globals.h"

#include <stdlib.h>		// NULL is defined

#if (IOREMOTE_PLATFORM == PLATFORM_STM32)
	#include <stm32f10x.h>
	#include <sa_clock.h>
	#include <hwconfig.h>
	#include <app-config.h>
	#include <pcb.h>
	#include <pcb-dio.h>
	#include <adc-app.h>
	#include <dac-app.h>
#elif (IOREMOTE_PLATFORM == PLATFORM_MILANDR)
	#include <MDR32Fx.h>
	#include <MDR32F9Qx_port.h>
	#include <MDR32F9Qx_rst_clk.h>
	#include <MDR32F9Qx_timer.h>
	#include <MDR32F9Qx_eeprom_FB.h>
	#include <Systick_FB.h>
	#include <PortsFunc_FB.h>
	#include <app-config.h>
#endif

#if (IOREMOTE_PRINTF_MODE == ON)
	#include <stdio.h>
	#include <string.h>
	#include <ctype.h>
	#include <stdarg.h>
#endif

#endif
