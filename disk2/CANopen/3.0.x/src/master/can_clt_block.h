static void sdo_client_down_block(struct sdocltappl *ca)
{
	unsigned8 numb, nblk, lbf, srvcrc;
	unsigned32 cnt;
	unsigned16 retransmit;
	int16 fnr;
	canbyte *datapnt;
	struct sdoclttrans ct;

	ct.sd.si = ca->si;
	ct.sd.cs = CAN_CCS_SDO_DOWNBLOCK;
	ct.adjcs = CAN_SCS_SDO_DOWNBLOCK;
	ct.sd.b0.bl.crc = 1;
	ct.sd.b0.bl.ds = 1;
	ct.sd.b0.bl.sub = CAN_SDOSUB_INIT;
	clear_can_data(ct.sd.bd);
	u32_to_canframe(ca->datasize, ct.sd.bd);
	can_client_basic(&ct);
	ct.blksize = ct.sd.bd[0];
	if (ct.ss.state != CAN_TRANSTATE_OK) ca->ss = ct.ss;
	else if (ct.sd.si.index != ca->si.index || ct.sd.si.subind != ca->si.subind) {
		ca->ss.state = CAN_TRANSTATE_SDO_MPX;
	} else if (ct.sd.b0.bl.sub != CAN_SDOSUB_INIT) {
		ca->ss.state = CAN_TRANSTATE_SDO_SUB;
	} else if (ct.blksize < CAN_BLOCK_SIZE_MIN || ct.blksize > CAN_BLOCK_SIZE_MAX) {
		abort_can_sdo(&ca->si, CAN_ABORT_SDO_BLKSIZE);
		ca->ss.state = CAN_TRANSTATE_SDO_BLKSIZE;
	}
	if (ca->ss.state != CAN_TRANSTATE_OK) return;
	numb = 0;
	srvcrc = ct.sd.b0.bl.crc;
	datapnt = ca->datapnt;
	retransmit = 0;
	ct.rembytes = ca->datasize;
	while (ct.rembytes > 0) {
		ct.sd.si.sdoind = ca->si.sdoind;
		ct.sd.b0.bl.ds = 0;
		ct.bufpnt = datapnt;
		ct.sd.b0.bl.lf = 0;
		ct.sd.b0.bl.crc = CAN_DATASEGM_OTHER;
		if (ct.rembytes > (unsigned32)(CAN_DATASEGM_OTHER * ct.blksize)) {
			lbf = 0;
			nblk = ct.blksize-1;
		} else {
			lbf = 1;
			nblk = (unsigned8)(ct.rembytes / CAN_DATASEGM_OTHER);
			numb = (unsigned8)(ct.rembytes % CAN_DATASEGM_OTHER);
			if (numb == 0) {
				nblk--;
				numb = CAN_DATASEGM_OTHER;
			}
		}
		for (cnt = 0; cnt < nblk; cnt++) {
			ct.sd.b0.bl.ds++;
			fnr = can_client_send_block_frame(&ct);
			if (fnr != CAN_RETOK) {
				if (fnr == CAN_ERRET_SDO_INVALID) ct.ss.state = CAN_TRANSTATE_SDO_INVALID;
				else ct.ss.state = CAN_TRANSTATE_SDO_WRITERR;
				return;
			}
		}
		if (lbf) {
			ct.sd.b0.bl.lf = 1;
			ct.sd.b0.bl.crc = numb;
		}
		nblk++;
		ct.sd.b0.bl.ds++;
		ct.sd.cs = CAN_CCS_SDO_SPECIAL_DOWN;
		ct.adjcs = CAN_SCS_SDO_DOWNBLOCK;
		can_client_basic(&ct);
		ct.blksize = ct.sd.bd[1];
		if (ct.ss.state != CAN_TRANSTATE_OK) ca->ss = ct.ss;
		else if (ct.sd.b0.bl.sub != CAN_SDOSUB_LOAD) {
			ca->ss.state = CAN_TRANSTATE_SDO_SUB;
		} else if (ct.sd.bd[0] > nblk) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_SEQNO);
			ca->ss.state = CAN_TRANSTATE_SDO_SEQNO;
		} else if (ct.sd.bd[0] < nblk) {
			retransmit++;
			if (retransmit > CAN_BLOCK_RETRANSMIT) {
				ca->ss.state = CAN_TRANSTATE_SDO_RETRANSMIT;
			}
		} else if (ct.blksize < CAN_BLOCK_SIZE_MIN || ct.blksize > CAN_BLOCK_SIZE_MAX) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_BLKSIZE);
			ca->ss.state = CAN_TRANSTATE_SDO_BLKSIZE;
		}
		if (ca->ss.state != CAN_TRANSTATE_OK) return;
		cnt = CAN_DATASEGM_OTHER * ct.sd.bd[0];
		if (cnt >= ct.rembytes) break;
		ct.rembytes -= cnt;
		datapnt += cnt;
	}
	ct.sd.si.sdoind = ca->si.sdoind;
	ct.sd.si.index = 0;
	ct.sd.si.subind = 0;
	ct.sd.cs = CAN_CCS_SDO_DOWNBLOCK;
	ct.adjcs = CAN_SCS_SDO_DOWNBLOCK;
	ct.sd.b0.bl.ds = CAN_DATASEGM_OTHER - numb;
	ct.sd.b0.bl.sub = CAN_SDOSUB_END;
	clear_can_data(ct.sd.bd);
	if (srvcrc != 0) {
		datapnt = ca->datapnt;
		can_start_crc(0);
		for (cnt = 0; cnt < ca->datasize; cnt++) {
			can_calc_crc(*datapnt);
			datapnt++;
		}
		can_calc_crc(0);
		ct.sd.si.index = can_calc_crc(0);
	}
	can_client_basic(&ct);
	if (ct.ss.state != CAN_TRANSTATE_OK) ca->ss = ct.ss;
	else if (ct.sd.b0.bl.sub != CAN_SDOSUB_END) ca->ss.state = CAN_TRANSTATE_SDO_SUB;
}

