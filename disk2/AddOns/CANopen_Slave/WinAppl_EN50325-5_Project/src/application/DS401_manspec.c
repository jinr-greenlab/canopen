#include <DS401_header.h>

#if CHECK_VERSION_APPL(2, 1, 2)
//  CHECK_VERSION_APPL(2, 0, 1)

static unsigned8 subs_config;
static unsigned8 subs_digital_cnt;
static const unsigned8 subs_logical_cnt=LOGICAL_COUNTERS_MAX;
static const unsigned8 counters_int_source=1;	// 32 interrupt sources max

static unsigned16 dout_inhemcy, anout_inhemcy;
static unsigned32 dout_inhcnt, dout_resetcnt, anout_inhcnt;
static unsigned32 digout_status, digout_status_prev, digout_emcy_cs_mask;
static unsigned8 anout_status, anout_status_prev, anout_emcy_cs_mask, anout_emcy_ld_mask;

static struct {
	unsigned8 updated;
	unsigned8 dac_clock;
	unsigned8 dac_step;
} dacrate[ANALOG_OUTPUT_CHANS_MAX];

static struct digcnt {
	unsigned32 data;
	unsigned32 prev_data;
	unsigned8 int_trigger;
	unsigned32 upper_limit;
	unsigned32 delta;
} counter[DIGITAL_COUNTERS_MAX];

static unsigned8 logical_counters[LOGICAL_COUNTERS_MAX];
static unsigned16 zero_mask;

static unsigned32 int_source_counter;
static unsigned8 int_enable_counter;

#if ((IOREMOTE_APPLICATION_MODE != APPLICATION_REGULAR) || (IOREMOTE_PLATFORM != PLATFORM_STM32))
static unsigned32 dummy_data=0;
#endif

// Called from the application_monitor_routine()
void process_logical_counter(unsigned8 lcc)
{
	unsigned8 chan;
	unsigned32 dif;
	struct digcnt *dc;

	if (lcc >= LOGICAL_COUNTERS_MAX) return;
	chan = logical_counters[lcc]-1;
	if (chan >= DIGITAL_COUNTERS_MAX) return;
	dc = counter+chan;
	if (dc->data == dc->prev_data) return;
	if (int_enable_counter == FALSE) return;
	if (dc->data < dc->upper_limit) return;
	if ((dc->int_trigger & MASK_COUNTER_INT_UP_LIMIT) == 0) return;
	if (dc->int_trigger & MASK_COUNTER_INT_DELTA) {
		if (dc->data >= dc->prev_data) dif = dc->data - dc->prev_data;
		else dif = dc->prev_data - dc->data;
		if (dif < dc->delta) return;
	}
	dc->prev_data = dc->data;
	int_source_counter |= (1 << chan);
	set_transmit_pdo((canindex)(INDEX_TRNPDO_COMM_COUNTER_2 + lcc/2));
}

// Called from the application_monitor_routine()
void write_digital_counter(unsigned8 chan, unsigned32 data)
{
	if (chan >= DIGITAL_COUNTERS_MAX) return;
	counter[chan].data = data;
}

static void get_sub0_basic(struct object *obj)
{
	obj->size = sizeof(unsigned8);
	obj->deftype = CAN_DEFTYPE_UNSIGNED8;
	obj->access = CAN_MASK_ACCESS_RO;
}

static void get_sub0_digital_cnt(struct object *obj)
{
	get_sub0_basic(obj);
	obj->pnt = (canbyte*)&subs_digital_cnt;
}

static void get_sub0_digout(struct object *obj)
{
	get_sub0_basic(obj);
	obj->pnt = (canbyte*)&digital_outblocks;
}

static void get_sub0_aninp(struct object *obj)
{
	get_sub0_basic(obj);
	obj->pnt = (canbyte*)&analog_inputs;
}

static void get_sub0_anout(struct object *obj)
{
	get_sub0_basic(obj);
	obj->pnt = (canbyte*)&analog_outputs;
}

