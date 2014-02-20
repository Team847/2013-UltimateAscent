#include "OI.h"
#include "Robotmap.h"

OI::OI(){
	// >:( WARUM GABST DU DER CLASSE DUMF NAMEN? Translation: Orcas are the Best
	liveWin = LiveWindow::GetInstance();
	leftJoystick = new Joystick(LEFT_JS);
	rightJoystick = new Joystick(RIGHT_JS);
	soloJoystick = new Joystick(SOLO_JS);
	gamePad = new DualAction(DUALACTION);
	dashBoard = DriverStation::GetInstance();//Dashboard stuff for autonomous
}
