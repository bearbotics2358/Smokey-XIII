
#include "Prefs.h"
#include <frc/DigitalInput.h>

class BeamBreak
{
public:

    BeamBreak(int port);
    bool beamBroken();
    bool isBroken = false; 

private:    

    frc::DigitalInput a_Input; 

};