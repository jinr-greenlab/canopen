#include <syslog.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <common.h>
#include <http.h>
#include <can.h>
#include <master_header.h>

int main(int argc, char** argv)
{
    openlog("Demo", LOG_CONS, LOG_USER);
    char * path_config = clparser(argc, argv);
    int req_pipe[2];
    int resp_pipe[2];
    int ret;

    pthread_t http_server;

    if (pipe2(req_pipe, O_NONBLOCK) < 0) exit(EXIT_FAILURE);
    if (pipe2(resp_pipe, O_NONBLOCK) < 0) exit(EXIT_FAILURE);

    // can master reads from req pipe and writes to resp pipe
    master_config_t master_config = { path_config, req_pipe[0], resp_pipe[1] };
    // http server writes to req pipe and reads from resp pipe
    http_config_t http_config = { PORT, req_pipe[1], resp_pipe[0] };

    printf("Starting http server thread\n");
    ret = pthread_create(&http_server, NULL, start_http_server, &http_config);
    if (ret < 0) {
        fprintf(stderr, "Error while starting http server\n");
        exit(EXIT_FAILURE);
    }

    start_master(&master_config);

    pthread_join(http_server, NULL);
    return EXIT_SUCCESS;
}
