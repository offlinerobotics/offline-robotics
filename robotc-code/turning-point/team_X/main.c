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
#pragma config(Motor,  port7,           Lift,          tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port4,           Flipper,       tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port9,           RightDrive,    tmotorVex393_MC29, openLoop, encoderPort, I2C_3)



/* Platform and competition controls
====================== */
#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#include "globals.h"



/* User-defined tasks and global variables
====================== */

	void stopDrive(){
		motor[port9] = 0;
		motor[port2] = 0;
	}

	void moveForward(float time, int speed){
		motor[port9] = speed;
		motor[port2] = speed;
		wait1Msec(time);
		stopDrive();
	}

	void moveBackward(float time, int speed){
		motor[port9] = -speed;
		motor[port2] = -speed;
		wait1Msec(time);
		stopDrive();
	} 
	
			
	
	void pivot(int direction, int maxSpeed, float revolutions) {
		/*int ticks = revolutions * 627.2;
		if (direction == 1)  {  // counterclockwise
			moveMotorTarget(port9, ticks, maxSpeed, true);
			moveMotorTarget(port2, -ticks, maxSpeed, true);
			wait1Msec(100);
		}
		if (direction == 0) {  // clockwise
			moveMotorTarget(port9, -ticks, maxSpeed, true);
			moveMotorTarget(port2, ticks, maxSpeed, true);
			wait1Msec(100);
		}*/
		if (direction == 0) {
			while(SensorValue[I2C_2] < (360 * revolutions)) {
					motor[port2] = maxSpeed;	
			  }		
		 }
		 else if (direction == 1) {
			while(SensorValue[I2C_2] < (360 * revolutions)) {
					motor[port9] = maxSpeed;	
			  }		   
		 }
		
		/*while(SensorValue[I2C_3] < (360 * revolutions)) {
			motor[port9] = maxSpeed;
		}	*/	
		wait1Msec(100);
	}

/* Pre-autonomous mode
====================== */
void pre_auton()
{
	bStopTasksBetweenModes = true;

	/* -------*
	Motor Encoder Reset
	----*
	*/
	resetMotorEncoder(port4);
	resetMotorEncoder(port7);

} // end preautonomous



/* Autonomous mode
====================== */
task autonomous()
{
	/* -------*
	Toggle Autonomous Mode
	----* */
	currentSelection = RED_BACK;
	// currentSelection = RED_BACK;
	// currentSelection = BLUE_FRONT;
	// currentSelection = BLUE_BACK;

	/* -------*
	Event Handle Every Possible Starting Position
	----* */
		switch(currentSelection)
		{
			case RED_FRONT:
			  moveForward(2700, 127);
			  moveBackward(1100,127);
			  pivot(1, 50, 0.5);
			  moveForward(3000, 127);
				break;

			case RED_BACK:
			  moveForward(2700, 127);
			  moveBackward(1100,127);
			  pivot(1, 50, 0.5);
			  moveForward(3000, 127);
				break;

			case BLUE_FRONT:
			  moveForward(2700, 127);
			  moveBackward(1100,127);
			  pivot(0, 50, 0.5);
			  moveForward(3000, 127);
				break;

			case BLUE_BACK:
			  moveForward(2700, 127);
			  moveBackward(1100,127);
			  pivot(0, 50, 0.5);
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

		motor[port2] = A-B; //right
		motor[port9] = A+B; //left

		 /* ---- Lift System ---- */
		if(vexRT[Btn8U] == 1) {
			motor[port3] = 127;
			motor[port7] = -127;
		}
		if(vexRT[Btn8D] == 1) {
				motor[port3] = -127;
		  	motor[port7] = 127;
		}
		if(vexRT[Btn8U] == vexRT[Btn8D]) {
			  motor[port7] = 0;
			  motor[port3] = 0;
		}

		/* ---- Flipping mechanism ---- */
		if(vexRT[Btn6U] == 1)
			{
			motor[port4] = 60;
		}																				//	setMotorTarget(port4, 60, 65, 1);

		else if(vexRT[Btn6D] == 1)
		{
			motor[port4] = -60;
		}
		else motor[port4] = 0;
		/*if((vexRT[Btn5U] == 1) && ) {
			motor[port8] = 75;
		}
		if(vexRT[Btn5D] == 1) {
			motor[port8] = -75;
		}
		if(vexRT[Btn5D] == vexRT[Btn5U]) {
			motor[port8] = 0;
		}*/
	}
} //end user control
