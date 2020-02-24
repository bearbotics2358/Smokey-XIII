#ifndef LAPTOP
#pragma once

#include <rev/CANSparkMax.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>
#include "Prefs.h"
#include <math.h>
#include <frc/smartdashboard/SmartDashboard.h>

class SwerveModule // Handles steering and driving of each Swerve Module
{
    public:
        SwerveModule(int driveID, int steerID, int steerEncID); // CAN IDs, analog port for steer encoder
        
        float getDistance(void); // Returns position of the distance encoder
        void resetDriveEncoder(void); 

        float getAngleRaw(void); // position of steering encoder
        float getAngle(void); // scaled angle between 0 and 360

        void goToPosition(float setpoint); // Position PID control, moves to specified position
        void steerToAng(float setpoint); // Angle PID control

        void setDriveSpeed(float target); // update current
        
        void setSteerSpeed(float target);
        float getDriveSpeed(void);

        float setDriveVelocity(float percent); // Drive Velocity Loop - WIP

        void updateDrivePID(double pNew, double iNew, double dNew);
        void updateSteerPID(double pNew, double iNew, double dNew);

        bool adjustAngle(float targetAngle);

    private:
        rev::CANSparkMax driveMotor;
        rev::CANSparkMax steerMotor;

        rev::CANEncoder driveEnc; // Built-in NEO Encoders
        rev::CANEncoder steerEncNEO; 

        frc::AnalogInput rawSteerEnc;
        frc::AnalogEncoder steerEnc; // placeholder, may change wiring

        frc2::PIDController drivePID;
        frc2::PIDController steerPID;

        
};
#endif