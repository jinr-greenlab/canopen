#include <DS401_header.h>

#if CHECK_VERSION_APPL(2, 1, 1)
//  CHECK_VERSION_APPL(2, 0, 1)

static const unsigned8 analog_inputs_int_source=1;	// 32 interrupt sources max

static struct diginp {
	unsigned8 data;
	unsigned8 prev_data;
	unsigned8 polarity;
	unsigned8 int_any;
	unsigned8 int_l_h;
	unsigned8 int_h_l;
} dinp[DIGITAL_INP8_BLOCKS_MAX];

static unsigned8 int_enable_diginp;

static struct digout {
	unsigned8 data;
	unsigned8 data_out;
	unsigned8 output;
	unsigned8 polarity;
	unsigned8 errmode;
	unsigned8 errvalue;
	unsigned8 filter;
} dout[DIGITAL_OUT8_BLOCKS_MAX];

#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
static unsigned32 digout_data_raw;
#endif

static struct analogin {
	int32 data;
	int32 prev_data;
	unsigned8 int_trigger;
	int32 upper_limit;
	int32 lower_limit;
	unsigned32 delta;
	real32 data_float;
	real32 offset;
	real32 scaling;
} aninp[ANALOG_INPUT_CHANS_MAX];

static unsigned32 int_source_aninp;
static unsigned8 int_enable_aninp;

static struct analogout {
	int32 data;
	int32 data_out;
	unsigned8 error_mode;
	int32 error_value;
} anout[ANALOG_OUTPUT_CHANS_MAX];

static unsigned8 error_state;

static void process_digital_output(unsigned8 blk, unsigned8 *data)
{
	unsigned8 dtmp;
	struct digout *dp;
	
	dp = dout+blk;
	dtmp = dp->data;
	if (error_state == TRUE) {
		dtmp &= ~dp->errmode;
		dtmp |= dp->errvalue & dp->errmode;
	}
	dtmp ^= dp->polarity;
	dp->output &= ~dp->filter;
	dp->output |= dtmp & dp->filter;
	*data = dp->output;
}

static void aninp_interrupt(unsigned8 chan)
{
	unsigned32 dif;
	struct analogin *ap;
	
	ap = aninp+chan;
	if (ap->int_trigger & MASK_ANINP_INT_DELTA) {
		if (ap->data >= ap->prev_data) dif = ap->data - ap->prev_data;
		else dif = ap->prev_data - ap->data;
		if (dif < ap->delta) return;
	}
	ap->prev_data = ap->data;
	int_source_aninp |= (1 << chan);
	if (chan < 4) set_transmit_pdo((canindex)INDEX_TRNPDO_COMM_ANINP_2);
	else set_transmit_pdo((canindex)INDEX_TRNPDO_COMM_ANINP_3);
}

static void process_analog_output(unsigned8 chan, int32 *data)
{
	struct analogout *ap;
	
	ap = anout+chan;
	*data = ap->data;
	if (error_state == TRUE) {
		if (ap->error_mode != 0) *data = ap->error_value;	// 1.8.4
	}
}

static void digital_input_forced(unsigned8 blk, unsigned8 data)
{
	unsigned8 dtprev;
	struct diginp *dp;

	dp = dinp+blk;
	data ^= dp->polarity;
	if (data == dp->data) return;
	dtprev = dp->data;
	dp->data = data;
	if (int_enable_diginp == FALSE) return;
	if (((dp->data ^ dtprev) & dp->int_any) != 0) {
		set_transmit_pdo(INDEX_TRNPDO_COMM_DIGINP);
		return;
	}
	if (((dp->data & ~dtprev) & dp->int_l_h) != 0) {
		set_transmit_pdo(INDEX_TRNPDO_COMM_DIGINP);
		return;
	}
	if (((~dp->data & dtprev) & dp->int_h_l) != 0) {
		set_transmit_pdo(INDEX_TRNPDO_COMM_DIGINP);
		return;
	}
}

