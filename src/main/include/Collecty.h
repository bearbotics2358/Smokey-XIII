
#pragma once

#include <rev/CANSparkMax.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>

class Collecty // Class to handle the kinematics of Swerve Drive
{
    public:
        Collecty(int intake, int mover, int arm);
        
       
    private:
        rev::CANSparkMax a_intake;
        rev::CANSparkMax a_belts;
        rev::CANSparkMax a_arm;



        
};