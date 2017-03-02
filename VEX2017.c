#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    angle,          sensorAnalog)
#pragma config(Sensor, dgtl1,  limitRight,     sensorTouch)
#pragma config(Sensor, dgtl2,  limitLeft,      sensorTouch)
#pragma config(Sensor, dgtl3,  right_sweeper_encoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  left_sweeper_encoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, led1,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, led2,           sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  latch_encoder,  sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  strafe_encoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  left_drive_encoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  left_lift_encoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  right_lift_encoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_6,  compass,        sensorSpare2OnI2CPort,         , 0x1E )
#pragma config(Motor,  port1,           right_sweeper, tmotorVex393_HBridge, PIDControl, reversed, encoderPort, dgtl3)
#pragma config(Motor,  port2,           latch2,        tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           left_sweeper,  tmotorVex393_MC29, PIDControl, encoderPort, dgtl6)
#pragma config(Motor,  port4,           right_drive_1, tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port5,           right_drive_2, tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port6,           left_drive_1,  tmotorVex393_MC29, PIDControl, driveLeft, encoderPort, I2C_3)
#pragma config(Motor,  port7,           left_drive_2,  tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port8,           right_launch,  tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_5)
#pragma config(Motor,  port9,           left_launch,   tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port10,          strafe,        tmotorVex393_HBridge, PIDControl, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

