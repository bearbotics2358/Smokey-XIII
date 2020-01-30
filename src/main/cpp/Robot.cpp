
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
a_swerveyDrive(&a_FLModule, &a_FRModule, &a_BLModule, &a_BRModule),
a_LimeyLight(),
a_CFS(SHOOT_1, SHOOT_2, FEED_1, FEED_2, COLLECT, PIVOT)
{
    a_FLModule.updateDrivePID(0.0, 0, 0);
    a_FLModule.updateSteerPID(2.0, 0, 0.02);

    a_FRModule.updateDrivePID(0.8, 0, 0);
    a_FRModule.updateSteerPID(2.2, 0, 0.002);

    a_BLModule.updateDrivePID(0.8, 0, 0);
    a_BLModule.updateSteerPID(2.0, 0, 0.002);

    a_BRModule.updateDrivePID(0.0, 0, 0);
    a_BRModule.updateSteerPID(2.0, 0, 0.01);
}

void Robot::RobotInit() 
{
    frc::SmartDashboard::init();
    a_Gyro.Init();
    a_Gyro.Cal();
    a_Gyro.Zero();
}

void Robot::RobotPeriodic()
{
    a_Gyro.Update(); 
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
    float x = -1 * joystickOne.GetRawAxis(0);
    float y = -1 * joystickOne.GetRawAxis(1);
    float z = joystickOne.GetRawAxis(2);
    float gyro = a_Gyro.GetAngle(0); 
    bool fieldOreo = true; // field oriented? - yes

    frc::SmartDashboard::PutNumber("Chase: ", z);
    bool inDeadzone = (((sqrt(x * x + y * y) < JOYSTICK_DEADZONE) && (fabs(z) < 0.01)) ? true : false); // Checks joystick deadzones

    if(!inDeadzone) {
        if(joystickOne.GetRawButton(1)) {
            a_swerveyDrive.swerveUpdate(x, y, z, gyro, fieldOreo);
        } else {
           a_swerveyDrive.swerveUpdate(x, y, 0, gyro, fieldOreo);
        }
    } else {
        a_swerveyDrive.swerveUpdate(0, 0, 0, gyro, fieldOreo);
    }

    frc::SmartDashboard::PutNumber("Gyro: ", gyro);
    frc::SmartDashboard::PutNumber("GYRO 2: ", a_Gyro.GetAngle(1));
    frc::SmartDashboard::PutNumber("GYRO 3: ", a_Gyro.GetAngle(2));

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=- Limelight Stuffs -=-=-=-=-=-=-=-=-=-=-=-=-=-=- \\
        
    if(joystickOne.GetRawButton(7)) {
        a_LimeyLight.ledOn(); 
        frc::SmartDashboard::PutNumber("Limelight: ", 1); 
        // *gasp* turns led on
    } else if(joystickOne.GetRawButton(9)) {
        a_LimeyLight.ledOff();
        frc::SmartDashboard::PutNumber("Limelight: ", 0);
        // *even bigger gasp* turns led off 
    }
    
    if(joystickOne.GetRawButton(8)) {
        a_LimeyLight.cameraMode(0);
        //  turn on vision
    } else if(joystickOne.GetRawButton(10)) {
        a_LimeyLight.cameraMode(1); 
        // turn on remote viewing 
    }

        /*
            cameraMode 0: Vision processing
            cameraMode 1: Remote viewing 
            :)
        */

    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

    a_LimeyLight.printValues();
}

void Robot::TestInit() 
{

}

void Robot::TestPeriodic() 
{
    
    a_CFS.Shoot(joystickOne.GetRawAxis(3));
    a_CFS.Feed(joystickOne.GetRawAxis(1));
    
}

int main() { return frc::StartRobot<Robot>(); } // Initiate main loop
