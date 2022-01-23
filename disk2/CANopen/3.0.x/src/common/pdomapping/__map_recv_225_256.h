// RPDOs from 225 to 256

#define CAN_SIZE_PDOMAP_16E0		CAN_NOF_MAP	// 225th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_16E1		CAN_NOF_MAP	// 226th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_16E2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16E3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16E4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16E5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16E6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16E7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16E8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16E9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16EA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16EB		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16EC		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16ED		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16EE		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16EF		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F0		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F1		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F2		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F3		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F4		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F5		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F6		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F7		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F8		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16F9		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16FA		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16FB		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16FC		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16FD		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_16FE		CAN_NOF_MAP	// 255th receive PDO mapping max. entries
#define CAN_SIZE_PDOMAP_16FF		CAN_NOF_MAP	// 256th receive PDO mapping max. entries

#if CAN_NOF_PDO_RECEIVE >= 225
static unsigned32 map16E0[CAN_SIZE_PDOMAP_16E0];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+1
static unsigned32 map16E1[CAN_SIZE_PDOMAP_16E1];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+2
static unsigned32 map16E2[CAN_SIZE_PDOMAP_16E2];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+3
static unsigned32 map16E3[CAN_SIZE_PDOMAP_16E3];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+4
static unsigned32 map16E4[CAN_SIZE_PDOMAP_16E4];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+5
static unsigned32 map16E5[CAN_SIZE_PDOMAP_16E5];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+6
static unsigned32 map16E6[CAN_SIZE_PDOMAP_16E6];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+7
static unsigned32 map16E7[CAN_SIZE_PDOMAP_16E7];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+8
static unsigned32 map16E8[CAN_SIZE_PDOMAP_16E8];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+9
static unsigned32 map16E9[CAN_SIZE_PDOMAP_16E9];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+10
static unsigned32 map16EA[CAN_SIZE_PDOMAP_16EA];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+11
static unsigned32 map16EB[CAN_SIZE_PDOMAP_16EB];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+12
static unsigned32 map16EC[CAN_SIZE_PDOMAP_16EC];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+13
static unsigned32 map16ED[CAN_SIZE_PDOMAP_16ED];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+14
static unsigned32 map16EE[CAN_SIZE_PDOMAP_16EE];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+15
static unsigned32 map16EF[CAN_SIZE_PDOMAP_16EF];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+16
static unsigned32 map16F0[CAN_SIZE_PDOMAP_16F0];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+17
static unsigned32 map16F1[CAN_SIZE_PDOMAP_16F1];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+18
static unsigned32 map16F2[CAN_SIZE_PDOMAP_16F2];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+19
static unsigned32 map16F3[CAN_SIZE_PDOMAP_16F3];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+20
static unsigned32 map16F4[CAN_SIZE_PDOMAP_16F4];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+21
static unsigned32 map16F5[CAN_SIZE_PDOMAP_16F5];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+22
static unsigned32 map16F6[CAN_SIZE_PDOMAP_16F6];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+23
static unsigned32 map16F7[CAN_SIZE_PDOMAP_16F7];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+24
static unsigned32 map16F8[CAN_SIZE_PDOMAP_16F8];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+25
static unsigned32 map16F9[CAN_SIZE_PDOMAP_16F9];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+26
static unsigned32 map16FA[CAN_SIZE_PDOMAP_16FA];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+27
static unsigned32 map16FB[CAN_SIZE_PDOMAP_16FB];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+28
static unsigned32 map16FC[CAN_SIZE_PDOMAP_16FC];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+29
static unsigned32 map16FD[CAN_SIZE_PDOMAP_16FD];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+30
static unsigned32 map16FE[CAN_SIZE_PDOMAP_16FE];
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+31
static unsigned32 map16FF[CAN_SIZE_PDOMAP_16FF];
#endif


