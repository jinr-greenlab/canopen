// ..MASTER/__obd_mans_client.c internal functions below
void master_init_manstan_application(void);
void master_init_manstan_communication(void);

// ..MASTER/can_cltrans.c internal functions below
void can_client_sdo(canindex sdoind, canframe *cf);
void can_client_basic(struct sdoclttrans *ct);
void can_client_control(void);
void can_init_client(void);
int16 can_client_send_block_frame(struct sdoclttrans *ct);

// ..MASTER/can_obdsdo_client.c internal functions below
int16 find_sdo_client_send_canid(canindex index, canlink *canid);
int16 get_sdo_client_bytes_objsize(canindex index, cansubind subind);
int16 read_sdo_client_objdict(canindex index, cansubind subind, canbyte *data);
int16 write_sdo_client_objdict(canindex index, cansubind subind, canbyte *data);
void can_init_sdo_client(void);

#include "__can_defunc_master.h"
