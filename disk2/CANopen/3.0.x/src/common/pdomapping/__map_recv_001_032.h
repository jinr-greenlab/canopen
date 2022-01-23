// RPDOs from 1 to 32

#define CAN_SIZE_PDOMAP_1600		CAN_NOF_MAP	// 1st receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1601		CAN_NOF_MAP	// 2nd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1602		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1603		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1604		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1605		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1606		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1607		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1608		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1609		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_160A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_160B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_160C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_160D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_160E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_160F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1610		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1611		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1612		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1613		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1614		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1615		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1616		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1617		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1618		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1619		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_161A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_161B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_161C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_161D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_161E		CAN_NOF_MAP	// 31st receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_161F		CAN_NOF_MAP	// 32nd receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 1
static unsigned32 map1600[CAN_SIZE_PDOMAP_1600];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+1
static unsigned32 map1601[CAN_SIZE_PDOMAP_1601];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+2
static unsigned32 map1602[CAN_SIZE_PDOMAP_1602];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+3
static unsigned32 map1603[CAN_SIZE_PDOMAP_1603];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+4
static unsigned32 map1604[CAN_SIZE_PDOMAP_1604];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+5
static unsigned32 map1605[CAN_SIZE_PDOMAP_1605];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+6
static unsigned32 map1606[CAN_SIZE_PDOMAP_1606];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+7
static unsigned32 map1607[CAN_SIZE_PDOMAP_1607];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+8
static unsigned32 map1608[CAN_SIZE_PDOMAP_1608];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+9
static unsigned32 map1609[CAN_SIZE_PDOMAP_1609];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+10
static unsigned32 map160A[CAN_SIZE_PDOMAP_160A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+11
static unsigned32 map160B[CAN_SIZE_PDOMAP_160B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+12
static unsigned32 map160C[CAN_SIZE_PDOMAP_160C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+13
static unsigned32 map160D[CAN_SIZE_PDOMAP_160D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+14
static unsigned32 map160E[CAN_SIZE_PDOMAP_160E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+15
static unsigned32 map160F[CAN_SIZE_PDOMAP_160F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+16
static unsigned32 map1610[CAN_SIZE_PDOMAP_1610];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+17
static unsigned32 map1611[CAN_SIZE_PDOMAP_1611];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+18
static unsigned32 map1612[CAN_SIZE_PDOMAP_1612];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+19
static unsigned32 map1613[CAN_SIZE_PDOMAP_1613];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+20
static unsigned32 map1614[CAN_SIZE_PDOMAP_1614];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+21
static unsigned32 map1615[CAN_SIZE_PDOMAP_1615];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+22
static unsigned32 map1616[CAN_SIZE_PDOMAP_1616];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+23
static unsigned32 map1617[CAN_SIZE_PDOMAP_1617];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+24
static unsigned32 map1618[CAN_SIZE_PDOMAP_1618];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+25
static unsigned32 map1619[CAN_SIZE_PDOMAP_1619];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+26
static unsigned32 map161A[CAN_SIZE_PDOMAP_161A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+27
static unsigned32 map161B[CAN_SIZE_PDOMAP_161B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+28
static unsigned32 map161C[CAN_SIZE_PDOMAP_161C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+29
static unsigned32 map161D[CAN_SIZE_PDOMAP_161D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+30
static unsigned32 map161E[CAN_SIZE_PDOMAP_161E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+31
static unsigned32 map161F[CAN_SIZE_PDOMAP_161F];
#endif


static void define_map_recv_001_032(void)
{
#if CAN_NOF_PDO_RECEIVE >= 1
	pdomap[1-1].pointer = map1600;
	pdomap[1-1].nmax = sizeof(map1600) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+1
	pdomap[1].pointer = map1601;
	pdomap[1].nmax = sizeof(map1601) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+2
	pdomap[1+1].pointer = map1602;
	pdomap[1+1].nmax = sizeof(map1602) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+3
	pdomap[1+2].pointer = map1603;
	pdomap[1+2].nmax = sizeof(map1603) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+4
	pdomap[1+3].pointer = map1604;
	pdomap[1+3].nmax = sizeof(map1604) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+5
	pdomap[1+4].pointer = map1605;
	pdomap[1+4].nmax = sizeof(map1605) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+6
	pdomap[1+5].pointer = map1606;
	pdomap[1+5].nmax = sizeof(map1606) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+7
	pdomap[1+6].pointer = map1607;
	pdomap[1+6].nmax = sizeof(map1607) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+8
	pdomap[1+7].pointer = map1608;
	pdomap[1+7].nmax = sizeof(map1608) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+9
	pdomap[1+8].pointer = map1609;
	pdomap[1+8].nmax = sizeof(map1609) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+10
	pdomap[1+9].pointer = map160A;
	pdomap[1+9].nmax = sizeof(map160A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+11
	pdomap[1+10].pointer = map160B;
	pdomap[1+10].nmax = sizeof(map160B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+12
	pdomap[1+11].pointer = map160C;
	pdomap[1+11].nmax = sizeof(map160C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+13
	pdomap[1+12].pointer = map160D;
	pdomap[1+12].nmax = sizeof(map160D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+14
	pdomap[1+13].pointer = map160E;
	pdomap[1+13].nmax = sizeof(map160E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+15
	pdomap[1+14].pointer = map160F;
	pdomap[1+14].nmax = sizeof(map160F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+16
	pdomap[1+15].pointer = map1610;
	pdomap[1+15].nmax = sizeof(map1610) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+17
	pdomap[1+16].pointer = map1611;
	pdomap[1+16].nmax = sizeof(map1611) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+18
	pdomap[1+17].pointer = map1612;
	pdomap[1+17].nmax = sizeof(map1612) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+19
	pdomap[1+18].pointer = map1613;
	pdomap[1+18].nmax = sizeof(map1613) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+20
	pdomap[1+19].pointer = map1614;
	pdomap[1+19].nmax = sizeof(map1614) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+21
	pdomap[1+20].pointer = map1615;
	pdomap[1+20].nmax = sizeof(map1615) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+22
	pdomap[1+21].pointer = map1616;
	pdomap[1+21].nmax = sizeof(map1616) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+23
	pdomap[1+22].pointer = map1617;
	pdomap[1+22].nmax = sizeof(map1617) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+24
	pdomap[1+23].pointer = map1618;
	pdomap[1+23].nmax = sizeof(map1618) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+25
	pdomap[1+24].pointer = map1619;
	pdomap[1+24].nmax = sizeof(map1619) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+26
	pdomap[1+25].pointer = map161A;
	pdomap[1+25].nmax = sizeof(map161A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+27
	pdomap[1+26].pointer = map161B;
	pdomap[1+26].nmax = sizeof(map161B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+28
	pdomap[1+27].pointer = map161C;
	pdomap[1+27].nmax = sizeof(map161C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+29
	pdomap[1+28].pointer = map161D;
	pdomap[1+28].nmax = sizeof(map161D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+30
	pdomap[1+29].pointer = map161E;
	pdomap[1+29].nmax = sizeof(map161E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 1+31
	pdomap[1+30].pointer = map161F;
	pdomap[1+30].nmax = sizeof(map161F) / sizeof(unsigned32);
#endif
}
