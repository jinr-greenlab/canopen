// TPDOs from 33 to 64

#define CAN_SIZE_PDOMAP_1A20		CAN_NOF_MAP	// 33rd transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1A21		CAN_NOF_MAP	// 34th transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1A22		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A23		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A24		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A25		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A26		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A27		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A28		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A29		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A2A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A2B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A2C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A2D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A2E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A2F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A30		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A31		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A32		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A33		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A34		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A35		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A36		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A37		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A38		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A39		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A3A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A3B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A3C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A3D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A3E		CAN_NOF_MAP	// 63rd transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1A3F		CAN_NOF_MAP	// 64th transmit PDO mapping max. entries

#if CAN_NOF_PDO_TRANSMIT >= 33
static unsigned32 map1A20[CAN_SIZE_PDOMAP_1A20];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+1
static unsigned32 map1A21[CAN_SIZE_PDOMAP_1A21];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+2
static unsigned32 map1A22[CAN_SIZE_PDOMAP_1A22];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+3
static unsigned32 map1A23[CAN_SIZE_PDOMAP_1A23];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+4
static unsigned32 map1A24[CAN_SIZE_PDOMAP_1A24];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+5
static unsigned32 map1A25[CAN_SIZE_PDOMAP_1A25];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+6
static unsigned32 map1A26[CAN_SIZE_PDOMAP_1A26];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+7
static unsigned32 map1A27[CAN_SIZE_PDOMAP_1A27];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+8
static unsigned32 map1A28[CAN_SIZE_PDOMAP_1A28];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+9
static unsigned32 map1A29[CAN_SIZE_PDOMAP_1A29];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+10
static unsigned32 map1A2A[CAN_SIZE_PDOMAP_1A2A];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+11
static unsigned32 map1A2B[CAN_SIZE_PDOMAP_1A2B];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+12
static unsigned32 map1A2C[CAN_SIZE_PDOMAP_1A2C];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+13
static unsigned32 map1A2D[CAN_SIZE_PDOMAP_1A2D];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+14
static unsigned32 map1A2E[CAN_SIZE_PDOMAP_1A2E];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+15
static unsigned32 map1A2F[CAN_SIZE_PDOMAP_1A2F];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+16
static unsigned32 map1A30[CAN_SIZE_PDOMAP_1A30];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+17
static unsigned32 map1A31[CAN_SIZE_PDOMAP_1A31];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+18
static unsigned32 map1A32[CAN_SIZE_PDOMAP_1A32];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+19
static unsigned32 map1A33[CAN_SIZE_PDOMAP_1A33];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+20
static unsigned32 map1A34[CAN_SIZE_PDOMAP_1A34];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+21
static unsigned32 map1A35[CAN_SIZE_PDOMAP_1A35];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+22
static unsigned32 map1A36[CAN_SIZE_PDOMAP_1A36];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+23
static unsigned32 map1A37[CAN_SIZE_PDOMAP_1A37];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+24
static unsigned32 map1A38[CAN_SIZE_PDOMAP_1A38];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+25
static unsigned32 map1A39[CAN_SIZE_PDOMAP_1A39];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+26
static unsigned32 map1A3A[CAN_SIZE_PDOMAP_1A3A];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+27
static unsigned32 map1A3B[CAN_SIZE_PDOMAP_1A3B];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+28
static unsigned32 map1A3C[CAN_SIZE_PDOMAP_1A3C];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+29
static unsigned32 map1A3D[CAN_SIZE_PDOMAP_1A3D];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+30
static unsigned32 map1A3E[CAN_SIZE_PDOMAP_1A3E];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+31
static unsigned32 map1A3F[CAN_SIZE_PDOMAP_1A3F];
#endif


