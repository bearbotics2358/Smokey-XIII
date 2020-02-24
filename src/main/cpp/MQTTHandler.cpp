#include "MQTTHandler.h"

struct
{
    float distance;
    float angle;
} data;

int MQTTHandler::open_nb_socket (const char *addr, const char *port)
{
    int sockfd = socket (AF_INET, SOCK_STREAM | O_NONBLOCK, 0); // IPv4, byte stream, non-blocking socket
    if (sockfd == -1)
    {
        return -1;
    }

    struct sockaddr_in addrs;
    addrs.sin_family = AF_INET;
    addrs.sin_port = htons (atoi (port)); // Convert to right endianness
    addrs.sin_addr.s_addr = inet_addr (addr);

    int ret = connect (sockfd, (struct sockaddr *)&addrs, sizeof (addrs));

	if (ret != 0 && errno != EINPROGRESS)
	{
		return -1;
	}

	struct pollfd mfd
	{
		sockfd,		// socket fd
		(short) POLLIN,	// wait for read
		(short) 0
	};

	poll (&mfd, 1, 100);

	int flags = fcntl (sockfd, F_GETFL, 0);
	int ret2 = fcntl (sockfd, F_SETFL, flags & (~O_NONBLOCK));

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

    printf ("address %s", rcdata->addres);
    printf ("befor socket");

    int sockfd = MQTTHandler::open_nb_socket (rcdata->addres, rcdata->port);
    if (sockfd == -1)
    {
        return;
    }

    printf ("before reinit");

    mqtt_reinit (client, sockfd, rcdata->sendbuf, rcdata->sendbuf_size, rcdata->recvbuf, rcdata->recvbuf_size);

    printf ("before reconnect");

    mqtt_connect (client, NULL, NULL, NULL, 0, NULL, NULL, MQTT_CONNECT_CLEAN_SESSION, 5);

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
    strncpy ((char *) &rcdata.addres, addrin.c_str (), 15);
    strncpy ((char *) &rcdata.port, portin.c_str (), 7);
    strncpy ((char *) &rcdata.topic, topicin.c_str (), 1023);
    rcdata.sendbuf = sendbuf;
    rcdata.sendbuf_size = sizeof(sendbuf);
    rcdata.recvbuf = recvbuf;
    rcdata.recvbuf_size = sizeof(recvbuf);

    mqtt_init_reconnect (&client, reconnect_callback, &rcdata, publish_callback);

    mqtt_sync (&client);

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

void MQTTHandler::injectError ()
{
	client.error = MQTT_ERROR_SOCKET_ERROR;
}
