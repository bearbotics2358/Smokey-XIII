
#include "Robot.h"
#include "Prefs.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <stdio.h>
#include <string>
/*~~ hi :) ~~ */
Robot::Robot():
#ifndef LAPTOP
a_Gyro(frc::I2C::kMXP), // 1
a_FLModule(FL_DRIVE_ID, FL_STEER_ID, 1), 
a_FRModule(FR_DRIVE_ID, FR_STEER_ID, 2), // (when we get analog encoders, replace 1-4 with actual IDs)
a_BLModule(BL_DRIVE_ID, BL_STEER_ID, 3),
a_BRModule(BR_DRIVE_ID, BR_STEER_ID, 4),
joystickOne(JOYSTICK_PORT),
a_xBoxController(XBOX_CONTROLLER),
a_buttonbox(BUTTON_BOX),
a_swerveyDrive(&a_FLModule, &a_FRModule, &a_BLModule, &a_BRModule),
a_LimeyLight(),
a_CFS(SHOOT_1, SHOOT_2, FEED_1, FEED_2, COLLECT, PIVOT, CLIMBER, BROKEN_BEAM, REESES_BEAM),
#endif
a_mqttHandler("10.23.58.26", "1183", "PI/CV/SHOOT/DATA"),
#ifndef LAPTOP
a_canHandler(canMakeIn2020()),
// a_coms(&a_mqttHandler, &a_canHandler),
a_JAutonomous(&a_Gyro, &a_mqttHandler, &a_buttonbox, &a_swerveyDrive, &a_CFS, &a_LimeyLight),
#endif
syncSafe(true)
{
    #ifndef LAPTOP
    a_FLModule.updateDrivePID(0.001, 0, 0);
    a_FLModule.updateSteerPID(2.0, 0, 0.02);

    a_FRModule.updateDrivePID(0.001, 0, 0);
    a_FRModule.updateSteerPID(2.2, 0, 0.002);

    a_BLModule.updateDrivePID(0.001, 0, 0);
    a_BLModule.updateSteerPID(2.0, 0, 0.002);

    a_BRModule.updateDrivePID(0.001, 0, 0);
    a_BRModule.updateSteerPID(2.0, 0, 0.01);
    #endif
}

void Robot::RobotInit() 
{
    #ifndef LAPTOP
    frc::SmartDashboard::init();
    a_Gyro.Init();
    // sa_Gyro.Cal();
    a_Gyro.Zero();

    a_LimeyLight.ledOff();
    a_LimeyLight.cameraMode(0);
    #endif

    if (signal (SIGPIPE, sigpipeHandler) == SIG_ERR)
    {
        printf ("Connecting SIGPIPE handler failed");
        syncSafe = false;
    }
}

void Robot::RobotPeriodic()
{
    // if signal handler for sigpipe didn't succeed, don't run or else robot code will crash if pi crashes
    if (syncSafe)
    {
        a_mqttHandler.publish(std::to_string(a_mqttHandler.angle) + " " + std::to_string(a_mqttHandler.distance), "data");
        a_mqttHandler.update ();
    }

    #ifndef LAPTOP
    a_Gyro.Update(); 
    
    frc::SmartDashboard::PutNumber("Wheel Speed L: ", a_CFS.GetWheelSpeedL());
    frc::SmartDashboard::PutNumber("Wheel Speed R: ", a_CFS.GetWheelSpeedR());

    frc::SmartDashboard::PutBoolean("Bottom Beam Break: ", a_CFS.GetBottomBeam());
    frc::SmartDashboard::PutBoolean("Top Beam Break: ", a_CFS.GetTopBeam());
    
    frc::SmartDashboard::PutNumber("Pivot Voltage: ", a_CFS.GetPivotPosition());
    frc::SmartDashboard::PutNumber("Pivot Angle: ", a_CFS.GetArmAngle());
    frc::SmartDashboard::PutBoolean("Limelight Target?", a_LimeyLight.isTarget());

    frc::SmartDashboard::PutNumber("Feeder Top: ", a_CFS.GetFeedSpeedTop());
    frc::SmartDashboard::PutNumber("Feeder Bot: ", a_CFS.GetFeedSpeedBot());

    frc::SmartDashboard::PutNumber("Distance Driven: ", a_swerveyDrive.getAvgDistance());
    frc::SmartDashboard::PutNumber("angle??????????: ", a_Gyro.GetAngle(0));
    #endif
}

void Robot::DisabledInit()
{
    #ifndef LAPTOP
    a_swerveyDrive.resetDrive();
    #endif
}

void Robot::DisabledPeriodic()
{

}

void Robot::AutonomousInit() 
{
    #ifndef LAPTOP
    a_JAutonomous.Init();
    a_JAutonomous.DecidePath(5); // path number we are using
    a_JAutonomous.StartPathMaster();
    #endif
}

void Robot::AutonomousPeriodic() 
{
    #ifndef LAPTOP
    a_JAutonomous.PeriodicPathMaster();
    #endif
}

void Robot::TeleopInit() 
{

}

