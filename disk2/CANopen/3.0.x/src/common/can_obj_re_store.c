#include <can_header.h>

#if CHECK_VERSION(3, 0, 3)
//  CHECK_VERSION(2, 3, 3)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 2)
//  CHECK_VERSION(1, 7, 1)

#if CAN_OBJECT_RE_STORE == TRUE || CAN_OBJECT_LSS == TRUE

#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

#define CAN_NOF_RESTORE_SUBINDS				6	// Save active nodeid and bitrate
//#define CAN_NOF_RESTORE_SUBINDS				4	// Save configured nodeid and bitrate	

#define CAN_SUBIND_RESTORE_ALL				1
#define CAN_SUBIND_RESTORE_COMMUNICATION	2
#define CAN_SUBIND_RESTORE_APPLICATION		3
#define CAN_SUBIND_RESTORE_COBIDS			4
#define CAN_SUBIND_RESTORE_NODEID			5	// Save active nodeid
#define CAN_SUBIND_RESTORE_BITRATE			6	// Save active bitrate

#define CAN_RESTORE_DATA_SIZE_MAX			64	// Max size of the saved object (bytes)

#define CCITT_CRC_INITVALUE			0x1D0F

#define FLASH_FLAG_CRC				1		// Calculate flash CRC only
#define FLASH_FLAG_WRITE_OBD		2		// Write to object dictionary from flash

#define MASK_SAVE_ON_COMMAND		0x00000001
#define MASK_LOAD_DEFAULT			0x00000001

#define MASK_FLAG_VALUE_SET			0x8000
#define MASK_FLAG_VALUE_RETURN		0x00FF

#define CAN_NOF_LOAD_COMM_1			32
#define CAN_NOF_LOAD_COMM_2			11
#define CAN_NOF_LOAD_APPL			1
	
#define FLASH_PAGE_SIZE_BYTES		1024

/***** Non-volatile (EEPROM/FLASH) memory data *****/
static unsigned8 test_store_flag[FLASH_PAGE_SIZE_BYTES];
static unsigned8 test_store_comm[FLASH_PAGE_SIZE_BYTES];
static unsigned8 test_store_appl[FLASH_PAGE_SIZE_BYTES];
/***** Non-volatile (EEPROM/FLASH) memory data *****/

//#define PAGE_FLAG_START_ADDR		0x0801F400		// Page 125 start, STM32 microcontroller
#define PAGE_FLAG_START_ADDR		test_store_flag
#define PAGE_FLAG_END_ADDR			(PAGE_FLAG_START_ADDR+FLASH_PAGE_SIZE_BYTES-1)
#define PAGE_FLAG_INITFLASH_ADDR	PAGE_FLAG_START_ADDR		// CCITT_CRC_INITVALUE flash initiated
#define PAGE_FLAG_RESMASK_ADDR		(PAGE_FLAG_START_ADDR+2)	// Re-store bit mask
#define PAGE_FLAG_NODEID_ADDR		(PAGE_FLAG_START_ADDR+4)	// Node ID
#define PAGE_FLAG_BITRATE_ADDR		(PAGE_FLAG_START_ADDR+6)	// Bit rate

//#define PAGE_COMM_START_ADDR		0x0801F800		// Page 126 start, STM32 microcontroller
#define PAGE_COMM_START_ADDR		test_store_comm
#define PAGE_COMM_END_ADDR			(PAGE_COMM_START_ADDR+FLASH_PAGE_SIZE_BYTES-1)
#define PAGE_COMM_2_START_ADDR		(PAGE_COMM_START_ADDR+FLASH_PAGE_SIZE_BYTES-64)

//#define PAGE_APPL_START_ADDR		0x0801FC00		// Page 127 start, STM32 microcontroller
#define PAGE_APPL_START_ADDR		test_store_appl
#define PAGE_APPL_END_ADDR			(PAGE_APPL_START_ADDR+FLASH_PAGE_SIZE_BYTES-1)

static struct store stc_1[CAN_NOF_LOAD_COMM_1];
static struct store stc_2[CAN_NOF_LOAD_COMM_2];
static struct store stap[CAN_NOF_LOAD_APPL];

static unsigned8 *flashaddr;
static unsigned8 *minaddr, *maxaddr;

static void set_error_store_err(void)
{
	set_error_field(CAN_EMCY_STORE_PROC, 0);
}

