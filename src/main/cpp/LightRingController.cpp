#include <LightRingController.h>
#include <Prefs.h>

LightRingController::LightRingController():
a_I2C(frc::I2C::kOnboard, LIGHT_RING_CONTROLLER_ADDRESS) //Remember to change when we a specified device address
{


}


// Our current LRC's support light rings on pins 0, 1, and 2- don't try to set the color of other ones, please
bool LightRingController::SetColor(int device, int r, int g, int b) {
	uint8_t out[4];
	out[0] = device;
	out[1] = r;
	out[2] = g;
	out[3] = b;
	// return a_I2C.Transaction(out, 3, NULL, 0);
	return a_I2C.WriteBulk(out, 4);
}

void LightRingController::SetAllColor(int r, int g, int b){
	SetColor(0, r, g, b);
	SetColor(1, r, g, b);
	SetColor(2, r, g, b);
}

bool LightRingController::SetFlash(int device, bool set) {
	if(set)
	{
		return SetColor(device,255,255,255);
	}
	else
	{
		return SetColor(device,0,0,0);
	}
}