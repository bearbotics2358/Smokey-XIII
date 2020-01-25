
#pragma once
 
#include <frc/TimedRobot.h> // ignore include error
#include "SwerveModule.h" // SwerveModule lower level class
#include <frc/Joystick.h> // Joystick (logitech 2-axis flightstick probably)
#include "SwerveDrive.h"

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
  private: 

    SwerveModule a_FLModule;
    SwerveModule a_FRModule;
    SwerveModule a_BLModule;
    SwerveModule a_BRModule;
     
    frc::Joystick joystickOne; // 2D flightstick (Logitech Attack 3?)

    frc::Joystick a_buttonbox;

    // Swerve Drive object
    SwerveDrive a_swerveyDrive;

    // SwerveModule testModule; // Temporary module object
};
