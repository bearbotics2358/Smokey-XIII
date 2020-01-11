#include "Collecty.h"

Collecty::Collecty(int intake, int mover, int arm):
a_intake(intake, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
a_belts(mover, rev::CANSparkMaxLowLevel::MotorType::kBrushless),
a_arm(arm, rev::CANSparkMaxLowLevel::MotorType::kBrushless)
{ // WIP

}