static void set_error_store_crc(void)
{
	set_error_field(CAN_EMCY_STORE_CRC, 0);
}

static int16 init_flash_page_flag(void)		// 3.0.1 init as flash (0xFF)
{
	unsigned16 cnt;

// Erase corresponding flash page here.
// If failed, set_error_store_err(); and return CAN_ERRET_FLASH_INIT;
	for (cnt = 0; cnt < FLASH_PAGE_SIZE_BYTES; cnt++) test_store_flag[cnt] = 0xFF;

	return CAN_RETOK;
}

static int16 init_flash_page_comm(void)		// 3.0.1 init as flash (0xFF)
{
	unsigned16 cnt;

// Erase corresponding flash page here.
// If failed, set_error_store_err(); and return CAN_ERRET_FLASH_INIT;
	for (cnt = 0; cnt < FLASH_PAGE_SIZE_BYTES; cnt++) test_store_comm[cnt] = 0xFF;

	flashaddr = PAGE_COMM_START_ADDR;
	minaddr = PAGE_COMM_START_ADDR;
	maxaddr = PAGE_COMM_END_ADDR;
	return CAN_RETOK;
}

static int16 init_flash_page_appl(void)		// 3.0.1 init as flash (0xFF)
{
	unsigned16 cnt;

// Erase corresponding flash page here.
// If failed, set_error_store_err(); and return CAN_ERRET_FLASH_INIT;
	for (cnt = 0; cnt < FLASH_PAGE_SIZE_BYTES; cnt++) test_store_appl[cnt] = 0xFF;

	flashaddr = PAGE_APPL_START_ADDR;
	minaddr = PAGE_APPL_START_ADDR;
	maxaddr = PAGE_APPL_END_ADDR;
	return CAN_RETOK;
}

static void read_flash_variable(unsigned16 *data)
{
	*data = 0;
	if (flashaddr < minaddr || flashaddr > maxaddr) {
		set_error_store_err();
		return;
	}

// Read 16 bit flash word into *data here.
	*data = *(unsigned16*)flashaddr;

	flashaddr += sizeof(unsigned16);
}

static int16 write_flash_variable(unsigned16 data)
{
	if (flashaddr < minaddr || flashaddr > maxaddr) {
		set_error_store_err();
		return CAN_ERRET_FLASH_ADDRESS;
	}

// Write (program) 16 bit flash word from data here.
// If failed, set_error_store_err(); and return CAN_ERRET_RE_STORE;
	*(unsigned16*)flashaddr = data;

	can_calc_crc((data >> 8) & 0xFF);
	can_calc_crc(data & 0xFF);
	flashaddr += sizeof(unsigned16);
	return CAN_RETOK;
}

static void crc_flash_variable(void)
{
	unsigned16 data;

	if (flashaddr < minaddr || flashaddr > maxaddr) {
		set_error_store_err();
		return;
	}

// Read 16 bit flash word into data here.
	data = *(unsigned16*)flashaddr;

	can_calc_crc((data >> 8) & 0xFF);
	can_calc_crc(data & 0xFF);
	flashaddr += sizeof(unsigned16);
}

static int16 get_flash_flag_data(unsigned8 *addr)
{
	unsigned16 fl;

	if (*(unsigned16*)PAGE_FLAG_INITFLASH_ADDR != CCITT_CRC_INITVALUE) return CAN_ERRET_FLASH_DATA;
	fl = *(unsigned16*)addr;
	if (fl & MASK_FLAG_VALUE_SET) return (fl & MASK_FLAG_VALUE_RETURN);
	return CAN_ERRET_FLASH_VALUE;
}

