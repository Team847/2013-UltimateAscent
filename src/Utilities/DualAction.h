#ifndef DUALACTION_H
#define DUALACTION_H
#include "WPILib.h"

class DualAction {
private:
	Joystick *gamepad;
public:
	DualAction(int);
//	float getLeftX(void);
//	float getLeftY(void);
//	float getRightX(void);
//	float getRightY(void);
//	float getDpadX(void);
//	float getDpadY(void);
	enum axisName{
		leftX=1,
		leftY=2,
		rightX=3,
		rightY=4,
		dPadX=5,
		dPadY=6
	};

	float getAxis(DualAction::axisName);
	bool getButton(int);
	int getFirstButton(void);
};
#endif
