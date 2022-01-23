#include <can_header.h>

#if CHECK_VERSION(3, 0, 1)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 0)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 0)

void parse_sdo(struct cansdo *sd, canbyte *data)
{
	int16 mode;

	sd->si.index = 0;
	sd->si.subind = 0;
	clear_can_data(sd->bd);
	mode = 0;
	sd->cs = (*data >> 5) & CAN_MASK_SDO_CS;
	sd->b0.sg.ndata = 0;
	sd->b0.sg.bit_0 = 0;
	sd->b0.sg.bit_1 = 0;
	sd->b0.sg.toggle = 0;
#if CAN_APPLICATION_MODE == MASTER
	if (sd->cs == CAN_SCS_SDO_UPLOAD_INIT) mode = 1;
	else if (sd->cs == CAN_SCS_SDO_UPSEGM_DATA) mode = 2;
	else if (sd->cs == CAN_SCS_SDO_DOWNSEGM_DATA) mode = 3;
	else if (sd->cs == CAN_SCS_SDO_UPBLOCK) mode = 4;
	else if (sd->cs == CAN_SCS_SDO_DOWNBLOCK) mode = 5;
#elif CAN_APPLICATION_MODE == SLAVE
	if (sd->cs == CAN_CCS_SDO_DOWNLOAD_INIT) mode = 1;
	else if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA) mode = 2;
	else if (sd->cs == CAN_CCS_SDO_UPSEGM_DATA) mode = 3;
	else if (sd->cs == CAN_CCS_SDO_DOWNBLOCK) mode = 4;
	else if (sd->cs == CAN_CCS_SDO_UPBLOCK) mode = 5;
#elif CAN_APPLICATION_MODE == TEST
	if (sd->si.sdoind >= CAN_INDEX_CLIENT_SDO_MIN && sd->si.sdoind <= CAN_INDEX_CLIENT_SDO_MAX) {
		if (sd->cs == CAN_SCS_SDO_UPLOAD_INIT) mode = 1;
		else if (sd->cs == CAN_SCS_SDO_UPSEGM_DATA) mode = 2;
		else if (sd->cs == CAN_SCS_SDO_DOWNSEGM_DATA) mode = 3;
		else if (sd->cs == CAN_SCS_SDO_UPBLOCK) mode = 4;
		else if (sd->cs == CAN_SCS_SDO_DOWNBLOCK) mode = 5;
	} else {
		if (sd->cs == CAN_CCS_SDO_DOWNLOAD_INIT) mode = 1;
		else if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA) mode = 2;
		else if (sd->cs == CAN_CCS_SDO_UPSEGM_DATA) mode = 3;
		else if (sd->cs == CAN_CCS_SDO_DOWNBLOCK) mode = 4;
		else if (sd->cs == CAN_CCS_SDO_UPBLOCK) mode = 5;
	}
#endif
	if (mode == 1) {
		sd->b0.sg.bit_1 = (*data >> 1) & 01;
		sd->b0.sg.bit_0 = *data & 01;
		if (sd->b0.sg.bit_0 != 0) sd->b0.sg.ndata = (*data >> 2) & 03;
	} else if (mode == 2) {
		sd->b0.sg.bit_0 = *data & 01;
		sd->b0.sg.ndata = (*data >> 1) & 07;
		sd->b0.sg.toggle = (*data >> 4) & 01;
	} else if (mode == 3) {
		sd->b0.sg.toggle = (*data >> 4) & 01;
	}
#if CAN_PROTOCOL_BLOCK == TRUE
	if (mode == 4) {
		sd->b0.bl.sub = *data & 01;
		if (sd->b0.bl.sub == CAN_SDOSUB_INIT) {
			sd->b0.bl.crc = (*data >> 2) & 01;
			sd->b0.bl.ds = (*data >> 1) & 01;
		} else if (sd->b0.bl.sub == CAN_SDOSUB_END) {
			sd->b0.bl.ds = (*data >> 2) & 07;
		}
	} else if (mode == 5) {
		sd->b0.bl.sub = *data & 03;
		if (sd->b0.bl.sub == CAN_SDOSUB_INIT) {
			sd->b0.bl.crc = (*data >> 2) & 01;
		}
	}
#endif
	data++;
	mode = 1;
#if CAN_APPLICATION_MODE == MASTER
	if (sd->cs == CAN_SCS_SDO_DOWNSEGM_DATA || sd->cs == CAN_SCS_SDO_UPSEGM_DATA) mode = 2;
	else if (sd->cs == CAN_SCS_SDO_DOWNBLOCK) {
		if (sd->b0.bl.sub != CAN_SDOSUB_INIT) mode = 2;
	}
