/* Motor configuration
====================== */
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  Intake_Limit,   sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           LeftDrive,     tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port3,           Lift2,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           Flywheel,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           Flywheel_2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Lift,          tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port8,           Flipper,       tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port9,           RightDrive,    tmotorVex393_MC29, openLoop, encoderPort, I2C_3)


/* Platform and competition controls
====================== */
#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#include "globals.h"

/* User-defined tasks and global variables
====================== */
	// string currentSelection;

	void stopDrive(){
		motor[port9] = 0;
		motor[port2] = 0;
	}

	void moveForward(float time, int speed){
		motor[port9] = speed;
		motor[port2] = -speed;
		wait1Msec(time);
		stopDrive();
	}

	void moveBackward(float time, int speed){
		motor[port9] = -speed;
		motor[port2] = speed;
		wait1Msec(time);
		stopDrive();
	}

	/*void rightVeer(float time, int speed, int offset) {
		wait1Msec(time);
		stopDrive();
	}

	void leftVeer(float time, int speed, int offset) {
		wait1Msec(time);
		stopDrive();
	}*/

/* Pre-autonomous mode
====================== */
void pre_auton()
{
	bStopTasksBetweenModes = true;

	/* -------*
	Select Autonomous Procedure Based on Starting Position
	----* */


	while(bIfiRobotDisabled) {
		if(vexRT[Btn5D] == 1) currentSelection = RED_FRONT;
		if(vexRT[Btn5U] == 1) currentSelection = RED_BACK;
		if(vexRT[Btn6D] == 1) currentSelection = BLUE_FRONT;
		if(vexRT[Btn6U] == 1) currentSelection = BLUE_BACK;
	}

} // end preautonomous



/* Autonomous mode
====================== */
task autonomous()
{
	/* -------*
	Event Handle Every Possible Starting Position
	----* */
		switch(currentSelection)
		{
			case RED_FRONT:
			  moveForward(3000, 127);
				break;

			case RED_BACK:
				moveForward(3000, 127);
				break;

			case BLUE_FRONT:
				moveForward(3000, 127);
				break;

			case BLUE_BACK:
				moveForward(3000, 127);
				break;

			default:
				break;
			}

			// AutonomousCodePlaceholderForTesting();

}	// end autonomous



/* User control mode
====================== */

task usercontrol()
{
	/* -------*
	Motor Encoder Reset
	----*
	*/
	resetMotorEncoder(port8);
	resetMotorEncoder(port7);


	/* -------*
	Main Execution Loop
	----*
	*/
	while(true)
	{
		/* ---- Variable initialization ---- */
		int A;
		int B;

		/* ---- Driver control ---- */
		if(abs(vexRT[Ch3]) > 20) {
			A = vexRT[Ch3];
		}
		else {
			A = 0;
		}

		if(abs(vexRT[Ch4]) > 20) {
			B = vexRT[Ch4];
		} else {
			B = 0;
		}


		motor[port9] = A-B; //right
		motor[port2] = A+B; //left

	 /* ---- Lift System ---- */
		if(vexRT[Btn7U] == 1) {
			motor[port3] = 127;
			motor[port7] = -127;
		}
		if(vexRT[Btn7D] == 1) {
				motor[port3] = -127;
		  	motor[port7] = 127;
		}
		if(vexRT[Btn7U] == vexRT[Btn7D]) {
			  motor[port7] = 0;
			  motor[port3] = 0;
		}

		/* ---- Flipping mechanism ---- */
		if(vexRT[Btn5U] == 1) {
			motor[port8] = 127;
		}
		if(vexRT[Btn5D] == 1) {
			motor[port8] = -127;
		}
		if(vexRT[Btn5D] == vexRT[Btn5U]) {
			motor[port8] = 0;
		}
	}
} //end user control
