// RPDOs from 33 to 64

#define CAN_SIZE_PDOMAP_1620		CAN_NOF_MAP	// 33rd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1621		CAN_NOF_MAP	// 34th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1622		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1623		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1624		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1625		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1626		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1627		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1628		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1629		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_162A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_162B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_162C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_162D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_162E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_162F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1630		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1631		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1632		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1633		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1634		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1635		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1636		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1637		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1638		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1639		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_163A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_163B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_163C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_163D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_163E		CAN_NOF_MAP	// 63rd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_163F		CAN_NOF_MAP	// 64th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 33
static unsigned32 map1620[CAN_SIZE_PDOMAP_1620];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+1
static unsigned32 map1621[CAN_SIZE_PDOMAP_1621];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+2
static unsigned32 map1622[CAN_SIZE_PDOMAP_1622];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+3
static unsigned32 map1623[CAN_SIZE_PDOMAP_1623];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+4
static unsigned32 map1624[CAN_SIZE_PDOMAP_1624];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+5
static unsigned32 map1625[CAN_SIZE_PDOMAP_1625];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+6
static unsigned32 map1626[CAN_SIZE_PDOMAP_1626];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+7
static unsigned32 map1627[CAN_SIZE_PDOMAP_1627];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+8
static unsigned32 map1628[CAN_SIZE_PDOMAP_1628];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+9
static unsigned32 map1629[CAN_SIZE_PDOMAP_1629];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+10
static unsigned32 map162A[CAN_SIZE_PDOMAP_162A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+11
static unsigned32 map162B[CAN_SIZE_PDOMAP_162B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+12
static unsigned32 map162C[CAN_SIZE_PDOMAP_162C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+13
static unsigned32 map162D[CAN_SIZE_PDOMAP_162D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+14
static unsigned32 map162E[CAN_SIZE_PDOMAP_162E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+15
static unsigned32 map162F[CAN_SIZE_PDOMAP_162F];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+16
static unsigned32 map1630[CAN_SIZE_PDOMAP_1630];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+17
static unsigned32 map1631[CAN_SIZE_PDOMAP_1631];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+18
static unsigned32 map1632[CAN_SIZE_PDOMAP_1632];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+19
static unsigned32 map1633[CAN_SIZE_PDOMAP_1633];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+20
static unsigned32 map1634[CAN_SIZE_PDOMAP_1634];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+21
static unsigned32 map1635[CAN_SIZE_PDOMAP_1635];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+22
static unsigned32 map1636[CAN_SIZE_PDOMAP_1636];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+23
static unsigned32 map1637[CAN_SIZE_PDOMAP_1637];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+24
static unsigned32 map1638[CAN_SIZE_PDOMAP_1638];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+25
static unsigned32 map1639[CAN_SIZE_PDOMAP_1639];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+26
static unsigned32 map163A[CAN_SIZE_PDOMAP_163A];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+27
static unsigned32 map163B[CAN_SIZE_PDOMAP_163B];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+28
static unsigned32 map163C[CAN_SIZE_PDOMAP_163C];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+29
static unsigned32 map163D[CAN_SIZE_PDOMAP_163D];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+30
static unsigned32 map163E[CAN_SIZE_PDOMAP_163E];
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+31
static unsigned32 map163F[CAN_SIZE_PDOMAP_163F];
#endif


static void define_map_recv_033_064(void)
{
#if CAN_NOF_PDO_RECEIVE >= 33
	pdomap[33-1].pointer = map1620;
	pdomap[33-1].nmax = sizeof(map1620) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+1
	pdomap[33].pointer = map1621;
	pdomap[33].nmax = sizeof(map1621) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+2
	pdomap[33+1].pointer = map1622;
	pdomap[33+1].nmax = sizeof(map1622) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+3
	pdomap[33+2].pointer = map1623;
	pdomap[33+2].nmax = sizeof(map1623) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+4
	pdomap[33+3].pointer = map1624;
	pdomap[33+3].nmax = sizeof(map1624) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+5
	pdomap[33+4].pointer = map1625;
	pdomap[33+4].nmax = sizeof(map1625) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+6
	pdomap[33+5].pointer = map1626;
	pdomap[33+5].nmax = sizeof(map1626) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+7
	pdomap[33+6].pointer = map1627;
	pdomap[33+6].nmax = sizeof(map1627) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+8
	pdomap[33+7].pointer = map1628;
	pdomap[33+7].nmax = sizeof(map1628) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+9
	pdomap[33+8].pointer = map1629;
	pdomap[33+8].nmax = sizeof(map1629) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+10
	pdomap[33+9].pointer = map162A;
	pdomap[33+9].nmax = sizeof(map162A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+11
	pdomap[33+10].pointer = map162B;
	pdomap[33+10].nmax = sizeof(map162B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+12
	pdomap[33+11].pointer = map162C;
	pdomap[33+11].nmax = sizeof(map162C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+13
	pdomap[33+12].pointer = map162D;
	pdomap[33+12].nmax = sizeof(map162D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+14
	pdomap[33+13].pointer = map162E;
	pdomap[33+13].nmax = sizeof(map162E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+15
	pdomap[33+14].pointer = map162F;
	pdomap[33+14].nmax = sizeof(map162F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+16
	pdomap[33+15].pointer = map1630;
	pdomap[33+15].nmax = sizeof(map1630) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+17
	pdomap[33+16].pointer = map1631;
	pdomap[33+16].nmax = sizeof(map1631) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+18
	pdomap[33+17].pointer = map1632;
	pdomap[33+17].nmax = sizeof(map1632) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+19
	pdomap[33+18].pointer = map1633;
	pdomap[33+18].nmax = sizeof(map1633) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+20
	pdomap[33+19].pointer = map1634;
	pdomap[33+19].nmax = sizeof(map1634) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+21
	pdomap[33+20].pointer = map1635;
	pdomap[33+20].nmax = sizeof(map1635) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+22
	pdomap[33+21].pointer = map1636;
	pdomap[33+21].nmax = sizeof(map1636) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+23
	pdomap[33+22].pointer = map1637;
	pdomap[33+22].nmax = sizeof(map1637) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+24
	pdomap[33+23].pointer = map1638;
	pdomap[33+23].nmax = sizeof(map1638) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+25
	pdomap[33+24].pointer = map1639;
	pdomap[33+24].nmax = sizeof(map1639) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+26
	pdomap[33+25].pointer = map163A;
	pdomap[33+25].nmax = sizeof(map163A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+27
	pdomap[33+26].pointer = map163B;
	pdomap[33+26].nmax = sizeof(map163B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+28
	pdomap[33+27].pointer = map163C;
	pdomap[33+27].nmax = sizeof(map163C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+29
	pdomap[33+28].pointer = map163D;
	pdomap[33+28].nmax = sizeof(map163D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+30
	pdomap[33+29].pointer = map163E;
	pdomap[33+29].nmax = sizeof(map163E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 33+31
	pdomap[33+30].pointer = map163F;
	pdomap[33+30].nmax = sizeof(map163F) / sizeof(unsigned32);
#endif
}