static void get_object_manspec(struct object *obj)
{
	obj->size = CAN_ERRET_OBD_NOSUBIND;
	obj->deftype = 0; 
	obj->access = 0;
	obj->pnt = NULL;

	if (digital_inblocks != 0) {
		if (obj->index == INDEX_LOGICAL_CNT_DATA) {
			if (obj->subind == 0) {
				get_sub0_basic(obj);
				obj->pnt = (canbyte*)&subs_logical_cnt;
			} else if (obj->subind <= subs_logical_cnt) {
				obj->size = sizeof(unsigned32);
				obj->deftype = CAN_DEFTYPE_UNSIGNED32;
				obj->access = CAN_MASK_ACCESS_RO | CAN_MASK_ACCESS_PDO;
				obj->pnt = (canbyte*)&counter[logical_counters[obj->subind-1]-1].data;
			}
			return;
		}
		if (obj->index == INDEX_COUNTERS_ZERO_MASK) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned16);
				obj->deftype = CAN_DEFTYPE_UNSIGNED16;
				obj->access = CAN_MASK_ACCESS_WO | CAN_MASK_ACCESS_PDO;
				obj->pnt = (canbyte*)&zero_mask;
			}
			return;
		}
		if (obj->index == INDEX_COUNTER_DATA_UNS) {
			if (obj->subind == 0) {
				get_sub0_digital_cnt(obj);
			} else if (obj->subind <= subs_digital_cnt) {
				obj->size = sizeof(unsigned32);
				obj->deftype = CAN_DEFTYPE_UNSIGNED32;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&counter[obj->subind-1].data;
			}
			return;
		}	  
		if (obj->index == INDEX_LOGICAL_CNT_SET) {
			if (obj->subind == 0) {
				get_sub0_basic(obj);
				obj->pnt = (canbyte*)&subs_logical_cnt;
			} else if (obj->subind <= subs_logical_cnt) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&logical_counters[obj->subind-1];
			}
			return;
		}	  
		if (obj->index == INDEX_COUNTER_INT_ENABLE) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_BOOLEAN;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&int_enable_counter;
			}
			return;
		}
		if (obj->index == INDEX_COUNTER_INT_TRIGGER) {
			if (obj->subind == 0) {
				get_sub0_digital_cnt(obj);
			} else if (obj->subind <= subs_digital_cnt) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&counter[obj->subind-1].int_trigger;
			}
			return;
		}
		if (obj->index == INDEX_COUNTER_INT_SOURCE) {
			if (obj->subind == 0) {
				get_sub0_basic(obj);
				obj->pnt = (canbyte*)&counters_int_source;
			} else if (obj->subind <= counters_int_source) {
				obj->size = sizeof(unsigned32);
				obj->deftype = CAN_DEFTYPE_UNSIGNED32;
				obj->access = CAN_MASK_ACCESS_RO;
				obj->pnt = (canbyte*)&int_source_counter;
			}
			return;
		}
		if (obj->index == INDEX_COUNTER_UPPER_UNS) {
			if (obj->subind == 0) {
				get_sub0_digital_cnt(obj);
			} else if (obj->subind <= subs_digital_cnt) {
				obj->size = sizeof(unsigned32);
				obj->deftype = CAN_DEFTYPE_UNSIGNED32;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&counter[obj->subind-1].upper_limit;
			}
			return;
		}
		if (obj->index == INDEX_COUNTER_DELTA_UNS) {
			if (obj->subind == 0) {
				get_sub0_digital_cnt(obj);
			} else if (obj->subind <= subs_digital_cnt) {
				obj->size = sizeof(unsigned32);
				obj->deftype = CAN_DEFTYPE_UNSIGNED32;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&counter[obj->subind-1].delta;
			}
			return;
		}
    if (obj->index == INDEX_DIGINP_TPDO_FORCED) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_BOOLEAN;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&diginp_tpdo_forced;
			}
			return;
		}
	}

	if (digital_outblocks != 0) {
		if (obj->index == INDEX_DIGOUT_STATUS) {
			if (obj->subind == 0) {
				get_sub0_digout(obj);
			} else if (obj->subind <= digital_outblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RO;
				obj->pnt = (canbyte*)&digout_status + obj->subind - 1;
			}
			return;
		}
		if (obj->index == INDEX_DIGOUT_EMCY_INHIBIT) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned16);
				obj->deftype = CAN_DEFTYPE_UNSIGNED16;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dout_inhemcy;
			}
			return;
		}
		if (obj->index == INDEX_DIGOUT_EMCY_CS_MASK) {
			if (obj->subind == 0) {
				get_sub0_digout(obj);
			} else if (obj->subind <= digital_outblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&digout_emcy_cs_mask + obj->subind - 1;
			}
			return;
		}
	}   

	if (analog_inputs != 0) {
		if (obj->index == INDEX_ANINP_RANGE) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RO;
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
				obj->pnt = (canbyte*)&hwconf.ain_range_num;
#else
				obj->pnt = (canbyte*)&dummy_data;
				dummy_data = 1;		// 0..+5B
#endif
			}
			return;
		}
		if (obj->index == INDEX_ANINP_RATE) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RO;
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
				obj->pnt = (canbyte*)&hwconf.ain_sps_num;
