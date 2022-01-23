// *** The system version. ***
// All modules major and minor versions must be equal to the system ones
// and release not less then the system one.

#define MAJOR_VERSION   3  // Major system version
#define MINOR_VERSION   0  // Minor system version
#define RELEASE         0  // The system release


#ifndef FALSE
#define FALSE			0
#endif
#ifndef TRUE
#define TRUE			1
#endif

#define OFF				0
#define ON				1

#define NOT_VALID		0
#define VALID			1

#define UN_RESTRICTED	0
#define RESTRICTED		1

#define CANID11			0
#define CANID29			1

#define DYNAMIC			0
#define STATIC			1

#define AFSINGLE		0
#define AFDUAL			1
#define AFTRIPLE		2

#define NORMAL			0
#define REVERSE			1

#define SEPARATE		0
#define COMBINED		1

#define BYTES			0	// Object size units flag
#define BITS			1

#define MAPBIT			0	// PDO mapping granularity flag - one bit granularity
#define MAPBYTE			1	// PDO mapping granularity flag - 8 bits granularity

#define SERVER			0	// Server node operational mode
#define CLIENT			1	// Client node operational mode

#define SLAVE			0	// Slave node operational mode
#define MASTER			1	// Master node operational mode

#define SIGNAL			0
#define POLL			1

#define RESOLVED		0
#define OCCURRED		1

#define CRCTABLE		0
#define CRCDIRECT		1

#define TEST			2	// Client / Server and Master / Slave node operational mode (for test use only)

#define LSS_OFF				0
#define LSS_WAITING			1
#define LSS_CONFIGURATION	2

#define CIA_BITRATE_TABLE		0
#define CIA_BITRATE_INDEX_1000	0
#define CIA_BITRATE_INDEX_800	1
#define CIA_BITRATE_INDEX_500	2
#define CIA_BITRATE_INDEX_250	3
#define CIA_BITRATE_INDEX_125	4
#define CIA_BITRATE_INDEX_50	6
#define CIA_BITRATE_INDEX_20	7
#define CIA_BITRATE_INDEX_10	8
#define CIA_BITRATE_INDEX_AUTO	9

#include "__can_defines.h"

// *** Various static defaults ***

#define CAN_NODE_ID_MIN			1		// Minimum device node ID
#define CAN_NODE_ID_MAX			127		// Maximum device node ID
#define CAN_LSS_NODEID			255		// Non configured device node ID

#define CAN_SIZEOF_FACTOR		8	// BIT object length calculation factor
#define CAN_SIZEOF_BOOLEAN		1	// Boolean data type size both in bits and bytes

// *** CAN_SIZE_... Various buffers sizes below ***

#define CAN_SIZE_CLTBASIC		4	// SDO client BASIC transactions work buffer size
#define CAN_SIZE_SRVFULL		2	// SDO server FULL transactions work buffer size

// *** Various time-related constants ***

#define CAN_SLEEP_ONE_MILLISEC	1000	// One millisecond sleep interval - microseconds
#define CAN_SLEEP_READ			100		// SDO client BASIC transaction sleep interval - microseconds

// *** CAN_WRITECACHE_... -  CANopen output cache related ***

#define CAN_WRITECACHE_SIZE		8		// Number of output cache buffers. Min = 8.
#define CAN_WRITECACHE_ATTEMPTS	64		// No of write output cache attempts (max 32767), separated with WRITECACHE_DELAY.
#define CAN_WRITECACHE_DELAY	1000	// Write output cache attempts separator in microseconds
										// Must satisfy SDO block protocol

// *** CAN_MASK_... - various bit masks ***

#if CAN_ID_MODE == CANID11
	#define CAN_MASK_CANID		0x7FF		// CAN-ID 11 bit mask, renamed 2.2.x
#elif CAN_ID_MODE == CANID29
	#define CAN_MASK_CANID		0x1FFFFFFF	// CAN-ID 29 bit mask, renamed 2.2.x
#endif
#define CAN_MASK_CANID_FUNC		0x780		// Function code mask for CANID-11
#define CAN_MASK_CANID_NODE		0x07F		// Node-ID mask for CANID-11
#define CAN_MASK_IDSIZE			0x20000000	// CAN ID size bit mask
#define CAN_MASK_TIME_MS		0xFFFFFFF	// Time of Day structure ms mask (28 bits)
#define CAN_MASK_SDO_CS			0x7		// SDO command specifier mask
#define CAN_MASK_SDO_BLAST		0x80	// Last block SDO segment mask
#define CAN_MASK_SDO_SEQNO		0x7F	// Sequence number block SDO mask
#define CAN_MASK_ACCESS_PDO		0x1		// Object PDO mapping mask
#define CAN_MASK_ACCESS_RO		0x2		// Read-only object access mask
#define CAN_MASK_ACCESS_WO		0x4		// Write-only object access mask
#define CAN_MASK_ACCESS_RW		0x6		// Read and write object access mask

#define CAN_MASK_LOAD_COMM_1	0x1			// Restore node-independent communication parameters
#define CAN_MASK_LOAD_COMM_2	0x2			// Restore node-related communication parameters
#define CAN_MASK_LOAD_APPL		0x4			// Restore application parameters

#define CAN_MASK_COBID_INVALID	0x80000000	// COB-IDs in-validity bit mask (EMCY, SDO, PDO)

