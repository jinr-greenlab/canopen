#ifndef __COMMONHEAD_WINLIB_H__
#define __COMMONHEAD_WINLIB_H__

#define _WIN32_WINNT  _WIN32_WINNT_WIN7  // 0x0601

#include <windows.h>
#ifdef _MT
	#include <process.h>
#endif

#include <chai.h>

#include <lib_defines.h>
#include <lib_typedefs.h>
#include <lib_macros.h>
#include <lib_structures.h>

#endif
