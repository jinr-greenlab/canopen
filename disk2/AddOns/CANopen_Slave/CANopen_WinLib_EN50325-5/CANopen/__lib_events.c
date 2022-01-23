#include <lib_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 1)

void consume_sync(unsigned8 sc)
{
}

void no_sync_event(void)
{
	set_led_red_triple_flash();
}

void consume_controller_error(canev ev)
{
	if (ev == CIEV_BOFF) {
		process_serious_error(CAN_SUBIND_ERRBEH_COMM);
		set_led_red_on();
	} else if (ev == CIEV_HOVR) {
		produce_emcy_default(CAN_EMCY_HOVR);
	} else if (ev == CIEV_SOVR) {
		produce_emcy_default(CAN_EMCY_SOVR); 
	} else if (ev == CIEV_EWL) {
		produce_emcy_default(CAN_EMCY_EWL);
		set_led_red_single_flash();
	} else if (ev == CIEV_WTOUT) {
		produce_emcy_default(CAN_EMCY_WTOUT); 
	}
}

void life_guarding_event(void)
{
	produce_emcy_default(CAN_EMCY_HEARTBEAT);
	set_led_red_double_flash();
}

void life_guarding_resolved(void)
{
}

void pdo_activated_slave(canindex index, cansubind subind)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) return;	// Dummy entries
}

void srdo_activated_slave(canindex index, cansubind subind)
{
	if (index >= CAN_INDEX_DEFTYPE_MIN && index <= CAN_INDEX_DEFTYPE_MAX) return;	// Dummy entries
}

void no_pdo_event(canindex index)		// 2.2.1
{
	produce_emcy_default(CAN_EMCY_RPDO_TIMEOUT);
	set_led_red_quadruple_flash();
}

void can_timer_overlap(void)
{
	produce_emcy_default(CAN_EMCY_TIMEROVERLAP);
}

void can_cache_overflow(canbyte state)
{
	set_error_field(CAN_EMCYREG_CACHE, 0);
	if (state != CAN_NODE_STATE_OPERATIONAL) {
		can_set_datalink_layer(OFF);
		set_led_green_off();
		set_led_red_on();
	}
	process_serious_error(CAN_SUBIND_ERRBEH_COMM);
}

#endif