static void define_map_recv_225_256(void)
{
#if CAN_NOF_PDO_RECEIVE >= 225
	pdomap[225-1].pointer = map16E0;
	pdomap[225-1].nmax = sizeof(map16E0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+1
	pdomap[225].pointer = map16E1;
	pdomap[225].nmax = sizeof(map16E1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+2
	pdomap[225+1].pointer = map16E2;
	pdomap[225+1].nmax = sizeof(map16E2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+3
	pdomap[225+2].pointer = map16E3;
	pdomap[225+2].nmax = sizeof(map16E3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+4
	pdomap[225+3].pointer = map16E4;
	pdomap[225+3].nmax = sizeof(map16E4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+5
	pdomap[225+4].pointer = map16E5;
	pdomap[225+4].nmax = sizeof(map16E5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+6
	pdomap[225+5].pointer = map16E6;
	pdomap[225+5].nmax = sizeof(map16E6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+7
	pdomap[225+6].pointer = map16E7;
	pdomap[225+6].nmax = sizeof(map16E7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+8
	pdomap[225+7].pointer = map16E8;
	pdomap[225+7].nmax = sizeof(map16E8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+9
	pdomap[225+8].pointer = map16E9;
	pdomap[225+8].nmax = sizeof(map16E9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+10
	pdomap[225+9].pointer = map16EA;
	pdomap[225+9].nmax = sizeof(map16EA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+11
	pdomap[225+10].pointer = map16EB;
	pdomap[225+10].nmax = sizeof(map16EB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+12
	pdomap[225+11].pointer = map16EC;
	pdomap[225+11].nmax = sizeof(map16EC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+13
	pdomap[225+12].pointer = map16ED;
	pdomap[225+12].nmax = sizeof(map16ED) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+14
	pdomap[225+13].pointer = map16EE;
	pdomap[225+13].nmax = sizeof(map16EE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+15
	pdomap[225+14].pointer = map16EF;
	pdomap[225+14].nmax = sizeof(map16EF) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+16
	pdomap[225+15].pointer = map16F0;
	pdomap[225+15].nmax = sizeof(map16F0) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+17
	pdomap[225+16].pointer = map16F1;
	pdomap[225+16].nmax = sizeof(map16F1) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+18
	pdomap[225+17].pointer = map16F2;
	pdomap[225+17].nmax = sizeof(map16F2) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+19
	pdomap[225+18].pointer = map16F3;
	pdomap[225+18].nmax = sizeof(map16F3) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+20
	pdomap[225+19].pointer = map16F4;
	pdomap[225+19].nmax = sizeof(map16F4) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+21
	pdomap[225+20].pointer = map16F5;
	pdomap[225+20].nmax = sizeof(map16F5) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+22
	pdomap[225+21].pointer = map16F6;
	pdomap[225+21].nmax = sizeof(map16F6) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+23
	pdomap[225+22].pointer = map16F7;
	pdomap[225+22].nmax = sizeof(map16F7) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+24
	pdomap[225+23].pointer = map16F8;
	pdomap[225+23].nmax = sizeof(map16F8) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+25
	pdomap[225+24].pointer = map16F9;
	pdomap[225+24].nmax = sizeof(map16F9) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+26
	pdomap[225+25].pointer = map16FA;
	pdomap[225+25].nmax = sizeof(map16FA) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+27
	pdomap[225+26].pointer = map16FB;
	pdomap[225+26].nmax = sizeof(map16FB) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+28
	pdomap[225+27].pointer = map16FC;
	pdomap[225+27].nmax = sizeof(map16FC) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+29
	pdomap[225+28].pointer = map16FD;
	pdomap[225+28].nmax = sizeof(map16FD) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+30
	pdomap[225+29].pointer = map16FE;
	pdomap[225+29].nmax = sizeof(map16FE) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_RECEIVE >= 225+31
	pdomap[225+30].pointer = map16FF;
	pdomap[225+30].nmax = sizeof(map16FF) / sizeof(unsigned32);
#endif
}