static int16 put_flash_flag(unsigned8 *addr, unsigned16 flag)	// 2.2.1 some changes
{
	unsigned16 flpar[3];

	if (*(unsigned16*)PAGE_FLAG_INITFLASH_ADDR != CCITT_CRC_INITVALUE) return CAN_ERRET_FLASH_DATA;
	flpar[0] = *(unsigned16*)PAGE_FLAG_RESMASK_ADDR;
	flpar[1] = *(unsigned16*)PAGE_FLAG_NODEID_ADDR;
	flpar[2] = *(unsigned16*)PAGE_FLAG_BITRATE_ADDR;
	if (addr == PAGE_FLAG_RESMASK_ADDR) flpar[0] = flag;
	else if (addr == PAGE_FLAG_NODEID_ADDR) flpar[1] = flag;
	else if (addr == PAGE_FLAG_BITRATE_ADDR) flpar[2] = flag;
	else return CAN_ERRET_FLASH_ADDRESS;
	if (init_flash_page_flag() != CAN_RETOK) return CAN_ERRET_FLASH_INIT;
	*(unsigned16*)PAGE_FLAG_INITFLASH_ADDR = CCITT_CRC_INITVALUE;
	*(unsigned16*)PAGE_FLAG_RESMASK_ADDR = flpar[0];
	*(unsigned16*)PAGE_FLAG_NODEID_ADDR = flpar[1];
	*(unsigned16*)PAGE_FLAG_BITRATE_ADDR = flpar[2];
	if (*(unsigned16*)PAGE_FLAG_INITFLASH_ADDR != CCITT_CRC_INITVALUE) return CAN_ERRET_FLASH_DATA;
	if (*(unsigned16*)PAGE_FLAG_RESMASK_ADDR != flpar[0]) return CAN_ERRET_FLASH_DATA;
	if (*(unsigned16*)PAGE_FLAG_NODEID_ADDR != flpar[1]) return CAN_ERRET_FLASH_DATA;
	if (*(unsigned16*)PAGE_FLAG_BITRATE_ADDR != flpar[2]) return CAN_ERRET_FLASH_DATA;
	return CAN_RETOK;
}

static void obd_pre_process(canindex index)
{
	canbyte data;

	if (index == CAN_INDEX_EMCY_COBID) {
		server_write_obd_u32(index, 0, CAN_MASK_COBID_INVALID | (CAN_CANID_EMCY_BASE + node_id));	// 2.3.2 canid corrected to un_restricted
		return;
	}
	if ( (index >= CAN_INDEX_RCVPDO_MAP_MIN && index < CAN_INDEX_RCVPDO_MAP_MIN+CAN_NOF_PDO_RECEIVE) ||
		 (index >= CAN_INDEX_TRNPDO_MAP_MIN && index < CAN_INDEX_TRNPDO_MAP_MIN+CAN_NOF_PDO_TRANSMIT) ) { 
		server_read_object_dictionary(index, 0, &data);
		if (data != 0) {
			data = 0;
			server_write_object_dictionary(index, 0, &data);
		}
		return;
	}
}

static int32 get_object_size_words_16(canindex index, cansubind subind)
{
	int32 size;

	size = server_get_object_size(index, subind, BYTES);
	if (size > CAN_RESTORE_DATA_SIZE_MAX) {
		set_error_store_err();
		return CAN_ERRET_RE_STORE;
	}
	if (size <= 0) {
		set_error_store_err();
		return size;
	}
	return (1 + (size-1)/2);
}

static int16 object_store(canindex index, cansubind subind)
{
	int32 size, cnt;
	int16 fnr;
	canbyte data[CAN_RESTORE_DATA_SIZE_MAX];
	unsigned16 *pnt16;

	size = get_object_size_words_16(index, subind);
	if (size <= 0) return (int16)size;
	pnt16 = (unsigned16*)data;
	for (cnt = 0; cnt < CAN_RESTORE_DATA_SIZE_MAX; cnt++) data[cnt] = 0;
	server_read_object_dictionary(index, subind, data);
	for (cnt = 0; cnt < size; cnt++) {
		fnr = write_flash_variable(*pnt16);
		if (fnr != CAN_RETOK) return fnr;
		pnt16++;
	}
	return CAN_RETOK;
}

static int16 process_store(canindex index, unsigned16 submask)
{
	cansubind cs;
	unsigned16 msk;
	int16 fnr;

	if (index == CAN_INDEX_DUMMY) return CAN_RETOK;
	if (submask == 0) return object_store(index, 0);
	msk = 1;
	for (cs = 1; cs <= 16; cs++) {
		if (submask & msk) {
			fnr = object_store(index, cs);
			if (fnr != CAN_RETOK) return fnr;
		}
		msk <<= 1;
	}
	return CAN_RETOK;
}

