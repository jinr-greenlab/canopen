#include <stdio.h>
#include <ulfius.h>
#include <pthread.h>
#include <string.h>
#include <syslog.h>
#include <jansson.h>

#define PORT 5000

typedef struct board_state_t {
  int voltage[128];
} board_state_t;

typedef struct web_config_t {
  int port;
  int op_pipe;
  board_state_t * board_state;
} web_config_t;

typedef struct operator_config_t {
  int op_pipe;
  board_state_t * board_state;
} operator_config_t;

typedef struct set_voltage_op_t {
  int channel;
  int voltage;
} set_voltage_op_t;

static int callback_get_voltage(const struct _u_request * request, struct _u_response * response, void * user_data) {
  board_state_t * state = (board_state_t *) user_data;
  json_t * json_body = NULL;
  int channel = atoi(u_map_get(request->map_url, "channel"));
  json_body = json_object();
  json_object_set_new(json_body, "channel", json_integer(channel));
  // int ADC_code = func read ADC code board's
  int upper = 4200000;
  int lower = 10000;
  int ADC_code = (rand() % (upper - lower + 1)) + lower;
  json_object_set_new(json_body, "ADC_code", json_integer(ADC_code));  //state->voltage[channel]
  ulfius_set_json_body_response(response, 200, json_body);
  syslog(LOG_ERR, "Get voltage response, \n%s", json_dumps(json_body, 0));
  json_decref(json_body);
  printf("READ: Channel %d --- ADC code %d\n", channel, ADC_code);
  return U_CALLBACK_CONTINUE;
}

static int callback_set_voltage(const struct _u_request * request, struct _u_response * response, void * user_data) {
  int channel = atoi(u_map_get(request->map_url, "channel"));
  int voltage;
  syslog(LOG_ERR, "Trying to set voltage on channel: %d", channel);
  json_t * json_body = ulfius_get_json_body_request(request, NULL);
  syslog(LOG_ERR, "Set voltage request body, \n%s", json_dumps(json_body, 0));
  json_t * j_voltage = json_object_get(json_body, "DAC_code");
  if (j_voltage == NULL){
    ulfius_set_string_body_response(response, 400, "Wrong request body. Voltage must be set\n");
    json_decref(json_body);
    return U_CALLBACK_ERROR;
  }
  if (json_is_integer(j_voltage)){
    voltage = (int)json_integer_value(j_voltage);
  } else if (json_is_string(j_voltage)){
    voltage = (int)strtol(json_string_value(j_voltage), NULL, 0);
  } else {
    ulfius_set_string_body_response(response, 400, "Wrong request body. Voltage must be integer or hexadecimal string\n");
    json_decref(json_body);
    return U_CALLBACK_CONTINUE;
  }
  set_voltage_op_t op = { channel, voltage };
  write(*(int *)user_data, &op, sizeof(set_voltage_op_t));
  ulfius_set_string_body_response(response, 200, "Ok\n");
  json_decref(json_body);
  printf("SET: Channel %d --- Voltage %d\n", channel, voltage);
  return U_CALLBACK_CONTINUE;
}


void *start_web_server(void * _config) {
  struct _u_instance instance;
  web_config_t * config = (web_config_t *)_config;

  if (ulfius_init_instance(&instance, config->port, NULL, NULL) != U_OK) {
    syslog(LOG_ERR, "Error while initializing web server, abort");
    return NULL;
  }

  ulfius_add_endpoint_by_val(&instance, "GET", "/api", "/voltage/:channel", 0, &callback_get_voltage, config->board_state);
  ulfius_add_endpoint_by_val(&instance, "POST", "/api", "/voltage/:channel", 0, &callback_set_voltage, &(config->op_pipe));

  if (ulfius_start_framework(&instance) == U_OK) {
    getchar();
  } else {
    syslog(LOG_ERR, "Error while starting web server");
  }

  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);

  return NULL;
}

void *start_operator(void * _config) {
  operator_config_t * config = (operator_config_t *)_config;
  set_voltage_op_t op;
  int rsize;
  while(1) {
    rsize = read(config->op_pipe, &op, sizeof(set_voltage_op_t));
    if (rsize != sizeof(set_voltage_op_t)){
      syslog(LOG_ERR, "Error while read operation from pipe");
    }
    syslog(LOG_INFO, "Set voltage op received: channel: %d voltage: %d", op.channel, op.voltage);
    config->board_state->voltage[op.channel] = op.voltage;
    usleep(100000);
  }
}


int main(void) {
  openlog("Demo", LOG_CONS, LOG_USER);
  pthread_t web_server;
  pthread_t operator;
  board_state_t * board_state = malloc(sizeof(board_state_t));
  int ret;

  for (int i = 0; i < 128; i++){
    board_state->voltage[i] = 0;
  }

  int pipefd[2];
  if (pipe(pipefd) < 0) {
    exit(EXIT_FAILURE);
  }

  web_config_t web_config = { PORT, pipefd[1], board_state };
  operator_config_t operator_config = { pipefd[0], board_state };

  fprintf(stderr, "Port: %d\n", web_config.port);
  fprintf(stderr, "Pipe write desc: %d\n", web_config.op_pipe);

  fprintf(stderr, "Starting web server thread\n");
  ret = pthread_create(&web_server, NULL, start_web_server, &web_config);
  if (ret < 0) {
    fprintf(stderr, "Error while starting web server\n");
    exit(EXIT_FAILURE);
  }

  fprintf(stderr, "Starting op reader thread\n");
  ret = pthread_create(&operator, NULL, start_operator, &operator_config);
  if (ret < 0) {
    fprintf(stderr, "Error while starting op reader\n");
    exit(EXIT_FAILURE);
  }

  pthread_join(web_server, NULL);
  exit(EXIT_SUCCESS);
}
