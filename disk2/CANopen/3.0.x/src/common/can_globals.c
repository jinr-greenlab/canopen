#include <can_header.h>

unsigned8		can_netchan;	// CAN driver channel; 3.0.0 renamed
unsigned8		bitrate_index; 	// Bit rate index

cannode			node_id;		// The slave device node ID
canbyte			node_state; 	// CAN node state; one of the CAN_NODE_STATE_...

#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE
unsigned8		lss_state;	 	// LSS protocol state (off, waiting, configuration)
#endif
