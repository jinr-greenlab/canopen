#include <master_header.h>
#include <syslog.h>
#include <common.h>
#include <can.h>
#include <unistd.h>

#define DEVICE_ID 2
#define CANOPEN_DAC_W 0x2411
#define CANOPEN_ADC_R 0x2402

void * start_master(void * _config) {
    master_config_t * config = (master_config_t *)_config;
    req_t req;
    resp_t resp;
    int rsize;

    printf("Starting can master\n");
    if (start_can_master(config->can_config_path) != CAN_RETOK) {
        fprintf(stderr, "Error while starting can master\n");
        return NULL;
    }

    canbyte * voltage_adc = malloc(sizeof(canbyte) * 4);
    int16 sdo_status;

    while(TRUE) {
        can_sleep(100000);

        rsize = read(config->req_fd, &req, sizeof(req_t));
        if (rsize == sizeof(req_t)){
            if (req.type == Set) {
                syslog(LOG_INFO, "Set voltage request received: channel: %d voltage: %d", req.channel, req.voltage_dac);
                sdo_status = write_device_object(DEVICE_ID, CANOPEN_DAC_W, req.channel, &req.voltage_dac, 2);
                if (sdo_status != CAN_TRANSTATE_OK) {
                    syslog(LOG_ERR, "Error while writing canopen object: idx: %d sub: %d", CANOPEN_DAC_W, req.channel);
                }
            } else if (req.type == Get) {
                syslog(LOG_INFO, "Get voltage request received: channel: %d", req.channel);
                sdo_status = read_device_object(DEVICE_ID, 0x2402, req.channel, voltage_adc, sizeof(canbyte) * 4);
                if (sdo_status != CAN_TRANSTATE_OK) {
                    syslog(LOG_ERR, "Error while reading canopen object: idx: %d sub: %d", CANOPEN_ADC_R, req.channel);
                    continue;
                }
                resp.channel = req.channel;
                resp.voltage_adc = *((unsigned32 *)voltage_adc);
                write(config->resp_fd, &resp, sizeof(resp_t));
            }
        }
    }

    printf("Stopping can master\n");
    if (stop_can_master() != CAN_RETOK) {
        fprintf(stderr, "Error while stopping can master\n");
        return NULL;
    }
    return NULL;
}
