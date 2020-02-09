
#pragma once

#include <ctre/Phoenix.h>
#include <rev/CANSparkMax.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>
#include <Prefs.h>
#include "BeamBreak.h"

class CFS 
{
    public:
        CFS(int shoot1, int shoot2, int feed1, int feed2, int collect, int pivot); 

        void Shoot();
        void Shoot(float speed);

        void Collect();
        void Collect(float speed);

        void Feed();
        void Feed(float speed);
        void FeedBeamBreak(); 

        void ArmMove(float speed);

        void ShootVelocity(float speed);

        float GetWheelSpeedR(); // return floats of velocity for right and left
        float GetWheelSpeedL(); 

        
       

        /* 
           bool ball6;
           bool ball7;
           bool ball8; 
           (rainy day booleans)
        */

    private:
    
    WPI_TalonSRX a_ShootLeft;
    WPI_TalonSRX a_ShootRight;
    WPI_TalonSRX a_FeedTop;
    WPI_TalonSRX a_FeedBot;
    WPI_TalonSRX a_Collector;

    BeamBreak a_BeamBreak;

    rev::CANSparkMax a_Pivot; // arm motor 

    



        
};