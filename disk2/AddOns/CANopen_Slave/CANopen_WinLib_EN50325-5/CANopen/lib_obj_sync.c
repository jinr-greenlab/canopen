#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 1)

#define MASK_SYNC_GENERATE		0x40000000	// SYNC message generate bit mask

static unsigned32 cobidsync;
static unsigned32 period;
static unsigned32 window, wincnt;
static unsigned32 ticktot, tickcnt;
static unsigned8 syncover, synccnt;

static void reset_sync(void)
{
	unsigned32 ttot;

	ticktot = 0;
	tickcnt = 0xFFFFFFFF;	// 2.2.2
	if (period == 0) {
		synccnt = CAN_SYNC_COUNTER_MIN;
		return;
	}
	ttot = period / CAN_TIMERUSEC;
	if (ttot == 0) ttot = 1;
	if ( (cobidsync & MASK_SYNC_GENERATE) != 0 ) {
		tickcnt = 1;
	} else {
		ttot += 1;
		tickcnt = ttot;
	}
	ticktot = ttot;
}

int16 get_sync_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_SYNC_COBID) {
		if (subind == 0) return sizeof(cobidsync);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	if (index == CAN_INDEX_SYNC_PERIOD) {
		if (subind == 0) return sizeof(period);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	if (index == CAN_INDEX_SYNC_WINDOW) {
		if (subind == 0) return sizeof(window);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	if (index == CAN_INDEX_SYNC_OVERFLOW) {
		if (subind == 0) return sizeof(syncover);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_sync_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_sync_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_MASK_ACCESS_RW;
}

int16 get_sync_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_sync_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_SYNC_OVERFLOW) return CAN_DEFTYPE_UNSIGNED8;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_sync_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;

	size = get_sync_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_SYNC_COBID) bpnt = (canbyte*)&cobidsync;
	else if (index == CAN_INDEX_SYNC_PERIOD) bpnt = (canbyte*)&period;
	else if (index == CAN_INDEX_SYNC_WINDOW) bpnt = (canbyte*)&window;
	else bpnt = (canbyte*)&syncover;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_sync_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, fnr;
	unsigned32 buf;
	canbyte *bpnt;

	size = get_sync_bytes_objsize(index, subind);
	if (size <= 0) return size;
	bpnt = (canbyte*)&buf; buf = 0;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (index == CAN_INDEX_SYNC_COBID) {
		if ( (cobidsync & MASK_SYNC_GENERATE) != 0 && (buf & MASK_SYNC_GENERATE) != 0 ) {
			return CAN_ERRET_OBD_OBJACCESS;
		}
		if (CAN_ID_MODE == CANID11 && (buf & CAN_MASK_IDSIZE) != 0) return CAN_ERRET_OBD_VALRANGE;
		if (check_canid_restricted((canlink)buf) == RESTRICTED) return CAN_ERRET_OBD_VALRANGE;	// 2.2.1
		buf &= (MASK_SYNC_GENERATE | CAN_MASK_IDSIZE | CAN_MASK_CANID);
		if ( (buf & MASK_SYNC_GENERATE) != 0) {
			fnr = correct_recv_canid(CAN_INDEX_SYNC_COBID, CAN_CANID_DUMMY);
		} else {
			fnr = correct_recv_canid(CAN_INDEX_SYNC_COBID, (canlink)buf);
		}
		if (fnr == CAN_RETOK) {
			cobidsync = buf;
			synccnt = CAN_SYNC_COUNTER_MIN;
			reset_sync();
		}
		return fnr;
	} else if (index == CAN_INDEX_SYNC_PERIOD) {
		period = buf;
		reset_sync();
	} else if (index == CAN_INDEX_SYNC_WINDOW) {
		window = buf;
	} else {
		if (ticktot != 0) return CAN_ERRET_OBD_DEVSTATE;
		if (buf == 0 || (buf >= CAN_SYNC_COUNTER_MIN+1 && buf <= CAN_SYNC_COUNTER_MAX)) {
			syncover = (unsigned8)buf;
			synccnt = CAN_SYNC_COUNTER_MIN;
		} else return CAN_ERRET_OBD_VALRANGE;
	}
	return CAN_RETOK;
}

void reset_sync_counter(void)
{
	synccnt = CAN_SYNC_COUNTER_MIN;
}

unsigned8 sync_window_expired(void)
{
	if (window == 0) return FALSE;
	if (wincnt == 0) return TRUE;
	return FALSE;
}

void sync_received(canframe *cf)	// 2.2.1 some changes
{
	unsigned8 sc;

	if (syncover > CAN_SYNC_COUNTER_MIN) {
		if (cf->len != CAN_DATALEN_SYNC_COUNTER) {
			produce_emcy_default(CAN_EMCY_SYNCLEN);
			return;
		}
		sc = cf->data[0];
		if (sc < CAN_SYNC_COUNTER_MIN || sc > CAN_SYNC_COUNTER_MAX) return;
	} else {
		if (cf->len != CAN_DATALEN_SYNC) {
			produce_emcy_default(CAN_EMCY_SYNCLEN);
			return;
		}
		sc = 0;
	}
	tickcnt = ticktot;
	wincnt = 1 + window / CAN_TIMERUSEC;
	process_sync_pdo(sc);
	consume_sync(sc);
}
	
void control_sync(void)
{
	canframe cf;

	if (wincnt > 0) wincnt--;
	if (ticktot == 0) return;
	if (node_state == CAN_NODE_STATE_STOPPED) {
		if ( (cobidsync & MASK_SYNC_GENERATE) != 0 ) tickcnt = 1;
		else tickcnt = ticktot;
		return;
	}
	if (tickcnt == 0) return;	// 2.2.1
	tickcnt--;
	if (tickcnt != 0) return;
	if ( (cobidsync & MASK_SYNC_GENERATE) != 0 ) {
		CLEAR_FRAME(&cf);
		cf.id = cobidsync & CAN_MASK_CANID;
		if (syncover > CAN_SYNC_COUNTER_MIN) {
			cf.data[0] = synccnt;
			synccnt++;
			if (synccnt > syncover) synccnt = CAN_SYNC_COUNTER_MIN;
			cf.len = CAN_DATALEN_SYNC_COUNTER;
		} else {
			cf.len = CAN_DATALEN_SYNC;
		}
		send_can_data(&cf);
		sync_received(&cf);
	} else {
		tickcnt = ticktot;
		no_sync_event();
	}
}

void can_init_sync(void)
{
	cobidsync = CAN_CANID_SYNC;
	window = 0;
	wincnt = 0;
	period = 0;
	reset_sync();	// 2.2.2
	syncover = 0;
	correct_recv_canid(CAN_INDEX_SYNC_COBID, (canlink)cobidsync);
}

#endif
