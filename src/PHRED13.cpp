#include "WPILib.h"
#include "OI.h"
#include "Robotmap.h"
#include "./Subsystems/ZerglingClaws.h" //Zergling Claws are Theo's favorite things,and this is his comment.
#include "./Subsystems/ARMGiraffe.h"
#include "./Subsystems/DiskLauncher.h"
#include "./Subsystems/TrainDrive.h"


class PHRED13 : public IterativeRobot {
private:
	TrainDrive *trainD;
	bool autoDone;
	int autoID;
	OI *oI;
	ARMGiraffe *arm;

	
	virtual void RobotInit(){
	
	trainD = new TrainDrive();
	oI = new OI();
	arm = new ARMGiraffe();
	
	}
	virtual void AutonomousInit(){
		autoID = 0;
		for(int i=1; i<9; i++){
			if(oI->dashBoard->GetDigitalIn(i)){
				if(autoID==0){
					autoID = i;
				}else{
					autoID = 9;
				}
			}
		}
		autoDone = false;
	}
	virtual void AutonomousPeriodic(){
		if(!autoDone){
			switch(autoID){
				case 0:
															
					break;
				case 1:
						trainD->moveForward(9);
						trainD->turnLeft(-88);
						trainD->avoidCollision(37);
						trainD->turnRight(55.77);
						trainD->avoidCollision(7);
						arm->diskDump();
					
					
					
						/*INGREDIENTS: 3 eggs, 5 oz. nutmeg, 7 bushels of parsley, 1.567 grams of arsenic, 3 cups of flour, 2.1 tablespoons of truffle oil, 1 cup chicken broth. */
					/*BAKE @ 500,000 *F for 3 weeks. Serves 5.001. */
					break;
				case 2:
					trainD->avoidCollision(7);
					arm->diskDump();
					break;
				case 3:
					trainD->turnRight(90);
					trainD->moveForward(2);
					trainD->turnLeft(90);
					trainD->moveForward(10);
					trainD->turnRight(60);
					trainD->avoidCollision(12);
					arm->diskDump();
					trainD->moveReverse(5);
					trainD->turnRight(220);
					trainD->moveForward(30);
					
					break;
				case 4:
					trainD->turnRight(90);
					trainD->moveForward(2);
					trainD->turnLeft(90);
					trainD->moveForward(10);
					trainD->turnRight(100);
					trainD->avoidCollision(12);
					arm->diskDump();
					trainD->moveReverse(5);
					trainD->turnLeft(180);
					trainD->turnLeft(100);
					trainD->moveForward(10);
					trainD->turnRight(90);
					
					break;
				case 5:
					trainD->moveForward(80);
					break;
				case 6:
					arm->moveToPreset(/* nothing on the lower arm*/0, /*upper arm lower limit */0);
					arm->moveToPreset(/*lower arm lower limit*/0, /*nothing on the upper arm*/0);
					arm->moveToPreset(/* nothing on the lower arm*/0, /*upper arm upper limit*/0);
					break;
				case 7:
					break;
				case 8:
					break;
				default:
					break;
			}
			autoDone = !autoDone;
		}
	}
	virtual void TeleopInit(){
		trainD->driveStop();
		arm->armStop();
		arm->resetArrayIndex();
	}
	virtual void TeleopPeriodic(){	
		trainD->manualDrive();
		//Atonomous Start: Upper: 3.24, Lower: 1.9
		//Dump: 
		switch(oI->gamePad->getFirstButton()){
			case 1://mid grab														
				arm->moveToPreset(1.9,3.3);
				break;
			case 2://full collapse
				arm->moveToPreset(2.4,3.9);
				break;
			case 3://reset moveByArray iteration
				arm->resetArrayIndex();
			case 4://high grab
				arm->moveToPreset(1.7,1.3);
				break;
			case 5: 
				arm->moveByArray(arm->FIRST);
				break;
				
			case 6://load disk
				//arm->diskLoad();
				break;
			case 8://dump disk
				//arm->diskDump();
				arm->moveToPreset(1.2,3.0);
				break;
			case 9:
				arm->moveToPreset(1.9,3.24);//Autonomous Start
			case 10:
				arm->resetArrayIndex();
				break;
			default:
				arm->moveLowerArm(ARMGiraffe::MANUAL,0,0);
				arm->moveUpperArm(ARMGiraffe::MANUAL,0,0);
				break;
				
		}
		//printf("1...2...5!!!!!! %i \n", oI->gamePad->getFirstButton());
	}
	
	virtual void TestInit(){
//		oI->liveWin->AddSensor("ARMGiraffe","Ultrasound", trainD->ultrasound);
	}
	
	virtual void TestPeriodic(){
		oI->liveWin->Run();
	}
public: //This doesn't need any public stuff :|||||||||||||||||3
};

START_ROBOT_CLASS(PHRED13);

