#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 2)
//  CHECK_VERSION(2, 2, 0)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 0)

#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST

#if CAN_PROTOCOL_BLOCK == TRUE
#include "can_clt_block.h"
#endif

static void sdo_client_down_init(struct sdocltappl *ca)
{
	struct sdoclttrans ct;
	unsigned32 cnt;
	canbyte *datapnt;

	ct.sd.si = ca->si;
	ct.sd.cs = CAN_CCS_SDO_DOWNLOAD_INIT;
	ct.adjcs = CAN_SCS_SDO_DOWNLOAD_INIT;
	clear_can_data(ct.sd.bd);
	ct.sd.b0.sg.bit_0 = 1;
	if (ca->operation == CAN_SDOPER_DOWN_EXPEDITED) {
		ct.sd.b0.sg.bit_1 = 1;
		ct.sd.b0.sg.ndata = (unsigned8)(CAN_DATASEGM_EXPEDITED - ca->datasize);
		if (ca->datapnt == NULL) {
			if (node_read_manstan_objdict_network(ca->node, ca->si.index, ca->si.subind, ct.sd.bd) != CAN_RETOK) {
				ca->ss.state = CAN_TRANSTATE_OBD_READ;
				return;
			}
		} else {
			datapnt = ca->datapnt;
			for (cnt = 0; cnt < ca->datasize; cnt++) {
				ct.sd.bd[cnt] = *datapnt;
				datapnt++;
			}
		}
	} else {
		ct.sd.b0.sg.bit_1 = 0;
		ct.sd.b0.sg.ndata = 0;
		u32_to_canframe(ca->datasize, ct.sd.bd);
	}
	can_client_basic(&ct);
	if (ct.ss.state != CAN_TRANSTATE_OK) {
		ca->ss = ct.ss;
		return;
	}
	if (ct.sd.si.index != ca->si.index || ct.sd.si.subind != ca->si.subind) {
		if (ca->operation != CAN_SDOPER_DOWN_EXPEDITED) abort_can_sdo(&ca->si, CAN_ABORT_SDO_DATAMISM);
		ca->ss.state = CAN_TRANSTATE_SDO_MPX;
	}
}

static void sdo_client_up_init(struct sdocltappl *ca)
{
	struct sdoclttrans ct;
	unsigned32 cnt;
	canbyte *datapnt;

	ct.sd.si = ca->si;
	ct.sd.cs = CAN_CCS_SDO_UPLOAD_INIT;
	ct.adjcs = CAN_SCS_SDO_UPLOAD_INIT;
	clear_can_data(ct.sd.bd);
	can_client_basic(&ct);
	if (ct.ss.state != CAN_TRANSTATE_OK) {
		ca->ss = ct.ss;
		return;
	}
	if (ct.sd.si.index != ca->si.index || ct.sd.si.subind != ca->si.subind) {
		if (ca->operation != CAN_SDOPER_UP_EXPEDITED) abort_can_sdo(&ca->si, CAN_ABORT_SDO_DATAMISM);
		ca->ss.state = CAN_TRANSTATE_SDO_MPX;
		return;
	}
	if (ca->operation == CAN_SDOPER_UP_EXPEDITED) {
		if (ct.sd.b0.sg.bit_1 == 0) {
			ca->ss.state = CAN_TRANSTATE_SDO_MODE;
		} else if (ct.sd.b0.sg.bit_0 != 0 && ca->datasize != (unsigned32)(CAN_DATASEGM_EXPEDITED - ct.sd.b0.sg.ndata)) {
			ca->ss.state = CAN_TRANSTATE_SDO_OBJSIZE;
		} else {
			if (ca->datapnt == NULL) {
				if (node_write_manstan_objdict_network(ca->node, ca->si.index, ca->si.subind, ct.sd.bd) != CAN_RETOK) {
					ca->ss.state = CAN_TRANSTATE_OBD_WRITE;
				}
			} else {
				datapnt = ca->datapnt;
				for (cnt = 0; cnt < ca->datasize; cnt++) {
					*datapnt = ct.sd.bd[cnt];
					datapnt++;
				}
			}
		}
	} else {
		if (ct.sd.b0.sg.bit_1 != 0) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_DATAMISM);
			ca->ss.state = CAN_TRANSTATE_SDO_MODE;
		} else if (ct.sd.b0.sg.bit_0 != 0 && ca->datasize != canframe_to_u32(ct.sd.bd)) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_DATAMISM);
			ca->ss.state = CAN_TRANSTATE_SDO_OBJSIZE;
		}
	}
}

