#include "MQTTHandler.h"

char *msgbuf = NULL;

void MQTTHandler::publish_callback(void** unused, struct mqtt_response_publish *published) 
{
    /* note that published->topic_name is NOT null-terminated (here we'll change it to a c-string) */
    //char* topic_name = (char*) malloc(published->topic_name_size + 1);
    memcpy(::msgbuf, published->topic_name, published->topic_name_size);
    ::msgbuf[published->topic_name_size] = '\0';

    printf("Received publish('%s'): %s\n", ::msgbuf, (const char*) published->application_message);

    frc::SmartDashboard::PutString ("Message", std::string ((char *) published->application_message));

    //free(topic_name);
}

MQTTHandler::MQTTHandler ()
{
    if (!::msgbuf)
    {
        ::msgbuf = (char *) calloc (32, sizeof (char));
    }
}

MQTTHandler::MQTTHandler (std::string addrin, std::string portin, std::string topicin)
{
    if (!::msgbuf)
    {
        ::msgbuf = (char *) calloc (32, sizeof (char));
    }
    init (addrin, portin, topicin);
}

int MQTTHandler::init (std::string addrin, std::string portin, std::string topicin)
{
    char* addr = (char*) addrin.c_str();
    char* port = (char*) portin.c_str();
    char* topic = (char*) topicin.c_str();
    
    /* open the non-blocking TCP socket (connecting to the broker) */
    sockfd = open_nb_socket(addr, port);


    if (sockfd == -1) {
        // perror("Failed to open socket: ");
        return -1;
    }

    mqtt_init(&client, sockfd, sendbuf, sizeof(sendbuf), recvbuf, sizeof(recvbuf), publish_callback);
    /* Create an anonymous session */
    const char* client_id = NULL;
    /* Ensure we have a clean session */
    uint8_t connect_flags = MQTT_CONNECT_CLEAN_SESSION;
    /* Send connection request to the broker. */
    mqtt_connect(&client, client_id, NULL, NULL, 0, NULL, NULL, connect_flags, 400);

    /* check that we don't have any errors */
    if (client.error != MQTT_OK) {
        //fprintf(stderr, "error: %s\n", mqtt_error_str(client.error));
        return -2;
    }

     mqtt_subscribe(&client, topic, 0);
}

float MQTTHandler::getDistance ()
{
    std::string temp = "";
    int i = 0;
    while (msgbuf[i] != ' ')
    {
        temp += msgbuf[i];
        if (i > MSG_BUF_SIZE - 1)
        {
            return -INFINITY;
        }
    }
    return stof (temp);
}

float MQTTHandler::getAngle ()
{
    std::string temp = "";
    int i = 0;
    bool flag = false;
    while (msgbuf[i] != 'N')
    {
        if (flag)
        {
            temp += msgbuf[i];
        }
        else if (msgbuf[i] == ' ')
        {
            flag = true;
        }
        if (i > MSG_BUF_SIZE - 1)
        {
            return -INFINITY;
        }
    }
    return stof (temp);
}

int MQTTHandler::open_nb_socket(char* addr, char* port) {
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

std::string MQTTHandler::getMessage ()
{
    
}

void MQTTHandler::exit_example(int status, int sockfd, pthread_t *client_daemon)
{
}

void MQTTHandler::update ()
{
    mqtt_sync (&client);
}