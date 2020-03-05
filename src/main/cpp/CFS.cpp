
#include "CFS.h"



CFS::CFS(int shoot1, int shoot2, int feed1, int feed2, int collect, int pivot, int climb, int beam1, int beam2):
    a_ShootLeft(shoot1),
    a_ShootRight(shoot2),
    a_FeedTop(feed1),
    a_FeedBot(feed2),
    a_Collector(collect),
    a_BrokenBeam(beam1),
    a_TopBeam(beam2),
    a_Pivot(pivot, rev::CANSparkMaxLowLevel::MotorType::kBrushless),  
    a_Climber(climb, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
    pivotInput(0),
    a_PivotEncoder(pivotInput),
    armAnglePID(0.02, 0, 0)
{

    a_ShootLeft.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);
    a_ShootRight.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);

    a_ShootLeft.Config_kP(0, 2.5, 0); // 2
    a_ShootLeft.Config_kI(0, 0, 0);
    a_ShootLeft.Config_kD(0, 0.1, 0);
    a_ShootLeft.Config_kF(0, 1.72, 0);

    a_ShootRight.Config_kP(0, 2.5, 0); // 2
    a_ShootRight.Config_kI(0, 0, 0);
    a_ShootRight.Config_kD(0, 0.5, 0);
    a_ShootRight.Config_kF(0, 1.84, 0);
    // p - makes speed more agressive in change
    // f - the lowest speed it can go (y intercept)

    a_FeedBot.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
    a_FeedTop.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);

    a_FeedBot.Config_kP(0, 0.12, 0);
    a_FeedBot.Config_kI(0, 0, 0);
    a_FeedBot.Config_kD(0, 0, 0);
    a_FeedBot.Config_kF(0, 0.91, 0); // 1.3

    a_FeedTop.Config_kP(0, 0.12, 0);
    a_FeedTop.Config_kI(0, 0, 0);
    a_FeedTop.Config_kD(0, 0, 0); 
    a_FeedTop.Config_kF(0, 0.94, 0); // 1.5

    
}

 void CFS::Shoot() {
        a_ShootLeft.Set(ControlMode::PercentOutput, -SHOOT_VOLTS);
        a_ShootRight.Set(ControlMode::PercentOutput, SHOOT_VOLTS);
    }

 void CFS::Shoot(float speed) {
        a_ShootLeft.Set(ControlMode::PercentOutput, -speed);
        a_ShootRight.Set(ControlMode::PercentOutput, speed);
 }

 void CFS::Collect() {
     a_Collector.Set(ControlMode::PercentOutput, -COLLECT_SPEED);
 }

 void CFS::Collect(float speed) {
     a_Collector.Set(ControlMode::PercentOutput, -speed);
 }

 void CFS::Feed() {
     a_FeedBot.Set(ControlMode::PercentOutput, -FEED_SPEED);
     a_FeedTop.Set(ControlMode::PercentOutput, FEED_SPEED);
 }

 void CFS::Feed(float speed) {
     a_FeedBot.Set(ControlMode::PercentOutput, -speed);
     a_FeedTop.Set(ControlMode::PercentOutput, speed);
 }

void CFS::AutoCollect() {
    if(!a_TopBeam.beamBroken()) // less than 4
    {
        Collect(-0.40);
        if(a_BrokenBeam.beamBroken()) {
            // Feed(-0.55);
            FeedVelocity(1200);
        } else {
            Feed(0);
        }
    }
    else // 4+
    {
        Feed(0);
        if(a_BrokenBeam.beamBroken())
        {
            // Feed(-0.70);
            Collect(0);
        }
        else
        {
            // Feed(0);
            Collect(-0.40);
        }
    }
}

 void CFS::ArmMove(float speed) {
         a_Pivot.Set(speed);
 }


 void CFS::ShootVelocity(float speed) {
     a_ShootLeft.Set(ControlMode::Velocity, speed);
     a_ShootRight.Set(ControlMode::Velocity, -speed); 
 }

 void CFS::FeedVelocity(float speed)
 {
    a_FeedBot.Set(ControlMode::Velocity, speed);
    a_FeedTop.Set(ControlMode::Velocity, -speed);
 }

 float CFS::GetWheelSpeedR() {
     return a_ShootRight.GetSelectedSensorVelocity(); 
 }

 float CFS::GetWheelSpeedL() {
     return a_ShootLeft.GetSelectedSensorVelocity();
 }

 bool CFS::GetBottomBeam() {
     return a_BrokenBeam.beamBroken(); 
 }

bool CFS::GetTopBeam() {
    return a_TopBeam.beamBroken();
}

float CFS::GetPivotPosition()
{
    float ret = pivotInput.GetVoltage();
    return ret;
}

float CFS::GetArmAngle()
{
    float volts = GetPivotPosition();

    float angle = (((volts - VOLTS_MIN) * (ANGLE_MAX - ANGLE_MIN)) / (VOLTS_MAX - VOLTS_MIN)) + ANGLE_MIN;
    return angle;
}

float CFS::GetFeedSpeedTop(void)
{
    return a_FeedTop.GetSelectedSensorVelocity(0);
}

float CFS::GetFeedSpeedBot(void)
{
    return a_FeedBot.GetSelectedSensorVelocity(0);
}

void CFS::setArmAngle(float angle)
{
    float temp = std::clamp(-1 * armAnglePID.Calculate(GetArmAngle(), angle), -0.3, 0.3);
    a_Pivot.Set(temp);
}

void CFS::ClimbQuestionMark(float speed)
{

    a_Climber.Set(-1 * speed);

}