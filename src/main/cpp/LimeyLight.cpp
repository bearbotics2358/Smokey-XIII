#include "LimeyLight.h"

 //std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

LimeyLight::LimeyLight ()
: table(nt::NetworkTableInstance::GetDefault()),
lemonLight(0.0, 0.0, 0.0)
{

}

LimeyLight::~LimeyLight ()
{

}

/* 
        tv: are there any valid targets? 
            - returns 0 or 1
        tx: horizontal offset: how much of the target can the robot see? 
            - -27 to 27 degrees
        ty: vertical offset: how much of the target can the robot see? 
            - -20.5 to 20.5
        ta: target area: distance to the target
            - 0% to 100% of image 
        thor: gets width of target 
            - returns a float
*/   

float LimeyLight::getDist () const
{
    // distance in feet
    float temp = GET_LIMELIGHT_VALUE(table, "ts") * (M_PI / 180.0f);
    return ((58.0f / (GET_LIMELIGHT_VALUE(table, "thor"))) / cos(temp)) * 191.0f; //Temporary Constants
}

float LimeyLight::getXAngleShooter (const std::vector<float> velocity, const float gyro) const
{
    float diff = gyro + getAngleX();
    diff = diff < 0 ? 360 + diff : diff;
    return diff;
}

float LimeyLight::getYAngleShooter () const
{
    return 0.0f;
}

float LimeyLight::getVelocityShooter () const
{
    /* velocity = (distance * sqrt(g)) /
    sqrt(2 * height * cos^2(shooter angle) - 2 * distance * sin(shooter angle) cos(shooter angle)) */
    // constants are wrong right now
    float distance = getDist ();
    return ((3.130495168 * distance) / sqrt (TH2_COS2_ANGLE - distance * SIN_2ANGLE));
}

bool LimeyLight::isTarget () const
{
    return GET_LIMELIGHT_VALUE(table, "tv") == 1;
}

float LimeyLight::getAngleX () const
{
    return GET_LIMELIGHT_VALUE(table, "tx");
}

float LimeyLight::getAngleY () const
{
    return GET_LIMELIGHT_VALUE(table, "ty") + SHOOTER_ANGLE;
}

float LimeyLight::getArea () const
{
    return GET_LIMELIGHT_VALUE(table, "ta");
}

float LimeyLight::getAngleTarget () const
{
    return GET_LIMELIGHT_VALUE(table, "ts");
}

float LimeyLight::getWidth () const
{
    return GET_LIMELIGHT_VALUE(table, "thor");
}

/* 
    LED Mode Number Meanings: 
    0: LED is set to current pipeline
    1: Turn LED Off 
    2: LED Blink
    3: Turn LED On
*/ 

void LimeyLight::ledOff () 
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1); 
}

void LimeyLight::ledOn ()
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
}

void LimeyLight::cameraMode(int whichCam) 
{
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", whichCam);
} 

void LimeyLight::printValues () 
{
    // reading values form the lime light
    double angleX = getAngleX(); // offset in degrees (x)
    double angleY = getAngleY(); // offset in degrees (y)
    double targetArea = getArea(); // <- Target area, between 0 and 100 (how much of the target can be seen)
    double targetSkew = getAngleTarget(); // <- Rotation of target 
    double width = getWidth(); // width of the target box **not the actual target

    frc::SmartDashboard::PutNumber("Horizontal Offset: ", angleX); 
    frc::SmartDashboard::PutNumber("Vertical Offset: ",  angleY); 
    frc::SmartDashboard::PutNumber("Target Area: ", targetArea); 
    frc::SmartDashboard::PutNumber("Target Skew: ", targetSkew); 
    frc::SmartDashboard::PutNumber("Target Width: ", width); 

}

void calcZAxis() {
    /* // float rowlet = getAngleX();
    float shinyRowlet = lemonLight.Calculate(0.0, getAngleX());
    return shinyRowlet;
    */
    
}