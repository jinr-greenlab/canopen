#define PORT 5000

typedef struct http_config_t {
    // TCP port to listen to serve HTTP
    int port;
    int req_fd;
    int resp_fd;
} http_config_t;

void * start_http_server(void * _config);
