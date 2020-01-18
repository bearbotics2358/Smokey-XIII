

#pragma once

#include <frc/WPILib.h>
#include <Shooty.h>
#include <SwerveDrive.h>
#include <Climby.h>
#include <Collecty.h>
#include <frc/Joystick.h> 
#include <Prefs.h>
// #include <JrimmyGyro.h>




enum AutoState0 { // Encoders
	kAutoIdle0 = 0,
	kDriveAway0
};

enum AutoState1 { // Encoders
	kAutoIdle1 = 0,
	kShoot1,
    kDriveAway1
};

enum AutoState2 { // T.O.F and Encoders
	kAutoIdle2 = 0,
	kShoot2,
    kTurnToParallel2,
    kDriveToWall2,
    kDriveBackThroughThreeBalls2,
    kSecondShoot2
};

enum AutoState3 { // T.O.F and Encoders
	kAutoIdle3 = 0,
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
	Autonomous(int ButtonsID);
	void Init();
	//void UpdateGameData();
	//void DecidePath();
	//void DecidePath(int intent);
	//int GetCurrentPath();
	//void StartPathMaster();
	//void StartPathMaster(int path);
	//void PeriodicPathMaster();
	//void PeriodicPathMaster(int path);
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


 private:

	// JrimmyGyro a_Gyro;

	AutoState0 a_AutoState0;
	AutoState1 a_AutoState1;
	AutoState2 a_AutoState2;
    AutoState3 a_AutoState3;
    AutoState4 a_AutoState4;

    frc::Joystick a_buttonBox;


};