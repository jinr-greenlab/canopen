// *** IOremote application platform ***
//
#define IOREMOTE_PLATFORM		PLATFORM_WINDOWS		// Windows application, TEST mode only
//#define IOREMOTE_PLATFORM		PLATFORM_STM32			// STM32F103xx application
//#define IOREMOTE_PLATFORM		PLATFORM_MILANDR		// Milandr 1986BE9x application

// *** IOremote application mode - microcontroller or test-emulated ***
//
//#define IOREMOTE_APPLICATION_MODE		APPLICATION_REGULAR		// Regular application mode (NOT for Windows)
#define IOREMOTE_APPLICATION_MODE		APPLICATION_TEST		// Test application mode for all platforms

// IOremote printf mode - ON for Windows, OFF for microcontrollers
// For the test application only
//
//#define IOREMOTE_PRINTF_MODE		OFF		// microcontroller
#define IOREMOTE_PRINTF_MODE		ON		// Windows

// *** IOremote NodeID anb Bitrate switches - hardware or flash-only (virtual) ***
//
//#define IOREMOTE_NODERATE_SWITCH	HARDWARE_SW			// NodeID anb Bitrate hardware switches
#define IOREMOTE_NODERATE_SWITCH	VIRTUAL_SW			// NodeID anb Bitrate flash switches

// *** Actual CAN controller network configuration ***
#define CAN_MASK_NETWORKS			(CAN_MASK_NETCHAN_0 | CAN_MASK_NETCHAN_1)

#define CAN_DATALINK_OUTOFF			FALSE	// can_cache_overflow() at the output cache overflow;
//#define CAN_DATALINK_OUTOFF			TRUE	// datalink_mode = OFF at the output cache overflow;

#define CAN_LED_INDICATOR			SEPARATE	// SEPARATE - separate green and red LEDs
//#define CAN_LED_INDICATOR			COMBINED	// COMBINED - one green/red LED.

#define CAN_TPDO_LOCAL_LOOPBACK		OFF		// Standard TPDO behaviour
//#define CAN_TPDO_LOCAL_LOOPBACK		ON		// TPDO transmitted and loopbacked into RPDO. Use with care.

// *** Actual IOremote device type - for the Milandr and Test application ***
//
#define IOREMOTE_DEVICE_TYPE    R2DIO_IO          // Digital I/O
//#define IOREMOTE_DEVICE_TYPE    R2AIO_8INP        // Analog 8 inputs
//#define IOREMOTE_DEVICE_TYPE    R2AIO_8OUT			  // Analog 8 outputs
//#define IOREMOTE_DEVICE_TYPE    R2AIO_4INP_2OUT   // Analog 4 inpits 2 outputs (Milandr)

// *** R2DIO 8I-8O test mode APPLICATION_TEST ***
//
//#define R2DIO_TESTMODE				TESTMODE_TIMER			// 8I-8O digital inputs are switched by the timer
#define R2DIO_TESTMODE				TESTMODE_LOOPBACK		// 8I-8O digital inputs are switched by outputs

#define CAN_SERIAL_NUMBER			0   // The device serial number

#define CAN_BITRATE_INDEX			CIA_BITRATE_INDEX_500   // 500 Kbit/S
//#define CAN_BITRATE_INDEX			CIA_BITRATE_INDEX_250   // 250 Kbit/S

// *** NodeID autoselect ***
#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
	#if (IOREMOTE_DEVICE_TYPE == R2DIO_IO)
		#define CAN_NODEID_SLAVE		1
	#elif (IOREMOTE_DEVICE_TYPE == R2AIO_8INP)
		#define CAN_NODEID_SLAVE		2
	#elif (IOREMOTE_DEVICE_TYPE == R2AIO_8OUT)
		#define CAN_NODEID_SLAVE		3
	#elif (IOREMOTE_DEVICE_TYPE == R2AIO_4INP_2OUT)
		#define CAN_NODEID_SLAVE		4
	#endif
