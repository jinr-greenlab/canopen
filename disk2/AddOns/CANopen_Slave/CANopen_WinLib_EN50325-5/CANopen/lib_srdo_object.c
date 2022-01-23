#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 2)

#define MASK_PDOMAP_INDEX     0xFFFF0000  // SRDO mapping entry index mask
#define MASK_PDOMAP_SUBIND    0x0000FF00  // SRDO mapping entry subindex mask
#define MASK_PDOMAP_LENGTH    0x000000FF  // SRDO mapping entry object length mask

#define GFC_MODE_DEFAULT              0x00
#define MASK_GFC_CONSUMER_DISABLED    0x01  // GFC consumer disabled
#define MASK_GFC_PRODUCER_DISABLED    0x02  // GFC producer disabled
#define MASK_GFC_DISABLED             (MASK_GFC_CONSUMER_DISABLED | MASK_GFC_PRODUCER_DISABLED)

static unsigned8 gfc_command, gfc_param;
static unsigned8 sr_configuration;
static unsigned8 sr_runstatus;
static int16 sem_srdo_recv, flag_srdo_recv;
static struct srdostruct srdo[CAN_NOF_SRDO];


static void reset_srdo(int16 entry)
{
	unsigned16 cnt;

	srdo[entry].plain.len = 0;
	srdo[entry].bwinv.len = 0;
	for (cnt = 0; cnt < CAN_DATALEN_MAXIMUM; cnt++) {
		srdo[entry].plain.data[cnt] = 0;
		srdo[entry].bwinv.data[cnt] = 0;
	}
}

static void reset_all_srdos(void)
{
	int16 entry;

	for (entry = 0; entry < CAN_NOF_SRDO; entry++) {
		srdo[entry].srvt_cnt = -1;
		srdo[entry].sct_cnt = -1;
		srdo[entry].odev_cnt = -1;
		reset_srdo(entry);
	}
}

static void find_srdo_entry(canindex index, int16 *entry)
{
	if (index >= CAN_INDEX_SRDO_COMM_MIN && index < CAN_INDEX_SRDO_COMM_MIN+CAN_NOF_SRDO) {
		*entry = index - CAN_INDEX_SRDO_COMM_MIN;
	} else if (index >= CAN_INDEX_SRDO_MAP_MIN && index < CAN_INDEX_SRDO_MAP_MIN+CAN_NOF_SRDO) {
		*entry = index - CAN_INDEX_SRDO_MAP_MIN;
	} else {
		*entry = -1;
	}
}

static unsigned8 check_sr_async(void)
{
	if (node_state != CAN_NODE_STATE_OPERATIONAL ||
		sr_configuration != SR_CONFIG_VALID || gfc_command == GFC_VALID) {
		return OFF;
	}
	return ON;
}

static void crc_data32(unsigned32 data)
{
	can_calc_crc((unsigned8)data);
	data >>= 8;
	can_calc_crc((unsigned8)data);
	data >>= 8;
	can_calc_crc((unsigned8)data);
	data >>= 8;
	can_calc_crc((unsigned8)data);
}

static unsigned16 crc_srdo_config(int16 entry)
{
	unsigned8 cnt;

	can_start_crc(0);
	can_calc_crc(srdo[entry].dir);
	can_calc_crc(srdo[entry].sct & 0xFF);
	can_calc_crc((srdo[entry].sct >> 8) & 0xFF);
	can_calc_crc(srdo[entry].srvt);
	crc_data32(srdo[entry].id_odd);
	crc_data32(srdo[entry].id_even);
	can_calc_crc(srdo[entry].nrec);
	for (cnt = 0; cnt < srdo[entry].nrec; cnt++) {
		can_calc_crc(cnt+1);
		if (cnt & 1) crc_data32(~(srdo[entry].map[cnt/2]));
		else crc_data32(srdo[entry].map[cnt/2]);
	}
	can_calc_crc(0);
	return can_calc_crc(0);
}

static void reset_config(int16 entry)
{
	sr_configuration = SR_CONFIG_NOT_VALID;
	srdo[entry].config = SR_CONFIG_NOT_VALID;
	srdo[entry].signature = 0;
}

