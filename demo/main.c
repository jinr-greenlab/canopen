#include <master_header.h>

int main(int argc, char** argv)
{
    if (start_can_master() != CAN_RETOK) {
        return CAN_ERRET_MAIN;
    }

    return 0;
}
