#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 2)
//  CHECK_VERSION(2, 2, 0)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 2)
//  CHECK_VERSION(1, 7, 1)

#if (CAN_APPLICATION_MODE == MASTER && CAN_SLAVE_DEVICE_CLASS == CAN_DEVICE_TEST) || CAN_APPLICATION_MODE == TEST

// The master test device module executes various test operations with master/client and
// slave/server object dictionaries, including "manufacturer-specific" profile area.
// In order to separate test application from operational ones, access to the
// test node-mirror object dictionary is supported directly from this module.
// See also:
// ../MASTER/__obdms_master_test.h (master/client test node-mirror object dictionary);
// ../SLAVE/__obdms_slave_test.h (slave/server test object dictionary).
//
// Besides comments, see also printf(...) operators as special events description.
//

static unsigned16 initcnt;
static canindex sdo_index;
static cannode test_node;

#include "__obdms_master_test.h"

canbyte *node_get_manstan_objpointer(cannode node, canindex index, cansubind subind)
{
	return test_get_manstan_objpointer(index, subind);
}

int16 node_see_manstan_access(cannode node, canindex index, cansubind subind)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return see_deftype_access(index, subind);
	}
	return test_see_manstan_access(index, subind);
}

int32 node_get_manstan_objsize(cannode node, canindex index, cansubind subind, int16 unit)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return get_deftype_objsize(index, subind, unit);
	}
	return test_get_manstan_objsize(index, subind, unit);
}

int16 node_get_manstan_objtype(cannode node, canindex index, cansubind subind)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return get_deftype_objtype(index, subind);
	}
	return test_get_manstan_objtype(index, subind);
}

int16 node_read_manstan_objdict(cannode node, canindex index, cansubind subind, canbyte *data)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return read_deftype_objdict(index, subind, data);
	}
	return test_read_manstan_objdict(index, subind, data);
}

int16 node_write_manstan_objdict(cannode node, canindex index, cansubind subind, canbyte *data)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) {
		return write_deftype_objdict(index, subind, data);
	}
	return test_write_manstan_objdict(index, subind, data);
}

void master_init_manstan_application(void)
{
	test_init_application();	// Reinitializing node-mirror object dictionary.
}

void master_init_manstan_communication(void)
{
	test_init_communication();
}

static void test_show_object_dictionary(void)
{
	unsigned8 ch;
	int16 sh;
	unsigned32 in;
	int64 ln;
	real32 fl;
	real64 db;
	char st[51];
	unsigned16 cnt;
	char unp[22], sig;

	node_read_manstan_objdict(0, 0x2000, 1, (canbyte*)&ch);
	node_read_manstan_objdict(0, 0x2000, 2, (canbyte*)&sh);
	node_read_manstan_objdict(0, 0x2000, 3, (canbyte*)&in);
	node_read_manstan_objdict(0, 0x2000, 4, (canbyte*)&ln);
	node_read_manstan_objdict(0, 0x2000, 5, (canbyte*)&fl);
	node_read_manstan_objdict(0, 0x2000, 6, (canbyte*)&db);
	node_read_manstan_objdict(0, 0x2000, 7, (canbyte*)st);
	if (ln < 0) { sig = '-'; ln = -ln; }
	else if (ln == 0) sig = '0';
	else sig = ' ';
	for (cnt = 0; cnt <= 20; cnt++) unp[cnt] = ' ';
	unp[21] = '\0';
	for (cnt = 20; cnt > 0; cnt--) {
		if (ln == 0) break;
		unp[cnt] = (char)('0' + ln%10);
		ln /= 10;
	}
	unp[cnt] = sig;
	printf("------  Test node-mirror object dictionary  ------\n");
	printf("%6i %8i %12i %s\n", ch, sh, in, unp);
	printf("%16.4f %30.5f\n", fl, db);
	printf("%s \n", st);
	printf("--------------------------------------------------\n");
}