static int16 process_sr_config(unsigned8 src)
{
	int16 entry;

	sr_configuration = SR_CONFIG_NOT_VALID;
	if (src != SR_CONFIG_VALID) return CAN_RETOK;
	for (entry = 0; entry < CAN_NOF_SRDO; entry++) {
		if (srdo[entry].config != SR_CONFIG_VALID) {
			return CAN_ERRET_OBD_PARINCOMP;
		}
	}
	sr_configuration = SR_CONFIG_VALID;
	if (gfc_param != GFC_MODE_DEFAULT) produce_emcy_default(CAN_EMCY_GFC_MODE);
	return CAN_RETOK;
}

static int16 process_signature(int16 entry, unsigned16 sign)
{
	if ((srdo[entry].dir == SRDO_DIR_RECEIVE || srdo[entry].dir == SRDO_DIR_TRANSMIT) && srdo[entry].nrec == 0) {
		reset_config(entry);
		return CAN_ERRET_OBD_PARINCOMP;
	}
	if (crc_srdo_config(entry) != sign) {
		reset_config(entry);
		return CAN_ERRET_OBD_VALRANGE;
	}
	srdo[entry].config = SR_CONFIG_VALID;
	srdo[entry].signature = sign;
	return CAN_RETOK;
}

static int16 srdo_comm_bytes_objsize(cansubind subind)
{
	switch (subind) {
		case 0:								return sizeof(unsigned8);
		case SUBIND_SRDO_COMM_DIRECTION:	return sizeof(srdo[0].dir);
		case SUBIND_SRDO_COMM_SCT:			return sizeof(srdo[0].sct);
		case SUBIND_SRDO_COMM_SRVT:			return sizeof(srdo[0].srvt);
		case SUBIND_SRDO_COMM_TRTYPE:		return sizeof(srdo[0].trtype);
		case SUBIND_SRDO_COMM_COBID_ODD:	return sizeof(srdo[0].id_odd);
		case SUBIND_SRDO_COMM_COBID_EVEN:	return sizeof(srdo[0].id_even);
	}
	return CAN_ERRET_OBD_NOSUBIND;
}

int16 get_srdo_comm_bytes_objsize(canindex index, cansubind subind)
{
	int16 entry;

	find_srdo_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	return srdo_comm_bytes_objsize(subind);
}

static int16 srdo_comm_access(cansubind subind)
{
	if (subind == 0) return CAN_MASK_ACCESS_RO;
	if (subind == SUBIND_SRDO_COMM_TRTYPE) return CAN_MASK_ACCESS_RO;
	if (node_state == CAN_NODE_STATE_OPERATIONAL) return CAN_MASK_ACCESS_RO;
	return CAN_MASK_ACCESS_RW;
}

int16 see_srdo_comm_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_srdo_comm_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return srdo_comm_access(subind);
}

int16 get_srdo_comm_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_srdo_comm_bytes_objsize(index, subind);
	if (size <= 0) return size;
	switch (subind) {
		case SUBIND_SRDO_COMM_SCT:			return CAN_DEFTYPE_UNSIGNED16;
		case SUBIND_SRDO_COMM_COBID_ODD:	return CAN_DEFTYPE_UNSIGNED32;
		case SUBIND_SRDO_COMM_COBID_EVEN:	return CAN_DEFTYPE_UNSIGNED32;
	}
	return CAN_DEFTYPE_UNSIGNED8;
}

