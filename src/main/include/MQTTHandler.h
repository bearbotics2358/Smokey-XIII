#pragma once

#include "mqtt.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string>
#include <frc/smartdashboard/SmartDashboard.h>

typedef struct
{
    char *addres;
    char *port;
    char *topic;
    uint8_t *sendbuf;
    size_t sendbuf_size;
    uint8_t *recvbuf;
    size_t recvbuf_size;
} reconnect_data;


class MQTTHandler
{
    public:
        MQTTHandler ();
        MQTTHandler (std::string addrin, std::string portin, std::string topicin);
        int init (std::string addrin, std::string portin, std::string topicin);
        void update ();
        int mqttPublish (std::string msg, std::string topic);
        float getDistance () const;
        float getAngle () const;
    private:
        static int open_nb_socket (char *addr, char *port);
        static void publish_callback(void **unused, struct mqtt_response_publish *published);
        static void reconnect_callback(struct mqtt_client *client, void **state);
        struct mqtt_client client;
        reconnect_data rcdata;
        uint8_t sendbuf[2048];
        uint8_t recvbuf[1024];
        int sockfd;
};