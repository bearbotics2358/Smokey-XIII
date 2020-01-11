
#pragma once

#include <rev/CANSparkMax.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>

class SwerveModule // Handles steering and driving of the modules
{
    public:
        SwerveModule(int driveID, int steerID, int steerEncID);
        
        void setDriveSpeed(float target);
        void setSteerSpeed(float target);
    private:
        rev::CANSparkMax driveMotor;
        rev::CANSparkMax steerMotor;

        frc::AnalogInput rawSteerEnc;

        frc::AnalogEncoder steerEnc; // placeholder, may change wiring

        frc2::PIDController drivePID;
        frc2::PIDController steerPID;
};