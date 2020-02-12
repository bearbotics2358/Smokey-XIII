

#pragma once

// #include <frc/WPILib.h>
#include <SwerveDrive.h>
#include <Climby.h>
#include <CFS.h>
#include <frc/Joystick.h> 
#include <frc/Timer.h>
#include <Prefs.h>
#include <JrimmyGyro.h>




enum AutoState0 { // Encoders
	kAutoIdle0 = 0,
	kArmMove0,
	kDriveAway0
};

enum AutoState1 { // Encoders
	kAutoIdle1 = 0,
	kArmMove1,
	kBallFind1,
	kShoot1,
    kDriveAway1
};

enum AutoState2 { // T.O.F and Encoders
	kAutoIdle2 = 0,
	kArmMove2,
	kShoot2,
    kTurnToParallel2,
    kDriveToWall2,
    kDriveBackThroughThreeBalls2,
    kSecondShoot2
};

enum AutoState3 { // T.O.F and Encoders
	kAutoIdle3 = 0,
	kArmMove3,
	kShoot3,
    kTurnToParallel3,
    kDriveToWall3,
    kDriveBackThroughFiveBalls3,
    kDriveForwardThroughControlPanel3,
    kSecondShoot3
};


/*                     depending on width of the bot and width between 2 balls behind the control panel
enum AutoState3 {
	kAutoIdle3 = 0,
	kShoot3,
    kTurnToParallel3,
    kDriveToWall3,
    kDriveBackThroughControlPanel,
    kCollectTwoBalls,
    kDriveForwardThroughControlPanel,
    kSecondShoot2
};
*/

enum AutoState4 { // Uses vision
	kAutoIdle4 = 0,
	kArmMove4,
	kShoot4,
    kTurnToTruss4,
    kDrivetoBalls4,
    kMoveAway4,
    kSecondShoot4
};


// add more vision versions later


class Autonomous
{
 public:
	Autonomous(JrimmyGyro *Gyro, frc::Joystick *ButtonBox, SwerveDrive *SwerveDrive, CFS *CFS);
	void Init();
	//void UpdateGameData();
	void DecidePath();
	void DecidePath(int intent);

	int GetCurrentPath();

	void StartPathMaster();
	void StartPathMaster(int path);

	void PeriodicPathMaster();
	void PeriodicPathMaster(int path);

	void AutonomousStart0();
	void AutonomousPeriodic0();

	void AutonomousStart1();
	void AutonomousPeriodic1();

	void AutonomousStart2();
	void AutonomousPeriodic2();

	void AutonomousStart3();
	void AutonomousPeriodic3();

	void AutonomousStart4();
	void AutonomousPeriodic4();


// ------------------Sub-Routines-------------------------//

	void IDontLikeExercise(); // IDLE
	void waitplz(double anticipate); // Wait
	bool MoveDaArm(double angle); // arm move to angle
	bool DriveDist(double dist, double angle); // Drive a distance based off encoders
	bool CheckBallPos();
	bool RootyTootyShooty(int count); // Shooting balls 




 private:

	
	JrimmyGyro *a_Gyro;
	frc::Joystick *a_ButtonBox;
	SwerveDrive *a_SwerveDrive;
	CFS *a_CFS;
	frc::Timer a_Anticipation;


	AutoState0 a_AutoState0;
	AutoState1 a_AutoState1;
	AutoState2 a_AutoState2;
    AutoState3 a_AutoState3;
    AutoState4 a_AutoState4;


    int autoPathMaster;
	int BallsShot;
	bool prevbeam;
	bool currbeam;


};