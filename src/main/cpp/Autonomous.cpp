
#include <math.h>
#include "Autonomous.h"




Autonomous::Autonomous(JrimmyGyro *Gyro, frc::Joystick *ButtonBox, SwerveDrive *SwerveDrive, CFS *CFS):
    a_Gyro(Gyro),
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
    BallsShot = 0;
    prevbeam = false;
    currbeam = true;

}

void Autonomous::Init(){
	a_Gyro->Zero();
    a_Anticipation.Start();
}

void Autonomous::DecidePath(){
    
    if(a_ButtonBox->GetRawButton(1)){
    
        autoPathMaster = 0;

    }
    else if(a_ButtonBox->GetRawButton(2)){
    
        autoPathMaster = 1;

    }    
    else if(a_ButtonBox->GetRawButton(3)){

        autoPathMaster = 2;

    }
    else if(a_ButtonBox->GetRawButton(4)){
    
        autoPathMaster = 3;

    }
    else if(a_ButtonBox->GetRawButton(5)){
    
        autoPathMaster = 4;

    }
    else if(a_ButtonBox->GetRawButton(7)){

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
    a_Gyro->Zero();

}


void Autonomous::AutonomousPeriodic0(){

    AutoState0 nextState = a_AutoState0;

	switch(a_AutoState0){

	    case kAutoIdle0:
		    IDontLikeExercise();

		    break;

	    case kArmMove0:
	    	if(!MoveDaArm(ARM_DEFAULT_POSITION)){
                MoveDaArm(ARM_DEFAULT_POSITION);

            } else {

            nextState = kDriveAway0;

           }


		    break;

        case kDriveAway0:
           if(!DriveDist(ARBITRARY_DIST_BACKWARDS, 0)){
               DriveDist(ARBITRARY_DIST_BACKWARDS, 0);

           } else {

            nextState = kAutoIdle0;

           }

            break;
	}

    
	a_AutoState0 = nextState;

}


void Autonomous::AutonomousStart1(){
    
    a_AutoState1 = kArmMove1;
    a_Gyro->Zero();

}


void Autonomous::AutonomousPeriodic1(){

    AutoState1 nextState = a_AutoState1;

	switch(a_AutoState1){

	    case kAutoIdle1:
		    IDontLikeExercise();

		    break;

	    case kArmMove1:
	    	if(!MoveDaArm(ARM_DEFAULT_POSITION)){
                MoveDaArm(ARM_DEFAULT_POSITION);

            } else {

            nextState = kShoot1;

           }


		    break;


        case kBallFind1:
            if(CheckBallPos()){
               a_CFS->Feed(AUTO_FEED_VAL);

            } else {
               nextState = kShoot1;

            }

            break;




        case kShoot1:
           if(!RootyTootyShooty(AUTO_START_BALL_NUM)){
               RootyTootyShooty(AUTO_START_BALL_NUM);

           } else {

            nextState = kDriveAway1;

           }

            break;


        case kDriveAway1:
           if(!DriveDist(ARBITRARY_DIST_BACKWARDS, 180.0)){
               DriveDist(ARBITRARY_DIST_BACKWARDS, 180.0);

           } else {

            nextState = kAutoIdle1;

           }

            break;
	}

    
	a_AutoState1 = nextState;

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

void Autonomous::IDontLikeExercise(){

    a_Gyro->Zero();
    a_SwerveDrive->swerveUpdate(0, 0, 0, a_Gyro->GetAngle(0), true);

}


void Autonomous::waitplz(double anticipate){
   /* double woah = frc2::Timer::GetMatchTime().to<double>;
    
    while (a_Anticipation.Get().to<double> < woah.to<double> + anticipate)
    {
        if (woah >= 15){
            break; 
        }
    }
    
*/

}

bool Autonomous::MoveDaArm(double angle){


return true;

/*
    if(a_CFS->getArmAngle() < angle){         /////AUTO_SHOOT_ANGLE
        a_CFS->ArmMovePos(angle);
        frc::SmartDashboard::PutNumber("ArM POsItIoN", a_CFS->getArmAngle());
        return false;

    } else {
        // a_CFS->ArmMovePos(KILL); ????? something to stop it
        frc::SmartDashboard::PutNumber("ArM POsItIoN", a_CFS->getArmAngle());
        return true;
    }


*/

}


bool Autonomous::DriveDist(double dist, double angle){ // true is done, false is not done

    if((double) a_SwerveDrive->getAvgDistance() < dist){
        a_SwerveDrive->driveDistance(dist, angle);
        frc::SmartDashboard::PutNumber("Encoder average?????", a_SwerveDrive->getAvgDistance());
        return false;


    } else {
        a_SwerveDrive->swerveUpdate(0, 0, 0, a_Gyro->GetAngle(0), true);
        frc::SmartDashboard::PutNumber("We done????? ", a_SwerveDrive->getAvgDistance());
        return true;

    }
            

}


bool Autonomous::CheckBallPos(){
    if(a_CFS->GetTopBeam()){
        return true;

    } else {
        return false;

    }

}


bool Autonomous::RootyTootyShooty(int count){
    currbeam = CheckBallPos();
    
    
    if(BallsShot < ((2 * count)) and !currbeam == prevbeam){
        BallsShot++;
        prevbeam = currbeam;
        return false;
    }
    else if(BallsShot < ((2 * count))){
        a_CFS->ShootVelocity(AUTO_SHOOT_VELOCITY);
        a_CFS->Feed(AUTO_FEED_VAL);
        return false;
    }
    else{
        BallsShot = 0;
        return true;
    }


    
}
