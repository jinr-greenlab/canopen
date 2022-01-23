#include <can_header.h>

#if !(CAN_APPLICATION_MODE == SLAVE && CAN_PROTOCOL_BLOCK == FALSE && CAN_NOF_SDO_SERVER == 1)

#define MEMSIZE_1		8
#define MEMSIZE_2		32
#define MEMSIZE_3		64
#define MEMSIZE_4		256

#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
#define NUMOF_1			8	// Number of 8 bytes size memory buffers
#define NUMOF_2			4	// Number of 32 bytes size memory buffers
#define NUMOF_3			4	// Number of 64 bytes size memory buffers
#define NUMOF_4			2	// Number of 256 bytes size memory buffers
#define NUMOF_MAX		2	// Number of MAXIMUM bytes size memory buffers
#elif CAN_APPLICATION_MODE == SLAVE
#define NUMOF_1			2	// Number of 8 bytes size memory buffers
#define NUMOF_2			1	// Number of 32 bytes size memory buffers
#define NUMOF_3			1	// Number of 64 bytes size memory buffers
#define NUMOF_4			1	// Number of 256 bytes size memory buffers
#define NUMOF_MAX		1	// Number of  MAXIMUM bytes size memory buffers
#endif

typedef char			align;

#if (CAN_SIZE_MAXSDOMEM <= MEMSIZE_1)
	#define NUMOF_MEMBUFS	NUMOF_1
	#define MEMSIZE_MAX		MEMSIZE_1
#elif (CAN_SIZE_MAXSDOMEM <= MEMSIZE_2)
	#define NUMOF_MEMBUFS	(NUMOF_1 + NUMOF_2)
	#define MEMSIZE_MAX		MEMSIZE_2
#elif (CAN_SIZE_MAXSDOMEM <= MEMSIZE_3)
	#define NUMOF_MEMBUFS	(NUMOF_1 + NUMOF_2 + NUMOF_3)
	#define MEMSIZE_MAX		MEMSIZE_3
#elif (CAN_SIZE_MAXSDOMEM <= MEMSIZE_4)
	#define NUMOF_MEMBUFS	(NUMOF_1 + NUMOF_2 + NUMOF_3 + NUMOF_4)
	#define MEMSIZE_MAX		MEMSIZE_4
#else
	#define NUMOF_MEMBUFS	(NUMOF_1 + NUMOF_2 + NUMOF_3 + NUMOF_4 + NUMOF_MAX)
	#define MEMSIZE_MAX		CAN_SIZE_MAXSDOMEM
#endif

static int16 sem_free;

static struct bufdes {
	int16 busy;
	unsigned8 capture;
	void *ptr;
} bd[NUMOF_MEMBUFS];

static union mem1 {
	align al;
	unsigned8 mb[MEMSIZE_1];
} m1[NUMOF_1];

#if CAN_SIZE_MAXSDOMEM > MEMSIZE_1
	static union mem2 {
		align al;
		unsigned8 mb[MEMSIZE_2];
	} m2[NUMOF_2];
#endif

#if CAN_SIZE_MAXSDOMEM > MEMSIZE_2
	static union mem3 {
		align al;
		unsigned8 mb[MEMSIZE_3];
	} m3[NUMOF_3];
#endif

#if CAN_SIZE_MAXSDOMEM > MEMSIZE_3
	static union mem4 {
		align al;
		unsigned8 mb[MEMSIZE_4];
	} m4[NUMOF_4];
#endif

#if CAN_SIZE_MAXSDOMEM > MEMSIZE_4
	static union mmax {
		align al;
		unsigned8 mb[MEMSIZE_MAX];
	} mm[NUMOF_MAX];
#endif

static void free_actually(void)
{
	unsigned16 cnt;

	CAN_CRITICAL_BEGIN
	sem_free++;
	if (sem_free == 0) {
		CAN_CRITICAL_END
		for (cnt = 0; cnt < NUMOF_MEMBUFS; cnt++) {
			if (bd[cnt].capture == 255) {
				bd[cnt].capture = 0;
				bd[cnt].busy = -1;
			}
		}
		CAN_CRITICAL_BEGIN
	}
	sem_free--;
	CAN_CRITICAL_END
}

canbyte *can_malloc(int32 bytes)
{
	unsigned16 nbuf;

	if (bytes <= 0 || bytes > MEMSIZE_MAX) return NULL;
	nbuf = 0;
#if CAN_SIZE_MAXSDOMEM > MEMSIZE_1
	if (bytes > MEMSIZE_1) nbuf += NUMOF_1;
#endif
#if CAN_SIZE_MAXSDOMEM > MEMSIZE_2
	if (bytes > MEMSIZE_2) nbuf += NUMOF_2;
#endif
#if CAN_SIZE_MAXSDOMEM > MEMSIZE_3
	if (bytes > MEMSIZE_3) nbuf += NUMOF_3;
#endif
#if CAN_SIZE_MAXSDOMEM > MEMSIZE_4
	if (bytes > MEMSIZE_4) nbuf += NUMOF_4;
#endif
	free_actually();
	CAN_CRITICAL_BEGIN
	sem_free++;
	CAN_CRITICAL_END
	while (nbuf < NUMOF_MEMBUFS) {
		CAN_CRITICAL_BEGIN
		bd[nbuf].busy++;
		if (bd[nbuf].busy == 0) {
			CAN_CRITICAL_END
			if (bd[nbuf].capture == 0) {
				bd[nbuf].capture = 1;
				CAN_CRITICAL_BEGIN
				sem_free--;
				CAN_CRITICAL_END
				return bd[nbuf].ptr;
			}
		} else {
			bd[nbuf].busy--;
			CAN_CRITICAL_END
		}
		nbuf++;
	}
	CAN_CRITICAL_BEGIN
	sem_free--;
	CAN_CRITICAL_END
	return NULL;
}

void can_free(canbyte *ptr)
{
	unsigned16 cnt;

	for (cnt = 0; cnt < NUMOF_MEMBUFS; cnt++) {
		if (ptr == bd[cnt].ptr) bd[cnt].capture = 255;
	}
}

void can_init_malloc(void)
{
	unsigned16 cnt, mbc;

	mbc = 0;
	for (cnt = 0; cnt < NUMOF_1; cnt++) {
		bd[mbc].ptr = m1[cnt].mb;
		mbc++;
	}
#if CAN_SIZE_MAXSDOMEM > MEMSIZE_1
	for (cnt = 0; cnt < NUMOF_2; cnt++) {
		bd[mbc].ptr = m2[cnt].mb;
		mbc++;
	}
#endif
#if CAN_SIZE_MAXSDOMEM > MEMSIZE_2
	for (cnt = 0; cnt < NUMOF_3; cnt++) {
		bd[mbc].ptr = m3[cnt].mb;
		mbc++;
	}
#endif
#if CAN_SIZE_MAXSDOMEM > MEMSIZE_3
	for (cnt = 0; cnt < NUMOF_4; cnt++) {
		bd[mbc].ptr = m4[cnt].mb;
		mbc++;
	}
#endif
#if CAN_SIZE_MAXSDOMEM > MEMSIZE_4
	for (cnt = 0; cnt < NUMOF_MAX; cnt++) {
		bd[mbc].ptr = mm[cnt].mb;
		mbc++;
	}
#endif
	for (cnt = 0; cnt < NUMOF_MEMBUFS; cnt++) {
		bd[cnt].capture = 0;
		bd[cnt].busy = -1;
	}
	sem_free = -1;
}

#endif