int16 load_device_object(unsigned8 oper, canindex index, cansubind subind, canbyte *data, unsigned32 datasize)
{
	struct sdocltappl ca;

	ca.operation = oper;			// Transfer transaction mode
									// After the transfer call, keeps the operation code actually used by the transaction:
									// CAN_SDOPER_(UP / DOWN)_EXPEDITED or
									// CAN_SDOPER_(UP / DOWN)_SEGMENTED or
									// CAN_SDOPER_(UP / DOWN)_BLOCK.
									// UPload or DOWNload modes themselves are NEVER changed.
	ca.si.sdoind = CAN_INDEX_CLIENT_SDO_MIN+test_node-1;	// Client SDO communication parameter index.
	ca.si.index =  index;			// Application object dictionary entry index.
	ca.si.subind = subind;			// Application object dictionary entry sub-index.
	ca.datapnt = data;				// Local data pointer. If NULL, the data is transferred between
									// server object dictionary and its node-mirror one.
	ca.datasize = datasize;			// If ca.datapnt is NOT NULL, the data size in bytes has also to be specified.
	can_sdo_client_transfer(&ca);	// Client transfer transaction call.
	can_client_state(&ca);			// The transaction results diagnostics.
	return ca.ss.state;
}

static void transfer_obd(unsigned8 oper)	// Test object dictionary transfers.
{
	load_device_object(oper, 0x2000, 1, NULL, 0);
	load_device_object(oper, 0x2000, 2, NULL, 0);
	load_device_object(oper, 0x2000, 3, NULL, 0);
	load_device_object(oper, 0x2000, 4, NULL, 0);
	load_device_object(oper, 0x2000, 5, NULL, 0);
	load_device_object(oper, 0x2000, 6, NULL, 0);
	load_device_object(oper, 0x2000, 7, NULL, 0);
}

static void read_server_specs(void)		// Reading server/slave device specifications.
{
	char str[CAN_LEN_VISIBLE_STRING];
	unsigned32 data;
	int16 state;

	printf("\n***** Reading server/slave specifications:\n");

	state = load_device_object(CAN_SDOPER_UPLOAD, 0x1000, 0, (canbyte*)&data, sizeof(unsigned32));
	if (state == CAN_TRANSTATE_OK) printf("Device type (0x1000):  0x%08X\n", canframe_to_u32((canbyte*)&data));

	state = load_device_object(CAN_SDOPER_UPLOAD, 0x1002, 0, (canbyte*)&data, sizeof(unsigned32));
	if (state == CAN_TRANSTATE_OK) printf("Manufacturer status register (0x1002):  0x%08X\n", canframe_to_u32((canbyte*)&data));

	state = load_device_object(CAN_SDOPER_UPLOAD, 0x1008, 0, (canbyte*)str, sizeof(str));
	if (state == CAN_TRANSTATE_OK) printf("Manufacturer device name (0x1008):  %s\n", str);
	state = load_device_object(CAN_SDOPER_UPLOAD, 0x1009, 0, (canbyte*)str, sizeof(str));
	if (state == CAN_TRANSTATE_OK) printf("Manufacturer hardware version (0x1009):  %s\n", str);
	state = load_device_object(CAN_SDOPER_UPLOAD, 0x100A, 0, (canbyte*)str, sizeof(str));
	if (state == CAN_TRANSTATE_OK) printf("Manufacturer software version (0x100A):  %s\n", str);
	
	state = load_device_object(CAN_SDOPER_UPLOAD, 0x1018, 1, (canbyte*)&data, sizeof(unsigned32));
	if (state == CAN_TRANSTATE_OK) printf("Vendor ID (0x1018/1):  0x%08X\n", canframe_to_u32((canbyte*)&data));
	state = load_device_object(CAN_SDOPER_UPLOAD, 0x1018, 2, (canbyte*)&data, sizeof(unsigned32));
	if (state == CAN_TRANSTATE_OK) printf("Product code (0x1018/2):  0x%08X\n", canframe_to_u32((canbyte*)&data));
	state = load_device_object(CAN_SDOPER_UPLOAD, 0x1018, 3, (canbyte*)&data, sizeof(unsigned32));
	if (state == CAN_TRANSTATE_OK) printf("Revision number (0x1018/3):  0x%08X\n", canframe_to_u32((canbyte*)&data));
	state = load_device_object(CAN_SDOPER_UPLOAD, 0x1018, 4, (canbyte*)&data, sizeof(unsigned32));
	if (state == CAN_TRANSTATE_OK) printf("Serial number (0x1018/4):  0x%08X\n", canframe_to_u32((canbyte*)&data));

	printf("\n");
}

