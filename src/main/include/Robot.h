
#pragma once
 
<<<<<<< HEAD
#include <frc/TimedRobot.h> // ignore include error
#include "SwerveModule.h" // SwerveModule lower level class
#include <frc/Joystick.h> // Joystick (logitech 2-axis flightstick probably)
#include "MQTTHandler.h"
=======
#include <frc/TimedRobot.h> // "Timed Robot" template
#include "SwerveModule.h" // Swerve modules
#include <frc/Joystick.h> // Joystick 
#include "SwerveDrive.h" // Swerve kinematics
#include "JrimmyGyro.h" // Gyro wrapper class; takes in I2C port
#include "LimeyLight.h"
>>>>>>> master

class Robot : public frc::TimedRobot 
{
  public:
    Robot();
    void RobotInit();

    void AutonomousInit();
    void AutonomousPeriodic();

    void TeleopInit();
    void TeleopPeriodic();

    void TestInit();
    void TestPeriodic();

    void RobotPeriodic();
  private: 
    JrimmyGyro a_Gyro;
    SwerveModule a_FLModule;
    SwerveModule a_FRModule;
    SwerveModule a_BLModule;
    SwerveModule a_BRModule;
     
    frc::Joystick joystickOne; // 3D flightstick (Logitech Attack 3?)

    frc::Joystick a_buttonbox;

    // Swerve Drive object
    SwerveDrive a_swerveyDrive;

    // Lime Light Object
    LimeyLight a_LimeyLight; 

<<<<<<< HEAD
    frc::Joystick joystickOne; // 2D flightstick (Logitech Attack 3?)
    MQTTHandler handler;
=======
>>>>>>> master
};
