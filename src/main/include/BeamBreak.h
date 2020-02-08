
#include "Prefs.h"
#include <frc/DigitalInput.h>

class BeamBreak
{
public:

    BeamBreak(int port);
    bool beamBroken();

private:    

    frc::DigitalInput a_Input; 

};