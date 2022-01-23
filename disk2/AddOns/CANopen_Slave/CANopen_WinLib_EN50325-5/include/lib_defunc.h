#ifndef __DEFUNC_WINLIB_H__
#define __DEFUNC_WINLIB_H__

// System dependent functions
void can_sleep(int32 microseconds);
void can_init_system_timer(void (*handler)(void));
void can_cancel_system_timer(void);
void init_critical(void);
void enter_critical(void);
void leave_critical(void);
void enable_can_transmitter(void);
void disable_can_transmitter(void);
void green_led_on(void);
void green_led_off(void);
void red_led_on(void);
void red_led_off(void);

// ..CANopen\__lib_events.c functions below
void consume_sync(unsigned8 sc);
void no_sync_event(void);
void consume_controller_error(canev ev);
void life_guarding_event(void);
void life_guarding_resolved(void);
void pdo_activated_slave(canindex index, cansubind subind);
void srdo_activated_slave(canindex index, cansubind subind);
void no_pdo_event(canindex index);
void can_timer_overlap(void);
void can_cache_overflow(canbyte state);

// ..CANopen\lib_backinit.c functions below
unsigned8 get_netmask_free(void);
int16 cifunc_start(void);
int16 cifunc_stop(void);
int16 can_reset_communication(void);
int16 can_reset_node(void);
int16 start_can_device(void);
int16 stop_can_device(void);
void canopen_monitor(void);

// ..CANopen\lib_can_networks.c functions below
int16 get_can_networks_bytes_objsize(canindex index, cansubind subind);
int16 see_can_networks_access(canindex index, cansubind subind);
int16 get_can_networks_objtype(canindex index, cansubind subind);
int16 read_can_networks_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_can_networks_objdict(canindex index, cansubind subind, canbyte *data);

// ..CANopen\lib_canid.c functions below
int16 correct_recv_canid(canindex index, canlink canid);
int16 correct_double_canid(canindex index, canlink canid_1, canlink canid_2);
canindex find_comm_recv_index(canlink canid);		// 3.0.1 API changed
unsigned8 check_canid_restricted(canlink canid);	// 2.2.1
void can_init_recv_canids(void);

// ..CANopen\lib_inout.c functions below
void push_all_can_data(void);
int16 send_can_data(canframe *cf);
void can_read_handler_0(canev ev);
void can_read_handler_1(canev ev);
void can_read_handler_2(canev ev);
void can_read_handler_3(canev ev);
void can_read_handler_4(canev ev);
void can_read_handler_5(canev ev);
void can_read_handler_6(canev ev);
void can_read_handler_7(canev ev);
void can_set_datalink_layer(unsigned8 mode);
void can_init_io(void);

// ..CANopen\lib_led_indicator.c functions below
void led_control(void);
void set_led_red_on(void);
void set_led_green_on(void);
void set_led_red_off(void);
void set_led_green_off(void);
void set_leds_flickering(void);
void set_led_red_blinking(void);
void set_led_green_blinking(void);
void set_led_red_single_flash(void);
void set_led_green_single_flash(void);
void set_led_red_double_flash(void);
void set_led_green_double_flash(void);
void set_led_red_triple_flash(void);
void set_led_green_triple_flash(void);
void set_led_red_quadruple_flash(void);
void set_led_green_quadruple_flash(void);
void can_init_led_indication(void);

// ..CANopen\lib_lib.c functions below
void can_start_crc(unsigned16 val);
unsigned16 can_calc_crc(unsigned8 data);
void can_init_crc(void);
int16 check_node_id(cannode node);
int16 check_bitrate_index(unsigned8 br);
cannode get_dev_nodeid(void);
unsigned8 get_dev_node_state(void);
void clear_can_data(canbyte *data);
void u16_to_canframe(unsigned16 ud, canbyte *data);
unsigned16 canframe_to_u16(canbyte *data);
void u32_to_canframe(unsigned32 ud, canbyte *data);
unsigned32 canframe_to_u32(canbyte *data);

// ..CANopen\lib_nmt_slave.c functions below
void start_node(void);
void stop_node(void);
void enter_pre_operational(void);
void nmt_slave_process(canframe *cf);
void nmt_slave_control(void);
int16 get_ecpslave_bytes_objsize(canindex index, cansubind subind);
int16 see_ecpslave_access(canindex index, cansubind subind);
int16 get_ecpslave_objtype(canindex index, cansubind subind);
int16 read_ecpslave_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_ecpslave_objdict(canindex index, cansubind subind, canbyte *data);
void node_guard_slave(void);
void manage_slave_ecp(void);
void can_init_ecp(void);

// ..CANopen\lib_obdsdo_server.c functions below
int16 find_sdo_server_send_canid(canlink *canid);
int16 get_sdo_server_bytes_objsize(canindex index, cansubind subind);
int16 see_sdo_server_access(canindex index, cansubind subind);
int16 get_sdo_server_objtype(canindex index, cansubind subind);
int16 read_sdo_server_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_sdo_server_objdict(canindex index, cansubind subind, canbyte *data);
void can_init_sdo_server(void);

