#include "Shooty.h"

Shooty::Shooty(int shootw1, int shootw2, int shootwb):
a_SWheel1(shootw1, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
a_SWheel2(shootw2, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
a_SWheelb(shootwb, rev::CANSparkMaxLowLevel::MotorType::kBrushless)
{ // WIP

}