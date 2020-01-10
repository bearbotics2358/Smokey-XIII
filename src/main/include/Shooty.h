
#pragma once

#include <rev/CANSparkMax.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>

class Shooty // Class to handle the kinematics of Swerve Drive
{
    public:
        Shooty(int shootw1, int shootw2);
        
       
    private:
        rev::CANSparkMax SWheel1;
        rev::CANSparkMax SWheel2;


        
};