int p,i,d;
bool finishedHoming = true, sweeping = false;
const int SWEEPER_POWER = 25;
float angle_measurement;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  p = 80;
  i = 10;
  d = 0;

  mtrPid_kP[latch2] = 50;
	mtrPid_kI[latch2] = i;
	mtrPid_kD[latch2] = 10;
	mtrPid_kP[right_drive_1] = p;
	mtrPid_kI[right_drive_1] = i;
	mtrPid_kD[right_drive_1] = d;
	mtrPid_kP[left_drive_1] = p;
	mtrPid_kI[left_drive_1] = i;
	mtrPid_kD[left_drive_1] = d;
	mtrPid_kP[right_launch] = p;
	mtrPid_kI[right_launch] = i;
	mtrPid_kD[right_launch] = d;
	mtrPid_kP[left_launch] = p;
	mtrPid_kI[left_launch] = i;
	mtrPid_kD[left_launch] = d;
	mtrPid_kP[strafe] = p;
	mtrPid_kI[strafe] = i;
	mtrPid_kD[strafe] = d;

	slaveMotor(right_drive_2,right_drive_1);
	slaveMotor(left_drive_2,left_drive_1);

	resetMotorEncoder(left_launch);
	resetMotorEncoder(right_launch);
	resetMotorEncoder(latch2);
	wait1Msec(2000);

	/*char msg[]={0x01,0x1E,0x02};
	sendI2CMsg(msg,0);
	msg[2]=0x00;
	sendI2CMsg(msg,0);*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	int x=0,y=0,L=0,R=0,maxi=0,sum=0,dif=0;
  // User control code here, inside the loop

  while (true)
  {
  	x = vexRT[Ch1];
  	y = vexRT[Ch3];

  	if(x < 10 && x > -10) {
  		x = 0;
  	}
  	if(y < 10 && y > -10) {
  		y = 0;
  	}

  	maxi = abs(y);

    if (abs(x) > maxi)
    {
        maxi = abs(x);
    }

    sum = y + x;
    dif = y - x;

    if(y >= 0)
    {
        if (x >= 0)
        {
            L = maxi;
            R = dif;
        }
        else
        {
            L = sum;
            R = maxi;
        }
    }
    else
    {
        if ( x >= 0)
        {
            L = sum;
            R = -maxi;
        }
        else
        {
            L = -maxi;
            R = dif;
        }
    }

  	motor[left_drive_1] = -L;
    motor[right_drive_1] = R;

    if(vexRT[Ch4] > 10 || vexRT[Ch4] < -10) {
   		motor[strafe] = -vexRT[Ch4];
   	}

  	if (finishedHoming) {
  		setMotorTarget(left_launch,-getMotorEncoder(right_launch),127,true);
  	}

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    // Remove this function call once you have "real" code.
    if(vexRT[Btn8DXmtr2]) {
    	int power = 115;
			int dist = 4400;
    	setMotorTarget(right_launch, -dist, power, true);
			//setMotorTarget(L1, dist, power, true);
    }

    if(vexRT[Btn8UXmtr2]) {
    	int power = 115;
			int dist = 200;
    	setMotorTarget(right_launch, -dist, power, true);
			//setMotorTarget(L1, dist, power, true);
    }

    if(vexRT[Btn8LXmtr2] || !finishedHoming) {
    	if(SensorValue(limitLeft) == 0) {
    		motor[left_launch] = -50;
    	}
    	else {
    		motor[left_launch] = 0;
    	}
    	if(SensorValue(limitRight) == 0) {
    		motor[right_launch] = 50;
    	}
    	else {
    		motor[right_launch] = 0;
    	}
    	if(SensorValue(limitLeft) == 1 && SensorValue(limitRight) == 1) {
    		finishedHoming = true;
    		motor[right_launch] = 0;
    		motor[left_launch] = 0;
    		resetMotorEncoder(left_launch);
    		resetMotorEncoder(right_launch);
    		//setMotorTarget(right_launch,-200,50,true);
    		//setMotorTarget(L1,200,50,true);
    	}
    	else {
    		finishedHoming = false;
    	}
  	}

  	if(vexRT[Btn7LXmtr2]) {
  		//motor[latch2] = -127;
  		setMotorTarget(latch2,0,127,true);
  	}
  	else if(vexRT[Btn7RXmtr2]) {
  		//motor[latch2] = 100;
  		setMotorTarget(latch2,175,127,true);
  	}

  	if(vexRT[Btn7UXmtr2] && !sweeping && !vexRT[Btn5UXmtr2] && !vexRT[Btn5DXmtr2] && !vexRT[Btn6UXmtr2] && !vexRT[Btn6DXmtr2]) {
  		motor[left_sweeper] = SWEEPER_POWER;
  		motor[right_sweeper] = SWEEPER_POWER;
  		sweeping = true;
  	}
  	else if(vexRT[Btn7UXmtr2] && sweeping && !vexRT[Btn5UXmtr2] && !vexRT[Btn5DXmtr2] && !vexRT[Btn6UXmtr2] && !vexRT[Btn6DXmtr2]) {
  		motor[left_sweeper] = 0;
  		motor[right_sweeper] = 0;
  		sweeping = false;
  	}

  	if(vexRT[Btn5UXmtr2] && !vexRT[Btn5DXmtr2]) {//1500 //-150
  		motor[left_sweeper] = SWEEPER_POWER;
  	}
  	else if(vexRT[Btn5DXmtr2] && !vexRT[Btn5UXmtr2]) {
  		motor[left_sweeper] = -SWEEPER_POWER;
  	}
  	else {
  		motor[left_sweeper] = 0;
  	}
  	if(vexRT[Btn6UXmtr2] && !vexRT[Btn6DXmtr2]) {
  		motor[right_sweeper] = SWEEPER_POWER;
  	}
  	else if(vexRT[Btn6DXmtr2] && !vexRT[Btn6UXmtr2]) {
  		motor[right_sweeper] = -SWEEPER_POWER;
  	}
  	else {
  		motor[right_sweeper] = 0;
  	}

  	/*char msg[]={0x01,0x1E,0x03};
  	sendI2CMsg(msg,6);
  	bytes_available = nI2CBytesReady;
  	readI2CReply(reading,6);*/

  	angle_measurement = (SensorValue(angle)*(360/3600.));

  }
}

void turnToAngle(float angle) {

}