static void digital_input_normal(unsigned8 blk, unsigned8 data)
{
	struct diginp *dp;

	dp = dinp+blk;
	dp->data = data ^ dp->polarity;
	if (dp->data == dp->prev_data) return;
	if (int_enable_diginp == FALSE) return;
	if (((dp->data ^ dp->prev_data) & dp->int_any) != 0) {
		dp->prev_data = dp->data;
		set_transmit_pdo(INDEX_TRNPDO_COMM_DIGINP);
		return;
	}
	if (((dp->data & ~dp->prev_data) & dp->int_l_h) != 0) {
		dp->prev_data = dp->data;
		set_transmit_pdo(INDEX_TRNPDO_COMM_DIGINP);
		return;
	}
	if (((~dp->data & dp->prev_data) & dp->int_h_l) != 0) {
		dp->prev_data = dp->data;
		set_transmit_pdo(INDEX_TRNPDO_COMM_DIGINP);
		return;
	}
}

// Called from the application_monitor_routine()
void process_digital_input(unsigned8 blk, unsigned8 data)
{
	if (blk >= DIGITAL_INP8_BLOCKS_MAX) return;
	if (diginp_tpdo_forced) digital_input_forced(blk, data);
  else digital_input_normal(blk, data);
}

// Called from the application_monitor_routine()
void process_analog_input(unsigned8 chan, int32 data)
{
	struct analogin *ap;

	if (chan >= analog_inputs) return;
	ap = aninp+chan;
	ap->data = data;
	ap->data_float = ap->scaling * data + ap->offset;
	if (ap->data == ap->prev_data) return;
	if (int_enable_aninp == FALSE) return;
	if (ap->data >= ap->upper_limit) {
		if (ap->int_trigger & MASK_ANINP_INT_UP_LIMIT) aninp_interrupt(chan);
	} else if (ap->data < ap->lower_limit) {
		if (ap->int_trigger & MASK_ANINP_INT_LOW_LIMIT) aninp_interrupt(chan);
	}
}

// Called from the application_monitor_routine()
void write_digital_output(unsigned8 blk)
{
	unsigned8 data;
#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
	unsigned8 bit;
#endif

	if (device_state == OFF) return;
	if (blk >= DIGITAL_OUT8_BLOCKS_MAX) return;
	process_digital_output(blk, &data);
#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
	if (data == dout[blk].data_out) return;
	dout[blk].data_out = data;
	data = dout[0].data_out;
	for (bit = 0; bit < 8; bit++) {
		if (data & 1) print_appl("1  ");
		else print_appl("0  ");
		data >>= 1;
	}
	if (digital_outblocks > 1) {
		data = dout[1].data_out;
		for (bit = 0; bit < 8; bit++) {
			if (data & 1) print_appl("1  ");
			else print_appl("0  ");
			data >>= 1;
		}
	}
	print_appl("\r");
#elif (IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR)
  #if (IOREMOTE_PLATFORM == PLATFORM_STM32)
	if (blk == 0) {
		digout_data_raw &= 0xFF00;
		digout_data_raw |= data;
	} else if (blk == 1) {
		digout_data_raw &= 0x00FF;
		digout_data_raw |= (data << 8);
	} else return;
	digout_data_raw &= 0xFFFF;
	if ((DIO_GetOut32Bit() & 0xFFFF) != digout_data_raw) {
		DIO_SetOut32Bit(digout_data_raw);
	}
  #elif (IOREMOTE_PLATFORM == PLATFORM_MILANDR)
	Write_raw_data_to_ports((unsigned32)data);
  #endif
#endif
}

// Called from the application_monitor_routine()
void write_analog_output(unsigned8 chan)
{
	int32 data;
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
	unsigned16 draw;
#endif

	if (device_state == OFF) return;
	if (chan >= analog_outputs) return;
	process_analog_output(chan, &data);
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
	draw = (unsigned16)(data+32768);
	if (DAC_AppGetDataCode(chan) != draw) {
		DAC_AppSetDataCode(chan, draw);
	}
#elif (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
	if (data == anout[chan].data_out) return;
	anout[chan].data_out = data;
	for (chan = 0; chan < analog_outputs; chan++) {
		print_appl("%6i  ", (int16)anout[chan].data_out);
	}
	print_appl("\r");
#endif
}

