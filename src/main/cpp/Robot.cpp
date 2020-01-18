
#include "Robot.h"
#include "Prefs.h"
#include <frc/smartdashboard/SmartDashboard.h>

Robot::Robot():
testModule(TEST_DRIVE_ID, TEST_STEER_ID, 1), // fix encoders at some point
joystickOne(JOYSTICK_PORT)
{

}

void Robot::RobotInit() 
{
    frc::SmartDashboard::init();
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

void Robot::TeleopPeriodic() // main loop
{
    float scalar = 0.2;

    float y = joystickOne.GetRawAxis(0);
    float x = joystickOne.GetRawAxis(1);

    float floatyGoat = testModule.getDistance();

    frc::SmartDashboard::PutNumber("Joystick Y: ", y);
    frc::SmartDashboard::PutNumber("Joystick X: ", x);
    frc::SmartDashboard::PutNumber("Drive Encoder?????", floatyGoat);
    
    testModule.setDriveSpeed(scalar * joystickOne.GetRawAxis(0)); // Drive
    testModule.setSteerSpeed(scalar * joystickOne.GetRawAxis(1)); // Steer
}

void Robot::TestInit() 
{

}

void Robot::TestPeriodic() 
{

}

int main() { return frc::StartRobot<Robot>(); } // Initiate main loop