static int16 can_process_store_comm(void)
{
	unsigned16 cob;
	int16 fnr;

	if (init_flash_page_comm() != CAN_RETOK) return CAN_ERRET_FLASH_INIT;
	can_start_crc(0);
	fnr = write_flash_variable(CCITT_CRC_INITVALUE);
	if (fnr != CAN_RETOK) return fnr;
	for (cob = 0; cob < CAN_NOF_LOAD_COMM_1; cob++) {
		fnr = process_store(stc_1[cob].index, stc_1[cob].submask01);
		if (fnr != CAN_RETOK) return fnr;
	}
	can_calc_crc(0);
	fnr = write_flash_variable(can_calc_crc(0));
	if (fnr != CAN_RETOK) return fnr;
	flashaddr = PAGE_COMM_2_START_ADDR;
	can_start_crc(0);
	fnr = write_flash_variable(CCITT_CRC_INITVALUE);
	if (fnr != CAN_RETOK) return fnr;
	for (cob = 0; cob < CAN_NOF_LOAD_COMM_2; cob++) {
		fnr = process_store(stc_2[cob].index, stc_2[cob].submask01);
		if (fnr != CAN_RETOK) return fnr;
	}
	can_calc_crc(0);
	return write_flash_variable(can_calc_crc(0));
}

static int16 can_process_store_application(void)	// 3.0.2 some changes
{
	unsigned16 cob;
	int16 fnr;

	if (init_flash_page_appl() != CAN_RETOK) return CAN_ERRET_FLASH_INIT;
	can_start_crc(0);
	fnr = write_flash_variable(CCITT_CRC_INITVALUE);
	if (fnr != CAN_RETOK) return fnr;
	for (cob = 0; cob < CAN_NOF_LOAD_APPL; cob++) {
		fnr = process_store(stap[cob].index, stap[cob].submask01);
		if (fnr != CAN_RETOK) return fnr;
	}
	can_calc_crc(0);
	return write_flash_variable(can_calc_crc(0));
}

static int16 object_re_store_crc(canindex index, cansubind subind)
{
	int32 size, cnt;

	size = get_object_size_words_16(index, subind);
	if (size <= 0) return (int16)size;
	for (cnt = 0; cnt < size; cnt++) crc_flash_variable();
	return CAN_RETOK;
}

static int16 object_re_store_write(canindex index, cansubind subind)
{
	int32 size, cnt;
	canbyte data[CAN_RESTORE_DATA_SIZE_MAX];
	unsigned16 *pnt16;

	size = get_object_size_words_16(index, subind);
	if (size <= 0) return (int16)size;
	pnt16 = (unsigned16*)data;
	for (cnt = 0; cnt < CAN_RESTORE_DATA_SIZE_MAX; cnt++) data[cnt] = 0;
	for (cnt = 0; cnt < size; cnt++) {
		read_flash_variable(pnt16);
		pnt16++;
	}
	obd_pre_process(index);
	server_write_object_dictionary(index, subind, data);
	return CAN_RETOK;
}

static int16 process_re_store(canindex index, unsigned16 submask, unsigned16 flag)
{
	cansubind cs;
	unsigned16 msk;
	int16 fnr;

	if (index == CAN_INDEX_DUMMY) return CAN_RETOK;
	if (submask == 0) {
		if (flag == FLASH_FLAG_CRC) return object_re_store_crc(index, 0);
		else return object_re_store_write(index, 0);
	}
	msk = 1;
	for (cs = 1; cs <= 16; cs++) {
		if (submask & msk) {
			if (flag == FLASH_FLAG_CRC) fnr = object_re_store_crc(index, cs);
			else fnr = object_re_store_write(index, cs);
			if (fnr != CAN_RETOK) return fnr;
		}
		msk <<= 1;
	}
	return CAN_RETOK;
}

static int16 prepare_read_flash_data(void)
{
	unsigned16 data;

	read_flash_variable(&data);
	if (data != CCITT_CRC_INITVALUE) {
		set_error_store_crc();
		return CAN_ERRET_RE_STORE;
	}
	can_start_crc(0);
	can_calc_crc((data >> 8) & 0xFF);
	can_calc_crc(data & 0xFF);
	return CAN_RETOK;
}

int16 get_re_store_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_STORE || index == CAN_INDEX_RE_STORE) {
		if (subind == 0) return sizeof(unsigned8);
		if (subind <= CAN_NOF_RESTORE_SUBINDS) return sizeof(unsigned32);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_re_store_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_re_store_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_MASK_ACCESS_RO;
	return CAN_MASK_ACCESS_RW;
}

