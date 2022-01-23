// TPDOs from 65 to 96

#define CAN_SIZE_PDOMAP_1A40		CAN_NOF_MAP	// 65th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1A41		CAN_NOF_MAP	// 66th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1A42		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A43		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A44		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A45		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A46		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A47		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A48		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A49		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A4A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A4B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A4C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A4D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A4E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A4F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A50		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A51		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A52		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A53		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A54		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A55		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A56		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A57		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A58		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A59		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A5A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A5B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A5C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A5D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A5E		CAN_NOF_MAP	// 95th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1A5F		CAN_NOF_MAP	// 96th transmit PDO mapping max. entries

#if CAN_NOF_PDO_TRANSMIT >= 65
static unsigned32 map1A40[CAN_SIZE_PDOMAP_1A40];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+1
static unsigned32 map1A41[CAN_SIZE_PDOMAP_1A41];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+2
static unsigned32 map1A42[CAN_SIZE_PDOMAP_1A42];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+3
static unsigned32 map1A43[CAN_SIZE_PDOMAP_1A43];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+4
static unsigned32 map1A44[CAN_SIZE_PDOMAP_1A44];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+5
static unsigned32 map1A45[CAN_SIZE_PDOMAP_1A45];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+6
static unsigned32 map1A46[CAN_SIZE_PDOMAP_1A46];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+7
static unsigned32 map1A47[CAN_SIZE_PDOMAP_1A47];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+8
static unsigned32 map1A48[CAN_SIZE_PDOMAP_1A48];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+9
static unsigned32 map1A49[CAN_SIZE_PDOMAP_1A49];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+10
static unsigned32 map1A4A[CAN_SIZE_PDOMAP_1A4A];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+11
static unsigned32 map1A4B[CAN_SIZE_PDOMAP_1A4B];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+12
static unsigned32 map1A4C[CAN_SIZE_PDOMAP_1A4C];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+13
static unsigned32 map1A4D[CAN_SIZE_PDOMAP_1A4D];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+14
static unsigned32 map1A4E[CAN_SIZE_PDOMAP_1A4E];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+15
static unsigned32 map1A4F[CAN_SIZE_PDOMAP_1A4F];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+16
static unsigned32 map1A50[CAN_SIZE_PDOMAP_1A50];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+17
static unsigned32 map1A51[CAN_SIZE_PDOMAP_1A51];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+18
static unsigned32 map1A52[CAN_SIZE_PDOMAP_1A52];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+19
static unsigned32 map1A53[CAN_SIZE_PDOMAP_1A53];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+20
static unsigned32 map1A54[CAN_SIZE_PDOMAP_1A54];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+21
static unsigned32 map1A55[CAN_SIZE_PDOMAP_1A55];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+22
static unsigned32 map1A56[CAN_SIZE_PDOMAP_1A56];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+23
static unsigned32 map1A57[CAN_SIZE_PDOMAP_1A57];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+24
static unsigned32 map1A58[CAN_SIZE_PDOMAP_1A58];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+25
static unsigned32 map1A59[CAN_SIZE_PDOMAP_1A59];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+26
static unsigned32 map1A5A[CAN_SIZE_PDOMAP_1A5A];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+27
static unsigned32 map1A5B[CAN_SIZE_PDOMAP_1A5B];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+28
static unsigned32 map1A5C[CAN_SIZE_PDOMAP_1A5C];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+29
static unsigned32 map1A5D[CAN_SIZE_PDOMAP_1A5D];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+30
static unsigned32 map1A5E[CAN_SIZE_PDOMAP_1A5E];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+31
static unsigned32 map1A5F[CAN_SIZE_PDOMAP_1A5F];
#endif


