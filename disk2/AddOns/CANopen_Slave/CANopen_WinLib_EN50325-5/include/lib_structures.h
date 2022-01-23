// *** CANopen data structures and buffers definitions ***

union cansdob0 {		// SDO byte 0 explicit data presentation.
	struct segm {		//  For segmented/expedited transfers.
		unsigned8 ndata;		// The number of bytes in a segment that do not contain data.
		unsigned8 bit_0;		// Bit 0: Data size indication flag etc.
		unsigned8 bit_1;		// Bit 1: Expedited flag etc.
		unsigned8 toggle;		// Toggle bit value.
	} sg;
};

struct sdoixs {			// Application object
	canindex index;			// Application object dictionary index
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
	unsigned8 toggle;		// Toggle bit value
	unsigned32 timeout;		// Single operation timeout counter
	struct sdoixs si;
	canbyte *bufpnt;		// Data buffer current pointer
	unsigned32 rembytes;	// Remained to transfer data size
};

struct srdodata {
	unsigned8 len;						// CAN frame data length
	canbyte data[CAN_DATALEN_MAXIMUM];	// CAN frame raw data
};

struct srdostruct {		// EN50325-5 protocol support structure
	unsigned8 dir;				// Information direction sub01
	unsigned8 srvt;				// SRVT sub03, millisecond
	unsigned8 trtype;			// Transmission type sub04
	unsigned16 sct;				// Refresh-time / SCT sub02, millisecond
	unsigned32 id_odd;			// Odd CAN-ID sub05
	unsigned32 id_even;			// Even CAN-ID sub06
	unsigned16 signature;		// SRDO signature (CRC)
	unsigned8 config;			// SRDO object configuration (VALID / NOT_VALID)
	unsigned8 nrec;				// Number of mapped objects
	unsigned32 map[CAN_NOF_MAP_BYTEGR];		// SRDO mapped objects
	int16 srvt_cnt;				// SRVT counter, signed for the async OFF control.
	int32 sct_cnt;				// SCT counter, signed for the async OFF control
	int16 odev_cnt;				// Odd-even CAN-IDs delay transmission counter
	struct srdodata plain;		// Receive or transmit SRDO plain data
	struct srdodata bwinv;		// Receive SRDO bitwise inverted data
};
