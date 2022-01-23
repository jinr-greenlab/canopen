#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 1)

#define NETWORKS_SUBIND_MASK_TOTAL		1
#define NETWORKS_SUBIND_MASK_FREE		2
#define NETWORKS_SUBIND_MASK_WORK		3
#define NETWORKS_SUBIND_CHANNEL			4


int16 get_can_networks_bytes_objsize(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_NETWORKS_CONFIG) {
		if (subind <= 4) return sizeof(unsigned8);
		return CAN_ERRET_OBD_NOSUBIND;
	}
	return CAN_ERRET_OBD_NOOBJECT;
}

int16 see_can_networks_access(canindex index, cansubind subind)
{
	int16 size;

	size = get_can_networks_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_NETWORKS_CONFIG) return CAN_MASK_ACCESS_RO;
	return CAN_MASK_ACCESS_RW;
}

int16 get_can_networks_objtype(canindex index, cansubind subind)
{
	int16 size;

	size = get_can_networks_bytes_objsize(index, subind);
	if (size <= 0) return size;
	if (index == CAN_INDEX_NETWORKS_CONFIG) return CAN_DEFTYPE_UNSIGNED8;
	return CAN_DEFTYPE_UNSIGNED32;
}

int16 read_can_networks_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;
	unsigned32 buf;

	size = get_can_networks_bytes_objsize(index, subind);
	if (size <= 0) return size;
	bpnt = (canbyte*)&buf; buf = 0;
	if (index == CAN_INDEX_NETWORKS_CONFIG) {
		if (subind == 0) buf = 4;
		else if (subind == NETWORKS_SUBIND_MASK_TOTAL) buf = CAN_MASK_NETWORKS;
		else if (subind == NETWORKS_SUBIND_MASK_FREE) buf = get_netmask_free();
		else if (subind == NETWORKS_SUBIND_MASK_WORK) buf = netmask_work;
		else if (subind == NETWORKS_SUBIND_CHANNEL) buf = can_netchan;
	}
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

int16 write_can_networks_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size;

	size = get_can_networks_bytes_objsize(index, subind);
	if (size <= 0) return size;
	return CAN_ERRET_OBD_READONLY;
}

#endif