#define CAN_ERRBIT_GENERIC		0x01	// Generic error
#define CAN_ERRBIT_CURRENT		0x02	// Current
#define CAN_ERRBIT_VOLTAGE		0x04	// Voltage
#define CAN_ERRBIT_TEMP			0x08	// Temperature
#define CAN_ERRBIT_COMM			0x10	// Communication
#define CAN_ERRBIT_PROFILE		0x20	// Device profile specific
#define CAN_ERRBIT_RESERVED		0x40	// Reserved
#define CAN_ERRBIT_MANSPEC		0x80	// Manufacture specific
#define CAN_MASK_ANY_ERROR		0xFE	// Any error mask


// *V* CAN_FLAG_... - Can frame structure flag masks *V*

#if CAN_APPLICATION_MODE == TEST
  #define CAN_FLAG_RTR        0x1
  #define CAN_FLAG_EFF        0x4
#else
  #define CAN_FLAG_RTR        FRAME_RTR  // RTR frame mask, defined in chai.h
  #define CAN_FLAG_EFF        FRAME_EFF  // Extended frame format mask, defined in chai.h
#endif

#define CAN_DATALEN_GFC           0  // GFC frame data length
#define CAN_DATALEN_SYNC          0  // SYNC frame data length
#define CAN_DATALEN_SYNC_COUNTER  1  // SYNC v.4.2 counter frame data length
#define CAN_DATALEN_TIME          6  // TIME frame data length
#define CAN_DATALEN_ECP           1  // Heartbeat frame data length
#define CAN_DATALEN_NMT_MC        2  // NMT master command frame data length
#define CAN_DATALEN_EMCY          8  // EMCY frame data length
#define CAN_DATALEN_SDO           8  // SDO frame data length
#define CAN_DATALEN_LSS           8  // LSS frame data length
#define CAN_DATALEN_MAXIMUM       8  // Maximum CAN frame data length

#define CAN_SYNC_COUNTER_MIN      1   // Minimum SYNC counter value
#define CAN_SYNC_COUNTER_MAX      240  // Maximum SYNC counter value

// *** CAN_CANID_... - CAN communication object default identifiers of the pre-defined connection set ***

#define CAN_CANID_DUMMY				0x000

#define CAN_CANID_NMT				0x000	// NMT CAN-ID
#define CAN_CANID_GFC				0x001	// Global Failsafe Command (GFC) CAN-ID
#define CAN_CANID_SYNC				0x080	// SYNC CAN-ID
#define CAN_CANID_TIME				0x100	// TIME CAN-ID

#define CAN_CANID_EMCY_BASE			0x080	// Base emergency CAN-ID
#define CAN_CANID_SRDO_BASE			0x0FF	// Base SRDO (EN50325-5) CAN-ID
#define CAN_CANID_PDO_TRN_BASE		0x180	// Base transmit PDO
#define CAN_CANID_PDO_RCV_BASE		0x200	// Base receive PDO
#define CAN_CANID_PDO_SHIFT			0x100	// Pre-defined PDO CAN-IDs shift
#define CAN_CANID_SDO_SC_BASE		0x580	// Base Server->Client SDO
#define CAN_CANID_SDO_CS_BASE		0x600	// Base Client->Server SDO
#define CAN_CANID_NMT_ERROR_BASE	0x700	// Base NMT error control

#define CAN_CANID_EMCY_MIN			0x081	// Min emergency CAN-ID
#define CAN_CANID_EMCY_MAX			0x0FF	// Max emergency CAN-ID
#define CAN_CANID_SRDO_MIN			0x101	// Min SRDO (EN50325-5) CAN-ID
#define CAN_CANID_SRDO_MAX			0x180	// Max SRDO (EN50325-5) CAN-ID
#define CAN_CANID_PDO1_TRN_MIN		0x181	// Min transmit PDO1
#define CAN_CANID_PDO1_TRN_MAX		0x1FF	// Max transmit PDO1
#define CAN_CANID_PDO1_RCV_MIN		0x201	// Min receive PDO1
#define CAN_CANID_PDO1_RCV_MAX		0x27F	// Max receive PDO1
#define CAN_CANID_PDO2_TRN_MIN		0x281	// Min transmit PDO2
#define CAN_CANID_PDO2_TRN_MAX		0x2FF	// Max transmit PDO2
#define CAN_CANID_PDO2_RCV_MIN		0x301	// Min receive PDO2
#define CAN_CANID_PDO2_RCV_MAX		0x37F	// Max receive PDO2
#define CAN_CANID_PDO3_TRN_MIN		0x381	// Min transmit PDO3
#define CAN_CANID_PDO3_TRN_MAX		0x3FF	// Max transmit PDO3
#define CAN_CANID_PDO3_RCV_MIN		0x401	// Min receive PDO3
#define CAN_CANID_PDO3_RCV_MAX		0x47F	// Max receive PDO3
#define CAN_CANID_PDO4_TRN_MIN		0x481	// Min transmit PDO4
#define CAN_CANID_PDO4_TRN_MAX		0x4FF	// Max transmit PDO4
#define CAN_CANID_PDO4_RCV_MIN		0x501	// Min receive PDO4
#define CAN_CANID_PDO4_RCV_MAX		0x57F	// Max receive PDO4
#define CAN_CANID_SDO_SC_MIN		0x581	// Min Server->Client SDO
#define CAN_CANID_SDO_SC_MAX		0x5FF	// Max Server->Client SDO
#define CAN_CANID_SDO_CS_MIN		0x601	// Min Client->Server SDO
#define CAN_CANID_SDO_CS_MAX		0x67F	// Max Client->Server SDO
#define CAN_CANID_NMT_ERROR_MIN		0x701	// Min NMT error control
#define CAN_CANID_NMT_ERROR_MAX		0x77F	// Max NMT error control

