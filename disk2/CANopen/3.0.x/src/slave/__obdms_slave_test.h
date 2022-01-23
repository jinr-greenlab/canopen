// Test SLAVE/SERVER "manufacturer-specific" profile area object dictionary.
// See also:
// ../MASTER/__can_test_application.c (master/client test application);
// ../MASTER/__obdms_master_test.h (master/client test node-mirror object dictionary).

#define	STRINGLEN	51

static struct objdict {
	unsigned8 ch;
	int16 sh;
	unsigned32 in;
	int64 ln;
	real32 fl;
	real64 db;
	char st[STRINGLEN];
	char reset[4];
} test;
// Object dictionary physical presentation.

int16 application_0x2048(void)
{
	if (test.reset[0] == 'I' && test.reset[1] == 'n' && test.reset[2] == 'i' && test.reset[3] == 't') {
		slave_init_manstan_application();
		return CAN_RETOK;
	}
	return CAN_RETOK;	// Only to pass CANopen conformance test 
//	return CAN_ERRET_SIGNATURE;
}
// The application routines are called when some object dictionary entries are read or written.
// With application_0x2048(..) function, object dictionary is (re)initialized when the
// word 'Init' is written into the dictionary index 0x2048, sub-index 0 entry.

int32 server_get_manstan_objsize(canindex index, cansubind subind, int16 unit)
{
	int32 size;

	size = CAN_ERRET_OBD_NOOBJECT;
	if (index == 0x2000 || index == 0x2001) {
		switch (subind) {
			case 0: size = sizeof(unsigned8); break;
			case 1: size = sizeof(test.ch); break;
			case 2: size = sizeof(test.sh); break;
			case 3: size = sizeof(test.in); break;
			case 4: size = sizeof(test.ln); break;
			case 5: size = sizeof(test.fl); break;
			case 6: size = sizeof(test.db); break;
			case 7: size = sizeof(test.st); break;
			default: size = CAN_ERRET_OBD_NOSUBIND; break;
		}
	} else if (index == 0x2048) {
		if (subind == 0) size = sizeof(test.reset);
		else size = CAN_ERRET_OBD_NOSUBIND;
	}
	if (size < 0 || unit == BYTES) return size;
	return size * CAN_SIZEOF_FACTOR;
}
// The function server_get_manstan_objsize(..) returns server object dictionary
// entry size, expressed either in bytes (unit == BYTES) or in bits (unit == BITS).
// The function is reference one for defining object dictionary entry existence.
// Bit object size is used to form bit-oriented PDO mapping.
// Two indexes are used for the same object in order to separate
// receive and transmit PDOs.

canbyte *server_get_manstan_objpointer(canindex index, cansubind subind)
{
	if (index == 0x2000 || index == 0x2001) {
		switch (subind) {
			case 1: return (canbyte*)&test.ch;
			case 2: return (canbyte*)&test.sh;
			case 3: return (canbyte*)&test.in;
			case 4: return (canbyte*)&test.ln;
			case 5: return (canbyte*)&test.fl;
			case 6: return (canbyte*)&test.db;
			case 7: return (canbyte*)test.st;
		}
	} else if (index == 0x2048) {
		if (subind == 0) return (canbyte*)test.reset;
	}
	return NULL;
}
// The function server_get_manstan_objpointer(..) is used to obtain byte pointer
// to the server object dictionary entry.
// If an object can't be addressed with the poiner, NULL is returned.
// The pointer is also used for block data transfer protocols, as they can
// read or write object dictionary entries directly - without buffering.

int16 server_see_manstan_access(canindex index, cansubind subind)
{
	int32 size;

	size = server_get_manstan_objsize(index, subind, BYTES);
	if (size <= 0) return (int16)size;
	if (index == 0x2048) return CAN_MASK_ACCESS_WO;
	if (subind == 0) return CAN_MASK_ACCESS_RO;
	if (subind <= 6) return CAN_MASK_ACCESS_PDO | CAN_MASK_ACCESS_RW;
	return CAN_MASK_ACCESS_RW;
}
// The function server_see_manstan_access(..) returns
// server object dictionary entries access type as a bitwise mask.
// CAN_MASK_ACCESS_RO - read access
// CAN_MASK_ACCESS_WO - write access
// CAN_MASK_ACCESS_PDO - PDO mapping supported

int16 server_get_manstan_objtype(canindex index, cansubind subind)
{
	int32 size;

	size = server_get_manstan_objsize(index, subind, BYTES);
	if (size <= 0) return (int16)size;
	if (index == 0x2000 || index == 0x2001) {
		switch (subind) {
			case 0: return CAN_DEFTYPE_UNSIGNED8;
			case 1: return CAN_DEFTYPE_UNSIGNED8;
			case 2: return CAN_DEFTYPE_INTEGER16;
			case 3: return CAN_DEFTYPE_UNSIGNED32;
			case 4: return CAN_DEFTYPE_UNSIGNED64;
			case 5: return CAN_DEFTYPE_REAL32;
			case 6: return CAN_DEFTYPE_REAL64;
		}
	}
	return CAN_DEFTYPE_VISIBLE_STRING;
}
// The function server_get_manstan_objtype(..) returns
// server object dictionary entries data types.

