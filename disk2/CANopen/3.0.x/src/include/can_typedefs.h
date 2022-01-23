// *** CANopen data type definitions ***

typedef	signed char		int8;
typedef	unsigned char	unsigned8;
typedef	signed short	int16;
typedef	unsigned short	unsigned16;
typedef	float			real32;
typedef	double			real64;

#ifdef CAN_OS_LINUX
typedef	signed int			int32;
typedef	unsigned int		unsigned32;
typedef	signed long long	int64;
typedef	unsigned long long	unsigned64;
#endif
#ifdef CAN_OS_WIN32
typedef	signed int			int32;
typedef	unsigned int		unsigned32;
typedef	LONGLONG			int64;
typedef	ULONGLONG			unsigned64;
#endif

typedef	unsigned8		canbyte;	// CAN data byte
typedef	unsigned8		cannode;	// Node-ID
typedef	unsigned16		canindex;	// Object dictionary index
typedef	unsigned8		cansubind;	// Object dictionary subindex

#if CAN_ID_MODE == CANID11
	typedef	unsigned16		canlink;	// CAN datalink identifier, v. 2.3 renamed
#elif CAN_ID_MODE == CANID29
	typedef	unsigned32		canlink;	// CAN datalink identifier, v. 2.3 renamed
#endif

#if CAN_APPLICATION_MODE == TEST
	typedef	int16			canev;		// CAN event
	typedef struct {
		unsigned32 id;
		unsigned8 data[8];
		unsigned8 len;
		unsigned16 flags;
	} canframe;
#else
	typedef	_s16			canev;		// CAN event
	typedef	canmsg_t		canframe;	// CAN network frame
#endif

