#include "DualAction.h"

DualAction::DualAction(int port){
	gamepad = new Joystick(port);
}
//float DualAction::getLeftX(){
//	return gamepad->GetRawAxis(1);
//}
//float DualAction::getLeftY(){
//	return gamepad->GetRawAxis(2);
//}
//float DualAction::getRightX(){
//	return gamepad->GetRawAxis(3);
//}
//float DualAction::getRightY(){
//	return gamepad->GetRawAxis(4);
//}
//float DualAction::getDpadX(){
//	return gamepad->GetRawAxis(5);
//}
//float DualAction::getDpadY(){
//	return gamepad->GetRawAxis(6);
//}
float DualAction::getAxis(DualAction::axisName axis){
	return gamepad->GetRawAxis(axis);
}
bool DualAction::getButton(int button){
	return gamepad->GetRawButton(button);
}
int DualAction::getFirstButton(){
	for(int i=1; i<13; i++){
		if(this->getButton(i)){
			return i;
		}
	}
	return 0;
}