#define CAN_CANID_CONFIG_MAX		0x67F	// Maximum configurable 11 bit CAN-ID.

#define CAN_CANID_LSS_SLAVE			0x7E4	// LSS slave
#define CAN_CANID_LSS_MASTER		0x7E5	// LSS master

// *** CAN_CLASS_... - CAN objects classes ***

#define CAN_CLASS_MANSPEC			1
#define CAN_CLASS_STANDEV			2
#define CAN_CLASS_ERROR				3
#define CAN_CLASS_ECP				4
#define CAN_CLASS_DEFTYPE			5
#define CAN_CLASS_SYNC				6
#define CAN_CLASS_CLIENT_SDO		7
#define CAN_CLASS_SERVER_SDO		8
#define CAN_CLASS_PDO_COMM			9
#define CAN_CLASS_PDO_MAP			10
#define CAN_CLASS_DEVICE			11
#define CAN_CLASS_TIME				12
#define CAN_CLASS_EMCY				13
#define CAN_CLASS_RE_STORE			14
#define CAN_CLASS_ERR_BEHAVIOUR		15
#define CAN_CLASS_SR_COMM			16
#define CAN_CLASS_SR_MAP			17
#define CAN_CLASS_SR_CONFIG			18
#define CAN_CLASS_NETWORKS			19

// *** CAN_DEFTYPE_... - CAN data type entry specification indexes ***

#define CAN_DEFTYPE_BOOLEAN				0x0001
#define CAN_DEFTYPE_INTEGER8			0x0002
#define CAN_DEFTYPE_INTEGER16			0x0003
#define CAN_DEFTYPE_INTEGER32			0x0004
#define CAN_DEFTYPE_UNSIGNED8			0x0005
#define CAN_DEFTYPE_UNSIGNED16			0x0006
#define CAN_DEFTYPE_UNSIGNED32			0x0007
#define CAN_DEFTYPE_REAL32				0x0008
#define CAN_DEFTYPE_VISIBLE_STRING		0x0009
#define CAN_DEFTYPE_OCTET_STRING		0x000A
#define CAN_DEFTYPE_UNICODE_STRING		0x000B
#define CAN_DEFTYPE_TIME_OF_DAY			0x000C
#define CAN_DEFTYPE_TIME_DIFFERENCE		0x000D
#define CAN_DEFTYPE_DOMAIN				0x000F
#define CAN_DEFTYPE_INTEGER24			0x0010
#define CAN_DEFTYPE_REAL64				0x0011
#define CAN_DEFTYPE_INTEGER40			0x0012
#define CAN_DEFTYPE_INTEGER48			0x0013
#define CAN_DEFTYPE_INTEGER56			0x0014
#define CAN_DEFTYPE_INTEGER64			0x0015
#define CAN_DEFTYPE_UNSIGNED24			0x0016
#define CAN_DEFTYPE_UNSIGNED40			0x0018
#define CAN_DEFTYPE_UNSIGNED48			0x0019
#define CAN_DEFTYPE_UNSIGNED56			0x001A
#define CAN_DEFTYPE_UNSIGNED64			0x001B

// *** CAN_INDEX_... - CAN object dictionary indexes ***

#define CAN_INDEX_DUMMY					0x0000

#define CAN_INDEX_DEFTYPE_MIN			0x0001	// Data type min index
#define CAN_INDEX_DEFTYPE_MAX			0x001F	// Data type max index

#define CAN_INDEX_COMMAREA_BEGIN		0x1000	// Communication profile area begin
#define CAN_INDEX_COMMAREA_END			0x1FFF	// Communication profile area end
#define CAN_INDEX_MANSPEC_BEGIN			0x2000	// Manufacturer specific profile area begin
#define CAN_INDEX_MANSPEC_END			0x5FFF	// Manufacturer specific profile area end
#define CAN_INDEX_STANDEV_BEGIN			0x6000	// Standardised device profile area begin
#define CAN_INDEX_STANDEV_END			0x9FFF	// Standardised device profile area end

#define CAN_INDEX_DEVICE_TYPE			0x1000	// Device type

#define CAN_INDEX_ERROR_REG				0x1001	// Error register

#define CAN_INDEX_MAN_STATUS			0x1002	// Manufacturer status register

#define CAN_INDEX_PREDEF_ERROR			0x1003	// Pre-defined Error Field

#define CAN_INDEX_SYNC_COBID			0x1005	// COB-ID SYNC
#define CAN_INDEX_SYNC_PERIOD			0x1006	// Communication cycle period
#define CAN_INDEX_SYNC_WINDOW			0x1007	// Synchronous window length

#define CAN_INDEX_MAN_DEV_NAME			0x1008	// Manufacturer device name
#define CAN_INDEX_MAN_HARD_VER			0x1009	// Manufacturer hardware version
#define CAN_INDEX_MAN_SOFT_VER			0x100A	// Manufacturer software version

#define CAN_INDEX_GUARD_TIME			0x100C	// Guard time
#define CAN_INDEX_LIFETIME_FACTOR		0x100D	// Life time factor

#define CAN_INDEX_STORE					0x1010	// Store parameters
#define CAN_INDEX_RE_STORE				0x1011	// Restore default parameters

#define CAN_INDEX_TIME_COBID			0x1012	// COB-ID TIME

#define CAN_INDEX_EMCY_COBID			0x1014	// COB-ID emergency object
#define CAN_INDEX_EMCY_INHIBIT			0x1015	// Inhibit time EMCY

