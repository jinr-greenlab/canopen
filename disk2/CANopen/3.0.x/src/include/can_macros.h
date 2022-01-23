// *** CANopen macros definitions ***

#if CAN_APPLICATION_MODE == TEST
	#define	CLEAR_FRAME	test_zero
#else
	#define	CLEAR_FRAME	msg_zero
#endif

#define CHECK_VERSION(MAJ, MIN, REL)   ((MAJ == MAJOR_VERSION) && (MIN == MINOR_VERSION) && (REL >= RELEASE))

#define OBJECT_DICTIONARY_TO_CANOPEN for (cnt = 0; cnt < size; cnt++) { \
		*data = *bpnt;  \
		data++; bpnt++; \
}

#define FROM_CANOPEN_TO_OBJECT_DICTIONARY for (cnt = 0; cnt < size; cnt++) { \
		*bpnt = *data;  \
		bpnt++; data++; \
}

#ifdef CAN_OS_WIN32
	#define CAN_CRITICAL_INIT    init_critical();
	#define CAN_CRITICAL_BEGIN   enter_critical();
	#define CAN_CRITICAL_END     leave_critical();
#else
	#define CAN_CRITICAL_INIT
	#define CAN_CRITICAL_BEGIN
	#define CAN_CRITICAL_END
#endif