#else
				obj->pnt = (canbyte*)&dummy_data;
				dummy_data = 4;		// 30 Ãö
#endif
			}
			return;
		}
	}

	if (analog_outputs != 0) {
		if (obj->index == INDEX_ANOUT_STATUS) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RO;
				obj->pnt = (canbyte*)&anout_status;
			}
			return;
		}
		if (obj->index == INDEX_ANOUT_EMCY_INHIBIT) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned16);
				obj->deftype = CAN_DEFTYPE_UNSIGNED16;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&anout_inhemcy;
			}
			return;
		}
		if (obj->index == INDEX_ANOUT_EMCY_CS_MASK) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&anout_emcy_cs_mask;
			}
			return;
		}
		if (obj->index == INDEX_ANOUT_EMCY_LD_MASK) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&anout_emcy_ld_mask;
			}
			return;
		}
		if (obj->index == INDEX_ANOUT_RANGE) {
			if (obj->subind == 0) {
				get_sub0_anout(obj);
			} else if (obj->subind <= analog_outputs) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
			 	obj->access = CAN_MASK_ACCESS_RO;
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
				obj->pnt = (canbyte*)&hwconf.aout_range_num[obj->subind-1];
#else
				obj->pnt = (canbyte*)&dummy_data;
				dummy_data = 0;
#endif
			}
			return;
		}
		if (obj->index == INDEX_ANOUT_DAC_CLOCK) {
			if (obj->subind == 0) {
				get_sub0_anout(obj);
			} else if (obj->subind <= analog_outputs) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
			 	obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dacrate[obj->subind-1].dac_clock;
			}
			return;
		}
		if (obj->index == INDEX_ANOUT_DAC_STEP) {
			if (obj->subind == 0) {
				get_sub0_anout(obj);
			} else if (obj->subind <= analog_outputs) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
			 	obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dacrate[obj->subind-1].dac_step;
			}
			return;
		}
	}

	if (obj->index == INDEX_EEPROM_CAN_NODEID ||
		obj->index == INDEX_EEPROM_CAN_BITRATE) {
		if (obj->subind == 0) {
			obj->size = sizeof(unsigned8);
			obj->deftype = CAN_DEFTYPE_UNSIGNED8;
			obj->access = CAN_MASK_ACCESS_RW;
			if (obj->index == INDEX_EEPROM_CAN_NODEID) {
				obj->pnt = (canbyte*)&nodeid_eeprom;
			} else {
				obj->pnt = (canbyte*)&brindex_eeprom;
			}
		}
		return;
	}

	if (obj->index == INDEX_DEVICE_CONFIG) {
		if (obj->subind == 0) {
			obj->size = sizeof(unsigned8);
			obj->deftype = CAN_DEFTYPE_UNSIGNED8;
			obj->access = CAN_MASK_ACCESS_RO;
			obj->pnt = (canbyte*)&subs_config;
		} else if (obj->subind <= subs_config) {
			obj->size = sizeof(unsigned8);
			obj->deftype = CAN_DEFTYPE_UNSIGNED8;
			obj->access = CAN_MASK_ACCESS_RO;
			if (obj->subind == SUBIND_CONFIG_DIGINP) obj->pnt = (canbyte*)&digital_inblocks;
			else if (obj->subind == SUBIND_CONFIG_DIGOUT) obj->pnt = (canbyte*)&digital_outblocks;
			else if (obj->subind == SUBIND_CONFIG_ANINP) obj->pnt = (canbyte*)&analog_inputs;
			else if (obj->subind == SUBIND_CONFIG_ANOUT) obj->pnt = (canbyte*)&analog_outputs;
			else if (obj->subind == SUBIND_CONFIG_AI_RES) obj->pnt = (canbyte*)&analog_inp_res;
			else if (obj->subind == SUBIND_CONFIG_AO_RES) obj->pnt = (canbyte*)&analog_out_res;
			if (obj->subind == SUBIND_CONFIG_AIO_TYPE) {
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
				obj->pnt = (canbyte*)&hwconf.aio_type;
#else
				obj->pnt = (canbyte*)&dummy_data;
				dummy_data = 0;
#endif
			}
		}
		return;
	}

	obj->size = CAN_ERRET_OBD_NOOBJECT;
}

