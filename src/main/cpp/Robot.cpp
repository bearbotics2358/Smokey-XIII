
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
    float scalar = 0.3;

    float y = joystickOne.GetRawAxis(1);
    float x = joystickOne.GetRawAxis(0);

    float floatyGoat = testModule.getDistance();
    float followMe = testModule.getAngleRaw();
    float calculatedAngle = testModule.getAngle();

    bool enablePID = joystickOne.GetRawButton(1);

    float tarf = (atan2(x, y)) * 180 / 3.1415926;
    if(tarf < 0)
    {
        tarf += 360;
    }

    frc::SmartDashboard::PutNumber("Joystick Y: ", y);
    frc::SmartDashboard::PutNumber("Joystick X: ", x);
    frc::SmartDashboard::PutNumber("Drive Encoder: ", floatyGoat);
    frc::SmartDashboard::PutNumber("Angle Encoder: ", followMe);
    frc::SmartDashboard::PutNumber("Calc Angle: ", calculatedAngle);
    frc::SmartDashboard::PutNumber("Targ Angle: ", tarf);

    float radius = sqrt(x * x + y * y); 

    if(radius >= 0.15)
    {
        if(enablePID)
        {
            testModule.steerToAng(calculatedAngle, tarf);
            testModule.setDriveSpeed(radius * 0.2); 
        }
        else
        { 
            testModule.setDriveSpeed(scalar * y); // Drive
            testModule.setSteerSpeed(scalar * x); // Steer    
        }
    }
    else
    {
        testModule.setDriveSpeed(0);
        testModule.setSteerSpeed(0);
    }
    
    
    
}

void Robot::TestInit() 
{

}

void Robot::TestPeriodic() 
{

}

int main() { return frc::StartRobot<Robot>(); } // Initiate main loop