#define CAN_INDEX_CONS_HBT				0x1016	// Consumer heartbeat time
#define CAN_INDEX_PROD_HBT				0x1017	// Producer heartbeat time

#define CAN_INDEX_IDENTITY				0x1018	// Identity object

#define CAN_INDEX_SYNC_OVERFLOW			0x1019	// Synchronous counter overflow value

#define CAN_INDEX_ERR_BEHAVIOUR			0x1029	// Error behaviour object

#define CAN_INDEX_SERVER_SDO_MIN		0x1200	// Server SDO parameter min index
#define CAN_INDEX_SERVER_SDO_DEFAULT	0x1200	// Default server SDO parameter index
#define CAN_INDEX_SERVER_SDO_MAX		0x127F	// Server SDO parameter max index
#define CAN_INDEX_CLIENT_SDO_MIN		0x1280	// Client SDO parameter min index
#define CAN_INDEX_CLIENT_SDO_DEFAULT	0x1280	// Default client SDO parameter index
#define CAN_INDEX_CLIENT_SDO_MAX		0x12FF	// Client SDO parameter max index

#define CAN_INDEX_RCVPDO_COMM_MIN		0x1400	// Receive PDO communication parameter min index
#define CAN_INDEX_RCVPDO_COMM_MAX		0x15FF	// Receive PDO communication parameter max index
#define CAN_INDEX_RCVPDO_MAP_MIN		0x1600	// Receive PDO mapping parameter min index
#define CAN_INDEX_RCVPDO_MAP_MAX		0x17FF	// Receive PDO mapping parameter max index
#define CAN_INDEX_TRNPDO_COMM_MIN		0x1800	// Transmit PDO communication parameter min index
#define CAN_INDEX_TRNPDO_COMM_MAX		0x19FF	// Transmit PDO communication parameter max index
#define CAN_INDEX_TRNPDO_MAP_MIN		0x1A00	// Transmit PDO mapping parameter min index
#define CAN_INDEX_TRNPDO_MAP_MAX		0x1BFF	// Transmit PDO mapping parameter max index

// *** CAN_CS_..., CAN_CCS_..., CAN_SCS_... - CANopen general, client and server command specifiers ***

#define CAN_CCS_SDO_DOWNLOAD_INIT	1	// Client command specifier for initiate expedited/segmented SDO download
#define CAN_SCS_SDO_DOWNLOAD_INIT	3	// Server command specifier for initiate expedited/segmented SDO download
#define CAN_CCS_SDO_DOWNSEGM_DATA	0	// Client command specifier for segmented download SDO data
#define CAN_SCS_SDO_DOWNSEGM_DATA	1	// Server command specifier for segmented download SDO data
#define CAN_CCS_SDO_UPLOAD_INIT		2 	// Client command specifier for initiate expedited/segmented SDO upload
#define CAN_SCS_SDO_UPLOAD_INIT		2 	// Server command specifier for initiate expedited/segmented SDO upload
#define CAN_CCS_SDO_UPSEGM_DATA		3 	// Client command specifier for segmented upload SDO data
#define CAN_SCS_SDO_UPSEGM_DATA		0	// Server command specifier for segmented upload SDO data
#define CAN_CCS_SDO_DOWNBLOCK		6 	// Client command specifier for block SDO download
#define CAN_SCS_SDO_DOWNBLOCK		5 	// Server command specifier for block SDO download
#define CAN_CCS_SDO_UPBLOCK			5 	// Client command specifier for block SDO upload
#define CAN_SCS_SDO_UPBLOCK			6 	// Server command specifier for block SDO upload

#define CAN_CS_SDO_ABORT			4	// SDO abort command specifier

#define CAN_CCS_SDO_SPECIAL_DOWN	0xFE	// Client special SDO command for block download protocol
#define CAN_CCS_SDO_SPECIAL_UP		0xFF	// Client special SDO command for block upload protocol

// *** CAN_BLOCK_... CAN_BLMODE_... CAN_SDOSUB_... - various definitions for block protocols ***

#define CAN_BLOCK_SIZE_MIN			1		// Minimun number of segments per block
#define CAN_BLOCK_SIZE_MAX			127		// Maximum number of segments per block
#define CAN_BLOCK_RETRANSMIT		128		// No of retransmit events for the SDO block protocol

#define CAN_BLMODE_NORMAL			0		// Normal mode
#define CAN_BLMODE_DOWNBLOCK		0xFE	// Download block segment mode
#define CAN_BLMODE_UPBLOCK			0xFF	// Upload block segment mode

#define CAN_SDOSUB_INIT				0		// SUB-command specifier for initiate block SDO protocol
#define CAN_SDOSUB_END				1		// SUB-command specifier for end block SDO protocol
#define CAN_SDOSUB_LOAD				2		// SUB-command specifier for load SDO block protocol
#define CAN_SDOSUB_START			3		// SUB-command specifier for start SDO block upload protocol

// *** CAN_NODE_STATE_...  Can node possible states ***

#define CAN_NODE_STATE_INITIALISING		0
#define CAN_NODE_STATE_STOPPED			4
#define CAN_NODE_STATE_OPERATIONAL		5
#define CAN_NODE_STATE_PRE_OPERATIONAL	127
//#define CAN_NODE_STATE_DUMMY			254		// for some applications only
//#define CAN_NODE_STATE_UNCERTAIN		255		// for some applications only

// *** CAN_NMT_...  Can network management protocoles command specifiers ***

