// RPDOs from 385 to 416

#define CAN_SIZE_PDOMAP_1780		CAN_NOF_MAP	// 385th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1781		CAN_NOF_MAP	// 386th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1782		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1783		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1784		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1785		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1786		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1787		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1788		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1789		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_178A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_178B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_178C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_178D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_178E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_178F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1790		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1791		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1792		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1793		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1794		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1795		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1796		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1797		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1798		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1799		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_179A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_179B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_179C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_179D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_179E		CAN_NOF_MAP	// 415th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_179F		CAN_NOF_MAP	// 416th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 385
static unsigned32 map1780[CAN_SIZE_PDOMAP_1780];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+1
static unsigned32 map1781[CAN_SIZE_PDOMAP_1781];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+2
static unsigned32 map1782[CAN_SIZE_PDOMAP_1782];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+3
static unsigned32 map1783[CAN_SIZE_PDOMAP_1783];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+4
static unsigned32 map1784[CAN_SIZE_PDOMAP_1784];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+5
static unsigned32 map1785[CAN_SIZE_PDOMAP_1785];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+6
static unsigned32 map1786[CAN_SIZE_PDOMAP_1786];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+7
static unsigned32 map1787[CAN_SIZE_PDOMAP_1787];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+8
static unsigned32 map1788[CAN_SIZE_PDOMAP_1788];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+9
static unsigned32 map1789[CAN_SIZE_PDOMAP_1789];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+10
static unsigned32 map178A[CAN_SIZE_PDOMAP_178A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+11
static unsigned32 map178B[CAN_SIZE_PDOMAP_178B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+12
static unsigned32 map178C[CAN_SIZE_PDOMAP_178C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+13
static unsigned32 map178D[CAN_SIZE_PDOMAP_178D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+14
static unsigned32 map178E[CAN_SIZE_PDOMAP_178E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+15
static unsigned32 map178F[CAN_SIZE_PDOMAP_178F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+16
static unsigned32 map1790[CAN_SIZE_PDOMAP_1790];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+17
static unsigned32 map1791[CAN_SIZE_PDOMAP_1791];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+18
static unsigned32 map1792[CAN_SIZE_PDOMAP_1792];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+19
static unsigned32 map1793[CAN_SIZE_PDOMAP_1793];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+20
static unsigned32 map1794[CAN_SIZE_PDOMAP_1794];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+21
static unsigned32 map1795[CAN_SIZE_PDOMAP_1795];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+22
static unsigned32 map1796[CAN_SIZE_PDOMAP_1796];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+23
static unsigned32 map1797[CAN_SIZE_PDOMAP_1797];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+24
static unsigned32 map1798[CAN_SIZE_PDOMAP_1798];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+25
static unsigned32 map1799[CAN_SIZE_PDOMAP_1799];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+26
static unsigned32 map179A[CAN_SIZE_PDOMAP_179A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+27
static unsigned32 map179B[CAN_SIZE_PDOMAP_179B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+28
static unsigned32 map179C[CAN_SIZE_PDOMAP_179C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+29
static unsigned32 map179D[CAN_SIZE_PDOMAP_179D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+30
static unsigned32 map179E[CAN_SIZE_PDOMAP_179E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+31
static unsigned32 map179F[CAN_SIZE_PDOMAP_179F];
#endif


static void define_map_recv_385_416(void)
{
#if CAN_NOF_PDO_RECEIVE >= 385
	pdomap[385-1].pointer = map1780;
	pdomap[385-1].nmax = sizeof(map1780) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+1
	pdomap[385].pointer = map1781;
	pdomap[385].nmax = sizeof(map1781) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+2
	pdomap[385+1].pointer = map1782;
	pdomap[385+1].nmax = sizeof(map1782) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+3
	pdomap[385+2].pointer = map1783;
	pdomap[385+2].nmax = sizeof(map1783) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+4
	pdomap[385+3].pointer = map1784;
	pdomap[385+3].nmax = sizeof(map1784) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+5
	pdomap[385+4].pointer = map1785;
	pdomap[385+4].nmax = sizeof(map1785) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+6
	pdomap[385+5].pointer = map1786;
	pdomap[385+5].nmax = sizeof(map1786) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+7
	pdomap[385+6].pointer = map1787;
	pdomap[385+6].nmax = sizeof(map1787) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+8
	pdomap[385+7].pointer = map1788;
	pdomap[385+7].nmax = sizeof(map1788) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+9
	pdomap[385+8].pointer = map1789;
	pdomap[385+8].nmax = sizeof(map1789) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+10
	pdomap[385+9].pointer = map178A;
	pdomap[385+9].nmax = sizeof(map178A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+11
	pdomap[385+10].pointer = map178B;
	pdomap[385+10].nmax = sizeof(map178B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+12
	pdomap[385+11].pointer = map178C;
	pdomap[385+11].nmax = sizeof(map178C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+13
	pdomap[385+12].pointer = map178D;
	pdomap[385+12].nmax = sizeof(map178D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+14
	pdomap[385+13].pointer = map178E;
	pdomap[385+13].nmax = sizeof(map178E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+15
	pdomap[385+14].pointer = map178F;
	pdomap[385+14].nmax = sizeof(map178F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+16
	pdomap[385+15].pointer = map1790;
	pdomap[385+15].nmax = sizeof(map1790) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+17
	pdomap[385+16].pointer = map1791;
	pdomap[385+16].nmax = sizeof(map1791) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+18
	pdomap[385+17].pointer = map1792;
	pdomap[385+17].nmax = sizeof(map1792) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+19
	pdomap[385+18].pointer = map1793;
	pdomap[385+18].nmax = sizeof(map1793) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+20
	pdomap[385+19].pointer = map1794;
	pdomap[385+19].nmax = sizeof(map1794) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+21
	pdomap[385+20].pointer = map1795;
	pdomap[385+20].nmax = sizeof(map1795) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+22
	pdomap[385+21].pointer = map1796;
	pdomap[385+21].nmax = sizeof(map1796) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+23
	pdomap[385+22].pointer = map1797;
	pdomap[385+22].nmax = sizeof(map1797) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+24
	pdomap[385+23].pointer = map1798;
	pdomap[385+23].nmax = sizeof(map1798) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+25
	pdomap[385+24].pointer = map1799;
	pdomap[385+24].nmax = sizeof(map1799) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+26
	pdomap[385+25].pointer = map179A;
	pdomap[385+25].nmax = sizeof(map179A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+27
	pdomap[385+26].pointer = map179B;
	pdomap[385+26].nmax = sizeof(map179B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+28
	pdomap[385+27].pointer = map179C;
	pdomap[385+27].nmax = sizeof(map179C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+29
	pdomap[385+28].pointer = map179D;
	pdomap[385+28].nmax = sizeof(map179D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+30
	pdomap[385+29].pointer = map179E;
	pdomap[385+29].nmax = sizeof(map179E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 385+31
	pdomap[385+30].pointer = map179F;
	pdomap[385+30].nmax = sizeof(map179F) / sizeof(unsigned32);
#endif
}
