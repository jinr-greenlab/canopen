extern unsigned16	project_code;   // Based on the device configuration
extern unsigned8  device_state;   // The device logical state ON/OFF

extern unsigned8 digital_inblocks, digital_outblocks;  // Device configuration, digital 8 bit blocks
extern unsigned8 analog_inputs, analog_outputs;        // Device configuration, analog channels
extern unsigned8 analog_inp_res, analog_out_res;       // Analog resolution, Bits

extern cannode     nodeid_eeprom;   // 0x2110
extern unsigned8   brindex_eeprom;  // 0x2111

extern unsigned8   diginp_tpdo_forced;    // Digital inputs TPDO mode

extern struct store stc_1[CAN_NOF_LOAD_COMM_1];   // Re-store communication 1 configuration
extern struct store stc_2[CAN_NOF_LOAD_COMM_2];   // Re-store communication 2 configuration
extern struct store stap[CAN_NOF_LOAD_APPL];      // Re-store application configuration
