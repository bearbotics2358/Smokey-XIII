#pragma once

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

#include <frc/smartdashboard/SmartDashboard.h>

#define GET_LIMELIGHT_VALUE(table, key) (table).GetTable("limelight")->GetNumber((key), 0.0f)

class LimeyLight
{
    public:
        LimeyLight ();
        ~LimeyLight ();
        float getDist () const;
        float getAngleShooter () const;
        float getAngleX () const;
        float getAngleY () const;
        float getArea () const;
        float getAngleTarget () const;
        float getWidth () const;
        void ledOn();
        void ledOff();
        void cameraMode(int whichCam);
        void printValues(); 
        
    private:
        nt::NetworkTableInstance table;
};