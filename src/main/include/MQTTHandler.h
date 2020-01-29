#pragma once

#include "mqtt.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string>
#include <frc/smartdashboard/SmartDashboard.h>

class MQTTHandler
{
    public:
        MQTTHandler ();
        MQTTHandler (std::string addrin, std::string portin, std::string topicin);
        int init (std::string addrin, std::string portin, std::string topicin);
        std::string getMessage ();
        void update ();
    private:
        int open_nb_socket (char *addr, char *port);
        void exit_example(int status, int sockfd, pthread_t *client_daemon);
        static void publish_callback(void **unused, struct mqtt_response_publish *published);
        struct mqtt_client client;
        uint8_t sendbuf[2048];
        uint8_t recvbuf[1024];
        int sockfd;
};