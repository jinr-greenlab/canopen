// RPDOs from 193 to 224

#define CAN_SIZE_PDOMAP_16C0		CAN_NOF_MAP	// 193rd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_16C1		CAN_NOF_MAP	// 194th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_16C2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16C3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16C4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16C5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16C6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16C7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16C8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16C9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16CA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16CB	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16CC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16CD	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16CE		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16CF		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16D9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16DA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16DB		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16DC	CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16DD		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16DE		CAN_NOF_MAP	// 223rd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_16DF		CAN_NOF_MAP	// 224th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 193
static unsigned32 map16C0[CAN_SIZE_PDOMAP_16C0];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+1
static unsigned32 map16C1[CAN_SIZE_PDOMAP_16C1];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+2
static unsigned32 map16C2[CAN_SIZE_PDOMAP_16C2];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+3
static unsigned32 map16C3[CAN_SIZE_PDOMAP_16C3];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+4
static unsigned32 map16C4[CAN_SIZE_PDOMAP_16C4];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+5
static unsigned32 map16C5[CAN_SIZE_PDOMAP_16C5];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+6
static unsigned32 map16C6[CAN_SIZE_PDOMAP_16C6];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+7
static unsigned32 map16C7[CAN_SIZE_PDOMAP_16C7];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+8
static unsigned32 map16C8[CAN_SIZE_PDOMAP_16C8];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+9
static unsigned32 map16C9[CAN_SIZE_PDOMAP_16C9];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+10
static unsigned32 map16CA[CAN_SIZE_PDOMAP_16CA];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+11
static unsigned32 map16CB[CAN_SIZE_PDOMAP_16CB];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+12
static unsigned32 map16CC[CAN_SIZE_PDOMAP_16CC];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+13
static unsigned32 map16CD[CAN_SIZE_PDOMAP_16CD];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+14
static unsigned32 map16CE[CAN_SIZE_PDOMAP_16CE];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+15
static unsigned32 map16CF[CAN_SIZE_PDOMAP_16CF];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+16
static unsigned32 map16D0[CAN_SIZE_PDOMAP_16D0];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+17
static unsigned32 map16D1[CAN_SIZE_PDOMAP_16D1];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+18
static unsigned32 map16D2[CAN_SIZE_PDOMAP_16D2];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+19
static unsigned32 map16D3[CAN_SIZE_PDOMAP_16D3];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+20
static unsigned32 map16D4[CAN_SIZE_PDOMAP_16D4];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+21
static unsigned32 map16D5[CAN_SIZE_PDOMAP_16D5];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+22
static unsigned32 map16D6[CAN_SIZE_PDOMAP_16D6];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+23
static unsigned32 map16D7[CAN_SIZE_PDOMAP_16D7];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+24
static unsigned32 map16D8[CAN_SIZE_PDOMAP_16D8];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+25
static unsigned32 map16D9[CAN_SIZE_PDOMAP_16D9];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+26
static unsigned32 map16DA[CAN_SIZE_PDOMAP_16DA];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+27
static unsigned32 map16DB[CAN_SIZE_PDOMAP_16DB];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+28
static unsigned32 map16DC[CAN_SIZE_PDOMAP_16DC];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+29
static unsigned32 map16DD[CAN_SIZE_PDOMAP_16DD];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+30
static unsigned32 map16DE[CAN_SIZE_PDOMAP_16DE];
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+31
static unsigned32 map16DF[CAN_SIZE_PDOMAP_16DF];
#endif


static void define_map_recv_193_224(void)
{
#if CAN_NOF_PDO_RECEIVE >= 193
	pdomap[193-1].pointer = map16C0;
	pdomap[193-1].nmax = sizeof(map16C0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+1
	pdomap[193].pointer = map16C1;
	pdomap[193].nmax = sizeof(map16C1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+2
	pdomap[193+1].pointer = map16C2;
	pdomap[193+1].nmax = sizeof(map16C2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+3
	pdomap[193+2].pointer = map16C3;
	pdomap[193+2].nmax = sizeof(map16C3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+4
	pdomap[193+3].pointer = map16C4;
	pdomap[193+3].nmax = sizeof(map16C4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+5
	pdomap[193+4].pointer = map16C5;
	pdomap[193+4].nmax = sizeof(map16C5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+6
	pdomap[193+5].pointer = map16C6;
	pdomap[193+5].nmax = sizeof(map16C6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+7
	pdomap[193+6].pointer = map16C7;
	pdomap[193+6].nmax = sizeof(map16C7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+8
	pdomap[193+7].pointer = map16C8;
	pdomap[193+7].nmax = sizeof(map16C8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+9
	pdomap[193+8].pointer = map16C9;
	pdomap[193+8].nmax = sizeof(map16C9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+10
	pdomap[193+9].pointer = map16CA;
	pdomap[193+9].nmax = sizeof(map16CA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+11
	pdomap[193+10].pointer = map16CB;
	pdomap[193+10].nmax = sizeof(map16CB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+12
	pdomap[193+11].pointer = map16CC;
	pdomap[193+11].nmax = sizeof(map16CC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+13
	pdomap[193+12].pointer = map16CD;
	pdomap[193+12].nmax = sizeof(map16CD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+14
	pdomap[193+13].pointer = map16CE;
	pdomap[193+13].nmax = sizeof(map16CE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+15
	pdomap[193+14].pointer = map16CF;
	pdomap[193+14].nmax = sizeof(map16CF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+16
	pdomap[193+15].pointer = map16D0;
	pdomap[193+15].nmax = sizeof(map16D0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+17
	pdomap[193+16].pointer = map16D1;
	pdomap[193+16].nmax = sizeof(map16D1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+18
	pdomap[193+17].pointer = map16D2;
	pdomap[193+17].nmax = sizeof(map16D2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+19
	pdomap[193+18].pointer = map16D3;
	pdomap[193+18].nmax = sizeof(map16D3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+20
	pdomap[193+19].pointer = map16D4;
	pdomap[193+19].nmax = sizeof(map16D4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+21
	pdomap[193+20].pointer = map16D5;
	pdomap[193+20].nmax = sizeof(map16D5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+22
	pdomap[193+21].pointer = map16D6;
	pdomap[193+21].nmax = sizeof(map16D6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+23
	pdomap[193+22].pointer = map16D7;
	pdomap[193+22].nmax = sizeof(map16D7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+24
	pdomap[193+23].pointer = map16D8;
	pdomap[193+23].nmax = sizeof(map16D8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+25
	pdomap[193+24].pointer = map16D9;
	pdomap[193+24].nmax = sizeof(map16D9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+26
	pdomap[193+25].pointer = map16DA;
	pdomap[193+25].nmax = sizeof(map16DA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+27
	pdomap[193+26].pointer = map16DB;
	pdomap[193+26].nmax = sizeof(map16DB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+28
	pdomap[193+27].pointer = map16DC;
	pdomap[193+27].nmax = sizeof(map16DC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+29
	pdomap[193+28].pointer = map16DD;
	pdomap[193+28].nmax = sizeof(map16DD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+30
	pdomap[193+29].pointer = map16DE;
	pdomap[193+29].nmax = sizeof(map16DE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 193+31
	pdomap[193+30].pointer = map16DF;
	pdomap[193+30].nmax = sizeof(map16DF) / sizeof(unsigned32);
#endif
}
