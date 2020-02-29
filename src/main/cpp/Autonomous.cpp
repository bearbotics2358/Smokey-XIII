
#ifndef LAPTOP
#include <math.h>
#include "Autonomous.h"




Autonomous::Autonomous(JrimmyGyro *Gyro, MQTTHandler *handler, frc::Joystick *ButtonBox, SwerveDrive *SwerveDrive, CFS *CFS):
    a_Gyro(Gyro),
    a_handler(),
    a_ButtonBox(ButtonBox),
    a_SwerveDrive(SwerveDrive),
    a_CFS(CFS),
    a_Anticipation(),
    a_AutoState0(kAutoIdle0),
    a_AutoState1(kAutoIdle1),
    a_AutoState2(kAutoIdle2),
    a_AutoState3(kAutoIdle3),
    a_AutoState4(kAutoIdle4),
    a_AutoState5(kAutoIdle5)
    
{

    autoPathMaster = -1;
    BallsShot = 0;
    prevbeam = false;
    currbeam = true;

}

void Autonomous::Init(){
	// a_Gyro->Zero();
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
	Autonomous::StartPathMaster(autoPathMaster);
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
            frc::SmartDashboard::PutBoolean("Auto Started", true);
			AutonomousStart5();
		
	

			break;
	}
}

void Autonomous::PeriodicPathMaster(){
    Autonomous::PeriodicPathMaster(autoPathMaster);
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
            AutonomousPeriodic5();
			
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
	    	if(false) {// !MoveDaArm(ARM_DEFAULT_POSITION)){
                MoveDaArm(ARM_DEFAULT_POSITION);

            } else {

            nextState = kDriveAway0;

           }


		    break;

        case kDriveAway0:
           if(!IHaveAProposal(0.3, 30.0, ARBITRARY_DIST_BACKWARDS)) {//DriveDist(ARBITRARY_DIST_BACKWARDS, 180)){
               // DriveDist(ARBITRARY_DIST_BACKWARDS, 0);

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
                // MoveDaArm(ARM_DEFAULT_POSITION);

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
               // RootyTootyShooty(AUTO_START_BALL_NUM);

           } else {

            nextState = kDriveAway1;

           }

            break;


        case kDriveAway1:
           if(!DriveDist(ARBITRARY_DIST_BACKWARDS, 180.0)){
               // DriveDist(ARBITRARY_DIST_BACKWARDS, 180.0);

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
    AutonomousStart5 ();
    a_AutoState4 = kAutoDo54;
    a_Gyro->Zero();
}



void Autonomous::AutonomousPeriodic4() {
    // Call initial drive stuff and shooting
    float angle_in;
    float angle_out;
    switch (a_AutoState4)
    {
        case kAutoIdle4:
            IDontLikeExercise ();
            break;
        case kAutoDo54:
            AutonomousPeriodic5 ();
            if (a_AutoState5 == kAutoIdle5)
            {
                a_AutoState4 = kCollectBalls4;
            }
            break;
        case kAutoTurnBack4:
            if (TurnTaAngle (0))
            {
                a_AutoState4 = kCollectBalls4;
            }
            break;
        case kCollectBalls4: // get 3 balls
            if (a_CFS->count >= 3 || a_SwerveDrive->getAvgDistance () > 12345) // temp distance
            {
                a_handler->publish ("view", "/camera/control/claw");
                a_AutoState4 = kShoot4;
            }
            
            if (!a_handler->noErrors ())
            {
                a_AutoState4 = kShoot4;
            }

            // signs might not br right
            angle_in = a_handler->angle;
            angle_out = 0;
            if ((angle_in < 0 ? -angle_in : angle_in) > 5)
            {
                angle_out = angle_in < 0 ? 0.3 : -0.3;
            }
            a_SwerveDrive->crabDriveUpdate (angle_out, -0.2, a_Gyro->GetAngle ());
            a_CFS->AutoCollect ();
            break;
        case kShoot4: // attempt to shoot
            break;
        default:
            break;
    }
}

void Autonomous::AutonomousStart5(){

    a_AutoState5 = kArmMove5;
    a_Gyro->Zero();

}



void Autonomous::AutonomousPeriodic5(){

    AutoState5 nextState = a_AutoState5;

    switch(a_AutoState5){

	    case kAutoIdle5:
		    IDontLikeExercise();

		    break;

	    case kArmMove5:
	    	// if(!MoveDaArm(25)){
                //MoveDaArm(ARM_DEFAULT_POSITION);

           // } else {

            nextState = kDriveBack5;

          //  }


		    break;

        case kDriveBack5:
           if(!IHaveAProposal(0.4, 180.0, ARBITRARY_DIST_BACKWARDS)){
               // DriveDist(ARBITRARY_DIST_BACKWARDS, 0);

           } else {

            nextState = kTurntoShoot5;

           }

            break;
        case kTurntoShoot5:
           if(!TurnTaAngle(15)){
            

           } else {

            nextState = kShootBalls5;

           }

            break;
        

        case kShootBalls5:
           if(!RootyTootyShooty(AUTO_START_BALL_NUM)){
               
           } else {

            nextState = kAutoIdle5;

           }

            break;
        
	}

	a_AutoState5 = nextState;


}








void Autonomous::IDontLikeExercise(){

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

    double current = a_CFS->GetArmAngle();
    // frc::SmartDashboard::PutNumber("ArM pOsItIoN", a_CFS->GetArmAngle());
    a_CFS->ArmMovePos(angle);

    return fabs(current - angle) < 0.8;

}


bool Autonomous::DriveDist(double dist, double angle){ // true is done, false is not done

    if((double) fabs(a_SwerveDrive->getAvgDistance()) < dist){
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
    return a_CFS->GetTopBeam();
}


bool Autonomous::RootyTootyShooty(int count){
    currbeam = CheckBallPos();
    
    
    if(BallsShot < ((2 * count)) && currbeam != prevbeam){
        BallsShot++;
        prevbeam = currbeam;
        return false;
    }
    else if(BallsShot < ((2 * count))){
        a_CFS->ShootVelocity(462.5);
        float avg = (fabs(a_CFS->GetWheelSpeedL()) + fabs(a_CFS->GetWheelSpeedR())) / 2.0;
        if(avg >= 400)
        {
            a_CFS->FeedVelocity(1000);
        }
        else
        {
            a_CFS->FeedVelocity(0); 
        }
        
        return false;
    }
    else{
        BallsShot = 0;
        a_CFS->ShootVelocity(0);
        a_CFS->FeedVelocity(0);
        return true;
    }


    
}


bool Autonomous::TurnTaAngle(float angle){
    
    if(fabs(a_Gyro->GetAngle(0) - angle) >= 1){
        a_SwerveDrive->turnToAngle(a_Gyro->GetAngle(0), angle);
        frc::SmartDashboard::PutNumber("Encoder average?????", a_SwerveDrive->getAvgDistance());
        return false;
    } else {
        a_SwerveDrive->swerveUpdate(0, 0, 0, a_Gyro->GetAngle(0), true);
        frc::SmartDashboard::PutNumber("We done????? ", a_SwerveDrive->getAvgDistance());
        return true;

    }





}


bool Autonomous::IHaveAProposal(float speed, float dir, float dist){ // true is done, false is not done

    if(fabs(a_SwerveDrive->getAvgDistance()) < dist){

        if (a_SwerveDrive->getAvgDistance() > (0.50 * (dist))){
		    a_SwerveDrive->GoToTheDon(speed / 2, dir, dist, a_Gyro->GetAngle(0));

		} else {
            a_SwerveDrive->GoToTheDon(speed, dir, dist, a_Gyro->GetAngle(0));
		
        }
        frc::SmartDashboard::PutNumber("Encoder average?????", a_SwerveDrive->getAvgDistance());
        return false;

    } else {
        a_SwerveDrive->swerveUpdate(0, 0, 0, a_Gyro->GetAngle(0), true);
        frc::SmartDashboard::PutNumber("We done????? ", a_SwerveDrive->getAvgDistance());
        return true;

    }
            

}
#endif