int32 server_get_manspec_objsize(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	return obj.size;
}

int32 server_put_manspec_objsize(canindex index, cansubind subind, int32 size)
{
	return CAN_ERRET_OBD_DATAMISM;
}

int16 server_see_manspec_access(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	return obj.access;
}

int16 server_get_manspec_objtype(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	return obj.deftype;
}

// NO async data update
int16 server_read_manspec_objdict(canindex index, cansubind subind, canbyte *data)
{
	int32 size, cnt;
	canbyte *bpnt;
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	if ((obj.access & CAN_MASK_ACCESS_RO) == 0) return CAN_ERRET_OBD_WRITEONLY;
	if (obj.pnt == NULL) return CAN_ERRET_NULL_POINTER;		// Extra-safety check
	size = obj.size;
	bpnt = obj.pnt;
	OBJECT_DICTIONARY_TO_CANOPEN
	if (index == INDEX_COUNTER_INT_SOURCE) int_source_counter = 0;
	return CAN_RETOK;
}

// NO async usage of the multi-byte data
int16 server_write_manspec_objdict(canindex index, cansubind subind, canbyte *data)
{
	int32 size, cnt;
	canbyte *bpnt;
	struct object obj;
	union numbers num;
 	unsigned8 chan;

	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	if ((obj.access & CAN_MASK_ACCESS_WO) == 0) return CAN_ERRET_OBD_READONLY;
	size = obj.size;
	bpnt = (canbyte*)&num;
	num.init = 0;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (index == INDEX_COUNTER_INT_TRIGGER) {
		if (num.uns8 > 0x1F) return CAN_ERRET_OBD_VALRANGE;
	} else if (index == INDEX_DIGOUT_EMCY_INHIBIT || index == INDEX_ANOUT_EMCY_INHIBIT) {
		if (num.uns16 > 0 && num.uns16 < CAN_EMCY_INHIBIT_100MCS_OUTPUT_MIN) return CAN_ERRET_OBD_VALRANGE;
	} else if (index == INDEX_LOGICAL_CNT_SET) {
		if (num.uns8 == 0 || num.uns8 > subs_digital_cnt) return CAN_ERRET_OBD_VALRANGE;
	} else if (index == INDEX_COUNTERS_ZERO_MASK) {
		for (chan = 0; chan < subs_digital_cnt; chan++) {
			if (num.uns16 & 1) {
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
				DIO_SetCounters(chan, 0);
#elif (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
				reset_emulated_counter(chan, 0);
#endif
			}
			num.uns16 >>= 1;
		}
		return CAN_RETOK;
	} else if (index == INDEX_COUNTER_DATA_UNS) {
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
		DIO_SetCounters(subind-1, num.uns32);
#elif (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
		reset_emulated_counter(subind-1, num.uns32);
#endif
		return CAN_RETOK;
	} else if (index == INDEX_ANOUT_DAC_CLOCK) {
		if (num.uns8 > 0xF) return CAN_ERRET_OBD_VALRANGE;
	} else if (index == INDEX_ANOUT_DAC_STEP) {
		if (num.uns8 > 0x7) return CAN_ERRET_OBD_VALRANGE;
	} else if (index == INDEX_EEPROM_CAN_NODEID) {
		if (check_node_id(num.uns8) != CAN_RETOK) return CAN_ERRET_OBD_VALRANGE;
	} else if (index == INDEX_EEPROM_CAN_BITRATE) {
		if (check_bitrate_index(num.uns8) != CAN_RETOK) return CAN_ERRET_OBD_VALRANGE;
	}
	if (obj.pnt == NULL) return CAN_ERRET_NULL_POINTER;		// Extra-safety check
	if (obj.deftype == CAN_DEFTYPE_BOOLEAN) {
		if (num.uns8 != FALSE) num.uns8 = TRUE;				// 1.8.4
	}
	bpnt = (canbyte*)&num;
	for (cnt = 0; cnt < size; cnt++) {
		*obj.pnt = *bpnt;
		obj.pnt++; bpnt++;
	}
	if (index == INDEX_ANOUT_DAC_STEP || index == INDEX_ANOUT_DAC_CLOCK) {
		dacrate[subind-1].updated = TRUE;
	}
	return CAN_RETOK;
}

