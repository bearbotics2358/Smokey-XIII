
#pragma once

#include "SwerveModule.h"
#include "Prefs.h"

class SwerveDrive // Class to handle the kinematics of Swerve Drive
{
    public:
        SwerveDrive(SwerveModule *FL_Ptr, SwerveModule *FR_Ptr, SwerveModule *BL_Ptr, SwerveModule *BR_Ptr);
        float lockZ(float gyro);

        void crabDriveUpdate(float xIn, float yIn, float gyroIn); // clutzy from club penguin


        
        void swerveUpdate(float xIn, float yIn, float zIn, float gyroIn, bool fieldOriented); // Updates Swerve Modules for swerve drive
            /*
                xIn = x asix on joystick
                yIn = y axis on joystick
                zIn =  z axis on joystick
                gyroIn = sensor
                fieldOriented = are you looking at the field head on or not? 

            */

        void driveDistance(float dist, float direction); // dist in inches and angle 0-360
        void resetDrive();
        float getAvgDistance(void); // baka-47

        void turnToAngle(float gyro, float angle); 
        
        void makeShiftTurn(float speed);

        void GoToTheDon(float speed, float direction, float distance);
    private:

        SwerveModule *FL_Module;
        SwerveModule *FR_Module;
        SwerveModule *BL_Module;
        SwerveModule *BR_Module;
        
        frc2::PIDController anglePID;
        frc2::PIDController jenkinsTheCrabPID; // blame kordt

        float holdAngle;
        bool crab; // if we're in crab drive mode

        const float DRIVE_LENGTH = 29.75;
        const float DRIVE_WIDTH = 29.75;

        const float PI = M_PI;

        /* frc::AnalogInput FL_Input;
        frc::AnalogInput FR_Input;
        frc::AnalogInput BL_Input;
        frc::AnalogInput BR_Input;

        frc::AnalogEncoder FL_Encoder; 
        frc::AnalogEncoder FR_Encoder; 
        frc::AnalogEncoder BL_Encoder; 
        frc::AnalogEncoder BR_Encoder; */
};