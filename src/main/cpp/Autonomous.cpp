#include <math.h>
#include "Autonomous.h"




Autonomous::Autonomous(frc::Joystick &ButtonBox, SwerveDrive &SwerveDrive, CFS &CFS):
    a_ButtonBox(ButtonBox),
    a_SwerveDrive(SwerveDrive),
    a_CFS(CFS),
    a_Anticipation(),
    a_AutoState0(kAutoIdle0),
    a_AutoState1(kAutoIdle1),
    a_AutoState2(kAutoIdle2),
    a_AutoState3(kAutoIdle3),
    a_AutoState4(kAutoIdle4)
    
{

    autoPathMaster = -1;

}

void Autonomous::Init(){
	a_Gyro.Zero();
    a_Anticipation.Start();
}

void Autonomous::DecidePath(){
    
    if(a_ButtonBox.GetRawButton(1)){
    
        autoPathMaster = 0;

    }
    else if(a_ButtonBox.GetRawButton(2)){
    
        autoPathMaster = 1;

    }    
    else if(a_ButtonBox.GetRawButton(3)){
    
        autoPathMaster = 2;

    }
    else if(a_ButtonBox.GetRawButton(4)){
    
        autoPathMaster = 3;

    }
    else if(a_ButtonBox.GetRawButton(5)){
    
        autoPathMaster = 4;

    }
    else if(a_ButtonBox.GetRawButton(7)){\

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
			frc::SmartDashboard::PutBoolean("Auto Started", false);
		
        	break;
		
        case 0:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart0();
		
        	break;
		
        case 1:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart1();
		
        	break;
		
        case 2:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart2();
		
        	break;
		
        case 3:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart3();
		
        	break;
		
        case 4:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
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
			frc::SmartDashboard::PutBoolean("Auto Started", false);
		
        	break;
		
        case 0:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart0();
		
        	break;
		
        case 1:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart1();
		
        	break;
		
        case 2:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart2();
		
        	break;
		
        case 3:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart3();
		
        	break;
		
        case 4:
			frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart4();
		
        	break;
		
        case 5:
	

			break;
	}
}

void Autonomous::PeriodicPathMaster(){
	switch(autoPathMaster){
		case -1:
			// Error!
			break;
		case 0:
			AutonomousPeriodic0();

			break;

		case 1:
			AutonomousPeriodic1();
			
            break;
		
        case 2:
			AutonomousPeriodic2();
			
            break;
		
        case 3:
			AutonomousPeriodic3();
			
            break;
		
        case 4:
            AutonomousPeriodic4();
			
            break;
		
        case 5: 
			
            break;
	}
}

void Autonomous::PeriodicPathMaster(int path){
	switch(path){
		case -1:
			// Error!
			break;
		case 0:
			AutonomousPeriodic0();

			break;
		
        case 1:
			AutonomousPeriodic1();
			
            break;
		
        case 2:
			AutonomousPeriodic2();
			
            break;
		
        case 3:
			AutonomousPeriodic3();
			
            break;
		
        case 4:
			AutonomousPeriodic4();
			
            break;
		
        case 5:
			
            break;
	}
}




void Autonomous::AutonomousStart0(){

    a_AutoState0 = kArmMove0;
    // a_Gyro.Zero();

}


void Autonomous::AutonomousPeriodic0(){

    AutoState0 nextState = a_AutoState0;

	switch(a_AutoState0){

	    case kAutoIdle0:
		    

		    break;

	    case kArmMove0:
	    	

		    break;

        case kDriveAway0:


            break;
	}

    
	a_AutoStateU0 = nextState;

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

void Autonomous::waitplz(float anticipate){
    int woah = frc2::Timer::GetMatchTime();
    
    while (a_Anticipation.Get().to<float> < woah.to<float> + anticipate)
    {
        if (woah.to<float> >= 15){
            break; 
        }
    }
    


}