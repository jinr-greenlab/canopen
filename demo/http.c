#include <stdio.h>
#include <ulfius.h>
#include <string.h>
#include <syslog.h>
#include <jansson.h>
#include <common.h>
#include <http.h>
#include <time.h>

#define RESP_TIMEOUT 3

// get the voltage from the in-memory state and respond to a user
static int callback_get_voltage(const struct _u_request * request, struct _u_response * response, void * _config) {
    http_config_t * config = (http_config_t *) _config;
    json_t * json_body = NULL;
    int rsize;
    time_t req_timestamp;
    time_t current_timestamp;
    req_t req;
    resp_t resp;
    // get channel number from the url /api/voltage/:channel
    int channel = atoi(u_map_get(request->map_url, "channel"));
    syslog(LOG_INFO, "Trying to get voltage for channel: %d", channel);

    req.type = Get;
    req.channel = channel;
    write(config->req_fd, &req, sizeof(req_t));
    time(&req_timestamp);
    while (TRUE) {
        usleep(100000);
        rsize = read(config->resp_fd, &resp, sizeof(resp_t));
        if (rsize == sizeof(resp_t)){
            break;
        }
        time(&current_timestamp);
        if (current_timestamp - req_timestamp > RESP_TIMEOUT) {
            syslog(LOG_ERR, "CAN response timeout");
            json_body = json_object();
            json_object_set_new(json_body, "error", json_string("CAN response timeout"));
            ulfius_set_json_body_response(response, 408, json_body);
            json_decref(json_body);
            return U_CALLBACK_CONTINUE;
        }
    }

    // create response data formatted like '{"channel": channel, "voltage": voltage}'
    json_body = json_object();
    json_object_set_new(json_body, "channel", json_integer(resp.channel));
    json_object_set_new(json_body, "voltage_adc", json_integer(resp.voltage_adc));
    ulfius_set_json_body_response(response, 200, json_body);
    syslog(LOG_INFO, "Get voltage response, %s", json_dumps(json_body, 0));
    json_decref(json_body);
    return U_CALLBACK_CONTINUE;
}

// parse request and put the voltage to the pipe
static int callback_set_voltage(const struct _u_request * request, struct _u_response * response, void * _config) {
    http_config_t * config = (http_config_t *) _config;

    // get channel number from the url /api/voltage/:channel
    int channel = atoi(u_map_get(request->map_url, "channel"));
    syslog(LOG_INFO, "Trying to set voltage on channel: %d", channel);

    // get voltage from the request data,
    // data must json formatted as follows '{"voltage": "0x3FFF"}' or '{"voltage": 16383}'
    unsigned16 voltage_dac;
    json_t * json_body = ulfius_get_json_body_request(request, NULL);
    syslog(LOG_INFO, "Set voltage request body, \n%s", json_dumps(json_body, 0));
    json_t * j_voltage_dac = json_object_get(json_body, "voltage_dac");
    if (j_voltage_dac == NULL){
        ulfius_set_string_body_response(response, 400, "Wrong request body. Voltage must be set\n");
        json_decref(json_body);
        return U_CALLBACK_CONTINUE;
    }
    if (json_is_integer(j_voltage_dac)){
        voltage_dac = (unsigned16)json_integer_value(j_voltage_dac);
    } else if (json_is_string(j_voltage_dac)){
        voltage_dac = (unsigned16)strtol(json_string_value(j_voltage_dac), NULL, 0);
    } else {
        ulfius_set_string_body_response(response, 400, "Wrong request body. Voltage must be integer or hexadecimal string\n");
        json_decref(json_body);
        return U_CALLBACK_CONTINUE;
    }

    // create set voltage operation and write it to the pipe
    req_t req = { Set, channel, voltage_dac };
    write(config->req_fd, &req, sizeof(req_t));
    ulfius_set_string_body_response(response, 200, "Ok\n");
    json_decref(json_body);
    return U_CALLBACK_CONTINUE;
}

void * start_http_server(void * _config) {
    struct _u_instance instance;
    http_config_t * config = (http_config_t *)_config;
    printf("Web server port: %d\n", config->port);

    if (ulfius_init_instance(&instance, config->port, NULL, NULL) != U_OK) {
        syslog(LOG_ERR, "Error while initializing http server, abort");
        return NULL;
    }
    
    ulfius_add_endpoint_by_val(&instance, "GET", "/api", "/voltage/:channel", 0, &callback_get_voltage, config);
    ulfius_add_endpoint_by_val(&instance, "POST", "/api", "/voltage/:channel", 0, &callback_set_voltage, config);

    if (ulfius_start_framework(&instance) == U_OK) {
        getchar();
    } else {
        syslog(LOG_ERR, "Error while starting web server");
    }

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);
    return NULL;
}
