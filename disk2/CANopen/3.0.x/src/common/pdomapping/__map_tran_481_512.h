// TPDOs from 481 to 512

#define CAN_SIZE_PDOMAP_1BE0		CAN_NOF_MAP	// 481st transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1BE1		CAN_NOF_MAP	// 482nd transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1BE2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BE3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BE4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BE5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BE6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BE7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BE8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BE9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BEA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BEB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BEC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BED	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BEE		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BEF		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BF9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BFA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BFB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BFC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BFD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BFE		CAN_NOF_MAP	// 511th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1BFF		CAN_NOF_MAP	// 512th transmit PDO mapping max. entries

#if CAN_NOF_PDO_TRANSMIT >= 481
static unsigned32 map1BE0[CAN_SIZE_PDOMAP_1BE0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+1
static unsigned32 map1BE1[CAN_SIZE_PDOMAP_1BE1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+2
static unsigned32 map1BE2[CAN_SIZE_PDOMAP_1BE2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+3
static unsigned32 map1BE3[CAN_SIZE_PDOMAP_1BE3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+4
static unsigned32 map1BE4[CAN_SIZE_PDOMAP_1BE4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+5
static unsigned32 map1BE5[CAN_SIZE_PDOMAP_1BE5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+6
static unsigned32 map1BE6[CAN_SIZE_PDOMAP_1BE6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+7
static unsigned32 map1BE7[CAN_SIZE_PDOMAP_1BE7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+8
static unsigned32 map1BE8[CAN_SIZE_PDOMAP_1BE8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+9
static unsigned32 map1BE9[CAN_SIZE_PDOMAP_1BE9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+10
static unsigned32 map1BEA[CAN_SIZE_PDOMAP_1BEA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+11
static unsigned32 map1BEB[CAN_SIZE_PDOMAP_1BEB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+12
static unsigned32 map1BEC[CAN_SIZE_PDOMAP_1BEC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+13
static unsigned32 map1BED[CAN_SIZE_PDOMAP_1BED];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+14
static unsigned32 map1BEE[CAN_SIZE_PDOMAP_1BEE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+15
static unsigned32 map1BEF[CAN_SIZE_PDOMAP_1BEF];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+16
static unsigned32 map1BF0[CAN_SIZE_PDOMAP_1BF0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+17
static unsigned32 map1BF1[CAN_SIZE_PDOMAP_1BF1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+18
static unsigned32 map1BF2[CAN_SIZE_PDOMAP_1BF2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+19
static unsigned32 map1BF3[CAN_SIZE_PDOMAP_1BF3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+20
static unsigned32 map1BF4[CAN_SIZE_PDOMAP_1BF4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+21
static unsigned32 map1BF5[CAN_SIZE_PDOMAP_1BF5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+22
static unsigned32 map1BF6[CAN_SIZE_PDOMAP_1BF6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+23
static unsigned32 map1BF7[CAN_SIZE_PDOMAP_1BF7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+24
static unsigned32 map1BF8[CAN_SIZE_PDOMAP_1BF8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+25
static unsigned32 map1BF9[CAN_SIZE_PDOMAP_1BF9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+26
static unsigned32 map1BFA[CAN_SIZE_PDOMAP_1BFA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+27
static unsigned32 map1BFB[CAN_SIZE_PDOMAP_1BFB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+28
static unsigned32 map1BFC[CAN_SIZE_PDOMAP_1BFC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+29
static unsigned32 map1BFD[CAN_SIZE_PDOMAP_1BFD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+30
static unsigned32 map1BFE[CAN_SIZE_PDOMAP_1BFE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+31
static unsigned32 map1BFF[CAN_SIZE_PDOMAP_1BFF];
#endif


static void define_map_tran_481_512(void)
{
#if CAN_NOF_PDO_TRANSMIT >= 481
	pdomap[CAN_NOF_PDO_RECEIVE+481-1].pointer = map1BE0;
	pdomap[CAN_NOF_PDO_RECEIVE+481-1].nmax = sizeof(map1BE0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+1
	pdomap[CAN_NOF_PDO_RECEIVE+481].pointer = map1BE1;
	pdomap[CAN_NOF_PDO_RECEIVE+481].nmax = sizeof(map1BE1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+2
	pdomap[CAN_NOF_PDO_RECEIVE+481+1].pointer = map1BE2;
	pdomap[CAN_NOF_PDO_RECEIVE+481+1].nmax = sizeof(map1BE2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+3
	pdomap[CAN_NOF_PDO_RECEIVE+481+2].pointer = map1BE3;
	pdomap[CAN_NOF_PDO_RECEIVE+481+2].nmax = sizeof(map1BE3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+4
	pdomap[CAN_NOF_PDO_RECEIVE+481+3].pointer = map1BE4;
	pdomap[CAN_NOF_PDO_RECEIVE+481+3].nmax = sizeof(map1BE4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+5
	pdomap[CAN_NOF_PDO_RECEIVE+481+4].pointer = map1BE5;
	pdomap[CAN_NOF_PDO_RECEIVE+481+4].nmax = sizeof(map1BE5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+6
	pdomap[CAN_NOF_PDO_RECEIVE+481+5].pointer = map1BE6;
	pdomap[CAN_NOF_PDO_RECEIVE+481+5].nmax = sizeof(map1BE6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+7
	pdomap[CAN_NOF_PDO_RECEIVE+481+6].pointer = map1BE7;
	pdomap[CAN_NOF_PDO_RECEIVE+481+6].nmax = sizeof(map1BE7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+8
	pdomap[CAN_NOF_PDO_RECEIVE+481+7].pointer = map1BE8;
	pdomap[CAN_NOF_PDO_RECEIVE+481+7].nmax = sizeof(map1BE8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+9
	pdomap[CAN_NOF_PDO_RECEIVE+481+8].pointer = map1BE9;
	pdomap[CAN_NOF_PDO_RECEIVE+481+8].nmax = sizeof(map1BE9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+10
	pdomap[CAN_NOF_PDO_RECEIVE+481+9].pointer = map1BEA;
	pdomap[CAN_NOF_PDO_RECEIVE+481+9].nmax = sizeof(map1BEA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+11
	pdomap[CAN_NOF_PDO_RECEIVE+481+10].pointer = map1BEB;
	pdomap[CAN_NOF_PDO_RECEIVE+481+10].nmax = sizeof(map1BEB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+12
	pdomap[CAN_NOF_PDO_RECEIVE+481+11].pointer = map1BEC;
	pdomap[CAN_NOF_PDO_RECEIVE+481+11].nmax = sizeof(map1BEC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+13
	pdomap[CAN_NOF_PDO_RECEIVE+481+12].pointer = map1BED;
	pdomap[CAN_NOF_PDO_RECEIVE+481+12].nmax = sizeof(map1BED) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+14
	pdomap[CAN_NOF_PDO_RECEIVE+481+13].pointer = map1BEE;
	pdomap[CAN_NOF_PDO_RECEIVE+481+13].nmax = sizeof(map1BEE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+15
	pdomap[CAN_NOF_PDO_RECEIVE+481+14].pointer = map1BEF;
	pdomap[CAN_NOF_PDO_RECEIVE+481+14].nmax = sizeof(map1BEF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+16
	pdomap[CAN_NOF_PDO_RECEIVE+481+15].pointer = map1BF0;
	pdomap[CAN_NOF_PDO_RECEIVE+481+15].nmax = sizeof(map1BF0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+17
	pdomap[CAN_NOF_PDO_RECEIVE+481+16].pointer = map1BF1;
	pdomap[CAN_NOF_PDO_RECEIVE+481+16].nmax = sizeof(map1BF1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+18
	pdomap[CAN_NOF_PDO_RECEIVE+481+17].pointer = map1BF2;
	pdomap[CAN_NOF_PDO_RECEIVE+481+17].nmax = sizeof(map1BF2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+19
	pdomap[CAN_NOF_PDO_RECEIVE+481+18].pointer = map1BF3;
	pdomap[CAN_NOF_PDO_RECEIVE+481+18].nmax = sizeof(map1BF3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+20
	pdomap[CAN_NOF_PDO_RECEIVE+481+19].pointer = map1BF4;
	pdomap[CAN_NOF_PDO_RECEIVE+481+19].nmax = sizeof(map1BF4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+21
	pdomap[CAN_NOF_PDO_RECEIVE+481+20].pointer = map1BF5;
	pdomap[CAN_NOF_PDO_RECEIVE+481+20].nmax = sizeof(map1BF5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+22
	pdomap[CAN_NOF_PDO_RECEIVE+481+21].pointer = map1BF6;
	pdomap[CAN_NOF_PDO_RECEIVE+481+21].nmax = sizeof(map1BF6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+23
	pdomap[CAN_NOF_PDO_RECEIVE+481+22].pointer = map1BF7;
	pdomap[CAN_NOF_PDO_RECEIVE+481+22].nmax = sizeof(map1BF7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+24
	pdomap[CAN_NOF_PDO_RECEIVE+481+23].pointer = map1BF8;
	pdomap[CAN_NOF_PDO_RECEIVE+481+23].nmax = sizeof(map1BF8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+25
	pdomap[CAN_NOF_PDO_RECEIVE+481+24].pointer = map1BF9;
	pdomap[CAN_NOF_PDO_RECEIVE+481+24].nmax = sizeof(map1BF9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+26
	pdomap[CAN_NOF_PDO_RECEIVE+481+25].pointer = map1BFA;
	pdomap[CAN_NOF_PDO_RECEIVE+481+25].nmax = sizeof(map1BFA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+27
	pdomap[CAN_NOF_PDO_RECEIVE+481+26].pointer = map1BFB;
	pdomap[CAN_NOF_PDO_RECEIVE+481+26].nmax = sizeof(map1BFB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+28
	pdomap[CAN_NOF_PDO_RECEIVE+481+27].pointer = map1BFC;
	pdomap[CAN_NOF_PDO_RECEIVE+481+27].nmax = sizeof(map1BFC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+29
	pdomap[CAN_NOF_PDO_RECEIVE+481+28].pointer = map1BFD;
	pdomap[CAN_NOF_PDO_RECEIVE+481+28].nmax = sizeof(map1BFD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+30
	pdomap[CAN_NOF_PDO_RECEIVE+481+29].pointer = map1BFE;
	pdomap[CAN_NOF_PDO_RECEIVE+481+29].nmax = sizeof(map1BFE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 481+31
	pdomap[CAN_NOF_PDO_RECEIVE+481+30].pointer = map1BFF;
	pdomap[CAN_NOF_PDO_RECEIVE+481+30].nmax = sizeof(map1BFF) / sizeof(unsigned32);
#endif
}
