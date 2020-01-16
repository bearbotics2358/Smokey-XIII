
#pragma once

#include <rev/CANSparkMax.h>
#include "ctre/Phoenix.h"
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>

class Shooty
{
    public:
        Shooty(int shootw1, int shootw2);
        void BasicShoot();
        double GetSpeed();
        void SetSpeed(double sped);
        void SetSpeed();
        void SetShootPID1(float P, float I, float D);
        void SetShootPID2(float P, float I, float D);
        void VelocityShoot(float sped);   
        double GetVelocity1();
        double GetVelocity2();     
        double GetVoltage1();
        double GetVoltage2();

       
    private:
        WPI_TalonSRX a_SWheel1;
        WPI_TalonSRX a_SWheel2;


        double speed;


        
};