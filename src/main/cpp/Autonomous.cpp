#include <FRC/WPILib.h>
#include <math.h>
#include "Autonomous.h"




Autonomous::Autonomous(int BoxButtons):
    a_buttonBox(BoxButtons),
    a_AutoState0(kAutoIdle0),
    a_AutoState1(kAutoIdle1),
    a_AutoState2(kAutoIdle2),
    a_AutoState3(kAutoIdle3),
    a_AutoState4(kAutoIdle4)
{

    autoPathMaster = -1;

}

void Autonomous::Init(){
	// a_Gyro.Zero();
}

void Autonomous::DecidePath(){
    
    




}



void Autonomous::DecidePath(int intent){
    autoPathMaster = intent;

}


void AutonomousStart0(){


}


void Autonomous::AutonomousPeriodic0(){



}


void Autonomous::AutonomousStart1(){



}


void Autonomous::AutonomousPeriodic1(){


}


void Autonomous::AutonomousStart2(){



}


void Autonomous::AutonomousPeriodic2(){



}


void Autonomous::AutonomousStart3(){



}


void Autonomous::AutonomousPeriodic3(){



}


void Autonomous::AutonomousStart4(){




}



void Autonomous::AutonomousPeriodic4(){




}