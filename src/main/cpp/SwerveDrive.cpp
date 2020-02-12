
#include "SwerveDrive.h"

SwerveDrive::SwerveDrive(SwerveModule *FL_Ptr, SwerveModule *FR_Ptr, SwerveModule *BL_Ptr, SwerveModule *BR_Ptr):
FL_Module(FL_Ptr),
FR_Module(FR_Ptr),
BL_Module(BL_Ptr),
BR_Module(BR_Ptr)
{

}

void SwerveDrive::swerveUpdate(float xIn, float yIn, float zIn, float gyroIn, bool fieldOriented) // Swerve Kinematics - Manages each module
{
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

	float scalar = 1; // scalar to adjust if speed is too high
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

	FL_Module->setDriveSpeed(0.35 * FL_Speed);
	FL_Module->steerToAng(currentFL, FL_Angle);

	FR_Module->setDriveSpeed(0.35 * FR_Speed);
	FR_Module->steerToAng(currentFR, FR_Angle);

 	BL_Module->setDriveSpeed(0.35 * BL_Speed);
	BL_Module->steerToAng(currentBL, BL_Angle);

	BR_Module->setDriveSpeed(0.35 * BR_Speed);
	BR_Module->steerToAng(currentBR, BR_Angle);
}


bool SwerveDrive::needsAngOpt(float currentAngle, float targetAngle)
{
	float currentTemp = currentAngle;
	float targetTemp = targetAngle;

	if(currentTemp < 360 && currentTemp > 180)
		currentTemp -= 360;
	else if(currentTemp > -360 && currentTemp < -180)
		currentTemp += 360;

	
	//           0
	// 
	// 90                -90
	//	       
	//       180 or -180

	
	if(fabs(currentTemp) < 90 && fabs(targetTemp) < 90)
	{
		if(fabs(currentTemp - targetTemp) > 90)
		{
			return true;
		}
	}
	else if((fabs(currentTemp) >= 90 && fabs(targetTemp) < 90) || (fabs(targetTemp) >= 90 && fabs(currentTemp) < 90))
	{
		if(fabs(currentTemp - targetTemp) > 90)
		{
			return true;
		}
	}
	else
	{
		if(currentTemp < 0 && targetTemp > 0)
		{
			if(fabs((360 + currentTemp) - targetTemp) > 90)
			{
				return true;
			}
		} 
		else if(currentTemp > 0 && targetTemp < 0)
		{
			if(fabs((360 + targetTemp) - currentTemp) > 90)
			{
				return true;
			}
		}
	}
		/*
		if(targetTemp < 0) // bounds to +/- 180
			targetTemp += 180;
		else
			targetTemp -= 180;
		FL_Speed *= -1;
		*/
	return false;
}