void application_manspec_timer(void)
{
	if (dout_inhcnt > 0) dout_inhcnt--;
	if (dout_resetcnt > 0) dout_resetcnt--;
	if (anout_inhcnt > 0) anout_inhcnt--;
}

// Called from the application_monitor_routine()
void control_digital_outputs(void)
{
	canbyte dserr[5];
	canbyte *bpnt;

#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
	digout_status = ~DIO_GetStatusOut32Bit() & hwconf.dout_mask;
#else
	digout_status = 0;
#endif
	if (digout_status == 0) {
		if (digout_status_prev != 0) {
			clear_error_register(CAN_ERRBIT_CURRENT);
			digout_status_prev = 0;
		}
		return;
	}
	if (dout_resetcnt == 0) {
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
		DIO_RstStatusOut32Bit(digout_status);
#endif
		dout_resetcnt = 1 + CAN_DIGOUT_RESET_MCS / CAN_TIMERUSEC;
	}
	if (dout_inhemcy == 0) {
		if (digout_status == digout_status_prev) return;
		digout_status_prev = digout_status;
	} else {
		if (dout_inhcnt != 0) return;
		dout_inhcnt = (unsigned32)dout_inhemcy * 100 / CAN_TIMERUSEC;
	}
	if ((digout_emcy_cs_mask & digout_status) != 0) {
		bpnt = (canbyte*)&digout_status;
		dserr[0] = *bpnt; bpnt++;
		dserr[1] = *bpnt; bpnt++;
		dserr[2] = *bpnt; bpnt++;
		dserr[3] = *bpnt;
		dserr[4] = 0;
		produce_emcy(CAN_EMCY_SHORT_CIRCUIT, 0, dserr);
	} else {
		set_error_field(CAN_EMCY_SHORT_CIRCUIT, 0);
	}
}

// Called from the application_monitor_routine()
void control_analog_outputs(void)
{
	canbyte dserr[5];
	unsigned8 arm;
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
	unsigned8 chan;
	struct _DACErr derr;
#endif

#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
	for (chan = 0; chan < analog_outputs; chan++) {
		if (dacrate[chan].updated == TRUE) {
			dacrate[chan].updated = FALSE;
			DAC_AppSetSlewRate(chan, dacrate[chan].dac_clock, dacrate[chan].dac_step);
		}
	}
	DAC_AppGetErr(&derr);
	anout_status = derr.out_fault;
#else
	anout_status = 0;
#endif
	if (anout_status == 0) {
		if (anout_status_prev != 0) {
			clear_error_register(CAN_ERRBIT_CURRENT);
			anout_status_prev = 0;
		}
		return;
	}
	if (anout_inhemcy == 0) {
		if (anout_status == anout_status_prev) return;
		anout_status_prev = anout_status;
	} else {
		if (anout_inhcnt != 0) return;
		anout_inhcnt = (unsigned32)anout_inhemcy * 100 / CAN_TIMERUSEC;
	}
	dserr[1] = 0;
	dserr[2] = 0;
	dserr[3] = 0;
	dserr[4] = 0;
	arm = 0;
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
	for (chan = 0; chan < analog_outputs; chan++) {
		if ((hwconf.aout_range_num[chan] & 0x4) != 0) arm |= (1 << chan);	// Current channels
	}
#endif
	dserr[0] = anout_status & arm;
	if (dserr[0] != 0) {
		if ((anout_emcy_ld_mask & dserr[0]) != 0) {
			produce_emcy(CAN_EMCY_LOAD_DUMP, 0, dserr);
		} else {
			set_error_field(CAN_EMCY_LOAD_DUMP, 0);
		}
	}
	dserr[0] = anout_status & ~arm;
	if (dserr[0] != 0) {
		if ((anout_emcy_cs_mask & dserr[0]) != 0) {
			produce_emcy(CAN_EMCY_SHORT_CIRCUIT, 0, dserr);
		} else {
			set_error_field(CAN_EMCY_SHORT_CIRCUIT, 0);
		}
	}
}

