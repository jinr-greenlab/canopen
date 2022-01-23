// RPDOs from 257 to 288

#define CAN_SIZE_PDOMAP_1700		CAN_NOF_MAP	// 257th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1701		CAN_NOF_MAP	// 258th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1702		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1703		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1704		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1705		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1706		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1707		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1708		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1709		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_170A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_170B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_170C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_170D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_170E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_170F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1710		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1711		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1712		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1713		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1714		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1715		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1716		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1717		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1718		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1719		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_171A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_171B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_171C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_171D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_171E		CAN_NOF_MAP	// 287th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_171F		CAN_NOF_MAP	// 288th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 257
static unsigned32 map1700[CAN_SIZE_PDOMAP_1700];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+1
static unsigned32 map1701[CAN_SIZE_PDOMAP_1701];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+2
static unsigned32 map1702[CAN_SIZE_PDOMAP_1702];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+3
static unsigned32 map1703[CAN_SIZE_PDOMAP_1703];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+4
static unsigned32 map1704[CAN_SIZE_PDOMAP_1704];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+5
static unsigned32 map1705[CAN_SIZE_PDOMAP_1705];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+6
static unsigned32 map1706[CAN_SIZE_PDOMAP_1706];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+7
static unsigned32 map1707[CAN_SIZE_PDOMAP_1707];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+8
static unsigned32 map1708[CAN_SIZE_PDOMAP_1708];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+9
static unsigned32 map1709[CAN_SIZE_PDOMAP_1709];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+10
static unsigned32 map170A[CAN_SIZE_PDOMAP_170A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+11
static unsigned32 map170B[CAN_SIZE_PDOMAP_170B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+12
static unsigned32 map170C[CAN_SIZE_PDOMAP_170C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+13
static unsigned32 map170D[CAN_SIZE_PDOMAP_170D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+14
static unsigned32 map170E[CAN_SIZE_PDOMAP_170E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+15
static unsigned32 map170F[CAN_SIZE_PDOMAP_170F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+16
static unsigned32 map1710[CAN_SIZE_PDOMAP_1710];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+17
static unsigned32 map1711[CAN_SIZE_PDOMAP_1711];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+18
static unsigned32 map1712[CAN_SIZE_PDOMAP_1712];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+19
static unsigned32 map1713[CAN_SIZE_PDOMAP_1713];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+20
static unsigned32 map1714[CAN_SIZE_PDOMAP_1714];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+21
static unsigned32 map1715[CAN_SIZE_PDOMAP_1715];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+22
static unsigned32 map1716[CAN_SIZE_PDOMAP_1716];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+23
static unsigned32 map1717[CAN_SIZE_PDOMAP_1717];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+24
static unsigned32 map1718[CAN_SIZE_PDOMAP_1718];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+25
static unsigned32 map1719[CAN_SIZE_PDOMAP_1719];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+26
static unsigned32 map171A[CAN_SIZE_PDOMAP_171A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+27
static unsigned32 map171B[CAN_SIZE_PDOMAP_171B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+28
static unsigned32 map171C[CAN_SIZE_PDOMAP_171C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+29
static unsigned32 map171D[CAN_SIZE_PDOMAP_171D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+30
static unsigned32 map171E[CAN_SIZE_PDOMAP_171E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+31
static unsigned32 map171F[CAN_SIZE_PDOMAP_171F];
#endif


static void define_map_recv_257_288(void)
{
#if CAN_NOF_PDO_RECEIVE >= 257
	pdomap[257-1].pointer = map1700;
	pdomap[257-1].nmax = sizeof(map1700) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+1
	pdomap[257].pointer = map1701;
	pdomap[257].nmax = sizeof(map1701) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+2
	pdomap[257+1].pointer = map1702;
	pdomap[257+1].nmax = sizeof(map1702) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+3
	pdomap[257+2].pointer = map1703;
	pdomap[257+2].nmax = sizeof(map1703) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+4
	pdomap[257+3].pointer = map1704;
	pdomap[257+3].nmax = sizeof(map1704) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+5
	pdomap[257+4].pointer = map1705;
	pdomap[257+4].nmax = sizeof(map1705) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+6
	pdomap[257+5].pointer = map1706;
	pdomap[257+5].nmax = sizeof(map1706) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+7
	pdomap[257+6].pointer = map1707;
	pdomap[257+6].nmax = sizeof(map1707) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+8
	pdomap[257+7].pointer = map1708;
	pdomap[257+7].nmax = sizeof(map1708) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+9
	pdomap[257+8].pointer = map1709;
	pdomap[257+8].nmax = sizeof(map1709) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+10
	pdomap[257+9].pointer = map170A;
	pdomap[257+9].nmax = sizeof(map170A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+11
	pdomap[257+10].pointer = map170B;
	pdomap[257+10].nmax = sizeof(map170B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+12
	pdomap[257+11].pointer = map170C;
	pdomap[257+11].nmax = sizeof(map170C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+13
	pdomap[257+12].pointer = map170D;
	pdomap[257+12].nmax = sizeof(map170D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+14
	pdomap[257+13].pointer = map170E;
	pdomap[257+13].nmax = sizeof(map170E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+15
	pdomap[257+14].pointer = map170F;
	pdomap[257+14].nmax = sizeof(map170F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+16
	pdomap[257+15].pointer = map1710;
	pdomap[257+15].nmax = sizeof(map1710) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+17
	pdomap[257+16].pointer = map1711;
	pdomap[257+16].nmax = sizeof(map1711) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+18
	pdomap[257+17].pointer = map1712;
	pdomap[257+17].nmax = sizeof(map1712) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+19
	pdomap[257+18].pointer = map1713;
	pdomap[257+18].nmax = sizeof(map1713) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+20
	pdomap[257+19].pointer = map1714;
	pdomap[257+19].nmax = sizeof(map1714) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+21
	pdomap[257+20].pointer = map1715;
	pdomap[257+20].nmax = sizeof(map1715) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+22
	pdomap[257+21].pointer = map1716;
	pdomap[257+21].nmax = sizeof(map1716) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+23
	pdomap[257+22].pointer = map1717;
	pdomap[257+22].nmax = sizeof(map1717) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+24
	pdomap[257+23].pointer = map1718;
	pdomap[257+23].nmax = sizeof(map1718) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+25
	pdomap[257+24].pointer = map1719;
	pdomap[257+24].nmax = sizeof(map1719) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+26
	pdomap[257+25].pointer = map171A;
	pdomap[257+25].nmax = sizeof(map171A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+27
	pdomap[257+26].pointer = map171B;
	pdomap[257+26].nmax = sizeof(map171B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+28
	pdomap[257+27].pointer = map171C;
	pdomap[257+27].nmax = sizeof(map171C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+29
	pdomap[257+28].pointer = map171D;
	pdomap[257+28].nmax = sizeof(map171D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+30
	pdomap[257+29].pointer = map171E;
	pdomap[257+29].nmax = sizeof(map171E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 257+31
	pdomap[257+30].pointer = map171F;
	pdomap[257+30].nmax = sizeof(map171F) / sizeof(unsigned32);
#endif
}
