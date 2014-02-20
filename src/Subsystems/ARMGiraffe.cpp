#include "ARMGiraffe.h"
#include "../Robotmap.h"

//lower, upper
float ARMGiraffe::firstStageArray[] ={
		0.0, 3.58,
		1.95, 0.0,
		0.0, 3.74,
		2.09, 0.0,
		0.0, 4.10,
		2.40, 0.0,
		0.0, 0.0,
		EOA, EOA
};
float ARMGiraffe::secondStageArray[]={
		0.0, 0.0,
		0.0, 0.0,
		EOA, EOA
};
float ARMGiraffe::thirdStageArray[]={
		0.0, 0.0,
		0.0, 0.0,
		EOA, EOA
};
	
ARMGiraffe::ARMGiraffe(){		
	LowerArm = new Victor(4);
	UpperArm = new Victor(3);
	oIarm = new OI();
	upperPoten = new LimitedPotentiometer(3,1.2,4.1/*1*/);	//port,   upper, lower
	lowerPoten = new LimitedPotentiometer(4,0.7,2.4);         //1.0,2.6
	cylLowerLimitTrip = false;
	topLowerLimitTrip = false;
	botLowerLimitTrip = false;
	cylUpperLimitTrip = false;
	topUpperLimitTrip = false;
	botUpperLimitTrip = false;
	aPtr = 0;
}
void ARMGiraffe::moveToPreset(float lowerArmPreset, float upperArmPreset){
	if(lowerArmPreset){
		if(lowerPoten->getVoltage() < lowerArmPreset)
			ARMGiraffe::moveLowerArm(ARMGiraffe::PRESET, lowerArmPreset, 1.0);
		else
			ARMGiraffe::moveLowerArm(ARMGiraffe::PRESET, lowerArmPreset, -1.0);
	}
	if(upperArmPreset){
		if(upperPoten->getVoltage() < upperArmPreset)
			ARMGiraffe::moveUpperArm(ARMGiraffe::PRESET, upperArmPreset, 1.0);
		else
			ARMGiraffe::moveUpperArm(ARMGiraffe::PRESET, upperArmPreset, -1.0);
	}
}
void ARMGiraffe::moveByArray(ARMGiraffe::Array array){
	if(aPtr == 0){
		switch(array){
			case 1: aPtr = firstStageArray; break;
			case 2: aPtr = secondStageArray; break;
			case 3: aPtr = thirdStageArray; break;
			default: break;
		}
	}
	if(*aPtr != EOA){
		printf("\n%f   %f", *aPtr, *(aPtr+1));
		if(!lowerPoten->isAtPreset(*aPtr) || !upperPoten->isAtPreset(*(aPtr+1))){
			ARMGiraffe::moveToPreset(*aPtr, *(aPtr+1));
		}else{
			aPtr+=2;
		}
	}
}
void ARMGiraffe::resetArrayIndex(void){
	aPtr=0;
}
void ARMGiraffe::diskDump(void){
	while(!(lowerPoten->isAtPreset(1.2) && lowerPoten->isAtPreset(3.0))){
		ARMGiraffe::moveToPreset(1.2,3.0);
	}
	ARMGiraffe::armStop();
}
void ARMGiraffe::moveLowerArm(ARMGiraffe::mode mode, float preset, float motorSpeed){
	cylLowerLimitTrip = false;
	topLowerLimitTrip = false;
	botLowerLimitTrip = false;

	if(mode == MANUAL)											//MANUAL mode: use joystick values as motorspeed
		joyvalue1 = oIarm->gamePad->getAxis(DualAction::rightY);//Values are negative if pushing up, positive if pushing down (Range: -1.0 to 1.0)
	else														//AUTONOMOUS/PRESET mode: use passed motorspeed
		joyvalue1 = motorSpeed;
	
	if(fabs(joyvalue1) < 0.1)
		joyvalue1 = 0.0;
	else if(lowerPoten->isAtPreset(preset) && mode == PRESET)	//If PRESET mode check for preset point 
		joyvalue1 = 0.0;
	else if(ARMGiraffe::isBeyondCylinder() && joyvalue1 > 0.0){
		joyvalue1 = 0.0;
		cylLowerLimitTrip = true;
	}
	else if(lowerPoten->isBeyondLower() && joyvalue1 > 0.0){
		joyvalue1 = 0.0;
		botLowerLimitTrip = true;
	}
	else if(lowerPoten->isBeyondUpper() && joyvalue1 < 0.0){
		joyvalue1 = 0.0;
		topLowerLimitTrip = true;
	}
	
	LowerArm->Set(joyvalue1 * -1.0);  //gamepad control for lower arm motor, and limit switch

	oIarm->sDash->PutNumber("Lower Potentiometer", lowerPoten->getVoltage());
	oIarm->sDash->PutBoolean("Exceeded Cylendar", cylLowerLimitTrip);
	oIarm->sDash->PutBoolean("Lower Arm, low Limit trip", botLowerLimitTrip);
	oIarm->sDash->PutBoolean("Lower Arm, upper Limit Trip", topLowerLimitTrip);
}

