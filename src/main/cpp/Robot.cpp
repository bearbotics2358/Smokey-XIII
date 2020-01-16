
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

    a_shooter.SetShootPID1(1, 0, 0);
    a_shooter.SetShootPID2(1, 0, 0);

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

        a_shooter.SetSpeed(.785);

    }else{

        a_shooter.SetSpeed(0);
    
    }

    a_shooter.BasicShoot();

    frc::SmartDashboard::PutNumber("Percent output", a_shooter.GetSpeed());
    frc::SmartDashboard::PutNumber("Motor speed 1", a_shooter.GetVelocity1());
    frc::SmartDashboard::PutNumber("Motor speed 2", a_shooter.GetVelocity2());
    frc::SmartDashboard::PutNumber("Motor voltage 1", a_shooter.GetVoltage1());
    frc::SmartDashboard::PutNumber("Motor voltage 2", a_shooter.GetVotage2());

}

void Robot::TestInit() 
{

}

void Robot::TestPeriodic() 
{
    
   
    if(a_conTroller.GetRawButton(3))
	{
        a_shooter.VelocityShoot(100 * a_conTroller.GetRawAxis(1));
			
	}else{

        a_shooter.VelocityShoot(0);
    
    }

 
    frc::SmartDashboard::PutNumber("Percent output", a_shooter.GetSpeed());
    frc::SmartDashboard::PutNumber("Motor speed 1", a_shooter.GetVelocity1());
    frc::SmartDashboard::PutNumber("Motor speed 2", a_shooter.GetVelocity2());
    frc::SmartDashboard::PutNumber("Motor voltage 1", a_shooter.GetVoltage1());
    frc::SmartDashboard::PutNumber("Motor voltage 2", a_shooter.GetVotage2());


}

int main() { return frc::StartRobot<Robot>(); } // Initiate main program
