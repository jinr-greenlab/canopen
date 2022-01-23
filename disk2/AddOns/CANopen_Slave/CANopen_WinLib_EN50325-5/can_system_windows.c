#include <lib_header.h>

#define CAN_TIMERUSEC_MIN	100	// Minimum CANopen timer period in microseconds.

struct ThreadArg{
	unsigned int msec;  // milliseconds
	void (* fun)(void);
};

static VOID APIENTRY TimerAPCfunct(LPVOID, DWORD, DWORD);
static unsigned int WINAPI ThreadFunct(void *);
struct ThreadArg ThreadArgs;
HANDLE TimerHandle=NULL;

CRITICAL_SECTION crs;

void can_sleep(int32 microseconds)
{
	if (microseconds <= 0) return;
	Sleep(1+microseconds/1000);
}

void can_init_system_timer(void (*handler)(void))	// 2.3.1 API changed
{
	HANDLE *ThreadHandle;
	unsigned int ThreadId;

	if (CAN_TIMERUSEC < CAN_TIMERUSEC_MIN) {
		set_error_field(CAN_EMCYREG_TIMERFAIL, 0);
 		return;
	}
	memset(&ThreadArgs, 0, sizeof(struct ThreadArg));
	ThreadArgs.msec = (CAN_TIMERUSEC+500)/1000;
	if (ThreadArgs.msec == 0) ThreadArgs.msec = 1;
	ThreadArgs.fun = handler;
	ThreadHandle = (HANDLE) _beginthreadex(NULL, 0, ThreadFunct, (void *)&ThreadArgs, 0, &ThreadId);
}

static unsigned int WINAPI ThreadFunct(void *PArgc)
{
	DWORD Period;
	LARGE_INTEGER DueTime;
	struct ThreadArg *p=(struct ThreadArg *)PArgc;

	Period=p->msec;
	DueTime.QuadPart = -(LONGLONG)Period * 10000;
	if (TimerHandle != NULL){
		CancelWaitableTimer (TimerHandle);
		CloseHandle (TimerHandle);
	}
	TimerHandle = CreateWaitableTimer (NULL, FALSE, NULL);
	if (TimerHandle == NULL){
		// Failure creating waitable timer
		set_error_field(CAN_EMCYREG_TIMERFAIL, 0);
 		return 1;
	}
	if (!SetWaitableTimer (TimerHandle, &DueTime,Period,TimerAPCfunct,NULL,TRUE )) {
		// Failure setting waitable timer
		set_error_field(CAN_EMCYREG_TIMERFAIL, 0);
 		return 1;
	}
	while (TRUE) {
		SleepEx (INFINITE, TRUE);
		(*p->fun)();
	}
	CancelWaitableTimer (TimerHandle);
	CloseHandle (TimerHandle);
	return 0;
}

static VOID APIENTRY TimerAPCfunct(LPVOID lpCount,
	DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
}

void can_cancel_system_timer(void)
{
	CancelWaitableTimer (TimerHandle);
	CloseHandle (TimerHandle);
}

void init_critical(void)
{
	InitializeCriticalSection(&crs);
}

void enter_critical(void)
{
	EnterCriticalSection(&crs);
}

void leave_critical(void)
{
	LeaveCriticalSection(&crs);
}

void enable_can_transmitter(void)
{
}

void disable_can_transmitter(void)
{
}

void green_led_on(void)
{
}

void green_led_off(void)
{
}

void red_led_on(void)
{
}

void red_led_off(void)
{
}
