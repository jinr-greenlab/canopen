#include <stdio.h>
#include <master_header.h>

#if CHECK_VERSION_CANLIB(3, 0, 4)

static int16 sem_sys=-1024;

// FIXME: Figure out what does this function do.
static void canopen_timer(void)
{
    sem_sys++;
    if (sem_sys == 0) {
        control_sync();
        can_client_control();
        manage_master_ecp();
        push_all_can_data();
    }
    sem_sys--;
}

static int16 set_controller_bitrate(unsigned8 br_index)
{
    if (CiStop(can_network) < 0) return CAN_ERRET_CI_STOP;
    if (br_index == CIA_BITRATE_INDEX_1000) {
        if (CiSetBaud(can_network, BCI_1M) < 0) return CAN_ERRET_CI_BITRATE;
    } else if (br_index == CIA_BITRATE_INDEX_800) {
        if (CiSetBaud(can_network, BCI_800K) < 0) return CAN_ERRET_CI_BITRATE;
    } else if (br_index == CIA_BITRATE_INDEX_500) {
        if (CiSetBaud(can_network, BCI_500K) < 0) return CAN_ERRET_CI_BITRATE;
    } else if (br_index == CIA_BITRATE_INDEX_250) {
        if (CiSetBaud(can_network, BCI_250K) < 0) return CAN_ERRET_CI_BITRATE;
    } else if (br_index == CIA_BITRATE_INDEX_125) {
        if (CiSetBaud(can_network, BCI_125K) < 0) return CAN_ERRET_CI_BITRATE;
    } else if (br_index == CIA_BITRATE_INDEX_50) {
        if (CiSetBaud(can_network, BCI_50K) < 0) return CAN_ERRET_CI_BITRATE;
    } else if (br_index == CIA_BITRATE_INDEX_20) {
        if (CiSetBaud(can_network, BCI_20K) < 0) return CAN_ERRET_CI_BITRATE;
    } else if (br_index == CIA_BITRATE_INDEX_10) {
        if (CiSetBaud(can_network, BCI_10K) < 0) return CAN_ERRET_CI_BITRATE;
    } else return CAN_ERRET_BITRATE;
    if (CiStart(can_network) < 0) return CAN_ERRET_CI_START;
    return CAN_RETOK;
}

static int16 can_init_controller(void)
{
    if (CiStop(can_network) < 0) return CAN_ERRET_CI_STOP;
    if (CiClose(can_network) < 0) return CAN_ERRET_CI_CLOSE;
    if (CiOpen(can_network, CIO_CAN11) < 0) return CAN_ERRET_CI_OPEN;
    if (CiSetWriteTout(can_network, 0) < 0) return CAN_ERRET_CI_WTOUT;    // NO timeout
    if (CiSetCB(can_network, CIEV_RC, (void*)can_read_handler) < 0) return CAN_ERRET_CI_HANDLER;
    if (CiSetCB(can_network, CIEV_CANERR, (void*)consume_controller_error) < 0) return CAN_ERRET_CI_HANDLER;
    return set_controller_bitrate(bitrate_index);
}


int16 start_can_master(int argc, char** argv)
{
    int16 fnr;
    printf("Configuring ...\n");
    configure(argc, argv);

    printf("CiInit ...\n");
    if (CiInit() < 0) {
        master_event(EVENT_CLASS_MASTER_CHAI, EVENT_TYPE_FATAL, CAN_ERRET_CI_INIT, EVENT_INFO_DUMMY);
        return CAN_ERRET_CI_INIT;
    }
    printf("CiOpen ...\n");
    if (CiOpen(can_network, 0) < 0) {
        master_event(EVENT_CLASS_MASTER_CHAI, EVENT_TYPE_FATAL, CAN_ERRET_CI_OPEN, EVENT_INFO_DUMMY);
        return CAN_ERRET_CI_OPEN;
    }
    printf("can_init_client\n");
    can_init_client();
    printf("can_init_sdo_client\n");
    can_init_sdo_client();
    printf("can_init_io\n");
    can_init_io();
    printf("can_init_pdo\n");
    can_init_pdo();
    printf("can_init_sync\n");
    can_init_sync();
    printf("can_init_system_timer\n");
    can_init_system_timer(canopen_timer);
    printf("can_init_controller\n");
    fnr = can_init_controller();
    if (fnr != CAN_RETOK) {
        master_event(EVENT_CLASS_MASTER_CHAI, EVENT_TYPE_FATAL, fnr, EVENT_INFO_DUMMY);
        return fnr;
    }
    sem_sys = -1;
    printf("start_can_network\n");
    start_can_network();
    return CAN_RETOK;
}

int16 stop_can_master(void)   // 3.0.4 return conditions changed
{
    sem_sys = -1024;
    can_cancel_system_timer();
    CiStop(can_network);
    CiClose(can_network);
    return CAN_RETOK;
}

#endif
