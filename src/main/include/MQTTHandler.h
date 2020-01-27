#pragma once

#include "mqtt.h"
#include <stdio.h>
#include <sys/types.h>
#if !defined(WIN32)
#include <sys/socket.h>
#include <netdb.h>
#endif
#include <fcntl.h>
#include <stdlib.h>
#include <string>

class MQTTHandler
{
    public:
        MQTTHandler (std::string addrin, std::string portin, std::string topicin);
        std::string getMessage ();
    private:
        int open_nb_socket (char *addr, char *port);
        void exit_example(int status, int sockfd, pthread_t *client_daemon);
        friend void publish_callback(void **unused, struct mqtt_response_publish *published);
        struct mqtt_client client;
        uint8_t sendbuf[2048];
        uint8_t recvbuf[1024];
        int sockfd;
};