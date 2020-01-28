
#include "CFS.h"



CFS::CFS(int shoot1, int shoot2, int feed1, int feed2, int collect, int pivot):
    a_ShootLeft(shoot1),
    a_ShootRight(shoot2),
    a_FeedTop(feed1),
    a_FeedBot(feed2),
    a_Collector(collect),
    a_Pivot(pivot)
{

    a_ShootLeft.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);

    a_ShootRight.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 0);



}