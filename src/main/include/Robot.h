
#pragma once
 
#include <frc/TimedRobot.h> // ignore include error
#include "SwerveModule.h" // SwerveModule lower level class
#include <frc/Joystick.h> // Joystick (logitech 2-axis flightstick probably)
#include "MQTTHandler.h"

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
    SwerveModule testModule; // Temporary module object

    frc::Joystick joystickOne; // 2D flightstick (Logitech Attack 3?)
    MQTTHandler handler;
};