#elif CAN_APPLICATION_MODE == SLAVE
	if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA || sd->cs == CAN_CCS_SDO_UPSEGM_DATA) mode = 2;
	else if (sd->cs == CAN_CCS_SDO_UPBLOCK) {
		if (sd->b0.bl.sub != CAN_SDOSUB_INIT) mode = 2;
	}
#elif CAN_APPLICATION_MODE == TEST
	if (sd->si.sdoind >= CAN_INDEX_CLIENT_SDO_MIN && sd->si.sdoind <= CAN_INDEX_CLIENT_SDO_MAX) {
		if (sd->cs == CAN_SCS_SDO_DOWNSEGM_DATA || sd->cs == CAN_SCS_SDO_UPSEGM_DATA) mode = 2;
		else if (sd->cs == CAN_SCS_SDO_DOWNBLOCK) {
			if (sd->b0.bl.sub != CAN_SDOSUB_INIT) mode = 2;
		}
	} else {
		if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA || sd->cs == CAN_CCS_SDO_UPSEGM_DATA) mode = 2;
		else if (sd->cs == CAN_CCS_SDO_UPBLOCK) {
			if (sd->b0.bl.sub != CAN_SDOSUB_INIT) mode = 2;
		}
	}
#endif
	if (mode == 1) {
		sd->si.index = canframe_to_u16(data);
		data++; data++;
		sd->si.subind = *data; data++;
	}
	sd->bd[0] = *data; data++;
	sd->bd[1] = *data; data++;
	sd->bd[2] = *data; data++;
	sd->bd[3] = *data;
	if (mode == 2) {
		data++;
		sd->bd[4] = *data; data++;
		sd->bd[5] = *data; data++;
		sd->bd[6] = *data;
	}
}

void receive_can_sdo(canindex sdoind, canframe *cf)
{
#if CAN_APPLICATION_MODE == MASTER
	can_client_sdo(sdoind, cf);
#elif CAN_APPLICATION_MODE == SLAVE
	can_server_sdo(sdoind, cf);
#elif CAN_APPLICATION_MODE == TEST
	if (sdoind >= CAN_INDEX_CLIENT_SDO_MIN && sdoind <= CAN_INDEX_CLIENT_SDO_MAX) {
		can_client_sdo(sdoind, cf);
	} else {
		can_server_sdo(sdoind, cf);
	}
#endif
}

static void assemble_sdo(struct cansdo *sd, canbyte *data)
{
	int16 mode;

	mode = 0;
	*data = (sd->cs & CAN_MASK_SDO_CS) << 5;
#if CAN_APPLICATION_MODE == MASTER
	if (sd->cs == CAN_CCS_SDO_DOWNLOAD_INIT) mode = 1;
	else if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA) mode = 2;
	else if (sd->cs == CAN_CCS_SDO_UPSEGM_DATA) mode = 3;
	else if (sd->cs == CAN_CCS_SDO_DOWNBLOCK) mode = 4;
	else if (sd->cs == CAN_CCS_SDO_UPBLOCK) mode = 5;
#elif CAN_APPLICATION_MODE == SLAVE
	if (sd->cs == CAN_SCS_SDO_UPLOAD_INIT) mode = 1;
	else if (sd->cs == CAN_SCS_SDO_UPSEGM_DATA) mode = 2;
	else if (sd->cs == CAN_SCS_SDO_DOWNSEGM_DATA) mode = 3;
	else if (sd->cs == CAN_SCS_SDO_UPBLOCK) mode = 4;
	else if (sd->cs == CAN_SCS_SDO_DOWNBLOCK) mode = 5;
#elif CAN_APPLICATION_MODE == TEST
	if (sd->si.sdoind >= CAN_INDEX_CLIENT_SDO_MIN && sd->si.sdoind <= CAN_INDEX_CLIENT_SDO_MAX) {
		if (sd->cs == CAN_CCS_SDO_DOWNLOAD_INIT) mode = 1;
		else if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA) mode = 2;
		else if (sd->cs == CAN_CCS_SDO_UPSEGM_DATA) mode = 3;
		else if (sd->cs == CAN_CCS_SDO_DOWNBLOCK) mode = 4;
		else if (sd->cs == CAN_CCS_SDO_UPBLOCK) mode = 5;
	} else {
		if (sd->cs == CAN_SCS_SDO_UPLOAD_INIT) mode = 1;
		else if (sd->cs == CAN_SCS_SDO_UPSEGM_DATA) mode = 2;
		else if (sd->cs == CAN_SCS_SDO_DOWNSEGM_DATA) mode = 3;
		else if (sd->cs == CAN_SCS_SDO_UPBLOCK) mode = 4;
		else if (sd->cs == CAN_SCS_SDO_DOWNBLOCK) mode = 5;
	}
