#include <can_header.h>

#if CHECK_VERSION(3, 0, 1)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 3)
//  CHECK_VERSION(2, 0, 2)
//  CHECK_VERSION(1, 7, 2)

void consume_sync(unsigned8 sc)
{
}

void no_sync_event(void)
{
	set_led_red_triple_flash();
}

#if CAN_OBJECT_TIME == TRUE
void consume_time(canframe *cf)
{
	struct time_of_day ts;

	ts.ms = canframe_to_u32(&cf->data[0]);
	ts.ms &= CAN_MASK_TIME_MS;
	ts.days = canframe_to_u16(&cf->data[4]);

//	ts.ms		Time in milliseconds after midnight of the TIME_OF_DAY structure
//	ts.days		Number of days since January 1, 1984 of the TIME_OF_DAY structure

}
#endif

void consume_controller_error(canev ev)
{
	#if CAN_NMT_MODE == SLAVE && CAN_APPLICATION_MODE != TEST
	if (ev == CIEV_BOFF) {
		process_serious_error(CAN_SUBIND_ERRBEH_COMM);
		set_led_red_on();
	} else if (ev == CIEV_HOVR) {
		#if CAN_OBJECT_EMCY == TRUE
		produce_emcy_default(CAN_EMCY_HOVR);
		#endif
	} else if (ev == CIEV_SOVR) {
		#if CAN_OBJECT_EMCY == TRUE
		produce_emcy_default(CAN_EMCY_SOVR); 
		#endif
	} else if (ev == CIEV_EWL) {
		#if CAN_OBJECT_EMCY == TRUE
		produce_emcy_default(CAN_EMCY_EWL);
		#endif
		set_led_red_single_flash();
	} else if (ev == CIEV_WTOUT) {
		#if CAN_OBJECT_EMCY == TRUE
		produce_emcy_default(CAN_EMCY_WTOUT); 
		#endif
	}
	#endif
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	printf("CAN controller error %5i\n ", ev);
	#endif
}

#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST

#if CAN_OBJECT_EMCY == TRUE
void master_emcy(unsigned16 errorcode)
{
	printf("MASTER EMERGENCY: 0x%04x\n", errorcode);
}

void consume_emcy(canframe *cf)
{
	unsigned16 cnt;

	printf("EMERGENCY received from node %4li: ", cf->id-CAN_CANID_EMCY_BASE);
	for (cnt = 0; cnt < 8; cnt++) printf(" 0x%02x", cf->data[cnt]);
	printf("\n");
}
#endif

void pdo_activated_master(cannode node, canindex index, cansubind subind)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) return;	// Dummy entries
}

void can_client_state(struct sdocltappl *ca)
{
	if (ca->ss.state == CAN_TRANSTATE_OK) return;
	printf("Client transaction state code (see CAN_TRANSTATE_...): %4i\n", ca->ss.state);
	if (ca->ss.state == CAN_TRANSTATE_SDO_SRVABORT) {
		printf("Abort code 0x%08x", ca->ss.abortcode);
		printf(" RECEIVED for SDO communication index 0x%04x\n", ca->si.sdoind);
		printf("Object dictionary index 0x%04x", ca->si.index);
		printf(" and subindex 0x%02x\n", ca->si.subind);
	}
}

#endif

#if CAN_NMT_MODE == MASTER || CAN_APPLICATION_MODE == TEST

void heartbeat_event(cannode node)
{
	set_led_red_double_flash();
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	printf("Heartbeat event from node %3i\n", node);
	#endif
}

void heartbeat_resolved(cannode node)
{
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	printf("Heartbeat from node %3i resolved\n", node);
	#endif
	// It's a bit embarassing to process
	// dynamic, periodic and irreversible error
	// as a static one, requred by DS301...
}

void node_guarding_event(cannode node)
{
	set_led_red_double_flash();
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	printf("Node guarding event, node %3i\n", node);
	#endif
}

void node_guarding_resolved(cannode node)
{
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	printf("Node guarding from node %3i resolved\n", node);
	#endif
	// It's a bit embarassing to process
	// dynamic, periodic and irreversible error
	// as a static one, requred by DS301...
}

void bootup_event(cannode node)
{
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	printf("Bootup event from node %-3i\n", node);
	#endif
}

void node_state_event(cannode node, canbyte state)
{
	#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST

	return;

	printf("Node %-1i state: ", node);
	if (state == CAN_NODE_STATE_STOPPED) printf("Stopped");
	else if (state == CAN_NODE_STATE_OPERATIONAL) printf("Operational");
	else if (state == CAN_NODE_STATE_PRE_OPERATIONAL) printf("Pre-operational");
	else printf("%-1i", state);
	printf("\n");
	#endif
}

#endif

#if CAN_NMT_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
void life_guarding_event(void)
{
	#if CAN_OBJECT_EMCY == TRUE
	produce_emcy_default(CAN_EMCY_HEARTBEAT);
	#endif
	set_led_red_double_flash();
}

void life_guarding_resolved(void)
{
	// It's a bit embarassing to process
	// dynamic, periodic and irreversible error
	// as a static one, requred by DS301...
}
#endif

#if CAN_APPLICATION_MODE == SLAVE || CAN_APPLICATION_MODE == TEST
void pdo_activated_slave(canindex index, cansubind subind)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) return;	// Dummy entries
}
#endif

void no_pdo_event(canindex index)		// 2.2.1
{
	#if CAN_OBJECT_EMCY == TRUE
	produce_emcy_default(CAN_EMCY_RPDO_TIMEOUT);
	#endif
	set_led_red_quadruple_flash();
}

void can_timer_overlap(void)
{
	#if CAN_OBJECT_EMCY == TRUE
	produce_emcy_default(CAN_EMCY_TIMEROVERLAP);
	#endif
}

void can_cache_overflow(canbyte state)
{
#if CAN_APPLICATION_MODE == MASTER || CAN_APPLICATION_MODE == TEST
	#if CAN_OBJECT_EMCY == TRUE
	master_emcy(CAN_EMCYREG_CACHE);
	#endif
#else
	set_error_field(CAN_EMCYREG_CACHE, 0);
	if (state != CAN_NODE_STATE_OPERATIONAL) {
		can_set_datalink_layer(OFF);
		set_led_green_off();
		set_led_red_on();
	}
	#if CAN_NMT_MODE == SLAVE	// 3.0.1
	process_serious_error(CAN_SUBIND_ERRBEH_COMM);
	#endif
#endif
}

#endif
