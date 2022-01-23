struct store {
  canindex index;         // Application object index
  unsigned16 submask01;   // Subindex mask (subindexes 1..16)
  unsigned8 flag;         // Re-store operation mode flag
};

struct object {    // Application object generic presentation
  canindex index;     // Object index
  cansubind subind;   // Object subindex
  int32 size;         // Object size
  canindex deftype;   // Object data type index
  int16 access;       // Object access mask
  canbyte *pnt;       // Object pointer
};

union numbers {        // Objects numeric data
	unsigned64 init;
	unsigned32 dt32[2];
	unsigned16 dt16[4];
	unsigned8 dt8[8];
	int8 i8;
	unsigned8 uns8;
	int16 i16;
	unsigned16 uns16;
	int32 i32;
	unsigned32 uns32;
	int64 i64;
	unsigned64 uns64;
	real32 re32;
	real64 re64;
};