#define CAN_NMT_CS_DUMMY				0
#define CAN_NMT_START_REMOTE_NODE		1
#define CAN_NMT_STOP_REMOTE_NODE		2
#define CAN_NMT_ENTER_PRE_OPERATIONAL	128
#define CAN_NMT_RESET_NODE				129
#define CAN_NMT_RESET_COMMUNICATION		130

// *** CAN_SDOPER_..., CAN_SDOSIZE_... - CANopen SDO transfer mode selection codes and values ***

#define CAN_SDOPER_DOWNLOAD			0	// Expedited <= 4 bytes; Segmented <= CAN_SDOSIZE_SEGMENTED, > Block
#define CAN_SDOPER_DOWN_EXPEDITED	1	// actual download mode
#define CAN_SDOPER_DOWN_SEGMENTED	2	// actual download mode
#define CAN_SDOPER_DOWN_BLOCK		3	// actual download mode
#define CAN_SDOPER_UPLOAD			10	// Expedited <= 4 bytes; Segmented <= CAN_SDOSIZE_SEGMENTED, > Block
#define CAN_SDOPER_UP_EXPEDITED		11	// actual upload mode
#define CAN_SDOPER_UP_SEGMENTED		12	// actual upload mode
#define CAN_SDOPER_UP_BLOCK			13	// actual upload mode

#define CAN_SDOSIZE_EXPEDITED			4	// Expedited SDO transfers maximum data size in bytes
#if CAN_APPLICATION_MODE == TEST
	#define CAN_SDOSIZE_SEGMENTED		40	// For block mode test only
#else
	#define CAN_SDOSIZE_SEGMENTED		CAN_SIZE_MAXSDOMEM
#endif									// Segmented SDO transfers maximum data size in bytes

#define CAN_DATASEGM_EXPEDITED		4	// Expedited SDO transfers data segment size in bytes
#define CAN_DATASEGM_OTHER			7	// Segmented and block SDO transfers data segment size in bytes

// *V* CAN_ID_PRIORITY_... - Data send program priority threshold IDs  *V*

#define CAN_ID_PRIORITY_0			0x080	// ID <= then buffer 0.., NMT, GFC, SYNC
#define CAN_ID_PRIORITY_1			0x180	// ID <= then buffer 1.., EMCY, TS
#define CAN_ID_PRIORITY_2			0x580	// ID <= then buffer 2.., PDO
											// Buffers 4 to CAN_WRITECACHE_SIZE-1 for the higher IDs

// *** CAN_TRANSTATE_... - Status codes (states) for client transaction operations ***

#define CAN_TRANSTATE_OBD_ZERO			-105	// Object dictionary entry is of zero size
#define CAN_TRANSTATE_OBD_READ			-104	// Object dictionary read error
#define CAN_TRANSTATE_OBD_WRITE			-103	// Object dictionary write error
#define CAN_TRANSTATE_OBD_NOOBJECT		-102	// Object does not exist in the object dictionary
#define CAN_TRANSTATE_OBD_NOSUBIND		-101	// Sub-index does not exist
#define CAN_TRANSTATE_OBD_MALLOC		-100	// Object transfer buffer allocation error
#define CAN_TRANSTATE_SDO_RETRANSMIT	-44 	// No of retransmit events exceeded (block protocol)
#define CAN_TRANSTATE_SDO_BLKSIZE		-43 	// SDO number of segments per block invalid (block protocol)
#define CAN_TRANSTATE_SDO_SEQNO			-42 	// SDO sequence number invalid (block protocol)
#define CAN_TRANSTATE_SDO_CRC			-41 	// SDO CRC error (block protocol)
#define CAN_TRANSTATE_SDO_SUB			-40 	// SDO subcommand invalid or mismatch (block protocol)
#define CAN_TRANSTATE_SDO_TOGGLE		-39 	// SDO segmented transfer toggle error
#define CAN_TRANSTATE_SDO_DATASIZE		-33 	// SDO protocol data size parameter is incorrect
#define CAN_TRANSTATE_SDO_OBJSIZE		-32 	// SDO object sizes, known to client and server mismatch
#define CAN_TRANSTATE_SDO_MODE			-31 	// SDO client and server transfer modes mismatch
#define CAN_TRANSTATE_SDO_MPX			-30 	// SDO client and server multiplexors mismatch
#define CAN_TRANSTATE_SDO_SRVABORT		-20 	// SDO transfer protocol aborted by server
#define CAN_TRANSTATE_SDO_INVALID		-16		// SDO is not valid
#define CAN_TRANSTATE_SDO_WRITERR		-15		// SDO write error
#define CAN_TRANSTATE_SDO_SCSERR		-14		// SDO client received not valid or unknown server command specifier
#define CAN_TRANSTATE_SDO_TRANS_TIMEOUT	-13		// SDO client BASIC transaction wait cycle timeout
#define CAN_TRANSTATE_SDO_NET_TIMEOUT	-12		// SDO client BASIC transaction network operation timeout
#define CAN_TRANSTATE_SDO_READ_TIMEOUT	-11		// SDO client BASIC transaction reset due to data read timeout
#define CAN_TRANSTATE_SDO_NOWORKB		-10		// SDO client BASIC transaction work buffer is full and unable to store new data
#define CAN_TRANSTATE_SDO_NODE			-2		// Can't read node-id of the SDO server
#define CAN_TRANSTATE_ERROR				-1 		// General client transaction error
#define CAN_TRANSTATE_OK				0		// Succesfull transaction termination (and status after reset)
#define CAN_TRANSTATE_SDO_WORK			1		// SDO client BASIC transaction is going on


// *V* CAN_ERRET_... - Functions return error codes - negative values only *V*