void ARMGiraffe::moveUpperArm(ARMGiraffe::mode mode, float preset, float motorSpeed){
	cylUpperLimitTrip = false;
	topUpperLimitTrip = false;
	botUpperLimitTrip = false;

	if(mode == MANUAL)
		joyvalue2=oIarm->gamePad->getAxis(DualAction::leftY);	//Values are negative if pushing up, positive if pushing down (Range: -1.0 to 1.0)
	else
		joyvalue2 = motorSpeed;

	if (fabs(joyvalue2) < 0.1)
		joyvalue2 = 0.0;
	else if(upperPoten->isAtPreset(preset) && mode == PRESET)	//If PRESET mode check for preset point
		joyvalue2 = 0.0;
	else if(ARMGiraffe::isBeyondCylinder() && joyvalue2 < 0.0){
		joyvalue2 = 0.0;
		cylUpperLimitTrip = true;
	}
	else if(upperPoten->isBeyondLower() && joyvalue2 > 0.0){
		joyvalue2 = 0.0;
		botUpperLimitTrip = true;
	}
	else if(upperPoten->isBeyondUpper() && joyvalue2 < 0.0){
		joyvalue2 = 0.0;
		topUpperLimitTrip = true;
	}

	UpperArm->Set(joyvalue2 * -1.0);  //gamepad control for upper motors and limit switches
	
	oIarm->sDash->PutNumber("Upper Ponentiometer", upperPoten->getVoltage());
	oIarm->sDash->PutBoolean("Exceeded Cylendar, Upper Arm", cylUpperLimitTrip);
	oIarm->sDash->PutBoolean("Upper Arm, low Limit trip", botUpperLimitTrip);
	oIarm->sDash->PutBoolean("Upper Arm, upper Limit Trip", topUpperLimitTrip);
}

void ARMGiraffe::armStop() {
	LowerArm->Set(0.0);
	UpperArm->Set(0.0);
	
}

bool ARMGiraffe::isBeyondCylinder() {
	// 17 inches is the distance from the pivot point to the front of the robot
	// along a circle taken from the corners
//	printf("X: %f\tAng1: %f\tAng2: %f\n", tipPositionX() + 17, lowerPotenAngle(), upperPotenAngle());
	return tipPositionX() + 17 > 54;
}

float ARMGiraffe::tipPositionX() {
	return   lowerArmLength * cos(lowerPotenAngle())
		   + upperArmLength * cos(lowerPotenAngle() + upperPotenAngle());
}

float ARMGiraffe::lowerPotenAngle() {
	return Util::lerp(lowerPotenVoltage1, lowerPotenVoltage2,
			lowerPotenAngle1, lowerPotenAngle2, lowerPoten->getVoltage());
}

float ARMGiraffe::upperPotenAngle() {
	return Util::lerp(upperPotenVoltage1, upperPotenVoltage2,
			upperPotenAngle1, upperPotenAngle2, upperPoten->getVoltage());
}
void ARMGiraffe::lowBarSet(void){
	
}
void ARMGiraffe::highBarSet(void){
	
}
void ARMGiraffe::diskLoad(void){
	
}
