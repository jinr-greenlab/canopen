#include <can_header.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 0)
//  CHECK_VERSION(2, 1, 1)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 0)

int16 get_deftype_objsize(canindex index, cansubind subind, int16 unit)
{
	int16 size;

	if (index < CAN_DEFTYPE_BOOLEAN || index > CAN_DEFTYPE_UNSIGNED32) return CAN_ERRET_OBD_NOOBJECT;
	if (subind != 0)  return CAN_ERRET_OBD_NOSUBIND;
	size = CAN_SIZEOF_BOOLEAN;
	if (index == CAN_DEFTYPE_INTEGER8 || index == CAN_DEFTYPE_UNSIGNED8) size = sizeof(unsigned8);
	else if (index == CAN_DEFTYPE_INTEGER16 || index == CAN_DEFTYPE_UNSIGNED16) size = sizeof(unsigned16);
	else if (index == CAN_DEFTYPE_INTEGER32 || index == CAN_DEFTYPE_UNSIGNED32) size = sizeof(unsigned32);
	if (unit == BITS && index != CAN_DEFTYPE_BOOLEAN) size *= CAN_SIZEOF_FACTOR;
	return size;
}

int16 see_deftype_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_deftype_objsize(index, subind, BYTES);
	if (size <= 0) return size;
	return CAN_MASK_ACCESS_PDO | CAN_MASK_ACCESS_RW;
}

int16 get_deftype_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_deftype_objsize(index, subind, BYTES);
	if (size <= 0) return size;
	return index;
}

int16 read_deftype_objdict(canindex index, cansubind subind, canbyte *data)		// 2.3.1 some changes
{
	int16 size, cnt;
	unsigned32 buf;
	canbyte *bpnt;

	size = get_deftype_objsize(index, subind, BYTES);
	if (size <= 0) return size;
	bpnt = (canbyte*)&buf; buf = 0;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_deftype_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size;

	size = get_deftype_objsize(index, subind, BYTES);
	if (size <= 0) return size;
	return CAN_RETOK;
}

#endif
