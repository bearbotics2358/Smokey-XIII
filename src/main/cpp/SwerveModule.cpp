
#include "SwerveModule.h"

SwerveModule::SwerveModule(int driveID, int steerID, int steerEncID):
driveMotor(driveID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
steerMotor(steerID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
driveEnc(driveMotor.GetEncoder()),
steerEncNEO(steerMotor.GetEncoder()),
rawSteerEnc(steerEncID),
steerEnc(rawSteerEnc),
drivePID(0, 0, 0),
steerPID(0, 0, 0)
{ 
    steerPID.EnableContinuousInput(0.0, 360.0);
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

void SwerveModule::goToPosition(float setpoint)
{
    float speed = std::clamp(drivePID.Calculate(getDistance(), setpoint) / 60.0, -0.5, 0.5); // Calculates scaled output based off of encoder feedback. 
    driveMotor.Set(speed);
}

void SwerveModule::steerToAng(float setpoint) // the twO
{
    float speed = std::clamp(steerPID.Calculate(getAngle(), setpoint) / 270.0, -0.5, 0.5);                                           
    steerMotor.Set(speed);
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
    float ret = driveEnc.GetVelocity();
    return ret;
}

void SwerveModule::setDriveVelocity(float percent) // the onE
{
    float currentSpeed = getDriveSpeed();
    float theta = drivePID.Calculate(currentSpeed, percent * DRIVE_VELOCITY);
    driveMotor.Set(theta); 
}

void SwerveModule::updateDrivePID(double pNew, double iNew, double dNew)
{   
    drivePID.SetP(pNew);
    drivePID.SetI(iNew);
    drivePID.SetD(dNew);
}

void SwerveModule::updateSteerPID(double pNew, double iNew, double dNew)
{
    steerPID.SetP(pNew);
    steerPID.SetI(iNew);
    steerPID.SetD(dNew);
}

bool SwerveModule::adjustAngle(float targetAngle) {
    float tempCurrent = getAngle();
    float tempTarget = targetAngle;
    bool changeMade = false; 

    if(tempCurrent - tempTarget > 180) {
        tempCurrent -= 360;  
    } else if(tempCurrent - tempTarget < -180) {
        tempCurrent += 360; 
    }
    float distOfAngle = tempTarget - tempCurrent;

    if(distOfAngle > 90) {
        tempTarget -= 180; 
        changeMade = true;
    } 

    if(distOfAngle < -90)
    {
        tempTarget += 180;
        changeMade = true; 
    }

    if(tempTarget < 0) {
        tempTarget += 360;
    } else if(tempTarget > 360) {
        tempTarget -= 360;
    } // zzzzzzzzzzzzzz

    steerToAng(tempTarget);

    return changeMade; 
}



/*
    steer module to given angle 
    - return boolean (do we need to change the speed or not?)
        o specify wether or not the direction need to be reversed  
        o still move even if angle doesn't need to be adjusted
*/ 