int16 server_read_manstan_objdict(canindex index, cansubind subind, canbyte *data)
{
	int32 size, cnt;
	canbyte *bpnt;

	size = server_get_manstan_objsize(index, subind, BYTES);
	if (size <= 0) return (int16)size;
	if (index == 0x2048) return CAN_ERRET_OBD_WRITEONLY;
	if (subind == 0) {
		*data = 7;
		return CAN_RETOK;
	}
	bpnt = server_get_manstan_objpointer(index, subind);
	if (bpnt == NULL) return CAN_ERRET_NULL_POINTER;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}
// The function server_read_manstan_objdict(..) reads server object
// dictionary entry into byte-pointered *data.
// The entry size in bytes is requested with server_get_manstan_objsize(..) function.

int16 server_write_manstan_objdict(canindex index, cansubind subind, canbyte *data)
{
	int32 size, cnt;
	canbyte *bpnt;

	size = server_get_manstan_objsize(index, subind, BYTES);
	if (size <= 0) return (int16)size;
	if (index == 0x2000 || index == 0x2001) {
		if (subind == 0) return CAN_ERRET_OBD_READONLY;
	}
	bpnt = server_get_manstan_objpointer(index, subind);
	if (bpnt == NULL) return CAN_ERRET_NULL_POINTER;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (index == 0x2048) return application_0x2048();
	return CAN_RETOK;
}
// The function server_write_manstan_objdict(..) writes byte-pointered *data
// into server object dictionary entry.
// The entry size in bytes is requested with server_get_manstan_objsize(..) function.

void slave_init_manstan_application(void)
{
	int32 cnt;

	test.ch = 21;
	test.sh = -2339;
	test.in = 555777333;
	test.ln = 8877665544332211;
	test.fl = (float)-90.0123;
	test.db = 0.9876;
	for (cnt = 0; cnt < STRINGLEN; cnt++) test.st[cnt] = '\0';
	test.st[0] = 'S'; test.st[1] = 'E'; test.st[2] = 'R';
	test.st[3] = 'V'; test.st[4] = 'E'; test.st[5] = 'R';
	for (cnt = 0; cnt < 4; cnt++) test.reset[cnt] = '\0';
}
// The function server_init_manstan_application(..) initializes server application (object dictionary).

void slave_init_manstan_communication(void)
{
	#if CAN_APPLICATION_MODE == SLAVE
	server_write_obd_u32(0x1400, 0x2, 255);
	server_write_obd_u32(0x1401, 0x2, 255);
	server_write_obd_u32(0x1402, 0x2, 255);
	server_write_obd_u32(0x1403, 0x2, 255);
	server_write_obd_u32(0x1600, 0x1, 0x20000108);
	server_write_obd_u32(0x1600, 0x2, 0x20000520);
	server_write_obd_u32(0x1600, 0x3, 0x20000210);
	server_write_obd_u32(0x1600, 0, 3);
	server_write_obd_u32(0x1601, 0x1, 0x20000320);
	server_write_obd_u32(0x1601, 0, 1);
	server_write_obd_u32(0x1602, 0x1, 0x20000440);
	server_write_obd_u32(0x1602, 0, 1);
	server_write_obd_u32(0x1603, 0x1, 0x20000640);
	server_write_obd_u32(0x1603, 0, 1);
	set_pdo_state(0x1400, VALID);
	set_pdo_state(0x1401, VALID);
	set_pdo_state(0x1402, VALID);
	set_pdo_state(0x1403, VALID);
	server_write_obd_u32(0x1800, 0x2, 4);
	server_write_obd_u32(0x1801, 0x2, 10);
	server_write_obd_u32(0x1802, 0x2, 16);
	server_write_obd_u32(0x1803, 0x2, 28);
	server_write_obd_u32(0x1A00, 0x1, 0x20010108);
	server_write_obd_u32(0x1A00, 0x2, 0x20010520);
	server_write_obd_u32(0x1A00, 0x3, 0x20010210);
	server_write_obd_u32(0x1A00, 0, 3);
	server_write_obd_u32(0x1A01, 0x1, 0x20010320);
	server_write_obd_u32(0x1A01, 0, 1);
	server_write_obd_u32(0x1A02, 0x1, 0x20010440);
	server_write_obd_u32(0x1A02, 0, 1);
	server_write_obd_u32(0x1A03, 0x1, 0x20010640);
	server_write_obd_u32(0x1A03, 0, 1);
	set_pdo_state(0x1800, VALID);
	set_pdo_state(0x1801, VALID);
	set_pdo_state(0x1802, VALID);
	set_pdo_state(0x1803, VALID);
	#endif
}
// The function server_init_manstan_communication(..) initializes (configures) server
// communication objects - default PDO values.
