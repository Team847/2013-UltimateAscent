#include "TrainDrive.h"
#include "math.h"
#include "../Robotmap.h"

TrainDrive::TrainDrive(){
	driveOI = new OI();
	driveRobot = new RobotDrive(1,2);
	gyro = new Gyro(1);
	driveRobot->SetSafetyEnabled(false);
	gyro->Reset();
	ltooth = new GearTooth(1);
	rtooth = new GearTooth(2);
	ltooth->Reset();
	rtooth->Reset();
	ltooth->Start();
	rtooth->Start();
	ultrasound = new AnalogChannel(2);
	}

void TrainDrive::avoidCollision(float distance){//stop the robot before it runs into something; these ought to be what they sound like
	while(100.0*ultrasound->GetVoltage()>distance && driveOI->dashBoard->IsAutonomous()){
		driveRobot->TankDrive(1.0, 1.0);
	}
	driveRobot->TankDrive(0.0, 0.0);
}

void TrainDrive::manualDrive(){
	float lMotorSpeed = setMotorSpeed(driveOI->leftJoystick->GetY(), 1.5) * -1.0;
	float rMotorSpeed = setMotorSpeed(driveOI->rightJoystick->GetY(), 1.5) * -1.0;
	
	driveRobot->TankDrive(lMotorSpeed, rMotorSpeed);
	driveOI->sDash->PutNumber("Ultrasonic", ultrasound->GetVoltage());
	driveOI->sDash->PutNumber("Gyroscope", gyro->GetAngle());
}
void TrainDrive::moveForward (float fdistance){
	ltooth->Reset();
	while ((((float(ltooth->Get()))/16.0)*19.0)<fdistance && driveOI->dashBoard->IsAutonomous()){
		driveRobot->TankDrive(1.0, 1.0);	
		driveOI->sDash->PutNumber("leftytooth", ltooth->Get());
		driveOI->sDash->PutNumber("rightytooth", rtooth->Get());
	}
	driveRobot->TankDrive(0.0, 0.0);
}
void TrainDrive::moveReverse (float bdistance){
	rtooth->Reset();
	while ((((float(rtooth->Get()))/16.0)*19.0)<bdistance && driveOI->dashBoard->IsAutonomous()){
		driveRobot->TankDrive(-1.0, -1.0);	
		//driveOI->sDash->PutNumber("Gear Tooth", rtooth->Get());
	}
		driveRobot->TankDrive(0.0, 0.0);
}
void TrainDrive::checkDistance (void){

	
}  
void TrainDrive::turnLeft (float lpost){
	gyro->Reset();
	while(gyro->GetAngle()>lpost && driveOI->dashBoard->IsAutonomous()){
		driveRobot->TankDrive(-0.60, 0.60);
	}
	driveRobot->TankDrive(0.0, 0.0);
}
void TrainDrive::turnRight (float rpost){
	gyro->Reset();
	while(gyro->GetAngle()<rpost && driveOI->dashBoard->IsAutonomous()){
		driveRobot->TankDrive(0.60, -0.60);
	}
	driveRobot->TankDrive(0.0, 0.0);
}
void TrainDrive::checkGyro (void){
	printf ("angle %f \n", gyro->GetAngle());
	
}
void TrainDrive::driveStop(void){
	gyro->Reset();
	ltooth->Reset();
	rtooth->Reset();
	ultrasound->ResetAccumulator();
	driveRobot->TankDrive(0.0,0.0);
}

float TrainDrive::setMotorSpeed(float speed, float power){
	if(speed < 0.0)
		return ( pow(fabs(speed), power) * -1.0 );
	else
		return ( pow(speed, power) );
}
