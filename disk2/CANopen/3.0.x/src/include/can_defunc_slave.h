// ..SLAVE/__obd_mans_slave.c internal functions below
int32 server_get_manstan_objsize(canindex index, cansubind subind, int16 unit);
canbyte *server_get_manstan_objpointer(canindex index, cansubind subind);
int16 server_see_manstan_access(canindex index, cansubind subind);
int16 server_get_manstan_objtype(canindex index, cansubind subind);
int16 server_read_manstan_objdict(canindex index, cansubind subind, canbyte *data);
int16 server_write_manstan_objdict(canindex index, cansubind subind, canbyte *data);
void slave_init_manstan_application(void);
void slave_init_manstan_communication(void);

// ..SLAVE/can_lss_slave.c internal functions below
void lss_slave_process(canframe *cf);
void can_init_lss(void);

// ..SLAVE/can_obdsdo_server.c internal functions below
int16 find_sdo_server_send_canid(canindex index, canlink *canid);
int16 get_sdo_server_bytes_objsize(canindex index, cansubind subind);
int16 see_sdo_server_access(canindex index, cansubind subind);
int16 get_sdo_server_objtype(canindex index, cansubind subind);
int16 read_sdo_server_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_sdo_server_objdict(canindex index, cansubind subind, canbyte *data);
void can_init_sdo_server(void);

// ..SLAVE/can_obj_device.c internal functions below
int16 get_dev_bytes_objsize(canindex index, cansubind subind);
int16 see_dev_access(canindex index, cansubind subind);
int16 get_dev_objtype(canindex index, cansubind subind);
int16 read_dev_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_dev_objdict(canindex index, cansubind subind, canbyte *data);

// ..SLAVE/can_server.c internal functions below
void can_server_upload_block(void);
void can_server_sdo(canindex sdoind, canframe *cf);
void can_server_control(void);
void can_init_server(void);

// ..common/can_obj_errors.c internal functions below
int16 get_err_bytes_objsize(canindex index, cansubind subind);
int16 see_err_access(canindex index, cansubind subind);
int16 get_err_objtype(canindex index, cansubind subind);
int16 read_err_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_err_objdict(canindex index, cansubind subind, canbyte *data);
unsigned8 read_error_register(void);
void can_init_error(void);

// ..common/can_obj_re_store.c internal functions below
int16 get_re_store_bytes_objsize(canindex index, cansubind subind);
int16 see_re_store_access(canindex index, cansubind subind);
int16 get_re_store_objtype(canindex index, cansubind subind);
int16 read_re_store_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_re_store_objdict(canindex index, cansubind subind, canbyte *data);
int16 can_process_saved(unsigned16 mask);
int16 check_init_flash(void);
void can_init_re_store(void);
void can_test_re_store(void);

// ..common/can_obj_emcy.c internal functions below
int16 get_emcy_bytes_objsize(canindex index, cansubind subind);
int16 see_emcy_access(canindex index, cansubind subind);
int16 get_emcy_objtype(canindex index, cansubind subind);
int16 read_emcy_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_emcy_objdict(canindex index, cansubind subind, canbyte *data);
void control_emcy_inhibit(void);
