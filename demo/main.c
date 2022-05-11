#include <master_header.h>
#include <syslog.h>


int main(int argc, char** argv)
{
    openlog("Demo", LOG_CONS, LOG_USER);

    if (start_can_master() != CAN_RETOK) {
        return CAN_ERRET_MAIN;
    }

    return 0;
}
