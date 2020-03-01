
#include "JrimmyGyro.h"

const uint8_t JrimmyGyro::kPowerMgmRegister;
// const uint8_t JrimmyGyro::kDataFormatRegister;
// const uint8_t JrimmyGyro::kDataRegister;
// constexpr double JrimmyGyro::kGsPerLSB;

/**
 * Constructor.
 *
 * @param port The I2C port the gyro is attached to
 */
JrimmyGyro::JrimmyGyro(Port port):
		I2C(port, 0x68)
{
	// uint8_t Buff[256];
	lastUpdate = 0;
	Init();
	// printf("Reg 0 is: %d", GetReg0());
	// m_i2c = new I2C((I2C::Port)port, kAddress);
	// int ret = Read(0, 1, Buff);
	// printf("Jake Buff: %2.2X\n", Buff[0] & 0x00ff);

	// Specify the data format to read
	// SetRange(range);

	// HALReport(HALUsageReporting::kResourceType_ADXL345, HALUsageReporting::kJrimmyGyro, 0);
}

JrimmyGyro::~JrimmyGyro()
{
	// delete m_i2c;
	// m_i2c = NULL;
}

void JrimmyGyro::WaitForValues()
{
	uint8_t stat;
	bool result;
	double start = frc::Timer::GetFPGATimestamp();
	double now;

	do {
		result = Read(kIntStatus, 1, &stat);
		now = frc::Timer::GetFPGATimestamp();
	} while( (((stat&5) != 5) || (result == 0)) && ((now-start) < 0.100));
	// TODO: report errors/timeouts
}

void JrimmyGyro::Init()
{
	lastUpdate = 0;
	Write(kDLPFRegister, 0x1B);
	Write(kSampleRateDivider, 9);
	Write(kPowerMgmRegister, 1); // set to more accurate clock
	Write(kIntCfg, 5);

	Cal();
}

void JrimmyGyro::Cal()
{
	// get gyro drift biases
	int i;
	double tstart = frc::Timer::GetFPGATimestamp();
	while(frc::Timer::GetFPGATimestamp() < tstart + 0.100) {
		// wait 100 ms for readings 
	}
	
	for(i = 0; i < 3; i++) {
		angleBias[i] = 0;
	}

	// throw out first reading, it is 0
	WaitForValues();
	Update();

	for(int i = 0; i < 10; i++) {
		WaitForValues();
		Update();
		angleBias[0] += XAxis;
		angleBias[1] += YAxis;
		angleBias[2] += ZAxis;

		// printf("XAxis: %6.2lf  ", XAxis);
		// printf("YAxis: %6.2lf  ", YAxis);
		// printf("ZAxis: %6.2lf\n", ZAxis);
	}

	for(i = 0; i < 3; i++) {
		angleBias[i] /= 10;
		angle[i] = 0;
	}
	// printf("Bias read time %6.3lf\n", GetTime() - tstart);
	// printf("AngleBias: %6.3lf %6.3lf %6.3lf\n", angleBias[0], angleBias[1], angleBias[2]);
	// SmartDashboard::PutNumber("Angle Bias X", angleBias[0]);
	// SmartDashboard::PutNumber("Angle Bias Y", angleBias[1]);
	// SmartDashboard::PutNumber("Angle Bias Z", angleBias[2]);
}

uint8_t JrimmyGyro::GetReg0()
{
	uint8_t id;
	Read(0, 1, &id);
	// SmartDashboard::PutNumber("Gyro ID", id);

	return id;
}

int16_t JrimmyGyro::GetReg(uint8_t regNum)
{
	uint16_t ret;
	uint8_t buff[2];

	Read(regNum, 2, buff);
	ret = (buff[0] << 8) | buff[1];
	return (int16_t)ret;
}

void JrimmyGyro::Update()
{
	if(lastUpdate == 0){
		lastUpdate = frc::Timer::GetFPGATimestamp();
		return;
	}
	double time = frc::Timer::GetFPGATimestamp();
	double timeDelta = (time - lastUpdate);

	temperature = GetReg(kTempRegister);
	temperature = -13200 - temp;
	temperature = temperature / 280;
	temperature += 35;

	XAxis = GetReg(kDataRegister + kAxis_X);
	XAxis = XAxis / 14.375;

	YAxis = GetReg(kDataRegister + kAxis_Y);
	YAxis = YAxis / 14.375;

	ZAxis = GetReg(kDataRegister + kAxis_Z);
	ZAxis = ZAxis / 14.375;

	angle[0] += ((XAxis - angleBias[0]) * timeDelta);
	angle[1] += ((YAxis - angleBias[1]) * timeDelta);
	angle[2] += ((ZAxis - angleBias[2]) * timeDelta);
	lastUpdate = time;

	/* for(int i = 0; i < 3; i++) {
		if (angle[i] > 360) {
			angle[i] -= 360;
		}	else if (angle[i] < 0) {
			angle[i] += 360;
		}
	 } */
	// printf("X: %f, Y: %f, Z: %f\n", angle[0], angle[1], angle[2]);
}

double JrimmyGyro::GetX()
{
	return XAxis;
}

double JrimmyGyro::GetY()
{
	return YAxis;
}

double JrimmyGyro::GetZ()
{
	return ZAxis;
}

int JrimmyGyro::GetTemp() {
	return temperature;
}

double JrimmyGyro::GetAngle(int xyz)
{
	return angle[xyz];
}

void JrimmyGyro::Zero() {
	for(int i = 0; i < 3; i++) {
		angle[i] = 0;
	}
}

std::string JrimmyGyro::GetSmartDashboardType() {
	return "3AxisAccelerometer";
}
