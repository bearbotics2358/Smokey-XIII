#include "UnderGlow.h"

    UnderGlow::UnderGlow(int port):
    a_LED(UNDER_GLOW),
    a_RGB(0, 0, 0)
    {

    }

    void UnderGlow::AutoGlow() {
        
    }

    void UnderGlow::PowerOn() {
        a_LED.Start(); 
    }

    void UnderGlow::PowerOff() {
        a_LED.Stop();
    }

    void UnderGlow::SetHyperDrive() {
        if(count <= 150) {
            a_RGB.SetRGB(0, 0, 255); // sets leds to blue 
            count++;  
        } else if (count > 150) {
            if(count == 300) {
                count = 0;
            }
            a_RGB.SetRGB(255, 255, 255); // sets leds to white
            count++; 
        }
        
    }