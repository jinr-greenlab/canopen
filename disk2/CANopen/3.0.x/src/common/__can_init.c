#include <can_header.h>
#include <__can_node_id.h>

#if CHECK_VERSION(3, 0, 0)
//  CHECK_VERSION(2, 3, 0)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 3)
//  CHECK_VERSION(2, 1, 0)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 0)

#if CAN_APPLICATION_MODE == MASTER

cannode get_node_id(void)
{
	#if CAN_SLAVE_DEVICE_CLASS == CAN_DEVICE_TEST
	return CAN_NODEID_SLAVE;
	#else
	return 0;
	#endif
}

unsigned8 get_bit_rate_index(void)
{
	return CAN_BITRATE_INDEX;
}

#elif CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST

cannode get_node_id(void)
{
#if CAN_OBJECT_RE_STORE == TRUE || CAN_OBJECT_LSS == TRUE
	int16 nf;
    
	nf = get_flash_nodeid();
	if (nf < 0) return CAN_NODEID_SLAVE;
	if (check_node_id((cannode)nf) == CAN_RETOK) return (cannode)nf;
#endif
	return CAN_NODEID_SLAVE;
}

unsigned8 get_bit_rate_index(void)
{
#if CAN_OBJECT_RE_STORE == TRUE || CAN_OBJECT_LSS == TRUE
	int16 br;
    
	br = get_flash_bitrate_index();
	if (br < 0) return CAN_BITRATE_INDEX;
	if (check_bitrate_index((unsigned8)br) == CAN_RETOK) return (unsigned8)br;
#endif
	return CAN_BITRATE_INDEX;
}

unsigned32 get_serial_number(void)
{
	return CAN_SERIAL_NUMBER;
}

#endif

#endif
