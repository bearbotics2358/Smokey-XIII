#pragma once

#include <thread>
#include <mutex>
#include <string>
#include <unistd.h>
#include "MQTTHandler.h"
#include "CANHandler.h"
#include "Prefs.h"

class ComsMultithread
{
    public:
        ComsMultithread (MQTTHandler *mqttHandler, CANHandler *canHandler);
        float getVDist () const;
        float getVAngle () const;
        void sendVMsg (std::string msg, std::string topic);
        float getCanData (const int which);
    private:
        void operator() ();
        MQTTHandler *a_mqttHandler;
        CANHandler *a_canHandler;
        std::mutex mqttMutex;
        std::mutex canMutex;
};