static void sdo_client_down_data(struct sdocltappl *ca)
{
	unsigned8 numb, toggle;
	unsigned32 cnt;
	canbyte *bufbeg, *bufpnt, *datapnt;
	struct sdoclttrans ct;

	bufbeg = can_malloc(ca->datasize);
	if (bufbeg == NULL) {
		abort_can_sdo(&ca->si,  CAN_ABORT_SDO_OUTOFMEM);
		ca->ss.state = CAN_TRANSTATE_OBD_MALLOC;
		return;
	}
	bufpnt = bufbeg;
	if (ca->datapnt == NULL) {
		if (node_read_manstan_objdict_network(ca->node, ca->si.index, ca->si.subind, bufbeg) != CAN_RETOK) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_ERROR);
			ca->ss.state = CAN_TRANSTATE_OBD_READ;
			can_free(bufbeg);
			return;
		}
	} else {
		datapnt = ca->datapnt;
		for (cnt = 0; cnt < ca->datasize; cnt++) {
			*bufpnt = *datapnt;
			bufpnt++;
			datapnt++;
		}
		bufpnt = bufbeg;
	}
	toggle = 0;
	ct.rembytes = ca->datasize;
	while (ct.rembytes > 0) {
		ct.sd.si = ca->si;
		ct.sd.cs = CAN_CCS_SDO_DOWNSEGM_DATA;
		ct.adjcs = CAN_SCS_SDO_DOWNSEGM_DATA;
		ct.sd.b0.sg.toggle = toggle;
		if (ct.rembytes > CAN_DATASEGM_OTHER) {
			ct.sd.b0.sg.bit_0 = 0;
			ct.sd.b0.sg.ndata = 0;
			numb = CAN_DATASEGM_OTHER;
			ct.rembytes -= CAN_DATASEGM_OTHER;
		} else {
			ct.sd.b0.sg.bit_0 = 1;
			ct.sd.b0.sg.ndata = (unsigned8)(CAN_DATASEGM_OTHER - ct.rembytes);
			numb = (unsigned8)ct.rembytes;
			ct.rembytes = 0;
		}
		clear_can_data(ct.sd.bd);
		for (cnt = 0; cnt < numb; cnt++) {
			ct.sd.bd[cnt] = *bufpnt;
			bufpnt++;
		}
		can_client_basic(&ct);
		if (ct.ss.state != CAN_TRANSTATE_OK) {
			ca->ss = ct.ss;
			can_free(bufbeg);
			return;
		}
		if (ct.sd.b0.sg.toggle != toggle) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_TOGGLE);
			ca->ss.state = CAN_TRANSTATE_SDO_TOGGLE;
			can_free(bufbeg);
			return;
		}
		toggle ^= 1;
	}
	can_free(bufbeg);
}

static void sdo_client_up_data(struct sdocltappl *ca)
{
	unsigned8 numb, toggle;
	unsigned32 cnt;
	canbyte *bufbeg, *bufpnt, *datapnt;
	struct sdoclttrans ct;

	bufbeg = can_malloc(ca->datasize);
	if (bufbeg == NULL) {
		abort_can_sdo(&ca->si,  CAN_ABORT_SDO_OUTOFMEM);
		ca->ss.state = CAN_TRANSTATE_OBD_MALLOC;
		return;
	}
	bufpnt = bufbeg;
	toggle = 0;
	ct.rembytes = ca->datasize;
	while (ct.rembytes > 0) {
		ct.sd.si = ca->si;
		ct.sd.cs = CAN_CCS_SDO_UPSEGM_DATA;
		ct.adjcs = CAN_SCS_SDO_UPSEGM_DATA;
		ct.sd.b0.sg.toggle = toggle;
		clear_can_data(ct.sd.bd);
		can_client_basic(&ct);
		if (ct.ss.state != CAN_TRANSTATE_OK) {
			ca->ss = ct.ss;
			can_free(bufbeg);
			return;
		}
		if (ct.sd.b0.sg.toggle != toggle) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_TOGGLE);
			ca->ss.state = CAN_TRANSTATE_SDO_TOGGLE;
			can_free(bufbeg);
			return;
		}
		numb = CAN_DATASEGM_OTHER - ct.sd.b0.sg.ndata;
		if ( (ct.rembytes < numb) ||
		      (ct.rembytes > numb && ct.sd.b0.sg.bit_0 != 0) ||
		      (ct.rembytes == numb && ct.sd.b0.sg.bit_0 == 0) ) {
			abort_can_sdo(&ca->si, CAN_ABORT_SDO_DATAMISM);
			ca->ss.state = CAN_TRANSTATE_SDO_DATASIZE;
			can_free(bufbeg);
			return;
		}
		for (cnt = 0; cnt < numb; cnt++) {
			*bufpnt = ct.sd.bd[cnt];
			bufpnt++;
		}
		ct.rembytes -= numb;
		toggle ^= 1;
	}
	if (ca->datapnt == NULL) {
		if (node_write_manstan_objdict_network(ca->node, ca->si.index, ca->si.subind, bufbeg) != CAN_RETOK) {
			ca->ss.state = CAN_TRANSTATE_OBD_WRITE;
		}
	} else {
		datapnt = ca->datapnt;
		bufpnt = bufbeg;
		for (cnt = 0; cnt < ca->datasize; cnt++) {
			*datapnt = *bufpnt;
			bufpnt++;
			datapnt++;
		}
	}
	can_free(bufbeg);
}

