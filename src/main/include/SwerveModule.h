
#pragma once

#include <rev/CANSparkMax.h>
#include <frc/PIDController.h>
#include <frc/Encoder.h>

class SwerveModule // Handles steering and driving of the modules
{
    public:
        SwerveModule(int driveID, int steerID);
    private:
        rev::CANSparkMax *driveMotor;
        rev::CANSparkMax *steerMotor;

        frc::Encoder *driveEnc; // placeholder, may change wiring
        frc::Encoder *steerEnc; 

        frc::PIDController *drivePID;
        frc::PIDController *steerPID;
};