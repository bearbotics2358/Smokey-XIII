
#include "Robot.h"
#include "Prefs.h"
#include <frc/smartdashboard/SmartDashboard.h>

Robot::Robot():
a_Gyro(frc::I2C::kMXP), // 1
a_FLModule(FL_DRIVE_ID, FL_STEER_ID, 1), // what is the steerEncID???
a_FRModule(FR_DRIVE_ID, FR_STEER_ID, 2), // (when we get analog encoders, replace 1-4 with actual IDs)
a_BLModule(BL_DRIVE_ID, BL_STEER_ID, 3),
a_BRModule(BR_DRIVE_ID, BR_STEER_ID, 4),
joystickOne(JOYSTICK_PORT),
a_buttonbox(3),
a_swerveyDrive(&a_FLModule, &a_FRModule, &a_BLModule, &a_BRModule)
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
    float x = joystickOne.GetRawAxis(0);
    float y = joystickOne.GetRawAxis(1);
    float z = joystickOne.GetRawAxis(2);
    float gyro = 9; // placeholder value
    bool fieldOreo = false; // field oriented? 

    bool inDeadzone = (sqrt(x * x + y * y) < JOYSTICK_DEADZONE && z < 0.01 ? true : false); // Checks joystick deadzones

    if(inDeadzone) {
        if(joystickOne.GetRawButton(1)) {
            a_swerveyDrive.swerveUpdate(x, y, z, gyro, fieldOreo);
        } else {
           a_swerveyDrive.swerveUpdate(x, y, 0, gyro, fieldOreo);
        }
    } else {
        a_swerveyDrive.swerveUpdate(0, 0, 0, 0, fieldOreo);
    }
}

void Robot::TestInit() 
{

}

void Robot::TestPeriodic() 
{
    
    frc::SmartDashboard::PutBoolean("Switch 1", a_buttonbox.GetRawButton(1));
    frc::SmartDashboard::PutBoolean("Switch 2", a_buttonbox.GetRawButton(2));
    frc::SmartDashboard::PutBoolean("Switch 3", a_buttonbox.GetRawButton(3));
    frc::SmartDashboard::PutBoolean("Switch 4", a_buttonbox.GetRawButton(4));
    frc::SmartDashboard::PutBoolean("Switch 5", a_buttonbox.GetRawButton(5));
    frc::SmartDashboard::PutBoolean("Switch 7", a_buttonbox.GetRawButton(7));

}

int main() { return frc::StartRobot<Robot>(); } // Initiate main loop
