// TPDOs from 193 to 224

#define CAN_SIZE_PDOMAP_1AC0		CAN_NOF_MAP	// 193rd transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1AC1		CAN_NOF_MAP	// 194th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1AC2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AC3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AC4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AC5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AC6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AC7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AC8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AC9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ACA	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ACB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ACC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ACD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ACE	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ACF	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AD9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ADA	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ADB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ADC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ADD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ADE		CAN_NOF_MAP	// 223rd transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1ADF		CAN_NOF_MAP	// 224th transmit PDO mapping max. entries

#if CAN_NOF_PDO_TRANSMIT >= 193
static unsigned32 map1AC0[CAN_SIZE_PDOMAP_1AC0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+1
static unsigned32 map1AC1[CAN_SIZE_PDOMAP_1AC1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+2
static unsigned32 map1AC2[CAN_SIZE_PDOMAP_1AC2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+3
static unsigned32 map1AC3[CAN_SIZE_PDOMAP_1AC3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+4
static unsigned32 map1AC4[CAN_SIZE_PDOMAP_1AC4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+5
static unsigned32 map1AC5[CAN_SIZE_PDOMAP_1AC5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+6
static unsigned32 map1AC6[CAN_SIZE_PDOMAP_1AC6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+7
static unsigned32 map1AC7[CAN_SIZE_PDOMAP_1AC7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+8
static unsigned32 map1AC8[CAN_SIZE_PDOMAP_1AC8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+9
static unsigned32 map1AC9[CAN_SIZE_PDOMAP_1AC9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+10
static unsigned32 map1ACA[CAN_SIZE_PDOMAP_1ACA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+11
static unsigned32 map1ACB[CAN_SIZE_PDOMAP_1ACB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+12
static unsigned32 map1ACC[CAN_SIZE_PDOMAP_1ACC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+13
static unsigned32 map1ACD[CAN_SIZE_PDOMAP_1ACD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+14
static unsigned32 map1ACE[CAN_SIZE_PDOMAP_1ACE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+15
static unsigned32 map1ACF[CAN_SIZE_PDOMAP_1ACF];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+16
static unsigned32 map1AD0[CAN_SIZE_PDOMAP_1AD0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+17
static unsigned32 map1AD1[CAN_SIZE_PDOMAP_1AD1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+18
static unsigned32 map1AD2[CAN_SIZE_PDOMAP_1AD2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+19
static unsigned32 map1AD3[CAN_SIZE_PDOMAP_1AD3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+20
static unsigned32 map1AD4[CAN_SIZE_PDOMAP_1AD4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+21
static unsigned32 map1AD5[CAN_SIZE_PDOMAP_1AD5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+22
static unsigned32 map1AD6[CAN_SIZE_PDOMAP_1AD6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+23
static unsigned32 map1AD7[CAN_SIZE_PDOMAP_1AD7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+24
static unsigned32 map1AD8[CAN_SIZE_PDOMAP_1AD8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+25
static unsigned32 map1AD9[CAN_SIZE_PDOMAP_1AD9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+26
static unsigned32 map1ADA[CAN_SIZE_PDOMAP_1ADA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+27
static unsigned32 map1ADB[CAN_SIZE_PDOMAP_1ADB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+28
static unsigned32 map1ADC[CAN_SIZE_PDOMAP_1ADC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+29
static unsigned32 map1ADD[CAN_SIZE_PDOMAP_1ADD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+30
static unsigned32 map1ADE[CAN_SIZE_PDOMAP_1ADE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+31
static unsigned32 map1ADF[CAN_SIZE_PDOMAP_1ADF];
#endif


static void define_map_tran_193_224(void)
{
#if CAN_NOF_PDO_TRANSMIT >= 193
	pdomap[CAN_NOF_PDO_RECEIVE+193-1].pointer = map1AC0;
	pdomap[CAN_NOF_PDO_RECEIVE+193-1].nmax = sizeof(map1AC0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+1
	pdomap[CAN_NOF_PDO_RECEIVE+193].pointer = map1AC1;
	pdomap[CAN_NOF_PDO_RECEIVE+193].nmax = sizeof(map1AC1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+2
	pdomap[CAN_NOF_PDO_RECEIVE+193+1].pointer = map1AC2;
	pdomap[CAN_NOF_PDO_RECEIVE+193+1].nmax = sizeof(map1AC2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+3
	pdomap[CAN_NOF_PDO_RECEIVE+193+2].pointer = map1AC3;
	pdomap[CAN_NOF_PDO_RECEIVE+193+2].nmax = sizeof(map1AC3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+4
	pdomap[CAN_NOF_PDO_RECEIVE+193+3].pointer = map1AC4;
	pdomap[CAN_NOF_PDO_RECEIVE+193+3].nmax = sizeof(map1AC4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+5
	pdomap[CAN_NOF_PDO_RECEIVE+193+4].pointer = map1AC5;
	pdomap[CAN_NOF_PDO_RECEIVE+193+4].nmax = sizeof(map1AC5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+6
	pdomap[CAN_NOF_PDO_RECEIVE+193+5].pointer = map1AC6;
	pdomap[CAN_NOF_PDO_RECEIVE+193+5].nmax = sizeof(map1AC6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+7
	pdomap[CAN_NOF_PDO_RECEIVE+193+6].pointer = map1AC7;
	pdomap[CAN_NOF_PDO_RECEIVE+193+6].nmax = sizeof(map1AC7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+8
	pdomap[CAN_NOF_PDO_RECEIVE+193+7].pointer = map1AC8;
	pdomap[CAN_NOF_PDO_RECEIVE+193+7].nmax = sizeof(map1AC8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+9
	pdomap[CAN_NOF_PDO_RECEIVE+193+8].pointer = map1AC9;
	pdomap[CAN_NOF_PDO_RECEIVE+193+8].nmax = sizeof(map1AC9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+10
	pdomap[CAN_NOF_PDO_RECEIVE+193+9].pointer = map1ACA;
	pdomap[CAN_NOF_PDO_RECEIVE+193+9].nmax = sizeof(map1ACA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+11
	pdomap[CAN_NOF_PDO_RECEIVE+193+10].pointer = map1ACB;
	pdomap[CAN_NOF_PDO_RECEIVE+193+10].nmax = sizeof(map1ACB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+12
	pdomap[CAN_NOF_PDO_RECEIVE+193+11].pointer = map1ACC;
	pdomap[CAN_NOF_PDO_RECEIVE+193+11].nmax = sizeof(map1ACC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+13
	pdomap[CAN_NOF_PDO_RECEIVE+193+12].pointer = map1ACD;
	pdomap[CAN_NOF_PDO_RECEIVE+193+12].nmax = sizeof(map1ACD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+14
	pdomap[CAN_NOF_PDO_RECEIVE+193+13].pointer = map1ACE;
	pdomap[CAN_NOF_PDO_RECEIVE+193+13].nmax = sizeof(map1ACE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+15
	pdomap[CAN_NOF_PDO_RECEIVE+193+14].pointer = map1ACF;
	pdomap[CAN_NOF_PDO_RECEIVE+193+14].nmax = sizeof(map1ACF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+16
	pdomap[CAN_NOF_PDO_RECEIVE+193+15].pointer = map1AD0;
	pdomap[CAN_NOF_PDO_RECEIVE+193+15].nmax = sizeof(map1AD0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+17
	pdomap[CAN_NOF_PDO_RECEIVE+193+16].pointer = map1AD1;
	pdomap[CAN_NOF_PDO_RECEIVE+193+16].nmax = sizeof(map1AD1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+18
	pdomap[CAN_NOF_PDO_RECEIVE+193+17].pointer = map1AD2;
	pdomap[CAN_NOF_PDO_RECEIVE+193+17].nmax = sizeof(map1AD2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+19
	pdomap[CAN_NOF_PDO_RECEIVE+193+18].pointer = map1AD3;
	pdomap[CAN_NOF_PDO_RECEIVE+193+18].nmax = sizeof(map1AD3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+20
	pdomap[CAN_NOF_PDO_RECEIVE+193+19].pointer = map1AD4;
	pdomap[CAN_NOF_PDO_RECEIVE+193+19].nmax = sizeof(map1AD4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+21
	pdomap[CAN_NOF_PDO_RECEIVE+193+20].pointer = map1AD5;
	pdomap[CAN_NOF_PDO_RECEIVE+193+20].nmax = sizeof(map1AD5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+22
	pdomap[CAN_NOF_PDO_RECEIVE+193+21].pointer = map1AD6;
	pdomap[CAN_NOF_PDO_RECEIVE+193+21].nmax = sizeof(map1AD6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+23
	pdomap[CAN_NOF_PDO_RECEIVE+193+22].pointer = map1AD7;
	pdomap[CAN_NOF_PDO_RECEIVE+193+22].nmax = sizeof(map1AD7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+24
	pdomap[CAN_NOF_PDO_RECEIVE+193+23].pointer = map1AD8;
	pdomap[CAN_NOF_PDO_RECEIVE+193+23].nmax = sizeof(map1AD8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+25
	pdomap[CAN_NOF_PDO_RECEIVE+193+24].pointer = map1AD9;
	pdomap[CAN_NOF_PDO_RECEIVE+193+24].nmax = sizeof(map1AD9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+26
	pdomap[CAN_NOF_PDO_RECEIVE+193+25].pointer = map1ADA;
	pdomap[CAN_NOF_PDO_RECEIVE+193+25].nmax = sizeof(map1ADA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+27
	pdomap[CAN_NOF_PDO_RECEIVE+193+26].pointer = map1ADB;
	pdomap[CAN_NOF_PDO_RECEIVE+193+26].nmax = sizeof(map1ADB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+28
	pdomap[CAN_NOF_PDO_RECEIVE+193+27].pointer = map1ADC;
	pdomap[CAN_NOF_PDO_RECEIVE+193+27].nmax = sizeof(map1ADC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+29
	pdomap[CAN_NOF_PDO_RECEIVE+193+28].pointer = map1ADD;
	pdomap[CAN_NOF_PDO_RECEIVE+193+28].nmax = sizeof(map1ADD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+30
	pdomap[CAN_NOF_PDO_RECEIVE+193+29].pointer = map1ADE;
	pdomap[CAN_NOF_PDO_RECEIVE+193+29].nmax = sizeof(map1ADE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 193+31
	pdomap[CAN_NOF_PDO_RECEIVE+193+30].pointer = map1ADF;
	pdomap[CAN_NOF_PDO_RECEIVE+193+30].nmax = sizeof(map1ADF) / sizeof(unsigned32);
#endif
}
