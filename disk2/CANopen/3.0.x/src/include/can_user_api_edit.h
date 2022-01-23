// ..SLAVE/can_device.c API functions below
unsigned32 read_dev_type_object(canindex index, cansubind subind);
void read_dev_string_object(canindex index, cansubind subind, canbyte *data);

// ..common/__can_init.c API functions below
cannode get_node_id(void);
unsigned8 get_bit_rate_index(void);
unsigned32 get_serial_number(void);

// ..common/__can_events.c API functions below
void consume_sync(unsigned8 sc);
void no_sync_event(void);
void consume_time(canframe *cf);
void consume_controller_error(canev ev);

void master_emcy(unsigned16 errorcode);
void consume_emcy(canframe *cf);
void can_client_state(struct sdocltappl *ca);

void heartbeat_event(cannode node);
void heartbeat_resolved(cannode node);
void node_guarding_event(cannode node);
void node_guarding_resolved(cannode node);
void bootup_event(cannode node);
void node_state_event(cannode node, canbyte state);

void life_guarding_event(void);
void life_guarding_resolved(void);

void pdo_activated_master(cannode node, canindex index, cansubind subind);
void pdo_activated_slave(canindex index, cansubind subind);
void no_pdo_event(canindex index);		// 2.2.1

void can_timer_overlap(void);
void can_cache_overflow(canbyte state);
