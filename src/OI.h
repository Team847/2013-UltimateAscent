#ifndef OI_H
#define OI_H
#include "WPILib.h"
#include "./Utilities/DualAction.h"
class OI {
private:
// I looked at last year's code and didn't find anything in here
public:
	OI(); //needed for OI.cpp :)
	LiveWindow *liveWin;
	Joystick *leftJoystick;
	Joystick *rightJoystick;
	Joystick *soloJoystick;
	DualAction *gamePad;
	SmartDashboard *sDash;
	DriverStation *dashBoard;
};
#endif
