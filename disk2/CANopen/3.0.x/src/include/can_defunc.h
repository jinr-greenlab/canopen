#ifndef __CAN_DEFUNC_H__
#define __CAN_DEFUNC_H__

// ..can_system.c internal functions below
// operational system dependent functions
void can_sleep(int32 microseconds);
void can_init_system_timer(void (*handler)(void));	// 2.3.1 API changed
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

// ..MASTER/can_test_driver.c internal functions below
void test_zero(canframe *cf);
int16 read_can_test_driver(unsigned8 chan, canframe *mbuf, int16 cnt);
int16 write_can_test_driver(unsigned8 chan, canframe *mbuf, int16 cnt);

// ..common/can_backinit.c internal functions below
int16 set_controller_bitrate(unsigned8  br_index);
int16 can_reset_communication(void);
int16 can_reset_node(void);
void canopen_monitor(void);
int16 start_can_device(unsigned8 net);
int16 stop_can_device(void);

// ..common/can_malloc.c internal functions below
canbyte *can_malloc(int32 bytes);
void can_free(canbyte *ptr);
void can_init_malloc(void);

// ..common/can_lib.c internal functions below
void can_start_crc(unsigned16 val);
unsigned16 can_calc_crc(unsigned8 data);
void can_init_crc(void);
int16 check_node_id(cannode node);
int16 check_bitrate_index(unsigned8 br);
void clear_can_data(canbyte *data);
void u16_to_canframe(unsigned16 ud, canbyte *data);
unsigned16 canframe_to_u16(canbyte *data);
void u32_to_canframe(unsigned32 ud, canbyte *data);
unsigned32 canframe_to_u32(canbyte *data);

// ..common/can_canid.c internal functions below
int16 correct_recv_canid(canindex index, canlink canid);
canindex find_comm_recv_index(canlink canid);			// 3.0.1 API changed
unsigned8 check_sdo_canid(canindex index, cansubind subind, canlink canid);		// 2.2.1
unsigned8 check_canid_restricted(canlink canid);		// 2.2.1
void can_init_recv_canids(void);

// ..common/can_inout.c internal functions below
void push_all_can_data(void);
int16 send_can_data(canframe *cf);		// 3.0.1 API changed
void can_read_handler(canev ev);
void can_set_datalink_layer(unsigned8 mode);
void can_init_io(void);

// ..common/can_sdo_proc.c internal functions below
void parse_sdo(struct cansdo *sd, canbyte *data);
void receive_can_sdo(canindex sdoind, canframe *cf);
int16 send_can_sdo(struct cansdo *sd);
void abort_can_sdo(struct sdoixs *si, unsigned32 abortcode);

// ..common/can_pdo_proc.c internal functions below
void receive_can_pdo(canindex index, canframe *cf);
void transmit_rtr_pdo(canindex index);
void process_sync_pdo(unsigned8 sc);
void can_init_pdo_proc(void);

// ..common/can_pdo_map.c internal functions below
int16 check_pdo_map_object(canindex index);		// 2.2.1
int16 get_pdo_map_bytes_objsize(canindex index, cansubind subind);
int16 see_pdo_map_access(canindex index, cansubind subind);
int16 get_pdo_map_objtype(canindex index, cansubind subind);
int16 read_pdo_map_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_pdo_map_objdict(canindex index, cansubind subind, canbyte *data);
int16 map_pdo(canindex index, canframe *cf);
int16 activate_pdo(canindex index, canframe *cf);
void can_init_pdo_map(void);

// ..common/can_pdo_obd.c internal functions below
int16 check_pdo_comm_object(canindex index);	// 2.2.1
int16 find_pdo_recv_trantype(canindex index, unsigned8 *trtype);
int16 find_pdo_tran_trantype(canindex index, unsigned8 *trtype);
int16 find_pdo_recv_canid(canindex index, canlink *canid);
int16 find_pdo_tran_canid(canindex index, canlink *canid);
void find_pdo_rtr_tran_index(canlink canid, canindex *index);
void set_pdo_tran_event_timer(canindex index);
void set_pdo_recv_event_timer(canindex index);
int16 test_cyclic_tpdo(canindex index, unsigned8 sc);
int16 test_tpdo_inhibit(canindex index);
void control_pdo(void);
int16 get_pdo_comm_bytes_objsize(canindex index, cansubind subind);
int16 see_pdo_comm_access(canindex index, cansubind subind);
int16 get_pdo_comm_objtype(canindex index, cansubind subind);
int16 read_pdo_comm_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_pdo_comm_objdict(canindex index, cansubind subind, canbyte *data);
int16 set_pdo_state(canindex index, unsigned8 state);
void can_init_pdo(void);

// ..common/can_obj_sync.c internal functions below
void reset_sync_counter(void);
int16 get_sync_bytes_objsize(canindex index, cansubind subind);
int16 see_sync_access(canindex index, cansubind subind);
int16 get_sync_objtype(canindex index, cansubind subind);
int16 read_sync_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_sync_objdict(canindex index, cansubind subind, canbyte *data);
unsigned8 sync_window_expired(void);
void sync_received(canframe *cf);
void control_sync(void);
void can_init_sync(void);

// ..common/can_obj_deftype.c internal functions below
int16 get_deftype_objsize(canindex index, cansubind subind, int16 unit);
int16 see_deftype_access(canindex index, cansubind subind);
int16 get_deftype_objtype(canindex index, cansubind subind);
int16 read_deftype_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_deftype_objdict(canindex index, cansubind subind, canbyte *data);

// ..common/can_obj_emcy.c internal functions below
void can_init_emcy(void);

// ..common/can_obj_time.c internal functions below
int16 get_time_bytes_objsize(canindex index, cansubind subind);
int16 see_time_access(canindex index, cansubind subind);
int16 get_time_objtype(canindex index, cansubind subind);
int16 read_time_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_time_objdict(canindex index, cansubind subind, canbyte *data);
void can_init_time(void);

// ..common/can_obj_err_behaviour.c internal functions below
int16 get_err_behaviour_bytes_objsize(canindex index, cansubind subind);
int16 see_err_behaviour_access(canindex index, cansubind subind);
int16 get_err_behaviour_objtype(canindex index, cansubind subind);
int16 read_err_behaviour_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_err_behaviour_objdict(canindex index, cansubind subind, canbyte *data);
void process_serious_error(cansubind subind);
void can_init_err_behaviour(void);

// ..common/can_obj_errors.c internal functions below
void set_error_field(unsigned16 errorcode, unsigned16 addinf);

// ..common/can_led_indicator.c functions below
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

#include "can_defunc_nmt.h"
#include "can_defunc_master.h"
#include "can_defunc_slave.h"

#include "can_user_api_call.h"
#include "can_user_api_edit.h"

#endif
