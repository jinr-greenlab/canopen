#include <can_header.h>

#if CAN_APPLICATION_MODE == TEST

#define	FIFOSIZE	16

static canframe cnm[FIFOSIZE];
static unsigned16 tail=0, head=0;

void test_zero(canframe *cf)
{
	unsigned16 cnt;
	canbyte *bpnt;

	bpnt = (canbyte*)cf;
	for (cnt = 0; cnt < sizeof(canframe); cnt++) {
		*bpnt = 0; bpnt++;
	}
}

int16 read_can_test_driver(unsigned8 chan, canframe *cf, int16 cnt)
{
	unsigned16 t;

	if (tail == head) return -1;
	t = tail + 1;
	if (t >= FIFOSIZE) t = 0;
	*cf = cnm[t];
	tail = t;
	return 1;
}

int16 write_can_test_driver(unsigned8 chan, canframe *cf, int16 cnt)
{
	unsigned16 h;

	h = head + 1;
	if (h >= FIFOSIZE) h = 0;
	if (h == tail) return -1;
	cnm[h] = *cf;
	head = h;
	return 1;
}

#endif
