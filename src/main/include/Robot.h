
#pragma once
 
#include <frc/TimedRobot.h> // ignore include error
#include "SwerveModule.h" // SwerveModule lower level class
#include <frc/Joystick.h> // Joystick (logitech 3-axis flightstick probably)

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
    SwerveModule testModule; // Temporary module object

    frc::Joystick joystickOne;
};