static void define_map_tran_065_096(void)
{
#if CAN_NOF_PDO_TRANSMIT >= 65
	pdomap[CAN_NOF_PDO_RECEIVE+65-1].pointer = map1A40;
	pdomap[CAN_NOF_PDO_RECEIVE+65-1].nmax = sizeof(map1A40) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+1
	pdomap[CAN_NOF_PDO_RECEIVE+65].pointer = map1A41;
	pdomap[CAN_NOF_PDO_RECEIVE+65].nmax = sizeof(map1A41) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+2
	pdomap[CAN_NOF_PDO_RECEIVE+65+1].pointer = map1A42;
	pdomap[CAN_NOF_PDO_RECEIVE+65+1].nmax = sizeof(map1A42) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+3
	pdomap[CAN_NOF_PDO_RECEIVE+65+2].pointer = map1A43;
	pdomap[CAN_NOF_PDO_RECEIVE+65+2].nmax = sizeof(map1A43) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+4
	pdomap[CAN_NOF_PDO_RECEIVE+65+3].pointer = map1A44;
	pdomap[CAN_NOF_PDO_RECEIVE+65+3].nmax = sizeof(map1A44) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+5
	pdomap[CAN_NOF_PDO_RECEIVE+65+4].pointer = map1A45;
	pdomap[CAN_NOF_PDO_RECEIVE+65+4].nmax = sizeof(map1A45) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+6
	pdomap[CAN_NOF_PDO_RECEIVE+65+5].pointer = map1A46;
	pdomap[CAN_NOF_PDO_RECEIVE+65+5].nmax = sizeof(map1A46) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+7
	pdomap[CAN_NOF_PDO_RECEIVE+65+6].pointer = map1A47;
	pdomap[CAN_NOF_PDO_RECEIVE+65+6].nmax = sizeof(map1A47) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+8
	pdomap[CAN_NOF_PDO_RECEIVE+65+7].pointer = map1A48;
	pdomap[CAN_NOF_PDO_RECEIVE+65+7].nmax = sizeof(map1A48) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+9
	pdomap[CAN_NOF_PDO_RECEIVE+65+8].pointer = map1A49;
	pdomap[CAN_NOF_PDO_RECEIVE+65+8].nmax = sizeof(map1A49) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+10
	pdomap[CAN_NOF_PDO_RECEIVE+65+9].pointer = map1A4A;
	pdomap[CAN_NOF_PDO_RECEIVE+65+9].nmax = sizeof(map1A4A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+11
	pdomap[CAN_NOF_PDO_RECEIVE+65+10].pointer = map1A4B;
	pdomap[CAN_NOF_PDO_RECEIVE+65+10].nmax = sizeof(map1A4B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+12
	pdomap[CAN_NOF_PDO_RECEIVE+65+11].pointer = map1A4C;
	pdomap[CAN_NOF_PDO_RECEIVE+65+11].nmax = sizeof(map1A4C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+13
	pdomap[CAN_NOF_PDO_RECEIVE+65+12].pointer = map1A4D;
	pdomap[CAN_NOF_PDO_RECEIVE+65+12].nmax = sizeof(map1A4D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+14
	pdomap[CAN_NOF_PDO_RECEIVE+65+13].pointer = map1A4E;
	pdomap[CAN_NOF_PDO_RECEIVE+65+13].nmax = sizeof(map1A4E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+15
	pdomap[CAN_NOF_PDO_RECEIVE+65+14].pointer = map1A4F;
	pdomap[CAN_NOF_PDO_RECEIVE+65+14].nmax = sizeof(map1A4F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+16
	pdomap[CAN_NOF_PDO_RECEIVE+65+15].pointer = map1A50;
	pdomap[CAN_NOF_PDO_RECEIVE+65+15].nmax = sizeof(map1A50) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+17
	pdomap[CAN_NOF_PDO_RECEIVE+65+16].pointer = map1A51;
	pdomap[CAN_NOF_PDO_RECEIVE+65+16].nmax = sizeof(map1A51) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+18
	pdomap[CAN_NOF_PDO_RECEIVE+65+17].pointer = map1A52;
	pdomap[CAN_NOF_PDO_RECEIVE+65+17].nmax = sizeof(map1A52) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+19
	pdomap[CAN_NOF_PDO_RECEIVE+65+18].pointer = map1A53;
	pdomap[CAN_NOF_PDO_RECEIVE+65+18].nmax = sizeof(map1A53) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+20
	pdomap[CAN_NOF_PDO_RECEIVE+65+19].pointer = map1A54;
	pdomap[CAN_NOF_PDO_RECEIVE+65+19].nmax = sizeof(map1A54) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+21
	pdomap[CAN_NOF_PDO_RECEIVE+65+20].pointer = map1A55;
	pdomap[CAN_NOF_PDO_RECEIVE+65+20].nmax = sizeof(map1A55) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+22
	pdomap[CAN_NOF_PDO_RECEIVE+65+21].pointer = map1A56;
	pdomap[CAN_NOF_PDO_RECEIVE+65+21].nmax = sizeof(map1A56) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+23
	pdomap[CAN_NOF_PDO_RECEIVE+65+22].pointer = map1A57;
	pdomap[CAN_NOF_PDO_RECEIVE+65+22].nmax = sizeof(map1A57) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+24
	pdomap[CAN_NOF_PDO_RECEIVE+65+23].pointer = map1A58;
	pdomap[CAN_NOF_PDO_RECEIVE+65+23].nmax = sizeof(map1A58) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+25
	pdomap[CAN_NOF_PDO_RECEIVE+65+24].pointer = map1A59;
	pdomap[CAN_NOF_PDO_RECEIVE+65+24].nmax = sizeof(map1A59) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+26
	pdomap[CAN_NOF_PDO_RECEIVE+65+25].pointer = map1A5A;
	pdomap[CAN_NOF_PDO_RECEIVE+65+25].nmax = sizeof(map1A5A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+27
	pdomap[CAN_NOF_PDO_RECEIVE+65+26].pointer = map1A5B;
	pdomap[CAN_NOF_PDO_RECEIVE+65+26].nmax = sizeof(map1A5B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+28
	pdomap[CAN_NOF_PDO_RECEIVE+65+27].pointer = map1A5C;
	pdomap[CAN_NOF_PDO_RECEIVE+65+27].nmax = sizeof(map1A5C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+29
	pdomap[CAN_NOF_PDO_RECEIVE+65+28].pointer = map1A5D;
	pdomap[CAN_NOF_PDO_RECEIVE+65+28].nmax = sizeof(map1A5D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+30
	pdomap[CAN_NOF_PDO_RECEIVE+65+29].pointer = map1A5E;
	pdomap[CAN_NOF_PDO_RECEIVE+65+29].nmax = sizeof(map1A5E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 65+31
	pdomap[CAN_NOF_PDO_RECEIVE+65+30].pointer = map1A5F;
	pdomap[CAN_NOF_PDO_RECEIVE+65+30].nmax = sizeof(map1A5F) / sizeof(unsigned32);
#endif
}
