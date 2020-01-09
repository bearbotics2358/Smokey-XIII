
#pragma once
 
#include <frc/TimedRobot.h> // ignore include error

class Robot : public frc::TimedRobot 
{
 public:
  void RobotInit();

  void AutonomousInit();
  void AutonomousPeriodic();

  void TeleopInit();
  void TeleopPeriodic();

  void TestInit();
  void TestPeriodic();
};
