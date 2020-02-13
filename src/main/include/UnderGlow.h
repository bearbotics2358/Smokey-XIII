#include "Robot.h"
#include "Prefs.h"
#include <frc/AddressableLED.h>

class UnderGlow 
{
 public: 

    UnderGlow(int port); 
    void AutoGlow();
    void PowerOn(); 
    void PowerOff(); 
    void SetHyperDrive(); 

   

 private:

   frc::AddressableLED a_LED; 
   frc::AddressableLED::LEDData a_RGB; 

   int count = 0; // functions called every 20 milliseconds

    

};