#include <lib_header.h>

unsigned8		netmask_work;				// Working CAN networks mask
unsigned8		can_netchan;				// CAN driver channel

cannode			node_id;					// The slave device node ID
unsigned8		node_state;					// CAN node state; one of the CAN_NODE_STATE_...

struct store stc_1[CAN_NOF_LOAD_COMM_1];	// Re-store communication 1 configuration
struct store stc_2[CAN_NOF_LOAD_COMM_2];	// Re-store communication 2 configuration
struct store stap[CAN_NOF_LOAD_APPL];		// Re-store application configuration

