// TPDOs from 417 to 448

#define CAN_SIZE_PDOMAP_1BA0		CAN_NOF_MAP	// 417th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1BA1		CAN_NOF_MAP	// 418th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1BA2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BA3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BA4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BA5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BA6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BA7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BA8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BA9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BAA	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BAB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BAC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BAD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BAE		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BAF		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BB9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BBA	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BBB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BBC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BBD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BBE	CAN_NOF_MAP	// 447th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1BBF	CAN_NOF_MAP	// 448th transmit PDO mapping max. entries

#if CAN_NOF_PDO_TRANSMIT >= 417
static unsigned32 map1BA0[CAN_SIZE_PDOMAP_1BA0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+1
static unsigned32 map1BA1[CAN_SIZE_PDOMAP_1BA1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+2
static unsigned32 map1BA2[CAN_SIZE_PDOMAP_1BA2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+3
static unsigned32 map1BA3[CAN_SIZE_PDOMAP_1BA3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+4
static unsigned32 map1BA4[CAN_SIZE_PDOMAP_1BA4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+5
static unsigned32 map1BA5[CAN_SIZE_PDOMAP_1BA5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+6
static unsigned32 map1BA6[CAN_SIZE_PDOMAP_1BA6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+7
static unsigned32 map1BA7[CAN_SIZE_PDOMAP_1BA7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+8
static unsigned32 map1BA8[CAN_SIZE_PDOMAP_1BA8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+9
static unsigned32 map1BA9[CAN_SIZE_PDOMAP_1BA9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+10
static unsigned32 map1BAA[CAN_SIZE_PDOMAP_1BAA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+11
static unsigned32 map1BAB[CAN_SIZE_PDOMAP_1BAB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+12
static unsigned32 map1BAC[CAN_SIZE_PDOMAP_1BAC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+13
static unsigned32 map1BAD[CAN_SIZE_PDOMAP_1BAD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+14
static unsigned32 map1BAE[CAN_SIZE_PDOMAP_1BAE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+15
static unsigned32 map1BAF[CAN_SIZE_PDOMAP_1BAF];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+16
static unsigned32 map1BB0[CAN_SIZE_PDOMAP_1BB0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+17
static unsigned32 map1BB1[CAN_SIZE_PDOMAP_1BB1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+18
static unsigned32 map1BB2[CAN_SIZE_PDOMAP_1BB2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+19
static unsigned32 map1BB3[CAN_SIZE_PDOMAP_1BB3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+20
static unsigned32 map1BB4[CAN_SIZE_PDOMAP_1BB4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+21
static unsigned32 map1BB5[CAN_SIZE_PDOMAP_1BB5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+22
static unsigned32 map1BB6[CAN_SIZE_PDOMAP_1BB6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+23
static unsigned32 map1BB7[CAN_SIZE_PDOMAP_1BB7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+24
static unsigned32 map1BB8[CAN_SIZE_PDOMAP_1BB8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+25
static unsigned32 map1BB9[CAN_SIZE_PDOMAP_1BB9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+26
static unsigned32 map1BBA[CAN_SIZE_PDOMAP_1BBA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+27
static unsigned32 map1BBB[CAN_SIZE_PDOMAP_1BBB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+28
static unsigned32 map1BBC[CAN_SIZE_PDOMAP_1BBC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+29
static unsigned32 map1BBD[CAN_SIZE_PDOMAP_1BBD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+30
static unsigned32 map1BBE[CAN_SIZE_PDOMAP_1BBE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+31
static unsigned32 map1BBF[CAN_SIZE_PDOMAP_1BBF];
#endif


static void define_map_tran_417_448(void)
{
#if CAN_NOF_PDO_TRANSMIT >= 417
	pdomap[CAN_NOF_PDO_RECEIVE+417-1].pointer = map1BA0;
	pdomap[CAN_NOF_PDO_RECEIVE+417-1].nmax = sizeof(map1BA0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+1
	pdomap[CAN_NOF_PDO_RECEIVE+417].pointer = map1BA1;
	pdomap[CAN_NOF_PDO_RECEIVE+417].nmax = sizeof(map1BA1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+2
	pdomap[CAN_NOF_PDO_RECEIVE+417+1].pointer = map1BA2;
	pdomap[CAN_NOF_PDO_RECEIVE+417+1].nmax = sizeof(map1BA2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+3
	pdomap[CAN_NOF_PDO_RECEIVE+417+2].pointer = map1BA3;
	pdomap[CAN_NOF_PDO_RECEIVE+417+2].nmax = sizeof(map1BA3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+4
	pdomap[CAN_NOF_PDO_RECEIVE+417+3].pointer = map1BA4;
	pdomap[CAN_NOF_PDO_RECEIVE+417+3].nmax = sizeof(map1BA4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+5
	pdomap[CAN_NOF_PDO_RECEIVE+417+4].pointer = map1BA5;
	pdomap[CAN_NOF_PDO_RECEIVE+417+4].nmax = sizeof(map1BA5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+6
	pdomap[CAN_NOF_PDO_RECEIVE+417+5].pointer = map1BA6;
	pdomap[CAN_NOF_PDO_RECEIVE+417+5].nmax = sizeof(map1BA6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+7
	pdomap[CAN_NOF_PDO_RECEIVE+417+6].pointer = map1BA7;
	pdomap[CAN_NOF_PDO_RECEIVE+417+6].nmax = sizeof(map1BA7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+8
	pdomap[CAN_NOF_PDO_RECEIVE+417+7].pointer = map1BA8;
	pdomap[CAN_NOF_PDO_RECEIVE+417+7].nmax = sizeof(map1BA8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+9
	pdomap[CAN_NOF_PDO_RECEIVE+417+8].pointer = map1BA9;
	pdomap[CAN_NOF_PDO_RECEIVE+417+8].nmax = sizeof(map1BA9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+10
	pdomap[CAN_NOF_PDO_RECEIVE+417+9].pointer = map1BAA;
	pdomap[CAN_NOF_PDO_RECEIVE+417+9].nmax = sizeof(map1BAA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+11
	pdomap[CAN_NOF_PDO_RECEIVE+417+10].pointer = map1BAB;
	pdomap[CAN_NOF_PDO_RECEIVE+417+10].nmax = sizeof(map1BAB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+12
	pdomap[CAN_NOF_PDO_RECEIVE+417+11].pointer = map1BAC;
	pdomap[CAN_NOF_PDO_RECEIVE+417+11].nmax = sizeof(map1BAC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+13
	pdomap[CAN_NOF_PDO_RECEIVE+417+12].pointer = map1BAD;
	pdomap[CAN_NOF_PDO_RECEIVE+417+12].nmax = sizeof(map1BAD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+14
	pdomap[CAN_NOF_PDO_RECEIVE+417+13].pointer = map1BAE;
	pdomap[CAN_NOF_PDO_RECEIVE+417+13].nmax = sizeof(map1BAE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+15
	pdomap[CAN_NOF_PDO_RECEIVE+417+14].pointer = map1BAF;
	pdomap[CAN_NOF_PDO_RECEIVE+417+14].nmax = sizeof(map1BAF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+16
	pdomap[CAN_NOF_PDO_RECEIVE+417+15].pointer = map1BB0;
	pdomap[CAN_NOF_PDO_RECEIVE+417+15].nmax = sizeof(map1BB0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+17
	pdomap[CAN_NOF_PDO_RECEIVE+417+16].pointer = map1BB1;
	pdomap[CAN_NOF_PDO_RECEIVE+417+16].nmax = sizeof(map1BB1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+18
	pdomap[CAN_NOF_PDO_RECEIVE+417+17].pointer = map1BB2;
	pdomap[CAN_NOF_PDO_RECEIVE+417+17].nmax = sizeof(map1BB2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+19
	pdomap[CAN_NOF_PDO_RECEIVE+417+18].pointer = map1BB3;
	pdomap[CAN_NOF_PDO_RECEIVE+417+18].nmax = sizeof(map1BB3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+20
	pdomap[CAN_NOF_PDO_RECEIVE+417+19].pointer = map1BB4;
	pdomap[CAN_NOF_PDO_RECEIVE+417+19].nmax = sizeof(map1BB4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+21
	pdomap[CAN_NOF_PDO_RECEIVE+417+20].pointer = map1BB5;
	pdomap[CAN_NOF_PDO_RECEIVE+417+20].nmax = sizeof(map1BB5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+22
	pdomap[CAN_NOF_PDO_RECEIVE+417+21].pointer = map1BB6;
	pdomap[CAN_NOF_PDO_RECEIVE+417+21].nmax = sizeof(map1BB6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+23
	pdomap[CAN_NOF_PDO_RECEIVE+417+22].pointer = map1BB7;
	pdomap[CAN_NOF_PDO_RECEIVE+417+22].nmax = sizeof(map1BB7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+24
	pdomap[CAN_NOF_PDO_RECEIVE+417+23].pointer = map1BB8;
	pdomap[CAN_NOF_PDO_RECEIVE+417+23].nmax = sizeof(map1BB8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+25
	pdomap[CAN_NOF_PDO_RECEIVE+417+24].pointer = map1BB9;
	pdomap[CAN_NOF_PDO_RECEIVE+417+24].nmax = sizeof(map1BB9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+26
	pdomap[CAN_NOF_PDO_RECEIVE+417+25].pointer = map1BBA;
	pdomap[CAN_NOF_PDO_RECEIVE+417+25].nmax = sizeof(map1BBA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+27
	pdomap[CAN_NOF_PDO_RECEIVE+417+26].pointer = map1BBB;
	pdomap[CAN_NOF_PDO_RECEIVE+417+26].nmax = sizeof(map1BBB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+28
	pdomap[CAN_NOF_PDO_RECEIVE+417+27].pointer = map1BBC;
	pdomap[CAN_NOF_PDO_RECEIVE+417+27].nmax = sizeof(map1BBC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+29
	pdomap[CAN_NOF_PDO_RECEIVE+417+28].pointer = map1BBD;
	pdomap[CAN_NOF_PDO_RECEIVE+417+28].nmax = sizeof(map1BBD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+30
	pdomap[CAN_NOF_PDO_RECEIVE+417+29].pointer = map1BBE;
	pdomap[CAN_NOF_PDO_RECEIVE+417+29].nmax = sizeof(map1BBE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 417+31
	pdomap[CAN_NOF_PDO_RECEIVE+417+30].pointer = map1BBF;
	pdomap[CAN_NOF_PDO_RECEIVE+417+30].nmax = sizeof(map1BBF) / sizeof(unsigned32);
#endif
}