unsigned8 read_int_enable_counter(void)
{
	return int_enable_counter;
}

void slave_init_manspec_application(void)
{
 	unsigned8 chan;

	if (analog_inputs != 0) subs_config = R2AI_CONFIG_SUBINDS;
	else if (analog_outputs != 0) subs_config = R2AO_CONFIG_SUBINDS;
	else subs_config = R2DIO_CONFIG_SUBINDS;

  digout_status = 0;
  digout_status_prev = 0;
  anout_status = 0;
  anout_status_prev = 0;

  diginp_tpdo_forced = FALSE;

	for (chan = 0; chan < DIGITAL_COUNTERS_MAX; chan++) {
		counter[chan].data = 0;
		counter[chan].prev_data = 0;
		counter[chan].int_trigger = 0x7;
		counter[chan].upper_limit = 0;
		counter[chan].delta = 0;
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
		DIO_SetCounters(chan, 0);
#endif
	}
	for (chan = 0; chan < LOGICAL_COUNTERS_MAX; chan++) {
		logical_counters[chan] = chan+1;
	}
	subs_digital_cnt = 8 * digital_inblocks;
	int_source_counter = 0;
	zero_mask = 0;

	for (chan = 0; chan < ANALOG_OUTPUT_CHANS_MAX; chan++) {
		dacrate[chan].updated = TRUE;	// To update actually
		dacrate[chan].dac_clock = 0;
		dacrate[chan].dac_step = 0;
	}
}

void slave_init_manspec_communication(void)
{
	dout_inhemcy = CAN_EMCY_INHIBIT_100MCS_OUTPUT_DEF;
	dout_inhcnt = 0;
	dout_resetcnt = 0;
	digout_emcy_cs_mask = MASK_DIGOUT_EMCY_CS;
	
	anout_inhemcy = CAN_EMCY_INHIBIT_100MCS_OUTPUT_DEF;
	anout_inhcnt = 0;
	anout_emcy_cs_mask = MASK_ANOUT_EMCY_CS;
	anout_emcy_ld_mask = MASK_ANOUT_EMCY_LD;
	
	if (digital_inblocks != 0) {

		server_write_obd_u32(INDEX_RCVPDO_MAP_COUNTER_2, 1, 0x20220010);
		server_write_obd_u32(INDEX_RCVPDO_MAP_COUNTER_2, 0, 1);
		set_pdo_state(INDEX_RCVPDO_COMM_COUNTER_2, VALID);

		server_write_obd_u32(INDEX_TRNPDO_MAP_COUNTER_2, 1, 0x20210120);
		server_write_obd_u32(INDEX_TRNPDO_MAP_COUNTER_2, 2, 0x20210220);
		server_write_obd_u32(INDEX_TRNPDO_MAP_COUNTER_2, 0, 2);
		set_pdo_state(INDEX_TRNPDO_COMM_COUNTER_2, VALID);

		server_write_obd_u32(INDEX_TRNPDO_MAP_COUNTER_3, 1, 0x20210320);
		server_write_obd_u32(INDEX_TRNPDO_MAP_COUNTER_3, 2, 0x20210420);
		server_write_obd_u32(INDEX_TRNPDO_MAP_COUNTER_3, 0, 2);
		set_pdo_state(INDEX_TRNPDO_COMM_COUNTER_3, VALID);

		server_write_obd_u32(INDEX_TRNPDO_MAP_COUNTER_4, 1, 0x20210520);
		server_write_obd_u32(INDEX_TRNPDO_MAP_COUNTER_4, 2, 0x20210620);
		server_write_obd_u32(INDEX_TRNPDO_MAP_COUNTER_4, 0, 2);
		set_pdo_state(INDEX_TRNPDO_COMM_COUNTER_4, VALID);

	}

	int_enable_counter = FALSE;
}

#endif
