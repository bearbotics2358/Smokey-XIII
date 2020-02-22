
#pragma once

#include "MQTTHandler.h"
#include <frc/TimedRobot.h> // "Timed Robot" template
#include "SwerveModule.h" // Swerve modules
#include <frc/Joystick.h> // Joystick 
#include "SwerveDrive.h" // Swerve kinematics
#include "JrimmyGyro.h" // Gyro wrapper class; takes in I2C port
#include "LimeyLight.h"
#include "CFS.h"
#include "Autonomous.h"

class Robot : public frc::TimedRobot 
{
  public:
    Robot();
    void RobotInit();
    void RobotPeriodic();

    void DisabledInit();
    void DisabledPeriodic();

    void AutonomousInit();
    void AutonomousPeriodic();

    void TeleopInit();
    void TeleopPeriodic();

    void TestInit();
    void TestPeriodic();
  private: 
    JrimmyGyro a_Gyro;
    SwerveModule a_FLModule;
    SwerveModule a_FRModule;
    SwerveModule a_BLModule;
    SwerveModule a_BRModule;
     
    frc::Joystick joystickOne; // 3D flightstick (Logitech Attack 3?)
    frc::Joystick a_xBoxController; 
    frc::Joystick a_buttonbox;

    // Swerve Drive object
    SwerveDrive a_swerveyDrive;

    // Lime Light Object
    LimeyLight a_LimeyLight; 

    // MQTTHandler handler;
    CFS a_CFS; 

    Autonomous a_JAutonomous;

};
