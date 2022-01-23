// *** CAN_..._MODE - CANopen operational modes ***

#define CAN_APPLICATION_MODE	TEST		// Test application operational mode
//#define CAN_APPLICATION_MODE	MASTER		// Master application operational mode
//#define CAN_APPLICATION_MODE	SLAVE		// Slave application operational mode

//#define CAN_NMT_MODE			MASTER		// NMT master functionality mode
#define CAN_NMT_MODE			SLAVE		// NMT slave functionality mode

// *** CAN_DEVICE_... - all device profile classes numeric definitions ***
// *** CAN_SLAVE_DEVICE_CLASS - slave application device profile class ***
#define CAN_DEVICE_ANY		0			// Any non-test devices application
#define CAN_DEVICE_TEST		0xFFFF		// Test device

#define CAN_SLAVE_DEVICE_CLASS	CAN_DEVICE_TEST

#define CAN_NETWORK_CONTROLLER	0			// Default CAN driver channel (CAN controller number)

#define CAN_BITRATE_INDEX		CIA_BITRATE_INDEX_500	// CAN network bit rate index

//#define CAN_OS_LINUX		// The CANopen product operational system - Linux
#define CAN_OS_WIN32		// The CANopen product operational system - Win32

#define CAN_ID_MODE			CANID11	// CANID11 (11 bit ID) only for CANopen protocol.
									// Extended format frames are ignored.

#define CAN_FRAME_READ_MODE		SIGNAL		// CAN network frame is read with true signal or interrupt from CHAI
//#define CAN_FRAME_READ_MODE		POLL		// CAN network frame is read with polling

#define CAN_BYTE_ORDER		NORMAL	// NORMAL - Most SB on high address or REVERSE - Most SB on low address
//#define CAN_BYTE_ORDER		REVERSE	// NORMAL - Most SB on high address or REVERSE - Most SB on low address

#define CAN_PDO_MAPPING_MODE	DYNAMIC		// Dynamic or static PDO mapping support
//#define CAN_PDO_MAPPING_MODE	STATIC		// Dynamic or static PDO mapping support

#define CAN_DYNAMIC_MAPPING_GRANULARITY	MAPBIT	// Dynamic PDO mapping granularity - one bit granularity
//#define CAN_DYNAMIC_MAPPING_GRANULARITY	MAPBYTE	// Dynamic PDO mapping granularity - 8 bits granularity

//#define CAN_MASTER_RECVCANID_METHOD	DYNAMIC		// The method, used by master to process receive CAN-IDs
#define CAN_MASTER_RECVCANID_METHOD	STATIC		// The method, used by master to process receive CAN-IDs

#define CAN_HARD_ACCEPTANCE_FILTER	AFSINGLE	// Single level hardware acceptance filter
//#define CAN_HARD_ACCEPTANCE_FILTER	AFDUAL		// Dual level hardware acceptance filter
//#define CAN_HARD_ACCEPTANCE_FILTER	AFTRIPLE	// Triple level hardware acceptance filter (for EN50325-5)

#define CAN_LED_INDICATOR		SEPARATE	// separate green and red LEDs.
//#define CAN_LED_INDICATOR		COMBINED	// one green/red LED.

#define CAN_CRC_MODE			CRCTABLE	// table CRC calculation (byte based).
//#define CAN_CRC_MODE			CRCDIRECT	// direct polynomial CRC calculation (bit based).

#define CAN_TPDO_LOCAL_LOOPBACK		OFF		// Standard TPDO behaviour
//#define CAN_TPDO_LOCAL_LOOPBACK		ON		// TPDO transmitted and loopbacked into RPDO. Use with care.


// *** CAN_OBJECT_... - CAN objects conditions ***
// *** CAN_PROTOCOL_... - CAN protocol conditions ***

#define CAN_OBJECT_EMCY				TRUE	// TRUE - Emergency object exists, FALSE - does not
//#define CAN_OBJECT_EMCY			FALSE	// TRUE - Emergency object exists, FALSE - does not

#define CAN_OBJECT_TIME				TRUE	// TRUE - TIME object exists, FALSE - does not
//#define CAN_OBJECT_TIME			FALSE	// TRUE - TIME object exists, FALSE - does not

#define CAN_OBJECT_RE_STORE			TRUE	// TRUE - Store/restore object exists, FALSE - does not
//#define CAN_OBJECT_RE_STORE		FALSE	// TRUE - Store/restore object exists, FALSE - does not

#define CAN_OBJECT_ERR_BEHAVIOUR	TRUE	// TRUE - Error behaviour object exists, FALSE - does not
//#define CAN_OBJECT_ERR_BEHAVIOUR	FALSE	// TRUE - Error behaviour object exists, FALSE - does not

