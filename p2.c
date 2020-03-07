#pragma config(Sensor, S1,     ultrasonic,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     gyro,           sensorEV3_Gyro)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "include/mindsensors-ev3smux.h"
#include "include/mindsensors-imu.h"

void stopFull();
void wander();
void forward(short speed);
void rampLower();
void rampRaise();
void pushEggIntoNest();
void backward(short speed);
void turnAround();
void turnRight();
void turnLeft();
void pushEggTowardsNest();
void grabEgg();
bool atBlackLine();
bool inBase();
bool isStuck();

TLegoColors BASE_COLOR;
TLegoColors ENEMY_BASE_COLOR;

task main() {
	srand(123);
	BASE_COLOR = getColorName(S1);	// replace S1 with color sensor **
	if (BASE_COLOR == colorRed) {
		ENEMY_BASE_COLOR = colorBlue;
	} else {
		ENEMY_BASE_COLOR = colorRed;
	}

	// repeat until we have 30 seconds left
	repeatUntil(nClockMinutes >= 1.5) {
		// wander until we find an egg
		while (getUSDistance(ultrasonic) > 5 && !isStuck()) {
			wander();
			// replace S1 with color sensor **
			if (atBlackLine() || getColorName(S1) == ENEMY_BASE_COLOR) {
				turnAround();
				forward(50);
				sleep(500);
			}
		}
		stopFull();
		// push egg to/into nest then turn around from base and leave base
		grabEgg();
		turnAround();
		pushEggTowardsNest();
		pushEggIntoNest();
		turnAround();
		forward(50);
		sleep(500);
		resetMotorEncoder(motorB);
		
	}
	// go back to base, may not be necessary
}
/*
void collectEggs() {
	short numEggs = 0;
	
	while (numEggs < THIS_MANY_EGGS) {
		while (inBase()) {
			forward(80);
		}
		// if at enemy base we need to turn around
		/*if (atBlackLine() && getMotorEncoder(motorB) > 720) {
			turnAround();
		}
		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);
		wander();
		//pushEggIntoNest();
		numEggs += 1;
	}
}
*/


// push egg into nest and face 180 degrees from the base
void pushEggIntoNest() {
	// release the ball then backup to ensure we don't hit it
	rampLower();
	sleep(500);
	rampRaise();
	sleep(500);
	backward(50);
	sleep(700);
}

// move in a random direction at a random speed
void wander () {
	short speed = 0;
	short direction = 0 + random(1); // 0 for left, 1 for right
	
	speed = 25 + random(55);
	
	if (direction == 1) {
		turnRight();
	} else {
		turnLeft();
	}
	
	forward(speed);
	// sleep(500); // might need this sleep
}

/*
void wander() {
	short speed = 0;

	// while we're not at an egg
	while (getUSDistance(ultrasonic) > 5) {
		do {
			speed = 25 + random(55);

			forward(speed);
		} while (!isStuck(speed) && getUSDistance(ultrasonic) > 5);
	}
}
*/

void grabEgg() {
	rampLower();
	sleep(800);
	rampRaise();
	sleep(800);
}

void pushEggTowardsNest() {
	short speed = 0;

	while (!inBase()) {
		do {
			speed = 25 + random(55);
			forward(speed);
			
		} while (!isStuck() && !inBase());
	}
}

void turnRight() {
	resetGyro(gyro);
	
	repeatUntil(getGyroDegrees(gyro) >= 90) {
		setMotorSpeed(motorB, 0);
		setMotorSpeed(motorC, 75);
	}
	stopFull();
}

void turnLeft() {
	resetGyro(gyro);
	
	repeatUntil(getGyroDegrees(gyro) <= -90) {
		setMotorSpeed(motorC, 0);
		setMotorSpeed(motorB, 75);
	}
	stopFull();
}

void stopFull() {
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}

void turnAround() {
	resetGyro(gyro);

	repeatUntil(getGyroDegrees(gyro) >= 180) {
		setMotorSpeed(motorC, -20);
		setMotorSpeed(motorB, 75);
	}

	stopFull();
}

void forward(short speed) {
	setMotorSpeed(motorB, speed);
	setMotorSpeed(motorC, speed);
}

void backward(short speed) {
	setMotorSpeed(motorB, speed);
	setMotorSpeed(motorC, speed);
}

void rampLower() {
	setMotorSpeed(motorA, -75);
}

void rampRaise() {
	setMotorSpeed(motorA, 75);
}

bool atBlackLine() {
	return (colorBlack == getColorName(S1));	// replace S1 with color sensor **
}

bool inBase() {
	return (BASE_COLOR == getColorName(S1));	// replace S1 with color sensor **
}

// able to detect walls or if we're stuck
bool isStuck() {
		// check if the motors are stuck
		if (getTouchValue(S2) == 1 || getTouchValue(S4) == 1) {
			// if we're stuck then stop and turn around, used to detect walls
			stopFull();
			backward(50);
			sleep(500);
			turnAround();
		}
		
		return false;
}
