#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 1)

#define CRC_POLYNOM		0x1021

#define CRC_POLY_F		(CRC_POLYNOM | 0x10000)
#define CRC_TOPBIT		0x8000

#define CRC_POLY_7		(CRC_POLY_F << 7)
#define CRC_POLY_6		(CRC_POLY_F << 6)
#define CRC_POLY_5		(CRC_POLY_F << 5)
#define CRC_POLY_4		(CRC_POLY_F << 4)
#define CRC_POLY_3		(CRC_POLY_F << 3)
#define CRC_POLY_2		(CRC_POLY_F << 2)
#define CRC_POLY_1		(CRC_POLY_F << 1)
#define CRC_POLY_0		(CRC_POLY_F)

#define CRC_CHECK_7		0x800000
#define CRC_CHECK_6		0x400000
#define CRC_CHECK_5		0x200000
#define CRC_CHECK_4		0x100000
#define CRC_CHECK_3		0x80000
#define CRC_CHECK_2		0x40000
#define CRC_CHECK_1		0x20000
#define CRC_CHECK_0		0x10000

#if CAN_CRC_MODE == CRCTABLE
static unsigned16 crc;
static unsigned16 crctable[256];
#else
static unsigned32 crc;
#endif

void can_start_crc(unsigned16 val)
{
	unsigned16 cnt, bit;

	crc = val;
	for (cnt = 0; cnt < 16; cnt++) {
		bit = crc & 1;
		if (bit) crc ^= CRC_POLYNOM;
		crc >>= 1;
		if (bit) crc |= CRC_TOPBIT;
	}
}

unsigned16 can_calc_crc(unsigned8 data)
{
#if CAN_CRC_MODE == CRCTABLE
	unsigned8 tel;

	tel = crc >> 8;
	crc <<= 8;
	crc |= data;
	crc ^= crctable[tel];
	return crc;
#else
	crc <<= 8;
	crc |= data;
	if (crc & CRC_CHECK_7) crc ^= CRC_POLY_7;
	if (crc & CRC_CHECK_6) crc ^= CRC_POLY_6;
	if (crc & CRC_CHECK_5) crc ^= CRC_POLY_5;
	if (crc & CRC_CHECK_4) crc ^= CRC_POLY_4;
	if (crc & CRC_CHECK_3) crc ^= CRC_POLY_3;
	if (crc & CRC_CHECK_2) crc ^= CRC_POLY_2;
	if (crc & CRC_CHECK_1) crc ^= CRC_POLY_1;
	if (crc & CRC_CHECK_0) crc ^= CRC_POLY_0;
	return (unsigned16)crc;
#endif
}

void can_init_crc(void)
{
#if CAN_CRC_MODE == CRCTABLE
	unsigned16 cnt;
	unsigned32 tmp;

	for (cnt = 0; cnt < 256; cnt++) {
		tmp = cnt << 16;
		if (tmp & CRC_CHECK_7) tmp ^= CRC_POLY_7;
		if (tmp & CRC_CHECK_6) tmp ^= CRC_POLY_6;
		if (tmp & CRC_CHECK_5) tmp ^= CRC_POLY_5;
		if (tmp & CRC_CHECK_4) tmp ^= CRC_POLY_4;
		if (tmp & CRC_CHECK_3) tmp ^= CRC_POLY_3;
		if (tmp & CRC_CHECK_2) tmp ^= CRC_POLY_2;
		if (tmp & CRC_CHECK_1) tmp ^= CRC_POLY_1;
		if (tmp & CRC_CHECK_0) tmp ^= CRC_POLY_0;
		crctable[cnt] = (unsigned16)tmp;
	}
#endif
}

int16 check_node_id(cannode node)	// 2.2.1
{
	if (node >= CAN_NODE_ID_MIN && node <= CAN_NODE_ID_MAX) return CAN_RETOK;
	return CAN_ERRET_NODEID;
}

int16 check_bitrate_index(unsigned8 br)		// 2.2.1
{
	if (br == CIA_BITRATE_INDEX_1000 || br == CIA_BITRATE_INDEX_800 ||
		br == CIA_BITRATE_INDEX_500 || br == CIA_BITRATE_INDEX_250 ||
		br == CIA_BITRATE_INDEX_125 || br == CIA_BITRATE_INDEX_50 ||
		br == CIA_BITRATE_INDEX_20 || br == CIA_BITRATE_INDEX_10) {
		return CAN_RETOK;
	}
	return CAN_ERRET_BITRATE;
}

cannode get_dev_nodeid(void)    // 3.0.1 new function
{
  return node_id;
}

unsigned8 get_dev_node_state(void)    // 3.0.1 new function
{
  return node_state;
}

void clear_can_data(canbyte *data)		// 2.3.1 some changes
{
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;
}

void u16_to_canframe(unsigned16 ud, canbyte *data)		// 2.3.1 some changes
{
	canbyte *bpnt;

	bpnt = (canbyte*)&ud;
	data[0] = bpnt[0];
	data[1] = bpnt[1];
}

unsigned16 canframe_to_u16(canbyte *data)		// 2.3.1 some changes
{
	unsigned16 buf;
	canbyte *bpnt;

	bpnt = (canbyte*)&buf;
	bpnt[0] = data[0];
	bpnt[1] = data[1];
	return buf;
}

void u32_to_canframe(unsigned32 ud, canbyte *data)		// 2.3.1 some changes
{
	canbyte *bpnt;

	bpnt = (canbyte*)&ud;
	data[0] = bpnt[0];
	data[1] = bpnt[1];
	data[2] = bpnt[2];
	data[3] = bpnt[3];
}

unsigned32 canframe_to_u32(canbyte *data)		// 2.3.1 some changes
{
	unsigned32 buf;
	canbyte *bpnt;

	bpnt = (canbyte*)&buf;
	bpnt[0] = data[0];
	bpnt[1] = data[1];
	bpnt[2] = data[2];
	bpnt[3] = data[3];
	return buf;
}

#endif
