
#include "SwerveDrive.h"

SwerveDrive::SwerveDrive(SwerveModule *FL_Ptr, SwerveModule *FR_Ptr, SwerveModule *BL_Ptr, SwerveModule *BR_Ptr):
FL_Module(FL_Ptr),
FR_Module(FR_Ptr),
BL_Module(BL_Ptr),
BR_Module(BR_Ptr),
anglePID(0.03, 0.0 , 0.0),
jenkinsTheCrabPID(5, 0.0, 0.0)
/* FL_Input(0),
FR_Input(1),
BL_Input(2),
BR_Input(3),
FL_Encoder(FL_Input),
FR_Encoder(FR_Input),
BL_Encoder(BL_Input),
BR_Encoder(BR_Input)*/
{
	anglePID.EnableContinuousInput(0.0, 360.0);
	jenkinsTheCrabPID.EnableContinuousInput(0.0, 360.0);
}

void SwerveDrive::swerveUpdate(float xIn, float yIn, float zIn, float gyroIn, bool fieldOriented) // Swerve Kinematics - Manages each module
{
	crab = false;
	
    float xInput = xIn; // Temp variables to avoid corrupting the data
    float yInput = yIn;
    float zInput = zIn;

	if(fieldOriented) // Makes joystick inputs field oriented
	{
		float gyroRadians = gyroIn * M_PI / 180; 
		float temp = yInput * cos(gyroRadians) + xInput * sin(gyroRadians);
		xInput = -yInput * sin(gyroRadians) + xInput * cos(gyroRadians);
		yInput = temp;
	}
	
	

	float r =  sqrt((DRIVE_LENGTH * DRIVE_LENGTH) + (DRIVE_WIDTH * DRIVE_WIDTH)); // radius of the drive base

	float a = xInput - zInput * (DRIVE_LENGTH / r); // temp variables to simplify math
	float b = xInput + zInput * (DRIVE_LENGTH / r);
	float c = yInput - zInput * (DRIVE_WIDTH / r);
	float d = yInput + zInput * (DRIVE_WIDTH / r);

	float FL_Speed = sqrt(b*b + c*c);
    float FR_Speed = sqrt(b*b + d*d);
    float BL_Speed = sqrt(a*a + d*d);
    float BR_Speed = sqrt(a*a + c*c);

	float FL_Angle = atan2(b,c) * 180/M_PI; // calculates wheel angles and converts to radians
    float FR_Angle = atan2(b,d) * 180/M_PI;
    float BL_Angle = atan2(a,c) * 180/M_PI;
	float BR_Angle = atan2(a,d) * 180/M_PI;

	if(FL_Angle < 0) 
	{
		FL_Angle = FL_Angle + 360;	
	}

	if(FR_Angle < 0) 
	{
		FR_Angle = FR_Angle + 360;	
	}

	if(BL_Angle < 0) 
	{
		BL_Angle = BL_Angle + 360;	
	}

	if(BR_Angle < 0) 
	{
		BR_Angle = BR_Angle + 360;	
	}

	float max = std::max(std::max(FR_Speed, FL_Speed), std::max(BR_Speed, BL_Speed)); // find max speed value

    if(max > 1) // scale inputs respectively so no speed is greater than 1
	{
    	FL_Speed /= max;
    	FR_Speed /= max;
    	BL_Speed /= max;
    	BR_Speed /= max;
    }

	float scalar = 0.8; // scalar to adjust if speed is too high
	FL_Speed *= scalar;
    FR_Speed *= scalar;
    BL_Speed *= scalar;
    BR_Speed *= scalar;

	float currentFL = FL_Module->getAngle(); 
	float currentFR = FR_Module->getAngle();
	float currentBR = BR_Module->getAngle(); 
	float currentBL = BL_Module->getAngle();
	
	float deadzoneCheck = sqrt(xIn * xIn + yIn * yIn);

	if(deadzoneCheck < 0.15 && fabs(zIn) < 0.01)
	{
		FL_Speed = 0;
		FR_Speed = 0;
		BL_Speed = 0;
		BR_Speed = 0;

		FL_Angle = currentFL;
		FR_Angle = currentFR;
		BL_Angle = currentBL;
		BR_Angle = currentBR;
	}

	// update speeds and angles 

	/* FL_Module->setDriveSpeed(FL_Speed);
	FL_Module->steerToAng(FL_Angle);

	FR_Module->setDriveSpeed(FR_Speed);
	FR_Module->steerToAng(FR_Angle);

 	BL_Module->setDriveSpeed(BL_Speed);
	BL_Module->steerToAng(BL_Angle);

	BR_Module->setDriveSpeed(BR_Speed);
	BR_Module->steerToAng(BR_Angle);	
	*/

	if(FL_Module->adjustAngle(FL_Angle)){
		// frc::SmartDashboard::PutNumber("FL Set: ", FL_Module->setDriveVelocity(-FL_Speed));
		FL_Module->setDriveSpeed(-FL_Speed);
	} else {
		// frc::SmartDashboard::PutNumber("FL Set: ", FL_Module->setDriveVelocity(FL_Speed));
		FL_Module->setDriveSpeed(FL_Speed);
	}

	if(FR_Module->adjustAngle(FR_Angle)){
		// frc::SmartDashboard::PutNumber("FR Set: ", FR_Module->setDriveVelocity(-FR_Speed));
		FR_Module->setDriveSpeed(-FR_Speed);
	} else {
		// frc::SmartDashboard::PutNumber("FR Set: ", FR_Module->setDriveVelocity(-FR_Speed));
		FR_Module->setDriveSpeed(FR_Speed);
	}

 	if(BL_Module->adjustAngle(BL_Angle)){
		// frc::SmartDashboard::PutNumber("BL Set: ", FL_Module->setDriveVelocity(-BL_Speed));
		BL_Module->setDriveSpeed(-BL_Speed);
	} else {
		// frc::SmartDashboard::PutNumber("BL Set: ", FL_Module->setDriveVelocity(-BL_Speed));
		BL_Module->setDriveSpeed(BL_Speed);
	}

	if(BR_Module->adjustAngle(BR_Angle)){
		// frc::SmartDashboard::PutNumber("BR Set: ", FL_Module->setDriveVelocity(-BR_Speed));
		BR_Module->setDriveSpeed(-BR_Speed);
	} else {
		// frc::SmartDashboard::PutNumber("BR Set: ", FL_Module->setDriveVelocity(-BR_Speed));
		BR_Module->setDriveSpeed(BR_Speed);
	}
}

