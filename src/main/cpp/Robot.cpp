
#include "Robot.h"
#include "Prefs.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <stdio.h>

Robot::Robot():
<<<<<<< HEAD
testModule(TEST_DRIVE_ID, TEST_STEER_ID, 1), // fix encoders at some point
joystickOne(JOYSTICK_PORT),
handler("169.254.179.144", "1185", "data")
=======
a_Gyro(frc::I2C::kMXP), // 1
a_FLModule(FL_DRIVE_ID, FL_STEER_ID, 1), // what is the steerEncID???
a_FRModule(FR_DRIVE_ID, FR_STEER_ID, 2), // (when we get analog encoders, replace 1-4 with actual IDs)
a_BLModule(BL_DRIVE_ID, BL_STEER_ID, 3),
a_BRModule(BR_DRIVE_ID, BR_STEER_ID, 4),
joystickOne(JOYSTICK_PORT),
a_buttonbox(3),
a_swerveyDrive(&a_FLModule, &a_FRModule, &a_BLModule, &a_BRModule),
a_LimeyLight()
>>>>>>> master
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
    float gyro = a_Gyro.GetAngle(0); 
    bool fieldOreo = false; // field oriented? 

    bool inDeadzone = (sqrt(x * x + y * y) < JOYSTICK_DEADZONE && z < 0.01 ? true : false); // Checks joystick deadzones

    if(inDeadzone) {
        if(joystickOne.GetRawButton(1)) {
            a_swerveyDrive.swerveUpdate(x, y, z, gyro, fieldOreo);
        } else {
           a_swerveyDrive.swerveUpdate(x, y, 0, gyro, fieldOreo);
        }
    } else {
        a_swerveyDrive.swerveUpdate(0, 0, 0, gyro, fieldOreo);
    }

    frc::SmartDashboard::PutNumber("Gyro: ", gyro);

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

void Robot::RobotPeriodic() 
{
    //frc::SmartDashboard::PutNumber("MQTT CONNECT", 1);
    handler.update ();
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