#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
unsigned8 read_digital_output_0(void)
{
	return dout[0].output;
}
#endif

static void get_sub0_basic(struct object *obj)
{
	obj->size = sizeof(unsigned8);
	obj->deftype = CAN_DEFTYPE_UNSIGNED8;
	obj->access = CAN_MASK_ACCESS_RO;
}

static void get_sub0_diginp(struct object *obj)
{
	get_sub0_basic(obj);
	obj->pnt = (canbyte*)&digital_inblocks;
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

static void get_object_standev(struct object *obj)
{
	obj->size = CAN_ERRET_OBD_NOSUBIND;
	obj->deftype = 0; 
	obj->access = 0;
	obj->pnt = NULL;

	if (digital_inblocks != 0) {
		if (obj->index == INDEX_DIGINP_DATA) {
			if (obj->subind == 0) {
				get_sub0_diginp(obj);
			} else if (obj->subind <= digital_inblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RO | CAN_MASK_ACCESS_PDO;
				obj->pnt = (canbyte*)&dinp[obj->subind-1].data;
			}
			return;
		}
	}

	if (digital_outblocks != 0) {
		if (obj->index == INDEX_DIGOUT_DATA) {
			if (obj->subind == 0) {
				get_sub0_digout(obj);
			} else if (obj->subind <= digital_outblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW | CAN_MASK_ACCESS_PDO;
				obj->pnt = (canbyte*)&dout[obj->subind-1].data;
			}
			return;
		}
	}

	if (analog_inputs != 0) {
		if (obj->index == INDEX_ANINP_DATA_16) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(int16);
				obj->deftype = CAN_DEFTYPE_INTEGER16;
				obj->access = CAN_MASK_ACCESS_RO | CAN_MASK_ACCESS_PDO;
				obj->pnt = (canbyte*)&aninp[obj->subind-1].data;
			}
			return;
		}
		if (obj->index == INDEX_ANINP_DATA_FLOAT) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(real32);
				obj->deftype = CAN_DEFTYPE_REAL32;
				obj->access = CAN_MASK_ACCESS_RO | CAN_MASK_ACCESS_PDO;
				obj->pnt = (canbyte*)&aninp[obj->subind-1].data_float;
			}
			return;
		}
	}

	if (analog_outputs != 0) {
		if (obj->index == INDEX_ANOUT_DATA_16) {
			if (obj->subind == 0) {
				get_sub0_anout(obj);
			} else if (obj->subind <= analog_outputs) {
				obj->size = sizeof(int16);
				obj->deftype = CAN_DEFTYPE_INTEGER16;
			 	obj->access = CAN_MASK_ACCESS_RW | CAN_MASK_ACCESS_PDO;
				obj->pnt = (canbyte*)&anout[obj->subind-1].data;
			}
			return;
		}
	}

	if (digital_inblocks != 0) {
		if (obj->index == INDEX_DIGINP_INT_ENABLE) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_BOOLEAN;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&int_enable_diginp;
			}
			return;
		}
	}

	if (analog_inputs != 0) {
		if (obj->index == INDEX_ANINP_INT_ENABLE) {
			if (obj->subind == 0) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_BOOLEAN;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&int_enable_aninp;
			}
			return;
		}
	}

	if (digital_inblocks != 0) {
		if (obj->index == INDEX_DIGINP_POLARITY) {
			if (obj->subind == 0) {
				get_sub0_diginp(obj);
			} else if (obj->subind <= digital_inblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dinp[obj->subind-1].polarity;
			}
			return;
		}
		if (obj->index == INDEX_DIGINP_IMASK_ANY) {
			if (obj->subind == 0) {
				get_sub0_diginp(obj);
			} else if (obj->subind <= digital_inblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dinp[obj->subind-1].int_any;
			}
			return;
		}
		if (obj->index == INDEX_DIGINP_IMASK_L_H) {
			if (obj->subind == 0) {
				get_sub0_diginp(obj);
			} else if (obj->subind <= digital_inblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dinp[obj->subind-1].int_l_h;
			}
			return;
		}
		if (obj->index == INDEX_DIGINP_IMASK_H_L) {
			if (obj->subind == 0) {
				get_sub0_diginp(obj);
			} else if (obj->subind <= digital_inblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dinp[obj->subind-1].int_h_l;
			}
			return;
		}
	}

	if (digital_outblocks != 0) {
		if (obj->index == INDEX_DIGOUT_POLARITY) {
			if (obj->subind == 0) {
				get_sub0_digout(obj);
			} else if (obj->subind <= digital_outblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dout[obj->subind-1].polarity;
			}
			return;
		}
		if (obj->index == INDEX_DIGOUT_ERRMODE) {
			if (obj->subind == 0) {
				get_sub0_digout(obj);
			} else if (obj->subind <= digital_outblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dout[obj->subind-1].errmode;
			}
			return;
		}
		if (obj->index == INDEX_DIGOUT_ERRVALUE) {
			if (obj->subind == 0) {
				get_sub0_digout(obj);
			} else if (obj->subind <= digital_outblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dout[obj->subind-1].errvalue;
			}
			return;
		}
		if (obj->index == INDEX_DIGOUT_FILTER) {
			if (obj->subind == 0) {
				get_sub0_digout(obj);
			} else if (obj->subind <= digital_outblocks) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&dout[obj->subind-1].filter;
			}
			return;
		}
	}

	if (analog_inputs != 0) {
		if (obj->index == INDEX_ANINP_INT_TRIGGER) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&aninp[obj->subind-1].int_trigger;
			}
			return;
		}
		if (obj->index == INDEX_ANINP_INT_SOURCE) {
			if (obj->subind == 0) {
				get_sub0_basic(obj);
				obj->pnt = (canbyte*)&analog_inputs_int_source;
			} else if (obj->subind <= analog_inputs_int_source) {
				obj->size = sizeof(unsigned32);
				obj->deftype = CAN_DEFTYPE_UNSIGNED32;
				obj->access = CAN_MASK_ACCESS_RO;
				obj->pnt = (canbyte*)&int_source_aninp;
			}
			return;
		}
		if (obj->index == INDEX_ANINP_UPPER) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(int32);
				obj->deftype = CAN_DEFTYPE_INTEGER32;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&aninp[obj->subind-1].upper_limit;
			}
			return;
		}
		if (obj->index == INDEX_ANINP_LOWER) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(int32);
				obj->deftype = CAN_DEFTYPE_INTEGER32;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&aninp[obj->subind-1].lower_limit;
			}
			return;
		}
		if (obj->index == INDEX_ANINP_DELTA_UNS) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(unsigned32);
				obj->deftype = CAN_DEFTYPE_UNSIGNED32;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&aninp[obj->subind-1].delta;
			}
			return;
		}
		if (obj->index == INDEX_ANINP_OFFSET) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(real32);
				obj->deftype = CAN_DEFTYPE_REAL32;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&aninp[obj->subind-1].offset;
			}
			return;
		}
		if (obj->index == INDEX_ANINP_SCALING) {
			if (obj->subind == 0) {
				get_sub0_aninp(obj);
			} else if (obj->subind <= analog_inputs) {
				obj->size = sizeof(real32);
				obj->deftype = CAN_DEFTYPE_REAL32;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&aninp[obj->subind-1].scaling;
			}
			return;
		}
	}

	if (analog_outputs != 0) {
		if (obj->index == INDEX_ANOUT_ERRMODE) {
				if (obj->subind == 0) {
				get_sub0_anout(obj);
			} else if (obj->subind <= analog_outputs) {
				obj->size = sizeof(unsigned8);
				obj->deftype = CAN_DEFTYPE_UNSIGNED8;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&anout[obj->subind-1].error_mode;
			}
			return;
		}
		if (obj->index == INDEX_ANOUT_ERRVALUE) {
			if (obj->subind == 0) {
				get_sub0_anout(obj);
			} else if (obj->subind <= analog_outputs) {
				obj->size = sizeof(int32);
				obj->deftype = CAN_DEFTYPE_INTEGER32;
				obj->access = CAN_MASK_ACCESS_RW;
				obj->pnt = (canbyte*)&anout[obj->subind-1].error_value;
			}
			return;
		}
	}

	obj->size = CAN_ERRET_OBD_NOOBJECT;
}

