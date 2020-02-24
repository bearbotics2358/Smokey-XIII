#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string>
#include <poll.h>
#include <errno.h>
#include <signal.h>
#include "mqtt.h"
#include "Prefs.h"

typedef struct
{
    char addres[16];
    char port[8];
    char topic[1024];
    uint8_t *sendbuf;
    size_t sendbuf_size;
    uint8_t *recvbuf;
    size_t recvbuf_size;
} reconnect_data;

void sigpipeHandler (int signal);

class MQTTHandler
{
    public:
        MQTTHandler ();
        MQTTHandler (std::string addrin, std::string portin, std::string topicin);
        int init (std::string addrin, std::string portin, std::string topicin);
        bool update ();
        bool noErrors () const;
        int mqttPublish (std::string msg, std::string topic);
	    void injectError ();
        static float getDistance ();
        static float getAngle ();
    private:
        static int open_nb_socket (const char *addr, const char *port);
        static void publish_callback (void **unused, struct mqtt_response_publish *published);
        static void reconnect_callback (struct mqtt_client *client, void **state);
        struct mqtt_client client;
        reconnect_data rcdata;
        uint8_t sendbuf[SEND_BUF_LEN];
        uint8_t recvbuf[RECV_BUF_LEN];
        int sockfd;
        bool errorF;
};
