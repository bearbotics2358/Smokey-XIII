
#pragma once

#include <ctre/Phoenix.h>
#include <rev/CANSparkMax.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>
#include <Prefs.h>
#include "BeamBreak.h"
#include <frc/smartdashboard/SmartDashboard.h>

class CFS 
{
    public:
        CFS(int shoot1, int shoot2, int feed1, int feed2, int collect, int pivot, int beam1, int beam2); 

        void Shoot();
        void Shoot(float speed);

        void Collect();
        void Collect(float speed);

        void Feed();
        void Feed(float speed);

        void AutoCollect(); 

        void ArmMove(float speed);

        void ShootVelocity(float speed);

        float GetWheelSpeedR(); // return floats of velocity for right and left
        float GetWheelSpeedL(); 
        bool GetBottomBeam();
        bool GetTopBeam();

         
        float VoltToAngle();
        
       

        /* 
           bool ball6;
           bool ball7;
           bool ball8; 
           (rainy day booleans)
        */

        float GetPivotPosition(void);

    private:
    
    WPI_TalonSRX a_ShootLeft;
    WPI_TalonSRX a_ShootRight;
    WPI_TalonSRX a_FeedTop;
    WPI_TalonSRX a_FeedBot;
    WPI_TalonSRX a_Collector;

    BeamBreak a_BrokenBeam;
    BeamBreak a_TopBeam;

    rev::CANSparkMax a_Pivot; // arm motor 

    frc::AnalogInput pivotInput; // pivot encoder
    frc::AnalogEncoder a_PivotEncoder;

    



        
};