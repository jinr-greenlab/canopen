#include <syslog.h>
#include <master_header.h>

void master_event(unsigned8 cls, unsigned8 type, int16 code, int32 info)
{
    node_event(EVENT_NODE_MASTER, cls, type, code, info);
}

void node_event(cannode node, unsigned8 cls, unsigned8 type, int16 code, int32 info)
{
    syslog(LOG_INFO, "Event: node_id: %04d cls: %04d type: %04d code: %08d info: %08d", node, cls, type, code, info);
}