void Robot::TeleopPeriodic() // main loop
{


    #ifndef LAPTOP
    
    /* -=-=-=-=-=-=-=-=-=-=-=-=-=-=- Limelight Stuffs -=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

    static bool on = false;
    if(joystickOne.GetRawButton(7)) {
        if (!on)
        {
            on = true;
            a_LimeyLight.ledOn ();
            frc::SmartDashboard::PutNumber("Limelight: ", 1);
            a_CFS.ShootVelocity (a_LimeyLight.getVelocityShooter ());
        }
        else
        {
            on = false;
            a_LimeyLight.ledOff();
            frc::SmartDashboard::PutNumber("Limelight: ", 0);
        }
    }
    
    if(joystickOne.GetRawButton(10)) {
        a_LimeyLight.cameraMode(0);
        //  turn on vision
    } else if(joystickOne.GetRawButton(12)) {
        a_LimeyLight.cameraMode(1); 
        // turn on remote viewing 
    }

    /*
        cameraMode 0: Vision processing
        cameraMode 1: Remote viewing 
        :)
    */  
       
    a_LimeyLight.printValues();

    /* -=-=-=-=-=-=-=-=-=- End Of Lime Light Stuff -=-=-=-=-=-=-=-=-=-=- */
    
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
        if(joystickOne.GetRawButton(1)) 
        {
            if(on) 
            {
                a_swerveyDrive.swerveUpdate(0, 0, a_LimeyLight.calcZAxis(), gyro, false);
            } 
            else
            {
                a_swerveyDrive.swerveUpdate(x, y, 0.5 * z, gyro, fieldOreo);
            }
        } 
        else 
        {
           a_swerveyDrive.crabDriveUpdate(x, y, gyro);
        }
    } 
    else 
    {
        a_swerveyDrive.swerveUpdate(0, 0, 0, gyro, fieldOreo);
    }

    frc::SmartDashboard::PutNumber("Gyro: ", gyro);


    // PI stuff

    // force reconnect to pi and connect signal handler if failed
    if(joystickOne.GetRawButton(6))
    {
        if (!syncSafe && signal (SIGPIPE, sigpipeHandler) != SIG_ERR)
        {
            syncSafe = true;
        }
        a_mqttHandler.injectError();
    }

    // end PI stuff

    if(joystickOne.GetRawButton(5))
    {
        a_Gyro.Cal();
        a_Gyro.Zero();
    }

    if(a_xBoxController.GetRawButton(1)) {
        a_CFS.ShootVelocity(SHOOT_VELOCITY); 
    }
    else if(a_xBoxController.GetRawButton(3))
    {
        a_CFS.ShootVelocity(420); 
    }
    else {
        a_CFS.ShootVelocity(0);
    }

    if(a_xBoxController.GetRawButton(2))
    {
        a_CFS.AutoCollect();
    }
    else
    {   if(a_xBoxController.GetRawButton(4))
        {
            a_CFS.Collect(-0.4);
        }
        else if(fabs(a_xBoxController.GetRawAxis(3)) > 0.1)
        {
            a_CFS.Collect(a_xBoxController.GetRawAxis(3));
        }
        else if(fabs(a_xBoxController.GetRawAxis(2)) > 0.1)
        {
            a_CFS.Collect(-1* a_xBoxController.GetRawAxis(2));
        }
        else
        {
            a_CFS.Collect(0);
        }

        if(a_xBoxController.GetRawButton(5))
        {
            a_CFS.setArmAngle(70);
        }
        else
        {
            a_CFS.ArmMove(0.2 * a_xBoxController.GetRawAxis(5));
        }
        

        if(a_xBoxController.GetRawButton(6))
        {
            a_CFS.FeedVelocity(1000); // positive is intake
        }
        else
        {
            a_CFS.Feed(a_xBoxController.GetRawAxis(1));
        }

        if(fabs(a_xBoxController.GetRawAxis(1)) < 0.1)
        {
            a_CFS.ClimbQuestionMark(a_xBoxController.GetRawAxis(1));
        }
        else
        {
            a_CFS.ClimbQuestionMark(0);
        }
        
        
    }
    #endif
}

void Robot::TestInit() 
{

}


void Robot::TestPeriodic() 
{
    #ifndef LAPTOP



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




    if(joystickOne.GetRawButton(3)) {
        a_swerveyDrive.turnToAngle(gyro, 180.0);
    } else if(!inDeadzone) {
        if(joystickOne.GetRawButton(1)) 
        {
            if(joystickOne.GetRawButton(2)) 
            {
                a_swerveyDrive.makeShiftTurn(a_LimeyLight.calcZAxis());
            } 
            else
            {
                a_swerveyDrive.swerveUpdate(x, y, 0.5 * z, gyro, fieldOreo);
            }
        } 
        else 
        
        {
           a_swerveyDrive.crabDriveUpdate(x, y, gyro);
        }
    } 
    else 
    {
        if(joystickOne.GetRawButton(2)) 
        {
            a_swerveyDrive.makeShiftTurn(a_LimeyLight.calcZAxis());
        } 
        else
        {
            a_swerveyDrive.swerveUpdate(0, 0, 0, gyro, fieldOreo);
        }
    }

    frc::SmartDashboard::PutNumber("Gyro: ", gyro);




    if(joystickOne.GetRawButton(4)) {
        a_JAutonomous.RootyTootyShooty(2, 464);
    } else {
        a_CFS.ShootVelocity(0);
        a_CFS.FeedVelocity(0);
    }

    if(fabs(a_xBoxController.GetRawAxis(1)) < 0.1)
    {
        a_CFS.ClimbQuestionMark(a_xBoxController.GetRawAxis(1));
    }
    else
    {
        a_CFS.ClimbQuestionMark(0);
    }
    

    if(a_xBoxController.GetRawButton(5))
    {
        a_CFS.setArmAngle(45);
    }
    else
    {
        a_CFS.ArmMove(0);
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

    #endif
}


int main() { return frc::StartRobot<Robot>(); } // Initiate main loop
