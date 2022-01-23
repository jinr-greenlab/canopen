#include <DS401_header.h>

#if CHECK_VERSION_APPL(2, 1, 3)
// CHECK_VERSION_APPL(2, 0, 2)

static canindex pdo_tran_index[CAN_NOF_PDO_TRANSMIT];
static unsigned8 config_error=TRUE;
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
static struct _ADCData adc_data;
#endif


#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
#if (IOREMOTE_PRINTF_MODE == ON)
void print_appl(void *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stdout, (char *)fmt, ap);
	va_end(ap);
}
#else
void print_appl(void *fmt, ...)
{
}
#endif
#endif


#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)

static unsigned32 emulated_counter_value[DIGITAL_COUNTERS_MAX];
static unsigned8 emulated_data_prev[DIGITAL_INP8_BLOCKS_MAX];
static unsigned32 timer_cnt=0;

void reset_emulated_counter(unsigned8 chan, unsigned32 val)
{
	if (chan >= DIGITAL_COUNTERS_MAX) return;
	emulated_counter_value[chan] = val;
}

#endif

void set_transmit_pdo(canindex index)
{
	unsigned16 cnt;

	for (cnt = 0; cnt < CAN_NOF_PDO_TRANSMIT; cnt++) {
		if (pdo_tran_index[cnt] == CAN_INDEX_DUMMY) {
			pdo_tran_index[cnt] = index;
			return;
		}
		if (pdo_tran_index[cnt] == index) return;
	}
}

void consume_time(canframe *cf)
{
}

void start_hardware(void)	// 2.0.2 some changes
{
#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
 	unsigned8 chan;
#endif

#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
	timer_cnt = 0;
	for (chan = 0; chan < DIGITAL_COUNTERS_MAX; chan++) emulated_counter_value[chan] = 0;
	for (chan = 0; chan < DIGITAL_INP8_BLOCKS_MAX; chan++) emulated_data_prev[chan] = 0;
#endif

  nodeid_eeprom = get_node_id();
  brindex_eeprom = get_bit_rate_index();

  if (project_code == CAN_PROJECT_CODE_DUMMY) {
		device_state = OFF;
		config_error = TRUE;
		return;
	}
	device_state = ON;
	config_error = FALSE;
}

void stop_hardware(void)
{
	unsigned8 chan;

	slave_init_standev_application();
	if (digital_outblocks != 0) {
		write_digital_output(0);
		if (digital_outblocks > 1) write_digital_output(1);
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
		DIO_UpdateOut();
#endif
	}
	if (analog_outputs != 0) {
		for (chan = 0; chan < analog_outputs; chan++) {
			write_analog_output(chan);
		}
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
		DAC_AppPoll();
#endif
	}
	device_state = OFF;
}

void application_timer_routine(void)
{
	application_manspec_timer();

#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
	timer_cnt++;
#endif
}

#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
static void emulate_digital_counter(unsigned8 blk, unsigned8 data)
{
	unsigned8 chan, dtmp;

	if (data == emulated_data_prev[blk]) return;
	dtmp = emulated_data_prev[blk];
	emulated_data_prev[blk] = data;
	for (chan = 0; chan < 8; chan++) {
		if (((data & 1) != 0) && ((dtmp & 1) == 0)) emulated_counter_value[blk*8 + chan]++;
		data >>= 1;
		dtmp >>= 1;
	}
}
#endif

void application_monitor_routine(void)
{
	unsigned8 chan;
	unsigned32 rawdata;
#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
	unsigned32 timdiv;
#endif

	if (config_error == TRUE) {
		config_error = FALSE;
		set_led_green_off();
		set_led_red_blinking();		// Configuration error
	}
	if (device_state == OFF) return;

	for (chan = 0; chan < CAN_NOF_PDO_TRANSMIT; chan++) pdo_tran_index[chan] = CAN_INDEX_DUMMY;

#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
	timdiv = 160000 / CAN_TIMERUSEC;
#endif

	if (digital_inblocks != 0) {
#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
		rawdata = timer_cnt / timdiv;
		#if (R2DIO_TESTMODE == TESTMODE_LOOPBACK)
		if ((digital_inblocks == 1) && (digital_outblocks == 1)) {
			rawdata = read_digital_output_0();
		}
		#endif
		process_digital_input(0, (unsigned8)rawdata);
		emulate_digital_counter(0, (unsigned8)rawdata);
		if (digital_inblocks > 1) {
			rawdata = timer_cnt / (2*timdiv);
			process_digital_input(1, (unsigned8)rawdata);
			emulate_digital_counter(1, (unsigned8)rawdata);
		}
		for (chan = 0; chan < 8*digital_inblocks; chan++) {
			write_digital_counter(chan, emulated_counter_value[chan]);		
		}			
#elif (IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR)
  #if (IOREMOTE_PLATFORM == PLATFORM_STM32)
		DIO_UpdateOut();
		rawdata = DIO_GetIn32Bit();
		process_digital_input(0, (unsigned8)rawdata);
		if (digital_inblocks > 1) process_digital_input(1, (unsigned8)(rawdata >> 8));
		for (chan = 0; chan < 8*digital_inblocks; chan++) {
			DIO_GetCounters(chan, &rawdata);
			write_digital_counter(chan, rawdata);		
		}
  #elif (IOREMOTE_PLATFORM == PLATFORM_MILANDR)
		can_sleep(CAN_SLEEP_ONE_MILLISEC);		// 2.1.1 anti-ringing
		rawdata = Read_raw_data_from_ports();
		process_digital_input(0, (unsigned8)rawdata);
  #endif
#endif
		for (chan = 0; chan < LOGICAL_COUNTERS_MAX; chan++) {
			process_logical_counter(chan);		
		}
	}

	if (digital_outblocks != 0) {
		write_digital_output(0);
		if (digital_outblocks > 1) write_digital_output(1);
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
		DIO_UpdateOut();
#endif
		control_digital_outputs();
	}

	if (analog_inputs != 0) {
#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
		for (chan = 0; chan < analog_inputs; chan++) {
			process_analog_input(chan, (int16)((timer_cnt / (4*timdiv)) * (chan+1) * 211));
		}
#elif (IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR)
  #if (IOREMOTE_PLATFORM == PLATFORM_STM32)
		AdcAppPoll();
		if(AdcAppGetData(&adc_data)) {
			for (chan = 0; chan < analog_inputs; chan++) {
				process_analog_input(chan, (int32)(adc_data.code_int16[chan])-32768);   // 2.1.2 explicit type conversion
			}
		}
  #endif
#endif
	} 
	if (analog_outputs != 0) {
		for (chan = 0; chan < analog_outputs; chan++) {
			write_analog_output(chan);
		}
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
		DAC_AppPoll();
#endif
		control_analog_outputs();
	}

	for (chan = 0; chan < CAN_NOF_PDO_TRANSMIT; chan++) {
		if (pdo_tran_index[chan] == CAN_INDEX_DUMMY) break;
		transmit_can_pdo(pdo_tran_index[chan]);
	}

#if (IOREMOTE_PLATFORM == PLATFORM_WINDOWS)
	can_sleep(50*CAN_SLEEP_ONE_MILLISEC);
#endif
}

void application_init_device_routine(void)
{
	device_state = OFF;		// Extra init
	get_device_config();

#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
	if (digital_outblocks != 0) {
		DIO_SetOut32Bit(0x00000000);	// Set low all outputs, enable output
	}
	if (analog_inputs != 0) {
		AdcAppInit();
		AdcAppStartContConvert();
	}
	if (analog_outputs != 0) {
		DAC_AppInit();
	}
#endif
}


#endif
