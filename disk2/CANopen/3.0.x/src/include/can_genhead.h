#ifndef __CAN_GENHEAD_H__
#define __CAN_GENHEAD_H__

#include <can_defines.h>

#if CAN_APPLICATION_MODE != TEST
#include <chai.h>
#endif

#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#endif

#ifdef CAN_OS_LINUX
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#endif

#ifdef CAN_OS_WIN32
#include <windows.h>
#ifdef _MT
#include <process.h>
#endif
#endif

#include <can_typedefs.h>
#include <can_structures.h>
#include <can_macros.h>
#include <can_globals.h>

#endif
