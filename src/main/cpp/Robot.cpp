
#include "Robot.h"
#include "Prefs.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <stdio.h>

Robot::Robot():
a_Gyro(frc::I2C::kMXP), // 1
a_FLModule(FL_DRIVE_ID, FL_STEER_ID, 1), // what is the steerEncID???
a_FRModule(FR_DRIVE_ID, FR_STEER_ID, 2), // (when we get analog encoders, replace 1-4 with actual IDs)
a_BLModule(BL_DRIVE_ID, BL_STEER_ID, 3),
a_BRModule(BR_DRIVE_ID, BR_STEER_ID, 4),
joystickOne(JOYSTICK_PORT),
a_xBoxController(XBOX_CONTROLLER),
a_buttonbox(BUTTON_BOX),
a_swerveyDrive(&a_FLModule, &a_FRModule, &a_BLModule, &a_BRModule),
a_LimeyLight(),
// handler("169.254.179.144", "1185", "data"),
a_CFS(SHOOT_1, SHOOT_2, FEED_1, FEED_2, COLLECT, PIVOT, BROKEN_BEAM, REESES_BEAM)
// a_BrokenBeam(BROKEN_BEAM)
{
    a_FLModule.updateDrivePID(0.001, 0, 0);
    a_FLModule.updateSteerPID(2.0, 0, 0.02);

    a_FRModule.updateDrivePID(0.001, 0, 0);
    a_FRModule.updateSteerPID(2.2, 0, 0.002);

    a_BLModule.updateDrivePID(0.001, 0, 0);
    a_BLModule.updateSteerPID(2.0, 0, 0.002);

    a_BRModule.updateDrivePID(0.001, 0, 0);
    a_BRModule.updateSteerPID(2.0, 0, 0.01);
}

void Robot::RobotInit() 
{
    frc::SmartDashboard::init();
    a_Gyro.Init();
    a_Gyro.Cal();
    a_Gyro.Zero();

    a_LimeyLight.ledOff();
    a_LimeyLight.cameraMode(0);
}

void Robot::RobotPeriodic()
{
    a_Gyro.Update(); 
    // handler.update();
    frc::SmartDashboard::PutNumber("Wheel Speed L: ", a_CFS.GetWheelSpeedL());
    frc::SmartDashboard::PutNumber("Wheel Speed R: ", a_CFS.GetWheelSpeedR());
    frc::SmartDashboard::PutBoolean("Bottom Beam Break: ", a_CFS.GetBottomBeam());
    frc::SmartDashboard::PutBoolean("Top Beam Break: ", a_CFS.GetTopBeam());
    frc::SmartDashboard::PutNumber("FL Speed: ", a_FLModule.getDriveSpeed());
    frc::SmartDashboard::PutNumber("FR Speed: ", a_FRModule.getDriveSpeed());
    frc::SmartDashboard::PutNumber("BL Speed: ", a_BLModule.getDriveSpeed());
    frc::SmartDashboard::PutNumber("BR Speed: ", a_BRModule.getDriveSpeed());
    frc::SmartDashboard::PutNumber("Pivot Voltage: ", a_CFS.GetPivotPosition());
    frc::SmartDashboard::PutNumber("Pivot Angle: ", a_CFS.VoltToAngle());
    frc::SmartDashboard::PutBoolean("Limelight Target?", a_LimeyLight.isTarget());
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
    float z = -1 * joystickOne.GetRawAxis(2);
    float gyro = a_Gyro.GetAngle(0);

    if(fabs(x) < 0.10)
    {
        x = 0;
    }
    if(fabs(y) < 0.10)
    {
        y = 0;
    }
    if(fabs(z) < 0.10)
    {
        z = 0;
    }
    
    if(gyro < 0)
    {
        gyro = fmod(gyro, -360);
        gyro += 360;
    }
    else
    {
        gyro = fmod(gyro, 360);
    }
    
    bool fieldOreo = true; // field oriented? - yes

    frc::SmartDashboard::PutNumber("Chase: ", z);
    bool inDeadzone = (((sqrt(x * x + y * y) < JOYSTICK_DEADZONE) && (fabs(z) < JOYSTICK_DEADZONE)) ? true : false); // Checks joystick deadzones

    if(!inDeadzone) {
        if(joystickOne.GetRawButton(1)) {
            a_swerveyDrive.swerveUpdate(x, y, 0.5 * z, gyro, fieldOreo);
        } else {
           a_swerveyDrive.crabDriveUpdate(x, y, gyro);
        }
    } else {
        a_swerveyDrive.swerveUpdate(0, 0, 0, gyro, fieldOreo);
    }

    frc::SmartDashboard::PutNumber("Gyro: ", gyro);

    /* -=-=-=-=-=-=-=-=-=-=-=-=-=-=- Limelight Stuffs -=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
        
    if(joystickOne.GetRawButton(7)) {
        a_LimeyLight.ledOn(); 
        frc::SmartDashboard::PutNumber("Limelight: ", 1); 
        // *gasp* turns led on
    } else if(joystickOne.GetRawButton(9)) {
        a_LimeyLight.ledOff();
        frc::SmartDashboard::PutNumber("Limelight: ", 0);
        // *even bigger gasp* turns led off 
    }
    
    if(joystickOne.GetRawButton(10)) {
        a_LimeyLight.cameraMode(0);
        //  turn on vision
    } else if(joystickOne.GetRawButton(12)) {
        a_LimeyLight.cameraMode(1); 
        // turn on remote viewing 
    }

    

    // untested, temp button
    /* if(joystickOne.GetRawButton(6) && a_LimeyLight.isTarget()) {
        a_swerveyDrive.turnToAngle(gyro, a_LimeyLight.getXAngleShooter (std::vector<float> (), gyro));
        #ifdef CONTROL_VELOCITY
        #else
        
        #endif
    }
    */

        /*
            cameraMode 0: Vision processing
            cameraMode 1: Remote viewing 
            :)
        */

       if(joystickOne.GetRawButton(4)) {
           a_swerveyDrive.swerveUpdate(0, 0, a_LimeyLight.calcZAxis(), gyro, false);
       } // calculates what angle robot should turn 
       // joystickOne.GetRawAxis(0)
       // joystickOne.GetRawAxis(1)
       
    a_LimeyLight.printValues();

    /* -=-=-=-=-=-=-=-=-=- End Of Lime Light Stuff -=-=-=-=-=-=-=-=-=-=- */

    if(joystickOne.GetRawButton(5))
    {
        a_Gyro.Cal();
        a_Gyro.Zero();
    }

    if(a_xBoxController.GetRawButton(1)) {
        a_CFS.ShootVelocity(0.925); 
    }
    else if(a_xBoxController.GetRawButton(3))
    {
        a_CFS.ShootVelocity(0.52); 
    }
    else {
        a_CFS.ShootVelocity(0);
    }

    if(a_xBoxController.GetRawButton(2))
    {
        a_CFS.AutoCollect();
    }
    else
    {
        if(fabs(a_xBoxController.GetRawAxis(3)) > 0)
        {
            a_CFS.Collect(a_xBoxController.GetRawAxis(3));
        }
        else if(fabs(a_xBoxController.GetRawAxis(2)) > 0)
        {
            a_CFS.Collect(-1* a_xBoxController.GetRawAxis(2));
        }
        else
        {
            a_CFS.Collect(0);
        }

        a_CFS.Feed(0.5 * a_xBoxController.GetRawAxis(1));
    }
    
    float temp = 0.2 * a_xBoxController.GetRawAxis(5);
    a_CFS.ArmMove(temp);
    frc::SmartDashboard::PutNumber("Arm Input: ", temp);

}