int16 read_srdo_comm_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, entry;
	unsigned32 buf;
	canbyte *bpnt;

	find_srdo_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = srdo_comm_bytes_objsize(subind);
	if (size <= 0) return size;
	bpnt = (canbyte*)&buf; buf = 0;
	if (subind == 0) buf = 6;
	else if (subind == SUBIND_SRDO_COMM_DIRECTION) buf = srdo[entry].dir;
	else if (subind == SUBIND_SRDO_COMM_SCT) buf = srdo[entry].sct;
	else if (subind == SUBIND_SRDO_COMM_SRVT) buf = srdo[entry].srvt;
	else if (subind == SUBIND_SRDO_COMM_TRTYPE) buf = SRDO_TRTYPE_DEFAULT;
	else if (subind == SUBIND_SRDO_COMM_COBID_ODD) buf = srdo[entry].id_odd;
	else if (subind == SUBIND_SRDO_COMM_COBID_EVEN) buf = srdo[entry].id_even;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_srdo_comm_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, entry;
	unsigned32 buf;
	canbyte *bpnt;

	find_srdo_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = srdo_comm_bytes_objsize(subind);
	if (size <= 0) return size;
	if ((srdo_comm_access(subind) & CAN_MASK_ACCESS_WO) == 0) return CAN_ERRET_OBD_READONLY;
	bpnt = (canbyte*)&buf; buf = 0;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (subind == SUBIND_SRDO_COMM_DIRECTION) {
		if (buf > SRDO_DIR_MAXVAL) return CAN_ERRET_OBD_VALRANGE;
		srdo[entry].dir = (unsigned8)buf;
		srdo[entry].nrec = 0;		// Mapping must be checked
	} else if (subind == SUBIND_SRDO_COMM_SCT) {
		if ((unsigned16)buf == 0) return CAN_ERRET_OBD_VALRANGE;
		srdo[entry].sct = (unsigned16)buf;
	} else if (subind == SUBIND_SRDO_COMM_SRVT) {
		if ((unsigned8)buf == 0) return CAN_ERRET_OBD_VALRANGE;
		srdo[entry].srvt = (unsigned8)buf;
	} else if (subind == SUBIND_SRDO_COMM_COBID_ODD) {
		buf &= CAN_MASK_CANID;
		if (buf < CAN_CANID_SRDO_MIN || buf > CAN_CANID_SRDO_MAX) return CAN_ERRET_OBD_VALRANGE;
		if ((buf & 1) == 0) return CAN_ERRET_OBD_VALRANGE;
		srdo[entry].id_odd = buf;
	} else if (subind == SUBIND_SRDO_COMM_COBID_EVEN) {
		buf &= CAN_MASK_CANID;
		if (buf < CAN_CANID_SRDO_MIN || buf > CAN_CANID_SRDO_MAX) return CAN_ERRET_OBD_VALRANGE;
		if (buf & 1) return CAN_ERRET_OBD_VALRANGE;
		srdo[entry].id_even = buf;
	}
	reset_config(entry);
	if (subind == SUBIND_SRDO_COMM_DIRECTION ||
		subind == SUBIND_SRDO_COMM_COBID_ODD || subind == SUBIND_SRDO_COMM_COBID_EVEN) {
		if (srdo[entry].dir == SRDO_DIR_TRANSMIT) {
			return correct_double_canid(index, CAN_CANID_DUMMY, CAN_CANID_DUMMY);
		}
		return correct_double_canid(index, (canlink)(srdo[entry].id_odd), (canlink)(srdo[entry].id_even));
	}
	return CAN_RETOK;
}

static int16 srdo_map_bytes_objsize(cansubind subind)
{
	if (subind == 0) return sizeof(unsigned8);
	if (subind <= (2 * CAN_NOF_MAP_BYTEGR)) return sizeof(unsigned32);
	return CAN_ERRET_OBD_NOSUBIND;
}

int16 get_srdo_map_bytes_objsize(canindex index, cansubind subind)
{
	int16 entry;

	find_srdo_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	return srdo_map_bytes_objsize(subind);
}

int16 see_srdo_map_access(canindex index, cansubind subind)
{
	int16 entry;

	find_srdo_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	if (node_state == CAN_NODE_STATE_OPERATIONAL) return CAN_MASK_ACCESS_RO;
	if (subind != 0 && srdo[entry].nrec != 0) return CAN_MASK_ACCESS_RO;		// See EN50325-5
	return CAN_MASK_ACCESS_RW;
}