static void test_obd_sdo_transfer(void)	// Test object dictionary manipulations.
{
	char str[4];

	read_server_specs();

	can_sleep(5000000);

	test_show_object_dictionary();
	printf("\n***** UPload server test object dictionary.\n\n");
	transfer_obd(CAN_SDOPER_UPLOAD);
	test_show_object_dictionary();

	printf("\n***** Attempt to read (upload) write-only object.\n");
	printf("***** Abort code 0x06010001 (attempt to read a write-only object) has to be receiver from the server.\n");
	load_device_object(CAN_SDOPER_UPLOAD, 0x2048, 0, (canbyte*)str, sizeof(str));

	printf("\n***** Attempt to read (upload) non-existent object.\n");
	printf("***** Abort code 0x06020000 (object does not exist in the object dictionary) has to be receiver from the server.\n");
	load_device_object(CAN_SDOPER_UPLOAD, 0x2002, 1, (canbyte*)str, sizeof(str));

	printf("\n***** Attempt to read (upload) non-existent object.\n");
	printf("***** Abort code 0x06090011 (sub-index does not exist) has to be receiver from the server.\n");
	load_device_object(CAN_SDOPER_UPLOAD, 0x2000, 9, (canbyte*)str, sizeof(str));

	can_sleep(5000000);

	master_init_manstan_application();	// Reinitializing node-mirror object dictionary.

	test_show_object_dictionary();
	printf("\n***** DOWNload node-mirror test object dictionary.\n\n");
	transfer_obd(CAN_SDOPER_DOWNLOAD);
	test_show_object_dictionary();
	printf("\n***** UPload server test object dictionary.\n\n");
	transfer_obd(CAN_SDOPER_UPLOAD);
	test_show_object_dictionary();

	can_sleep(5000000);

	printf("\n***** RE-initializing SLAVE object dictionary.\n");
	str[0] = 'I'; str[1] = 'n'; str[2] = 'i'; str[3] = 't';
	load_device_object(CAN_SDOPER_DOWNLOAD, 0x2048, 0, (canbyte*)str, sizeof(str));

	printf("\n***** UPload server test object dictionary.\n\n");
	transfer_obd(CAN_SDOPER_UPLOAD);
	test_show_object_dictionary();
}

static void configure_sync(void)	// SYNC and NMT object configuration.
{
	int16 fnr;
	unsigned32 buf;
	unsigned32 data;

	fnr = client_write_obd_u32(0, CAN_INDEX_SYNC_OVERFLOW, 0, 0);			// SYNC overflow counter set.
	fnr = client_write_obd_u32(0, CAN_INDEX_SYNC_PERIOD, 0, 1000000);		// SYNC period is set to one second.
//	fnr = client_write_obd_u32(0, CAN_INDEX_SYNC_PERIOD, 0, 100000);		// SYNC period is set to 0.1 second. To check TPDO inhibit.
	fnr = client_write_obd_u32(0, CAN_INDEX_SYNC_COBID, 0, 0x40000080);		// SYNC message will be produced with 0x80 COBID.
//	Master SYNC configuration.

	u16_to_canframe(0x6A4, (canbyte*)&data);	// Slave (producer) heartbeat time will be 1700 milliseconds.
									// The bytes order is converted to the CAN frame transfer sequence.
	load_device_object(CAN_SDOPER_DOWNLOAD, CAN_INDEX_PROD_HBT, 0, (canbyte*)&data, 2);

	//	Slave heartbeat configuration. Heartbeat protocol is of higher priority, then node guarding one.

	buf = ((unsigned32)test_node << 16) + 0x8CA;
	fnr = client_write_obd_u32(0, CAN_INDEX_CONS_HBT, 1, buf);	// Master heartbeat configuration.
//	Consumer heartbeat time for the [test_node] (the above slave) is set to 2250 ms.
//	Sub-index 1 of the consumer heartbeat time object is used for the purpose.
//	The sub-index is now responsible for configuration of all master error control protocols for the [test_node] node.

	u16_to_canframe(0x5DC, (canbyte*)&data);	// Slave guard time is set to 1500 ms.
	load_device_object(CAN_SDOPER_DOWNLOAD, CAN_INDEX_GUARD_TIME, 0, (canbyte*)&data, 2);

	data = 2;		// Slave life time factor is 2.
	load_device_object(CAN_SDOPER_DOWNLOAD, CAN_INDEX_LIFETIME_FACTOR, 0, (canbyte*)&data, 1);
//	Slave node guarding configuration. Node guarding protocol is of lower priority, then the heartbeat one.

	fnr = client_write_obd_u32(0, CAN_INDEX_GUARD_TIME, 1, 0x5DC);
	fnr = client_write_obd_u32(0, CAN_INDEX_LIFETIME_FACTOR, 1, 2);
//	Master node guard time for the node, stored in the sub-index 1 is set to 1500 ms.
//	The node was stored by the above consumer heartbeat time configuration.
//	Master life time factor for the node is 2.

//	To actuate node guarding protocol, heartbeat must to be supressed.

	u16_to_canframe(0x0, (canbyte*)&data);		// Slave heartbeat time is zeroed, supressing the heartbeat producer.
//	load_device_object(CAN_SDOPER_DOWNLOAD, CAN_INDEX_PROD_HBT, 0, (canbyte*)&data, 2);

//	buf = ((unsigned32)test_node << 16);
//	fnr = client_write_obd_u32(0, CAN_INDEX_CONS_HBT, 1, buf);
//	Master heartbeat time for sub-index 1 is zeroed, supressing the heartbeat consumer.
//	So, node guarding protocol is used.
//	It is also possible now to change consumer heartbeat time object sub-index,
//	responsible for configuration of all master error control protocols for the [test_node] node.

	printf("\n***** SYNC and NMT configured.\n");
}

