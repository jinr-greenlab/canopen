// TPDOs from 1 to 32

#define CAN_SIZE_PDOMAP_1A00		CAN_NOF_MAP	// 1st transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1A01		CAN_NOF_MAP	// 2nd transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1A02		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A03		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A04		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A05		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A06		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A07		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A08		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A09		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A0A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A0B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A0C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A0D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A0E		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A0F		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A10		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A11		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A12		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A13		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A14		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A15		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A16		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A17		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A18		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A19		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A1A		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A1B		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A1C		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A1D		CAN_NOF_MAP	// ...
#define CAN_SIZE_PDOMAP_1A1E		CAN_NOF_MAP	// 31st transmit PDO mapping max. entries
#define CAN_SIZE_PDOMAP_1A1F		CAN_NOF_MAP	// 32nd transmit PDO mapping max. entries

#if CAN_NOF_PDO_TRANSMIT >= 1
static unsigned32 map1A00[CAN_SIZE_PDOMAP_1A00];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+1
static unsigned32 map1A01[CAN_SIZE_PDOMAP_1A01];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+2
static unsigned32 map1A02[CAN_SIZE_PDOMAP_1A02];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+3
static unsigned32 map1A03[CAN_SIZE_PDOMAP_1A03];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+4
static unsigned32 map1A04[CAN_SIZE_PDOMAP_1A04];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+5
static unsigned32 map1A05[CAN_SIZE_PDOMAP_1A05];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+6
static unsigned32 map1A06[CAN_SIZE_PDOMAP_1A06];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+7
static unsigned32 map1A07[CAN_SIZE_PDOMAP_1A07];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+8
static unsigned32 map1A08[CAN_SIZE_PDOMAP_1A08];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+9
static unsigned32 map1A09[CAN_SIZE_PDOMAP_1A09];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+10
static unsigned32 map1A0A[CAN_SIZE_PDOMAP_1A0A];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+11
static unsigned32 map1A0B[CAN_SIZE_PDOMAP_1A0B];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+12
static unsigned32 map1A0C[CAN_SIZE_PDOMAP_1A0C];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+13
static unsigned32 map1A0D[CAN_SIZE_PDOMAP_1A0D];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+14
static unsigned32 map1A0E[CAN_SIZE_PDOMAP_1A0E];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+15
static unsigned32 map1A0F[CAN_SIZE_PDOMAP_1A0F];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+16
static unsigned32 map1A10[CAN_SIZE_PDOMAP_1A10];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+17
static unsigned32 map1A11[CAN_SIZE_PDOMAP_1A11];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+18
static unsigned32 map1A12[CAN_SIZE_PDOMAP_1A12];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+19
static unsigned32 map1A13[CAN_SIZE_PDOMAP_1A13];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+20
static unsigned32 map1A14[CAN_SIZE_PDOMAP_1A14];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+21
static unsigned32 map1A15[CAN_SIZE_PDOMAP_1A15];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+22
static unsigned32 map1A16[CAN_SIZE_PDOMAP_1A16];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+23
static unsigned32 map1A17[CAN_SIZE_PDOMAP_1A17];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+24
static unsigned32 map1A18[CAN_SIZE_PDOMAP_1A18];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+25
static unsigned32 map1A19[CAN_SIZE_PDOMAP_1A19];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+26
static unsigned32 map1A1A[CAN_SIZE_PDOMAP_1A1A];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+27
static unsigned32 map1A1B[CAN_SIZE_PDOMAP_1A1B];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+28
static unsigned32 map1A1C[CAN_SIZE_PDOMAP_1A1C];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+29
static unsigned32 map1A1D[CAN_SIZE_PDOMAP_1A1D];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+30
static unsigned32 map1A1E[CAN_SIZE_PDOMAP_1A1E];
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+31
static unsigned32 map1A1F[CAN_SIZE_PDOMAP_1A1F];
#endif