int16 get_re_store_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_re_store_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_DEFTYPE_UNSIGNED8;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_re_store_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;
	unsigned32 store;

	size = get_re_store_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) {
		*data = CAN_NOF_RESTORE_SUBINDS;
	} else {
		if (index == CAN_INDEX_STORE) {
			if (subind == CAN_SUBIND_RESTORE_COBIDS) store = 0;
			else store = MASK_SAVE_ON_COMMAND;
		} else {
			store = MASK_LOAD_DEFAULT;
		}
		bpnt = (canbyte*)&store;
		OBJECT_DICTIONARY_TO_CANOPEN
	}
	return CAN_RETOK;
}

static int16 write_index_store(cansubind subind)	// 3.0.1 some changes
{
	int16 fnr;
	unsigned16 lm;

	lm = *(unsigned16*)PAGE_FLAG_RESMASK_ADDR;
	if (subind == CAN_SUBIND_RESTORE_ALL) {
		fnr = can_process_store_comm();
		if (fnr != CAN_RETOK) {
			lm &= ~(CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2);
			put_flash_flag(PAGE_FLAG_RESMASK_ADDR, lm);		// NO error check
			return fnr;
		}
		fnr = can_process_store_application();
		if (fnr != CAN_RETOK) {
			lm &= ~CAN_MASK_LOAD_APPL;
			put_flash_flag(PAGE_FLAG_RESMASK_ADDR, lm);		// NO error check
			return fnr;
		}
		fnr = put_flash_flag(PAGE_FLAG_RESMASK_ADDR, CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2 | CAN_MASK_LOAD_APPL);
		if (fnr != CAN_RETOK) return fnr;
		fnr = put_flash_nodeid(node_id);
		if (fnr != CAN_RETOK) return fnr;
		return put_flash_bitrate_index(bitrate_index);
	} else if (subind == CAN_SUBIND_RESTORE_COMMUNICATION) {
		fnr = can_process_store_comm();
		if (fnr != CAN_RETOK) {
			lm &= ~(CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2);
			put_flash_flag(PAGE_FLAG_RESMASK_ADDR, lm);		// NO error check
			return fnr;
		}
		lm |= CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2;
		return put_flash_flag(PAGE_FLAG_RESMASK_ADDR, lm);
	} else if (subind == CAN_SUBIND_RESTORE_APPLICATION) {
		fnr = can_process_store_application();
		if (fnr != CAN_RETOK) {
			lm &= ~CAN_MASK_LOAD_APPL;
			put_flash_flag(PAGE_FLAG_RESMASK_ADDR, lm);		// NO error check
			return fnr;
		}
		lm |= CAN_MASK_LOAD_APPL;
		return put_flash_flag(PAGE_FLAG_RESMASK_ADDR, lm);
	} else if (subind == CAN_SUBIND_RESTORE_COBIDS) {
		return CAN_ERRET_RE_STORE;
	} else if (subind == CAN_SUBIND_RESTORE_NODEID) {
		return put_flash_nodeid(node_id);
	} else if (subind == CAN_SUBIND_RESTORE_BITRATE) {
		return put_flash_bitrate_index(bitrate_index);
	}
	return CAN_ERRET_RE_STORE;
}

static int16 write_index_re_store(cansubind subind)
{
	int16 fnr;
	unsigned16 lm;

	lm = *(unsigned16*)PAGE_FLAG_RESMASK_ADDR;
	if (subind == CAN_SUBIND_RESTORE_ALL) {
		fnr = put_flash_flag(PAGE_FLAG_NODEID_ADDR, 0);
		if (fnr != CAN_RETOK) return fnr;
		fnr = put_flash_flag(PAGE_FLAG_BITRATE_ADDR, 0);
		if (fnr != CAN_RETOK) return fnr;
		return put_flash_flag(PAGE_FLAG_RESMASK_ADDR, 0);
	} else if (subind == CAN_SUBIND_RESTORE_COMMUNICATION) {
		lm &= ~(CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2);
		return put_flash_flag(PAGE_FLAG_RESMASK_ADDR, lm);
	} else if (subind == CAN_SUBIND_RESTORE_APPLICATION) {
		lm &= ~CAN_MASK_LOAD_APPL;
		return put_flash_flag(PAGE_FLAG_RESMASK_ADDR, lm);
	} else if (subind == CAN_SUBIND_RESTORE_COBIDS) {
		lm &= ~CAN_MASK_LOAD_COMM_2;
		return put_flash_flag(PAGE_FLAG_RESMASK_ADDR, lm);
	} else if (subind == CAN_SUBIND_RESTORE_NODEID) {
		return put_flash_flag(PAGE_FLAG_NODEID_ADDR, 0);
	} else if (subind == CAN_SUBIND_RESTORE_BITRATE) {
		return put_flash_flag(PAGE_FLAG_BITRATE_ADDR, 0);
	}
	return CAN_ERRET_RE_STORE;
}

