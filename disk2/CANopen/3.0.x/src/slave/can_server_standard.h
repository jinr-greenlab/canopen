static struct sdosrvfull srvfull[CAN_SIZE_SRVFULL];
static int16 sem_resetcan, flag_resetcan;

static void resetcanwork(struct sdosrvfull *sr)
{
	sr->toggle = 0;
	sr->timeout = 1 + CAN_TIMEOUT_SERVER / CAN_TIMERUSEC;		// 2.2.1
	sr->si.sdoind = 0;											// 2.3.1
	if (sr->dynamem == TRUE) can_free(sr->bufbeg);
	sr->bufbeg = NULL;
	sr->bufpnt = NULL;
	sr->dynamem = FALSE;
#if CAN_PROTOCOL_BLOCK == TRUE
	sr->sub = CAN_BLMODE_NORMAL;
#endif
	sr->capture = 0;
	sr->busy = -1;
}

void can_server_control(void)
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
	for (cnt = 0; cnt < CAN_SIZE_SRVFULL; cnt++) {
		if (srvfull[cnt].busy < 0) continue;
		srvfull[cnt].timeout--;
		if (srvfull[cnt].timeout == 0) resetcanwork(srvfull + cnt);
	}
	CAN_CRITICAL_BEGIN
	sem_resetcan--;
	CAN_CRITICAL_END
}

#include "can_server_common.h"

#if CAN_PROTOCOL_BLOCK == TRUE
#include "can_server_block.h"
#endif

static void sdo_server_segmented_init(struct cansdo *sd, int32 size)
{
	unsigned16 cnt;

	if (sd->cs == CAN_CCS_SDO_UPLOAD_INIT) {
		sd->cs = CAN_SCS_SDO_UPLOAD_INIT;
		u32_to_canframe(size, sd->bd);
		sd->b0.sg.bit_0 = 1;
		sd->b0.sg.bit_1 = 0;
	} else {
		if (sd->b0.sg.bit_0 != 0 && (unsigned32)size != canframe_to_u32(sd->bd)) {
			abort_can_sdo(&sd->si, CAN_ABORT_SDO_DATAMISM);
			return;
		}
		sd->cs = CAN_SCS_SDO_DOWNLOAD_INIT;
		clear_can_data(sd->bd);
	}
	contcan_lock();
	for (cnt = 0; cnt < CAN_SIZE_SRVFULL; cnt++) {
		CAN_CRITICAL_BEGIN
		srvfull[cnt].busy++;
		if (srvfull[cnt].busy == 0) {
			CAN_CRITICAL_END
			if (srvfull[cnt].capture == 0) {
				srvfull[cnt].capture = 1;
				srvfull[cnt].bufbeg = can_malloc(size);
				if (srvfull[cnt].bufbeg == NULL) {
					abort_can_sdo(&sd->si, CAN_ABORT_SDO_OUTOFMEM);
					resetcanwork(srvfull + cnt);
					contcan_unlock();
					return;
				}
				srvfull[cnt].dynamem = TRUE;
				srvfull[cnt].bufpnt = srvfull[cnt].bufbeg;
				srvfull[cnt].rembytes = size;
				srvfull[cnt].si = sd->si;
				if (sd->cs == CAN_SCS_SDO_UPLOAD_INIT) {
					if (server_read_obd(&srvfull[cnt].si, srvfull[cnt].bufbeg) != CAN_RETOK) {
						resetcanwork(srvfull + cnt);
						contcan_unlock();
						return;
					}
				}
				contcan_unlock();
				send_can_sdo(sd);
				return;
			}
		} else {
			srvfull[cnt].busy--;
			CAN_CRITICAL_END
		}
	}
	contcan_unlock();
	abort_can_sdo(&sd->si, CAN_ABORT_SDO_OUTOFMEM);
}

static void process_segmented_data(struct sdosrvfull *sr, struct cansdo *sd)
{
	unsigned8 numb;
	int16 cnt;

	if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA) {
		numb = CAN_DATASEGM_OTHER - sd->b0.sg.ndata;
		if ( (sr->rembytes < numb) ||
		      (sr->rembytes > numb && sd->b0.sg.bit_0 != 0) ||
		      (sr->rembytes == numb && sd->b0.sg.bit_0 == 0) ) {
			abort_can_sdo(&sr->si, CAN_ABORT_SDO_DATAMISM);
			resetcanwork(sr);
			return;
		}
		for (cnt = 0; cnt < numb; cnt++) {
			*sr->bufpnt = sd->bd[cnt];
			sr->bufpnt++;
		}
		if (sd->b0.sg.bit_0 != 0) {
			if (server_write_obd(&sr->si, sr->bufbeg) != CAN_RETOK) {
				resetcanwork(sr);
				return;
			}
		}
		sd->cs = CAN_SCS_SDO_DOWNSEGM_DATA;
		clear_can_data(sd->bd);
	} else {
		clear_can_data(sd->bd);
		if (sr->rembytes > CAN_DATASEGM_OTHER) {
			numb = CAN_DATASEGM_OTHER;
			sd->b0.sg.bit_0 = 0;
		} else {
			numb = (unsigned8)sr->rembytes;
			sd->b0.sg.bit_0 = 1;
		}
		for (cnt = 0; cnt < numb; cnt++) {
			sd->bd[cnt] = *sr->bufpnt;
			sr->bufpnt++;
		}
		sd->cs = CAN_SCS_SDO_UPSEGM_DATA;
		sd->b0.sg.ndata = CAN_DATASEGM_OTHER - numb;
	}
	send_can_sdo(sd);
	if (sd->b0.sg.bit_0 == 0) {
		sr->rembytes -= numb;
		sr->toggle ^= 1;
		sr->timeout = 1 + CAN_TIMEOUT_SERVER / CAN_TIMERUSEC;		// 2.2.1
	} else resetcanwork(sr);
}

