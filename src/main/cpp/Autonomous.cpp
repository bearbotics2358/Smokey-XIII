#include <FRC/WPILib.h> // please include in the .h and use only what you need; my compilation times are like 1 minute pls <3
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
    
    if(a_buttonBox.GetRawButton(1)){
    
        autoPathMaster = 0;

    }
    else if(a_buttonBox.GetRawButton(2)){
    
        autoPathMaster = 1;

    }    
    else if(a_buttonBox.GetRawButton(3)){
    
        autoPathMaster = 2;

    }
    else if(a_buttonBox.GetRawButton(4)){
    
        autoPathMaster = 3;

    }
    else if(a_buttonBox.GetRawButton(5)){
    
        autoPathMaster = 4;

    }
    else if(a_buttonBox.GetRawButton(7)){\

        autoPathMaster = 5;

    }
    else{

        autoPathMaster = -1;

    }


}



void Autonomous::DecidePath(int intent){
    
    autoPathMaster = intent;

}

int Autonomous::GetCurrentPath(){
    
    return autoPathMaster;
}

void Autonomous::StartPathMaster(){
	
    switch(autoPathMaster){
		
        case -1:
			// Error!
			SmartDashboard::PutBoolean("Auto Started", false);
		
        	break;
		
        case 0:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart0();
		
        	break;
		
        case 1:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart1();
		
        	break;
		
        case 2:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart2();
		
        	break;
		
        case 3:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart3();
		
        	break;
		
        case 4:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart4();
		
        	break;
		
        case 5:
	

			break;
	}
}

void Autonomous::StartPathMaster(int path){
	
    switch(path){
		
        case -1:
			// Error!
			SmartDashboard::PutBoolean("Auto Started", false);
		
        	break;
		
        case 0:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart0();
		
        	break;
		
        case 1:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart1();
		
        	break;
		
        case 2:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart2();
		
        	break;
		
        case 3:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart3();
		
        	break;
		
        case 4:
			SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart4();
		
        	break;
		
        case 5:
	

			break;
	}
}






void Autonomous::AutonomousStart0(){


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