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
void collectEggs(short numEggs);
bool atBlackLine();
//bool grabbedEgg();
bool inBase();
bool isStuck(short speed);

const short THIS_MANY_EGGS = 20;
const short BASE_COLOR = getColorName(S3);	// replace S3 with color sensor
const short THRESHOLD = 50; // the value to determine if we're on black

task main() {
	srand(123);
	collectEggs(THIS_MANY_EGGS);
}

void collectEggs(short numEggs) {
	while (numEggs < 20) {
		while (inBase()) {
			forward(80);
		}
		// if at enemy base we need to turn around
		if (atBlackLine() && getMotorEncoder(motorB) > 720) {
			turnAround();
		}
		resetMotorEncoder(motorB);
		resetMotorEncoder(motorC);
		wander();
		pushEggIntoNest();
		numEggs += 1;
	}
}

void pushEggIntoNest() {
	short speed = 0;
	//int rpm = 0;

	while (!inBase()) {
		speed = 50 + random(80);

		while (!isStuck(speed)) {
			forward(speed);
		}
	}

	// release the ball then kick it in (not really necessary but fun)
	rampLower();
	sleep(50);
	rampRaise();
	sleep(50);
	backward(100);
	sleep(10);
	forward(85);

	// get away from the ball and then turn around
	backward(100);
	turnAround();
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}

void wander() {
	short speed = 0;
	int rpm = 0;

	// while we're not at an egg
	while (getUSDistance(distanceCM) > 5) {
		do {
			speed = 25 + random(55);

			forward(speed);

			sleep(750);	// sleep for a short duration to allow motors to
									// reach speed
		} while (!isStuck(speed));
	}

	rampLower();
	sleep(100);
	rampRaise();
	sleep(100);
}

void stopFull() {
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}

void turnAround() {
	resetGyro(S2); // replace S2 with actual gyro number

	repeatUntil(getGyroDegrees(S2) >= 180) {
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
	setMotorSpeed(motorA, -100);
}

void rampRaise() {
	setMotorSpeed(motorA, 100);
}

bool atBlackLine() {
	return (THRESHOLD == getColorReflected(S3));	// replace S3
}

bool inBase() {
	return (BASE_COLOR == getColorName(S3));	// replace S3
}

/*bool grabbedEgg() {
	// need a way to sense if egg is infront of us or not
}*/

bool isStuck(short speed) {
		// check if the motors are stuck
		if (getMotorRPM(motorB) < speed || getMotorRPM(motorC) < speed) {
			// if we're stuck then stop and try to turn
			stopFull();
			resetGyro(S2);	// replace S2 with correct sensor
			// turn 90 degrees
			repeatUntil(getGyroDegrees(S2) > 90) {
				setMotorSpeed(motorB, -50);
				setMotorSpeed(motorC, 50);
			}
		}
}