int16 get_srdo_map_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_srdo_map_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_DEFTYPE_UNSIGNED8;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_srdo_map_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt, entry;
	unsigned32 buf;
	canbyte *bpnt;

	find_srdo_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = srdo_map_bytes_objsize(subind);
	if (size <= 0) return size;
	bpnt = (canbyte*)&buf; buf = 0;
	if (subind == 0) {
		buf = srdo[entry].nrec;
	} else {
		subind -= 1;
		buf = srdo[entry].map[subind/2];
		if (subind & 1) buf = ~buf;
	}
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

static int32 test_srdo_map(int16 entry, unsigned32 map)
{
	canindex mapind;
	cansubind mapsub;
	int32 size;
	int16 accs;

	mapind = (map & MASK_PDOMAP_INDEX) >> 16;
	if (mapind == 0) return CAN_ERRET_PDO_NOMAP;	// Re-store optimization for UNused objects
	mapsub = (map & MASK_PDOMAP_SUBIND) >> 8;
	accs = server_see_access(mapind, mapsub);
	if (accs < 0) return CAN_ERRET_PDO_NOMAP;
	if ((accs & CAN_MASK_ACCESS_PDO) == 0) return CAN_ERRET_PDO_NOMAP;
	if ((accs & CAN_MASK_ACCESS_RO) == 0) {
		if (srdo[entry].dir == SRDO_DIR_TRANSMIT) return CAN_ERRET_PDO_NOMAP;
	}
	if ((accs & CAN_MASK_ACCESS_WO) == 0) {
		if (srdo[entry].dir == SRDO_DIR_RECEIVE) return CAN_ERRET_PDO_NOMAP;
	}
	size = CAN_SIZEOF_FACTOR * server_get_object_size(mapind, mapsub);
	if (size <= 0) return CAN_ERRET_PDO_NOMAP;
	if (size > CAN_NOF_PDOBIT_MAX || (map & MASK_PDOMAP_LENGTH) != (unsigned32)size) {
		return CAN_ERRET_PDO_ERRMAP;
	}
	return size;
}

int16 write_srdo_map_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 entry;
	int32 size, cnt;
	unsigned16 len;
	unsigned32 buf;
	canbyte *bpnt;

	find_srdo_entry(index, &entry);
	if (entry < 0) return CAN_ERRET_OBD_NOOBJECT;
	size = srdo_map_bytes_objsize(subind);
	if (size <= 0) return (int16)size;
	if (node_state == CAN_NODE_STATE_OPERATIONAL) return CAN_ERRET_OBD_READONLY;
	if (subind == 0) {
		if (*data == 0) {
			srdo[entry].nrec = 0;
			reset_config(entry);
			return CAN_RETOK;
		} else {
			if (srdo[entry].nrec != 0) return CAN_ERRET_OBD_OBJACCESS;
			if (*data > (2 * CAN_NOF_MAP_BYTEGR)) return CAN_ERRET_PDO_ERRMAP;
			if (*data & 1) return CAN_ERRET_PDO_ERRMAP;
			len = 0;
			for (cnt = 0; cnt < *data/2; cnt++) {
				size = test_srdo_map(entry, srdo[entry].map[cnt]);
				if (size < 0) return (int16)size;
				len += (unsigned16)size;
				if (len > CAN_NOF_PDOBIT_MAX) return CAN_ERRET_PDO_ERRMAP;
			}
			srdo[entry].nrec = *data;
			reset_config(entry);
			return CAN_RETOK;
		}
	} else {
		if (srdo[entry].nrec != 0) return CAN_ERRET_OBD_READONLY;		// See EN50325-5
		bpnt = (canbyte*)&buf;
		size = sizeof(unsigned32);
		FROM_CANOPEN_TO_OBJECT_DICTIONARY
		subind -= 1;
		if (subind & 1) {
			if ((unsigned32)(~buf) != (unsigned32)(srdo[entry].map[subind/2])) {
				 return CAN_ERRET_PDO_NOMAP;
			}
			reset_config(entry);
			return CAN_RETOK;
		}
		size = test_srdo_map(entry, buf);
		if (size < 0) return (int16)size;
		srdo[entry].map[subind/2] = buf;
		reset_config(entry);
		return CAN_RETOK;
	}
}

