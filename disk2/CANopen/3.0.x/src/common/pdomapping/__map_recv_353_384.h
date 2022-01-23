// RPDOs from 353 to 384

#define CAN_SIZE_PDOMAP_1760		CAN_NOF_MAP	// 353rd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1761		CAN_NOF_MAP	// 354th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1762		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1763		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1764		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1765		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1766		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1767		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1768		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1769		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_176A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_176B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_176C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_176D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_176E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_176F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1770		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1771		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1772		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1773		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1774		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1775		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1776		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1777		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1778		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1779		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_177A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_177B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_177C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_177D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_177E		CAN_NOF_MAP	// 383rd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_177F		CAN_NOF_MAP	// 384th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 353
static unsigned32 map1760[CAN_SIZE_PDOMAP_1760];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+1
static unsigned32 map1761[CAN_SIZE_PDOMAP_1761];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+2
static unsigned32 map1762[CAN_SIZE_PDOMAP_1762];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+3
static unsigned32 map1763[CAN_SIZE_PDOMAP_1763];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+4
static unsigned32 map1764[CAN_SIZE_PDOMAP_1764];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+5
static unsigned32 map1765[CAN_SIZE_PDOMAP_1765];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+6
static unsigned32 map1766[CAN_SIZE_PDOMAP_1766];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+7
static unsigned32 map1767[CAN_SIZE_PDOMAP_1767];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+8
static unsigned32 map1768[CAN_SIZE_PDOMAP_1768];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+9
static unsigned32 map1769[CAN_SIZE_PDOMAP_1769];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+10
static unsigned32 map176A[CAN_SIZE_PDOMAP_176A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+11
static unsigned32 map176B[CAN_SIZE_PDOMAP_176B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+12
static unsigned32 map176C[CAN_SIZE_PDOMAP_176C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+13
static unsigned32 map176D[CAN_SIZE_PDOMAP_176D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+14
static unsigned32 map176E[CAN_SIZE_PDOMAP_176E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+15
static unsigned32 map176F[CAN_SIZE_PDOMAP_176F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+16
static unsigned32 map1770[CAN_SIZE_PDOMAP_1770];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+17
static unsigned32 map1771[CAN_SIZE_PDOMAP_1771];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+18
static unsigned32 map1772[CAN_SIZE_PDOMAP_1772];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+19
static unsigned32 map1773[CAN_SIZE_PDOMAP_1773];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+20
static unsigned32 map1774[CAN_SIZE_PDOMAP_1774];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+21
static unsigned32 map1775[CAN_SIZE_PDOMAP_1775];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+22
static unsigned32 map1776[CAN_SIZE_PDOMAP_1776];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+23
static unsigned32 map1777[CAN_SIZE_PDOMAP_1777];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+24
static unsigned32 map1778[CAN_SIZE_PDOMAP_1778];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+25
static unsigned32 map1779[CAN_SIZE_PDOMAP_1779];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+26
static unsigned32 map177A[CAN_SIZE_PDOMAP_177A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+27
static unsigned32 map177B[CAN_SIZE_PDOMAP_177B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+28
static unsigned32 map177C[CAN_SIZE_PDOMAP_177C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+29
static unsigned32 map177D[CAN_SIZE_PDOMAP_177D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+30
static unsigned32 map177E[CAN_SIZE_PDOMAP_177E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+31
static unsigned32 map177F[CAN_SIZE_PDOMAP_177F];
#endif


static void define_map_recv_353_384(void)
{
#if CAN_NOF_PDO_RECEIVE >= 353
	pdomap[353-1].pointer = map1760;
	pdomap[353-1].nmax = sizeof(map1760) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+1
	pdomap[353].pointer = map1761;
	pdomap[353].nmax = sizeof(map1761) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+2
	pdomap[353+1].pointer = map1762;
	pdomap[353+1].nmax = sizeof(map1762) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+3
	pdomap[353+2].pointer = map1763;
	pdomap[353+2].nmax = sizeof(map1763) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+4
	pdomap[353+3].pointer = map1764;
	pdomap[353+3].nmax = sizeof(map1764) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+5
	pdomap[353+4].pointer = map1765;
	pdomap[353+4].nmax = sizeof(map1765) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+6
	pdomap[353+5].pointer = map1766;
	pdomap[353+5].nmax = sizeof(map1766) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+7
	pdomap[353+6].pointer = map1767;
	pdomap[353+6].nmax = sizeof(map1767) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+8
	pdomap[353+7].pointer = map1768;
	pdomap[353+7].nmax = sizeof(map1768) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+9
	pdomap[353+8].pointer = map1769;
	pdomap[353+8].nmax = sizeof(map1769) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+10
	pdomap[353+9].pointer = map176A;
	pdomap[353+9].nmax = sizeof(map176A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+11
	pdomap[353+10].pointer = map176B;
	pdomap[353+10].nmax = sizeof(map176B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+12
	pdomap[353+11].pointer = map176C;
	pdomap[353+11].nmax = sizeof(map176C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+13
	pdomap[353+12].pointer = map176D;
	pdomap[353+12].nmax = sizeof(map176D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+14
	pdomap[353+13].pointer = map176E;
	pdomap[353+13].nmax = sizeof(map176E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+15
	pdomap[353+14].pointer = map176F;
	pdomap[353+14].nmax = sizeof(map176F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+16
	pdomap[353+15].pointer = map1770;
	pdomap[353+15].nmax = sizeof(map1770) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+17
	pdomap[353+16].pointer = map1771;
	pdomap[353+16].nmax = sizeof(map1771) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+18
	pdomap[353+17].pointer = map1772;
	pdomap[353+17].nmax = sizeof(map1772) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+19
	pdomap[353+18].pointer = map1773;
	pdomap[353+18].nmax = sizeof(map1773) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+20
	pdomap[353+19].pointer = map1774;
	pdomap[353+19].nmax = sizeof(map1774) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+21
	pdomap[353+20].pointer = map1775;
	pdomap[353+20].nmax = sizeof(map1775) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+22
	pdomap[353+21].pointer = map1776;
	pdomap[353+21].nmax = sizeof(map1776) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+23
	pdomap[353+22].pointer = map1777;
	pdomap[353+22].nmax = sizeof(map1777) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+24
	pdomap[353+23].pointer = map1778;
	pdomap[353+23].nmax = sizeof(map1778) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+25
	pdomap[353+24].pointer = map1779;
	pdomap[353+24].nmax = sizeof(map1779) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+26
	pdomap[353+25].pointer = map177A;
	pdomap[353+25].nmax = sizeof(map177A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+27
	pdomap[353+26].pointer = map177B;
	pdomap[353+26].nmax = sizeof(map177B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+28
	pdomap[353+27].pointer = map177C;
	pdomap[353+27].nmax = sizeof(map177C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+29
	pdomap[353+28].pointer = map177D;
	pdomap[353+28].nmax = sizeof(map177D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+30
	pdomap[353+29].pointer = map177E;
	pdomap[353+29].nmax = sizeof(map177E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 353+31
	pdomap[353+30].pointer = map177F;
	pdomap[353+30].nmax = sizeof(map177F) / sizeof(unsigned32);
#endif
}
