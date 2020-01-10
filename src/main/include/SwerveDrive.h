
#pragma once

#include "SwerveModule.h"

class SwerveDrive // Class to handle the kinematics of Swerve Drive
{
    public:
        SwerveDrive(SwerveModule *FL_Ptr, SwerveModule *FR_Ptr, SwerveModule *BL_Ptr, SwerveModule *BR_Ptr);
        
        void updateField(float xIn, float yIn, float zIn, float gyroIn); // Field oriented swerve
        void updateRobot(float xIn, float yIn, float zIn); // Robot oriented swerve
    private:
        SwerveModule *FL_Module;
        SwerveModule *FR_Module;
        SwerveModule *BL_Module;
        SwerveModule *BR_Module;

        bool fieldOriented;
        const float PI = 3.14159265;
        const float DEADZONE = 0.15; // Joystick Deadzone

        const float DRIVE_LENGTH = 29.75;
        const float DRIVE_WIDTH = 29.75;
};