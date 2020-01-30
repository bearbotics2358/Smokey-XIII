
#pragma once

#include "SwerveModule.h"
#include "Prefs.h"

class SwerveDrive // Class to handle the kinematics of Swerve Drive
{
    public:
        SwerveDrive(SwerveModule *FL_Ptr, SwerveModule *FR_Ptr, SwerveModule *BL_Ptr, SwerveModule *BR_Ptr);
        
        void swerveUpdate(float xIn, float yIn, float zIn, float gyroIn, bool fieldOriented); // Updates Swerve Modules for swerve drive
    private:
        bool needsAngOpt(float currentAngle, float targetAngle); // reverse motor check, returns true if needs reversing

        SwerveModule *FL_Module;
        SwerveModule *FR_Module;
        SwerveModule *BL_Module;
        SwerveModule *BR_Module;

        const float DRIVE_LENGTH = 29.75;
        const float DRIVE_WIDTH = 29.75;
};