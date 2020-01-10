
#include "SwerveDrive.h"

SwerveDrive::SwerveDrive(SwerveModule *FL_Ptr, SwerveModule *FR_Ptr, SwerveModule *BL_Ptr, SwerveModule *BR_Ptr):
FL_Module(FL_Ptr),
FR_Module(FR_Ptr),
BL_Module(BL_Ptr),
BR_Module(BR_Ptr)
{
    fieldOriented = true;
}

void SwerveDrive::updateField(float xIn, float yIn, float zIn, float gyroIn)
{
    float xInput = xIn; // Temp variables to avoid corrupting the data
    float yInput = yIn;
    float zInput = zIn;

	float gyroRadians = gyroIn * PI / 180; // Makes field oriented
	float temp = yInput * cos(gyroRadians) + xInput * sin(gyroRadians);
	xInput = -yInput * sin(gyroRadians) + xInput * cos(gyroRadians);
	yInput = temp;

	float radius = sqrt(pow(xInput, 2) + pow(yInput, 2));  // Checks deadzones
	bool inDeadzone = (radius < DEADZONE ? true : false);

	float r =  sqrt((DRIVE_LENGTH * DRIVE_LENGTH) + (DRIVE_WIDTH * DRIVE_WIDTH));

	float a = xInput - zInput * (DRIVE_LENGTH / r);
	float b = xInput + zInput * (DRIVE_LENGTH / r);
	float c = yInput - zInput * (DRIVE_WIDTH / r);
	float d = yInput + zInput * (DRIVE_WIDTH / r);

	float FL_Speed = sqrt(b*b + c*c);
    float FR_Speed = sqrt(b*b + d*d);
    float BL_Speed = sqrt(a*a + d*d);
    float BR_Speed = sqrt(a*a + c*c);

	float FL_Angle = atan2(b,c) * 180/PI;
    float FR_Angle = atan2(b,d) * 180/PI;
    float BR_Angle = atan2(a,d) * 180/PI;
    float BL_Angle = atan2(a,c) * 180/PI;

	float max = std::max(std::max(FR_Speed, FL_Speed), std::max(BR_Speed, BL_Speed));

    if(max > 1)
	{
    	FR_Speed /= max;
    	FL_Speed /= max;
    	BR_Speed /= max;
    	BL_Speed /= max;
    }
	float scalar = 1;
	FR_Speed *= scalar;
    FL_Speed *= scalar;
    BR_Speed *= scalar;
    BL_Speed *= scalar;

	float currentFL = FL_SwerveModule.GetAngle(); 
	float currentFR = FR_SwerveModule.GetAngle();
	float currentBR = BR_SwerveModule.GetAngle(); 
	float currentBL = BL_SwerveModule.GetAngle();

	if(NeedsAngOpt(currentFL, FL_Angle))
	{
		if(FL_Angle < 0)
			FL_Angle += 180;
		else
			FL_Angle -= 180;
		FL_Speed *= -1;
	}
	if(NeedsAngOpt(currentFR, FR_Angle))
	{
		if(FR_Angle < 0)
			FR_Angle += 180;
		else
			FR_Angle -= 180;
		FR_Speed *= -1;
	}
	if(NeedsAngOpt(currentBR, BR_Angle))
	{
		if(BR_Angle < 0)
			BR_Angle += 180;
		else
			BR_Angle -= 180;
		BR_Speed *= -1;
	}
	if(NeedsAngOpt(currentBL, BL_Angle))
	{
		if(BL_Angle < 0)
			BL_Angle += 180;
		else
			BL_Angle -= 180;
		BL_Speed *= -1;
	}

	if(inDeadzone && zIn == 0)
	{
		FR_Speed = 0;
		FL_Speed = 0;
		BR_Speed = 0;
		BL_Speed = 0;

		FR_Angle = FR_SwerveModule.GetAngle();
		FL_Angle = FL_SwerveModule.GetAngle();
		BR_Angle = BR_SwerveModule.GetAngle();
		BL_Angle = BL_SwerveModule.GetAngle();
	}
	// FR_SwerveModule.UpdateSpeedPID(FR_Speed);
	FR_SwerveModule.UpdateSpeed(FR_Speed);
	FR_SwerveModule.UpdateAnglePID(FR_Angle);
	// frc::SmartDashboard::PutNumber("FR Angle: ", FR_Angle);
	frc::SmartDashboard::PutNumber("FR speed: ", FR_Speed);
	// FR_SwerveModule.UpdateAngle(FR_Angle);

	// FL_SwerveModule.UpdateSpeedPID(FL_Speed);
 	FL_SwerveModule.UpdateSpeed(FL_Speed);
	FL_SwerveModule.UpdateAnglePID(FL_Angle);
	// frc::SmartDashboard::PutNumber("FL Angle: ", FL_Angle);
	frc::SmartDashboard::PutNumber("FL speed: ", FL_Speed);
	// FL_SwerveModule.UpdateAngle(FL_Angle);

	// BL_SwerveModule.UpdateSpeedPID(BL_Speed);
	BL_SwerveModule.UpdateSpeed(BL_Speed);
	BL_SwerveModule.UpdateAnglePID(BL_Angle);
	// frc::SmartDashboard::PutNumber("BL Angle: ", BL_Angle);
	frc::SmartDashboard::PutNumber("BL speed: ", BL_Speed);
	// BL_SwerveModule.UpdateAngle(BL_Angle);

	// BR_SwerveModule.UpdateSpeedPID(BR_Speed);
	BR_SwerveModule.UpdateSpeed(BR_Speed);
	BR_SwerveModule.UpdateAnglePID(BR_Angle);
	// frc::SmartDashboard::PutNumber("BR Angle: ", BR_Angle);
	frc::SmartDashboard::PutNumber("BR speed: ", BR_Speed);
	// BR_SwerveModule.UpdateAngle(BR_Angle);

	
	/*frc::SmartDashboard::PutNumber("Test Speed (FL): ", FL_SwerveModule.GetVelocity());
	frc::SmartDashboard::PutNumber("Test Speed (BL): ", BL_SwerveModule.GetVelocity());
	frc::SmartDashboard::PutNumber("Test Speed (BR): ", BR_SwerveModule.GetVelocity());
	frc::SmartDashboard::PutNumber("Test Speed (FR): ", FR_SwerveModule.GetVelocity());
	*/ // 450 is max velocity
}
}