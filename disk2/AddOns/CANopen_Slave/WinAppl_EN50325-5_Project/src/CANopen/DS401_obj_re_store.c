#include <DS401_header.h>

#if CHECK_VERSION_APPL(2, 1, 0)
//  CHECK_VERSION_APPL(2, 0, 1)

void can_init_re_store_application(void)
{
	unsigned16 msk, cnt;

	if (digital_inblocks != 0) {
		stc_1[32].index = INDEX_DIGINP_INT_ENABLE;		// Digital input global interrupt enable
	}
	if (analog_inputs != 0) {
		stc_1[36].index = INDEX_ANINP_INT_ENABLE;		// Analog input global interrupt enable
	}

	if (digital_inblocks != 0) {
		if (digital_inblocks == 1) msk = 0x1;
		else msk = 0x3;
		stap[0].index = INDEX_DIGINP_POLARITY;  // Polarity input 8 bit
		stap[0].submask01 = msk;
		stap[1].index = INDEX_DIGINP_IMASK_ANY; // Interrupt mask any change 8 bit
		stap[1].submask01 = msk;
		stap[2].index = INDEX_DIGINP_IMASK_L_H; // Interrupt mask low-to-high change 8 bit
		stap[2].submask01 = msk;
		stap[3].index = INDEX_DIGINP_IMASK_H_L; // Interrupt mask high-to-low change 8 bit
		stap[3].submask01 = msk;
	}

	if (digital_outblocks != 0) {
		if (digital_outblocks == 1) msk = 0x1;
		else msk = 0x3;
		stap[7].index = INDEX_DIGOUT_ERRMODE;   // Error mode output 8 bit
		stap[7].submask01 = msk;
		stap[8].index = INDEX_DIGOUT_ERRVALUE;  // Error value output 8 bit
		stap[8].submask01 = msk;
		stap[9].index = INDEX_DIGOUT_POLARITY;  // Change polarity output 8 bit
		stap[9].submask01 = msk;
		stap[10].index = INDEX_DIGOUT_DATA;		// Write output 8 bit
		stap[10].submask01 = msk;
		// Filter mask output excluded from the store list
	}

	if (analog_inputs != 0) {
		msk = 0;
		for (cnt = 0; cnt < analog_inputs; cnt++) msk = (msk << 1) | 1;
		stap[12].index = INDEX_ANINP_INT_TRIGGER;	// Analog input interrupt trigger selection
		stap[12].submask01 = msk;
		stap[13].index = INDEX_ANINP_UPPER;			// Analog input interrupt upper limit integer
		stap[13].submask01 = msk;
		stap[14].index = INDEX_ANINP_LOWER;			// Analog input interrupt lower limit integer
		stap[14].submask01 = msk;
		stap[15].index = INDEX_ANINP_DELTA_UNS;		// Analog input interrupt delta unsigned
		stap[15].submask01 = msk;
		stap[16].index = INDEX_ANINP_OFFSET;		// Analog input offset float
		stap[16].submask01 = msk;
		stap[17].index = INDEX_ANINP_SCALING;		// Analog input scaling float
		stap[17].submask01 = msk;
	}

	if (analog_outputs != 0) {
		msk = 0;
		for (cnt = 0; cnt < analog_outputs; cnt++) msk = (msk << 1) | 1;
		stap[18].index = INDEX_ANOUT_ERRMODE;   // Analog output error mode
		stap[18].submask01 = msk;
		stap[19].index = INDEX_ANOUT_ERRVALUE;  // Analog output error value integer
		stap[19].submask01 = msk;
		stap[20].index = INDEX_ANOUT_DAC_CLOCK;	// DAC slew rate clock period
		stap[20].submask01 = msk;
		stap[21].index = INDEX_ANOUT_DAC_STEP;	// DAC slew rate step
		stap[21].submask01 = msk;
		stap[22].index = INDEX_ANOUT_DATA_16;	// Write analog output 16 bit
		stap[22].submask01 = msk;
	}
}

#endif
