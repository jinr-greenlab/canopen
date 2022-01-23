// ..common/can_nmt_master.c internal functions below
int16 get_ecpmaster_bytes_objsize(canindex index, cansubind subind);
int16 see_ecpmaster_access(canindex index, cansubind subind);
int16 get_ecpmaster_objtype(canindex index, cansubind subind);
int16 read_ecpmaster_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_ecpmaster_objdict(canindex index, cansubind subind, canbyte *data);
void consume_nmt(canframe *cf);
void manage_master_ecp(void);
void start_can_master(void);
void can_init_nmt_master(void);

// ..common/can_nmt_slave.c internal functions below
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
