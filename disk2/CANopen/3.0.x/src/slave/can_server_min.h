static struct sdosrvfull srvfull;
static canbyte databuf[CAN_SIZE_MAXSDOMEM];
static int16 sem_resetcan, flag_resetcan;

static void resetcanwork(void)
{
	srvfull.toggle = 0;
	srvfull.timeout = 1 + CAN_TIMEOUT_SERVER / CAN_TIMERUSEC;		// 2.2.1
	srvfull.si.sdoind = 0;											// 2.3.1
	srvfull.capture = 0;
	srvfull.busy = -1;
}

void can_server_control(void)
{
	CAN_CRITICAL_BEGIN
	sem_resetcan++;
	if (sem_resetcan != 0) flag_resetcan++;
	else if (srvfull.busy >= 0) {
		srvfull.timeout--;
		if (srvfull.timeout == 0) resetcanwork();
	}
	sem_resetcan--;
	CAN_CRITICAL_END
}

#include "can_server_common.h"

static void sdo_server_segmented_init(struct cansdo *sd, int32 size)
{
	if (size > CAN_SIZE_MAXSDOMEM) {
		abort_can_sdo(&sd->si, CAN_ABORT_SDO_OUTOFMEM);
		return;
	}
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
	CAN_CRITICAL_BEGIN
	srvfull.busy++;
	if (srvfull.busy == 0) {
		CAN_CRITICAL_END
		if (srvfull.capture == 0) {
			srvfull.capture = 1;
			srvfull.bufpnt = databuf;
			srvfull.rembytes = size;
			srvfull.si = sd->si;
			if (sd->cs == CAN_SCS_SDO_UPLOAD_INIT) {
				if (server_read_obd(&srvfull.si, databuf) != CAN_RETOK) {
					resetcanwork();
					contcan_unlock();
					return;
				}
			}
			contcan_unlock();
			send_can_sdo(sd);
			return;
		}
	} else {
		srvfull.busy--;
		CAN_CRITICAL_END
	}
	contcan_unlock();
	abort_can_sdo(&sd->si, CAN_ABORT_SDO_OUTOFMEM);
}

static void process_segmented_data(struct cansdo *sd)
{
	unsigned8 numb;
	int16 cnt;

	if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA) {
		numb = CAN_DATASEGM_OTHER - sd->b0.sg.ndata;
		if ( (srvfull.rembytes < numb) ||
		      (srvfull.rembytes > numb && sd->b0.sg.bit_0 != 0) ||
		      (srvfull.rembytes == numb && sd->b0.sg.bit_0 == 0) ) {
			abort_can_sdo(&srvfull.si, CAN_ABORT_SDO_DATAMISM);
			resetcanwork();
			return;
		}
		for (cnt = 0; cnt < numb; cnt++) {
			*srvfull.bufpnt = sd->bd[cnt];
			srvfull.bufpnt++;
		}
		if (sd->b0.sg.bit_0 != 0) {
			if (server_write_obd(&srvfull.si, databuf) != CAN_RETOK) {
				resetcanwork();
				return;
			}
		}
		sd->cs = CAN_SCS_SDO_DOWNSEGM_DATA;
		clear_can_data(sd->bd);
	} else {
		clear_can_data(sd->bd);
		if (srvfull.rembytes > CAN_DATASEGM_OTHER) {
			numb = CAN_DATASEGM_OTHER;
			sd->b0.sg.bit_0 = 0;
		} else {
			numb = srvfull.rembytes;
			sd->b0.sg.bit_0 = 1;
		}
		for (cnt = 0; cnt < numb; cnt++) {
			sd->bd[cnt] = *srvfull.bufpnt;
			srvfull.bufpnt++;
		}
		sd->cs = CAN_SCS_SDO_UPSEGM_DATA;
		sd->b0.sg.ndata = CAN_DATASEGM_OTHER - numb;
	}
	send_can_sdo(sd);
	if (sd->b0.sg.bit_0 == 0) {
		srvfull.rembytes -= numb;
		srvfull.toggle ^= 1;
		srvfull.timeout = 1 + CAN_TIMEOUT_SERVER / CAN_TIMERUSEC;		// 2.2.1
	} else resetcanwork();
}

static void can_server_sdo_process(canframe *cf)
{
	struct cansdo sd;

	sd.si.sdoind = srvfull.si.sdoind;
	parse_sdo(&sd, cf->data);
	if (sd.cs == CAN_CS_SDO_ABORT) resetcanwork();
	else if (sd.cs == CAN_CCS_SDO_DOWNSEGM_DATA || sd.cs == CAN_CCS_SDO_UPSEGM_DATA) {
		if (sd.b0.sg.toggle != srvfull.toggle) {
			abort_can_sdo(&srvfull.si, CAN_ABORT_SDO_TOGGLE);
			resetcanwork();
		} else process_segmented_data(&sd);
	} else {
		abort_can_sdo(&srvfull.si, CAN_ABORT_SDO_CS);
		resetcanwork();
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
	} else {
		abort_can_sdo(&sd.si, CAN_ABORT_SDO_CS);
	}
}

void can_server_sdo(canindex sdoind, canframe *cf)
{
	contcan_lock();
	if (srvfull.busy >= 0 && srvfull.si.sdoind == sdoind) {
		can_server_sdo_process(cf);
		contcan_unlock();
	} else {
		contcan_unlock();
		can_server_sdo_init(sdoind, cf);
	}
}

void can_init_server(void)
{
 	sem_resetcan = 0;
 	flag_resetcan = 0;
	resetcanwork();
 	sem_resetcan = -1;
}
