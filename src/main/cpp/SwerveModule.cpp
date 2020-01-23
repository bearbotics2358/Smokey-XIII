
#include "SwerveModule.h"

SwerveModule::SwerveModule(int driveID, int steerID, int steerEncID):
driveMotor(driveID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
steerMotor(steerID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
driveEnc(driveMotor.GetEncoder()),
steerEncNEO(steerMotor.GetEncoder()),
rawSteerEnc(steerEncID),
steerEnc(rawSteerEnc),
drivePID(0.8, 0, 0),
steerPID(1.2, 0, 0.2)
{ 
    steerPID.EnableContinuousInput(0.0, 360.0); // Fixes wrap-around: SUPER CONVENIENT C:
}
void SwerveModule::setDriveSpeed(float target)
{
    driveMotor.Set(target);
}

void SwerveModule::setSteerSpeed(float target)
{
    steerMotor.Set(target);
}

float SwerveModule::getDriveSpeed(void)
{
    float ret = driveEnc.GetVelocity() / driveEnc.GetVelocityConversionFactor();
    return ret;
}

float SwerveModule::getDistanceRaw(void)
{
    float ret = driveEnc.GetPosition() / driveEnc.GetPositionConversionFactor();
    return ret;
}

float SwerveModule::getDistance(void)
{
    float ret = driveEnc.GetPosition();
    return ret;
}

void SwerveModule::resetDriveEncoder(void)
{
    driveEnc.SetPosition(0);
}

float SwerveModule::getAngleRaw(void)
{
    float ret = steerEncNEO.GetPosition();
    return ret;
}

float SwerveModule::getAngle(void)
{
    float temp = getAngleRaw(); // get raw position
    float angle = (fmod(temp, TICKS_STEERING) / TICKS_STEERING) * 360; // convert to angle in degrees

    float adjusted = angle;
    if(angle < 0)
    {
        adjusted += 360; // bounds to 0-360
    }

    return adjusted;
}

float SwerveModule::getAngleTest(void)
{
    float ret = steerEncNEO.GetPosition() / steerEncNEO.GetPositionConversionFactor();
    return ret;
}

void SwerveModule::goToPosition(float current, float setpoint)
{
    float speed = drivePID.Calculate(current, setpoint); // Calculates scaled output based off of encoder feedback.
    frc::SmartDashboard::PutNumber("velocity loop setpoint: ", speed);   
    speed = speed / 68;  // EXTREMELY temporary constant, will need to fix at some point
    driveMotor.Set(0.25 * speed);
}

void SwerveModule::steerToAng(float current, float setpoint)
{
    float speed = steerPID.Calculate(current, setpoint);  
    speed = speed / 270; // temp solution                                                          
    steerMotor.Set(speed);
}

void SwerveModule::setDriveVelocity(float percent)
{
    float change = percent * 300;
    goToPosition(getDistance(), getDistance() + change);
}