// ..CANopen\lib_obdsrv.c functions below
int32 server_get_object_size(canindex index, cansubind subind);
int32 server_put_object_size(canindex index, cansubind subind, int32 size);		// Variable data size
int16 server_see_access(canindex index, cansubind subind);
int16 server_get_object_type(canindex index, cansubind subind);
int16 server_read_object_dictionary(canindex index, cansubind subind, canbyte *data);
int16 server_write_object_dictionary(canindex index, cansubind subind, canbyte *data);
int16 server_read_obd_u32(canindex index, cansubind subind, unsigned32 *du32);
int16 server_write_obd_u32(canindex index, cansubind subind, unsigned32 du32);

// ..CANopen\lib_obj_deftype.c functions below
int16 get_deftype_bytes_objsize(canindex index, cansubind subind);
int16 see_deftype_access(canindex index, cansubind subind);
int16 get_deftype_objtype(canindex index, cansubind subind);
int16 read_deftype_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_deftype_objdict(canindex index, cansubind subind, canbyte *data);

// ..CANopen\lib_obj_device.c functions below
int16 get_dev_bytes_objsize(canindex index, cansubind subind);
int16 see_dev_access(canindex index, cansubind subind);
int16 get_dev_objtype(canindex index, cansubind subind);
int16 read_dev_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_dev_objdict(canindex index, cansubind subind, canbyte *data);

// ..CANopen\lib_obj_emcy.c functions below
int16 get_emcy_bytes_objsize(canindex index, cansubind subind);
int16 see_emcy_access(canindex index, cansubind subind);
int16 get_emcy_objtype(canindex index, cansubind subind);
int16 read_emcy_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_emcy_objdict(canindex index, cansubind subind, canbyte *data);
void control_emcy_inhibit(void);
int16 produce_emcy(unsigned16 errorcode, unsigned16 addinf, canbyte *mserr);
int16 produce_emcy_default(unsigned16 errorcode);
void can_init_emcy(void);

// ..CANopen\lib_obj_time.c internal functions below
int16 get_time_bytes_objsize(canindex index, cansubind subind);
int16 see_time_access(canindex index, cansubind subind);
int16 get_time_objtype(canindex index, cansubind subind);
int16 read_time_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_time_objdict(canindex index, cansubind subind, canbyte *data);
void can_init_time(void);

// ..CANopen\lib_obj_err_behaviour.c internal functions below
int16 get_err_behaviour_bytes_objsize(canindex index, cansubind subind);
int16 see_err_behaviour_access(canindex index, cansubind subind);
int16 get_err_behaviour_objtype(canindex index, cansubind subind);
int16 read_err_behaviour_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_err_behaviour_objdict(canindex index, cansubind subind, canbyte *data);
void process_serious_error(cansubind subind);
void can_init_err_behaviour(void);

// ..CANopen\lib_obj_errors.c functions below
int16 get_err_bytes_objsize(canindex index, cansubind subind);
int16 see_err_access(canindex index, cansubind subind);
int16 get_err_objtype(canindex index, cansubind subind);
int16 read_err_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_err_objdict(canindex index, cansubind subind, canbyte *data);
void set_error_field(unsigned16 errorcode, unsigned16 addinf);
void clear_error_register(unsigned8 mask);
unsigned8 read_error_register(void);
void can_init_error(void);

// ..CANopen\lib_obj_re_store.c internal functions below
int16 get_re_store_bytes_objsize(canindex index, cansubind subind);
int16 see_re_store_access(canindex index, cansubind subind);
int16 get_re_store_objtype(canindex index, cansubind subind);
int16 read_re_store_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_re_store_objdict(canindex index, cansubind subind, canbyte *data);
int16 can_process_saved(unsigned16 mask);
int16 get_flash_nodeid(void);
int16 get_flash_bitrate_index(void);
int16 check_init_flash(void);
void erase_flash_pages(void);
void can_init_re_store(void);

// ..CANopen\lib_obj_sync.c functions below
int16 get_sync_bytes_objsize(canindex index, cansubind subind);
int16 see_sync_access(canindex index, cansubind subind);
int16 get_sync_objtype(canindex index, cansubind subind);
int16 read_sync_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_sync_objdict(canindex index, cansubind subind, canbyte *data);
void reset_sync_counter(void);
unsigned8 sync_window_expired(void);
void sync_received(canframe *cf);
void control_sync(void);
void can_init_sync(void);

// ..CANopen\lib_pdo_obd.c functions below
int16 check_pdo_comm_object(canindex index);	// 2.2.1
int16 find_pdo_recv_canid(canindex index, canlink *canid);
int16 find_pdo_tran_canid(canindex index, canlink *canid);
int16 find_pdo_recv_trantype(canindex index, unsigned8 *trtype);
int16 find_pdo_tran_trantype(canindex index, unsigned8 *trtype);
void find_pdo_rtr_tran_index(canlink canid, canindex *index);
int16 set_pdo_state(canindex index, unsigned8 state);
void set_pdo_recv_event_timer(canindex index);
void set_pdo_tran_event_timer(canindex index);
int16 test_cyclic_tpdo(canindex index, unsigned8 sc);
int16 test_tpdo_inhibit(canindex index);
void control_pdo(void);
int16 get_pdo_comm_bytes_objsize(canindex index, cansubind subind);
int16 see_pdo_comm_access(canindex index, cansubind subind);
int16 get_pdo_comm_objtype(canindex index, cansubind subind);
int16 read_pdo_comm_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_pdo_comm_objdict(canindex index, cansubind subind, canbyte *data);
void can_init_pdo(void);

