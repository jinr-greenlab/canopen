#include <can_header.h>

#if CHECK_VERSION(3, 0, 1)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 1)

#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST

static struct sdocltbasic cltbasic[CAN_SIZE_CLTBASIC];
static int16 sem_resetcan, flag_resetcan;

static void resetcanwork(struct sdocltbasic *cb)
{
	cb->ct.ss.state = CAN_TRANSTATE_OK;
	cb->ct.ss.abortcode = 0;
	cb->ct.sd.si.sdoind = 0;		// 2.3.1
	cb->ct.bufpnt = NULL;
	cb->ct.blksize = 0;
	cb->timeout = 1 + CAN_TIMEOUT_RETRIEVE / CAN_TIMERUSEC;		// 2.2.1
	cb->capture = 0;
	cb->busy = -1;
}

void can_client_control(void)
{
	unsigned16 cnt;

	CAN_CRITICAL_BEGIN
	sem_resetcan++;
	if (sem_resetcan != 0) {
		sem_resetcan--;
		CAN_CRITICAL_END
		flag_resetcan++;
		return;
	}
	CAN_CRITICAL_END
	for (cnt = 0; cnt < CAN_SIZE_CLTBASIC; cnt++) {
		if (cltbasic[cnt].busy < 0) continue;
		cltbasic[cnt].timeout--;				// 2.2.1
		if (cltbasic[cnt].timeout == 0) {		// 2.2.1
			if (cltbasic[cnt].ct.ss.state == CAN_TRANSTATE_SDO_WORK) {
				abort_can_sdo(&cltbasic[cnt].ct.sd.si, CAN_ABORT_SDO_TIMEOUT);
				cltbasic[cnt].ct.ss.state = CAN_TRANSTATE_SDO_NET_TIMEOUT;
				cltbasic[cnt].timeout = 1 + CAN_TIMEOUT_READ / CAN_TIMERUSEC;		// 2.2.1
			} else {
				resetcanwork(cltbasic + cnt);
			}
		}
	}
	CAN_CRITICAL_BEGIN
	sem_resetcan--;
	CAN_CRITICAL_END
}

static void contcan_lock(void)
{
	CAN_CRITICAL_BEGIN
	sem_resetcan++;
	CAN_CRITICAL_END
}

static void contcan_unlock(void)
{
	CAN_CRITICAL_BEGIN
	sem_resetcan--;
	CAN_CRITICAL_END
	while (flag_resetcan > 0) {
		if (sem_resetcan != -1) break;
		can_client_control();
		flag_resetcan--;
	}
}

int16 can_client_send_block_frame(struct sdoclttrans *ct)
{
#if CAN_PROTOCOL_BLOCK == TRUE
	unsigned16 cnt;
	int16 fnr;
	canlink canid;
	canframe cf;

	CLEAR_FRAME(&cf);
	fnr = find_sdo_client_send_canid(ct->sd.si.sdoind, &canid);
	if (fnr != CAN_RETOK) return fnr;
	cf.id = canid;
	cf.data[0] = ((ct->sd.b0.bl.lf << 7) | (ct->sd.b0.bl.ds & CAN_MASK_SDO_SEQNO));
	for (cnt = 0; cnt < ct->sd.b0.bl.crc; cnt++) {
		cf.data[cnt+1] = *ct->bufpnt;
		ct->bufpnt++;
	}
	cf.len = CAN_DATALEN_SDO;
	return send_can_data(&cf);
#else
	return CAN_RETOK;
#endif
}

static void can_client_sdo_upblock(struct sdocltbasic *cb, canframe *cf)
{
#if CAN_PROTOCOL_BLOCK == TRUE
	unsigned16 cnt;

	if (cb->ct.sd.b0.bl.lf == 1) {
		if ( (cf->data[0] & CAN_MASK_SDO_SEQNO) == cb->ct.blksize ||
		      (cf->data[0] & CAN_MASK_SDO_BLAST) != 0 ) {
			cb->ct.sd.b0.bl.lf = 0;
			cb->ct.ss.state = CAN_TRANSTATE_OK;
		}
	} else if ((cf->data[0] & CAN_MASK_SDO_SEQNO) != 1+cb->ct.sd.b0.bl.ds) {
		cb->ct.sd.b0.bl.lf = 1;
	} else if ((cf->data[0] & CAN_MASK_SDO_BLAST) != 0) {
		if (cb->ct.rembytes > CAN_DATASEGM_OTHER) {
			cb->ct.ss.state = CAN_TRANSTATE_SDO_DATASIZE;
		} else {
			for (cnt = 1; cnt <= cb->ct.rembytes; cnt++) {
				*cb->ct.bufpnt = cf->data[cnt];
				cb->ct.bufpnt++;
			}
			cb->ct.sd.b0.bl.ds++;
			cb->ct.ss.state = CAN_TRANSTATE_OK;
		}
	} else {
		if (cb->ct.rembytes <= CAN_DATASEGM_OTHER) {
			cb->ct.ss.state = CAN_TRANSTATE_SDO_DATASIZE;
		} else {
			for (cnt = 1; cnt <= CAN_DATASEGM_OTHER; cnt++) {
				*cb->ct.bufpnt = cf->data[cnt];
				cb->ct.bufpnt++;
			}
			cb->ct.rembytes -= CAN_DATASEGM_OTHER;
			cb->ct.sd.b0.bl.ds++;
			if (cb->ct.sd.b0.bl.ds == cb->ct.blksize) {
				cb->ct.ss.state = CAN_TRANSTATE_OK;
			}
		}
	}
	cb->timeout = 1 + CAN_TIMEOUT_RETRIEVE / CAN_TIMERUSEC;		// 2.2.1
#endif
}

