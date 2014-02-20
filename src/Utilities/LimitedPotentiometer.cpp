#include "LimitedPotentiometer.h"

LimitedPotentiometer::LimitedPotentiometer(int port, float upper, float lower){
	channel = new AnalogChannel(port);
	upperLimit = upper;
	lowerLimit = lower;
}

bool LimitedPotentiometer::isAtPreset(float preset){
	printf("  %f ", LimitedPotentiometer::getVoltage());
	
	if(preset == 0.0){
		return(true);
	}
	else{
		return(LimitedPotentiometer::getVoltage() <= (preset +.02) && //A change of 0.01 volts is ~1/4in change at the end of an arm
				LimitedPotentiometer::getVoltage() >= (preset -.02));
	}
}
bool LimitedPotentiometer::isBeyondUpper(){
	return (channel->GetVoltage()<=upperLimit);
}

bool LimitedPotentiometer::isBeyondLower(){
	return (channel->GetVoltage()>=lowerLimit);
}

void LimitedPotentiometer::setUpperLimit(float f){
	upperLimit = f;
}

void LimitedPotentiometer::setLowerLimit(float f){
	lowerLimit = f;
}

float LimitedPotentiometer::getVoltage(){
	return channel->GetVoltage();
}

void LimitedPotentiometer::resetAccumulator(){
	channel->ResetAccumulator();
}

float LimitedPotentiometer::currentAngle(){
	const float potMaxRange = 5.236;     //Maximum turning radius of a potentiometer in radians ~300 degrees
	const float potMaxVoltage = 5.000;   //Maximum voltage of a potentiometer
	
	return(((fabs(upperLimit - lowerLimit)) * potMaxRange) / potMaxVoltage);
}