int16 write_re_store_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size;

	size = get_re_store_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_ERRET_OBD_READONLY;
	if (index == CAN_INDEX_STORE) {
		if (data[0] != 's' || data[1] != 'a' || data[2] != 'v' || data[3] != 'e') return CAN_ERRET_SIGNATURE;
		return write_index_store(subind);
	} else {
		if (data[0] != 'l' || data[1] != 'o' || data[2] != 'a' || data[3] != 'd') return CAN_ERRET_SIGNATURE;
		return write_index_re_store(subind);
	}
}

int16 can_process_saved(unsigned16 mask)
{
	unsigned16 cob, data;
	int16 fnr;

	mask &= *(unsigned16*)PAGE_FLAG_RESMASK_ADDR;
	if (mask == 0) return CAN_RETOK;
	if (mask & CAN_MASK_LOAD_COMM_1) {
		flashaddr = PAGE_COMM_START_ADDR;
		minaddr = PAGE_COMM_START_ADDR;
		maxaddr = PAGE_COMM_END_ADDR;
		fnr = prepare_read_flash_data();
		if (fnr != CAN_RETOK) return fnr;
		for (cob = 0; cob < CAN_NOF_LOAD_COMM_1; cob++) {
			fnr = process_re_store(stc_1[cob].index, stc_1[cob].submask01, FLASH_FLAG_CRC);
			if (fnr != CAN_RETOK) return fnr;
		}
		read_flash_variable(&data);
		can_calc_crc((data >> 8) & 0xFF);
		if (can_calc_crc(data & 0xFF) != 0) {
			set_error_store_crc();
			return CAN_ERRET_RE_STORE;
		}
		flashaddr = PAGE_COMM_START_ADDR + sizeof(unsigned16);
		for (cob = 0; cob < CAN_NOF_LOAD_COMM_1; cob++) {
			fnr = process_re_store(stc_1[cob].index, stc_1[cob].submask01, FLASH_FLAG_WRITE_OBD);
			if (fnr != CAN_RETOK) return fnr;
		}
	}
	if (mask & CAN_MASK_LOAD_COMM_2) {
		flashaddr = PAGE_COMM_2_START_ADDR;
		minaddr = PAGE_COMM_2_START_ADDR;
		maxaddr = PAGE_COMM_END_ADDR;
		fnr = prepare_read_flash_data();
		if (fnr != CAN_RETOK) return fnr;
		for (cob = 0; cob < CAN_NOF_LOAD_COMM_2; cob++) {
			fnr = process_re_store(stc_2[cob].index, stc_2[cob].submask01, FLASH_FLAG_CRC);
			if (fnr != CAN_RETOK) return fnr;
		}
		read_flash_variable(&data);
		can_calc_crc((data >> 8) & 0xFF);
		if (can_calc_crc(data & 0xFF) != 0) {
			set_error_store_crc();
			return CAN_ERRET_RE_STORE;
		}
		flashaddr = PAGE_COMM_2_START_ADDR + sizeof(unsigned16);
		for (cob = 0; cob < CAN_NOF_LOAD_COMM_2; cob++) {
			fnr = process_re_store(stc_2[cob].index, stc_2[cob].submask01, FLASH_FLAG_WRITE_OBD);
			if (fnr != CAN_RETOK) return fnr;
		}
	}
	if (mask & CAN_MASK_LOAD_APPL) {
		flashaddr = PAGE_APPL_START_ADDR;
		minaddr = PAGE_APPL_START_ADDR;
		maxaddr = PAGE_APPL_END_ADDR;
		fnr = prepare_read_flash_data();
		if (fnr != CAN_RETOK) return fnr;
		for (cob = 0; cob < CAN_NOF_LOAD_APPL; cob++) {
			fnr = process_re_store(stap[cob].index, stap[cob].submask01, FLASH_FLAG_CRC);
			if (fnr != CAN_RETOK) return fnr;
		}
		read_flash_variable(&data);
		can_calc_crc((data >> 8) & 0xFF);
		if (can_calc_crc(data & 0xFF) != 0) {
			set_error_store_crc();
			return CAN_ERRET_RE_STORE;
		}
		flashaddr = PAGE_APPL_START_ADDR + sizeof(unsigned16);
		for (cob = 0; cob < CAN_NOF_LOAD_APPL; cob++) {
			fnr = process_re_store(stap[cob].index, stap[cob].submask01, FLASH_FLAG_WRITE_OBD);
			if (fnr != CAN_RETOK) return fnr;
		}
	}
	return CAN_RETOK;
}

