#include <DS401_header.h>

#if CHECK_VERSION_APPL(2, 1, 1)
//  CHECK_VERSION_APPL(2, 0, 1)
//  CHECK_VERSION_APPL(1, 2, 0)


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


static const unsigned8 subs_octet_string=2;

static int32 read_octet_size, write_octet_size;
static unsigned8 octet[CAN_LEN_OCTET_STRING];

static void get_sub0_basic(struct object *obj)
{
	obj->size = sizeof(unsigned8);
	obj->deftype = CAN_DEFTYPE_UNSIGNED8;
	obj->access = CAN_MASK_ACCESS_RO;
}

static void get_object_manspec(struct object *obj)
{
	obj->size = CAN_ERRET_OBD_NOSUBIND;
	obj->deftype = 0; 
	obj->access = 0;
	obj->pnt = NULL;
      
	if (obj->index == INDEX_OCTET_STRING) {
		if (obj->subind == 0) {
			get_sub0_basic(obj);
			obj->pnt = (canbyte*)&subs_octet_string;
		} else if (obj->subind == 1) {
			obj->size = read_octet_size;
			obj->deftype = CAN_DEFTYPE_OCTET_STRING;
			obj->access = CAN_MASK_ACCESS_RO;
			obj->pnt = (canbyte*)&octet;
		} else if (obj->subind == 2) {
			obj->size = 0;
			obj->deftype = CAN_DEFTYPE_OCTET_STRING;
			obj->access = CAN_MASK_ACCESS_WO;
			obj->pnt = (canbyte*)&octet;
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
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	if (obj.size < 0) return obj.size;
	if (obj.size > 0) return CAN_ERRET_OBD_DATAMISM;
	if (size <= 0) return CAN_ERRET_OBD_DATALOW;
	if (size > CAN_LEN_OCTET_STRING) return CAN_ERRET_OBD_DATAHIGH;
	if (obj.index == INDEX_OCTET_STRING && obj.subind == 2) {
		write_octet_size = size;
		return size;
	}
	return CAN_ERRET_OBD_DATAMISM;
}

int16 server_see_manspec_access(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	if (obj.index == INDEX_OCTET_STRING) {
		if (obj.size < 0) return (int16)obj.size;
	} else {
		if (obj.size <= 0) return (int16)obj.size;
	}
	return obj.access;
}

int16 server_get_manspec_objtype(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	if (obj.index == INDEX_OCTET_STRING) {
		if (obj.size < 0) return (int16)obj.size;
	} else {
		if (obj.size <= 0) return (int16)obj.size;
	}
	return obj.deftype;
}

int16 server_read_manspec_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	if (obj.size < 0) return (int16)obj.size;
	if ((obj.access & CAN_MASK_ACCESS_RO) == 0) return CAN_ERRET_OBD_WRITEONLY;
	if (obj.size == 0) return CAN_ERRET_OBD_NODATA;
	size = obj.size;
	bpnt = obj.pnt;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 server_write_manspec_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;
	struct object obj;
        
	obj.index = index;
	obj.subind = subind;
	get_object_manspec(&obj);
	if (obj.index == INDEX_OCTET_STRING && obj.subind == 2) obj.size = write_octet_size;
	if (obj.size <= 0) return (int16)obj.size;
	if ((obj.access & CAN_MASK_ACCESS_WO) == 0) return CAN_ERRET_OBD_READONLY;
	size = obj.size;
	bpnt = obj.pnt;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	if (index == INDEX_OCTET_STRING) {
		read_octet_size = write_octet_size;
		write_octet_size = 0;
	}
	return CAN_RETOK;
}

void process_logical_counter(unsigned8 lcc)
{
}

void write_digital_counter(unsigned8 chan, unsigned32 data)
{
}

void application_manspec_timer(void)
{
}

void control_digital_outputs(void)
{
}

void control_analog_outputs(void)
{
}

unsigned8 read_int_enable_counter(void)
{
	return 0;
}

void slave_init_manspec_application(void)
{
	read_octet_size = 0;
	write_octet_size = 0;
}

void slave_init_manspec_communication(void)
{
}

#endif
