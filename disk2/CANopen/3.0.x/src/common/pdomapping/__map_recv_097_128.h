// RPDOs from 97 to 128

#define CAN_SIZE_PDOMAP_1660		CAN_NOF_MAP	// 97th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1661		CAN_NOF_MAP	// 98th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1662		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1663		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1664		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1665		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1666		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1667		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1668		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1669		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_166A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_166B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_166C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_166D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_166E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_166F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1670		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1671		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1672		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1673		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1674		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1675		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1676		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1677		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1678		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1679		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_167A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_167B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_167C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_167D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_167E		CAN_NOF_MAP	// 127th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_167F		CAN_NOF_MAP	// 128th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 97
static unsigned32 map1660[CAN_SIZE_PDOMAP_1660];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+1
static unsigned32 map1661[CAN_SIZE_PDOMAP_1661];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+2
static unsigned32 map1662[CAN_SIZE_PDOMAP_1662];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+3
static unsigned32 map1663[CAN_SIZE_PDOMAP_1663];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+4
static unsigned32 map1664[CAN_SIZE_PDOMAP_1664];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+5
static unsigned32 map1665[CAN_SIZE_PDOMAP_1665];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+6
static unsigned32 map1666[CAN_SIZE_PDOMAP_1666];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+7
static unsigned32 map1667[CAN_SIZE_PDOMAP_1667];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+8
static unsigned32 map1668[CAN_SIZE_PDOMAP_1668];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+9
static unsigned32 map1669[CAN_SIZE_PDOMAP_1669];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+10
static unsigned32 map166A[CAN_SIZE_PDOMAP_166A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+11
static unsigned32 map166B[CAN_SIZE_PDOMAP_166B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+12
static unsigned32 map166C[CAN_SIZE_PDOMAP_166C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+13
static unsigned32 map166D[CAN_SIZE_PDOMAP_166D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+14
static unsigned32 map166E[CAN_SIZE_PDOMAP_166E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+15
static unsigned32 map166F[CAN_SIZE_PDOMAP_166F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+16
static unsigned32 map1670[CAN_SIZE_PDOMAP_1670];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+17
static unsigned32 map1671[CAN_SIZE_PDOMAP_1671];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+18
static unsigned32 map1672[CAN_SIZE_PDOMAP_1672];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+19
static unsigned32 map1673[CAN_SIZE_PDOMAP_1673];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+20
static unsigned32 map1674[CAN_SIZE_PDOMAP_1674];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+21
static unsigned32 map1675[CAN_SIZE_PDOMAP_1675];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+22
static unsigned32 map1676[CAN_SIZE_PDOMAP_1676];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+23
static unsigned32 map1677[CAN_SIZE_PDOMAP_1677];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+24
static unsigned32 map1678[CAN_SIZE_PDOMAP_1678];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+25
static unsigned32 map1679[CAN_SIZE_PDOMAP_1679];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+26
static unsigned32 map167A[CAN_SIZE_PDOMAP_167A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+27
static unsigned32 map167B[CAN_SIZE_PDOMAP_167B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+28
static unsigned32 map167C[CAN_SIZE_PDOMAP_167C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+29
static unsigned32 map167D[CAN_SIZE_PDOMAP_167D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+30
static unsigned32 map167E[CAN_SIZE_PDOMAP_167E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+31
static unsigned32 map167F[CAN_SIZE_PDOMAP_167F];
#endif


static void define_map_recv_097_128(void)
{
#if CAN_NOF_PDO_RECEIVE >= 97
	pdomap[97-1].pointer = map1660;
	pdomap[97-1].nmax = sizeof(map1660) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+1
	pdomap[97].pointer = map1661;
	pdomap[97].nmax = sizeof(map1661) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+2
	pdomap[97+1].pointer = map1662;
	pdomap[97+1].nmax = sizeof(map1662) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+3
	pdomap[97+2].pointer = map1663;
	pdomap[97+2].nmax = sizeof(map1663) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+4
	pdomap[97+3].pointer = map1664;
	pdomap[97+3].nmax = sizeof(map1664) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+5
	pdomap[97+4].pointer = map1665;
	pdomap[97+4].nmax = sizeof(map1665) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+6
	pdomap[97+5].pointer = map1666;
	pdomap[97+5].nmax = sizeof(map1666) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+7
	pdomap[97+6].pointer = map1667;
	pdomap[97+6].nmax = sizeof(map1667) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+8
	pdomap[97+7].pointer = map1668;
	pdomap[97+7].nmax = sizeof(map1668) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+9
	pdomap[97+8].pointer = map1669;
	pdomap[97+8].nmax = sizeof(map1669) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+10
	pdomap[97+9].pointer = map166A;
	pdomap[97+9].nmax = sizeof(map166A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+11
	pdomap[97+10].pointer = map166B;
	pdomap[97+10].nmax = sizeof(map166B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+12
	pdomap[97+11].pointer = map166C;
	pdomap[97+11].nmax = sizeof(map166C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+13
	pdomap[97+12].pointer = map166D;
	pdomap[97+12].nmax = sizeof(map166D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+14
	pdomap[97+13].pointer = map166E;
	pdomap[97+13].nmax = sizeof(map166E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+15
	pdomap[97+14].pointer = map166F;
	pdomap[97+14].nmax = sizeof(map166F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+16
	pdomap[97+15].pointer = map1670;
	pdomap[97+15].nmax = sizeof(map1670) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+17
	pdomap[97+16].pointer = map1671;
	pdomap[97+16].nmax = sizeof(map1671) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+18
	pdomap[97+17].pointer = map1672;
	pdomap[97+17].nmax = sizeof(map1672) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+19
	pdomap[97+18].pointer = map1673;
	pdomap[97+18].nmax = sizeof(map1673) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+20
	pdomap[97+19].pointer = map1674;
	pdomap[97+19].nmax = sizeof(map1674) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+21
	pdomap[97+20].pointer = map1675;
	pdomap[97+20].nmax = sizeof(map1675) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+22
	pdomap[97+21].pointer = map1676;
	pdomap[97+21].nmax = sizeof(map1676) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+23
	pdomap[97+22].pointer = map1677;
	pdomap[97+22].nmax = sizeof(map1677) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+24
	pdomap[97+23].pointer = map1678;
	pdomap[97+23].nmax = sizeof(map1678) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+25
	pdomap[97+24].pointer = map1679;
	pdomap[97+24].nmax = sizeof(map1679) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+26
	pdomap[97+25].pointer = map167A;
	pdomap[97+25].nmax = sizeof(map167A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+27
	pdomap[97+26].pointer = map167B;
	pdomap[97+26].nmax = sizeof(map167B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+28
	pdomap[97+27].pointer = map167C;
	pdomap[97+27].nmax = sizeof(map167C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+29
	pdomap[97+28].pointer = map167D;
	pdomap[97+28].nmax = sizeof(map167D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+30
	pdomap[97+29].pointer = map167E;
	pdomap[97+29].nmax = sizeof(map167E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 97+31
	pdomap[97+30].pointer = map167F;
	pdomap[97+30].nmax = sizeof(map167F) / sizeof(unsigned32);
#endif
}