#define CAN_ERRET_CI_NETWORKS    -140  // CAN networks not available or busy
#define CAN_ERRET_CI_WTOUT       -139  // CAN driver timeout setting failed
#define CAN_ERRET_CI_WRITE       -138  // CAN driver data write operation failed
#define CAN_ERRET_CI_BITRATE     -137  // CAN controller baud rate could not be set.
#define CAN_ERRET_CI_HANDLER     -136  // CAN driver handler registration failed
#define CAN_ERRET_CI_FILTER      -135  // CAN controler acceptance filter set failed
#define CAN_ERRET_CI_START       -134  // CAN controller transition to the start state failed
#define CAN_ERRET_CI_STOP        -133  // CAN controller transition to the stop state failed
#define CAN_ERRET_CI_CLOSE       -132  // CAN IO channel closing error
#define CAN_ERRET_CI_OPEN        -131  // CAN IO channel opening error
#define CAN_ERRET_CI_INIT        -130  // CAN CHAI init failed
#define CAN_ERRET_OBD_INTINCOMP  -120  // General internal incompatibility in the device 2.2.x
#define CAN_ERRET_OBD_PARINCOMP  -119  // General parameter incompatibility reason
#define CAN_ERRET_OBD_DEVSTATE   -118  // Invalid present device state
#define CAN_ERRET_OBD_NODATA     -117  // No data available
#define CAN_ERRET_OBD_DATALOW    -116  // Data type does not match, length of service parameter too low
#define CAN_ERRET_OBD_DATAHIGH   -115  // Data type does not match, length of service parameter too high
#define CAN_ERRET_OBD_DATAMISM   -114  // Data type does not match, length of service parameter does not match
#define CAN_ERRET_OBD_VALMINMAX  -113  // Maximum value is less then minimum value
#define CAN_ERRET_OBD_VALLOW     -112  // Value of parameter written too low (download only)
#define CAN_ERRET_OBD_VALHIGH    -111  // Value of parameter written too high (download only)
#define CAN_ERRET_OBD_VALRANGE   -110  // Invalid value for parameter (download only)
#define CAN_ERRET_OBD_NODIRECT   -107  // Object can not be addressed directly (with its pointer)
#define CAN_ERRET_OBD_OBJACCESS  -106  // Unsupported access to an object
#define CAN_ERRET_OBD_WRITEONLY  -105  // Attempt to read a write only object
#define CAN_ERRET_OBD_READONLY   -104  // Attempt to write a read only object
#define CAN_ERRET_OBD_INVNODE    -103  // Invalid node
#define CAN_ERRET_OBD_NOOBJECT   -102  // Object does not exist in the object dictionary
#define CAN_ERRET_OBD_NOSUBIND   -101  // Sub-index does not exist
#define CAN_ERRET_OUTOFMEM       -100  // No space [to dispose new index for receive CAN-IDs etc]
#define CAN_ERRET_LSS_CANID      -70   // Invalid LSS protocol CAN-ID
#define CAN_ERRET_FLASH_MIN      -69   // ***** For the SDO abort code
#define CAN_ERRET_FLASH_DATA     -69   // Invalid/inconsistent flash data
#define CAN_ERRET_FLASH_VALUE    -68   // No flash data (flash erased or unavailable)
#define CAN_ERRET_FLASH_INIT     -67   // Flash page initialization failed
#define CAN_ERRET_FLASH_LOCKED   -66   // Write to the flash disabled
#define CAN_ERRET_FLASH_ADDRESS  -65   // Invalid flash address
#define CAN_ERRET_FLASH_SIZE     -64   // Invalid [total] store data size
#define CAN_ERRET_STORE_OBJECT   -63   // Invalid store object
#define CAN_ERRET_STORE_FILE     -62   // File operation failed
#define CAN_ERRET_RE_STORE       -61   // Default parameters save/load failed
#define CAN_ERRET_FLASH_MAX      -61   // ***** For the SDO abort code
#define CAN_ERRET_SIGNATURE      -60   // Wrong signature
#define CAN_ERRET_COMM_SEND      -50   // An attempt to send CAN data into the network failed
#define CAN_ERRET_EMCY_INHIBIT   -42   // Emergency is inhibited
#define CAN_ERRET_EMCY_INVALID   -41   // Emergency is not valid
#define CAN_ERRET_SYNC_NOTGENER  -40   // Device does not generate SYNC message
#define CAN_ERRET_PDO_NOMAP	     -32   // Object cannot be mapped to the PDO
#define CAN_ERRET_PDO_ERRMAP     -31   // The number and length of the objects to be mapped would exceed PDO length
#define CAN_ERRET_PDO_MAP_DEACT  -30   // PDO mapping deactivated
#define CAN_ERRET_PDO_TRTYPE     -24   // PDO transmittion type is invalid (requested operation is not supported)
#define CAN_ERRET_PDO_NORTR      -23   // RTR is not allowed for the PDO
#define CAN_ERRET_PDO_INHIBIT    -22   // TPDO is inhibited
#define CAN_ERRET_PDO_TRIGGER    -21   // Cyclic TPDO trigger counter has not expired yet
#define CAN_ERRET_PDO_INVALID    -20   // PDO is not valid
#define CAN_ERRET_SDO_INVALID    -10   // SDO is not valid
#define CAN_ERRET_BITRATE        -5    // Invalid configured bitrate index
#define CAN_ERRET_NODEID         -4    // Invalid configured NodeID
#define CAN_ERRET_NULL_POINTER   -3    // NULL pointer to an object returned
#define CAN_ERRET_NODE_STATE     -2    // Invalid node state