static void can_server_sdo_process(struct sdosrvfull *sr, canframe *cf)
{
	struct cansdo sd;

	sd.si.sdoind = sr->si.sdoind;
	parse_sdo(&sd, cf->data);
	if (sd.cs == CAN_CS_SDO_ABORT) resetcanwork(sr);
	else if (sd.cs == CAN_CCS_SDO_DOWNSEGM_DATA || sd.cs == CAN_CCS_SDO_UPSEGM_DATA) {
		if (sd.b0.sg.toggle != sr->toggle) {
			abort_can_sdo(&sr->si, CAN_ABORT_SDO_TOGGLE);
			resetcanwork(sr);
		} else process_segmented_data(sr, &sd);
#if CAN_PROTOCOL_BLOCK == TRUE
	} else if (sd.cs == CAN_CCS_SDO_DOWNBLOCK) {
		can_server_sdo_downblock_end(sr, &sd);
	} else if (sd.cs == CAN_CCS_SDO_UPBLOCK) {
		can_server_sdo_upblock(sr, &sd);
#endif
	} else {
		abort_can_sdo(&sr->si, CAN_ABORT_SDO_CS);
		resetcanwork(sr);
	}
}

static void can_server_sdo_init(canindex sdoind, canframe *cf)
{
	int32 size;
	int16 access;
	struct cansdo sd;

	sd.si.sdoind = sdoind;
	parse_sdo(&sd, cf->data);
	size = server_get_object_size(sd.si.index, sd.si.subind, BYTES);
	if (size < 0) {
		if (size == CAN_ERRET_OBD_NOOBJECT) abort_can_sdo(&sd.si, CAN_ABORT_SDO_NOOBJECT);
		else if (size == CAN_ERRET_OBD_NOSUBIND) abort_can_sdo(&sd.si, CAN_ABORT_SDO_NOSUBIND);
		else abort_can_sdo(&sd.si, CAN_ABORT_SDO_DATAMISM);
		return;
	}
	access = server_see_access(sd.si.index, sd.si.subind);
	if (access < 0) {
		abort_can_sdo(&sd.si, CAN_ABORT_SDO_NOOBJECT);
		return;
	}
	if (sd.cs == CAN_CCS_SDO_DOWNLOAD_INIT) {
		if ((access & CAN_MASK_ACCESS_WO) == 0) {
			abort_can_sdo(&sd.si, CAN_ABORT_SDO_READONLY);
			return;
		}
		if (sd.b0.sg.bit_1 != 0) sdo_server_expedited_download(&sd, size);
		else sdo_server_segmented_init(&sd, size);
	} else if (sd.cs == CAN_CCS_SDO_UPLOAD_INIT) {
		if ((access & CAN_MASK_ACCESS_RO) == 0) {
			abort_can_sdo(&sd.si, CAN_ABORT_SDO_WRITEONLY);
			return;
		}
		if (size == 0) {		// 3.0.1 extra check
			abort_can_sdo(&sd.si, CAN_ABORT_SDO_NODATA);
			return;
		}
		if (size <= CAN_DATASEGM_EXPEDITED) sdo_server_expedited_upload(&sd, size);
		else sdo_server_segmented_init(&sd, size);
#if CAN_PROTOCOL_BLOCK == TRUE
	} else if (sd.cs == CAN_CCS_SDO_DOWNBLOCK) {
		if ((access & CAN_MASK_ACCESS_WO) == 0) {
			abort_can_sdo(&sd.si, CAN_ABORT_SDO_READONLY);
			return;
		}
		can_server_sdo_block_init(&sd, size);
	} else if (sd.cs == CAN_CCS_SDO_UPBLOCK) {
		if ((access & CAN_MASK_ACCESS_RO) == 0) {
			abort_can_sdo(&sd.si, CAN_ABORT_SDO_WRITEONLY);
			return;
		}
		if (size == 0) {		// 3.0.1 extra check
			abort_can_sdo(&sd.si, CAN_ABORT_SDO_NODATA);
			return;
		}
		can_server_sdo_block_init(&sd, size);
#endif
	} else {
		abort_can_sdo(&sd.si, CAN_ABORT_SDO_CS);
	}
}

void can_server_sdo(canindex sdoind, canframe *cf)
{
	unsigned16 cnt;

	contcan_lock();
	for (cnt = 0; cnt < CAN_SIZE_SRVFULL; cnt++) {
		if (srvfull[cnt].busy >= 0 && srvfull[cnt].si.sdoind == sdoind) {
		#if CAN_PROTOCOL_BLOCK == TRUE
			if (srvfull[cnt].sub == CAN_BLMODE_DOWNBLOCK) can_server_sdo_downblock(srvfull+cnt, cf);
			else can_server_sdo_process(srvfull+cnt, cf);
		#else
			can_server_sdo_process(srvfull+cnt, cf);
		#endif
			contcan_unlock();
			return;
		}
	}
	contcan_unlock();
	can_server_sdo_init(sdoind, cf);
}

void can_init_server(void)
{
	unsigned16 cnt;

 	sem_resetcan = 0;
	#if CAN_PROTOCOL_BLOCK == TRUE
 	sem_upblock = 0;
	#endif
 	flag_resetcan = 0;
	for (cnt = 0; cnt < CAN_SIZE_SRVFULL; cnt++) {
		srvfull[cnt].dynamem = FALSE;
		resetcanwork(srvfull + cnt);
	}
 	sem_resetcan = -1;
	#if CAN_PROTOCOL_BLOCK == TRUE
 	sem_upblock = -1;
	#endif
}