float SwerveDrive::lockZ(float gyro)
{
	float ret = std::clamp(jenkinsTheCrabPID.Calculate(gyro, holdAngle) / 270.0, -0.5, 0.5);
	return ret;
}

void SwerveDrive::crabDriveUpdate(float xIn, float yIn, float gyroIn) // 
{
	if(!crab)
	{
		holdAngle = gyroIn;
		crab = true;
	}

	float xInput = xIn; // Temp variables to avoid corrupting the data
    float yInput = yIn;
    float zInput = lockZ(gyroIn);

	float gyroRadians = gyroIn * PI / 180; 
	float temp = yInput * cos(gyroRadians) + xInput * sin(gyroRadians);
	xInput = -yInput * sin(gyroRadians) + xInput * cos(gyroRadians);
	yInput = temp;
	
	
	

	float r =  sqrt((DRIVE_LENGTH * DRIVE_LENGTH) + (DRIVE_WIDTH * DRIVE_WIDTH)); // radius of the drive base

	float a = xInput - zInput * (DRIVE_LENGTH / r); // temp variables to simplify math
	float b = xInput + zInput * (DRIVE_LENGTH / r);
	float c = yInput - zInput * (DRIVE_WIDTH / r);
	float d = yInput + zInput * (DRIVE_WIDTH / r);

	float FL_Speed = sqrt(b*b + c*c);
    float FR_Speed = sqrt(b*b + d*d);
    float BL_Speed = sqrt(a*a + d*d);
    float BR_Speed = sqrt(a*a + c*c);

	float FL_Angle = atan2(b,c) * 180/PI; // calculates wheel angles and converts to radians
    float FR_Angle = atan2(b,d) * 180/PI;
    float BL_Angle = atan2(a,c) * 180/PI;
	float BR_Angle = atan2(a,d) * 180/PI;

	if(FL_Angle < 0) 
	{
		FL_Angle = FL_Angle + 360;	
	}

	if(FR_Angle < 0) 
	{
		FR_Angle = FR_Angle + 360;	
	}

	if(BL_Angle < 0) 
	{
		BL_Angle = BL_Angle + 360;	
	}

	if(BR_Angle < 0) 
	{
		BR_Angle = BR_Angle + 360;	
	}

	float max = std::max(std::max(FR_Speed, FL_Speed), std::max(BR_Speed, BL_Speed)); // find max speed value

    if(max > 1) // scale inputs respectively so no speed is greater than 1
	{
    	FL_Speed /= max;
    	FR_Speed /= max;
    	BL_Speed /= max;
    	BR_Speed /= max;
    }

	float scalar = 0.8; // scalar to adjust if speed is too high
	FL_Speed *= scalar;
    FR_Speed *= scalar;
    BL_Speed *= scalar;
    BR_Speed *= scalar;

	float currentFL = FL_Module->getAngle(); 
	float currentFR = FR_Module->getAngle();
	float currentBR = BR_Module->getAngle(); 
	float currentBL = BL_Module->getAngle();
	
	float deadzoneCheck = sqrt(xIn * xIn + yIn * yIn);

	if(deadzoneCheck < 0.15 && fabs(zInput) < 0.1)
	{
		FL_Speed = 0;
		FR_Speed = 0;
		BL_Speed = 0;
		BR_Speed = 0;

		FL_Angle = currentFL;
		FR_Angle = currentFR;
		BL_Angle = currentBL;
		BR_Angle = currentBR;
	}

	// update speeds and angles 

	if(FL_Module->adjustAngle(FL_Angle)){
		FL_Module->setDriveSpeed(-1 * FL_Speed);
	} else {
		FL_Module->setDriveSpeed(FL_Speed);
	}

	if(FR_Module->adjustAngle(FR_Angle)){
		FR_Module->setDriveSpeed(-1 * FR_Speed);
	} else {
		FR_Module->setDriveSpeed(FR_Speed);
	}

 	if(BL_Module->adjustAngle(BL_Angle)){
		BL_Module->setDriveSpeed(-1 * BL_Speed);
	} else {
		BL_Module->setDriveSpeed(BL_Speed);
	}

	if(BR_Module->adjustAngle(BR_Angle)){
		BR_Module->setDriveSpeed(-1 * BR_Speed);
	} else {
		BR_Module->setDriveSpeed(BR_Speed);
	}
	
}

