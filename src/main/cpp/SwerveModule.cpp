
#include "SwerveModule.h"

SwerveModule::SwerveModule(int driveID, int steerID, int driveEncID, int steerEncID):
driveMotor(driveID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
steerMotor(steerID, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
rawDriveEnc(driveEncID),
rawSteerEnc(steerEncID),
driveEnc(rawDriveEnc),
steerEnc(rawSteerEnc),
drivePID(0, 0, 0),
steerPID(0, 0, 0)
{ // WIP

}

void SwerveModule::setDriveSpeed(float target)
{
    driveMotor.Set(target);
}

void SwerveModule::setSteerSpeed(float target)
{
    steerMotor.Set(target);
}