#define CAN_PROTOCOL_BLOCK			TRUE	// TRUE - SDO block protocol supported, FALSE - not supported
//#define CAN_PROTOCOL_BLOCK		FALSE	// TRUE - SDO block protocol supported, FALSE - not supported

#define CAN_PROTOCOL_LSS			TRUE	// TRUE - LSS supported, FALSE - not supported
//#define CAN_PROTOCOL_LSS			FALSE	// TRUE - LSS supported, FALSE - not supported

// *** CAN device description objects ***

#define CAN_DEVICE_TYPE		0x00010000	// Device type object (Ind. 0x1000)
#define CAN_MAN_STATUS		0x00000000	// Manufacturer status register (Ind. 0x1002)
#define CAN_VENDOR_ID		0x00000000	// Vendor ID of identity object (Ind. 0x1018, sub 0x1)
#define CAN_PROD_CODE		0x00010000	// Product code of identity object (Ind. 0x1018, sub 0x2)
#define CAN_REV_NUM			0x00030000	// Revision number of identity object (Ind. 0x1018, sub 0x3)

// *** CAN_NOF_... - various reserved numbers ***

#define CAN_NOF_NODES				127	// Number of nodes in the CAN network

#define CAN_NOF_PREDEF_ERRORS		8	// Maximum number of registered errors in Pre-defined Error Field (1..254)

#define CAN_NOF_ERRBEH_SUBIND		1	// Highest sub-index of the error behaviour object (1..254)
#define CAN_SUBIND_ERRBEH_COMM		1	// Communication error behaviour subindex

#define CAN_NOF_MAP					8	// Maximum number of PDO mapped application objects (1..64)
										// May be set for each RPDO and TPDO individually.
										// Applicable only for dynamic PDOs with one bit granularity.

#define CAN_NOF_SDO_SERVER			1	// No of server SDO parameters (communication object dictionary entries)

#define CAN_NOF_PDO_RECV_SLAVE		4	// No of receive PDO parameters (obj. dict. entries) for the Server
#define CAN_NOF_PDO_TRAN_SLAVE		4	// No of transmit PDO parameters (obj. dict. entries) for the Server

#define CAN_NOF_RECVCANID_SLAVE		(3 + CAN_NOF_PDO_RECV_SLAVE + CAN_NOF_PDO_TRAN_SLAVE)
										// Number of Receive DYNAMIC CAN-IDs for the Server/Slave
										// SYNC, TIME STAMP, RPDO1..4, TPDO1..4(RTR), SDO.
										// Not needed for NMTs and Error

#define CAN_NOF_RECVCANID_MASTER	64	// Number of Receive DYNAMIC CAN-IDs for the Client/Master
#define CAN_NOF_SYNCPDO_MASTER		64	// Synchronous RPDO and TPDO buffer sizes for the Master, 2.3.0

// *** CAN_TI... - Timer (timeout) constants ***

#define CAN_TIMERUSEC			10000	// CANopen timer period in microseconds (10 milliseconds). MUST be >= 100.

#define CAN_TIMEOUT_RETRIEVE	500000	// SDO client BASIC transaction data retrieve timeout - microseconds
#define CAN_TIMEOUT_READ		500000	// SDO client BASIC transaction data read timeout - microseconds
#define CAN_TIMEOUT_SERVER		1000000	// SDO server BASIC transaction timeout - microseconds

// *** Various time-related constants ***

#define CAN_HBT_PRODUCER_MS		0	// Producer default heartbeat time in milliseconds
#define CAN_HBT_CONSUMER_MS		0	// Consumer default heartbeat time in milliseconds
#define CAN_EMCY_INHIBIT_100MCS	0	// Emergency inhibit default time in hundreds of microseconds

// *** Device profile dependent defaults ***

#define CAN_RPDO_TRTYPE			0	// Receive PDO default transmission type
#define CAN_TPDO_TRTYPE			0	// Transmit PDO default transmission type
#define CAN_TPDO_INHIBIT_100MCS	0	// TPDO inhibit default time in hundreds of microseconds
#define CAN_RPDO_ET_MS			0	// RPDO event timer default time in milliseconds
#define CAN_TPDO_ET_MS			0	// TPDO event timer default time in milliseconds

#define CAN_TPDO_SYNC_START		0	// TPDO SYNC start value

// *** CAN_SIZE_..., CAN_LEN_... Various buffers sizes and size limits below ***

#define CAN_SIZE_MAXSDOMEM		64	// Maximum data size in bytes, transferred consistently with SDOs.
									// The value is needed for memory allocation routine.

#define CAN_LEN_VISIBLE_STRING	32	// Visible string data type length