#else
	#define CAN_NODEID_SLAVE		CAN_NODE_ID_MAX
#endif


// *** CAN_TI... - Timer (timeout) constants ***

#define CAN_TIMERUSEC           5000     // CANopen timer period in microseconds (5 milliseconds).

#define CAN_TIMEOUT_SERVER      1000000  // SDO server BASIC transaction timeout - microseconds
#define CAN_BOOTUP_DELAY        0        // Pre-operational state delay: microseconds, 0 - disabled
#define CAN_OPERATIONAL_DELAY   0			   // Operational state delay after entering pre-operational: microseconds, 0 - disabled

// *** Various time-related constants ***

#define CAN_HBT_PRODUCER_MS			        0	    // Producer default heartbeat time in milliseconds

#define CAN_EMCY_INHIBIT_100MCS 		    0   	// Emergency inhibit default time in hundreds of microseconds
#define CAN_EMCY_INHIBIT_100MCS_OUTPUT_DEF	10000	// Default emergency inhibit time for digital and analog outputs short circuit
#define CAN_EMCY_INHIBIT_100MCS_OUTPUT_MIN	1000	// Minimum emergency inhibit time for digital and analog outputs short circuit

#define CAN_DIGOUT_RESET_MCS				1000000	// After reset delay for digital outputs short circuit

// *** IOremote device parameters ***

#define DIGITAL_INP8_BLOCKS_MAX     2  // Max. number of digital input 8 bit blocks
#define DIGITAL_OUT8_BLOCKS_MAX     2  // Max. number of digital output 8 bit blocks
#define DIGITAL_COUNTERS_MAX        (8 * DIGITAL_INP8_BLOCKS_MAX)  // Max. number of digital counters
#define LOGICAL_COUNTERS_MAX        6  // Number of logical counters for the TPDOs

#define DIGITAL_INP8_BLOCKS_TEST    1  // For the test mode, <= MAX
#define DIGITAL_OUT8_BLOCKS_TEST    1  // For the test mode, <= MAX

#define ANALOG_INPUT_CHANS_MAX      8   // Maximum number of analog input channels
#define ANALOG_INPUT_RESOLUTION     16  // Analog inputs actual resolution, bit

#define ANALOG_OUTPUT_CHANS_MAX     8   // Maximum number of analog output channels
#define ANALOG_OUTPUT_RESOLUTION    16  // Analog outputs actual resolution, bit

// *** CANopen IOremote parameters ***

#define CAN_DEVICE_TYPE               0x00000191  // Device type object (Ind. 0x1000)
#define DEVTYPE_MASK_DIGITAL_INPUT    0x00010000
#define DEVTYPE_MASK_DIGITAL_OUTPUT   0x00020000
#define DEVTYPE_MASK_ANALOG_INPUT     0x00040000
#define DEVTYPE_MASK_ANALOG_OUTPUT    0x00080000
#define DEVTYPE_MASK_PDO_MAPPING      0x00800000

#define CAN_MAN_STATUS_DIOC    0x00000000  // Manufacturer status register (Ind. 0x1002)
#define CAN_MAN_STATUS_ANINP   0x00000000  // Manufacturer status register (Ind. 0x1002)
#define CAN_MAN_STATUS_ANOUT   0x00000001  // Manufacturer status register (Ind. 0x1002)
                                           // 0x1 NO slew rate control

#define CAN_VENDOR_ID          0x000000BE  // Vendor ID of identity object (Ind. 0x1018, sub 0x1)

// Product code of identity object (Ind. 0x1018, sub 0x2)
#define CAN_PROJECT_CODE_DUMMY            0x0000  // Configuration error occurred
#define CAN_PROJECT_CODE_DIOC             0x0041  // Digital inputs, counters and digital outputs
#define CAN_PROJECT_CODE_ANALOG_16BIT     0x0042  // Analog 16 bit
#define CAN_PROJECT_CODE_ANALOG_32BIT     0x0043  // Analog 32 bit (reserved)
#define CAN_PROJECT_CODE_DEVICE_VARIANT   0x0005

