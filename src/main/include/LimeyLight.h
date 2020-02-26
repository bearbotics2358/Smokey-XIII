#ifndef LAPTOP
#pragma once

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Prefs.h"
#include <frc/controller/PIDController.h> 

#define GET_LIMELIGHT_VALUE(table, key) (table).GetTable("limelight")->GetNumber((key), 0.0f)

struct tableVal
{
    float dist;
    float value;
}

class LimeyLight
{
    public:
        LimeyLight ();
        ~LimeyLight ();
        float getDist () const;
        float getXAngleShooter (const std::vector<float> velocity, const float gyro) const;
        float getYAngleShooter () const;
        float getVelocityShooter () const;
        bool isTarget () const;
        float getAngleX () const;
        float getAngleY () const;
        float getArea () const;
        float getAngleTarget () const;
        float getWidth () const;
        void ledOn();
        void ledOff();
        void cameraMode(int whichCam);
        void printValues(); 
        float calcZAxis();
        
    private:
        nt::NetworkTableInstance table;
        frc2::PIDController lemonLight; 
        void setTableVal (const int index, const float dist, const float value);
        struct tableVal tableVals[LOOKUP_TABLE_LEN];
        struct tableVal tableSlope[LOOKUP_TABLE_LEN - 1];
};
#endif