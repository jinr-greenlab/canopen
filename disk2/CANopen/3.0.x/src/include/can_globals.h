extern unsigned8		can_netchan;	// CAN driver channel; 3.0.0 renamed
extern unsigned8		bitrate_index; 	// Bit rate index

extern cannode			node_id;		// The slave device node ID
extern canbyte			node_state; 	// CAN node state; one of the CAN_NODE_STATE_...

#if CAN_PROTOCOL_LSS == TRUE && CAN_APPLICATION_MODE == SLAVE
extern unsigned8		lss_state;	 	// LSS protocol state (off, waiting, configuration)
#endif
