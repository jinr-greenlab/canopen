// ..common/can_pdo_proc.c API functions below
int16 pdo_remote_transmit_request(canindex index);
int16 transmit_can_pdo(canindex index);

// ..common/can_obj_time.c API functions below
void produce_time(unsigned32 ms, unsigned16 days);

// ..common/can_obj_emcy.c API functions below
int16 produce_emcy_default(unsigned16 errorcode);
int16 produce_emcy(unsigned16 errorcode, unsigned16 addinf, canbyte *mserr);

// ..common/can_obj_errors.c API functions below
void clear_error_register(unsigned8 mask);

// ..common/can_obj_re_store.c internal functions below
int16 get_flash_nodeid(void);
int16 get_flash_bitrate_index(void);
int16 put_flash_nodeid(cannode node);
int16 put_flash_bitrate_index(unsigned8 br);

// ..common/can_nmt_master.c API functions below
void nmt_master_command(unsigned8 cs, cannode node);

// ..MASTER/__obd_mans_master.c API functions below
int32 node_get_manstan_objsize(cannode node, canindex index, cansubind subind, int16 unit);
canbyte *node_get_manstan_objpointer(cannode node, canindex index, cansubind subind);
int16 node_see_manstan_access(cannode node, canindex index, cansubind subind);
int16 node_get_manstan_objtype(cannode node, canindex index, cansubind subind);
int16 node_read_manstan_objdict(cannode node, canindex index, cansubind subind, canbyte *data);
int16 node_write_manstan_objdict(cannode node, canindex index, cansubind subind, canbyte *data);

// ..MASTER/can_client.c API functions below
void can_sdo_client_transfer(struct sdocltappl *ca);

// ..MASTER/can_obdclt.c API functions below
int16 node_read_manstan_objdict_network(cannode node, canindex index, cansubind subind, canbyte *data);
int16 node_write_manstan_objdict_network(cannode node, canindex index, cansubind subind, canbyte *data);
int32 client_get_object_size(canindex index, cansubind subind, int16 unit);
int16 client_see_access(canindex index, cansubind subind);
int16 client_read_object_dictionary(canindex index, cansubind subind, canbyte *data);
int16 client_write_object_dictionary(canindex index, cansubind subind, canbyte *data);
int16 client_read_obd_u32(cannode node, canindex index, cansubind subind, unsigned32 *du32);
int16 client_write_obd_u32(cannode node, canindex index, cansubind subind, unsigned32 du32);

// ..common/can_pdo_obd.c API functions below
int16 get_pdo_node(canindex index, cannode *node);
int16 put_pdo_node(canindex index, cannode node);

// ..SLAVE/can_obdsrv.c API functions below
int32 server_get_object_size(canindex index, cansubind subind, int16 unit);
canbyte *server_get_object_pointer(canindex index, cansubind subind);
int16 server_see_access(canindex index, cansubind subind);
int16 server_get_object_type(canindex index, cansubind subind);
int16 server_read_object_dictionary(canindex index, cansubind subind, canbyte *data);
int16 server_write_object_dictionary(canindex index, cansubind subind, canbyte *data);
int16 server_read_obd_network(canindex index, cansubind subind, canbyte *data);
int16 server_write_obd_network(canindex index, cansubind subind, canbyte *data);
int16 server_read_obd_u32(canindex index, cansubind subind, unsigned32 *du32);
int16 server_write_obd_u32(canindex index, cansubind subind, unsigned32 du32);