int16 get_flash_nodeid(void)
{
	return get_flash_flag_data(PAGE_FLAG_NODEID_ADDR);
}

int16 get_flash_bitrate_index(void)
{
	return get_flash_flag_data(PAGE_FLAG_BITRATE_ADDR);
}

int16 put_flash_nodeid(cannode node)	// 2.2.1
{
	return put_flash_flag(PAGE_FLAG_NODEID_ADDR, (unsigned16)node | MASK_FLAG_VALUE_SET);
}

int16 put_flash_bitrate_index(unsigned8 br)		// 2.2.1
{
	return put_flash_flag(PAGE_FLAG_BITRATE_ADDR, (unsigned16)br | MASK_FLAG_VALUE_SET);
}

int16 check_init_flash(void)
{
	// Initialize flash controller here.

	if (*(unsigned16*)PAGE_FLAG_INITFLASH_ADDR == CCITT_CRC_INITVALUE) return CAN_RETOK;
	if (init_flash_page_flag() != CAN_RETOK) return CAN_ERRET_FLASH_INIT;
	*(unsigned16*)PAGE_FLAG_INITFLASH_ADDR = CCITT_CRC_INITVALUE;
	*(unsigned16*)PAGE_FLAG_RESMASK_ADDR = 0;
	*(unsigned16*)PAGE_FLAG_NODEID_ADDR = 0;
	*(unsigned16*)PAGE_FLAG_BITRATE_ADDR = 0;
	return CAN_RETOK;
}

void can_init_re_store(void)
{
	unsigned16 cnt;

	for (cnt = 0; cnt < CAN_NOF_LOAD_COMM_1; cnt++) {
		stc_1[cnt].index = CAN_INDEX_DUMMY;
		stc_1[cnt].submask01 = 0;
	}
	for (cnt = 0; cnt < CAN_NOF_LOAD_COMM_2; cnt++) {
		stc_2[cnt].index = CAN_INDEX_DUMMY;
		stc_2[cnt].submask01 = 0;
	}
	for (cnt = 0; cnt < CAN_NOF_LOAD_APPL; cnt++) {
		stap[cnt].index = CAN_INDEX_DUMMY;
		stap[cnt].submask01 = 0;
	}

	stc_1[0].index = 0x1019;	// Must be re-stored before 0x1006
	stc_1[1].index = 0x1006;
	stc_1[2].index = 0x1007;
	stc_1[3].index = 0x100C;
	stc_1[4].index = 0x100D;
	stc_1[5].index = 0x1015;
	stc_1[6].index = 0x1017;
	stc_1[7].index = 0x1029;
	stc_1[7].submask01 = 0x01;
	stc_1[8].index = 0x1400;
	stc_1[8].submask01 = 0x12;
	stc_1[9].index = 0x1401;
	stc_1[9].submask01 = 0x12;
	stc_1[10].index = 0x1402;
	stc_1[10].submask01 = 0x12;
	stc_1[11].index = 0x1403;
	stc_1[11].submask01 = 0x12;
	stc_1[12].index = 0x1600;
	stc_1[12].submask01 = 0xFF;
	stc_1[13].index = 0x1600;
	stc_1[14].index = 0x1601;
	stc_1[14].submask01 = 0xFF;
	stc_1[15].index = 0x1601;
	stc_1[16].index = 0x1602;
	stc_1[16].submask01 = 0xFF;
	stc_1[17].index = 0x1602;
	stc_1[18].index = 0x1603;
	stc_1[18].submask01 = 0xFF;
	stc_1[19].index = 0x1603;
	stc_1[20].index = 0x1800;
	stc_1[20].submask01 = 0x36;
	stc_1[21].index = 0x1801;
	stc_1[21].submask01 = 0x36;
	stc_1[22].index = 0x1802;
	stc_1[22].submask01 = 0x36;
	stc_1[23].index = 0x1803;
	stc_1[23].submask01 = 0x36;
	stc_1[24].index = 0x1A00;
	stc_1[24].submask01 = 0xFF;
	stc_1[25].index = 0x1A00;
	stc_1[26].index = 0x1A01;
	stc_1[26].submask01 = 0xFF;
	stc_1[27].index = 0x1A01;
	stc_1[28].index = 0x1A02;
	stc_1[28].submask01 = 0xFF;
	stc_1[29].index = 0x1A02;
	stc_1[30].index = 0x1A03;
	stc_1[30].submask01 = 0xFF;
	stc_1[31].index = 0x1A03;

	stc_2[0].index = 0x1005;
	stc_2[1].index = 0x1012;
	stc_2[2].index = 0x1014;
	stc_2[3].index = 0x1400;
	stc_2[3].submask01 = 0x01;
	stc_2[4].index = 0x1401;
	stc_2[4].submask01 = 0x01;
	stc_2[5].index = 0x1402;
	stc_2[5].submask01 = 0x01;
	stc_2[6].index = 0x1403;
	stc_2[6].submask01 = 0x01;
	stc_2[7].index = 0x1800;
	stc_2[7].submask01 = 0x01;
	stc_2[8].index = 0x1801;
	stc_2[8].submask01 = 0x01;
	stc_2[9].index = 0x1802;
	stc_2[9].submask01 = 0x01;
	stc_2[10].index = 0x1803;
	stc_2[10].submask01 = 0x01;

	stap[0].index = 0x2000;
	stap[0].submask01 = 0x7F;
}

