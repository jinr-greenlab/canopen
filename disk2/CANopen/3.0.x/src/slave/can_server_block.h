static int16 sem_upblock;

static void can_server_sdo_block_init(struct cansdo *sd, int32 size)
{
	unsigned16 cnt;
	canbyte blsiz;

	if (sd->b0.bl.sub != CAN_SDOSUB_INIT) {
		abort_can_sdo(&sd->si, CAN_ABORT_SDO_ERROR);
		return;
	}
	blsiz = 0;
	if (sd->cs == CAN_CCS_SDO_UPBLOCK) {
		blsiz = sd->bd[0];
		if (blsiz < CAN_BLOCK_SIZE_MIN || blsiz > CAN_BLOCK_SIZE_MAX) {
			abort_can_sdo(&sd->si, CAN_ABORT_SDO_BLKSIZE);
			return;
		}
		sd->cs = CAN_SCS_SDO_UPBLOCK;
		sd->b0.bl.ds = 1;
		u32_to_canframe(size, sd->bd);
	} else {
		if (sd->b0.bl.ds != 0) {
			if ((unsigned32)size < canframe_to_u32(sd->bd)) {
				abort_can_sdo(&sd->si, CAN_ABORT_SDO_DATAMISM);
				return;
			} else size = canframe_to_u32(sd->bd);
  		}
		sd->cs = CAN_SCS_SDO_DOWNBLOCK;
		clear_can_data(sd->bd);
		sd->bd[0] = CAN_BLOCK_SIZE_MAX;
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
					srvfull[cnt].bufbeg = server_get_object_pointer(sd->si.index, sd->si.subind);
					if (srvfull[cnt].bufbeg == NULL) {
						abort_can_sdo(&sd->si, CAN_ABORT_SDO_OUTOFMEM);
						resetcanwork(srvfull + cnt);
						contcan_unlock();
						return;
					}
					srvfull[cnt].dynamem = FALSE;
				} else srvfull[cnt].dynamem = TRUE;
				srvfull[cnt].bufpnt = srvfull[cnt].bufbeg;
				srvfull[cnt].si = sd->si;
				srvfull[cnt].totbytes = size;
				srvfull[cnt].rembytes = size;
				srvfull[cnt].crc = sd->b0.bl.crc;
				srvfull[cnt].seq = 0;
				sd->b0.bl.crc = 1;
				if (sd->cs == CAN_SCS_SDO_UPBLOCK) {
					if (srvfull[cnt].dynamem == TRUE) {
						if (server_read_obd(&srvfull[cnt].si, srvfull[cnt].bufbeg) != CAN_RETOK) {
							resetcanwork(srvfull + cnt);
							contcan_unlock();
							return;
						}
					}
					srvfull[cnt].blksize = blsiz;
					srvfull[cnt].sub = CAN_SDOSUB_START;
				} else {
					srvfull[cnt].blksize = CAN_BLOCK_SIZE_MAX;
					srvfull[cnt].sub = CAN_BLMODE_DOWNBLOCK;
				}
				send_can_sdo(sd);
				contcan_unlock();
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

static void send_server_download_acq(struct sdosrvfull *sr)
{
	struct cansdo sd;

	sd.si = sr->si;
	sd.cs = CAN_SCS_SDO_DOWNBLOCK;
	sd.b0.bl.sub = CAN_SDOSUB_LOAD;
	clear_can_data(sd.bd);
	sd.bd[0] = sr->seq;
	sd.bd[1] = sr->blksize;
	send_can_sdo(&sd);
	sr->toggle = 0;
	sr->seq = 0;
}

static void can_server_sdo_downblock(struct sdosrvfull *sr, canframe *cf)
{
	unsigned16 cnt;

	if (sr->toggle != 0) {
		if ( (cf->data[0] & CAN_MASK_SDO_SEQNO) == sr->blksize ||
		      (cf->data[0] & CAN_MASK_SDO_BLAST) != 0 ) {
			sr->blksize -= (sr->blksize - sr->seq) / 2;
			send_server_download_acq(sr);
		}
	} else if ((cf->data[0] & CAN_MASK_SDO_SEQNO) != 1+sr->seq) {
		sr->toggle = 1;
	} else if ((cf->data[0] & CAN_MASK_SDO_BLAST) != 0) {
		if (sr->rembytes > CAN_DATASEGM_OTHER) {
			resetcanwork(sr);
			return;
		}
		for (cnt = 1; cnt <= sr->rembytes; cnt++) {
			*sr->bufpnt = cf->data[cnt];
			sr->bufpnt++;
		}
		sr->seq++;
		send_server_download_acq(sr);
		sr->sub = CAN_SDOSUB_END;
	} else {
		if (sr->rembytes <= CAN_DATASEGM_OTHER) {
			resetcanwork(sr);
			return;
		} else sr->rembytes -= CAN_DATASEGM_OTHER;
		for (cnt = 1; cnt <= CAN_DATASEGM_OTHER; cnt++) {
			*sr->bufpnt = cf->data[cnt];
			sr->bufpnt++;
		}
		sr->seq++;
		if (sr->seq == sr->blksize) send_server_download_acq(sr);
	}
	sr->timeout = 1 + CAN_TIMEOUT_SERVER / CAN_TIMERUSEC;		// 2.2.1
}

static void can_server_sdo_downblock_end(struct sdosrvfull *sr, struct cansdo *sd)
{
	unsigned32 cnt;

	if (sd->b0.bl.sub != CAN_SDOSUB_END) {
		abort_can_sdo(&sr->si, CAN_ABORT_SDO_ERROR);
		resetcanwork(sr);
		return;
	}
	if (sr->rembytes != (unsigned32)(CAN_DATASEGM_OTHER - sd->b0.bl.ds)) {
		abort_can_sdo(&sr->si, CAN_ABORT_SDO_DATAMISM);
		resetcanwork(sr);
		return;
	}
	if (sr->crc != 0) {
		sr->bufpnt = sr->bufbeg;
		can_start_crc(0);
		for (cnt = 0; cnt < sr->totbytes; cnt++) {
			can_calc_crc(*sr->bufpnt);
			sr->bufpnt++;
		}
		can_calc_crc((sd->si.index >> 8) & 0xFF);		// 2.3.2 Byte-order independent code
		if (can_calc_crc(sd->si.index & 0xFF) != 0) {
			abort_can_sdo(&sr->si, CAN_ABORT_SDO_CRC);
			resetcanwork(sr);
			return;
		}
	}
	if (sr->dynamem == TRUE) {
		if (server_write_obd(&sr->si, sr->bufbeg) != CAN_RETOK) {
			resetcanwork(sr);
			return;
		}
	}
	sd->cs = CAN_SCS_SDO_DOWNBLOCK;
	clear_can_data(sd->bd);
	send_can_sdo(sd);
	resetcanwork(sr);
}

static void upload_block(struct sdosrvfull *sr)
{
	unsigned16 cnt, c1;
	unsigned8 nblk, numb;
	canbyte *datapnt;
	canlink canid;
	canframe cf;

	if (find_sdo_server_send_canid(sr->si.sdoind, &canid) != CAN_RETOK) {		// 2.2.1
		resetcanwork(sr);
		return;
	}
	CLEAR_FRAME(&cf);
	cf.id = canid;
	cf.len = CAN_DATALEN_SDO;
	datapnt = sr->bufpnt;
	sr->seq = 0;
	if (sr->rembytes > (unsigned32)(CAN_DATASEGM_OTHER * sr->blksize)) {
		nblk = sr->blksize;
		numb = 0;
	} else {
		nblk = (unsigned8)(sr->rembytes / CAN_DATASEGM_OTHER);
		numb = (unsigned8)(sr->rembytes % CAN_DATASEGM_OTHER);
		if (numb == 0) {
			nblk--;
			numb = CAN_DATASEGM_OTHER;
		}
	}
	for (cnt = 0; cnt < nblk; cnt++) {
		sr->seq++;
		cf.data[0] = sr->seq;
		for (c1 = 1; c1 <= CAN_DATASEGM_OTHER; c1++) {
			cf.data[c1] = *datapnt;
			datapnt++;
		}
		send_can_data(&cf);
		sr->timeout = 1 + CAN_TIMEOUT_SERVER / CAN_TIMERUSEC;		// 2.2.1
	}
	if (numb != 0) {
		sr->seq++;
		clear_can_data(cf.data);
		cf.data[0] = sr->seq | CAN_MASK_SDO_BLAST;
		for (c1 = 1; c1 <= numb; c1++) {
			cf.data[c1] = *datapnt;
			datapnt++;
		}
		send_can_data(&cf);
		sr->timeout = 1 + CAN_TIMEOUT_SERVER / CAN_TIMERUSEC;		// 2.2.1
	}
	sr->sub = CAN_SDOSUB_LOAD;		// 2.2.1
}

void can_server_upload_block(void)
{
	unsigned16 cnt;

	CAN_CRITICAL_BEGIN
	sem_upblock++;
	if (sem_upblock == 0) {
		CAN_CRITICAL_END
		for (cnt = 0; cnt < CAN_SIZE_SRVFULL; cnt++) {
			if (srvfull[cnt].busy >= 0 && srvfull[cnt].sub == CAN_BLMODE_UPBLOCK) {
				upload_block(srvfull + cnt);
				break;
			}
		}
		CAN_CRITICAL_BEGIN
	}
	sem_upblock--;
	CAN_CRITICAL_END
}

static void can_server_sdo_upblock(struct sdosrvfull *sr, struct cansdo *sd)
{
	unsigned32 cnt, acqb;

	if (sd->b0.bl.sub != sr->sub) {
		abort_can_sdo(&sr->si, CAN_ABORT_SDO_ERROR);
		resetcanwork(sr);
		return;
	}
	if (sd->b0.bl.sub == CAN_SDOSUB_START) sr->sub = CAN_BLMODE_UPBLOCK;
	else if (sd->b0.bl.sub == CAN_SDOSUB_LOAD) {
		if (sd->bd[0] > sr->seq) {
			abort_can_sdo(&sr->si, CAN_ABORT_SDO_SEQNO);
			resetcanwork(sr);
			return;
		}
		acqb = CAN_DATASEGM_OTHER * sd->bd[0];
		if (acqb >= sr->rembytes) {
			sd->si.index = 0;
			sd->si.subind = 0;
			if (sr->crc != 0) {
				sr->bufpnt = sr->bufbeg;
				can_start_crc(0);
				for (cnt = 0; cnt < sr->totbytes; cnt++) {
					can_calc_crc(*sr->bufpnt);
					sr->bufpnt++;
				}
				can_calc_crc(0);
				sd->si.index = can_calc_crc(0);
			}
			sd->cs = CAN_SCS_SDO_UPBLOCK;
			sd->b0.bl.sub = CAN_SDOSUB_END;
			sd->b0.bl.ds = (unsigned8)(acqb - sr->rembytes);
			clear_can_data(sd->bd);
			send_can_sdo(sd);
			sr->sub = CAN_SDOSUB_END;
		} else {
			sr->rembytes -= acqb;
			sr->bufpnt += acqb;
			sr->blksize = sd->bd[1];
			if (sr->blksize < CAN_BLOCK_SIZE_MIN || sr->blksize > CAN_BLOCK_SIZE_MAX) {
				abort_can_sdo(&sr->si, CAN_ABORT_SDO_BLKSIZE);
				resetcanwork(sr);
			}
			sr->sub = CAN_BLMODE_UPBLOCK;
		}
	} else if (sd->b0.bl.sub == CAN_SDOSUB_END) resetcanwork(sr);
}
