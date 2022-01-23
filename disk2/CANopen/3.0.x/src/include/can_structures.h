// *** Various CANopen data structures and buffers definitions ***

struct time_of_day {	// Data type TIME_OF_DAY structure.
	unsigned32 ms;
	unsigned16 days;
};

union cansdob0 {		// SDO byte 0 extracted data.
	struct segm {		//  For segmented/expedited transfers.
		unsigned8 ndata;		// Size of data in a segment.
		unsigned8 bit_0;		// Bit 0: Data size indication flag etc.
		unsigned8 bit_1;		// Bit 1: E flag etc.
		unsigned8 toggle;		// Toggle bit value.
	} sg;
	struct block {		//  For block transfers.
		unsigned8 sub;		// Sub-command specifier.
		unsigned8 crc;		// CRC support flag; No of bytes in a frame for can_client_send_block_frame(...).
		unsigned8 ds;		// Data size indication flag; Number of valid bytes in the last frame; Sequence number.
		unsigned8 lf;		// Last segment flag.
	} bl;
};

struct sdoixs {			//  SDO indexes
	canindex sdoind;		// Communication SDO index (0x1200 .. 0x12FF)
	canindex index;			// Application object dictionary index OR CRC with end SDO block protocol.
	cansubind subind;		// and subindex
};

struct cancache {		// Data send cache
	int16 busy;				// Data busy flag, >= 0 if busy
	unsigned8 capture;		// Data capture and new data flag - to handle non-atomic data busy flag
	canframe cf;
};

struct cansdo {			// SDO data internal presentation with explicit fields
	unsigned8 cs;			// SDO command specifier - client or server
	struct sdoixs si;
	union cansdob0 b0;
	canbyte bd[8];			// CAN frame data
};

struct sdosrvfull {		// SDO server FULL transactions work buffer
	int16 busy;				// Data busy flag, >= 0 if busy
	unsigned8 capture;		// Data capture boolean flag - to handle non-atomic data busy flag
	unsigned8 toggle;		// Toggle bit value; Sequence number error flag for block protocol.
	unsigned32 timeout;		// Single operation timeout counter 2.2.x
	struct sdoixs si;
	canbyte *bufbeg;		// Data buffer begin pointer
	canbyte *bufpnt;		// Data buffer current pointer
	unsigned32 rembytes;	// Remained to transfer data size
	unsigned8 dynamem;		// Dynamic memory operation flag
#if CAN_PROTOCOL_BLOCK == TRUE
	unsigned32 totbytes;	// Total transferred data size for block protocol
	unsigned8 blksize;		// Block size
	unsigned8 crc;			// CRC support flag for block protocol
	unsigned8 seq;			// Sequence number for block protocol
	unsigned8 sub;			// Subcommand / upload operation for block protocol
#endif
};

struct sdostatus {		// SDO client status codes
	int16 state;			// State during and after client transaction
	unsigned32 abortcode;	// SDO abort code
};

struct sdoclttrans {	// SDO BASIC client transactions support structure
	unsigned8 adjcs;		// Adjacent command specifier or seqno for block upload
	struct sdostatus ss;
	struct cansdo sd;
	canbyte *bufpnt;		// Data buffer current pointer for block protocol
	unsigned32 rembytes;	// Remained to transfer data size
	unsigned8 blksize;		// Block size and CAN frame operation flag
};

struct sdocltbasic {	// SDO client BASIC transactions work buffer
	int16 busy;				// Data busy flag, >= 0 if busy
	unsigned8 capture;		// Data capture boolean flag - to handle non-atomic data busy flag
	unsigned32 timeout;		// Timeout counter 2.2.x
	struct sdoclttrans ct;
};

struct sdocltappl {		// Client application support structure
	unsigned8 operation;	// SDO transfer operation
	cannode node;			// Node-ID of the SDO server
	unsigned32 datasize;	// User data size, bytes. Needed only if datapnt != NULL.
	canbyte *datapnt;		// User data buffer pointer
	struct sdoixs si;
	struct sdostatus ss;
};

struct store {
	canindex index;			// Object index
	unsigned16 submask01;		// Subindex mask (subindexes 1..16)
};

struct lssaddress {		// LSS Address
	unsigned32 vendorid;
	unsigned32 prodcode;
	unsigned32 revnum;
	unsigned32 serial;
};

struct lssidentify {		// LSS address for identify rempte slave protocol
	unsigned32 vendorid;
	unsigned32 prodcode;
	unsigned32 revnum_low;
	unsigned32 revnum_high;
	unsigned32 serial_low;
	unsigned32 serial_high;
};
