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
		can_server_control();
		flag_resetcan--;
	}
}

static int16 server_read_obd(struct sdoixs *si, canbyte *data)		// 3.0.1 some changes
{
	int16 fnr;
	unsigned32 abortcode;

	fnr = server_read_obd_network(si->index, si->subind, data);
	if (fnr == CAN_RETOK) return CAN_RETOK;
	if (fnr == CAN_ERRET_OBD_WRITEONLY) abortcode = CAN_ABORT_SDO_WRITEONLY;
	else if (fnr == CAN_ERRET_OBD_NODATA) abortcode = CAN_ABORT_SDO_NODATA;
	else if (fnr == CAN_ERRET_OBD_INTINCOMP) abortcode = CAN_ABORT_SDO_INTINCOMP;	// 2.2.1
	else abortcode = CAN_ABORT_SDO_ERROR;	// 2.2.1
	abort_can_sdo(si, abortcode);
	return fnr;
}

static int16 server_write_obd(struct sdoixs *si, canbyte *data)		// 3.0.1 some changes
{
	int16 fnr;
	unsigned32 abortcode;

	fnr = server_write_obd_network(si->index, si->subind, data);
	if (fnr == CAN_RETOK) return CAN_RETOK;
	if (fnr == CAN_ERRET_OBD_READONLY) abortcode = CAN_ABORT_SDO_READONLY;
	else if (fnr == CAN_ERRET_OBD_VALRANGE) abortcode = CAN_ABORT_SDO_VALRANGE;
	else if (fnr == CAN_ERRET_OBD_OBJACCESS) abortcode = CAN_ABORT_SDO_OBJACCESS;
	else if (fnr == CAN_ERRET_OBD_PARINCOMP) abortcode = CAN_ABORT_SDO_PARINCOMP;
	else if (fnr == CAN_ERRET_OBD_DEVSTATE) abortcode = CAN_ABORT_SDO_TRAPDS;
	else if (fnr == CAN_ERRET_PDO_NOMAP) abortcode = CAN_ABORT_SDO_NOPDOMAP;
	else if (fnr == CAN_ERRET_PDO_ERRMAP) abortcode = CAN_ABORT_SDO_ERRPDOMAP;
	else if (fnr == CAN_ERRET_OUTOFMEM) abortcode = CAN_ABORT_SDO_OUTOFMEM;
	else if (fnr >= CAN_ERRET_FLASH_MIN && fnr <= CAN_ERRET_FLASH_MAX) abortcode = CAN_ABORT_SDO_HARDWARE;    // 3.0.3
	else abortcode = CAN_ABORT_SDO_TRAPPL;
	abort_can_sdo(si, abortcode);
	return fnr;
}

static void sdo_server_expedited_download(struct cansdo *sd, int32 size)
{
	if (size > CAN_DATASEGM_EXPEDITED ||
   	   (sd->b0.sg.bit_0 != 0 && size != CAN_DATASEGM_EXPEDITED - sd->b0.sg.ndata)) {
		abort_can_sdo(&sd->si, CAN_ABORT_SDO_DATAMISM);
		return;
	}
	if (server_write_obd(&sd->si, sd->bd) == CAN_RETOK) {
		sd->cs = CAN_SCS_SDO_DOWNLOAD_INIT;
		clear_can_data(sd->bd);
		send_can_sdo(sd);
	}
}

static void sdo_server_expedited_upload(struct cansdo *sd, int32 size)
{
	clear_can_data(sd->bd);
	if (server_read_obd(&sd->si, sd->bd) != CAN_RETOK) return;
	sd->cs = CAN_SCS_SDO_UPLOAD_INIT;
	sd->b0.sg.bit_0 = 1;
	sd->b0.sg.bit_1 = 1;
	sd->b0.sg.ndata = (unsigned8)(CAN_DATASEGM_EXPEDITED - size);
	send_can_sdo(sd);
}
