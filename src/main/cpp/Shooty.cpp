#include "Shooty.h"

Shooty::Shooty(int shootw1, int shootw2):
a_SWheel1(shootw1),
a_SWheel2(shootw2)
{ // WIP
    a_SWheel1.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);
	a_SWheel1.ConfigFeedbackNotContinuous(false, 0);

    a_SWheel2.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);
	a_SWheel2.ConfigFeedbackNotContinuous(false, 0);

    speed = 0;
}

void Shooty::BasicShoot(){
   
    a_SWheel1.Set(ControlMode::PercentOutput, speed);
    a_SWheel2.Set(ControlMode::PercentOutput, -speed);

}
double Shooty::GetSpeed(){

    return speed;

}

void Shooty::SetSpeed(double sped){

    speed = sped;

}

void Shooty::SetShootPID1(float P, float I, float D)
{
    a_SWheel1.Config_kP(0, P, 0);
	a_SWheel1.Config_kI(0, I, 0);
	a_SWheel1.Config_kD(0, D, 0);
}

void Shooty::SetShootPID2(float P, float I, float D)
{
    a_SWheel2.Config_kP(0, P, 0);
	a_SWheel2.Config_kI(0, I, 0);
	a_SWheel2.Config_kD(0, D, 0);
}

void Shooty::VelocityShoot(float sped){

    a_SWheel1.Set(ControlMode::Velocity, -sped);
    a_SWheel2.Set(ControlMode::Velocity, sped);

  }

double Shooty::GetVelocity1(){

    return a_SWheel1.GetSelectedSensorVelocity(0);
    

}

double Shooty::GetVelocity2(){

    return a_SWheel2.GetSelectedSensorVelocity(0);

}

double Shooty::GetVoltage1(){

    return a_SWheel1.GetMotorOutputVoltage();

}


double Shooty::GetVoltage2(){

     return a_SWheel12.GetMotorOutputVoltage();

}