#include <master_header.h>
#include <syslog.h>
#include <common.h>
#include <can.h>
#include <unistd.h>


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
    canbyte * ref_voltage = malloc(sizeof(canbyte) * 4);
    canbyte * ext_voltage = malloc(sizeof(canbyte) * 4);
    canbyte * mez_temp = malloc(sizeof(canbyte) * 4);
    int16 sdo_status;

    while(TRUE) {
        can_sleep(100000);
        rsize = read(config->req_fd, &req, sizeof(req_t));
        if (rsize == sizeof(req_t)){
            if (req.type == SetVoltage) {
                syslog(LOG_INFO, "Set voltage request received: node: %d --- channel: %d --- voltage: %d\n",req.node, req.subindex, req.voltage_dac);
                sdo_status = write_device_object(req.node, CANOPEN_DAC_W, req.subindex, (canbyte *)&req.voltage_dac, 2);
                if (sdo_status != CAN_TRANSTATE_OK) {
                    syslog(LOG_ERR, "Error while writing canopen object: idx: %d sub: %d\n", CANOPEN_DAC_W, req.subindex);
                }
            } else if (req.type == GetVoltage) {
                syslog(LOG_INFO, "Get voltage request received: node: %d --- channel: %d\n", req.node, req.subindex);
                sdo_status = read_device_object(req.node, CANOPEN_ADC_R, req.subindex, voltage_adc, sizeof(canbyte) * 4);
                if (sdo_status != CAN_TRANSTATE_OK) {
                    syslog(LOG_ERR, "Error while reading canopen object: idx: %d sub: %d\n", CANOPEN_ADC_R, req.subindex);
                    continue;
                }
                resp.subindex = req.subindex;
                resp.value = *((unsigned32 *)voltage_adc);
                write(config->resp_fd, &resp, sizeof(resp_t));
            }
            else if (req.type == GetRefVoltage) {
                syslog(LOG_INFO, "Get ref voltage request received: node: %d --- channel: %d\n", req.node, req.subindex);
                sdo_status = read_device_object(req.node, CANOPEN_REF_R, req.subindex, ref_voltage, sizeof(canbyte) * 4);
                if (sdo_status != CAN_TRANSTATE_OK) {
                    syslog(LOG_ERR, "Error while reading canopen object: idx: %d sub: %d\n", CANOPEN_REF_R, req.subindex);
                    continue;
                }
                resp.subindex = req.subindex;
                resp.value = *((unsigned32 *)ref_voltage);
                write(config->resp_fd, &resp, sizeof(resp_t));
            }
            else if (req.type == GetExtVoltage) {
                syslog(LOG_INFO, "Get ext voltage request received: node: %d --- channel: %d\n", req.node, req.subindex);
                sdo_status = read_device_object(req.node, CANOPEN_EXT_R, req.subindex, ext_voltage, sizeof(canbyte) * 4);
                if (sdo_status != CAN_TRANSTATE_OK) {
                    syslog(LOG_ERR, "Error while reading canopen object: idx: %d sub: %d\n", CANOPEN_EXT_R, req.subindex);
                    continue;
                }
                resp.subindex = req.subindex;
                resp.value = *((unsigned32 *)ext_voltage);
                write(config->resp_fd, &resp, sizeof(resp_t));
            }
            else if (req.type == GetMezTemp) {
                syslog(LOG_INFO, "Get mez.temperature request received: node: %d --- subindex: %d\n", req.node, req.subindex);
                sdo_status = read_device_object(req.node, CANOPEN_TEMP_R, req.subindex, mez_temp, sizeof(canbyte) * 4);
                if (sdo_status != CAN_TRANSTATE_OK) {
                    syslog(LOG_ERR, "Error while reading canopen object: idx: %d sub: %d\n", CANOPEN_TEMP_R, req.subindex);
                    continue;
                }
                resp.subindex = req.subindex;
                resp.value = *((unsigned32 *)mez_temp);
                write(config->resp_fd, &resp, sizeof(resp_t));
            }
            else if (req.type == ResetNode) {
                syslog(LOG_INFO, "Reset node: %d\n", req.node);
                reset_can_node(req.node);
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
