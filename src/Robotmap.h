#ifndef ROBOTMAP_H
#define ROBOTMAP_H
//ORCA=WIN

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 **/
 
/** 
 * For example to map the left and right motors, you could define the
 * following variables to use with your drivetrain subsystem.
 * #define LEFTMOTOR 1
 * #define RIGHTMOTOR 2

 * If you are using multiple modules, make sure to define both the port
 * number and the module. For example you with a rangefinder:
 * #define RANGE_FINDER_PORT 1
 * #define RANGE_FINDER_MODULE 1
 **/

//OI
#define LEFT_JS 1
#define RIGHT_JS 2
#define SOLO_JS 4
#define DUALACTION 3

//ARMGiraffe
#define LOWER_VICTOR_RIGHT 4
#define UPPER_VICTOR 3
#define UPPER_ARM_UPPER_LIMIT 5
#define UPPER_ARM_LOWER_LIMIT 6
#define LOWER_ARM_UPPER_LIMIT 3
#define LOWER_ARM_LOWER_LIMIT 4
#define UPPER_POTENTIOMETER 3
#define LOWER_POTENTIOMETER 4

//DiskLauncher

//TrainDrive
#define LEFT_MOTOR 1
#define RIGHT_MOTOR 2
#define LEFT_GEARTOOTH 1
#define RIGHT_GEARTOOTH 2
#define GYRO 1

//ARRRRMpresets
#define PRESET_MID_GRAB 0
#define PRESET_FULL_COLLAPSE 0
#define PRESET_HIGH_GRAB 0
#define PRESET_LOAD_DISK 0
#define PRESET_DUMP_DISK 0

#endif
