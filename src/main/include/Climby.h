
#pragma once

#include <rev/CANSparkMax.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>

class Climby // Class to handle the kinematics of Swerve Drive
{
    public:
        Climby(int climb1);
        
       
    private:
        rev::CANSparkMax a_climb1;



        
};