int16 get_sr_config_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_SR_GFC) {
		if (subind == 0) return sizeof(gfc_command);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	if (index == CAN_INDEX_SR_CONFIG) {
		if (subind == 0) return sizeof(sr_configuration);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	if (index == CAN_INDEX_SR_SIGNATURE) {
		if (subind == 0) return sizeof(unsigned8);
		if (subind <= CAN_NOF_SRDO) return sizeof(srdo[0].signature);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	if (index == CAN_INDEX_SR_GFCPARAM) {
		if (subind == 0) return sizeof(gfc_param);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	if (index == CAN_INDEX_SR_RUNSTATUS) {
		if (subind == 0) return sizeof(sr_runstatus);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

static int16 sr_config_access(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_SR_GFC) return CAN_MASK_ACCESS_RO;	// RW access in the EN50235-5
	if (index == CAN_INDEX_SR_RUNSTATUS) return CAN_MASK_ACCESS_RO;
	if (node_state == CAN_NODE_STATE_OPERATIONAL) return CAN_MASK_ACCESS_RO;
	if (index == CAN_INDEX_SR_SIGNATURE) {
		if (subind == 0) return CAN_MASK_ACCESS_RO;
	}
	return CAN_MASK_ACCESS_RW;
}

int16 see_sr_config_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_sr_config_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return sr_config_access(index, subind);
}

int16 get_sr_config_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_sr_config_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_SR_SIGNATURE) {
		if (subind != 0) return CAN_DEFTYPE_UNSIGNED16;
	}
	return CAN_DEFTYPE_UNSIGNED8;
}

int16 read_sr_config_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;

	size = get_sr_config_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_SR_GFC) {
		bpnt = (canbyte*)&gfc_command;
	} else if (index == CAN_INDEX_SR_CONFIG) {
		bpnt = (canbyte*)&sr_configuration;
	} else if (index == CAN_INDEX_SR_GFCPARAM) {
		bpnt = (canbyte*)&gfc_param;
	} else if (index == CAN_INDEX_SR_RUNSTATUS) {
		bpnt = (canbyte*)&sr_runstatus;
	} else {			// CAN_INDEX_SR_SIGNATURE
		if (subind == 0) {
			*data = CAN_NOF_SRDO;
			return CAN_RETOK;
		}
		bpnt = (canbyte*)&(srdo[subind-1].signature);
	}
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_sr_config_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	unsigned32 buf;
	canbyte *bpnt;

	size = get_sr_config_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if ((sr_config_access(index, subind) & CAN_MASK_ACCESS_WO) == 0) return CAN_ERRET_OBD_READONLY;
	bpnt = (canbyte*)&buf; buf = 0;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (index == CAN_INDEX_SR_CONFIG) {
		return process_sr_config((unsigned8)buf);
	} else if (index == CAN_INDEX_SR_SIGNATURE) {
		return process_signature(subind-1, (unsigned16)buf);
	} else if (index == CAN_INDEX_SR_GFCPARAM) {
		if (buf & ~MASK_GFC_DISABLED) return CAN_ERRET_OBD_VALRANGE;
		gfc_param = (unsigned8)buf;	
	}
	return CAN_RETOK;
}

void produce_sr_gfc(void)
{
	canframe cf;

	if (sr_runstatus == OFF) return;
	if (gfc_command == GFC_VALID) return;
	gfc_command = GFC_VALID;
	if (gfc_param & MASK_GFC_PRODUCER_DISABLED) return;
	CLEAR_FRAME(&cf);
	cf.id = CAN_CANID_GFC;
	cf.len = CAN_DATALEN_GFC;
	send_can_data(&cf);
}

void consume_sr_gfc(void)
{
	if (sr_runstatus == OFF) return;
	if (gfc_param & MASK_GFC_CONSUMER_DISABLED) return;
	gfc_command = GFC_VALID;
}