#define CAN_REV_NUM						0x00120014
										// Revision number of identity object (Ind. 0x1018, sub 0x3)
										// 0x0012 identifies CANopen behaviour of the device
										// 0x0014 defines the device version

// *** Device profile dependent defaults ***

#define CAN_RPDO_TRTYPE			    	255	// Receive PDO default transmission type
#define CAN_TPDO_TRTYPE				    255	// Transmit PDO default transmission type
#define CAN_TPDO_INHIBIT_100MCS			0	// TPDO inhibit default time in hundreds of microseconds
#define CAN_RPDO_ET_MS		    		0	// RPDO event timer default time in milliseconds
#define CAN_TPDO_ET_MS				    0	// TPDO event timer default time in milliseconds
#define CAN_TPDO_SYNC_START		    	0	// TPDO SYNC start value

#define CAN_NOF_LOAD_COMM_1				40	// Re-store communication 1 configuration size, 32 min
#define CAN_NOF_LOAD_COMM_2				10	// Re-store communication 2 configuration size, do NOT edit
#define CAN_NOF_LOAD_APPL				23  // Re-store application configuration size

#define CAN_NOF_ERRBEH_SUBIND			1	// Highest sub-index of the error behaviour object (1..254)
#define CAN_SUBIND_ERRBEH_COMM			1	// Communication error behaviour subindex

// *** IOremote profile masks ***

#define MASK_ANINP_INT_UP_LIMIT     0x1  // Upper limit exceeded
#define MASK_ANINP_INT_LOW_LIMIT    0x2  // Input below low limit
#define MASK_ANINP_INT_DELTA        0x4  // Input changed by more then delta

#define MASK_COUNTER_INT_UP_LIMIT   0x1  // Counter upper limit exceeded
#define MASK_COUNTER_INT_DELTA      0x4  // Counter changed by more then delta

#define MASK_DIGOUT_EMCY_CS   0xFFFF	// Default digital output short circuit emergency mask (2 blocks)
#define MASK_ANOUT_EMCY_CS    0xFF	  // Default analog output short circuit emergency mask
#define MASK_ANOUT_EMCY_LD    0xFF	  // Default analog output load dump emergency mask

// *** Additional emergency codes ***

#define CAN_EMCY_INT_DISABLED     0x0080  // Warning: global interrupt disabled

#define CAN_EMCY_SHORT_CIRCUIT    0x2320  // Digital or analog outputs short circuit
#define CAN_EMCY_LOAD_DUMP        0x2330  // Load dump at analog outputs
#define CAN_EMCY_ERROR_STATE      0xFF80  // Device is in the error state

// *** Application-related object dictionary entries ***

#define INDEX_SRDO_COMM_1				0x1301
#define INDEX_SRDO_MAP_1				0x1381
#define INDEX_SRDO_COMM_2				0x1302
#define INDEX_SRDO_MAP_2				0x1382

#define INDEX_SRDO_COMM_DIGINP    INDEX_SRDO_COMM_1
#define INDEX_SRDO_MAP_DIGINP     INDEX_SRDO_MAP_1
#define INDEX_SRDO_COMM_DIGOUT    INDEX_SRDO_COMM_2
#define INDEX_SRDO_MAP_DIGOUT     INDEX_SRDO_MAP_2

#define INDEX_SRDO_COMM_ANINP_1			INDEX_SRDO_COMM_1
#define INDEX_SRDO_MAP_ANINP_1			INDEX_SRDO_MAP_1
#define INDEX_SRDO_COMM_ANINP_2			INDEX_SRDO_COMM_2
#define INDEX_SRDO_MAP_ANINP_2			INDEX_SRDO_MAP_2

