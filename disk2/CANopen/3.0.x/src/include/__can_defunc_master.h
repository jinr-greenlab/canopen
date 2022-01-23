// Test application.
// ..MASTER/__can_test_application.c internal functions below
void test_monitor(void);
void start_test_application(void);

// Test object dictionary.
// ..MASTER/__obdms_master_test.h internal functions below
int32 test_get_manstan_objsize(canindex index, cansubind subind, int16 unit);
canbyte *test_get_manstan_objpointer(canindex index, cansubind subind);
int16 test_see_manstan_access(canindex index, cansubind subind);
int16 test_get_manstan_objtype(canindex index, cansubind subind);
int16 test_read_manstan_objdict(canindex index, cansubind subind, canbyte *data);
int16 test_write_manstan_objdict(canindex index, cansubind subind, canbyte *data);
