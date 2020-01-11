
#pragma once

#include <rev/CANSparkMax.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>

class Shooty // Class to handle the kinematics of Swerve Drive
{
    public:
        Shooty(int shootw1, int shootw2, int shootwb);
        
       
    private:
        rev::CANSparkMax a_SWheel1;
        rev::CANSparkMax a_SWheel2;
        rev::CANSparkMax a_SWheelb;



        
};