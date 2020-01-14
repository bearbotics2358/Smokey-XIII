
#include "Robot.h"
#include "Prefs.h"
#include <frc/smartdashboard/SmartDashboard.h>

Robot::Robot():
a_shooter(1, 2), // fix encoders at some point
a_conTroller(CONTROLLER_PORT)
{




}

void Robot::RobotInit() 
{
    frc::SmartDashboard::init();

    a_shooter.SetShootPID1(.5, 0, 0);
    a_shooter.SetShootPID2(.5, 0, 0);

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

    if(a_conTroller.GetRawButton(3))
	{
        a_shooter.SetSpeed(a_conTroller.GetRawAxis(1));
			
	}else if(a_conTroller.GetRawButton(2)){

        a_shooter.SetSpeed(-.72[]\);

    }else{

        a_shooter.SetSpeed(0);
    
    }

    a_shooter.BasicShoot();

    frc::SmartDashboard::PutNumber("Motor speed", a_shooter.GetSpeed());
    frc::SmartDashboard::PutNumber("Motor speed2", a_shooter.GetVelocity1());
    frc::SmartDashboard::PutNumber("Motor speed3", a_shooter.GetVelocity2());

}

void Robot::TestInit() 
{

}

void Robot::TestPeriodic() 
{
    
   
    if(a_conTroller.GetRawButton(3))
	{
        a_shooter.VelocityShoot(a_conTroller.GetRawAxis(1));
			
	}else{

        a_shooter.VelocityShoot(0);
    
    }

 

    frc::SmartDashboard::PutNumber("Motor speed", a_shooter.GetSpeed());
    frc::SmartDashboard::PutNumber("Motor speed2", a_shooter.GetVelocity1());
    frc::SmartDashboard::PutNumber("Motor speed3", a_shooter.GetVelocity2());

}

int main() { return frc::StartRobot<Robot>(); } // Initiate main program
