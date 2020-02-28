#include "ComsMultithread.h"

ComsMultithread::ComsMultithread (MQTTHandler *mqttHandler, CANHandler *canHandler)
: a_mqttHandler(mqttHandler),
a_canHandler(canHandler),
mqttMutex(),
canMutex()
{
    std::thread (ComsMultithread);
}

float ComsMultithread::getVDist () const
{
    return a_mqttHandler->distance;
}

float ComsMultithread::getVAngle () const
{
    return a_mqttHandler->angle;
}

void ComsMultithread::sendVMsg (std::string msg, std::string topic)
{
    mqttMutex.lock ();
    a_mqttHandler->publish (msg, topic);
    mqttMutex.unlock ();
}

float ComsMultithread::getCanData (const int which)
{
    canMutex.lock ();
    float out = a_canHandler->getData (which);
    canMutex.unlock ();
    return out;
}

void ComsMultithread::operator() ()
{
    for (;;)
    {
        mqttMutex.lock ();
        a_mqttHandler->update ();
        mqttMutex.unlock ();
        canMutex.lock ();
        a_canHandler->update ();
        canMutex.unlock ();
        usleep (20000);
    }
}