#endif
	if (mode == 1) *data |= ((sd->b0.sg.ndata & 03) << 2) | ((sd->b0.sg.bit_1 & 01) << 1) | (sd->b0.sg.bit_0 & 01);
	else if (mode == 2) *data |= ((sd->b0.sg.toggle & 01) << 4) | ((sd->b0.sg.ndata & 07) << 1) | (sd->b0.sg.bit_0 & 01);
	else if (mode == 3) *data |= (sd->b0.sg.toggle & 01) << 4;
#if CAN_PROTOCOL_BLOCK == TRUE
	if (mode == 4) {
		*data |= sd->b0.bl.sub & 01;
		if (sd->b0.bl.sub == CAN_SDOSUB_INIT) {
			*data |= ((sd->b0.bl.crc & 01) << 2) | ((sd->b0.bl.ds & 01) << 1);
		} else if (sd->b0.bl.sub == CAN_SDOSUB_END) {
			*data |= (sd->b0.bl.ds & 07) << 2;
		}
	} else if (mode == 5) {
		*data |= sd->b0.bl.sub & 03;
		if (sd->b0.bl.sub == CAN_SDOSUB_INIT) *data |= (sd->b0.bl.crc & 01) << 2;
	}
#endif
	data++;
	mode = 1;
#if CAN_APPLICATION_MODE == MASTER
	if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA || sd->cs == CAN_CCS_SDO_UPSEGM_DATA) mode = 2;
	else if (sd->cs == CAN_CCS_SDO_UPBLOCK) {
		if (sd->b0.bl.sub != CAN_SDOSUB_INIT) mode = 2;
	}
#elif CAN_APPLICATION_MODE == SLAVE
	if (sd->cs == CAN_SCS_SDO_DOWNSEGM_DATA || sd->cs == CAN_SCS_SDO_UPSEGM_DATA) mode = 2;
	else if (sd->cs == CAN_SCS_SDO_DOWNBLOCK) {
		if (sd->b0.bl.sub != CAN_SDOSUB_INIT) mode = 2;
	}
#elif CAN_APPLICATION_MODE == TEST
	if (sd->si.sdoind >= CAN_INDEX_CLIENT_SDO_MIN && sd->si.sdoind <= CAN_INDEX_CLIENT_SDO_MAX) {
		if (sd->cs == CAN_CCS_SDO_DOWNSEGM_DATA || sd->cs == CAN_CCS_SDO_UPSEGM_DATA) mode = 2;
		else if (sd->cs == CAN_CCS_SDO_UPBLOCK) {
			if (sd->b0.bl.sub != CAN_SDOSUB_INIT) mode = 2;
		}
	} else {
		if (sd->cs == CAN_SCS_SDO_DOWNSEGM_DATA || sd->cs == CAN_SCS_SDO_UPSEGM_DATA) mode = 2;
		else if (sd->cs == CAN_SCS_SDO_DOWNBLOCK) {
			if (sd->b0.bl.sub != CAN_SDOSUB_INIT) mode = 2;
		}
	}
#endif
	if (mode == 1) {
		u16_to_canframe(sd->si.index, data);
		data++; data++;
		*data = sd->si.subind; data++;
	}
	*data = sd->bd[0]; data++;
	*data = sd->bd[1]; data++;
	*data = sd->bd[2]; data++;
	*data = sd->bd[3];
	if (mode == 2) {
		data++;
		*data = sd->bd[4]; data++;
		*data = sd->bd[5]; data++;
		*data = sd->bd[6];
	}
}

int16 send_can_sdo(struct cansdo *sd)
{
	int16 fnr;
	canlink canid;
	canframe cf;

	CLEAR_FRAME(&cf);
	#if CAN_APPLICATION_MODE == MASTER
	fnr = find_sdo_client_send_canid(sd->si.sdoind, &canid);
	#elif CAN_APPLICATION_MODE == SLAVE
	fnr = find_sdo_server_send_canid(sd->si.sdoind, &canid);
	#elif CAN_APPLICATION_MODE == TEST
	if (sd->si.sdoind >= CAN_INDEX_CLIENT_SDO_MIN && sd->si.sdoind <= CAN_INDEX_CLIENT_SDO_MAX) {
		fnr = find_sdo_client_send_canid(sd->si.sdoind, &canid);
	} else {
		fnr = find_sdo_server_send_canid(sd->si.sdoind, &canid);
	}
	#endif
	if (fnr != CAN_RETOK) return fnr;
	cf.id = canid;
	assemble_sdo(sd, cf.data);
	cf.len = CAN_DATALEN_SDO;
	return send_can_data(&cf);
}

void abort_can_sdo(struct sdoixs *si, unsigned32 abortcode)
{
	struct cansdo sd;

	sd.cs = CAN_CS_SDO_ABORT;
	sd.si = *si;
	u32_to_canframe(abortcode, sd.bd);
	send_can_sdo(&sd);
}

#endif