static void can_client_sdo_main(struct sdocltbasic *cb, canframe *cf)
{
	struct cansdo sd;

	sd.si.sdoind = cb->ct.sd.si.sdoind;
	parse_sdo(&sd, cf->data);
	if (sd.cs == CAN_CS_SDO_ABORT) {
		cb->ct.ss.abortcode = canframe_to_u32(sd.bd);
		cb->ct.ss.state = CAN_TRANSTATE_SDO_SRVABORT;
	} else if (sd.cs == cb->ct.adjcs) {
		cb->ct.sd = sd;
		cb->ct.ss.state = CAN_TRANSTATE_OK;
	} else {
		abort_can_sdo(&cb->ct.sd.si, CAN_ABORT_SDO_CS);
		cb->ct.ss.state = CAN_TRANSTATE_SDO_SCSERR;
	}
	cb->timeout = 1 + CAN_TIMEOUT_READ / CAN_TIMERUSEC;		// 2.2.1
}

void can_client_sdo(canindex sdoind, canframe *cf)
{
	unsigned16 cnt;

	contcan_lock();
	for (cnt = 0; cnt < CAN_SIZE_CLTBASIC; cnt++) {
		if (cltbasic[cnt].ct.ss.state != CAN_TRANSTATE_SDO_WORK) continue;
		if (cltbasic[cnt].ct.sd.si.sdoind == sdoind) {
			if (cltbasic[cnt].ct.blksize == 0) can_client_sdo_main(cltbasic+cnt, cf);
			else can_client_sdo_upblock(cltbasic+cnt, cf);
			break;
		}
	}
	contcan_unlock();
}

static void readcbas(struct sdoclttrans *ct)
{
	unsigned16 cnt;

	contcan_lock();
	for (cnt = 0; cnt < CAN_SIZE_CLTBASIC; cnt++) {
		if (cltbasic[cnt].capture != 255) continue;		// 2.3.1
		if (cltbasic[cnt].ct.sd.si.sdoind == ct->sd.si.sdoind) {
			if (cltbasic[cnt].ct.ss.state != CAN_TRANSTATE_SDO_WORK) {
				*ct = cltbasic[cnt].ct;
				resetcanwork(cltbasic + cnt);
			}
			contcan_unlock();
			return;
		}
	}
	contcan_unlock();
	ct->ss.state = CAN_TRANSTATE_SDO_READ_TIMEOUT;
}

static void request_client_trans(struct sdoclttrans *ct)
{
	unsigned16 cnt;
	int16 fnr;

	ct->ss.state = CAN_TRANSTATE_SDO_WORK;
	ct->ss.abortcode = 0;
	contcan_lock();
	for (cnt = 0; cnt < CAN_SIZE_CLTBASIC; cnt++) {
		CAN_CRITICAL_BEGIN
		cltbasic[cnt].busy++;
		if (cltbasic[cnt].busy == 0) {
			CAN_CRITICAL_END
			if (cltbasic[cnt].capture == 0) {
				cltbasic[cnt].capture = 1;
				if (ct->sd.cs == CAN_CCS_SDO_SPECIAL_UP) ct->sd.cs = CAN_CCS_SDO_UPBLOCK;
				else ct->blksize = 0;
				cltbasic[cnt].ct = *ct;
				cltbasic[cnt].ct.ss.state = CAN_TRANSTATE_SDO_WORK;
				cltbasic[cnt].capture = 255;		// 2.3.1
				if (ct->sd.cs == CAN_CCS_SDO_SPECIAL_DOWN) {
					fnr = can_client_send_block_frame(ct);
				} else {
					fnr = send_can_sdo(&ct->sd);
				}
				if (fnr != CAN_RETOK) {
					if (fnr == CAN_ERRET_SDO_INVALID) ct->ss.state = CAN_TRANSTATE_SDO_INVALID;
					else ct->ss.state = CAN_TRANSTATE_SDO_WRITERR;
					resetcanwork(cltbasic + cnt);
				}
				contcan_unlock();
				return;
			}
		} else {
			cltbasic[cnt].busy--;
			CAN_CRITICAL_END
		}
	}
	contcan_unlock();
	ct->ss.state = CAN_TRANSTATE_SDO_NOWORKB;
}

void can_client_basic(struct sdoclttrans *ct)
{
	unsigned32 tout;

	request_client_trans(ct);
	if (ct->ss.state != CAN_TRANSTATE_SDO_WORK) return;
	tout = (2 + ct->blksize/2) * (1 + CAN_TIMEOUT_RETRIEVE / CAN_SLEEP_READ);		// 2.2.1
	while (tout > 0) {
		can_sleep(CAN_SLEEP_READ);
		#if CAN_FRAME_READ_MODE == POLL
		can_read_handler(0);
		#endif
		readcbas(ct);
		if (ct->ss.state != CAN_TRANSTATE_SDO_WORK) return;
		tout--;
	}
	ct->ss.state = CAN_TRANSTATE_SDO_TRANS_TIMEOUT;
}

void can_init_client(void)
{
	unsigned16 cnt;

 	sem_resetcan = 0;
 	flag_resetcan = 0;
	for (cnt = 0; cnt < CAN_SIZE_CLTBASIC; cnt++) resetcanwork(cltbasic + cnt);
 	sem_resetcan = -1;
}

#endif

#endif
