#ifndef __GENHEAD_WINLIB_H__
#define __GENHEAD_WINLIB_H__

#include <lib_commonhead.h>
#include <lib_application.h>
#include <lib_globals.h>


// *** The based-on CANopen library version. ***
// All modules major and minor versions must be equal to the listed ones
// and releases not less then the listed ones.

#define MAJ_VERS_CANLIB		3	// Major CANopen library software version
#define MIN_VERS_CANLIB		0	// Minor CANopen library software version
#define RELEASE_CANLIB		0	// The CANopen library software release


// *** CAN controller hardware acceptance filter definition ***
// Determined by the target platform and application

#define CAN_HARD_ACCEPTANCE_FILTER		AFSINGLE	// Single level hardware acceptance filter
//#define CAN_HARD_ACCEPTANCE_FILTER		AFDUAL		// Dual level hardware acceptance filter
//#define CAN_HARD_ACCEPTANCE_FILTER		AFTRIPLE	// Triple level hardware acceptance filter (for EN50325-5)

#endif
