// RPDOs from 129 to 160

#define CAN_SIZE_PDOMAP_1680		CAN_NOF_MAP	// 129th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1681		CAN_NOF_MAP	// 130th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1682		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1683		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1684		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1685		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1686		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1687		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1688		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1689		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_168A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_168B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_168C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_168D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_168E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_168F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1690		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1691		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1692		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1693		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1694		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1695		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1696		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1697		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1698		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1699		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_169A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_169B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_169C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_169D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_169E		CAN_NOF_MAP	// 159th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_169F		CAN_NOF_MAP	// 160th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 129
static unsigned32 map1680[CAN_SIZE_PDOMAP_1680];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+1
static unsigned32 map1681[CAN_SIZE_PDOMAP_1681];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+2
static unsigned32 map1682[CAN_SIZE_PDOMAP_1682];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+3
static unsigned32 map1683[CAN_SIZE_PDOMAP_1683];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+4
static unsigned32 map1684[CAN_SIZE_PDOMAP_1684];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+5
static unsigned32 map1685[CAN_SIZE_PDOMAP_1685];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+6
static unsigned32 map1686[CAN_SIZE_PDOMAP_1686];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+7
static unsigned32 map1687[CAN_SIZE_PDOMAP_1687];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+8
static unsigned32 map1688[CAN_SIZE_PDOMAP_1688];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+9
static unsigned32 map1689[CAN_SIZE_PDOMAP_1689];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+10
static unsigned32 map168A[CAN_SIZE_PDOMAP_168A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+11
static unsigned32 map168B[CAN_SIZE_PDOMAP_168B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+12
static unsigned32 map168C[CAN_SIZE_PDOMAP_168C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+13
static unsigned32 map168D[CAN_SIZE_PDOMAP_168D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+14
static unsigned32 map168E[CAN_SIZE_PDOMAP_168E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+15
static unsigned32 map168F[CAN_SIZE_PDOMAP_168F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+16
static unsigned32 map1690[CAN_SIZE_PDOMAP_1690];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+17
static unsigned32 map1691[CAN_SIZE_PDOMAP_1691];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+18
static unsigned32 map1692[CAN_SIZE_PDOMAP_1692];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+19
static unsigned32 map1693[CAN_SIZE_PDOMAP_1693];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+20
static unsigned32 map1694[CAN_SIZE_PDOMAP_1694];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+21
static unsigned32 map1695[CAN_SIZE_PDOMAP_1695];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+22
static unsigned32 map1696[CAN_SIZE_PDOMAP_1696];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+23
static unsigned32 map1697[CAN_SIZE_PDOMAP_1697];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+24
static unsigned32 map1698[CAN_SIZE_PDOMAP_1698];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+25
static unsigned32 map1699[CAN_SIZE_PDOMAP_1699];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+26
static unsigned32 map169A[CAN_SIZE_PDOMAP_169A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+27
static unsigned32 map169B[CAN_SIZE_PDOMAP_169B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+28
static unsigned32 map169C[CAN_SIZE_PDOMAP_169C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+29
static unsigned32 map169D[CAN_SIZE_PDOMAP_169D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+30
static unsigned32 map169E[CAN_SIZE_PDOMAP_169E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+31
static unsigned32 map169F[CAN_SIZE_PDOMAP_169F];
#endif


static void define_map_recv_129_160(void)
{
#if CAN_NOF_PDO_RECEIVE >= 129
	pdomap[129-1].pointer = map1680;
	pdomap[129-1].nmax = sizeof(map1680) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+1
	pdomap[129].pointer = map1681;
	pdomap[129].nmax = sizeof(map1681) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+2
	pdomap[129+1].pointer = map1682;
	pdomap[129+1].nmax = sizeof(map1682) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+3
	pdomap[129+2].pointer = map1683;
	pdomap[129+2].nmax = sizeof(map1683) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+4
	pdomap[129+3].pointer = map1684;
	pdomap[129+3].nmax = sizeof(map1684) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+5
	pdomap[129+4].pointer = map1685;
	pdomap[129+4].nmax = sizeof(map1685) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+6
	pdomap[129+5].pointer = map1686;
	pdomap[129+5].nmax = sizeof(map1686) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+7
	pdomap[129+6].pointer = map1687;
	pdomap[129+6].nmax = sizeof(map1687) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+8
	pdomap[129+7].pointer = map1688;
	pdomap[129+7].nmax = sizeof(map1688) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+9
	pdomap[129+8].pointer = map1689;
	pdomap[129+8].nmax = sizeof(map1689) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+10
	pdomap[129+9].pointer = map168A;
	pdomap[129+9].nmax = sizeof(map168A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+11
	pdomap[129+10].pointer = map168B;
	pdomap[129+10].nmax = sizeof(map168B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+12
	pdomap[129+11].pointer = map168C;
	pdomap[129+11].nmax = sizeof(map168C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+13
	pdomap[129+12].pointer = map168D;
	pdomap[129+12].nmax = sizeof(map168D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+14
	pdomap[129+13].pointer = map168E;
	pdomap[129+13].nmax = sizeof(map168E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+15
	pdomap[129+14].pointer = map168F;
	pdomap[129+14].nmax = sizeof(map168F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+16
	pdomap[129+15].pointer = map1690;
	pdomap[129+15].nmax = sizeof(map1690) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+17
	pdomap[129+16].pointer = map1691;
	pdomap[129+16].nmax = sizeof(map1691) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+18
	pdomap[129+17].pointer = map1692;
	pdomap[129+17].nmax = sizeof(map1692) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+19
	pdomap[129+18].pointer = map1693;
	pdomap[129+18].nmax = sizeof(map1693) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+20
	pdomap[129+19].pointer = map1694;
	pdomap[129+19].nmax = sizeof(map1694) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+21
	pdomap[129+20].pointer = map1695;
	pdomap[129+20].nmax = sizeof(map1695) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+22
	pdomap[129+21].pointer = map1696;
	pdomap[129+21].nmax = sizeof(map1696) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+23
	pdomap[129+22].pointer = map1697;
	pdomap[129+22].nmax = sizeof(map1697) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+24
	pdomap[129+23].pointer = map1698;
	pdomap[129+23].nmax = sizeof(map1698) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+25
	pdomap[129+24].pointer = map1699;
	pdomap[129+24].nmax = sizeof(map1699) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+26
	pdomap[129+25].pointer = map169A;
	pdomap[129+25].nmax = sizeof(map169A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+27
	pdomap[129+26].pointer = map169B;
	pdomap[129+26].nmax = sizeof(map169B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+28
	pdomap[129+27].pointer = map169C;
	pdomap[129+27].nmax = sizeof(map169C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+29
	pdomap[129+28].pointer = map169D;
	pdomap[129+28].nmax = sizeof(map169D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+30
	pdomap[129+29].pointer = map169E;
	pdomap[129+29].nmax = sizeof(map169E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 129+31
	pdomap[129+30].pointer = map169F;
	pdomap[129+30].nmax = sizeof(map169F) / sizeof(unsigned32);
#endif
}
