// RPDOs from 65 to 96

#define CAN_SIZE_PDOMAP_1640		CAN_NOF_MAP	// 65th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1641		CAN_NOF_MAP	// 66th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1642		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1643		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1644		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1645		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1646		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1647		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1648		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1649		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_164A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_164B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_164C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_164D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_164E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_164F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1650		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1651		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1652		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1653		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1654		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1655		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1656		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1657		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1658		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1659		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_165A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_165B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_165C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_165D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_165E		CAN_NOF_MAP	// 95th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_165F		CAN_NOF_MAP	// 96th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 65
static unsigned32 map1640[CAN_SIZE_PDOMAP_1640];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+1
static unsigned32 map1641[CAN_SIZE_PDOMAP_1641];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+2
static unsigned32 map1642[CAN_SIZE_PDOMAP_1642];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+3
static unsigned32 map1643[CAN_SIZE_PDOMAP_1643];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+4
static unsigned32 map1644[CAN_SIZE_PDOMAP_1644];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+5
static unsigned32 map1645[CAN_SIZE_PDOMAP_1645];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+6
static unsigned32 map1646[CAN_SIZE_PDOMAP_1646];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+7
static unsigned32 map1647[CAN_SIZE_PDOMAP_1647];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+8
static unsigned32 map1648[CAN_SIZE_PDOMAP_1648];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+9
static unsigned32 map1649[CAN_SIZE_PDOMAP_1649];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+10
static unsigned32 map164A[CAN_SIZE_PDOMAP_164A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+11
static unsigned32 map164B[CAN_SIZE_PDOMAP_164B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+12
static unsigned32 map164C[CAN_SIZE_PDOMAP_164C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+13
static unsigned32 map164D[CAN_SIZE_PDOMAP_164D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+14
static unsigned32 map164E[CAN_SIZE_PDOMAP_164E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+15
static unsigned32 map164F[CAN_SIZE_PDOMAP_164F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+16
static unsigned32 map1650[CAN_SIZE_PDOMAP_1650];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+17
static unsigned32 map1651[CAN_SIZE_PDOMAP_1651];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+18
static unsigned32 map1652[CAN_SIZE_PDOMAP_1652];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+19
static unsigned32 map1653[CAN_SIZE_PDOMAP_1653];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+20
static unsigned32 map1654[CAN_SIZE_PDOMAP_1654];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+21
static unsigned32 map1655[CAN_SIZE_PDOMAP_1655];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+22
static unsigned32 map1656[CAN_SIZE_PDOMAP_1656];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+23
static unsigned32 map1657[CAN_SIZE_PDOMAP_1657];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+24
static unsigned32 map1658[CAN_SIZE_PDOMAP_1658];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+25
static unsigned32 map1659[CAN_SIZE_PDOMAP_1659];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+26
static unsigned32 map165A[CAN_SIZE_PDOMAP_165A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+27
static unsigned32 map165B[CAN_SIZE_PDOMAP_165B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+28
static unsigned32 map165C[CAN_SIZE_PDOMAP_165C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+29
static unsigned32 map165D[CAN_SIZE_PDOMAP_165D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+30
static unsigned32 map165E[CAN_SIZE_PDOMAP_165E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+31
static unsigned32 map165F[CAN_SIZE_PDOMAP_165F];
#endif


static void define_map_recv_065_096(void)
{
#if CAN_NOF_PDO_RECEIVE >= 65
	pdomap[65-1].pointer = map1640;
	pdomap[65-1].nmax = sizeof(map1640) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+1
	pdomap[65].pointer = map1641;
	pdomap[65].nmax = sizeof(map1641) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+2
	pdomap[65+1].pointer = map1642;
	pdomap[65+1].nmax = sizeof(map1642) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+3
	pdomap[65+2].pointer = map1643;
	pdomap[65+2].nmax = sizeof(map1643) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+4
	pdomap[65+3].pointer = map1644;
	pdomap[65+3].nmax = sizeof(map1644) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+5
	pdomap[65+4].pointer = map1645;
	pdomap[65+4].nmax = sizeof(map1645) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+6
	pdomap[65+5].pointer = map1646;
	pdomap[65+5].nmax = sizeof(map1646) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+7
	pdomap[65+6].pointer = map1647;
	pdomap[65+6].nmax = sizeof(map1647) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+8
	pdomap[65+7].pointer = map1648;
	pdomap[65+7].nmax = sizeof(map1648) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+9
	pdomap[65+8].pointer = map1649;
	pdomap[65+8].nmax = sizeof(map1649) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+10
	pdomap[65+9].pointer = map164A;
	pdomap[65+9].nmax = sizeof(map164A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+11
	pdomap[65+10].pointer = map164B;
	pdomap[65+10].nmax = sizeof(map164B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+12
	pdomap[65+11].pointer = map164C;
	pdomap[65+11].nmax = sizeof(map164C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+13
	pdomap[65+12].pointer = map164D;
	pdomap[65+12].nmax = sizeof(map164D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+14
	pdomap[65+13].pointer = map164E;
	pdomap[65+13].nmax = sizeof(map164E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+15
	pdomap[65+14].pointer = map164F;
	pdomap[65+14].nmax = sizeof(map164F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+16
	pdomap[65+15].pointer = map1650;
	pdomap[65+15].nmax = sizeof(map1650) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+17
	pdomap[65+16].pointer = map1651;
	pdomap[65+16].nmax = sizeof(map1651) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+18
	pdomap[65+17].pointer = map1652;
	pdomap[65+17].nmax = sizeof(map1652) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+19
	pdomap[65+18].pointer = map1653;
	pdomap[65+18].nmax = sizeof(map1653) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+20
	pdomap[65+19].pointer = map1654;
	pdomap[65+19].nmax = sizeof(map1654) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+21
	pdomap[65+20].pointer = map1655;
	pdomap[65+20].nmax = sizeof(map1655) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+22
	pdomap[65+21].pointer = map1656;
	pdomap[65+21].nmax = sizeof(map1656) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+23
	pdomap[65+22].pointer = map1657;
	pdomap[65+22].nmax = sizeof(map1657) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+24
	pdomap[65+23].pointer = map1658;
	pdomap[65+23].nmax = sizeof(map1658) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+25
	pdomap[65+24].pointer = map1659;
	pdomap[65+24].nmax = sizeof(map1659) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+26
	pdomap[65+25].pointer = map165A;
	pdomap[65+25].nmax = sizeof(map165A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+27
	pdomap[65+26].pointer = map165B;
	pdomap[65+26].nmax = sizeof(map165B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+28
	pdomap[65+27].pointer = map165C;
	pdomap[65+27].nmax = sizeof(map165C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+29
	pdomap[65+28].pointer = map165D;
	pdomap[65+28].nmax = sizeof(map165D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+30
	pdomap[65+29].pointer = map165E;
	pdomap[65+29].nmax = sizeof(map165E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 65+31
	pdomap[65+30].pointer = map165F;
	pdomap[65+30].nmax = sizeof(map165F) / sizeof(unsigned32);
#endif
}
