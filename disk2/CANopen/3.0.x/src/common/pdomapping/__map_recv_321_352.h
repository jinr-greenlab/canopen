// RPDOs from 321 to 352

#define CAN_SIZE_PDOMAP_1740		CAN_NOF_MAP	// 321st receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1741		CAN_NOF_MAP	// 322nd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1742		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1743		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1744		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1745		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1746		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1747		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1748		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1749		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_174A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_174B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_174C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_174D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_174E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_174F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1750		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1751		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1752		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1753		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1754		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1755		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1756		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1757		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1758		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1759		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_175A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_175B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_175C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_175D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_175E		CAN_NOF_MAP	// 351nd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_175F		CAN_NOF_MAP	// 352nd receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 321
static unsigned32 map1740[CAN_SIZE_PDOMAP_1740];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+1
static unsigned32 map1741[CAN_SIZE_PDOMAP_1741];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+2
static unsigned32 map1742[CAN_SIZE_PDOMAP_1742];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+3
static unsigned32 map1743[CAN_SIZE_PDOMAP_1743];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+4
static unsigned32 map1744[CAN_SIZE_PDOMAP_1744];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+5
static unsigned32 map1745[CAN_SIZE_PDOMAP_1745];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+6
static unsigned32 map1746[CAN_SIZE_PDOMAP_1746];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+7
static unsigned32 map1747[CAN_SIZE_PDOMAP_1747];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+8
static unsigned32 map1748[CAN_SIZE_PDOMAP_1748];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+9
static unsigned32 map1749[CAN_SIZE_PDOMAP_1749];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+10
static unsigned32 map174A[CAN_SIZE_PDOMAP_174A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+11
static unsigned32 map174B[CAN_SIZE_PDOMAP_174B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+12
static unsigned32 map174C[CAN_SIZE_PDOMAP_174C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+13
static unsigned32 map174D[CAN_SIZE_PDOMAP_174D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+14
static unsigned32 map174E[CAN_SIZE_PDOMAP_174E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+15
static unsigned32 map174F[CAN_SIZE_PDOMAP_174F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+16
static unsigned32 map1750[CAN_SIZE_PDOMAP_1750];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+17
static unsigned32 map1751[CAN_SIZE_PDOMAP_1751];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+18
static unsigned32 map1752[CAN_SIZE_PDOMAP_1752];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+19
static unsigned32 map1753[CAN_SIZE_PDOMAP_1753];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+20
static unsigned32 map1754[CAN_SIZE_PDOMAP_1754];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+21
static unsigned32 map1755[CAN_SIZE_PDOMAP_1755];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+22
static unsigned32 map1756[CAN_SIZE_PDOMAP_1756];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+23
static unsigned32 map1757[CAN_SIZE_PDOMAP_1757];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+24
static unsigned32 map1758[CAN_SIZE_PDOMAP_1758];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+25
static unsigned32 map1759[CAN_SIZE_PDOMAP_1759];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+26
static unsigned32 map175A[CAN_SIZE_PDOMAP_175A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+27
static unsigned32 map175B[CAN_SIZE_PDOMAP_175B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+28
static unsigned32 map175C[CAN_SIZE_PDOMAP_175C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+29
static unsigned32 map175D[CAN_SIZE_PDOMAP_175D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+30
static unsigned32 map175E[CAN_SIZE_PDOMAP_175E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+31
static unsigned32 map175F[CAN_SIZE_PDOMAP_175F];
#endif


static void define_map_recv_321_352(void)
{
#if CAN_NOF_PDO_RECEIVE >= 321
	pdomap[321-1].pointer = map1740;
	pdomap[321-1].nmax = sizeof(map1740) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+1
	pdomap[321].pointer = map1741;
	pdomap[321].nmax = sizeof(map1741) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+2
	pdomap[321+1].pointer = map1742;
	pdomap[321+1].nmax = sizeof(map1742) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+3
	pdomap[321+2].pointer = map1743;
	pdomap[321+2].nmax = sizeof(map1743) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+4
	pdomap[321+3].pointer = map1744;
	pdomap[321+3].nmax = sizeof(map1744) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+5
	pdomap[321+4].pointer = map1745;
	pdomap[321+4].nmax = sizeof(map1745) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+6
	pdomap[321+5].pointer = map1746;
	pdomap[321+5].nmax = sizeof(map1746) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+7
	pdomap[321+6].pointer = map1747;
	pdomap[321+6].nmax = sizeof(map1747) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+8
	pdomap[321+7].pointer = map1748;
	pdomap[321+7].nmax = sizeof(map1748) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+9
	pdomap[321+8].pointer = map1749;
	pdomap[321+8].nmax = sizeof(map1749) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+10
	pdomap[321+9].pointer = map174A;
	pdomap[321+9].nmax = sizeof(map174A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+11
	pdomap[321+10].pointer = map174B;
	pdomap[321+10].nmax = sizeof(map174B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+12
	pdomap[321+11].pointer = map174C;
	pdomap[321+11].nmax = sizeof(map174C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+13
	pdomap[321+12].pointer = map174D;
	pdomap[321+12].nmax = sizeof(map174D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+14
	pdomap[321+13].pointer = map174E;
	pdomap[321+13].nmax = sizeof(map174E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+15
	pdomap[321+14].pointer = map174F;
	pdomap[321+14].nmax = sizeof(map174F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+16
	pdomap[321+15].pointer = map1750;
	pdomap[321+15].nmax = sizeof(map1750) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+17
	pdomap[321+16].pointer = map1751;
	pdomap[321+16].nmax = sizeof(map1751) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+18
	pdomap[321+17].pointer = map1752;
	pdomap[321+17].nmax = sizeof(map1752) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+19
	pdomap[321+18].pointer = map1753;
	pdomap[321+18].nmax = sizeof(map1753) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+20
	pdomap[321+19].pointer = map1754;
	pdomap[321+19].nmax = sizeof(map1754) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+21
	pdomap[321+20].pointer = map1755;
	pdomap[321+20].nmax = sizeof(map1755) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+22
	pdomap[321+21].pointer = map1756;
	pdomap[321+21].nmax = sizeof(map1756) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+23
	pdomap[321+22].pointer = map1757;
	pdomap[321+22].nmax = sizeof(map1757) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+24
	pdomap[321+23].pointer = map1758;
	pdomap[321+23].nmax = sizeof(map1758) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+25
	pdomap[321+24].pointer = map1759;
	pdomap[321+24].nmax = sizeof(map1759) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+26
	pdomap[321+25].pointer = map175A;
	pdomap[321+25].nmax = sizeof(map175A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+27
	pdomap[321+26].pointer = map175B;
	pdomap[321+26].nmax = sizeof(map175B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+28
	pdomap[321+27].pointer = map175C;
	pdomap[321+27].nmax = sizeof(map175C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+29
	pdomap[321+28].pointer = map175D;
	pdomap[321+28].nmax = sizeof(map175D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+30
	pdomap[321+29].pointer = map175E;
	pdomap[321+29].nmax = sizeof(map175E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 321+31
	pdomap[321+30].pointer = map175F;
	pdomap[321+30].nmax = sizeof(map175F) / sizeof(unsigned32);
#endif
}