static void monitor_receive_srdo(void)
{
	int16 entry;

	CAN_CRITICAL_BEGIN
	sem_srdo_recv++;
	if (sem_srdo_recv != 0) {
		sem_srdo_recv--;
		CAN_CRITICAL_END
		flag_srdo_recv++;
		return;
	}
	CAN_CRITICAL_END
	for (entry = 0; entry < CAN_NOF_SRDO; entry++) {
		if (srdo[entry].dir != SRDO_DIR_RECEIVE) continue;
		if (srdo[entry].srvt_cnt > 0) {
			srdo[entry].srvt_cnt--;
			if (srdo[entry].srvt_cnt == 0) reset_srdo(entry);
		}
		if (srdo[entry].sct_cnt > 0) {
			srdo[entry].sct_cnt--;
			if (srdo[entry].sct_cnt == 0) {
				produce_sr_gfc();		// SRDO processing stops with a single error
				break;
			}
		}
	}
	CAN_CRITICAL_BEGIN
	sem_srdo_recv--;
	CAN_CRITICAL_END
}

static void transmit_srdo_odd(int16 entry)
{
	canframe cf;

	CLEAR_FRAME(&cf);
	cf.id = srdo[entry].id_odd;
	cf.len = srdo[entry].plain.len;
	cf.data[0] = srdo[entry].plain.data[0];
	cf.data[1] = srdo[entry].plain.data[1];
	cf.data[2] = srdo[entry].plain.data[2];
	cf.data[3] = srdo[entry].plain.data[3];
	cf.data[4] = srdo[entry].plain.data[4];
	cf.data[5] = srdo[entry].plain.data[5];
	cf.data[6] = srdo[entry].plain.data[6];
	cf.data[7] = srdo[entry].plain.data[7];
	send_can_data(&cf);
}

static void transmit_srdo_even(int16 entry)
{
	canframe cf;

	CLEAR_FRAME(&cf);
	cf.id = srdo[entry].id_even;
	cf.len = srdo[entry].plain.len;
	cf.data[0] = ~srdo[entry].plain.data[0];
	cf.data[1] = ~srdo[entry].plain.data[1];
	cf.data[2] = ~srdo[entry].plain.data[2];
	cf.data[3] = ~srdo[entry].plain.data[3];
	cf.data[4] = ~srdo[entry].plain.data[4];
	cf.data[5] = ~srdo[entry].plain.data[5];
	cf.data[6] = ~srdo[entry].plain.data[6];
	cf.data[7] = ~srdo[entry].plain.data[7];
	send_can_data(&cf);
}

static int16 map_srdo(int16 entry)
{
	int16 fnr;
	unsigned16 len, cnt;
	unsigned8 nur;
	canindex mapind;
	cansubind mapsub;

	if (srdo[entry].nrec == 0) return CAN_ERRET_PDO_MAP_DEACT;
	srdo[entry].plain.len = 0;
	nur = srdo[entry].nrec / 2;
	for (cnt = 0; cnt < nur; cnt++) {
		mapind = (srdo[entry].map[cnt] & MASK_PDOMAP_INDEX) >> 16;
		mapsub = (srdo[entry].map[cnt] & MASK_PDOMAP_SUBIND) >> 8;
		len = 1 + ((srdo[entry].map[cnt] & MASK_PDOMAP_LENGTH) - 1) / CAN_SIZEOF_FACTOR;
		if ((srdo[entry].plain.len + len) > CAN_DATALEN_MAXIMUM) return CAN_ERRET_PDO_ERRMAP;
		fnr = server_read_object_dictionary(mapind, mapsub, &(srdo[entry].plain.data[srdo[entry].plain.len]));
		if (fnr != CAN_RETOK) return fnr;
		srdo[entry].plain.len += (unsigned8)len;
	}
	return CAN_RETOK;
}

