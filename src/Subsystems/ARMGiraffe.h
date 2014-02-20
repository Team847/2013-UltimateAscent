#ifndef ARMGIRAFFE_H
#define ARMGIRAFFE_H
#include "math.h"
#include "WPILib.h"
#include "../OI.h"
#include "../Utilities/DualAction.h"
#include "../Utilities/LimitedPotentiometer.h"
#include "../Utilities/Util.h"

class ARMGiraffe{
private:
		Victor *LowerArm;
		Victor *UpperArm;
		OI *oIarm;
		LimitedPotentiometer *lowerPoten;
		LimitedPotentiometer *upperPoten;
		float joyvalue1;
		float joyvalue2;
		bool cylLowerLimitTrip; //This and the bools below are the values that tell Smartdashboard if we have tripped a limit switch
		bool topLowerLimitTrip; //Limit switch on the top of the lower arm
		bool botLowerLimitTrip; //Limit on the bottom of the lower arm
		bool cylUpperLimitTrip; //Checks if were are outside cylendar area
		bool topUpperLimitTrip;	//Limit on the top of the Upper arm
		bool botUpperLimitTrip;	//Limit of the bottom of the Lower arm
		bool isBeyondCylinder(void);
		float tipPositionX(void);
		
		// Both of these functions work in radians
		float lowerPotenAngle(void);
		float upperPotenAngle(void);
		
		// Lower and upper arm lengths in inches
		static const float lowerArmLength = 24.0f;
		static const float upperArmLength = 24.0f;
		
		// Potentiometer calibration
		// Two data points are taken on each pot, and then lerped to convert to angles
		// Angles are in radians
		static const float lowerPotenVoltage1 = 2.67f;
		static const float lowerPotenAngle1 = 0.0f;
		static const float lowerPotenVoltage2 = 0.79f;
		static const float lowerPotenAngle2 = 1.57f;
		static const float upperPotenVoltage1 = 2.81f;
		static const float upperPotenAngle1 = 1.57f;
		static const float upperPotenVoltage2 = 1.80f;
		static const float upperPotenAngle2  = 0.79f;
		
		static float firstStageArray[];
		static float secondStageArray[];
		static float thirdStageArray[];
		
		static const float EOA = 10.0;
		float *aPtr;
		
public:
		enum mode{MANUAL = 1, PRESET = 2, AUTONOMOUS = 3};
		enum Array{FIRST = 1, SECOND = 2, THIRD = 3};
		void moveToPreset(float, float);
	ARMGiraffe();
	void moveLowerArm(ARMGiraffe::mode, float, float);//Tele-op mode
	void moveUpperArm(ARMGiraffe::mode, float, float);
	void collapseArm(void);//Autonomous mode from here down
	void lowBarSet(void);
	void highBarSet(void);
	void diskLoad(void);
	void diskDump(void);
	void armStop(void);
	void moveByArray(ARMGiraffe::Array);
	void resetArrayIndex(void);
};
#endif
