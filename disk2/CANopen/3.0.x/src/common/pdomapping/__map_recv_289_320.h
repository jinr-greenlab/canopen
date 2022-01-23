// RPDOs from 289 to 320

#define CAN_SIZE_PDOMAP_1720		CAN_NOF_MAP	// 289th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1721		CAN_NOF_MAP	// 290th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1722		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1723		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1724		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1725		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1726		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1727		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1728		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1729		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_172A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_172B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_172C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_172D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_172E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_172F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1730		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1731		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1732		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1733		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1734		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1735		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1736		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1737		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1738		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1739		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_173A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_173B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_173C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_173D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_173E		CAN_NOF_MAP	// 319th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_173F		CAN_NOF_MAP	// 320th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 289
static unsigned32 map1720[CAN_SIZE_PDOMAP_1720];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+1
static unsigned32 map1721[CAN_SIZE_PDOMAP_1721];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+2
static unsigned32 map1722[CAN_SIZE_PDOMAP_1722];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+3
static unsigned32 map1723[CAN_SIZE_PDOMAP_1723];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+4
static unsigned32 map1724[CAN_SIZE_PDOMAP_1724];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+5
static unsigned32 map1725[CAN_SIZE_PDOMAP_1725];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+6
static unsigned32 map1726[CAN_SIZE_PDOMAP_1726];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+7
static unsigned32 map1727[CAN_SIZE_PDOMAP_1727];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+8
static unsigned32 map1728[CAN_SIZE_PDOMAP_1728];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+9
static unsigned32 map1729[CAN_SIZE_PDOMAP_1729];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+10
static unsigned32 map172A[CAN_SIZE_PDOMAP_172A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+11
static unsigned32 map172B[CAN_SIZE_PDOMAP_172B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+12
static unsigned32 map172C[CAN_SIZE_PDOMAP_172C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+13
static unsigned32 map172D[CAN_SIZE_PDOMAP_172D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+14
static unsigned32 map172E[CAN_SIZE_PDOMAP_172E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+15
static unsigned32 map172F[CAN_SIZE_PDOMAP_172F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+16
static unsigned32 map1730[CAN_SIZE_PDOMAP_1730];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+17
static unsigned32 map1731[CAN_SIZE_PDOMAP_1731];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+18
static unsigned32 map1732[CAN_SIZE_PDOMAP_1732];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+19
static unsigned32 map1733[CAN_SIZE_PDOMAP_1733];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+20
static unsigned32 map1734[CAN_SIZE_PDOMAP_1734];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+21
static unsigned32 map1735[CAN_SIZE_PDOMAP_1735];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+22
static unsigned32 map1736[CAN_SIZE_PDOMAP_1736];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+23
static unsigned32 map1737[CAN_SIZE_PDOMAP_1737];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+24
static unsigned32 map1738[CAN_SIZE_PDOMAP_1738];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+25
static unsigned32 map1739[CAN_SIZE_PDOMAP_1739];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+26
static unsigned32 map173A[CAN_SIZE_PDOMAP_173A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+27
static unsigned32 map173B[CAN_SIZE_PDOMAP_173B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+28
static unsigned32 map173C[CAN_SIZE_PDOMAP_173C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+29
static unsigned32 map173D[CAN_SIZE_PDOMAP_173D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+30
static unsigned32 map173E[CAN_SIZE_PDOMAP_173E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+31
static unsigned32 map173F[CAN_SIZE_PDOMAP_173F];
#endif


static void define_map_recv_289_320(void)
{
#if CAN_NOF_PDO_RECEIVE >= 289
	pdomap[289-1].pointer = map1720;
	pdomap[289-1].nmax = sizeof(map1720) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+1
	pdomap[289].pointer = map1721;
	pdomap[289].nmax = sizeof(map1721) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+2
	pdomap[289+1].pointer = map1722;
	pdomap[289+1].nmax = sizeof(map1722) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+3
	pdomap[289+2].pointer = map1723;
	pdomap[289+2].nmax = sizeof(map1723) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+4
	pdomap[289+3].pointer = map1724;
	pdomap[289+3].nmax = sizeof(map1724) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+5
	pdomap[289+4].pointer = map1725;
	pdomap[289+4].nmax = sizeof(map1725) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+6
	pdomap[289+5].pointer = map1726;
	pdomap[289+5].nmax = sizeof(map1726) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+7
	pdomap[289+6].pointer = map1727;
	pdomap[289+6].nmax = sizeof(map1727) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+8
	pdomap[289+7].pointer = map1728;
	pdomap[289+7].nmax = sizeof(map1728) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+9
	pdomap[289+8].pointer = map1729;
	pdomap[289+8].nmax = sizeof(map1729) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+10
	pdomap[289+9].pointer = map172A;
	pdomap[289+9].nmax = sizeof(map172A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+11
	pdomap[289+10].pointer = map172B;
	pdomap[289+10].nmax = sizeof(map172B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+12
	pdomap[289+11].pointer = map172C;
	pdomap[289+11].nmax = sizeof(map172C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+13
	pdomap[289+12].pointer = map172D;
	pdomap[289+12].nmax = sizeof(map172D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+14
	pdomap[289+13].pointer = map172E;
	pdomap[289+13].nmax = sizeof(map172E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+15
	pdomap[289+14].pointer = map172F;
	pdomap[289+14].nmax = sizeof(map172F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+16
	pdomap[289+15].pointer = map1730;
	pdomap[289+15].nmax = sizeof(map1730) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+17
	pdomap[289+16].pointer = map1731;
	pdomap[289+16].nmax = sizeof(map1731) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+18
	pdomap[289+17].pointer = map1732;
	pdomap[289+17].nmax = sizeof(map1732) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+19
	pdomap[289+18].pointer = map1733;
	pdomap[289+18].nmax = sizeof(map1733) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+20
	pdomap[289+19].pointer = map1734;
	pdomap[289+19].nmax = sizeof(map1734) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+21
	pdomap[289+20].pointer = map1735;
	pdomap[289+20].nmax = sizeof(map1735) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+22
	pdomap[289+21].pointer = map1736;
	pdomap[289+21].nmax = sizeof(map1736) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+23
	pdomap[289+22].pointer = map1737;
	pdomap[289+22].nmax = sizeof(map1737) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+24
	pdomap[289+23].pointer = map1738;
	pdomap[289+23].nmax = sizeof(map1738) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+25
	pdomap[289+24].pointer = map1739;
	pdomap[289+24].nmax = sizeof(map1739) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+26
	pdomap[289+25].pointer = map173A;
	pdomap[289+25].nmax = sizeof(map173A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+27
	pdomap[289+26].pointer = map173B;
	pdomap[289+26].nmax = sizeof(map173B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+28
	pdomap[289+27].pointer = map173C;
	pdomap[289+27].nmax = sizeof(map173C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+29
	pdomap[289+28].pointer = map173D;
	pdomap[289+28].nmax = sizeof(map173D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+30
	pdomap[289+29].pointer = map173E;
	pdomap[289+29].nmax = sizeof(map173E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 289+31
	pdomap[289+30].pointer = map173F;
	pdomap[289+30].nmax = sizeof(map173F) / sizeof(unsigned32);
#endif
}