void Robot::TestInit() 
{

}


void Robot::TestPeriodic() 
{
    float scalar = 1.0;

    if(a_xBoxController.GetRawButton(1))
    {
        scalar = 0.8; // 80% speed if a is held
    }

    a_CFS.ShootVelocity(scalar * a_xBoxController.GetRawAxis(5));

    if(a_xBoxController.GetRawButton(2))
    {
        a_CFS.AutoCollect();
    }
    else
    {
        a_CFS.Feed(0.5 * a_xBoxController.GetRawAxis(1));
    }
    
    if(fabs(a_xBoxController.GetRawAxis(3)) > 0)
    {
        a_CFS.Collect(a_xBoxController.GetRawAxis(3));
    }
    else if(fabs(a_xBoxController.GetRawAxis(2)) > 0)
    {
        a_CFS.Collect(-1* a_xBoxController.GetRawAxis(2));
        frc::SmartDashboard::PutNumber("Collector Speed: ", -1 * a_xBoxController.GetRawAxis(2));
    }
    else
    {
        a_CFS.Collect(0);
    }
    

    /* 

    if(fabs(a_xBoxController.GetRawAxis(1)) < 0.10) {
        a_CFS.ArmMove(0);
    } else {,
        a_CFS.ArmMove(a_xBoxController.GetRawAxis(1));
    }

    if(fabs(a_xBoxController.GetRawAxis(3)) < 0.10) {
        a_CFS.Collect(0);
    } else {
        a_CFS.Collect(a_xBoxController.GetRawAxis(3)); 
    }

    if(fabs(a_xBoxController.GetRawAxis(2)) < 0.10) {
        a_CFS.Collect(0);
    } else {
        a_CFS.Collect(-1.0 * a_xBoxController.GetRawAxis(2));
    }

    if(a_xBoxController.GetRawButton(6)) {
        a_CFS.Feed(FEED_SPEED);
    } else {
        a_CFS.Feed(0);
    }

    if(a_xBoxController.GetRawButton(5)) {
        a_CFS.Feed(-1.0 * FEED_SPEED); 
    } else {
        a_CFS.Feed(0);
    }

    if(a_xBoxController.GetPOV() == 0) {
        // climb
    } else {
        // don't climb
    }

    */ 


}


int main() { return frc::StartRobot<Robot>(); } // Initiate main loop