static void process_transmit_srdo(void)
{
	int16 entry;

	for (entry = 0; entry < CAN_NOF_SRDO; entry++) {
		if (srdo[entry].dir != SRDO_DIR_TRANSMIT) continue;
		if (srdo[entry].odev_cnt > 0) {
			srdo[entry].odev_cnt--;
			if (srdo[entry].odev_cnt == 0) {
				transmit_srdo_even(entry);
			}
		}
		if (srdo[entry].sct_cnt > 0) {
			srdo[entry].sct_cnt--;
			if (srdo[entry].sct_cnt == 0) {
				if (map_srdo(entry) != CAN_RETOK) {
					produce_sr_gfc();		// SRDO processing stops with a single error
					return;
				}
				transmit_srdo_odd(entry);
				srdo[entry].sct_cnt = (int32)srdo[entry].sct * 1000 / CAN_TIMERUSEC;
				if (srdo[entry].sct_cnt == 0) srdo[entry].sct_cnt = 1;
				srdo[entry].odev_cnt = 1;
			}
		}
	}
}

void control_srdo(void)		// Called from the CANopen timer
{
	if (sr_runstatus == OFF) return;
	if (check_sr_async() == OFF) {		// Stops autonomously
		enter_error_state();			// produce_sr_gfc() may be called
		sr_runstatus = OFF;
		reset_all_srdos();
		produce_emcy_default(CAN_EMCY_SR_STOPPED);
		return;
	}
	monitor_receive_srdo();
	process_transmit_srdo();
}

static int16 activate_srdo(int16 entry)
{
	int16 fnr;
	unsigned16 pdoelm, cnt;
	unsigned8 nur;
	canindex mapind;
	cansubind mapsub;

	nur = srdo[entry].nrec / 2;
	pdoelm = 0;
	for (cnt = 0; cnt < nur; cnt++) {
		pdoelm += 1 + ((srdo[entry].map[cnt] & MASK_PDOMAP_LENGTH) - 1) / CAN_SIZEOF_FACTOR;
		if (pdoelm > srdo[entry].plain.len) {
			produce_emcy_default(CAN_EMCY_SRDOLENERR);
			return CAN_ERRET_PDO_ERRMAP;
		}
	}
	pdoelm = 0;
	for (cnt = 0; cnt < nur; cnt++) {
		mapind = (srdo[entry].map[cnt] & MASK_PDOMAP_INDEX) >> 16;
		mapsub = (srdo[entry].map[cnt] & MASK_PDOMAP_SUBIND) >> 8;
		fnr = server_write_object_dictionary(mapind, mapsub, &(srdo[entry].plain.data[pdoelm]));
		if (fnr != CAN_RETOK) return fnr;
		srdo_activated_slave(mapind, mapsub);
		pdoelm += 1 + ((srdo[entry].map[cnt] & MASK_PDOMAP_LENGTH) - 1) / CAN_SIZEOF_FACTOR;
	}
	return CAN_RETOK;
}

static void process_check_srdo(int16 entry)
{
	unsigned16 cnt;

	if (srdo[entry].plain.len != srdo[entry].bwinv.len) return;
	for (cnt = 0; cnt < srdo[entry].plain.len; cnt++) {
		if ((canbyte)(srdo[entry].plain.data[cnt]) != (canbyte)(~srdo[entry].bwinv.data[cnt])) {
			return;
		}
	}
	if (activate_srdo(entry) == CAN_RETOK) {
		srdo[entry].sct_cnt = 1 + (int32)srdo[entry].sct * 1000 / CAN_TIMERUSEC;
	}
}

static void process_buffer_srdo(int16 entry, canframe *cf)
{
	unsigned16 cnt;

	if (cf->id == srdo[entry].id_odd) {
		if (srdo[entry].srvt_cnt > 0) return;
		srdo[entry].srvt_cnt = (int16)(1 + (int32)srdo[entry].srvt * 1000 / CAN_TIMERUSEC);
		srdo[entry].plain.len = cf->len;
		for (cnt = 0; cnt < cf->len; cnt++) {
			srdo[entry].plain.data[cnt] = cf->data[cnt];
		}
	} else if (cf->id == srdo[entry].id_even) {
		if (srdo[entry].srvt_cnt <= 0) return;
		srdo[entry].srvt_cnt = -1;
		srdo[entry].bwinv.len = cf->len;
		for (cnt = 0; cnt < cf->len; cnt++) {
			srdo[entry].bwinv.data[cnt] = cf->data[cnt];
		}
		process_check_srdo(entry);
		reset_srdo(entry);
	}
}