#define INDEX_SRDO_COMM_ANOUT_1			INDEX_SRDO_COMM_1
#define INDEX_SRDO_MAP_ANOUT_1			INDEX_SRDO_MAP_1
#define INDEX_SRDO_COMM_ANOUT_2			INDEX_SRDO_COMM_2
#define INDEX_SRDO_MAP_ANOUT_2			INDEX_SRDO_MAP_2

#define INDEX_TRNPDO_COMM_DIGINP		0x1800
#define INDEX_TRNPDO_MAP_DIGINP			0x1A00

#define INDEX_RCVPDO_COMM_DIGOUT		0x1400
#define INDEX_RCVPDO_MAP_DIGOUT			0x1600

#define INDEX_RCVPDO_COMM_COUNTER_2		0x1401
#define INDEX_RCVPDO_COMM_COUNTER_3		0x1402
#define INDEX_RCVPDO_COMM_COUNTER_4		0x1403
#define INDEX_RCVPDO_MAP_COUNTER_2		0x1601
#define INDEX_RCVPDO_MAP_COUNTER_3		0x1602
#define INDEX_RCVPDO_MAP_COUNTER_4		0x1603

#define INDEX_TRNPDO_COMM_COUNTER_2		0x1801
#define INDEX_TRNPDO_COMM_COUNTER_3		0x1802
#define INDEX_TRNPDO_COMM_COUNTER_4		0x1803
#define INDEX_TRNPDO_MAP_COUNTER_2		0x1A01
#define INDEX_TRNPDO_MAP_COUNTER_3		0x1A02
#define INDEX_TRNPDO_MAP_COUNTER_4		0x1A03

#define INDEX_TRNPDO_COMM_ANINP_2		0x1801
#define INDEX_TRNPDO_COMM_ANINP_3		0x1802
#define INDEX_TRNPDO_MAP_ANINP_2		0x1A01
#define INDEX_TRNPDO_MAP_ANINP_3		0x1A02

#define INDEX_RCVPDO_COMM_ANOUT_2		0x1401
#define INDEX_RCVPDO_COMM_ANOUT_3		0x1402
#define INDEX_RCVPDO_MAP_ANOUT_2		0x1601
#define INDEX_RCVPDO_MAP_ANOUT_3		0x1602


#define INDEX_DIGINP_DATA           0x6000  // Read input 8 bit
#define INDEX_DIGINP_POLARITY       0x6002  // Polarity input 8 bit
#define INDEX_DIGINP_INT_ENABLE     0x6005  // Digital input global interrupt enable
#define INDEX_DIGINP_IMASK_ANY      0x6006  // Interrupt mask any change 8 bit
#define INDEX_DIGINP_IMASK_L_H      0x6007  // Interrupt mask low-to-high change 8 bit
#define INDEX_DIGINP_IMASK_H_L      0x6008  // Interrupt mask high-to-low change 8 bit

#define INDEX_DIGOUT_DATA           0x6200  // Write output 8 bit
#define INDEX_DIGOUT_POLARITY       0x6202  // Change polarity output 8 bit
#define INDEX_DIGOUT_ERRMODE        0x6206  // Error mode output 8 bit
#define INDEX_DIGOUT_ERRVALUE       0x6207  // Error value output 8 bit
#define INDEX_DIGOUT_FILTER         0x6208  // Filter mask output 8 bit

#define INDEX_ANINP_DATA_16         0x6401  // Read analog input 16 bit
#define INDEX_ANINP_DATA_32         0x6402  // Read analog input 32 bit
#define INDEX_ANINP_DATA_FLOAT      0x6403  // Read analog input float
#define INDEX_ANINP_INT_TRIGGER     0x6421  // Analog input interrupt trigger selection
#define INDEX_ANINP_INT_SOURCE      0x6422  // Analog input interrupt source
#define INDEX_ANINP_INT_ENABLE      0x6423  // Analog input global interrupt enable
#define INDEX_ANINP_UPPER           0x6424  // Analog input interrupt upper limit integer
#define INDEX_ANINP_LOWER           0x6425  // Analog input interrupt lower limit integer
#define INDEX_ANINP_DELTA_UNS       0x6426  // Analog input interrupt delta unsigned
#define INDEX_ANINP_OFFSET          0x642E  // Analog input offset float
#define INDEX_ANINP_SCALING         0x642F  // Analog input scaling float