static void configure_pdo(void)	// Master receive and slave transmit PDOs re-configuration.
{
	unsigned16 cnt;
	cansubind sub;
	int16 fnr;
	canindex trnpdo_map, trnpdo_comm, rcvpdo_map, rcvpdo_comm;
	unsigned32 data;

	rcvpdo_map = CAN_INDEX_RCVPDO_MAP_MIN + 4*(test_node-1);
	rcvpdo_comm = CAN_INDEX_RCVPDO_COMM_MIN + 4*(test_node-1);
	trnpdo_map = CAN_INDEX_TRNPDO_MAP_MIN;
	trnpdo_comm = CAN_INDEX_TRNPDO_COMM_MIN;
	#if CAN_APPLICATION_MODE == TEST
	trnpdo_map += 4*(test_node-1);
	trnpdo_comm += 4*(test_node-1);
	#endif

	data = 0;
	for (cnt = 0; cnt < 4; cnt++) {
		load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_map+cnt), 0, (canbyte*)&data, 1);
		fnr = client_write_obd_u32(0, (canindex)(rcvpdo_map+cnt), 0, 0);
	}
	// For changing PDOs mapping, they are to be deactivated (become invalid).
	// 4 master receive and 4 slave transmit PDOs mapping is deactivated
	// by setting 0 to sub-index 0 of the mapping parameters.
	// PDO COB-IDs becomes invalid


	u32_to_canframe(0x20010108, (canbyte*)&data);		// The bytes order is converted to the CAN frame transfer sequence.
	load_device_object(CAN_SDOPER_DOWNLOAD, trnpdo_map, 1, (canbyte*)&data, 4);
	fnr = client_write_obd_u32(0, rcvpdo_map, 1, 0x20010108);
	// First transmit and receive PDOs mapping.
	// Application object: index 0x2001 sub-index 1 (type unsigned char, 8 bits) is mapped.

	u32_to_canframe(0x20010520, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, trnpdo_map, 2, (canbyte*)&data, 4);
	fnr = client_write_obd_u32(0, rcvpdo_map, 2, 0x20010520);
	// First transmit and receive PDOs mapping.
	// Application object: index 0x2001 sub-index 5 (type float, 32 bits) is mapped.

	u32_to_canframe(0x20010210, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, trnpdo_map, 3, (canbyte*)&data, 4);
	fnr = client_write_obd_u32(0, rcvpdo_map, 3, 0x20010210);
	// First transmit and receive PDOs mapping.
	// Application object: index 0x2001 sub-index 2 (type short, 16 bits) is mapped.

	data = 3;
	load_device_object(CAN_SDOPER_DOWNLOAD, trnpdo_map, 0, (canbyte*)&data, 1);
	fnr = client_write_obd_u32(0, rcvpdo_map, 0, 3);
	// First transmit and receive PDOs mapping.
	// Number of mapped application objects (three) is written down.

	data = 4;
	load_device_object(CAN_SDOPER_DOWNLOAD, trnpdo_comm, 2, (canbyte*)&data, 1);
	fnr = client_write_obd_u32(0, rcvpdo_comm, 2, 4);
	// Transmission type of the first transmit and receive PDOs communication parameter is set.
	// The PDOs are configured as transferred synchronously and cyclically.
	// Four SYNCs are necessary to trigger PDO transmissions.

	u16_to_canframe(10000, (canbyte*)&data);	// Inhibit time 1 sec