static void define_map_tran_001_032(void)
{
#if CAN_NOF_PDO_TRANSMIT >= 1
	pdomap[CAN_NOF_PDO_RECEIVE+1-1].pointer = map1A00;
	pdomap[CAN_NOF_PDO_RECEIVE+1-1].nmax = sizeof(map1A00) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+1
	pdomap[CAN_NOF_PDO_RECEIVE+1].pointer = map1A01;
	pdomap[CAN_NOF_PDO_RECEIVE+1].nmax = sizeof(map1A01) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+2
	pdomap[CAN_NOF_PDO_RECEIVE+1+1].pointer = map1A02;
	pdomap[CAN_NOF_PDO_RECEIVE+1+1].nmax = sizeof(map1A02) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+3
	pdomap[CAN_NOF_PDO_RECEIVE+1+2].pointer = map1A03;
	pdomap[CAN_NOF_PDO_RECEIVE+1+2].nmax = sizeof(map1A03) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+4
	pdomap[CAN_NOF_PDO_RECEIVE+1+3].pointer = map1A04;
	pdomap[CAN_NOF_PDO_RECEIVE+1+3].nmax = sizeof(map1A04) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+5
	pdomap[CAN_NOF_PDO_RECEIVE+1+4].pointer = map1A05;
	pdomap[CAN_NOF_PDO_RECEIVE+1+4].nmax = sizeof(map1A05) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+6
	pdomap[CAN_NOF_PDO_RECEIVE+1+5].pointer = map1A06;
	pdomap[CAN_NOF_PDO_RECEIVE+1+5].nmax = sizeof(map1A06) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+7
	pdomap[CAN_NOF_PDO_RECEIVE+1+6].pointer = map1A07;
	pdomap[CAN_NOF_PDO_RECEIVE+1+6].nmax = sizeof(map1A07) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+8
	pdomap[CAN_NOF_PDO_RECEIVE+1+7].pointer = map1A08;
	pdomap[CAN_NOF_PDO_RECEIVE+1+7].nmax = sizeof(map1A08) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+9
	pdomap[CAN_NOF_PDO_RECEIVE+1+8].pointer = map1A09;
	pdomap[CAN_NOF_PDO_RECEIVE+1+8].nmax = sizeof(map1A09) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+10
	pdomap[CAN_NOF_PDO_RECEIVE+1+9].pointer = map1A0A;
	pdomap[CAN_NOF_PDO_RECEIVE+1+9].nmax = sizeof(map1A0A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+11
	pdomap[CAN_NOF_PDO_RECEIVE+1+10].pointer = map1A0B;
	pdomap[CAN_NOF_PDO_RECEIVE+1+10].nmax = sizeof(map1A0B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+12
	pdomap[CAN_NOF_PDO_RECEIVE+1+11].pointer = map1A0C;
	pdomap[CAN_NOF_PDO_RECEIVE+1+11].nmax = sizeof(map1A0C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+13
	pdomap[CAN_NOF_PDO_RECEIVE+1+12].pointer = map1A0D;
	pdomap[CAN_NOF_PDO_RECEIVE+1+12].nmax = sizeof(map1A0D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+14
	pdomap[CAN_NOF_PDO_RECEIVE+1+13].pointer = map1A0E;
	pdomap[CAN_NOF_PDO_RECEIVE+1+13].nmax = sizeof(map1A0E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+15
	pdomap[CAN_NOF_PDO_RECEIVE+1+14].pointer = map1A0F;
	pdomap[CAN_NOF_PDO_RECEIVE+1+14].nmax = sizeof(map1A0F) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+16
	pdomap[CAN_NOF_PDO_RECEIVE+1+15].pointer = map1A10;
	pdomap[CAN_NOF_PDO_RECEIVE+1+15].nmax = sizeof(map1A10) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+17
	pdomap[CAN_NOF_PDO_RECEIVE+1+16].pointer = map1A11;
	pdomap[CAN_NOF_PDO_RECEIVE+1+16].nmax = sizeof(map1A11) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+18
	pdomap[CAN_NOF_PDO_RECEIVE+1+17].pointer = map1A12;
	pdomap[CAN_NOF_PDO_RECEIVE+1+17].nmax = sizeof(map1A12) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+19
	pdomap[CAN_NOF_PDO_RECEIVE+1+18].pointer = map1A13;
	pdomap[CAN_NOF_PDO_RECEIVE+1+18].nmax = sizeof(map1A13) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+20
	pdomap[CAN_NOF_PDO_RECEIVE+1+19].pointer = map1A14;
	pdomap[CAN_NOF_PDO_RECEIVE+1+19].nmax = sizeof(map1A14) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+21
	pdomap[CAN_NOF_PDO_RECEIVE+1+20].pointer = map1A15;
	pdomap[CAN_NOF_PDO_RECEIVE+1+20].nmax = sizeof(map1A15) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+22
	pdomap[CAN_NOF_PDO_RECEIVE+1+21].pointer = map1A16;
	pdomap[CAN_NOF_PDO_RECEIVE+1+21].nmax = sizeof(map1A16) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+23
	pdomap[CAN_NOF_PDO_RECEIVE+1+22].pointer = map1A17;
	pdomap[CAN_NOF_PDO_RECEIVE+1+22].nmax = sizeof(map1A17) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+24
	pdomap[CAN_NOF_PDO_RECEIVE+1+23].pointer = map1A18;
	pdomap[CAN_NOF_PDO_RECEIVE+1+23].nmax = sizeof(map1A18) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+25
	pdomap[CAN_NOF_PDO_RECEIVE+1+24].pointer = map1A19;
	pdomap[CAN_NOF_PDO_RECEIVE+1+24].nmax = sizeof(map1A19) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+26
	pdomap[CAN_NOF_PDO_RECEIVE+1+25].pointer = map1A1A;
	pdomap[CAN_NOF_PDO_RECEIVE+1+25].nmax = sizeof(map1A1A) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+27
	pdomap[CAN_NOF_PDO_RECEIVE+1+26].pointer = map1A1B;
	pdomap[CAN_NOF_PDO_RECEIVE+1+26].nmax = sizeof(map1A1B) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+28
	pdomap[CAN_NOF_PDO_RECEIVE+1+27].pointer = map1A1C;
	pdomap[CAN_NOF_PDO_RECEIVE+1+27].nmax = sizeof(map1A1C) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+29
	pdomap[CAN_NOF_PDO_RECEIVE+1+28].pointer = map1A1D;
	pdomap[CAN_NOF_PDO_RECEIVE+1+28].nmax = sizeof(map1A1D) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+30
	pdomap[CAN_NOF_PDO_RECEIVE+1+29].pointer = map1A1E;
	pdomap[CAN_NOF_PDO_RECEIVE+1+29].nmax = sizeof(map1A1E) / sizeof(unsigned32);
#endif
#if CAN_NOF_PDO_TRANSMIT >= 1+31
	pdomap[CAN_NOF_PDO_RECEIVE+1+30].pointer = map1A1F;
	pdomap[CAN_NOF_PDO_RECEIVE+1+30].nmax = sizeof(map1A1F) / sizeof(unsigned32);
#endif
}
