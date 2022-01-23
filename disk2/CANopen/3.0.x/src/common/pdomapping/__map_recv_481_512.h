// RPDOs from 481 to 512

#define CAN_SIZE_PDOMAP_17E0		CAN_NOF_MAP	// 481st receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_17E1		CAN_NOF_MAP	// 482nd receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_17E2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17E3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17E4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17E5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17E6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17E7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17E8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17E9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17EA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17EB		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17EC		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17ED		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17EE		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17EF		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17F9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17FA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17FB		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17FC		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17FD		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_17FE		CAN_NOF_MAP	// 511th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_17FF		CAN_NOF_MAP	// 512th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 481
static unsigned32 map17E0[CAN_SIZE_PDOMAP_17E0];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+1
static unsigned32 map17E1[CAN_SIZE_PDOMAP_17E1];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+2
static unsigned32 map17E2[CAN_SIZE_PDOMAP_17E2];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+3
static unsigned32 map17E3[CAN_SIZE_PDOMAP_17E3];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+4
static unsigned32 map17E4[CAN_SIZE_PDOMAP_17E4];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+5
static unsigned32 map17E5[CAN_SIZE_PDOMAP_17E5];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+6
static unsigned32 map17E6[CAN_SIZE_PDOMAP_17E6];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+7
static unsigned32 map17E7[CAN_SIZE_PDOMAP_17E7];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+8
static unsigned32 map17E8[CAN_SIZE_PDOMAP_17E8];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+9
static unsigned32 map17E9[CAN_SIZE_PDOMAP_17E9];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+10
static unsigned32 map17EA[CAN_SIZE_PDOMAP_17EA];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+11
static unsigned32 map17EB[CAN_SIZE_PDOMAP_17EB];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+12
static unsigned32 map17EC[CAN_SIZE_PDOMAP_17EC];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+13
static unsigned32 map17ED[CAN_SIZE_PDOMAP_17ED];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+14
static unsigned32 map17EE[CAN_SIZE_PDOMAP_17EE];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+15
static unsigned32 map17EF[CAN_SIZE_PDOMAP_17EF];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+16
static unsigned32 map17F0[CAN_SIZE_PDOMAP_17F0];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+17
static unsigned32 map17F1[CAN_SIZE_PDOMAP_17F1];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+18
static unsigned32 map17F2[CAN_SIZE_PDOMAP_17F2];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+19
static unsigned32 map17F3[CAN_SIZE_PDOMAP_17F3];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+20
static unsigned32 map17F4[CAN_SIZE_PDOMAP_17F4];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+21
static unsigned32 map17F5[CAN_SIZE_PDOMAP_17F5];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+22
static unsigned32 map17F6[CAN_SIZE_PDOMAP_17F6];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+23
static unsigned32 map17F7[CAN_SIZE_PDOMAP_17F7];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+24
static unsigned32 map17F8[CAN_SIZE_PDOMAP_17F8];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+25
static unsigned32 map17F9[CAN_SIZE_PDOMAP_17F9];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+26
static unsigned32 map17FA[CAN_SIZE_PDOMAP_17FA];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+27
static unsigned32 map17FB[CAN_SIZE_PDOMAP_17FB];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+28
static unsigned32 map17FC[CAN_SIZE_PDOMAP_17FC];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+29
static unsigned32 map17FD[CAN_SIZE_PDOMAP_17FD];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+30
static unsigned32 map17FE[CAN_SIZE_PDOMAP_17FE];
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+31
static unsigned32 map17FF[CAN_SIZE_PDOMAP_17FF];
#endif


static void define_map_recv_481_512(void)
{
#if CAN_NOF_PDO_RECEIVE >= 481
	pdomap[481-1].pointer = map17E0;
	pdomap[481-1].nmax = sizeof(map17E0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+1
	pdomap[481].pointer = map17E1;
	pdomap[481].nmax = sizeof(map17E1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+2
	pdomap[481+1].pointer = map17E2;
	pdomap[481+1].nmax = sizeof(map17E2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+3
	pdomap[481+2].pointer = map17E3;
	pdomap[481+2].nmax = sizeof(map17E3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+4
	pdomap[481+3].pointer = map17E4;
	pdomap[481+3].nmax = sizeof(map17E4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+5
	pdomap[481+4].pointer = map17E5;
	pdomap[481+4].nmax = sizeof(map17E5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+6
	pdomap[481+5].pointer = map17E6;
	pdomap[481+5].nmax = sizeof(map17E6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+7
	pdomap[481+6].pointer = map17E7;
	pdomap[481+6].nmax = sizeof(map17E7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+8
	pdomap[481+7].pointer = map17E8;
	pdomap[481+7].nmax = sizeof(map17E8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+9
	pdomap[481+8].pointer = map17E9;
	pdomap[481+8].nmax = sizeof(map17E9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+10
	pdomap[481+9].pointer = map17EA;
	pdomap[481+9].nmax = sizeof(map17EA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+11
	pdomap[481+10].pointer = map17EB;
	pdomap[481+10].nmax = sizeof(map17EB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+12
	pdomap[481+11].pointer = map17EC;
	pdomap[481+11].nmax = sizeof(map17EC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+13
	pdomap[481+12].pointer = map17ED;
	pdomap[481+12].nmax = sizeof(map17ED) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+14
	pdomap[481+13].pointer = map17EE;
	pdomap[481+13].nmax = sizeof(map17EE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+15
	pdomap[481+14].pointer = map17EF;
	pdomap[481+14].nmax = sizeof(map17EF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+16
	pdomap[481+15].pointer = map17F0;
	pdomap[481+15].nmax = sizeof(map17F0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+17
	pdomap[481+16].pointer = map17F1;
	pdomap[481+16].nmax = sizeof(map17F1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+18
	pdomap[481+17].pointer = map17F2;
	pdomap[481+17].nmax = sizeof(map17F2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+19
	pdomap[481+18].pointer = map17F3;
	pdomap[481+18].nmax = sizeof(map17F3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+20
	pdomap[481+19].pointer = map17F4;
	pdomap[481+19].nmax = sizeof(map17F4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+21
	pdomap[481+20].pointer = map17F5;
	pdomap[481+20].nmax = sizeof(map17F5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+22
	pdomap[481+21].pointer = map17F6;
	pdomap[481+21].nmax = sizeof(map17F6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+23
	pdomap[481+22].pointer = map17F7;
	pdomap[481+22].nmax = sizeof(map17F7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+24
	pdomap[481+23].pointer = map17F8;
	pdomap[481+23].nmax = sizeof(map17F8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+25
	pdomap[481+24].pointer = map17F9;
	pdomap[481+24].nmax = sizeof(map17F9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+26
	pdomap[481+25].pointer = map17FA;
	pdomap[481+25].nmax = sizeof(map17FA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+27
	pdomap[481+26].pointer = map17FB;
	pdomap[481+26].nmax = sizeof(map17FB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+28
	pdomap[481+27].pointer = map17FC;
	pdomap[481+27].nmax = sizeof(map17FC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+29
	pdomap[481+28].pointer = map17FD;
	pdomap[481+28].nmax = sizeof(map17FD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+30
	pdomap[481+29].pointer = map17FE;
	pdomap[481+29].nmax = sizeof(map17FE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 481+31
	pdomap[481+30].pointer = map17FF;
	pdomap[481+30].nmax = sizeof(map17FF) / sizeof(unsigned32);
#endif
}