//	u16_to_canframe(60000, (canbyte*)&data);	// Inhibit time 6 sec - to check TPDO inhibit
	load_device_object(CAN_SDOPER_DOWNLOAD, trnpdo_comm, 3, (canbyte*)&data, 2);
	// Inhibit time of the first TPDO communication parameter is set.

	#if (CAN_APPLICATION_MODE == MASTER)
	u32_to_canframe(CAN_CANID_PDO1_TRN_MIN+test_node-1, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, trnpdo_comm, 1, (canbyte*)&data, 4);
	// PDO COB-ID is set to valid state.
	#endif


	#if CAN_DYNAMIC_MAPPING_GRANULARITY == MAPBIT
		for (sub = 1; sub <= 5; sub++) {
			u32_to_canframe(0x00010001, (canbyte*)&data);
			load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_map+1), sub, (canbyte*)&data, 4);
			fnr = client_write_obd_u32(0, (canindex)(rcvpdo_map+1), sub, 0x00010001);
		}
		// Second transmit and receive PDOs mapping. Bit-oriented PDOs test.
		// Five dummy objects: index 0x0001 sub-index 0x00 (type boolean, 1 bit) are mapped.
	#else
		sub = 1;
	#endif

	u32_to_canframe(0x20010320, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_map+1), sub, (canbyte*)&data, 4);
	fnr = client_write_obd_u32(0, (canindex)(rcvpdo_map+1), sub, 0x20010320);
	// Second transmit and receive PDOs mapping.
	// Application object: index 0x2001 sub-index 3 (type unsigned int, 32 bits) is mapped.

	data = sub;
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_map+1), 0, (canbyte*)&data, 1);
	fnr = client_write_obd_u32(0, (canindex)(rcvpdo_map+1), 0, sub);
	// Second transmit and receive PDOs mapping.
	// Number of mapped application objects (sub) is written down.

	data = 10;
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_comm+1), 2, (canbyte*)&data, 1);
	fnr = client_write_obd_u32(0, (canindex)(rcvpdo_comm+1), 2, 10);
	// Transmission type of the second transmit and receive PDOs communication parameter is set.
	// The PDOs are configured as transferred synchronously and cyclically.
	// Ten SYNCs are necessary to trigger PDO transmissions.

	#if (CAN_APPLICATION_MODE == MASTER)
	u32_to_canframe(CAN_CANID_PDO2_TRN_MIN+test_node-1, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_comm+1), 1, (canbyte*)&data, 4);
	// PDO COB-ID is set to valid state.
	#endif


	u32_to_canframe(0x20010440, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_map+2), 1, (canbyte*)&data, 4);
	fnr = client_write_obd_u32(0, (canindex)(rcvpdo_map+2), 1, 0x20010440);
	// Third transmit and receive PDOs mapping.
	// Application object: index 0x2001 sub-index 4 (type long long, 64 bits) is mapped.

	data = 1;
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_map+2), 0, (canbyte*)&data, 1);
	fnr = client_write_obd_u32(0, (canindex)(rcvpdo_map+2), 0, 1);
	// Third transmit and receive PDOs mapping.
	// Number of mapped application objects (one) is written down.

	data = 16;
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_comm+2), 2, (canbyte*)&data, 1);
	fnr = client_write_obd_u32(0, (canindex)(rcvpdo_comm+2), 2, 16);
	// Transmission type of the third transmit and receive PDOs communication parameter is set.
	// The PDOs are configured as transferred synchronously and cyclically.
	// Sixteen SYNCs are necessary to trigger PDO transmissions.

	#if (CAN_APPLICATION_MODE == MASTER)
	u32_to_canframe(CAN_CANID_PDO3_TRN_MIN+test_node-1, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_comm+2), 1, (canbyte*)&data, 4);
	// PDO COB-ID is set to valid state.
	#endif


	u32_to_canframe(0x20010640, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_map+3), 1, (canbyte*)&data, 4);
	fnr = client_write_obd_u32(0, (canindex)(rcvpdo_map+3), 1, 0x20010640);
	// Fourth transmit and receive PDOs mapping.
	// Application object: index 0x2001 sub-index 6 (type double, 64 bits) is mapped.

	data = 1;
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_map+3), 0, (canbyte*)&data, 1);
	fnr = client_write_obd_u32(0, (canindex)(rcvpdo_map+3), 0, 1);
	// Fourth transmit and receive PDOs mapping.
	// Number of mapped application objects (one) is written down.

	data = 24;
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_comm+3), 2, (canbyte*)&data, 1);
	fnr = client_write_obd_u32(0, (canindex)(rcvpdo_comm+3), 2, 24);
	// Transmission type of the forth transmit and receive PDOs communication parameter is set.
	// The PDOs are configured as transferred synchronously and cyclically.
	// Twenty four SYNCs are necessary to trigger PDO transmissions.

	#if (CAN_APPLICATION_MODE == MASTER)
	u32_to_canframe(CAN_CANID_PDO4_TRN_MIN+test_node-1, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_comm+3), 1, (canbyte*)&data, 4);
	// PDO COB-ID is set to valid state.
	#endif

	printf("\n***** PDOs configured.\n");
}