void SwerveDrive::driveDistance(float dist, float direction)
{ 
	float dist2ElectricBoogalo = dist / INCHES_PER_TICK;

	/*
	if(FL_Module->adjustAngle(direction)) {
		FL_Module->goToPosition(-1.0 * dist2ElectricBoogalo);
	} else {
		FL_Module->goToPosition(dist2ElectricBoogalo);
	}
	
	if(FR_Module->adjustAngle(direction)) {
		FR_Module->goToPosition(-1.0 * dist2ElectricBoogalo);
	} else {
		FR_Module->goToPosition(dist2ElectricBoogalo);
	}

	if(BL_Module->adjustAngle(direction)) {
		BL_Module->goToPosition(-1.0 * dist2ElectricBoogalo);
	} else {
		BL_Module->goToPosition(dist2ElectricBoogalo);
	}

	if(BR_Module->adjustAngle(direction)) {
		BR_Module->goToPosition(-1.0 * dist2ElectricBoogalo);
	} else {
		BR_Module->goToPosition(dist2ElectricBoogalo);
	}
	*/
    	
  		FL_Module->steerToAng(direction);
		FR_Module->steerToAng(direction);
		BL_Module->steerToAng(direction);
		BR_Module->steerToAng(direction);
		
		FL_Module->goToPosition(dist2ElectricBoogalo);
		FR_Module->goToPosition(dist2ElectricBoogalo);
		BL_Module->goToPosition(dist2ElectricBoogalo);
		BR_Module->goToPosition(dist2ElectricBoogalo); 
	

}

void SwerveDrive::resetDrive() {
	FL_Module->resetDriveEncoder();
	FR_Module->resetDriveEncoder();
	BL_Module->resetDriveEncoder();
	BR_Module->resetDriveEncoder();
}

float SwerveDrive::getAvgDistance(void)
{
	float ret = (fabs(FL_Module->getDistance()) + fabs(FR_Module->getDistance()) + fabs(BL_Module->getDistance()) + fabs(BR_Module ->getDistance()))/4.0;
	return ret * INCHES_PER_TICK;
}

void SwerveDrive::turnToAngle(float gyro, float angle) {

	if(gyro < 0)
    {
        gyro = fmod(gyro, -360);
        gyro += 360;
    }
    else
    {
        gyro = fmod(gyro, 360);
    }

	 FL_Module->steerToAng(45);
	 FR_Module->steerToAng(135);
	 BL_Module->steerToAng(225);
	 BR_Module->steerToAng(315);

	float speed = std::clamp(anglePID.Calculate(gyro, angle), -0.2, 0.2); // calculates a speed we need to go based off our current sensor and target position
	 FL_Module->setDriveSpeed(speed);
	 FR_Module->setDriveSpeed(speed);	 
	 BL_Module->setDriveSpeed(speed);
	 BR_Module->setDriveSpeed(speed);
 }

 void SwerveDrive::makeShiftTurn(float speed) {
	 FL_Module->steerToAng(45);
	 FR_Module->steerToAng(135);
	 BL_Module->steerToAng(225);
	 BR_Module->steerToAng(315);

	 FL_Module->setDriveSpeed(speed);
	 FR_Module->setDriveSpeed(speed);	 
	 BL_Module->setDriveSpeed(speed);
	 BR_Module->setDriveSpeed(speed);
 }