#ifndef LIMITEDPOTENTIOMETER_H
#define LIMITEDPOTENTIOMETER_H
#include "math.h"
#include "WPILib.h"

class LimitedPotentiometer{
private:
	float currentAngle();
	AnalogChannel *channel;
	float upperLimit;
	float lowerLimit;
public:
	LimitedPotentiometer(int, float, float);
	bool isBeyondUpper(void);
	bool isBeyondLower(void);
	void setUpperLimit(float);
	void setLowerLimit(float);
	float getVoltage(void);
	void resetAccumulator(void);
	bool isAtPreset(float);
};


#endif