static void check_pdo(void)	// Specific PDO check
{
	canindex trnpdo_comm;
	unsigned16 data;

	trnpdo_comm = CAN_INDEX_TRNPDO_COMM_MIN;
	#if CAN_APPLICATION_MODE == TEST
	trnpdo_comm += 4*(test_node-1);
	#endif
	printf("\n***** Attempt to write (download) an object, that is not allowed to change: PDO inhibit time when PDO exists.\n");
	printf("***** Abort code 0x06010000 (unsupported access to an object) has to be receiver from the server.\n");
	u16_to_canframe(1234, (canbyte*)&data);
	load_device_object(CAN_SDOPER_DOWNLOAD, (canindex)(trnpdo_comm+2), 3, (canbyte*)&data, 2);
}

void test_monitor(void)
{
	if (test_node < CAN_NODE_ID_MIN || test_node > CAN_NODE_ID_MAX) return;
	initcnt--;
	if (initcnt == 0) {
		initcnt = 10;
		printf("\n***** PDO test...\n");
		master_init_manstan_application();
	}
	test_show_object_dictionary();
	can_sleep(3000000);
//	can_sleep(100000);	// To check TPDO inhibit
}

void start_test_application(void)
{
	#if CAN_APPLICATION_MODE == TEST
	unsigned16 cnt;
	#endif

	test_node = get_node_id();

	#if CAN_OBJECT_RE_STORE == TRUE && CAN_APPLICATION_MODE == TEST
	can_test_re_store();
	#endif

	if (test_node < CAN_NODE_ID_MIN || test_node > CAN_NODE_ID_MAX) {
		#if CAN_PROTOCOL_LSS == TRUE
		if (test_node == CAN_LSS_NODEID) printf("\n\nLSS");
		else printf("\n\nINVALID");
		#else
		printf("\n\nINVALID");
		#endif
		printf(" node ID: %-1i\nTest finished.\n\n", test_node);
		return;
	}

	can_sleep(500000);
	#if CAN_NMT_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	nmt_master_command(CAN_NMT_RESET_NODE, 0);
	printf("\n***** Reset remote node broadcast issued.\n");
	#endif

	can_sleep(500000);
	#if CAN_APPLICATION_MODE == TEST
	nmt_slave_control();
	// The nmt_slave_control() call is used in the loopback test application
	// to enter the specified mode of the "slave" device.
	#endif

	can_sleep(500000);
	initcnt = 10;

	sdo_index = CAN_INDEX_CLIENT_SDO_MIN+test_node-1;
	// Client SDO communication parameter index is defined.

	client_write_obd_u32(0, sdo_index, 1, CAN_CANID_SDO_CS_BASE+test_node);
	client_write_obd_u32(0, sdo_index, 2, CAN_CANID_SDO_SC_BASE+test_node);
	// Enabling client SDO: disabled by default in DS301 v 4.02.

	test_obd_sdo_transfer();
	configure_pdo();
	configure_sync();

	#if CAN_NMT_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	can_sleep(500000);
	nmt_master_command(CAN_NMT_START_REMOTE_NODE, 0);
	printf("\n***** Start remote node broadcast issued.\n");
	start_can_master();
	// Makes all master PDOs valid.
	#endif

	can_sleep(500000);

	#if CAN_APPLICATION_MODE == TEST
	nmt_slave_control();
	for (cnt = 0; cnt < CAN_NOF_PDO_RECEIVE; cnt++) {
		set_pdo_state((canindex)(CAN_INDEX_RCVPDO_COMM_MIN + cnt), VALID);
	}
	// The code is used to process loopback test PDOs correctly
	// with the static master COBID method (Receive PDO COBIDs must 
	// be used for loopback test PDOs, so they are to be set last).
	#endif

	can_sleep(500000);
	check_pdo();
	can_sleep(5000000);
	printf("\n***** PDO test...\n");
	master_init_manstan_application();
}

#endif

#endif