#define CAN_ERRET                -1    // General return error
#define CAN_RETOK                 0    // Normal return

#define CAN_RETOK_MAIN            0    // Normal return from the main(..) function
#define CAN_RETURN_MAIN           1    // Return from the infinite loop of the main(..) function
#define CAN_ERRET_MAIN            2    // Error return from the main(..) function


// *** CAN_ABORT_SDO_... - CANopen SDO abort codes ***

#define CAN_ABORT_SDO_TOGGLE		0x05030000 	// Toggle bit not altered
#define CAN_ABORT_SDO_TIMEOUT		0x05040000 	// SDO protovol timed out
#define CAN_ABORT_SDO_CS			0x05040001	// Client/server command specifier not valid or unknown
#define CAN_ABORT_SDO_BLKSIZE		0x05040002	// Invalid block size (block mode only)
#define CAN_ABORT_SDO_SEQNO			0x05040003	// Invalid sequence number (block mode only)
#define CAN_ABORT_SDO_CRC			0x05040004	// CRC error (block mode only)
#define CAN_ABORT_SDO_OUTOFMEM		0x05040005	// Out of memory
#define CAN_ABORT_SDO_OBJACCESS		0x06010000	// Unsupported access to an object
#define CAN_ABORT_SDO_WRITEONLY		0x06010001	// Attempt to read a write only object
#define CAN_ABORT_SDO_READONLY		0x06010002	// Attempt to write a read only object
#define CAN_ABORT_SDO_NOOBJECT		0x06020000	// Object does not exist in the object dictionary
#define CAN_ABORT_SDO_NOPDOMAP		0x06040041	// Object cannot be mapped to the PDO
#define CAN_ABORT_SDO_ERRPDOMAP		0x06040042	// The number and length of the objects to be mapped would exceed PDO length
#define CAN_ABORT_SDO_PARINCOMP		0x06040043	// General parameter incompatibility reason
#define CAN_ABORT_SDO_INTINCOMP		0x06040047	// General internal incompatibility in the device
#define CAN_ABORT_SDO_HARDWARE		0x06060000	// Access failed due to a hardware error
#define CAN_ABORT_SDO_DATAMISM		0x06070010	// Data type does not match, length of service parameter does not match
#define CAN_ABORT_SDO_DATAHIGH		0x06070012	// Data type does not match, length of service parameter too high
#define CAN_ABORT_SDO_DATALOW		0x06070013	// Data type does not match, length of service parameter too low
#define CAN_ABORT_SDO_NOSUBIND		0x06090011	// Sub-index does not exist
#define CAN_ABORT_SDO_VALRANGE		0x06090030	// Invalid value for parameter (download only)
#define CAN_ABORT_SDO_VALHIGH		0x06090031	// Value of parameter written too high (download only)
#define CAN_ABORT_SDO_VALLOW		0x06090032	// Value of parameter written too low (download only)
#define CAN_ABORT_SDO_VALERR		0x06090036	// Maximum value is less then minimum value
#define CAN_ABORT_SDO_ERROR			0x08000000	// General error
#define CAN_ABORT_SDO_TRAPPL		0x08000020	// Data cannot be transferred or stored to the application
#define CAN_ABORT_SDO_TRAPLC		0x08000021	// Data cannot be transferred or stored to the application because of local control
#define CAN_ABORT_SDO_TRAPDS		0x08000022	// Data cannot be transferred or stored to the application because of the present device state
#define CAN_ABORT_SDO_OBJDICT		0x08000023	// Object dictionary dynamic generation fails or no object dictionary is present
#define CAN_ABORT_SDO_NODATA		0x08000024	// No data available


// *V* CAN_EMCY_... - CANopen emergency error codes *V*

#define CAN_EMCY_NO_ERROR        0x0000

#define CAN_EMCY_GFC_MODE        0x00FF	// Warning: GFC is not in the default mode

#define CAN_EMCYREG_CACHE        0x6180  // CAN send cache overflow. Registered only in object 0x1003.

#define CAN_EMCYREG_TIMERFAIL    0x6190  // System timer initiation failed. Registered only in object 0x1003.
#define CAN_EMCY_TIMEROVERLAP    0x6191  // System timer signals overlap

#define CAN_EMCY_STORE_CRC       0x61A0  // Non volatile memory (SSD file) data inconsistency (CRC, bwinv, etc)
#define CAN_EMCY_STORE_PROC      0x61A1  // Non volatile memory (SSD file) processing error
#define CAN_EMCY_STORE_OBJ       0x61A2  // Invalid object (No object, invalid object size, invalid access, etc)
#define CAN_EMCY_STORE_FILE      0x61A3  // SSD file operations error (create, open, etc)
#define CAN_EMCY_STORE_MEM       0x61A4  // Out of memory or invalid store address
#define CAN_EMCY_STORE_PARM      0x61A5  // Invalid store parameter
#define CAN_EMCY_STORE_DATA      0x61A6  // Invalid stored data

#define CAN_EMCY_HEARTBEAT       0x8130  // Life guard error or heartbeat error

#define CAN_EMCY_HOVR            0x8180  // CAN hardware overrun
#define CAN_EMCY_SOVR            0x8181  // CAN software overrun
#define CAN_EMCY_EWL             0x8182  // CAN error warning limit
#define CAN_EMCY_WTOUT           0x8183  // CAN write timeout

#define CAN_EMCY_SR_STOPPED      0x8190  // SR protocol execution stopped

