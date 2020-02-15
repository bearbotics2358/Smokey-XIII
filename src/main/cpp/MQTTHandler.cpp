#include "MQTTHandler.h"

struct
{
    float distance;
    float angle;
} data;

// From mqtt_c examples/sockets
int MQTTHandler::open_nb_socket (char* addr, char* port) {
    struct addrinfo hints = {0};

    hints.ai_family = AF_UNSPEC; /* IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Must be TCP */
    int sockfd = -1;
    int rv;
    struct addrinfo *p, *servinfo;

    /* get address information */
    rv = getaddrinfo(addr, port, &hints, &servinfo);
    if(rv != 0) {
        fprintf(stderr, "Failed to open socket (getaddrinfo): %s\n", gai_strerror(rv));
        return -1;
    }

    /* open the first possible socket */
    for(p = servinfo; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) continue;

        /* connect to server */
        rv = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
        if(rv == -1) continue;
        break;
    }  

    /* free servinfo */
    freeaddrinfo(servinfo);

    /* make non-blocking */
    if (sockfd != -1) fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL) | O_NONBLOCK);

    /* return the new socket fd */
    return sockfd;
}

void MQTTHandler::publish_callback (void** unused, struct mqtt_response_publish *published) 
{    
    sscanf ((char *) published->application_message, "%f %f", &(data.distance), &(data.angle));
}

void MQTTHandler::reconnect_callback (struct mqtt_client *client, void **state)
{
    reconnect_data *rcdata = *((reconnect_data **) state);

    if (client->error != MQTT_ERROR_INITIAL_RECONNECT)
    {
        close (client->socketfd);
    }

    int sockfd = MQTTHandler::open_nb_socket (rcdata->addres, rcdata->port);
    if (sockfd == -1)
    {
        return;
    }

    printf ("before reinit");

    mqtt_reinit (client, sockfd, rcdata->sendbuf, rcdata->sendbuf_size, rcdata->recvbuf, rcdata->recvbuf_size);

    printf ("before reconnect");

    mqtt_connect (client, NULL, NULL, NULL, 0, NULL, NULL, MQTT_CONNECT_CLEAN_SESSION, 400);

    printf ("before subscribe");

    mqtt_subscribe (client, rcdata->topic, 0);

    printf ("after subscribe");
}

MQTTHandler::MQTTHandler ()
{

}

MQTTHandler::MQTTHandler (std::string addrin, std::string portin, std::string topicin)
{
    init (addrin, portin, topicin);
}

int MQTTHandler::init (std::string addrin, std::string portin, std::string topicin)
{
    char *addr = (char *) addrin.c_str();
    char *port = (char *) portin.c_str();
    char *topic = (char *) topicin.c_str();
    
    sockfd = open_nb_socket (addr, port);
    if (sockfd == -1) {
        return -1;
    }

    reconnect_data rcdata;
    rcdata.addres = addr;
    rcdata.port = port;
    rcdata.topic = topic;
    rcdata.sendbuf = sendbuf;
    rcdata.sendbuf_size = sizeof(sendbuf);
    rcdata.recvbuf = recvbuf;
    rcdata.recvbuf_size = sizeof(recvbuf);

    mqtt_init_reconnect (&client, reconnect_callback, &rcdata, publish_callback);

    if (client.error != MQTT_OK) {
        return -2;
    }
    return 0;
}

bool MQTTHandler::update ()
{
    mqtt_sync (&client);
    if (client.error != MQTT_OK)
    {
        errorF = false;
        return false;
    }
    return true;
}

bool MQTTHandler::noErrors () const
{
    return errorF;
}

int MQTTHandler::mqttPublish (std::string msg, std::string topic)
{
    const char *ctopic = (const char *) topic.c_str();
    void *cmsg = (void *) msg.c_str();

    if (mqtt_publish (&client, ctopic, cmsg, msg.length (), MQTT_PUBLISH_RETAIN) != MQTT_OK)
    {
        return -1;
    }
    return 0;
}

float MQTTHandler::getDistance ()
{
    return data.distance;
}

float MQTTHandler::getAngle ()
{
    return data.angle;
}