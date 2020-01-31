
#include "SwerveModule.h"
#include "Math.h"

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
    float speed = drivePID.Calculate(getDistance(), setpoint); // Calculates scaled output based off of encoder feedback. 
    speed = speed / 68;  // EXTREMELY temporary constant, will need to fix at some point
    driveMotor.Set(0.4 * speed);
}

void SwerveModule::steerToAng(float setpoint) // the twO
{
    float speed = steerPID.Calculate(getAngle(), setpoint);  
    speed = speed / 270; // temp solution                                                          
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
    float ret = driveEnc.GetVelocity() / driveEnc.GetVelocityConversionFactor();
    return ret;
}

void SwerveModule::setDriveVelocity(float percent) // the onE
{
    float change = percent * 800;
    goToPosition(getDistance() + change);
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

    steerToAng(tempTarget);

    return changeMade; 
}

/*
    steer module to given angle 
    - return boolean (do we need to change the speed or not?)
        o specify wether or not the direction need to be reversed  
        o still move even if angle doesn't need to be adjusted
*/ 