static void sdo_client_up_block(struct sdocltappl *ca)
{
	unsigned8 srvcrc;
	unsigned32 cnt;
	unsigned16 retransmit;
	int16 fnr;
	struct sdoclttrans ct;
	canlink canid;
	canframe cf;

	ct.sd.si = ca->si;
	ct.sd.cs = CAN_CCS_SDO_UPBLOCK;
	ct.adjcs = CAN_SCS_SDO_UPBLOCK;
	ct.sd.b0.bl.crc = 1;
	ct.sd.b0.bl.ds = 1;
	ct.sd.b0.bl.sub = CAN_SDOSUB_INIT;
	clear_can_data(ct.sd.bd);
	ct.sd.bd[0] = CAN_BLOCK_SIZE_MAX;
	can_client_basic(&ct);
	if (ct.ss.state != CAN_TRANSTATE_OK) ca->ss = ct.ss;
	else if (ct.sd.si.index != ca->si.index || ct.sd.si.subind != ca->si.subind) {
		ca->ss.state = CAN_TRANSTATE_SDO_MPX;
	} else if (ct.sd.b0.bl.sub != CAN_SDOSUB_INIT) {
		ca->ss.state = CAN_TRANSTATE_SDO_SUB;
	} else if (ct.sd.b0.bl.ds != 0) {
		if (ca->datasize < canframe_to_u32(ct.sd.bd)) {
			ca->ss.state = CAN_TRANSTATE_SDO_OBJSIZE;
		} else ca->datasize = canframe_to_u32(ct.sd.bd);
	}
	if (ca->ss.state != CAN_TRANSTATE_OK) return;
	ct.blksize = CAN_BLOCK_SIZE_MAX;
	srvcrc = ct.sd.b0.bl.crc;
	ct.bufpnt = ca->datapnt;
	clear_can_data(ct.sd.bd);
	ct.sd.b0.bl.sub = CAN_SDOSUB_START;
	ct.sd.b0.bl.lf = 0;
	retransmit = 0;
	ct.rembytes = ca->datasize;
	while (ct.rembytes > 0) {
		ct.sd.si.sdoind = ca->si.sdoind;
		ct.sd.b0.bl.ds = 0;
		ct.sd.cs = CAN_CCS_SDO_SPECIAL_UP;
		can_client_basic(&ct);
		if (ct.ss.state != CAN_TRANSTATE_OK) ca->ss = ct.ss;
		else if (ct.sd.b0.bl.ds > ct.blksize) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_SEQNO);
			ca->ss.state = CAN_TRANSTATE_SDO_SEQNO;
		}
		if (ca->ss.state != CAN_TRANSTATE_OK) return;
		if (ct.sd.b0.bl.ds < ct.blksize) {
			retransmit++;
			if (retransmit > CAN_BLOCK_RETRANSMIT) {
				ca->ss.state = CAN_TRANSTATE_SDO_RETRANSMIT;
				return;
			}
			ct.blksize -= (ct.blksize - ct.sd.b0.bl.ds) / 2;
		}
		ct.sd.b0.bl.sub = CAN_SDOSUB_LOAD;
		ct.sd.bd[0] = ct.sd.b0.bl.ds;
		ct.sd.bd[1] = ct.blksize;
		if (ct.rembytes <= CAN_DATASEGM_OTHER) break;
	}
	ct.sd.si.index = 0;
	ct.sd.si.subind = 0;
	ct.sd.cs = CAN_CCS_SDO_UPBLOCK;
	ct.adjcs = CAN_SCS_SDO_UPBLOCK;
	can_client_basic(&ct);
	if (ct.ss.state != CAN_TRANSTATE_OK) ca->ss = ct.ss;
	else if (ct.sd.b0.bl.sub != CAN_SDOSUB_END) ca->ss.state = CAN_TRANSTATE_SDO_SUB;
	else if (ct.rembytes != (unsigned32)(CAN_DATASEGM_OTHER - ct.sd.b0.bl.ds)) {
		ca->ss.state = CAN_TRANSTATE_SDO_DATASIZE;
	}
	if (ca->ss.state != CAN_TRANSTATE_OK) return;
	if (srvcrc != 0) {
		ct.bufpnt = ca->datapnt;
		can_start_crc(0);
		for (cnt = 0; cnt < ca->datasize; cnt++) {
			can_calc_crc(*ct.bufpnt);
			ct.bufpnt++;
		}
		can_calc_crc((ct.sd.si.index >> 8) & 0xFF);		// 2.3.2 Byte-order independent code
		if (can_calc_crc(ct.sd.si.index & 0xFF) != 0) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_CRC);
			ca->ss.state = CAN_TRANSTATE_SDO_CRC;
			return;
		}
	}
	CLEAR_FRAME(&cf);
	fnr = find_sdo_client_send_canid(ca->si.sdoind, &canid);
	if (fnr == CAN_RETOK) {
		cf.id = canid;
		cf.data[0] = (CAN_CCS_SDO_UPBLOCK << 5) | CAN_SDOSUB_END;
		cf.len = CAN_DATALEN_SDO;
		fnr = send_can_data(&cf);
	}
	if (fnr != CAN_RETOK) {
		if (fnr == CAN_ERRET_SDO_INVALID) ct.ss.state = CAN_TRANSTATE_SDO_INVALID;
		else ct.ss.state = CAN_TRANSTATE_SDO_WRITERR;
	}
}
