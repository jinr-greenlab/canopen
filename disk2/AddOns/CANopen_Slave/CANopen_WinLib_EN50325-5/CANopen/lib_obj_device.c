#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 0)

int16 get_dev_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_DEVICE_TYPE || index == CAN_INDEX_MAN_STATUS) {
		if (subind == 0) return sizeof(unsigned32);
		return CAN_ERRET_OBD_NOSUBIND;
	} else if (index == CAN_INDEX_IDENTITY) {
		if (subind == 0) return sizeof(unsigned8);
		if (subind <= 4) return sizeof(unsigned32);
		return CAN_ERRET_OBD_NOSUBIND;
	} else if (index == CAN_INDEX_MAN_DEV_NAME || index == CAN_INDEX_MAN_HARD_VER ||
		index == CAN_INDEX_MAN_SOFT_VER) {
		if (subind == 0) return CAN_LEN_VISIBLE_STRING;
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_dev_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_dev_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_MAN_STATUS) return CAN_MASK_ACCESS_PDO | CAN_MASK_ACCESS_RO;
	return CAN_MASK_ACCESS_RO;
}

int16 get_dev_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_dev_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_DEVICE_TYPE || index == CAN_INDEX_MAN_STATUS) {
		return CAN_DEFTYPE_UNSIGNED32;
	} else if (index == CAN_INDEX_IDENTITY) {
		if (subind == 0) return CAN_DEFTYPE_UNSIGNED8;
		return CAN_DEFTYPE_UNSIGNED32;
	}
	return CAN_DEFTYPE_VISIBLE_STRING;
}

int16 read_dev_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	unsigned32 buf;
	canbyte *bpnt;

	size = get_dev_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_MAN_DEV_NAME || index == CAN_INDEX_MAN_HARD_VER ||
		index == CAN_INDEX_MAN_SOFT_VER) {
		for (cnt = 0; cnt < size; cnt++) {*data = 0; data++;}
		read_dev_string_object(index, subind, data-size);
		return CAN_RETOK;
	}
	bpnt = (canbyte*)&buf;
	buf = read_dev_type_object(index, subind);
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_dev_objdict(canindex index, cansubind subind, canbyte *data)	// 2.2.1 some changes
{
	int16 size;

	size = get_dev_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_ERRET_OBD_READONLY;
}

#endif
