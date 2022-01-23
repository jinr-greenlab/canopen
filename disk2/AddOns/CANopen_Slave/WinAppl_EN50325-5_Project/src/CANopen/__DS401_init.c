#include <DS401_header.h>

#if CHECK_VERSION_APPL(2, 1, 2)
//  CHECK_VERSION_APPL(2, 0, 2)

cannode get_node_id(void)    // 2.1.2 some changes
{
	int16 nf;
	cannode node;

	nf = get_flash_nodeid();
#if ( (IOREMOTE_NODERATE_SWITCH == HARDWARE_SW) && (IOREMOTE_PLATFORM == PLATFORM_STM32) )
	if (nf < 0) node = PCB_ReadNodeID();
	else node = (cannode)nf;
#else
	if (nf < 0) node = CAN_NODEID_SLAVE;
	else node = (cannode)nf;
#endif
	if (check_node_id(node) != CAN_RETOK) node = CAN_NODE_ID_MAX;
	server_write_object_dictionary(INDEX_EEPROM_CAN_NODEID, 0, (canbyte*)&node);
	return node;
}

unsigned8 get_bit_rate_index(void)    // 2.1.2 some changes
{
	int16 rf;
	unsigned8 br;
    
	rf = get_flash_bitrate_index();
#if ( (IOREMOTE_NODERATE_SWITCH == HARDWARE_SW) && (IOREMOTE_PLATFORM == PLATFORM_STM32) )
	if (rf < 0) br = PCB_ReadBaud();
	else br = (unsigned8)rf;
#else
	if (rf < 0) br = CAN_BITRATE_INDEX;
	else br = (unsigned8)rf;
#endif
	if (check_bitrate_index(br) != CAN_RETOK) br = CIA_BITRATE_INDEX_500;    // 500 Kbit/S
	server_write_object_dictionary(INDEX_EEPROM_CAN_BITRATE, 0, (canbyte*)&br);
	return br;
}

unsigned32 get_serial_number(void)
{
	return CAN_SERIAL_NUMBER;
}

