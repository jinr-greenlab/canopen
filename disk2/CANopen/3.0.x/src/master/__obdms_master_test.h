// Test MASTER/CLIENT "manufacturer-specific" profile area node-mirror object dictionary.
// See also:
// ../MASTER/__can_test_application.c (master/client test application);
// ../SLAVE/__obdms_slave_test.h (slave/server test object dictionary).

#define	STRINGLEN	51

static struct objdict {
	unsigned8 ch;
	int16 sh;
	unsigned32 in;
	int64 ln;
	real32 fl;
	real64 db;
	char st[STRINGLEN];
} test;
// Object dictionary physical presentation.

int32 test_get_manstan_objsize(canindex index, cansubind subind, int16 unit)
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
	}
	if (size < 0 || unit == BYTES) return size;
	return size * CAN_SIZEOF_FACTOR;
}
// The function test_get_manstan_objsize(...) returns node-mirror object dictionary
// entry size, expressed either in bytes (unit == BYTES) or in bits (unit == BITS).
// The function is reference one for defining object dictionary entry existence.
// Bit object size is used to form bit-oriented PDO mapping.
// Two indexes are used for the same object in order to separate
// receive and transmit PDOs.

canbyte *test_get_manstan_objpointer(canindex index, cansubind subind)
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
	}
	return NULL;
}
// The function test_get_manstan_objpointer(...) is used to obtain byte pointer
// to the node-mirror object dictionary entry.
// If an object can't be addressed with the poiner, NULL is returned.
// The pointer is also used for block data transfer protocols, as they can
// read or write object dictionary entries directly - without buffering.

int16 test_see_manstan_access(canindex index, cansubind subind)
{
	int32 size;

	size = test_get_manstan_objsize(index, subind, BYTES);
	if (size <= 0) return (int16)size;
	if (subind == 0) return CAN_MASK_ACCESS_RO;
	if (subind <= 6) return CAN_MASK_ACCESS_PDO | CAN_MASK_ACCESS_RW;
	return CAN_MASK_ACCESS_RW;
}
// The function client_see_manstan_pdomap(index, subindex) defines,
// whether the node-mirror object dictionary entry can be mapped into a PDO.

int16 test_get_manstan_objtype(canindex index, cansubind subind)
{
	int32 size;

	size = test_get_manstan_objsize(index, subind, BYTES);
	if (size <= 0) return (int16)size;
	switch (subind) {
		case 2: return CAN_DEFTYPE_INTEGER16;
		case 3: return CAN_DEFTYPE_UNSIGNED32;
		case 4: return CAN_DEFTYPE_UNSIGNED64;
		case 5: return CAN_DEFTYPE_REAL32;
		case 6: return CAN_DEFTYPE_REAL64;
		case 7: return CAN_DEFTYPE_VISIBLE_STRING;
	}
	return CAN_DEFTYPE_UNSIGNED8;
}

int16 test_read_manstan_objdict(canindex index, cansubind subind, canbyte *data)
{
	int32 size, cnt;
	canbyte *bpnt;

	size = test_get_manstan_objsize(index, subind, BYTES);
	if (size <= 0) return (int16)size;
	if (index == 0x2048) return CAN_ERRET_OBD_WRITEONLY;
	if (subind == 0) {
		*data = 7;
		return CAN_RETOK;
	}
	bpnt = test_get_manstan_objpointer(index, subind);
	if (bpnt == NULL) return CAN_ERRET_NULL_POINTER;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}
// The function test_read_manstan_objdict(index, subindex, *data) reads
// node-mirror object dictionary entry into byte-pointered *data.
// The entry size in bytes is requested with test_get_manstan_objsize(index, subindex) function.
// Object dictionary index 0x2048 write only entry is used for the server
// application object dictionary (re)initialization.

int16 test_write_manstan_objdict(canindex index, cansubind subind, canbyte *data)
{
	int32 size, cnt;
	canbyte *bpnt;

	size = test_get_manstan_objsize(index, subind, BYTES);
	if (size <= 0) return (int16)size;
	if (subind == 0) return CAN_ERRET_OBD_READONLY;
	bpnt = test_get_manstan_objpointer(index, subind);
	if (bpnt == NULL) return CAN_ERRET_NULL_POINTER;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	return CAN_RETOK;
}
// The function test_write_manstan_objdict(index, subindex, *data) writes
// byte-pointered *data into node-mirror object dictionary entry.
// The entry size in bytes is requested with test_get_manstan_objsize(index, subindex)
// function.

static void test_init_application(void)
{
	test.ch = 211;
	test.sh = -21077;
	test.in = 1234567890;
	test.ln = -123456789123456789;
	test.fl = (float)-13579.24;
	test.db = 2468024680.13579;
	strncpy(test.st, "The object dictionary SDO transfer test.....................", STRINGLEN-1);
	test.st[STRINGLEN-1] = '\0';
	printf("\nTest node-mirror object dictionary INITIALIZED \n\n");
}
// The function test_init_application(...) initializes node-mirror application (object dictionary).

static void test_init_communication(void)
{
}
// The function test_init_communication(...) initializes (configures) node-mirror communication objects.