#define CAN_EMCY_PDOLENERR       0x8210  // PDO not processed due to length error
#define CAN_EMCY_SRDOLENERR      0x8211  // SRDO not processed due to length error
#define CAN_EMCY_PDOLENEXC       0x8220  // PDO length exceeded

#define CAN_EMCY_SYNCLEN         0x8240  // Unexpected SYNC data length
#define CAN_EMCY_RPDO_TIMEOUT    0x8250  // RPDO timeout


// *** LSS_CS... - CAN LSS protocol command specifiers ***

#define LSS_CS_SWITCH_GLOBAL			04	// Switch state global
#define LSS_CS_CONFIG_NODEID			17	// Configure Node ID requestresponse
#define LSS_CS_CONFIG_TIMING			19	// Configure bit timing request/response
#define LSS_CS_ACTIVATE_TIMING			21	// Activate bit timing request
#define LSS_CS_STORE_CONFIG				23	// Store configuration parameters request/response

#define LSS_CS_SWSEL_VENDORID			64	// Switch state selective, vendor name request
#define LSS_CS_SWSEL_PRODCODE			65	// Switch state selective, product code request
#define LSS_CS_SWSEL_REVNUM				66	// Switch state selective, revision number request
#define LSS_CS_SWSEL_SERIAL				67	// Switch state selective, serial number request
#define LSS_CS_SWSEL_RESPONSE			68	// Switch state selective, response

#define LSS_CS_IDENTIFY_VENDORID		70	// Identify remote slave vendor-ID request
#define LSS_CS_IDENTIFY_PRODCODE		71	// Identify remote slave product code request
#define LSS_CS_IDENTIFY_REVNUM_LOW		72	// Identify remote slave revision number low request
#define LSS_CS_IDENTIFY_REVNUM_HIGH		73	// Identify remote slave revision number high request
#define LSS_CS_IDENTIFY_SERIAL_LOW		74	// Identify remote slave serial number low request
#define LSS_CS_IDENTIFY_SERIAL_HIGH		75	// Identify remote slave serial number high request
#define LSS_CS_IDENTIFY_SLAVE			79	// Identify remote slave response

#define LSS_CS_IDENTIFY_NONCONF_REQ		76	// Identify non-configured remote slave request
#define LSS_CS_IDENTIFY_NONCONF_RESP	80	// Identify non-configured remote slave response

#define LSS_CS_FASTSCAN					81	// FastScan protocol

#define LSS_CS_INQUIRE_VENDORID			90	// Inquire vendor-ID request/response
#define LSS_CS_INQUIRE_PRODCODE			91	// Inquire product code request/response
#define LSS_CS_INQUIRE_REVNUM			92	// Inquire revision number request/response
#define LSS_CS_INQUIRE_SERIAL			93	// Inquire serial number request/response
#define LSS_CS_INQUIRE_NODEID			94	// Inquire node ID request/response

// *** LSS_MODE... - CAN LSS protocol modes ***

#define LSS_MODE_SWITCH_WAITING			0	// Switch to waiting state
#define LSS_MODE_SWITCH_CONFIGURATION	1	// Switch to configuration state

#define LSS_CIA_BIT_TIMING_TABLE		0	// Standard CiA bit timing table
#define LSS_BITRATE_TABLE_INDEX_MAX		9	// Max. valid bit rate table index

// *** LSSFS_... - LSS FastScan protocol definitions ***

#define LSSFS_POS_VENDORID				0		// Vendor ID position
#define LSSFS_POS_PRODCODE				1		// Product code position
#define LSSFS_POS_REVNUM				2		// Revision number position
#define LSSFS_POS_SERIAL				3		// Serial number position
#define LSSFS_POS_OFF					255		// Not participationg

#define LSSFS_BITCHECK_MAX				31
#define LSSFS_BITCHECK_RESET			128


// *** CAN_NOF_... - various reserved numbers ***

#define CAN_NOF_PDOBIT_MAX		64	// Maximum PDO length in BIT
#define CAN_NOF_MAP_BYTEGR		8	// PDOs mapping max. entries - 8 bits granularity

#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	#define CAN_NOF_PDO_RECEIVE		(CAN_NOF_PDO_TRAN_SLAVE*CAN_NOF_NODES)	// 2.3.0 Crossed
	#define CAN_NOF_PDO_TRANSMIT	(CAN_NOF_PDO_RECV_SLAVE*CAN_NOF_NODES)	// 2.3.0 Crossed
	#define CAN_SYNCPDO_RECEIVE		(1 + CAN_NOF_SYNCPDO_MASTER)	// 2.3.0 Synchronous RPDO FIFO size
	#define CAN_SYNCPDO_TRANSMIT	(1 + CAN_NOF_SYNCPDO_MASTER)	// 2.3.0 Synchronous TPDO FIFO size
	#define CAN_NOF_RECV_CANIDS		CAN_NOF_RECVCANID_MASTER
#elif CAN_APPLICATION_MODE == SLAVE
	#define CAN_NOF_PDO_RECEIVE		CAN_NOF_PDO_RECV_SLAVE
	#define CAN_NOF_PDO_TRANSMIT	CAN_NOF_PDO_TRAN_SLAVE
	#define CAN_SYNCPDO_RECEIVE		(1 + CAN_NOF_PDO_RECV_SLAVE)	// 2.3.0 Synchronous RPDO FIFO size
	#define CAN_SYNCPDO_TRANSMIT	(1 + CAN_NOF_PDO_TRAN_SLAVE)	// 2.3.0 Synchronous TPDO FIFO size
	#define CAN_NOF_RECV_CANIDS		CAN_NOF_RECVCANID_SLAVE
#endif