void can_sdo_client_transfer(struct sdocltappl *ca)
{
	ca->ss.state = CAN_TRANSTATE_OK;
	ca->ss.abortcode = 0;
	if (client_read_object_dictionary(ca->si.sdoind, 3, &ca->node) != CAN_RETOK) {
		ca->ss.state = CAN_TRANSTATE_SDO_NODE;
		return;
	}
	if (ca->datapnt == NULL) {
		ca->datasize = node_get_manstan_objsize(ca->node, ca->si.index, ca->si.subind, BYTES);
		if (ca->datasize < 0) {
			if (ca->datasize == CAN_ERRET_OBD_NOOBJECT) ca->ss.state = CAN_TRANSTATE_OBD_NOOBJECT;
			else if (ca->datasize == CAN_ERRET_OBD_NOSUBIND) ca->ss.state = CAN_TRANSTATE_OBD_NOSUBIND;
			else ca->ss.state = CAN_TRANSTATE_ERROR;
			return;
		}
	}
	if (ca->datasize == 0) {
		ca->ss.state = CAN_TRANSTATE_OBD_ZERO;
		return;
	}
	if (ca->operation < CAN_SDOPER_UPLOAD) ca->operation = CAN_SDOPER_DOWNLOAD;
	else ca->operation = CAN_SDOPER_UPLOAD;
	if (ca->datasize <= CAN_SDOSIZE_EXPEDITED) {
		if (ca->operation == CAN_SDOPER_DOWNLOAD) ca->operation = CAN_SDOPER_DOWN_EXPEDITED;
		else ca->operation = CAN_SDOPER_UP_EXPEDITED;
	} else if (ca->datasize <= CAN_SDOSIZE_SEGMENTED) {
		if (ca->operation == CAN_SDOPER_DOWNLOAD) ca->operation = CAN_SDOPER_DOWN_SEGMENTED;
		else ca->operation = CAN_SDOPER_UP_SEGMENTED;
	} else {
#if CAN_PROTOCOL_BLOCK == TRUE
		if (ca->operation == CAN_SDOPER_DOWNLOAD) ca->operation = CAN_SDOPER_DOWN_BLOCK;
		else ca->operation = CAN_SDOPER_UP_BLOCK;
		if (ca->datapnt == NULL) {
			ca->datapnt = node_get_manstan_objpointer(ca->node, ca->si.index, ca->si.subind);
			if (ca->datapnt == NULL) {
				if (ca->operation == CAN_SDOPER_DOWN_BLOCK) ca->operation = CAN_SDOPER_DOWN_SEGMENTED;
				else ca->operation = CAN_SDOPER_UP_SEGMENTED;
			}
		}
#else
		if (ca->operation == CAN_SDOPER_DOWNLOAD) ca->operation = CAN_SDOPER_DOWN_SEGMENTED;
		else ca->operation = CAN_SDOPER_UP_SEGMENTED;
#endif
	}
	if (ca->operation == CAN_SDOPER_DOWN_EXPEDITED) sdo_client_down_init(ca);
	else if (ca->operation == CAN_SDOPER_UP_EXPEDITED) sdo_client_up_init(ca);
#if CAN_PROTOCOL_BLOCK == TRUE
	if (ca->operation == CAN_SDOPER_DOWN_BLOCK) {
		sdo_client_down_block(ca);
		if (ca->ss.state == CAN_TRANSTATE_SDO_SRVABORT && ca->ss.abortcode == CAN_ABORT_SDO_CS)  {
			ca->operation = CAN_SDOPER_DOWN_SEGMENTED;
			ca->ss.state = CAN_TRANSTATE_OK;
			ca->ss.abortcode = 0;
		}
	} else if (ca->operation == CAN_SDOPER_UP_BLOCK) {
 		sdo_client_up_block(ca);
		if (ca->ss.state == CAN_TRANSTATE_SDO_SRVABORT && ca->ss.abortcode == CAN_ABORT_SDO_CS)  {
			ca->operation = CAN_SDOPER_UP_SEGMENTED;
			ca->ss.state = CAN_TRANSTATE_OK;
			ca->ss.abortcode = 0;
		}
	}
#endif
	if (ca->operation == CAN_SDOPER_DOWN_SEGMENTED) {
		sdo_client_down_init(ca);
		if (ca->ss.state == CAN_TRANSTATE_OK) sdo_client_down_data(ca);
	} else if (ca->operation == CAN_SDOPER_UP_SEGMENTED) {
		sdo_client_up_init(ca);
		if (ca->ss.state == CAN_TRANSTATE_OK) sdo_client_up_data(ca);
	}
}

#endif

#endif