#define INDEX_ANOUT_DATA_16         0x6411  // Write analog output 16 bit
#define INDEX_ANOUT_DATA_32         0x6412  // Write analog output 32 bit
#define INDEX_ANOUT_ERRMODE         0x6443  // Analog output error mode
#define INDEX_ANOUT_ERRVALUE        0x6444  // Analog output error value integer


#define INDEX_DEVICE_CONFIG         0x2000
#define SUBIND_CONFIG_DIGINP        1
#define SUBIND_CONFIG_DIGOUT        2
#define SUBIND_CONFIG_ANINP         3
#define SUBIND_CONFIG_ANOUT         4
#define SUBIND_CONFIG_AIO_TYPE      5
#define SUBIND_CONFIG_AI_RES        6
#define SUBIND_CONFIG_AO_RES        7

#define R2DIO_CONFIG_SUBINDS        4  // 0x2000 object subindexes for digital IO
#define R2AI_CONFIG_SUBINDS		  		7  // 0x2000 object subindexes for analog inputs
#define R2AO_CONFIG_SUBINDS         7  // 0x2000 object subindexes for analog outputs

#define INDEX_ANINP_RANGE           0x2001
#define INDEX_ANINP_RATE            0x2002

#define INDEX_ANOUT_RANGE           0x2008

#define INDEX_DIGOUT_STATUS         0x2010
#define INDEX_DIGOUT_EMCY_INHIBIT   0x2011  // Digital outputs emergency inhibit time
#define INDEX_DIGOUT_EMCY_CS_MASK   0x2012  // Digital outputs short circuit emergency mask

#define INDEX_ANOUT_STATUS          0x2018
#define INDEX_ANOUT_EMCY_INHIBIT    0x2019  // Analog outputs emergency inhibit time
#define INDEX_ANOUT_EMCY_CS_MASK    0x201A  // Analog outputs short circuit emergency mask
#define INDEX_ANOUT_EMCY_LD_MASK    0x201B  // Analog outputs load dump emergency mask

#define INDEX_LOGICAL_CNT_SET       0x2020  // Logical counters set
#define INDEX_LOGICAL_CNT_DATA      0x2021  // Read logical counter (TPDO)
#define INDEX_COUNTERS_ZERO_MASK    0x2022  // Reset digital counters to zero mask, unsigned16

#define INDEX_DIGINP_TPDO_FORCED    0x2028  // Digital inputs TPDO forced mode, boolean

#define INDEX_ANOUT_DAC_CLOCK       0x2030  // DAC slew rate clock period
#define INDEX_ANOUT_DAC_STEP        0x2031  // DAC slew rate step

#define INDEX_EEPROM_CAN_NODEID     0x2110  // unsigned8
#define INDEX_EEPROM_CAN_BITRATE    0x2111  // unsigned8

#define INDEX_OCTET_STRING          0x2300  // Variable data length
#define SUBIND_OCS_RECEIVE          1
#define SUBIND_OCS_TRANSMIT         2

#define INDEX_COUNTER_DATA_UNS			0x2402	// Read 32 bit unsigned digital counter or reset the counter to some value
#define INDEX_COUNTER_INT_TRIGGER		0x2421	// Digital counter interrupt trigger selection
#define INDEX_COUNTER_INT_SOURCE		0x2422	// Digital counter interrupt source
#define INDEX_COUNTER_INT_ENABLE		0x2423	// Digital counter global interrupt enable
#define INDEX_COUNTER_UPPER_UNS			0x2424	// Digital counter interrupt upper limit unsigned
#define INDEX_COUNTER_DELTA_UNS			0x2426	// Digital counter interrupt delta unsigned
