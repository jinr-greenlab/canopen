// TPDOs from 225 to 256

#define CAN_SIZE_PDOMAP_1AE0		CAN_NOF_MAP	// 225th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1AE1		CAN_NOF_MAP	// 226th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1AE2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AE3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AE4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AE5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AE6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AE7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AE8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AE9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AEA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AEB		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AEC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AED		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AEE		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AEF		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AF9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AFA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AFB		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AFC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AFD		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AFE		CAN_NOF_MAP	// 255th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1AFF		CAN_NOF_MAP	// 256th transmit PDO mapping max. entries

#if CAN_NOF_PDO_TRANSMIT >= 225
static unsigned32 map1AE0[CAN_SIZE_PDOMAP_1AE0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+1
static unsigned32 map1AE1[CAN_SIZE_PDOMAP_1AE1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+2
static unsigned32 map1AE2[CAN_SIZE_PDOMAP_1AE2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+3
static unsigned32 map1AE3[CAN_SIZE_PDOMAP_1AE3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+4
static unsigned32 map1AE4[CAN_SIZE_PDOMAP_1AE4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+5
static unsigned32 map1AE5[CAN_SIZE_PDOMAP_1AE5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+6
static unsigned32 map1AE6[CAN_SIZE_PDOMAP_1AE6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+7
static unsigned32 map1AE7[CAN_SIZE_PDOMAP_1AE7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+8
static unsigned32 map1AE8[CAN_SIZE_PDOMAP_1AE8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+9
static unsigned32 map1AE9[CAN_SIZE_PDOMAP_1AE9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+10
static unsigned32 map1AEA[CAN_SIZE_PDOMAP_1AEA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+11
static unsigned32 map1AEB[CAN_SIZE_PDOMAP_1AEB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+12
static unsigned32 map1AEC[CAN_SIZE_PDOMAP_1AEC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+13
static unsigned32 map1AED[CAN_SIZE_PDOMAP_1AED];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+14
static unsigned32 map1AEE[CAN_SIZE_PDOMAP_1AEE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+15
static unsigned32 map1AEF[CAN_SIZE_PDOMAP_1AEF];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+16
static unsigned32 map1AF0[CAN_SIZE_PDOMAP_1AF0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+17
static unsigned32 map1AF1[CAN_SIZE_PDOMAP_1AF1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+18
static unsigned32 map1AF2[CAN_SIZE_PDOMAP_1AF2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+19
static unsigned32 map1AF3[CAN_SIZE_PDOMAP_1AF3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+20
static unsigned32 map1AF4[CAN_SIZE_PDOMAP_1AF4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+21
static unsigned32 map1AF5[CAN_SIZE_PDOMAP_1AF5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+22
static unsigned32 map1AF6[CAN_SIZE_PDOMAP_1AF6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+23
static unsigned32 map1AF7[CAN_SIZE_PDOMAP_1AF7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+24
static unsigned32 map1AF8[CAN_SIZE_PDOMAP_1AF8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+25
static unsigned32 map1AF9[CAN_SIZE_PDOMAP_1AF9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+26
static unsigned32 map1AFA[CAN_SIZE_PDOMAP_1AFA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+27
static unsigned32 map1AFB[CAN_SIZE_PDOMAP_1AFB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+28
static unsigned32 map1AFC[CAN_SIZE_PDOMAP_1AFC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+29
static unsigned32 map1AFD[CAN_SIZE_PDOMAP_1AFD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+30
static unsigned32 map1AFE[CAN_SIZE_PDOMAP_1AFE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+31
static unsigned32 map1AFF[CAN_SIZE_PDOMAP_1AFF];
#endif


static void define_map_tran_225_256(void)
{
#if CAN_NOF_PDO_TRANSMIT >= 225
	pdomap[CAN_NOF_PDO_RECEIVE+225-1].pointer = map1AE0;
	pdomap[CAN_NOF_PDO_RECEIVE+225-1].nmax = sizeof(map1AE0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+1
	pdomap[CAN_NOF_PDO_RECEIVE+225].pointer = map1AE1;
	pdomap[CAN_NOF_PDO_RECEIVE+225].nmax = sizeof(map1AE1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+2
	pdomap[CAN_NOF_PDO_RECEIVE+225+1].pointer = map1AE2;
	pdomap[CAN_NOF_PDO_RECEIVE+225+1].nmax = sizeof(map1AE2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+3
	pdomap[CAN_NOF_PDO_RECEIVE+225+2].pointer = map1AE3;
	pdomap[CAN_NOF_PDO_RECEIVE+225+2].nmax = sizeof(map1AE3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+4
	pdomap[CAN_NOF_PDO_RECEIVE+225+3].pointer = map1AE4;
	pdomap[CAN_NOF_PDO_RECEIVE+225+3].nmax = sizeof(map1AE4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+5
	pdomap[CAN_NOF_PDO_RECEIVE+225+4].pointer = map1AE5;
	pdomap[CAN_NOF_PDO_RECEIVE+225+4].nmax = sizeof(map1AE5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+6
	pdomap[CAN_NOF_PDO_RECEIVE+225+5].pointer = map1AE6;
	pdomap[CAN_NOF_PDO_RECEIVE+225+5].nmax = sizeof(map1AE6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+7
	pdomap[CAN_NOF_PDO_RECEIVE+225+6].pointer = map1AE7;
	pdomap[CAN_NOF_PDO_RECEIVE+225+6].nmax = sizeof(map1AE7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+8
	pdomap[CAN_NOF_PDO_RECEIVE+225+7].pointer = map1AE8;
	pdomap[CAN_NOF_PDO_RECEIVE+225+7].nmax = sizeof(map1AE8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+9
	pdomap[CAN_NOF_PDO_RECEIVE+225+8].pointer = map1AE9;
	pdomap[CAN_NOF_PDO_RECEIVE+225+8].nmax = sizeof(map1AE9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+10
	pdomap[CAN_NOF_PDO_RECEIVE+225+9].pointer = map1AEA;
	pdomap[CAN_NOF_PDO_RECEIVE+225+9].nmax = sizeof(map1AEA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+11
	pdomap[CAN_NOF_PDO_RECEIVE+225+10].pointer = map1AEB;
	pdomap[CAN_NOF_PDO_RECEIVE+225+10].nmax = sizeof(map1AEB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+12
	pdomap[CAN_NOF_PDO_RECEIVE+225+11].pointer = map1AEC;
	pdomap[CAN_NOF_PDO_RECEIVE+225+11].nmax = sizeof(map1AEC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+13
	pdomap[CAN_NOF_PDO_RECEIVE+225+12].pointer = map1AED;
	pdomap[CAN_NOF_PDO_RECEIVE+225+12].nmax = sizeof(map1AED) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+14
	pdomap[CAN_NOF_PDO_RECEIVE+225+13].pointer = map1AEE;
	pdomap[CAN_NOF_PDO_RECEIVE+225+13].nmax = sizeof(map1AEE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+15
	pdomap[CAN_NOF_PDO_RECEIVE+225+14].pointer = map1AEF;
	pdomap[CAN_NOF_PDO_RECEIVE+225+14].nmax = sizeof(map1AEF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+16
	pdomap[CAN_NOF_PDO_RECEIVE+225+15].pointer = map1AF0;
	pdomap[CAN_NOF_PDO_RECEIVE+225+15].nmax = sizeof(map1AF0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+17
	pdomap[CAN_NOF_PDO_RECEIVE+225+16].pointer = map1AF1;
	pdomap[CAN_NOF_PDO_RECEIVE+225+16].nmax = sizeof(map1AF1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+18
	pdomap[CAN_NOF_PDO_RECEIVE+225+17].pointer = map1AF2;
	pdomap[CAN_NOF_PDO_RECEIVE+225+17].nmax = sizeof(map1AF2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+19
	pdomap[CAN_NOF_PDO_RECEIVE+225+18].pointer = map1AF3;
	pdomap[CAN_NOF_PDO_RECEIVE+225+18].nmax = sizeof(map1AF3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+20
	pdomap[CAN_NOF_PDO_RECEIVE+225+19].pointer = map1AF4;
	pdomap[CAN_NOF_PDO_RECEIVE+225+19].nmax = sizeof(map1AF4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+21
	pdomap[CAN_NOF_PDO_RECEIVE+225+20].pointer = map1AF5;
	pdomap[CAN_NOF_PDO_RECEIVE+225+20].nmax = sizeof(map1AF5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+22
	pdomap[CAN_NOF_PDO_RECEIVE+225+21].pointer = map1AF6;
	pdomap[CAN_NOF_PDO_RECEIVE+225+21].nmax = sizeof(map1AF6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+23
	pdomap[CAN_NOF_PDO_RECEIVE+225+22].pointer = map1AF7;
	pdomap[CAN_NOF_PDO_RECEIVE+225+22].nmax = sizeof(map1AF7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+24
	pdomap[CAN_NOF_PDO_RECEIVE+225+23].pointer = map1AF8;
	pdomap[CAN_NOF_PDO_RECEIVE+225+23].nmax = sizeof(map1AF8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+25
	pdomap[CAN_NOF_PDO_RECEIVE+225+24].pointer = map1AF9;
	pdomap[CAN_NOF_PDO_RECEIVE+225+24].nmax = sizeof(map1AF9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+26
	pdomap[CAN_NOF_PDO_RECEIVE+225+25].pointer = map1AFA;
	pdomap[CAN_NOF_PDO_RECEIVE+225+25].nmax = sizeof(map1AFA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+27
	pdomap[CAN_NOF_PDO_RECEIVE+225+26].pointer = map1AFB;
	pdomap[CAN_NOF_PDO_RECEIVE+225+26].nmax = sizeof(map1AFB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+28
	pdomap[CAN_NOF_PDO_RECEIVE+225+27].pointer = map1AFC;
	pdomap[CAN_NOF_PDO_RECEIVE+225+27].nmax = sizeof(map1AFC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+29
	pdomap[CAN_NOF_PDO_RECEIVE+225+28].pointer = map1AFD;
	pdomap[CAN_NOF_PDO_RECEIVE+225+28].nmax = sizeof(map1AFD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+30
	pdomap[CAN_NOF_PDO_RECEIVE+225+29].pointer = map1AFE;
	pdomap[CAN_NOF_PDO_RECEIVE+225+29].nmax = sizeof(map1AFE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 225+31
	pdomap[CAN_NOF_PDO_RECEIVE+225+30].pointer = map1AFF;
	pdomap[CAN_NOF_PDO_RECEIVE+225+30].nmax = sizeof(map1AFF) / sizeof(unsigned32);
#endif
}
