
#include "SwerveModule.h"

SwerveModule::SwerveModule(int driveID, int steerID, int steerEncID):
driveMotor(driveID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
steerMotor(steerID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
driveEnc(driveMotor.GetEncoder()),
steerEncNEO(steerMotor.GetEncoder()),
rawSteerEnc(steerEncID),
steerEnc(rawSteerEnc),
drivePID(1, 0, 0),
steerPID(0, 0, 0)
{ 
    
}
void SwerveModule::setDriveSpeed(float target)
{
    driveMotor.Set(target);
}

void SwerveModule::setSteerSpeed(float target)
{
    steerMotor.Set(target);
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
    float angle = (fmod(temp, TICKS_STEERING) / TICKS_STEERING) * 360;

    float adjusted = angle;
    if(angle < 0)
    {
        adjusted += 360; 
    }

    return adjusted;
}

void SwerveModule::driveDistance(float current, float setpoint)
{
    float speed = drivePID.Calculate(current, setpoint); // Calculates scaled output based off of encoder feedback.
    driveMotor.Set(0.3 * speed);
}

void SwerveModule::setDrivePID(float p, float i, float d)
{
    // aaaa
}