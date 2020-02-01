
#include "CFS.h"



CFS::CFS(int shoot1, int shoot2, int feed1, int feed2, int collect, int pivot):
    a_ShootLeft(shoot1),
    a_ShootRight(shoot2),
    a_FeedTop(feed1),
    a_FeedBot(feed2),
    a_Collector(collect),
    a_Pivot(pivot, rev::CANSparkMaxLowLevel::MotorType::kBrushless)
{

    a_ShootLeft.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);
    a_ShootRight.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);

}

 void CFS::Shoot() {
        a_ShootLeft.Set(ControlMode::PercentOutput, SHOOT_SPEED);
        a_ShootRight.Set(ControlMode::PercentOutput, SHOOT_SPEED);
    }

 void CFS::Shoot(float speed) {
        a_ShootLeft.Set(ControlMode::PercentOutput, speed);
        a_ShootRight.Set(ControlMode::PercentOutput, speed);
 }

 void CFS::Collect() {
     a_Collector.Set(ControlMode::PercentOutput, COLLECT_SPEED);
 }

 void CFS::Collect(float speed) {
     a_Collector.Set(ControlMode::PercentOutput, speed);
 }

 void CFS::Feed() {
     a_FeedBot.Set(ControlMode::PercentOutput, FEED_SPEED);
     a_FeedTop.Set(ControlMode::PercentOutput, FEED_SPEED);
 }

 void CFS::Feed(float speed) {
     a_FeedBot.Set(ControlMode::PercentOutput, speed);
     a_FeedTop.Set(ControlMode::PercentOutput, speed);
 }

 void CFS::ArmMove(float speed) {
         a_Pivot.Set(speed);
 }

 void CFS::ShootVelocity(float speed) {
     a_ShootLeft.Set(ControlMode::Velocity, speed);
     a_ShootRight.Set(ControlMode::Velocity, speed); 
 }

 float CFS::GetWheelSpeedR() {
     return a_ShootRight.GetSelectedSensorVelocity(); 
 }

 float CFS::GetWheelSpeedL() {
     return a_ShootLeft.GetSelectedSensorVelocity();
 }