#include <master_header.h>
#include <syslog.h>


static void monitor(void)
{
    syslog(LOG_INFO, "Monitor cycle");
    can_sleep(100 * CAN_SLEEP_ONE_MILLISEC);
}


int main(int argc, char** argv)
{
    openlog("Demo", LOG_CONS, LOG_USER);

    syslog(LOG_INFO, "Starting can master");
    if (start_can_master() != CAN_RETOK) {
        return CAN_ERRET_MAIN;
    }

    while (TRUE) monitor();

    syslog(LOG_INFO, "Stopping can master");
    if (stop_can_master() != CAN_RETOK) {
        return CAN_ERRET_MAIN;
    }
    return CAN_RETOK_MAIN;
}
