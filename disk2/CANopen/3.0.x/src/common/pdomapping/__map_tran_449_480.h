// TPDOs from 449 to 480

#define CAN_SIZE_PDOMAP_1BC0	CAN_NOF_MAP	// 449th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1BC1	CAN_NOF_MAP	// 450th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1BC2	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BC3	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BC4	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BC5	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BC6	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BC7	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BC8	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BC9	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BCA	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BCB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BCC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BCD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BCE	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BCF	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BD9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BDA	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BDB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BDC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BDD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1BDE	CAN_NOF_MAP	// 479th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1BDF	CAN_NOF_MAP	// 480th transmit PDO mapping max. entries

#if CAN_NOF_PDO_TRANSMIT >= 449
static unsigned32 map1BC0[CAN_SIZE_PDOMAP_1BC0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+1
static unsigned32 map1BC1[CAN_SIZE_PDOMAP_1BC1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+2
static unsigned32 map1BC2[CAN_SIZE_PDOMAP_1BC2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+3
static unsigned32 map1BC3[CAN_SIZE_PDOMAP_1BC3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+4
static unsigned32 map1BC4[CAN_SIZE_PDOMAP_1BC4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+5
static unsigned32 map1BC5[CAN_SIZE_PDOMAP_1BC5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+6
static unsigned32 map1BC6[CAN_SIZE_PDOMAP_1BC6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+7
static unsigned32 map1BC7[CAN_SIZE_PDOMAP_1BC7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+8
static unsigned32 map1BC8[CAN_SIZE_PDOMAP_1BC8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+9
static unsigned32 map1BC9[CAN_SIZE_PDOMAP_1BC9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+10
static unsigned32 map1BCA[CAN_SIZE_PDOMAP_1BCA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+11
static unsigned32 map1BCB[CAN_SIZE_PDOMAP_1BCB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+12
static unsigned32 map1BCC[CAN_SIZE_PDOMAP_1BCC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+13
static unsigned32 map1BCD[CAN_SIZE_PDOMAP_1BCD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+14
static unsigned32 map1BCE[CAN_SIZE_PDOMAP_1BCE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+15
static unsigned32 map1BCF[CAN_SIZE_PDOMAP_1BCF];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+16
static unsigned32 map1BD0[CAN_SIZE_PDOMAP_1BD0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+17
static unsigned32 map1BD1[CAN_SIZE_PDOMAP_1BD1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+18
static unsigned32 map1BD2[CAN_SIZE_PDOMAP_1BD2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+19
static unsigned32 map1BD3[CAN_SIZE_PDOMAP_1BD3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+20
static unsigned32 map1BD4[CAN_SIZE_PDOMAP_1BD4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+21
static unsigned32 map1BD5[CAN_SIZE_PDOMAP_1BD5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+22
static unsigned32 map1BD6[CAN_SIZE_PDOMAP_1BD6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+23
static unsigned32 map1BD7[CAN_SIZE_PDOMAP_1BD7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+24
static unsigned32 map1BD8[CAN_SIZE_PDOMAP_1BD8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+25
static unsigned32 map1BD9[CAN_SIZE_PDOMAP_1BD9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+26
static unsigned32 map1BDA[CAN_SIZE_PDOMAP_1BDA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+27
static unsigned32 map1BDB[CAN_SIZE_PDOMAP_1BDB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+28
static unsigned32 map1BDC[CAN_SIZE_PDOMAP_1BDC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+29
static unsigned32 map1BDD[CAN_SIZE_PDOMAP_1BDD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+30
static unsigned32 map1BDE[CAN_SIZE_PDOMAP_1BDE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+31
static unsigned32 map1BDF[CAN_SIZE_PDOMAP_1BDF];
#endif


static void define_map_tran_449_480(void)
{
#if CAN_NOF_PDO_TRANSMIT >= 449
	pdomap[CAN_NOF_PDO_RECEIVE+449-1].pointer = map1BC0;
	pdomap[CAN_NOF_PDO_RECEIVE+449-1].nmax = sizeof(map1BC0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+1
	pdomap[CAN_NOF_PDO_RECEIVE+449].pointer = map1BC1;
	pdomap[CAN_NOF_PDO_RECEIVE+449].nmax = sizeof(map1BC1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+2
	pdomap[CAN_NOF_PDO_RECEIVE+449+1].pointer = map1BC2;
	pdomap[CAN_NOF_PDO_RECEIVE+449+1].nmax = sizeof(map1BC2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+3
	pdomap[CAN_NOF_PDO_RECEIVE+449+2].pointer = map1BC3;
	pdomap[CAN_NOF_PDO_RECEIVE+449+2].nmax = sizeof(map1BC3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+4
	pdomap[CAN_NOF_PDO_RECEIVE+449+3].pointer = map1BC4;
	pdomap[CAN_NOF_PDO_RECEIVE+449+3].nmax = sizeof(map1BC4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+5
	pdomap[CAN_NOF_PDO_RECEIVE+449+4].pointer = map1BC5;
	pdomap[CAN_NOF_PDO_RECEIVE+449+4].nmax = sizeof(map1BC5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+6
	pdomap[CAN_NOF_PDO_RECEIVE+449+5].pointer = map1BC6;
	pdomap[CAN_NOF_PDO_RECEIVE+449+5].nmax = sizeof(map1BC6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+7
	pdomap[CAN_NOF_PDO_RECEIVE+449+6].pointer = map1BC7;
	pdomap[CAN_NOF_PDO_RECEIVE+449+6].nmax = sizeof(map1BC7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+8
	pdomap[CAN_NOF_PDO_RECEIVE+449+7].pointer = map1BC8;
	pdomap[CAN_NOF_PDO_RECEIVE+449+7].nmax = sizeof(map1BC8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+9
	pdomap[CAN_NOF_PDO_RECEIVE+449+8].pointer = map1BC9;
	pdomap[CAN_NOF_PDO_RECEIVE+449+8].nmax = sizeof(map1BC9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+10
	pdomap[CAN_NOF_PDO_RECEIVE+449+9].pointer = map1BCA;
	pdomap[CAN_NOF_PDO_RECEIVE+449+9].nmax = sizeof(map1BCA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+11
	pdomap[CAN_NOF_PDO_RECEIVE+449+10].pointer = map1BCB;
	pdomap[CAN_NOF_PDO_RECEIVE+449+10].nmax = sizeof(map1BCB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+12
	pdomap[CAN_NOF_PDO_RECEIVE+449+11].pointer = map1BCC;
	pdomap[CAN_NOF_PDO_RECEIVE+449+11].nmax = sizeof(map1BCC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+13
	pdomap[CAN_NOF_PDO_RECEIVE+449+12].pointer = map1BCD;
	pdomap[CAN_NOF_PDO_RECEIVE+449+12].nmax = sizeof(map1BCD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+14
	pdomap[CAN_NOF_PDO_RECEIVE+449+13].pointer = map1BCE;
	pdomap[CAN_NOF_PDO_RECEIVE+449+13].nmax = sizeof(map1BCE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+15
	pdomap[CAN_NOF_PDO_RECEIVE+449+14].pointer = map1BCF;
	pdomap[CAN_NOF_PDO_RECEIVE+449+14].nmax = sizeof(map1BCF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+16
	pdomap[CAN_NOF_PDO_RECEIVE+449+15].pointer = map1BD0;
	pdomap[CAN_NOF_PDO_RECEIVE+449+15].nmax = sizeof(map1BD0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+17
	pdomap[CAN_NOF_PDO_RECEIVE+449+16].pointer = map1BD1;
	pdomap[CAN_NOF_PDO_RECEIVE+449+16].nmax = sizeof(map1BD1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+18
	pdomap[CAN_NOF_PDO_RECEIVE+449+17].pointer = map1BD2;
	pdomap[CAN_NOF_PDO_RECEIVE+449+17].nmax = sizeof(map1BD2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+19
	pdomap[CAN_NOF_PDO_RECEIVE+449+18].pointer = map1BD3;
	pdomap[CAN_NOF_PDO_RECEIVE+449+18].nmax = sizeof(map1BD3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+20
	pdomap[CAN_NOF_PDO_RECEIVE+449+19].pointer = map1BD4;
	pdomap[CAN_NOF_PDO_RECEIVE+449+19].nmax = sizeof(map1BD4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+21
	pdomap[CAN_NOF_PDO_RECEIVE+449+20].pointer = map1BD5;
	pdomap[CAN_NOF_PDO_RECEIVE+449+20].nmax = sizeof(map1BD5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+22
	pdomap[CAN_NOF_PDO_RECEIVE+449+21].pointer = map1BD6;
	pdomap[CAN_NOF_PDO_RECEIVE+449+21].nmax = sizeof(map1BD6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+23
	pdomap[CAN_NOF_PDO_RECEIVE+449+22].pointer = map1BD7;
	pdomap[CAN_NOF_PDO_RECEIVE+449+22].nmax = sizeof(map1BD7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+24
	pdomap[CAN_NOF_PDO_RECEIVE+449+23].pointer = map1BD8;
	pdomap[CAN_NOF_PDO_RECEIVE+449+23].nmax = sizeof(map1BD8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+25
	pdomap[CAN_NOF_PDO_RECEIVE+449+24].pointer = map1BD9;
	pdomap[CAN_NOF_PDO_RECEIVE+449+24].nmax = sizeof(map1BD9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+26
	pdomap[CAN_NOF_PDO_RECEIVE+449+25].pointer = map1BDA;
	pdomap[CAN_NOF_PDO_RECEIVE+449+25].nmax = sizeof(map1BDA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+27
	pdomap[CAN_NOF_PDO_RECEIVE+449+26].pointer = map1BDB;
	pdomap[CAN_NOF_PDO_RECEIVE+449+26].nmax = sizeof(map1BDB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+28
	pdomap[CAN_NOF_PDO_RECEIVE+449+27].pointer = map1BDC;
	pdomap[CAN_NOF_PDO_RECEIVE+449+27].nmax = sizeof(map1BDC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+29
	pdomap[CAN_NOF_PDO_RECEIVE+449+28].pointer = map1BDD;
	pdomap[CAN_NOF_PDO_RECEIVE+449+28].nmax = sizeof(map1BDD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+30
	pdomap[CAN_NOF_PDO_RECEIVE+449+29].pointer = map1BDE;
	pdomap[CAN_NOF_PDO_RECEIVE+449+29].nmax = sizeof(map1BDE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 449+31
	pdomap[CAN_NOF_PDO_RECEIVE+449+30].pointer = map1BDF;
	pdomap[CAN_NOF_PDO_RECEIVE+449+30].nmax = sizeof(map1BDF) / sizeof(unsigned32);
#endif
}
