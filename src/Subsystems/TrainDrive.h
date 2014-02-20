#ifndef TRAINDRIVE_H
#define TRAINDRIVE_H
#include "WPILib.h"
#include "../OI.h"

class TrainDrive{
private:
	OI *driveOI;
	RobotDrive *driveRobot;
	Gyro *gyro;
	GearTooth *ltooth;
	GearTooth *rtooth;
	AnalogChannel *ultrasound;
public:
	TrainDrive();
	void manualDrive (void);
	void moveForward (float);
	void moveReverse (float);
	void checkDistance (void);
	void turnLeft (float);
	void turnRight (float);
	void checkGyro (void);
	void avoidCollision (float);
	void driveStop (void);
	float setMotorSpeed(float, float);
};

#endif