static void define_map_tran_033_064(void)
{
#if CAN_NOF_PDO_TRANSMIT >= 33
	pdomap[CAN_NOF_PDO_RECEIVE+33-1].pointer = map1A20;
	pdomap[CAN_NOF_PDO_RECEIVE+33-1].nmax = sizeof(map1A20) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+1
	pdomap[CAN_NOF_PDO_RECEIVE+33].pointer = map1A21;
	pdomap[CAN_NOF_PDO_RECEIVE+33].nmax = sizeof(map1A21) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+2
	pdomap[CAN_NOF_PDO_RECEIVE+33+1].pointer = map1A22;
	pdomap[CAN_NOF_PDO_RECEIVE+33+1].nmax = sizeof(map1A22) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+3
	pdomap[CAN_NOF_PDO_RECEIVE+33+2].pointer = map1A23;
	pdomap[CAN_NOF_PDO_RECEIVE+33+2].nmax = sizeof(map1A23) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+4
	pdomap[CAN_NOF_PDO_RECEIVE+33+3].pointer = map1A24;
	pdomap[CAN_NOF_PDO_RECEIVE+33+3].nmax = sizeof(map1A24) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+5
	pdomap[CAN_NOF_PDO_RECEIVE+33+4].pointer = map1A25;
	pdomap[CAN_NOF_PDO_RECEIVE+33+4].nmax = sizeof(map1A25) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+6
	pdomap[CAN_NOF_PDO_RECEIVE+33+5].pointer = map1A26;
	pdomap[CAN_NOF_PDO_RECEIVE+33+5].nmax = sizeof(map1A26) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+7
	pdomap[CAN_NOF_PDO_RECEIVE+33+6].pointer = map1A27;
	pdomap[CAN_NOF_PDO_RECEIVE+33+6].nmax = sizeof(map1A27) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+8
	pdomap[CAN_NOF_PDO_RECEIVE+33+7].pointer = map1A28;
	pdomap[CAN_NOF_PDO_RECEIVE+33+7].nmax = sizeof(map1A28) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+9
	pdomap[CAN_NOF_PDO_RECEIVE+33+8].pointer = map1A29;
	pdomap[CAN_NOF_PDO_RECEIVE+33+8].nmax = sizeof(map1A29) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+10
	pdomap[CAN_NOF_PDO_RECEIVE+33+9].pointer = map1A2A;
	pdomap[CAN_NOF_PDO_RECEIVE+33+9].nmax = sizeof(map1A2A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+11
	pdomap[CAN_NOF_PDO_RECEIVE+33+10].pointer = map1A2B;
	pdomap[CAN_NOF_PDO_RECEIVE+33+10].nmax = sizeof(map1A2B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+12
	pdomap[CAN_NOF_PDO_RECEIVE+33+11].pointer = map1A2C;
	pdomap[CAN_NOF_PDO_RECEIVE+33+11].nmax = sizeof(map1A2C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+13
	pdomap[CAN_NOF_PDO_RECEIVE+33+12].pointer = map1A2D;
	pdomap[CAN_NOF_PDO_RECEIVE+33+12].nmax = sizeof(map1A2D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+14
	pdomap[CAN_NOF_PDO_RECEIVE+33+13].pointer = map1A2E;
	pdomap[CAN_NOF_PDO_RECEIVE+33+13].nmax = sizeof(map1A2E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+15
	pdomap[CAN_NOF_PDO_RECEIVE+33+14].pointer = map1A2F;
	pdomap[CAN_NOF_PDO_RECEIVE+33+14].nmax = sizeof(map1A2F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+16
	pdomap[CAN_NOF_PDO_RECEIVE+33+15].pointer = map1A30;
	pdomap[CAN_NOF_PDO_RECEIVE+33+15].nmax = sizeof(map1A30) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+17
	pdomap[CAN_NOF_PDO_RECEIVE+33+16].pointer = map1A31;
	pdomap[CAN_NOF_PDO_RECEIVE+33+16].nmax = sizeof(map1A31) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+18
	pdomap[CAN_NOF_PDO_RECEIVE+33+17].pointer = map1A32;
	pdomap[CAN_NOF_PDO_RECEIVE+33+17].nmax = sizeof(map1A32) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+19
	pdomap[CAN_NOF_PDO_RECEIVE+33+18].pointer = map1A33;
	pdomap[CAN_NOF_PDO_RECEIVE+33+18].nmax = sizeof(map1A33) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+20
	pdomap[CAN_NOF_PDO_RECEIVE+33+19].pointer = map1A34;
	pdomap[CAN_NOF_PDO_RECEIVE+33+19].nmax = sizeof(map1A34) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+21
	pdomap[CAN_NOF_PDO_RECEIVE+33+20].pointer = map1A35;
	pdomap[CAN_NOF_PDO_RECEIVE+33+20].nmax = sizeof(map1A35) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+22
	pdomap[CAN_NOF_PDO_RECEIVE+33+21].pointer = map1A36;
	pdomap[CAN_NOF_PDO_RECEIVE+33+21].nmax = sizeof(map1A36) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+23
	pdomap[CAN_NOF_PDO_RECEIVE+33+22].pointer = map1A37;
	pdomap[CAN_NOF_PDO_RECEIVE+33+22].nmax = sizeof(map1A37) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+24
	pdomap[CAN_NOF_PDO_RECEIVE+33+23].pointer = map1A38;
	pdomap[CAN_NOF_PDO_RECEIVE+33+23].nmax = sizeof(map1A38) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+25
	pdomap[CAN_NOF_PDO_RECEIVE+33+24].pointer = map1A39;
	pdomap[CAN_NOF_PDO_RECEIVE+33+24].nmax = sizeof(map1A39) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+26
	pdomap[CAN_NOF_PDO_RECEIVE+33+25].pointer = map1A3A;
	pdomap[CAN_NOF_PDO_RECEIVE+33+25].nmax = sizeof(map1A3A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+27
	pdomap[CAN_NOF_PDO_RECEIVE+33+26].pointer = map1A3B;
	pdomap[CAN_NOF_PDO_RECEIVE+33+26].nmax = sizeof(map1A3B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+28
	pdomap[CAN_NOF_PDO_RECEIVE+33+27].pointer = map1A3C;
	pdomap[CAN_NOF_PDO_RECEIVE+33+27].nmax = sizeof(map1A3C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+29
	pdomap[CAN_NOF_PDO_RECEIVE+33+28].pointer = map1A3D;
	pdomap[CAN_NOF_PDO_RECEIVE+33+28].nmax = sizeof(map1A3D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+30
	pdomap[CAN_NOF_PDO_RECEIVE+33+29].pointer = map1A3E;
	pdomap[CAN_NOF_PDO_RECEIVE+33+29].nmax = sizeof(map1A3E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 33+31
	pdomap[CAN_NOF_PDO_RECEIVE+33+30].pointer = map1A3F;
	pdomap[CAN_NOF_PDO_RECEIVE+33+30].nmax = sizeof(map1A3F) / sizeof(unsigned32);
#endif
}
