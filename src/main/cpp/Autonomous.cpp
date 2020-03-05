
#ifndef LAPTOP
#include <math.h>
#include "Autonomous.h"




Autonomous::Autonomous(JrimmyGyro *Gyro, MQTTHandler *handler, frc::Joystick *ButtonBox, SwerveDrive *SwerveDrive, CFS *CFS, LimeyLight *Lime):
    a_Gyro(Gyro),
    a_handler(handler),
    a_ButtonBox(ButtonBox),
    a_SwerveDrive(SwerveDrive),
    a_CFS(CFS),
    a_Lime(Lime),
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
    limeangle = 0.0;
    drivestart = 0.0;
    look = true;

}

void Autonomous::Init(){
	a_Gyro->Zero();
    a_Gyro->Cal();
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
	    	if(!MoveDaArm(24)) {// !MoveDaArm(ARM_DEFAULT_POSITION)){
                

            } else {

            nextState = kDriveAway0;

           }


		    break;

        case kDriveAway0:
           if(!IHaveAProposal(0.3, 30.0, TO_TRENCH_FROM_LINE)) {//DriveDist(ARBITRARY_DIST_BACKWARDS, 180)){
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
           if(!RootyTootyShooty(AUTO_START_BALL_NUM, AUTO_SHOOT_VELOCITY)){
               // RootyTootyShooty(AUTO_START_BALL_NUM);

           } else {

            nextState = kDriveAway1;

           }

            break;


        case kDriveAway1:
           if(!DriveDist(TO_TRENCH_FROM_LINE, 180.0)){
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
    AutonomousStart5 ();
    a_AutoState3 = kAutoTurnBack3;
    a_Gyro->Zero();
}


void Autonomous::AutonomousPeriodic3(){
    // Call initial drive stuff and shooting
    float angle_in;
    float angle_out;
    bool temp = false;
    switch (a_AutoState3)
    {
        case kAutoIdle3:
            IDontLikeExercise ();
            break;
        case kAutoDo53:
            // Runs through Jason Auto (3 ball)
            AutonomousPeriodic5 ();
            if (a_AutoState5 == kAutoIdle5)
            {
                a_AutoState3 = kAutoTurnBack3;
            }
            break;
        case kAutoTurnBack3:
            a_Lime->ledOff();
            // Turn to 0 degrees after shooting
            if (TurnTaAngle (0))
            {
                a_AutoState3 = kCollectBalls3;
            }
            break;
        case kCollectBalls3: // get 3 balls
            // Checks to see if we need to move out of collecting mode
            // Got rid of MQTT Error check as we have not tested it
            // Bring it back in later:
            // || !a_handler->noErrors ()
            if (a_CFS->count >= 4 || a_SwerveDrive->getAvgDistance () > 100) // Changed distance for 3 ball auto
            {
                // Change to remote viewing and turn limelight off
                a_handler->publish ("view", "/camera/control/claw");
                a_Lime->ledOn();
                a_AutoState3 = kDriveBack3;
            }
            // Read new angle
            angle_in = a_handler->angle;
            angle_out = 0;
            // Direction Changing Logic:
            // angle_in < 0, go Right; angle_in > 0, go Left
            if ((angle_in < 0 ? -angle_in : angle_in) > 5)
            {
                angle_out = angle_in < 0 ? 0.2 : -0.2;
            }
            // Update crab drive stafing and auto collect
            a_SwerveDrive->crabDriveUpdate (angle_out, -1 * AUTO_DRIVE_SPEED, a_Gyro->GetAngle (0));
            a_CFS->AutoCollect ();
            break;
        case kDriveBack3:
            // Drive back to original distance that we shot at during 3 ball auto
            if(!IHaveAProposal(AUTO_DRIVE_SPEED, 0, 100)) { // Need to test distance
                
            } else {
                a_AutoState3 = kTurntoShoot3;
            }
        case kTurntoShoot3:
            // Turn to angle and face the target using limelight
            if (TurnLime (true))
            {   
                a_AutoState3 = kShoot3;
                // a_AutoState3 = kprime3;
            }
            break;
            // Skip because no work
        case kprime3:
            // DO NOT USE, BEAM BREAK NEEDS TO BE RECTIFIED
            if (CheckBallPos())
            {
                a_CFS->FeedVelocity(-100);
            } else {
                a_AutoState3 = kShoot3;
                a_CFS->Feed(0);
            }
            break;

        case kShoot3:
            // Shoot at same velocity as 3 ball, as we are in roughly same spot
            if (RootyTootyShooty (3, 464.0)) // 3 Ball auto velocity
            {
                a_AutoState3 = kAutoIdle3;
            }
            
            break;
        default:
            break;
    }
}


void Autonomous::AutonomousStart4(){
    a_AutoState4 = kArmMove4;
    a_Gyro->Zero();
    a_Lime->ledOn();


}



void Autonomous::AutonomousPeriodic4(){

AutoState4 nextState = a_AutoState4;

    switch(a_AutoState4){

	    case kAutoIdle4:
		    IDontLikeExercise();

		    break;

	    case kArmMove4:
            if(!MoveDaArm(35)){


            } else {

            drivestart = a_SwerveDrive->getAvgDistance();
            nextState = kDriveBackLonger4;

            }

		    break;

        case kDriveBackLonger4:
           if(!GoToMcDonalds(0.4, 180.0, TO_BALL2_FROM_LINE)){
               // DriveDist(ARBITRARY_DIST_BACKWARDS, 0);

           } else {
               

            limeangle = a_Lime->getAngleX();

            nextState = kTurntoShoot4;

           }

            break;
      
        case kTurntoShoot4:
           if(!TurnLime(true)){
            

           } else {

            nextState = kShootBalls4;

           }

            break;
        case kPrime4:
           if(CheckBallPos()){
               a_CFS->FeedVelocity(-100);

            } else {
               nextState = kShootBalls4;

            }

            break;
        

        case kShootBalls4:
           if(!RootyTootyShooty(5, AUTO_SHOOT_VELOCITY5BALL)){
               
           } else {

          
            nextState = kAutoIdle4;

           }

            break;
        

	}

	a_AutoState4 = nextState;

}



void Autonomous::AutonomousStart5(){

    a_AutoState5 = kArmMove5;
    a_Gyro->Zero();
    a_Lime->ledOn();

}



void Autonomous::AutonomousPeriodic5(){

    AutoState5 nextState = a_AutoState5;

    switch(a_AutoState5){

	    case kAutoIdle5:
		    IDontLikeExercise();

		    break;

	    case kArmMove5:
	        if(!MoveDaArm(AUTO_ARM_FINAL_POS)){


            } else {

            drivestart = a_SwerveDrive->getAvgDistance();
            nextState = kDriveBack5;

            }


		    break;

        case kDriveBack5:
           if(!IHaveAProposal(AUTO_DRIVE_SPEED, AUTO_ANGLE_DRIVESTRAIGHT, TO_TRENCH_FROM_LINE)){
               // DriveDist(ARBITRARY_DIST_BACKWARDS, 0);

           } else {
               

            limeangle = a_Lime->getAngleX();

            nextState = kTurntoShoot5;

           }

            break;
      
        case kTurntoShoot5:
           if(!TurnLime(true)){
            

           } else {

            nextState = kShootBalls5;

           }

            break;
        

        case kShootBalls5:
           if(!RootyTootyShooty(AUTO_START_BALL_NUM, AUTO_SHOOT_VELOCITY)){
               
           } else {

            nextState = kAutoIdle5;

           }

            break;
        
	}

	a_AutoState5 = nextState;


}








void Autonomous::IDontLikeExercise(){

    a_SwerveDrive->swerveUpdate(0, 0, 0, a_Gyro->GetAngle(0), true);
    a_CFS->Shoot(0);
    a_CFS->Feed(0);
    a_CFS->Collect(0);
    a_CFS->ArmMove(0);

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

    if(fabs(a_CFS->GetArmAngle() - angle) >= 1){
        a_CFS->setArmAngle(angle);
        frc::SmartDashboard::PutNumber("Encoder average?????", a_SwerveDrive->getAvgDistance());
        return false;


    } else {
        a_CFS->ArmMove(0);
        frc::SmartDashboard::PutNumber("We done????? ", a_SwerveDrive->getAvgDistance());
        return true;
    }

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


bool Autonomous::RootyTootyShooty(int count, float velocity){
    currbeam = CheckBallPos();
    
    
    if(BallsShot < ((2 * count)) + 1 && currbeam != prevbeam){
        BallsShot++;
        prevbeam = currbeam;
        return false;
    }
    else if(BallsShot < ((2 * count))){
        a_CFS->ShootVelocity(velocity);
        float avg = (fabs(a_CFS->GetWheelSpeedL()) + fabs(a_CFS->GetWheelSpeedR())) / 2.0;
        if(avg >= .98 * velocity)
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

    if(fabs(a_SwerveDrive->getAvgDistance()) < (dist + drivestart)){

        if (a_SwerveDrive->getAvgDistance() > (0.80 * (dist + drivestart))){
		    a_SwerveDrive->GoToTheDon(speed / 2, dir, dist, a_Gyro->GetAngle(0));
            a_CFS->ShootVelocity(AUTO_SHOOT_VELOCITY);
		} else {
            a_SwerveDrive->GoToTheDon(speed, dir, dist, a_Gyro->GetAngle(0));
            a_CFS->ShootVelocity(0);
        }
        frc::SmartDashboard::PutNumber("Encoder average?????", a_SwerveDrive->getAvgDistance());
        return false;

    } else {
        a_SwerveDrive->swerveUpdate(0, 0, 0, a_Gyro->GetAngle(0), true);
        frc::SmartDashboard::PutNumber("We done????? ", a_SwerveDrive->getAvgDistance());
        return true;

    }
            

}

// Turn to target with limelight
// False = CW, True = CCW
bool Autonomous::TurnLime(bool dir){
    
    if(a_Lime->isTarget()){
        if(fabs((a_Lime->getAngleX())) >= 1.5){
            a_SwerveDrive->makeShiftTurn(a_Lime->calcZAxis());
            // frc::SmartDashboard::PutNumber("Encoder average?????", a_SwerveDrive->getAvgDistance());
            return false;


        } else {
            a_SwerveDrive->swerveUpdate(0, 0, 0, a_Gyro->GetAngle(0), true);
            // frc::SmartDashboard::PutNumber("We done????? ", a_SwerveDrive->getAvgDistance());
            a_Lime->ledOff();
            return true;

        }
    } else {
        // Changes direction based on boolean
        if(dir) {
            a_SwerveDrive->makeShiftTurn(.1);
        } else {
            a_SwerveDrive->makeShiftTurn(-.1);
        }
        
        return false;
    }


}

bool Autonomous::GoToMcDonalds(float speed, float dir, float dist){ // true is done, false is not done

    if(fabs(a_SwerveDrive->getAvgDistance()) < (dist + drivestart)){

        if (a_SwerveDrive->getAvgDistance() > (0.80 * (dist + drivestart))){
		    a_SwerveDrive->GoToTheDon(speed / 2, dir, dist, a_Gyro->GetAngle(0));
            a_CFS->ShootVelocity(AUTO_SHOOT_VELOCITY);
            a_CFS->AutoCollect();
		} else {
            a_SwerveDrive->GoToTheDon(speed, dir, dist, a_Gyro->GetAngle(0));
            a_CFS->AutoCollect();
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
