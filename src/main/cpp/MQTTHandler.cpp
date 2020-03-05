#include "MQTTHandler.h"

void sigpipeHandler (int signal)
{
    printf ("Recieved signal SIGPIPE");
}

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

	// int flags = fcntl (sockfd, F_GETFL, 0);
	// int ret2 = fcntl (sockfd, F_SETFL, flags & (~O_NONBLOCK));

    return sockfd;
}

void MQTTHandler::publish_callback (void** state, struct mqtt_response_publish *published) 
{    
    MQTTHandler *h_instance = (MQTTHandler *) *state;
    sscanf ((char *) published->application_message, "%f %f", &(h_instance->distance), &(h_instance->angle));
}

void MQTTHandler::reconnect_callback (struct mqtt_client *client, void **state)
{
    reconnect_data *rcdata = *((reconnect_data **) state);

    if (client->socketfd != 0)
    {
        close (client->socketfd);
    }
    client->socketfd = 0;

    printf ("address %s", rcdata->addres);
    printf ("befor socket");

    int sockfd = MQTTHandler::open_nb_socket (rcdata->addres, rcdata->port);
    if (sockfd == -1)
    {
        return;
    }

    mqtt_reinit (client, sockfd, rcdata->sendbuf, rcdata->sendbuf_size, rcdata->recvbuf, rcdata->recvbuf_size);
    mqtt_connect (client, NULL, NULL, NULL, 0, NULL, NULL, MQTT_CONNECT_CLEAN_SESSION, 5);
    mqtt_subscribe (client, rcdata->topic, 0);
}

// unsafe, dont use
MQTTHandler::MQTTHandler ()
{
    syncSafe = false;
    retrySignal ();
}

MQTTHandler::MQTTHandler (std::string addrin, std::string portin, std::string topicin)
{
    init (addrin, portin, topicin);
}

int MQTTHandler::init (std::string addrin, std::string portin, std::string topicin)
{
    errorF = false;
    syncSafe = false;
    retrySignal ();

    strncpy ((char *) &rcdata.addres, addrin.c_str (), 15);
    strncpy ((char *) &rcdata.port, portin.c_str (), 7);
    strncpy ((char *) &rcdata.topic, topicin.c_str (), 1023);
    rcdata.sendbuf = sendbuf;
    rcdata.sendbuf_size = sizeof(sendbuf);
    rcdata.recvbuf = recvbuf;
    rcdata.recvbuf_size = sizeof(recvbuf);

    client.socketfd = 0;
    mqtt_init_reconnect (&client, reconnect_callback, &rcdata, publish_callback);
    client.publish_response_callback_state = this;

    mqtt_sync (&client);

    if (client.error != MQTT_OK) {
        return -2;
    }
    return 0;
}

bool MQTTHandler::retrySignal ()
{
    if (!syncSafe)
    {
        if (signal (SIGPIPE, sigpipeHandler) != SIG_ERR)
        {
             syncSafe = true;
             return true;
        }
        else
        {
             return false;
        }
    }
    return true;
}

bool MQTTHandler::update ()
{
    if (!syncSafe)
    {
        return false;
    }
    mqtt_sync (&client);
    if (client.error != MQTT_OK)
    {
        errorF = false;
        return false;
    }
    else
    {
        errorF = true;
    }
    return true;
}

bool MQTTHandler::noErrors () const
{
<<<<<<< HEAD
    return !errorF || syncSafe;
=======
    return errorF && syncSafe;
>>>>>>> f139484ade732917ef3b8cc478ee25e3de6566e9
}

int MQTTHandler::publish (std::string msg, std::string topic)
{
    if (!syncSafe)
    {
        return -1;
    }
    const char *ctopic = (const char *) topic.c_str();
    void *cmsg = (void *) msg.c_str();

    if (mqtt_publish (&client, ctopic, cmsg, msg.length (), MQTT_PUBLISH_RETAIN) != MQTT_OK)
    {
        return -1;
    }
    return 0;
}

void MQTTHandler::injectError ()
{
	client.error = MQTT_ERROR_SOCKET_ERROR;
}
