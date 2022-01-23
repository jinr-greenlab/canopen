// TPDOs from 161 to 192

#define CAN_SIZE_PDOMAP_1AA0		CAN_NOF_MAP	// 161st transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1AA1		CAN_NOF_MAP	// 162nd transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1AA2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AA3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AA4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AA5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AA6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AA7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AA8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AA9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AAA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AAB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AAC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AAD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AAE		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AAF		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1AB9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ABA	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ABB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ABC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ABD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1ABE		CAN_NOF_MAP	// 191st transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1ABF		CAN_NOF_MAP	// 192nd transmit PDO mapping max. entries

#if CAN_NOF_PDO_TRANSMIT >= 161
static unsigned32 map1AA0[CAN_SIZE_PDOMAP_1AA0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+1
static unsigned32 map1AA1[CAN_SIZE_PDOMAP_1AA1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+2
static unsigned32 map1AA2[CAN_SIZE_PDOMAP_1AA2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+3
static unsigned32 map1AA3[CAN_SIZE_PDOMAP_1AA3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+4
static unsigned32 map1AA4[CAN_SIZE_PDOMAP_1AA4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+5
static unsigned32 map1AA5[CAN_SIZE_PDOMAP_1AA5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+6
static unsigned32 map1AA6[CAN_SIZE_PDOMAP_1AA6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+7
static unsigned32 map1AA7[CAN_SIZE_PDOMAP_1AA7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+8
static unsigned32 map1AA8[CAN_SIZE_PDOMAP_1AA8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+9
static unsigned32 map1AA9[CAN_SIZE_PDOMAP_1AA9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+10
static unsigned32 map1AAA[CAN_SIZE_PDOMAP_1AAA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+11
static unsigned32 map1AAB[CAN_SIZE_PDOMAP_1AAB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+12
static unsigned32 map1AAC[CAN_SIZE_PDOMAP_1AAC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+13
static unsigned32 map1AAD[CAN_SIZE_PDOMAP_1AAD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+14
static unsigned32 map1AAE[CAN_SIZE_PDOMAP_1AAE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+15
static unsigned32 map1AAF[CAN_SIZE_PDOMAP_1AAF];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+16
static unsigned32 map1AB0[CAN_SIZE_PDOMAP_1AB0];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+17
static unsigned32 map1AB1[CAN_SIZE_PDOMAP_1AB1];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+18
static unsigned32 map1AB2[CAN_SIZE_PDOMAP_1AB2];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+19
static unsigned32 map1AB3[CAN_SIZE_PDOMAP_1AB3];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+20
static unsigned32 map1AB4[CAN_SIZE_PDOMAP_1AB4];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+21
static unsigned32 map1AB5[CAN_SIZE_PDOMAP_1AB5];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+22
static unsigned32 map1AB6[CAN_SIZE_PDOMAP_1AB6];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+23
static unsigned32 map1AB7[CAN_SIZE_PDOMAP_1AB7];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+24
static unsigned32 map1AB8[CAN_SIZE_PDOMAP_1AB8];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+25
static unsigned32 map1AB9[CAN_SIZE_PDOMAP_1AB9];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+26
static unsigned32 map1ABA[CAN_SIZE_PDOMAP_1ABA];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+27
static unsigned32 map1ABB[CAN_SIZE_PDOMAP_1ABB];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+28
static unsigned32 map1ABC[CAN_SIZE_PDOMAP_1ABC];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+29
static unsigned32 map1ABD[CAN_SIZE_PDOMAP_1ABD];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+30
static unsigned32 map1ABE[CAN_SIZE_PDOMAP_1ABE];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+31
static unsigned32 map1ABF[CAN_SIZE_PDOMAP_1ABF];
#endif


static void define_map_tran_161_192(void)
{
#if CAN_NOF_PDO_TRANSMIT >= 161
	pdomap[CAN_NOF_PDO_RECEIVE+161-1].pointer = map1AA0;
	pdomap[CAN_NOF_PDO_RECEIVE+161-1].nmax = sizeof(map1AA0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+1
	pdomap[CAN_NOF_PDO_RECEIVE+161].pointer = map1AA1;
	pdomap[CAN_NOF_PDO_RECEIVE+161].nmax = sizeof(map1AA1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+2
	pdomap[CAN_NOF_PDO_RECEIVE+161+1].pointer = map1AA2;
	pdomap[CAN_NOF_PDO_RECEIVE+161+1].nmax = sizeof(map1AA2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+3
	pdomap[CAN_NOF_PDO_RECEIVE+161+2].pointer = map1AA3;
	pdomap[CAN_NOF_PDO_RECEIVE+161+2].nmax = sizeof(map1AA3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+4
	pdomap[CAN_NOF_PDO_RECEIVE+161+3].pointer = map1AA4;
	pdomap[CAN_NOF_PDO_RECEIVE+161+3].nmax = sizeof(map1AA4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+5
	pdomap[CAN_NOF_PDO_RECEIVE+161+4].pointer = map1AA5;
	pdomap[CAN_NOF_PDO_RECEIVE+161+4].nmax = sizeof(map1AA5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+6
	pdomap[CAN_NOF_PDO_RECEIVE+161+5].pointer = map1AA6;
	pdomap[CAN_NOF_PDO_RECEIVE+161+5].nmax = sizeof(map1AA6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+7
	pdomap[CAN_NOF_PDO_RECEIVE+161+6].pointer = map1AA7;
	pdomap[CAN_NOF_PDO_RECEIVE+161+6].nmax = sizeof(map1AA7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+8
	pdomap[CAN_NOF_PDO_RECEIVE+161+7].pointer = map1AA8;
	pdomap[CAN_NOF_PDO_RECEIVE+161+7].nmax = sizeof(map1AA8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+9
	pdomap[CAN_NOF_PDO_RECEIVE+161+8].pointer = map1AA9;
	pdomap[CAN_NOF_PDO_RECEIVE+161+8].nmax = sizeof(map1AA9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+10
	pdomap[CAN_NOF_PDO_RECEIVE+161+9].pointer = map1AAA;
	pdomap[CAN_NOF_PDO_RECEIVE+161+9].nmax = sizeof(map1AAA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+11
	pdomap[CAN_NOF_PDO_RECEIVE+161+10].pointer = map1AAB;
	pdomap[CAN_NOF_PDO_RECEIVE+161+10].nmax = sizeof(map1AAB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+12
	pdomap[CAN_NOF_PDO_RECEIVE+161+11].pointer = map1AAC;
	pdomap[CAN_NOF_PDO_RECEIVE+161+11].nmax = sizeof(map1AAC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+13
	pdomap[CAN_NOF_PDO_RECEIVE+161+12].pointer = map1AAD;
	pdomap[CAN_NOF_PDO_RECEIVE+161+12].nmax = sizeof(map1AAD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+14
	pdomap[CAN_NOF_PDO_RECEIVE+161+13].pointer = map1AAE;
	pdomap[CAN_NOF_PDO_RECEIVE+161+13].nmax = sizeof(map1AAE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+15
	pdomap[CAN_NOF_PDO_RECEIVE+161+14].pointer = map1AAF;
	pdomap[CAN_NOF_PDO_RECEIVE+161+14].nmax = sizeof(map1AAF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+16
	pdomap[CAN_NOF_PDO_RECEIVE+161+15].pointer = map1AB0;
	pdomap[CAN_NOF_PDO_RECEIVE+161+15].nmax = sizeof(map1AB0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+17
	pdomap[CAN_NOF_PDO_RECEIVE+161+16].pointer = map1AB1;
	pdomap[CAN_NOF_PDO_RECEIVE+161+16].nmax = sizeof(map1AB1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+18
	pdomap[CAN_NOF_PDO_RECEIVE+161+17].pointer = map1AB2;
	pdomap[CAN_NOF_PDO_RECEIVE+161+17].nmax = sizeof(map1AB2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+19
	pdomap[CAN_NOF_PDO_RECEIVE+161+18].pointer = map1AB3;
	pdomap[CAN_NOF_PDO_RECEIVE+161+18].nmax = sizeof(map1AB3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+20
	pdomap[CAN_NOF_PDO_RECEIVE+161+19].pointer = map1AB4;
	pdomap[CAN_NOF_PDO_RECEIVE+161+19].nmax = sizeof(map1AB4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+21
	pdomap[CAN_NOF_PDO_RECEIVE+161+20].pointer = map1AB5;
	pdomap[CAN_NOF_PDO_RECEIVE+161+20].nmax = sizeof(map1AB5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+22
	pdomap[CAN_NOF_PDO_RECEIVE+161+21].pointer = map1AB6;
	pdomap[CAN_NOF_PDO_RECEIVE+161+21].nmax = sizeof(map1AB6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+23
	pdomap[CAN_NOF_PDO_RECEIVE+161+22].pointer = map1AB7;
	pdomap[CAN_NOF_PDO_RECEIVE+161+22].nmax = sizeof(map1AB7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+24
	pdomap[CAN_NOF_PDO_RECEIVE+161+23].pointer = map1AB8;
	pdomap[CAN_NOF_PDO_RECEIVE+161+23].nmax = sizeof(map1AB8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+25
	pdomap[CAN_NOF_PDO_RECEIVE+161+24].pointer = map1AB9;
	pdomap[CAN_NOF_PDO_RECEIVE+161+24].nmax = sizeof(map1AB9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+26
	pdomap[CAN_NOF_PDO_RECEIVE+161+25].pointer = map1ABA;
	pdomap[CAN_NOF_PDO_RECEIVE+161+25].nmax = sizeof(map1ABA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+27
	pdomap[CAN_NOF_PDO_RECEIVE+161+26].pointer = map1ABB;
	pdomap[CAN_NOF_PDO_RECEIVE+161+26].nmax = sizeof(map1ABB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+28
	pdomap[CAN_NOF_PDO_RECEIVE+161+27].pointer = map1ABC;
	pdomap[CAN_NOF_PDO_RECEIVE+161+27].nmax = sizeof(map1ABC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+29
	pdomap[CAN_NOF_PDO_RECEIVE+161+28].pointer = map1ABD;
	pdomap[CAN_NOF_PDO_RECEIVE+161+28].nmax = sizeof(map1ABD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+30
	pdomap[CAN_NOF_PDO_RECEIVE+161+29].pointer = map1ABE;
	pdomap[CAN_NOF_PDO_RECEIVE+161+29].nmax = sizeof(map1ABE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 161+31
	pdomap[CAN_NOF_PDO_RECEIVE+161+30].pointer = map1ABF;
	pdomap[CAN_NOF_PDO_RECEIVE+161+30].nmax = sizeof(map1ABF) / sizeof(unsigned32);
#endif
}
