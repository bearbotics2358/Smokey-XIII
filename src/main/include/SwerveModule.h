
#pragma once

#include <rev/CANSparkMax.h>
#include <frc2/PIDController.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>


class SwerveModule // Handles steering and driving of the modules
{
    public:
        SwerveModule(int driveID, int steerID, int driveEncID, int steerEncID);
    private:
        rev::CANSparkMax driveMotor;
        rev::CANSparkMax steerMotor;

        frc::AnalogInput rawDriveEnc;
        frc::AnalogInput rawSteerEnc;

        frc::AnalogEncoder driveEnc; // placeholder, may change wiring
        frc::AnalogEncoder steerEnc; 

        frc2::PIDController drivePID;
        frc2::PIDController steerPID;
};