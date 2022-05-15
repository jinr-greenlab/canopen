#include <master_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 1)

#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

static unsigned8 erreg;
static unsigned8 numerr;
static unsigned32 predeferr[CAN_NOF_PREDEF_ERRORS];
static unsigned8 headerr;
static int16 sem_error, flag_error;		// 2.3.3

int16 get_err_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_ERROR_REG) {
		if (subind == 0) return sizeof(erreg);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	if (index == CAN_INDEX_PREDEF_ERROR) {
		if (subind == 0) return sizeof(unsigned8);
		if (subind <= CAN_NOF_PREDEF_ERRORS) return sizeof(unsigned32);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_err_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_err_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_ERROR_REG) return CAN_MASK_ACCESS_PDO | CAN_MASK_ACCESS_RO;
	if (subind == 0) return CAN_MASK_ACCESS_RW;
	return CAN_MASK_ACCESS_RO;
}

int16 get_err_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_err_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (subind == 0) return CAN_DEFTYPE_UNSIGNED8;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_err_objdict(canindex index, cansubind subind, canbyte *data)	// 2.2.1 some changes
{
	int16 size, cnt, errn;
	unsigned32 buf;
	canbyte *bpnt;

	size = get_err_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_ERROR_REG) {
		bpnt = (canbyte*)&erreg;
	} else {
		bpnt = (canbyte*)&buf;
		#if CAN_BYTE_ORDER == REVERSE
			bpnt += (sizeof(buf) - size);	// 2.3.1
		#endif
		buf = numerr;
		if (buf > CAN_NOF_PREDEF_ERRORS) buf = 0;
		if (subind != 0) {
			if (subind > buf) return CAN_ERRET_OBD_NODATA;
			do {
				flag_error = 0;
				errn = headerr - subind + 1;
				if (errn < 0) errn += CAN_NOF_PREDEF_ERRORS;
				buf = predeferr[errn];
			} while (flag_error != 0);
		}
	}
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_err_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size;

	size = get_err_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_ERROR_REG) return CAN_ERRET_OBD_READONLY;
	if (subind != 0) return CAN_ERRET_OBD_READONLY;
	if (*data != 0) return CAN_ERRET_OBD_VALRANGE;
	numerr = 0;
	return CAN_RETOK;
}

void set_error_field(unsigned16 errorcode, unsigned16 addinf)
{
	unsigned8 h;

	if (errorcode == CAN_EMCY_NO_ERROR) {
		erreg = 0;
		return;
	}
	sem_error++;
	if (sem_error == 0) {
		if (numerr == CAN_NOF_PREDEF_ERRORS) numerr--;
		h = headerr + 1;
		if (h >= CAN_NOF_PREDEF_ERRORS) h = 0;
		predeferr[h] = ((unsigned32)addinf << 16) | errorcode;
		headerr = h;
		numerr++;
		flag_error = 1;
	}
	sem_error--;
	errorcode &= 0xFF00;				// 2.3.4
	if (errorcode == 0x0000) return;	// 2.3.2
	erreg |= CAN_ERRBIT_GENERIC;
	if (errorcode == 0x1000) return;
	errorcode &= 0xF000;
	if (errorcode == 0x2000) erreg |= CAN_ERRBIT_CURRENT;
	else if (errorcode == 0x3000) erreg |= CAN_ERRBIT_VOLTAGE;
	else if (errorcode == 0x4000) erreg |= CAN_ERRBIT_TEMP;
	else if (errorcode == 0x5000) erreg |= CAN_ERRBIT_MANSPEC;
	else if (errorcode == 0x6000) erreg |= CAN_ERRBIT_MANSPEC;
	else if (errorcode == 0x8000) erreg |= CAN_ERRBIT_COMM;
	else if (errorcode == 0xF000) erreg |= CAN_ERRBIT_MANSPEC;
	else erreg |= CAN_ERRBIT_PROFILE;
}

void clear_error_register(unsigned8 mask)
{
	if (erreg == 0) return;
	erreg &= ~(mask & CAN_MASK_ANY_ERROR);
	if ((erreg & CAN_MASK_ANY_ERROR) == 0) {
		erreg = 0;
	#if CAN_OBJECT_EMCY == TRUE
		produce_emcy_default(CAN_EMCY_NO_ERROR);
	#endif
	}
}

unsigned8 read_error_register(void)
{
	return erreg;
}

void can_init_error(void)
{
	int16 cnt;

	erreg = 0;
	numerr = 0;
	headerr = 0;
	flag_error = 0;
	for (cnt = 0; cnt < CAN_NOF_PREDEF_ERRORS; cnt++) predeferr[cnt] = 0;
	sem_error = 0;
	if (CAN_NOF_PREDEF_ERRORS > 0 && CAN_NOF_PREDEF_ERRORS <= 254) sem_error = -1;
}

#elif CAN_APPLICATION_MODE == MASTER

void set_error_field(unsigned16 errorcode, unsigned16 addinf)
{
#if CAN_OBJECT_EMCY == TRUE
	master_emcy(errorcode);		// 2.3.3
#endif
}

#endif

#endif
