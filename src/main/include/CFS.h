
#pragma once

#include <ctre/Phoenix.h>
#include <frc/AnalogEncoder.h>
#include <frc/AnalogInput.h>
#include <frc/controller/PIDController.h>
#include <Prefs.h>

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
       
    private:
    
    WPI_TalonSRX a_ShootLeft;
    WPI_TalonSRX a_ShootRight;
    WPI_TalonSRX a_FeedTop;
    WPI_TalonSRX a_FeedBot;
    WPI_TalonSRX a_Collector;
    WPI_TalonSRX a_Pivot;



        
};