void get_device_config(void)
{
#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
  unsigned16 bitrate;
#endif
	project_code = CAN_PROJECT_CODE_DUMMY;
	digital_inblocks = 0;
	digital_outblocks = 0;
	analog_inputs = 0;
	analog_outputs = 0;
	analog_inp_res = 0;
	analog_out_res = 0;

#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)

	print_appl("\nIOremote CiA401+ EN50325-5");
	if (IOREMOTE_DEVICE_TYPE == R2DIO_IO) {
		project_code = CAN_PROJECT_CODE_DIOC;
		digital_inblocks = DIGITAL_INP8_BLOCKS_TEST;
		digital_outblocks = DIGITAL_OUT8_BLOCKS_TEST;
		if (digital_inblocks > DIGITAL_INP8_BLOCKS_MAX) digital_inblocks = DIGITAL_INP8_BLOCKS_MAX;
		if (digital_outblocks > DIGITAL_OUT8_BLOCKS_MAX) digital_outblocks = DIGITAL_OUT8_BLOCKS_MAX;
		print_appl("\nDIO digital, %-1i inputs and counters, %-1i outputs", 8*digital_inblocks, 8*digital_outblocks);
	} else if (IOREMOTE_DEVICE_TYPE == R2AIO_8INP) {
		project_code = CAN_PROJECT_CODE_ANALOG_16BIT;
		analog_inputs = ANALOG_INPUT_CHANS_MAX;
		if (analog_inputs > ANALOG_INPUT_CHANS_MAX) analog_inputs = ANALOG_INPUT_CHANS_MAX;
		analog_inp_res = ANALOG_INPUT_RESOLUTION;
		print_appl("\nAIO-8I 16bit-analog %-1i inputs", analog_inputs);
	} else if (IOREMOTE_DEVICE_TYPE == R2AIO_8OUT) {
		project_code = CAN_PROJECT_CODE_ANALOG_16BIT;
		analog_outputs = ANALOG_OUTPUT_CHANS_MAX;
		if (analog_outputs > ANALOG_OUTPUT_CHANS_MAX) analog_outputs = ANALOG_OUTPUT_CHANS_MAX;
		analog_out_res = ANALOG_OUTPUT_RESOLUTION;
		print_appl("\nAIO-8O 16bit-analog %-1i outputs",  analog_outputs);
	} else if (IOREMOTE_DEVICE_TYPE == R2AIO_4INP_2OUT) {
		project_code = CAN_PROJECT_CODE_ANALOG_16BIT;
		analog_inputs = 4;
		analog_outputs = 2;
		if (analog_inputs > ANALOG_INPUT_CHANS_MAX) analog_inputs = ANALOG_INPUT_CHANS_MAX;
		if (analog_outputs > ANALOG_OUTPUT_CHANS_MAX) analog_outputs = ANALOG_OUTPUT_CHANS_MAX;
		analog_inp_res = ANALOG_INPUT_RESOLUTION;
		analog_out_res = ANALOG_OUTPUT_RESOLUTION;
		print_appl("\nAIO-4I-2O 16bit-analog %-1i inputs, %-1i outputs", analog_inputs, analog_outputs);
	}
	bitrate = 0;
	if (CAN_BITRATE_INDEX == CIA_BITRATE_INDEX_1000) bitrate = 1000;
	else if (CAN_BITRATE_INDEX == CIA_BITRATE_INDEX_800) bitrate = 800;
	else if (CAN_BITRATE_INDEX == CIA_BITRATE_INDEX_500) bitrate = 500;
	else if (CAN_BITRATE_INDEX == CIA_BITRATE_INDEX_250) bitrate = 250;
	else if (CAN_BITRATE_INDEX == CIA_BITRATE_INDEX_125) bitrate = 125;
	else if (CAN_BITRATE_INDEX == CIA_BITRATE_INDEX_50) bitrate = 50;
	else if (CAN_BITRATE_INDEX == CIA_BITRATE_INDEX_20) bitrate = 20;
	else if (CAN_BITRATE_INDEX == CIA_BITRATE_INDEX_10) bitrate = 10;
	print_appl("\nBitRate %-1i Kbit/s,  CANopen node %-1i\n\n", bitrate, CAN_NODEID_SLAVE);

#elif (IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR)

  #if (IOREMOTE_PLATFORM == PLATFORM_STM32)
	
	hwconf.dev_type = DEV_PROJ;		// 1.7.x
	if (hwconf.dev_type == DEV_R2DIO) {
		project_code = CAN_PROJECT_CODE_DIOC;
		if (hwconf.din_num != 0) {
			digital_inblocks = 1 + (hwconf.din_num-1)/8;
			if (digital_inblocks >  DIGITAL_INP8_BLOCKS_MAX) digital_inblocks = DIGITAL_INP8_BLOCKS_MAX;
		}
		if (hwconf.dout_num != 0) {
			digital_outblocks = 1 + (hwconf.dout_num-1)/8;
			if (digital_outblocks >  DIGITAL_OUT8_BLOCKS_MAX) digital_outblocks = DIGITAL_OUT8_BLOCKS_MAX;
		}
	} else if (hwconf.dev_type == DEV_R2AI) {
		project_code = CAN_PROJECT_CODE_ANALOG_16BIT;
		analog_inputs =  ANALOG_INPUT_CHANS_MAX;
		if (analog_inputs > ANALOG_INPUT_CHANS_MAX) analog_inputs = ANALOG_INPUT_CHANS_MAX;
		analog_inp_res = ANALOG_INPUT_RESOLUTION;
	} else if (hwconf.dev_type == DEV_R2AO) {
		project_code = CAN_PROJECT_CODE_ANALOG_16BIT;
		analog_outputs =  ANALOG_OUTPUT_CHANS_MAX;
		if (analog_outputs > ANALOG_OUTPUT_CHANS_MAX) analog_outputs = ANALOG_OUTPUT_CHANS_MAX;
		analog_out_res = ANALOG_OUTPUT_RESOLUTION;
	}

  #elif (IOREMOTE_PLATFORM == PLATFORM_MILANDR)

	if (IOREMOTE_DEVICE_TYPE == R2DIO_IO) {
		project_code = CAN_PROJECT_CODE_DIOC;
		digital_inblocks = 1;
		digital_outblocks = 1;
		if (digital_inblocks > DIGITAL_INP8_BLOCKS_MAX) digital_inblocks = DIGITAL_INP8_BLOCKS_MAX;
		if (digital_outblocks > DIGITAL_OUT8_BLOCKS_MAX) digital_outblocks = DIGITAL_OUT8_BLOCKS_MAX;
	} else if (IOREMOTE_DEVICE_TYPE == R2AIO_4INP_2OUT) {
		project_code = CAN_PROJECT_CODE_ANALOG_16BIT;
		analog_inputs = 4;
		analog_outputs = 2;
		if (analog_inputs > ANALOG_INPUT_CHANS_MAX) analog_inputs = ANALOG_INPUT_CHANS_MAX;
		if (analog_outputs > ANALOG_OUTPUT_CHANS_MAX) analog_outputs = ANALOG_OUTPUT_CHANS_MAX;
		analog_inp_res = ANALOG_INPUT_RESOLUTION;
		analog_out_res = ANALOG_OUTPUT_RESOLUTION;
	}
	

  #endif

#endif

}

#endif
