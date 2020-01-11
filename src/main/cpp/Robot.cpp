
#include "Robot.h"
#include "Prefs.h"

Robot::Robot():
testModule(TEST_DRIVE_ID, TEST_STEER_ID, 0, 1), // fix encoders at some point
joystickOne(JOYSTICK_PORT)
{

}

void Robot::RobotInit() 
{

}

void Robot::AutonomousInit() 
{

}

void Robot::AutonomousPeriodic() 
{
    
}

void Robot::TeleopInit() 
{

}

void Robot::TeleopPeriodic() 
{
    float scalar = 0.2;

    testModule.setDriveSpeed(scalar * joystickOne.GetRawAxis(0)); // Drive
    testModule.setSteerSpeed(scalar * joystickOne.GetRawAxis(1)); // Steer
}

void Robot::TestInit() 
{

}

void Robot::TestPeriodic() 
{

}

int main() { return frc::StartRobot<Robot>(); } // Initiate main program
