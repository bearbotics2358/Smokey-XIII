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
        count = 0;
        if(count <= 150) {
            a_RGB.SetRGB(34, 0, 255); // sets leds to blue 
            count++;  
        } else if (count > 150) {
            if(count == 300) {
                count = 0;
            }
            a_RGB.SetRGB(225, 225, 225); // sets leds to white
            count++; 
        }
        
    }

    void UnderGlow::SetSith() {
        a_RGB.SetRGB(225, 17, 0);
    }

    void UnderGlow::SetJedi() {
        a_RGB.SetRGB(27, 250, 2);
    }

    void UnderGlow::SetRainbow() {
        count = 0; 
        if(count <= 100) {
            a_RGB.SetRGB(255, 0, 0);
            count++;
            // red
        } else if(count < 200) {
            a_RGB.SetRGB(255, 145, 0);
            count++;
            // orange
        } else if(count < 300) {
            a_RGB.SetRGB(255, 251, 0);
            count++;
            // yellow
        } else if(count < 400) {
            a_RGB.SetRGB(0, 255, 0);
            count++;
            // green
        } else if(count < 500) {
            a_RGB.SetRGB(0, 234, 255);
            count++;
            // cyan
        } else if(count < 600) {
            a_RGB.SetRGB(0, 0, 255);
            count++;
            // blue
        } else if(count < 700) {
            a_RGB.SetRGB(162, 0, 212);
            count++; 
            // purple
        } else if(count < 800) {
            a_RGB.SetRGB(255, 0, 221);
        } else if(count < 900) {
            count = 0; 
        }
    }