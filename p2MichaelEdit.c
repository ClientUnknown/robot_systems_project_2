

void wander();
bool isStuck(short speed);
void stopFull();
void forward(short speed);
void rampLower();
void rampRaise();
/*
void collectEggs(short numEggs);
void pushEggIntoNest();
void backward(short speed);
void turnAround();

bool atBlackLine();
//bool grabbedEgg();
bool inBase();
*/
const short THIS_MANY_EGGS = 20;
//const short BASE_COLOR = getColorName(S3);	// replace S3 with color sensor
const short THRESHOLD = 50; // the value to determine if we're on black

task main() {
	srand(123);
	wander();
}

void rampLower() {
	setMotorSpeed(motorA, -100);
}

void rampRaise() {
	setMotorSpeed(motorA, 100);
}

void forward(short speed) {
	setMotorSpeed(motorB, speed);
	setMotorSpeed(motorC, speed);
}

void turnLeft(short speed){
	setMotorSpeed(motorB, speed);
}

void turnRight(short speed){
	setMotorspeed(motorC, speed);
}

void wander() {
	short speed = 0;
	// int rpm = 0;
	// while we're not at an egg
	while(true){ //while not detecting egg or home...
			do {
				speed = 25 + random(35);

				forward(speed);
				//add logic for touching walls
				speed = 25 + random(35);
				turnLeft(speed);
				speed = 25 + random(35);
				turnRight(speed);

				sleep(200);	// sleep for a short duration to allow motors to
										// reach speed

				//add in logic for when egg is detected to break out of this do-while

			} while (!isStuck(speed));
		rampLower();
		sleep(100);
		rampRaise();
		sleep(100);
	}
}
/*
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
//possibly not needed function
void turnAround() {
	resetGyro(S3); // replace S3 with actual gyro number

	repeatUntil(getGyroDegrees(S3) >= 180) {
		setMotorSpeed(motorC, -20);
		setMotorSpeed(motorB, 75);
	}

	stopFull();
}

//possible not needed function
void backward(short speed) {
	setMotorSpeed(motorB, speed);
	setMotorSpeed(motorC, speed);
}


bool atBlackLine() {
	return (THRESHOLD == getColorReflected(S1));	// replace S1
}

bool inBase() {
	return (BASE_COLOR == getColorName(S1));	// replace S1
}


//bool grabbedEgg() {
	// need a way to sense if egg is infront of us or not
//}*/

void stopFull() {
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
}

bool isStuck(short speed) {
		// check if the motors are stuck
/*
		if (getMotorRPM(motorB) < speed || getMotorRPM(motorC) < speed) {
			// if we're stuck then stop and try to turn
			stopFull();
			resetGyro(S2);	// replace S2 with correct sensor
			// turn 90 degrees
			repeatUntil(getGyroDegrees(S2) > 90) {
				setMotorSpeed(motorB, -50);
				setMotorSpeed(motorC, 50);
			}
			return true;
		}
		return false;
		*/

		sleep(500);
		if(getTouchValue(S2) == 1 && getTouchValue(S4) == 1){
 			setMotorSpeed(motorB, -50);
			setMotorSpeed(motorC, -50);
			sleep(2000);
			stopFull();

			setMotorSpeed(motorB, speed+50);
			setMotorSpeed(motorC, speed);
			sleep(1000);
			return true;
	}
	return false;
}