#if CAN_APPLICATION_MODE == TEST

/*****
Find re-store data size volume.
The function can_test_re_store() is to be called
to determine actual size of non-volatile memory (EEPROM/FLASH),
which is necessary to (re)store all data.
The function is NOT needed to perform any further
(re)store operations.
*****/

void can_test_re_store(void)
{
	int16 fnr;

	can_init_re_store();

	printf("\n");
	fnr = can_process_store_comm();
	printf("can_process_store_comm(): ");
	if (fnr == 0) printf("OK\n");
	else printf("Error %-1i\n", fnr);
	fnr = can_process_store_application();
	printf("can_process_store_application(): ");
	if (fnr == 0) printf("OK\n");
	else printf("Error %-1i\n", fnr);

	printf("\n");
	put_flash_flag(PAGE_FLAG_RESMASK_ADDR, 0xFFFF);
	fnr = can_process_saved(CAN_MASK_LOAD_COMM_1);
	printf("can_process_saved(CAN_MASK_LOAD_COMM_1): ");
	if (fnr == 0) printf("OK, %-1i bytes\n", flashaddr-PAGE_COMM_START_ADDR+2);
	else printf("Error %-1i\n", fnr);
	fnr = can_process_saved(CAN_MASK_LOAD_COMM_2);
	printf("can_process_saved(CAN_MASK_LOAD_COMM_2): ");
	if (fnr == 0) printf("OK, %-1i bytes\n", flashaddr-PAGE_COMM_2_START_ADDR+2);
	else printf("Error %-1i\n", fnr);
	fnr = can_process_saved(CAN_MASK_LOAD_APPL);
	printf("can_process_saved(CAN_MASK_LOAD_APPL): ");
	if (fnr == 0) printf("OK, %-1i bytes\n", flashaddr-PAGE_APPL_START_ADDR+2);
	else printf("Error %-1i\n", fnr);

	printf("\n");
	fnr = can_process_saved(CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2 | CAN_MASK_LOAD_APPL);
	printf("can_process_saved() ALL parametes: ");
	if (fnr == 0) printf("OK\n");
	else printf("Error %-1i\n", fnr);
	fnr = can_process_saved(CAN_MASK_LOAD_COMM_1 | CAN_MASK_LOAD_COMM_2);
	printf("can_process_saved() COMM parameters: ");
	if (fnr == 0) printf("OK\n");
	else printf("Error %-1i\n", fnr);

}

#endif

#endif
#endif
#endif