void receive_can_srdo(canindex index, canframe *cf)
{
	int16 entry;

	if (sr_runstatus == OFF) return;
	if (check_sr_async() == OFF) return;	// Will be stopped by the control_srdo()
	find_srdo_entry(index, &entry);
	if (entry < 0) return;
	if (srdo[entry].dir != SRDO_DIR_RECEIVE) return;
	if (srdo[entry].nrec == 0) return;
	CAN_CRITICAL_BEGIN
	sem_srdo_recv++;
	CAN_CRITICAL_END
	process_buffer_srdo(entry, cf);
	CAN_CRITICAL_BEGIN
	sem_srdo_recv--;
	CAN_CRITICAL_END
	while (flag_srdo_recv > 0) {
		if (sem_srdo_recv != -1) break;
		monitor_receive_srdo();
		flag_srdo_recv--;
	}
}

void run_sr_operations(void)	// Called from the start_node()
{
	int16 entry;

	sr_runstatus = OFF;
	if (sr_configuration != SR_CONFIG_VALID) return;
	gfc_command = GFC_NOT_VALID;
	for (entry = 0; entry < CAN_NOF_SRDO; entry++) {
		if (srdo[entry].dir == SRDO_DIR_RECEIVE) {
			srdo[entry].sct_cnt = 1 + (int32)srdo[entry].sct * 1000 / CAN_TIMERUSEC;
		} else if (srdo[entry].dir == SRDO_DIR_TRANSMIT) {
			srdo[entry].sct_cnt = 1;
		}
	}
	sr_runstatus = ON;
}

unsigned8 get_sr_runstatus(void)
{
	return sr_runstatus;
}

void can_init_srdo(void)
{
	int16 entry, cm;

	sr_runstatus = OFF;
	sr_configuration = SR_CONFIG_NOT_VALID;

	gfc_command = GFC_NOT_VALID;
	gfc_param = GFC_MODE_DEFAULT;
	
 	sem_srdo_recv = -1;
 	flag_srdo_recv = 0;

	reset_all_srdos();

	for (entry = 0; entry < CAN_NOF_SRDO; entry++) {
		srdo[entry].dir = SRDO_DIR_INVALID;
		srdo[entry].sct = SRDO_SCT_RECEIVE;
		srdo[entry].srvt = SRDO_SRVT_RECEIVE;
		srdo[entry].trtype = SRDO_TRTYPE_DEFAULT;
		srdo[entry].config = SR_CONFIG_NOT_VALID;
		srdo[entry].signature = 0;
		srdo[entry].nrec = 0;
		for (cm = 0; cm < CAN_NOF_MAP_BYTEGR; cm++) srdo[entry].map[cm] = 0;
		if (node_id <= 64) srdo[entry].id_odd = CAN_CANID_SRDO_BASE + (2*node_id);
		else srdo[entry].id_odd = CAN_CANID_SRDO_BASE + 2*64;	// nodeID 64
		srdo[entry].id_even = srdo[entry].id_odd + 1;
	}
	if (node_id <= 32) {
		srdo[0].dir = SRDO_DIR_TRANSMIT;
		srdo[0].sct = SRDO_SCT_TRANSMIT;
	#if (CAN_NOF_SRDO > 1)
		srdo[1].dir = SRDO_DIR_RECEIVE;
		srdo[1].sct = SRDO_SCT_RECEIVE;
		srdo[1].id_odd = CAN_CANID_SRDO_BASE + (2*(node_id+32));
		srdo[1].id_even = srdo[1].id_odd + 1;
	#endif
	} else if (node_id <= 64) {
		srdo[0].dir = SRDO_DIR_RECEIVE;
		srdo[0].sct = SRDO_SCT_RECEIVE;
	}

	for (entry = 0; entry < CAN_NOF_SRDO; entry++) {
		if (srdo[entry].dir == SRDO_DIR_RECEIVE) {
			correct_double_canid((canindex)(CAN_INDEX_SRDO_COMM_MIN+entry), (canlink)(srdo[entry].id_odd), (canlink)(srdo[entry].id_even));
		}
	}

}

#endif