int32 server_get_standev_objsize(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	return obj.size;
}

int16 server_see_standev_access(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	return obj.access;
}

int16 server_get_standev_objtype(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	return obj.deftype;
}

// NO async data update
int16 server_read_standev_objdict(canindex index, cansubind subind, canbyte *data)
{
	int32 size, cnt;
	canbyte *bpnt;
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	if ((obj.access & CAN_MASK_ACCESS_RO) == 0) return CAN_ERRET_OBD_WRITEONLY;
	if (obj.pnt == NULL) return CAN_ERRET_NULL_POINTER;		// Extra-safety check
	size = obj.size;
	bpnt = obj.pnt;
	OBJECT_DICTIONARY_TO_CANOPEN
	if (index == INDEX_ANINP_INT_SOURCE) int_source_aninp = 0;
	return CAN_RETOK;
}

// NO async usage of the multi-byte data
int16 server_write_standev_objdict(canindex index, cansubind subind, canbyte *data)
{
	int32 size, cnt;
	canbyte *bpnt;
	struct object obj;
	union numbers num;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	if ((obj.access & CAN_MASK_ACCESS_WO) == 0) return CAN_ERRET_OBD_READONLY;
	if (error_state == TRUE) {
		if (index == INDEX_DIGOUT_DATA || index == INDEX_DIGOUT_POLARITY || index == INDEX_DIGOUT_FILTER ||
			index == INDEX_DIGOUT_ERRMODE || index == INDEX_DIGOUT_ERRVALUE ||
			index == INDEX_ANOUT_DATA_16 || index == INDEX_ANOUT_DATA_32 ||
			index == INDEX_ANOUT_ERRMODE || index == INDEX_ANOUT_ERRVALUE) {
			if (get_dev_node_state() == CAN_NODE_STATE_OPERATIONAL) produce_emcy_default(CAN_EMCY_ERROR_STATE);
			return CAN_ERRET_OBD_DEVSTATE;
		}
	}
	size = obj.size;
	bpnt = (canbyte*)&num;
	num.init = 0;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (index == INDEX_ANINP_INT_TRIGGER) {
		if (num.uns8 > 0x1F) return CAN_ERRET_OBD_VALRANGE;
	} else if (index == INDEX_ANOUT_ERRMODE) {
		if (num.uns8 > 1) return CAN_ERRET_OBD_VALRANGE;	// 1.8.4
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
	return CAN_RETOK;
}

void enter_error_state(void)
{
	if (error_state == FALSE) {
		error_state = TRUE;
		produce_sr_gfc();
	}
}

void exit_error_state(void)
{
	if (error_state == TRUE) {
		error_state = FALSE;
		clear_error_register(CAN_MASK_ANY_ERROR);
	}
	if (digital_inblocks != 0) {
		if (read_int_enable_counter() == FALSE) produce_emcy_default(CAN_EMCY_INT_DISABLED);
	}	
	if (analog_inputs != 0) {
		if (int_enable_aninp == FALSE) produce_emcy_default(CAN_EMCY_INT_DISABLED);
	}	
}

void slave_init_standev_application(void)
{
	unsigned8 chan;

	for (chan = 0; chan < DIGITAL_INP8_BLOCKS_MAX; chan++) {
		dinp[chan].data = 0;
		dinp[chan].prev_data = 0;
		dinp[chan].polarity = 0;
		dinp[chan].int_any = 0xFF;
		dinp[chan].int_l_h = 0;
		dinp[chan].int_h_l = 0;
	}

	for (chan = 0; chan < DIGITAL_OUT8_BLOCKS_MAX; chan++) {
		dout[chan].data = 0;
		dout[chan].data_out = 0xFF;
		dout[chan].output = 0;
		dout[chan].polarity = 0;
		dout[chan].errmode = 0xFF;
		dout[chan].errvalue = 0;
		dout[chan].filter = 0xFF;
	}
#if ((IOREMOTE_APPLICATION_MODE == APPLICATION_REGULAR) && (IOREMOTE_PLATFORM == PLATFORM_STM32))
	digout_data_raw = 0;
	DIO_RstStatusOut32Bit(0xFFFFFFFF);
#endif

	for (chan = 0; chan < ANALOG_INPUT_CHANS_MAX; chan++) {
		aninp[chan].data = 0;
		aninp[chan].prev_data = 0;
		aninp[chan].int_trigger = 0x7;
		aninp[chan].upper_limit = 0;
		aninp[chan].lower_limit = 0;
		aninp[chan].delta = 0;
		aninp[chan].data_float = 0.0;
		aninp[chan].offset = 0.0;
		aninp[chan].scaling = 1.0;
	}
	int_source_aninp = 0;

	for (chan = 0; chan < ANALOG_OUTPUT_CHANS_MAX; chan++) {
		anout[chan].data = 0;
		anout[chan].data_out = 0xFFFF;
		anout[chan].error_mode = 1;
		anout[chan].error_value = 0;
	}

	error_state = FALSE;
}

static void init_srdo_communication(void)
{
	unsigned32 dev, map;

	if (get_dev_nodeid() > 32) return;

	server_write_obd_u32(INDEX_SRDO_COMM_1, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_INVALID);
	server_write_obd_u32(INDEX_SRDO_COMM_1, SUBIND_SRDO_COMM_SCT, SRDO_SCT_TRANSMIT);
	server_write_obd_u32(INDEX_SRDO_MAP_1, 0, 0);
	server_write_obd_u32(INDEX_SRDO_COMM_2, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_INVALID);
	server_write_obd_u32(INDEX_SRDO_COMM_2, SUBIND_SRDO_COMM_SCT, SRDO_SCT_RECEIVE);
	server_write_obd_u32(INDEX_SRDO_MAP_2, 0, 0);

	if (digital_inblocks != 0) {
		server_write_obd_u32(INDEX_SRDO_COMM_DIGINP, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_TRANSMIT);
		server_write_obd_u32(INDEX_SRDO_COMM_DIGINP, SUBIND_SRDO_COMM_SCT, SRDO_SCT_TRANSMIT);
		for (dev = 1; dev <= DIGITAL_INP8_BLOCKS_MAX; dev++) {
			map = 0x60000008 | (dev << 8);
			server_write_obd_u32(INDEX_SRDO_MAP_DIGINP, (cansubind)(2*dev-1), map);
		}
		server_write_obd_u32(INDEX_SRDO_MAP_DIGINP, 0, 2*digital_inblocks);
	}
	if (digital_outblocks != 0) {
		server_write_obd_u32(INDEX_SRDO_COMM_DIGOUT, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_RECEIVE);
		server_write_obd_u32(INDEX_SRDO_COMM_DIGOUT, SUBIND_SRDO_COMM_SCT, SRDO_SCT_RECEIVE);
		for (dev = 1; dev <= DIGITAL_OUT8_BLOCKS_MAX; dev++) {
			map = 0x62000008 | (dev << 8);
			server_write_obd_u32(INDEX_SRDO_MAP_DIGOUT, (cansubind)(2*dev-1), map);
		}
		server_write_obd_u32(INDEX_SRDO_MAP_DIGOUT, 0, 2*digital_outblocks);
	}
	if (digital_inblocks != 0 || digital_outblocks != 0) return;	// DIO only

	if (analog_inputs != 0 && analog_outputs != 0) {
		if (analog_inputs > 4 || analog_outputs > 4) return;	// Invalid configuration
		server_write_obd_u32(INDEX_SRDO_COMM_ANINP_1, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_TRANSMIT);
		server_write_obd_u32(INDEX_SRDO_COMM_ANINP_1, SUBIND_SRDO_COMM_SCT, SRDO_SCT_TRANSMIT);
		server_write_obd_u32(INDEX_SRDO_COMM_ANOUT_2, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_RECEIVE);
		server_write_obd_u32(INDEX_SRDO_COMM_ANOUT_2, SUBIND_SRDO_COMM_SCT, SRDO_SCT_RECEIVE);
		for (dev = 1; dev <= 4; dev++) {		// Mapped For 4 inputs and 4 outputs
			map = 0x64010010 | (dev << 8);
			server_write_obd_u32(INDEX_SRDO_MAP_ANINP_1, (cansubind)(2*dev-1), map);
			map = 0x64110010 | (dev << 8);
			server_write_obd_u32(INDEX_SRDO_MAP_ANOUT_2, (cansubind)(2*dev-1), map);
		}
		server_write_obd_u32(INDEX_SRDO_MAP_ANINP_1, 0, 2*analog_inputs);
		server_write_obd_u32(INDEX_SRDO_MAP_ANOUT_2, 0, 2*analog_outputs);
		return;
	}

	if (analog_inputs != 0) {
		server_write_obd_u32(INDEX_SRDO_COMM_ANINP_1, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_TRANSMIT);
		server_write_obd_u32(INDEX_SRDO_COMM_ANINP_1, SUBIND_SRDO_COMM_SCT, SRDO_SCT_TRANSMIT);
		if (analog_inputs > 4) {
			server_write_obd_u32(INDEX_SRDO_COMM_ANINP_2, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_TRANSMIT);
			server_write_obd_u32(INDEX_SRDO_COMM_ANINP_2, SUBIND_SRDO_COMM_SCT, SRDO_SCT_TRANSMIT);
		}
		for (dev = 1; dev <= 4; dev++) {		// Mapped For 8 inputs
			map = 0x64010010 | (dev << 8);
			server_write_obd_u32(INDEX_SRDO_MAP_ANINP_1, (cansubind)(2*dev-1), map);
			map = 0x64010010 | ((dev+4) << 8);
			server_write_obd_u32(INDEX_SRDO_MAP_ANINP_2, (cansubind)(2*dev-1), map);
		}
		if (analog_inputs <= 4) {
			server_write_obd_u32(INDEX_SRDO_MAP_ANINP_1, 0, 2*analog_inputs);
		} else if (analog_inputs <= 8) {
			server_write_obd_u32(INDEX_SRDO_MAP_ANINP_1, 0, 2*4);
			server_write_obd_u32(INDEX_SRDO_MAP_ANINP_2, 0, 2*(analog_inputs-4));
		}
		return;
	}			

	if (analog_outputs != 0) {
		server_write_obd_u32(INDEX_SRDO_COMM_ANOUT_1, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_RECEIVE);
		server_write_obd_u32(INDEX_SRDO_COMM_ANOUT_1, SUBIND_SRDO_COMM_SCT, SRDO_SCT_RECEIVE);
		if (analog_outputs > 4) {
			server_write_obd_u32(INDEX_SRDO_COMM_ANOUT_2, SUBIND_SRDO_COMM_DIRECTION, SRDO_DIR_RECEIVE);
			server_write_obd_u32(INDEX_SRDO_COMM_ANOUT_2, SUBIND_SRDO_COMM_SCT, SRDO_SCT_RECEIVE);
		}
		for (dev = 1; dev <= 4; dev++) {		// Mapped For 8 outputs
			map = 0x64110010 | (dev << 8);
			server_write_obd_u32(INDEX_SRDO_MAP_ANOUT_1, (cansubind)(2*dev-1), map);
			map = 0x64110010 | ((dev+4) << 8);
			server_write_obd_u32(INDEX_SRDO_MAP_ANOUT_2, (cansubind)(2*dev-1), map);
		}
		if (analog_outputs <= 4) {
			server_write_obd_u32(INDEX_SRDO_MAP_ANOUT_1, 0, 2*analog_outputs);
		} else if (analog_outputs <= 8) {
			server_write_obd_u32(INDEX_SRDO_MAP_ANOUT_1, 0, 2*4);
			server_write_obd_u32(INDEX_SRDO_MAP_ANOUT_2, 0, 2*(analog_outputs-4));
		}
		return;
	}
}

void slave_init_standev_communication(void)
{
	unsigned32 dev, map;

	init_srdo_communication();

	if (digital_inblocks != 0) {
		for (dev = 1; dev <= DIGITAL_INP8_BLOCKS_MAX; dev++) {
			map = 0x60000008 | (dev << 8);
			server_write_obd_u32(INDEX_TRNPDO_MAP_DIGINP, (cansubind)dev, map);
		}
		server_write_obd_u32(INDEX_TRNPDO_MAP_DIGINP, 0, digital_inblocks);
		set_pdo_state(INDEX_TRNPDO_COMM_DIGINP, VALID);
	}

	if (digital_outblocks != 0) {
		for (dev = 1; dev <= DIGITAL_OUT8_BLOCKS_MAX; dev++) {
			map = 0x62000008 | (dev << 8);
			server_write_obd_u32(INDEX_RCVPDO_MAP_DIGOUT, (cansubind)dev, map);
		}
		server_write_obd_u32(INDEX_RCVPDO_MAP_DIGOUT, 0, digital_outblocks);
		set_pdo_state(INDEX_RCVPDO_COMM_DIGOUT, VALID);
	}

	if (analog_inputs != 0) {
		for (dev = 1; dev <= 4; dev++) {
			map = 0x64010010 | (dev << 8);
			server_write_obd_u32(INDEX_TRNPDO_MAP_ANINP_2, (cansubind)dev, map);
			map = 0x64010010 | ((dev+4) << 8);
			server_write_obd_u32(INDEX_TRNPDO_MAP_ANINP_3, (cansubind)dev, map);
		}
		if (analog_inputs <= 4) {
			server_write_obd_u32(INDEX_TRNPDO_MAP_ANINP_2, 0, analog_inputs);
			set_pdo_state(INDEX_TRNPDO_COMM_ANINP_2, VALID);
		} else if (analog_inputs <= 8) {
			server_write_obd_u32(INDEX_TRNPDO_MAP_ANINP_2, 0, 4);
			set_pdo_state(INDEX_TRNPDO_COMM_ANINP_2, VALID);
			server_write_obd_u32(INDEX_TRNPDO_MAP_ANINP_3, 0, analog_inputs-4);
			set_pdo_state(INDEX_TRNPDO_COMM_ANINP_3, VALID);
		}
	}

	if (analog_outputs != 0) {
		for (dev = 1; dev <= 4; dev++) {
			map = 0x64110010 | (dev << 8);
			server_write_obd_u32(INDEX_RCVPDO_MAP_ANOUT_2, (cansubind)dev, map);
			map = 0x64110010 | ((dev+4) << 8);
			server_write_obd_u32(INDEX_RCVPDO_MAP_ANOUT_3, (cansubind)dev, map);
		}
		if (analog_outputs <= 4) {
			server_write_obd_u32(INDEX_RCVPDO_MAP_ANOUT_2, 0, analog_outputs);
			set_pdo_state(INDEX_RCVPDO_COMM_ANOUT_2, VALID);
		} else if (analog_outputs <= 8) {
			server_write_obd_u32(INDEX_RCVPDO_MAP_ANOUT_2, 0, 4);
			set_pdo_state(INDEX_RCVPDO_COMM_ANOUT_2, VALID);
			server_write_obd_u32(INDEX_RCVPDO_MAP_ANOUT_3, 0, analog_outputs-4);
			set_pdo_state(INDEX_RCVPDO_COMM_ANOUT_3, VALID);
		}
	}

	if (digital_inblocks != 0) int_enable_diginp = TRUE;
	else int_enable_diginp = FALSE;

	int_enable_aninp = FALSE;
}

#endif
