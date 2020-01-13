
#pragma once

#include <rev/CANSparkMax.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>

class SwerveModule // Handles steering and driving of each Swerve Module
{
    public:
        SwerveModule(int driveID, int steerID, int steerEncID); // CAN IDs, analog port for steer encoder
        
        void setDriveSpeed(float target); // update drive speed
        void setSteerSpeed(float target); // update steer speed

        float getDistance(void); // Returns position of the distance encoder
        void resetDriveEncoder(void); // Zeros the distance encoder

        float getAngleRaw(void);
        float getAngle(void);

        void driveDistance(float current, float setpoint);
    private:
        rev::CANSparkMax driveMotor;
        rev::CANSparkMax steerMotor;

        rev::CANEncoder driveEnc;

        frc::AnalogInput rawSteerEnc;
        frc::AnalogEncoder steerEnc; // placeholder, may change wiring

        frc2::PIDController drivePID;
        frc2::PIDController steerPID;
};