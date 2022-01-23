// RPDOs from 161 to 192

#define CAN_SIZE_PDOMAP_16A0		CAN_NOF_MAP	// 161st receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_16A1		CAN_NOF_MAP	// 162nd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_16A2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16A3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16A4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16A5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16A6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16A7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16A8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16A9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16AA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16AB		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16AC		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16AD		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16AE		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16AF		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16B9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16BA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16BB		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16BC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16BD		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16BE		CAN_NOF_MAP	// 191st receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_16BF		CAN_NOF_MAP	// 192nd receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 161
static unsigned32 map16A0[CAN_SIZE_PDOMAP_16A0];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+1
static unsigned32 map16A1[CAN_SIZE_PDOMAP_16A1];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+2
static unsigned32 map16A2[CAN_SIZE_PDOMAP_16A2];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+3
static unsigned32 map16A3[CAN_SIZE_PDOMAP_16A3];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+4
static unsigned32 map16A4[CAN_SIZE_PDOMAP_16A4];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+5
static unsigned32 map16A5[CAN_SIZE_PDOMAP_16A5];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+6
static unsigned32 map16A6[CAN_SIZE_PDOMAP_16A6];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+7
static unsigned32 map16A7[CAN_SIZE_PDOMAP_16A7];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+8
static unsigned32 map16A8[CAN_SIZE_PDOMAP_16A8];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+9
static unsigned32 map16A9[CAN_SIZE_PDOMAP_16A9];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+10
static unsigned32 map16AA[CAN_SIZE_PDOMAP_16AA];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+11
static unsigned32 map16AB[CAN_SIZE_PDOMAP_16AB];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+12
static unsigned32 map16AC[CAN_SIZE_PDOMAP_16AC];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+13
static unsigned32 map16AD[CAN_SIZE_PDOMAP_16AD];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+14
static unsigned32 map16AE[CAN_SIZE_PDOMAP_16AE];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+15
static unsigned32 map16AF[CAN_SIZE_PDOMAP_16AF];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+16
static unsigned32 map16B0[CAN_SIZE_PDOMAP_16B0];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+17
static unsigned32 map16B1[CAN_SIZE_PDOMAP_16B1];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+18
static unsigned32 map16B2[CAN_SIZE_PDOMAP_16B2];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+19
static unsigned32 map16B3[CAN_SIZE_PDOMAP_16B3];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+20
static unsigned32 map16B4[CAN_SIZE_PDOMAP_16B4];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+21
static unsigned32 map16B5[CAN_SIZE_PDOMAP_16B5];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+22
static unsigned32 map16B6[CAN_SIZE_PDOMAP_16B6];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+23
static unsigned32 map16B7[CAN_SIZE_PDOMAP_16B7];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+24
static unsigned32 map16B8[CAN_SIZE_PDOMAP_16B8];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+25
static unsigned32 map16B9[CAN_SIZE_PDOMAP_16B9];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+26
static unsigned32 map16BA[CAN_SIZE_PDOMAP_16BA];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+27
static unsigned32 map16BB[CAN_SIZE_PDOMAP_16BB];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+28
static unsigned32 map16BC[CAN_SIZE_PDOMAP_16BC];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+29
static unsigned32 map16BD[CAN_SIZE_PDOMAP_16BD];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+30
static unsigned32 map16BE[CAN_SIZE_PDOMAP_16BE];
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+31
static unsigned32 map16BF[CAN_SIZE_PDOMAP_16BF];
#endif


static void define_map_recv_161_192(void)
{
#if CAN_NOF_PDO_RECEIVE >= 161
	pdomap[161-1].pointer = map16A0;
	pdomap[161-1].nmax = sizeof(map16A0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+1
	pdomap[161].pointer = map16A1;
	pdomap[161].nmax = sizeof(map16A1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+2
	pdomap[161+1].pointer = map16A2;
	pdomap[161+1].nmax = sizeof(map16A2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+3
	pdomap[161+2].pointer = map16A3;
	pdomap[161+2].nmax = sizeof(map16A3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+4
	pdomap[161+3].pointer = map16A4;
	pdomap[161+3].nmax = sizeof(map16A4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+5
	pdomap[161+4].pointer = map16A5;
	pdomap[161+4].nmax = sizeof(map16A5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+6
	pdomap[161+5].pointer = map16A6;
	pdomap[161+5].nmax = sizeof(map16A6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+7
	pdomap[161+6].pointer = map16A7;
	pdomap[161+6].nmax = sizeof(map16A7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+8
	pdomap[161+7].pointer = map16A8;
	pdomap[161+7].nmax = sizeof(map16A8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+9
	pdomap[161+8].pointer = map16A9;
	pdomap[161+8].nmax = sizeof(map16A9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+10
	pdomap[161+9].pointer = map16AA;
	pdomap[161+9].nmax = sizeof(map16AA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+11
	pdomap[161+10].pointer = map16AB;
	pdomap[161+10].nmax = sizeof(map16AB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+12
	pdomap[161+11].pointer = map16AC;
	pdomap[161+11].nmax = sizeof(map16AC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+13
	pdomap[161+12].pointer = map16AD;
	pdomap[161+12].nmax = sizeof(map16AD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+14
	pdomap[161+13].pointer = map16AE;
	pdomap[161+13].nmax = sizeof(map16AE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+15
	pdomap[161+14].pointer = map16AF;
	pdomap[161+14].nmax = sizeof(map16AF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+16
	pdomap[161+15].pointer = map16B0;
	pdomap[161+15].nmax = sizeof(map16B0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+17
	pdomap[161+16].pointer = map16B1;
	pdomap[161+16].nmax = sizeof(map16B1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+18
	pdomap[161+17].pointer = map16B2;
	pdomap[161+17].nmax = sizeof(map16B2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+19
	pdomap[161+18].pointer = map16B3;
	pdomap[161+18].nmax = sizeof(map16B3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+20
	pdomap[161+19].pointer = map16B4;
	pdomap[161+19].nmax = sizeof(map16B4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+21
	pdomap[161+20].pointer = map16B5;
	pdomap[161+20].nmax = sizeof(map16B5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+22
	pdomap[161+21].pointer = map16B6;
	pdomap[161+21].nmax = sizeof(map16B6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+23
	pdomap[161+22].pointer = map16B7;
	pdomap[161+22].nmax = sizeof(map16B7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+24
	pdomap[161+23].pointer = map16B8;
	pdomap[161+23].nmax = sizeof(map16B8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+25
	pdomap[161+24].pointer = map16B9;
	pdomap[161+24].nmax = sizeof(map16B9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+26
	pdomap[161+25].pointer = map16BA;
	pdomap[161+25].nmax = sizeof(map16BA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+27
	pdomap[161+26].pointer = map16BB;
	pdomap[161+26].nmax = sizeof(map16BB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+28
	pdomap[161+27].pointer = map16BC;
	pdomap[161+27].nmax = sizeof(map16BC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+29
	pdomap[161+28].pointer = map16BD;
	pdomap[161+28].nmax = sizeof(map16BD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+30
	pdomap[161+29].pointer = map16BE;
	pdomap[161+29].nmax = sizeof(map16BE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 161+31
	pdomap[161+30].pointer = map16BF;
	pdomap[161+30].nmax = sizeof(map16BF) / sizeof(unsigned32);
#endif
}
