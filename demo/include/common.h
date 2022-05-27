#include <master_header.h>

#ifndef __COMMON_H
#define __COMMON_H

// #define GETREQ 0
// #define SETREQ 1

typedef enum req_type_t {
    Get,
    Set
} req_type_t;

typedef struct req_t {
    req_type_t type;
    int channel;
    unsigned16 voltage_dac;
} req_t;

typedef struct resp_t {
    int channel;
    unsigned32 voltage_adc;
} resp_t;

#endif