// ..CANopen\lib_pdo_map.c functions below
int16 check_pdo_map_object(canindex index);		// 2.2.1
int16 get_pdo_map_bytes_objsize(canindex index, cansubind subind);
int16 see_pdo_map_access(canindex index, cansubind subind);
int16 get_pdo_map_objtype(canindex index, cansubind subind);
int16 read_pdo_map_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_pdo_map_objdict(canindex index, cansubind subind, canbyte *data);
int16 map_pdo(canindex index, canframe *cf);
int16 activate_pdo(canindex index, canframe *cf);
void can_init_pdo_map(void);

// ..CANopen\lib_pdo_proc.c functions below
int16 pdo_remote_transmit_request(canindex index);
void receive_can_pdo(canindex index, canframe *cf);
int16 transmit_can_pdo(canindex index);
void transmit_rtr_pdo(canindex index);
void process_sync_pdo(unsigned8 sc);
void can_init_pdo_proc(void);

// ..CANopen\lib_sdo_proc.c functions below
void parse_sdo(struct cansdo *sd, canbyte *data);
int16 send_can_sdo(struct cansdo *sd);
void abort_can_sdo(struct sdoixs *si, unsigned32 abortcode);

// ..CANopen\lib_server.c functions below
void receive_can_sdo(canframe *cf);
void can_server_control(void);
void can_init_server(void);

// ..CANopen\lib_srdo_object.c functions below
int16 get_srdo_comm_bytes_objsize(canindex index, cansubind subind);
int16 see_srdo_comm_access(canindex index, cansubind subind);
int16 get_srdo_comm_objtype(canindex index, cansubind subind);
int16 read_srdo_comm_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_srdo_comm_objdict(canindex index, cansubind subind, canbyte *data);
int16 get_srdo_map_bytes_objsize(canindex index, cansubind subind);
int16 see_srdo_map_access(canindex index, cansubind subind);
int16 get_srdo_map_objtype(canindex index, cansubind subind);
int16 read_srdo_map_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_srdo_map_objdict(canindex index, cansubind subind, canbyte *data);
int16 get_sr_config_bytes_objsize(canindex index, cansubind subind);
int16 see_sr_config_access(canindex index, cansubind subind);
int16 get_sr_config_objtype(canindex index, cansubind subind);
int16 read_sr_config_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_sr_config_objdict(canindex index, cansubind subind, canbyte *data);
void produce_sr_gfc(void);
void consume_sr_gfc(void);
void control_srdo(void);
void receive_can_srdo(canindex index, canframe *cf);
void run_sr_operations(void);
unsigned8 get_sr_runstatus(void);
void can_init_srdo(void);

// ***** Application MANDATORY functions or stubs below *****
//
// ..application\DS401_standev.c
int32 server_get_standev_objsize(canindex index, cansubind subind);
int16 server_see_standev_access(canindex index, cansubind subind);
int16 server_get_standev_objtype(canindex index, cansubind subind);
int16 server_read_standev_objdict(canindex index, cansubind subind, canbyte *data);
int16 server_write_standev_objdict(canindex index, cansubind subind, canbyte *data);
void enter_error_state(void);
void exit_error_state(void);
void slave_init_standev_application(void);
void slave_init_standev_communication(void);

// ...application\DS401_manspec.c
int32 server_get_manspec_objsize(canindex index, cansubind subind);
int32 server_put_manspec_objsize(canindex index, cansubind subind, int32 size);
int16 server_see_manspec_access(canindex index, cansubind subind);
int16 server_get_manspec_objtype(canindex index, cansubind subind);
int16 server_read_manspec_objdict(canindex index, cansubind subind, canbyte *data);
int16 server_write_manspec_objdict(canindex index, cansubind subind, canbyte *data);
void slave_init_manspec_application(void);
void slave_init_manspec_communication(void);

// ..application/DS401_control.c
void start_hardware(void);
void stop_hardware(void);
void application_timer_routine(void);
void application_monitor_routine(void);
void application_init_device_routine(void);

// ..CANopen\__DS401_devices.c
unsigned32 read_dev_type_object(canindex index, cansubind subind);
void read_dev_string_object(canindex index, cansubind subind, canbyte *data);

// ..CANopen\__DS401_init.c
cannode get_node_id(void);
unsigned8 get_bit_rate_index(void);
unsigned32 get_serial_number(void);
void get_device_config(void);

// ..CANopen\DS401_obj_re_store.c
void can_init_re_store_application(void);

#endif
