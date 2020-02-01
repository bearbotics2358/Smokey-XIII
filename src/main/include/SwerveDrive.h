
#pragma once

#include "SwerveModule.h"
#include "Prefs.h"

class SwerveDrive // Class to handle the kinematics of Swerve Drive
{
    public:
        SwerveDrive(SwerveModule *FL_Ptr, SwerveModule *FR_Ptr, SwerveModule *BL_Ptr, SwerveModule *BR_Ptr);

        void swerveUpdate(float xIn, float yIn, float zIn, float gyroIn, bool fieldOriented); // Updates Swerve Modules for swerve drive
        float lockZ(float gyro);

        void crabDriveUpdate(float xIn, float yIn, float gyroIn); // clutzy from club penguin

        void driveDistance(float dist, float direction); // dist in inches and angle 0-360
        void resetDrive();
        float getAvgDistance(void);

        void turnToAngle(float speed, float angle); 
    private:

        SwerveModule *FL_Module;
        SwerveModule *FR_Module;
        SwerveModule *BL_Module;
        SwerveModule *BR_Module;

        frc2::PIDController anglePID;
        frc2::PIDController jenkinsTheCrabPID; // blame kordt

        float holdAngle;
        bool crabs; // if we're in crab drive mode

        const float DRIVE_LENGTH = 29.75;
        const float DRIVE_WIDTH = 29.75;
};