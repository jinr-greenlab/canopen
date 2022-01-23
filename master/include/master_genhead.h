#ifndef __MASTER_GENHEAD_H__
#define __MASTER_GENHEAD_H__

#include <chai.h>

#include <master_defines.h>
#include <config_defines.h>
#include <__application_defines.h>
#include <__logger_defines.h>
#include <master_typedefs.h>

#ifdef CAN_OS_LINUX
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#endif

#define _WIN32_WINNT 0x0601

#ifdef CAN_OS_WIN32
#include <windows.h>
#ifdef _MT
#include <process.h>
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include <time.h>

#include <master_macros.h>
#include <master_structures.h>
#include <master_globals.h>

#endif
