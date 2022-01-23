#include <DS401_header.h>

unsigned16	project_code;   // Based on the device configuration
unsigned8   device_state;   // The device logical state ON/OFF

unsigned8 digital_inblocks, digital_outblocks;  // Device configuration, digital 8 bit blocks
unsigned8 analog_inputs, analog_outputs;        // Device configuration, analog channels
unsigned8 analog_inp_res, analog_out_res;       // Analog resolution, Bits

cannode     nodeid_eeprom;   // 0x2110
unsigned8   brindex_eeprom;  // 0x2111

unsigned8   diginp_tpdo_forced;  // Digital inputs TPDO mode

struct store stc_1[CAN_NOF_LOAD_COMM_1];   // Re-store communication 1 configuration
struct store stc_2[CAN_NOF_LOAD_COMM_2];   // Re-store communication 2 configuration
struct store stap[CAN_NOF_LOAD_APPL];      // Re-store application configuration
