#pragma once

#include "mqtt.h"
#include <stdio.h>
#include <sys/types.h>
#if !defined(WIN32)
#include <sys/socket.h>
#include <netdb.h>
#endif
#include <fcntl.h>
#include <string.h>

class MQTTHandler
{
    public:
        MQTTHandler (const std::string addrin, const std::string portin, const std::string topicin);
        std::string getMessage ();
    private:
        int open_nb_socket (const char *addr, const char *port);
        void exit_example(int status, int sockfd, pthread_t *client_daemon);
        struct mqtt_client client;
        uint8_t sendbuf[2048];
        uint8_t recvbuf[1024];
        int sockfd;
};