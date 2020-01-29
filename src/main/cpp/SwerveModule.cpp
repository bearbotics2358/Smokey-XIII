
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

void SwerveModule::goToPosition(float current, float setpoint)
{
    float speed = drivePID.Calculate(current, setpoint); // Calculates scaled output based off of encoder feedback.
    frc::SmartDashboard::PutNumber("velocity loop setpoint: ", speed);   
    speed = speed / 68;  // EXTREMELY temporary constant, will need to fix at some point
    driveMotor.Set(0.4 * speed);
}

void SwerveModule::steerToAng(float current, float setpoint) // the twO
{
    float speed = steerPID.Calculate(current, setpoint);  
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
    goToPosition(getDistance(), getDistance() + change);
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

float SwerveModule::adjustAngle(float currentAngle, float targetAngle) {
    double kappa = currentAngle - targetAngle; 
    if(kappa > 180) {
        currentAngle -= 360;  
    } else if(kappa < -180) {
        currentAngle += 360; 
    }
    float distOfAngle = targetAngle - currentAngle;

    if(distOfAngle > 90) {
        targetAngle -= 180; 
    } 

    float ahhhhhhhhhhhhhhhhhhhhhHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH = 0; 

    return ahhhhhhhhhhhhhhhhhhhhhHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH; 
}

