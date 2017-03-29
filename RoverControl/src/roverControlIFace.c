/* roverControl */

#include "../include/rovercontrol.h"
#include <stdio.h>
#include "../src-gen/RoverControl.h"

#define ENGINE 2  /* PWM channel of the engine controller */
#define REAR_STEERING 1  /* PWM channel of the rear steering servo */
#define FRONT_STEERING 0  /* PWM channel of the front steering servo */
#define FRONTSENSOR_MOVEMENT 8  /* PWM channel of the front sensor servo */
#define REARSENSOR_MOVEMENT 3  /* PWM channel of the rear sensor servo */

// The following GPIO pin numbers are for use with WiringPi.
// The numbers in comment are the respective standard GPIO pin numbers.
#define REDLED 21  // 5

#define TRIGRIGHT 4 // 23
#define ECHORIGHT 5 // 24

#define TRIGLEFT 2 // 27
#define ECHOLEFT 3 // 22

#define TRIGMID 26 // 12
#define ECHOMID 27 // 16

#define TRIGREAR 22 // 6
#define ECHOREAR 23 // 13

// engine speed
#define SLOW_FORWARD -15
#define SLOW_BACKWARD 20
#define STOP 0

// servo positions (servos can have angles from -90 to 90 degree)
// the steering servos are reduced from -60 to 60 degrees
#define MIN_STEERING_ANGLE -60
#define MAX_STEERING_ANGLE 60
#define NEUTRAL_ANGLE 0

int speed = STOP;
int heading = NEUTRAL_ANGLE;

int loggingEnabled = 1;

// Helpers
int limitedSteeringAngle(int angle) {
	int limitedAngle = angle;
	if (angle > MAX_STEERING_ANGLE)
		limitedAngle = MAX_STEERING_ANGLE;
	else if (angle < MIN_STEERING_ANGLE)
		limitedAngle = MIN_STEERING_ANGLE;
	return limitedAngle;
}

void logIt(char *logEntry) {
	if (loggingEnabled == 1) {
		printf("%s\n", logEntry);
	}
}

int getDistanceInCmWithLog(int trig, int echo, char *logInformation) {

	int distance = getDistanceInCm(trig, echo);

	char msg[100];
	sprintf(msg, "%s distance: %d cm", logInformation, distance);
	logIt(msg);
	return distance;
}
// End Helpers

//
void roverControlIface_slowForward(RoverControl* handle) {
	setServo(ENGINE, SLOW_FORWARD);
	speed = SLOW_FORWARD;
	logIt("Slow forward");
}

void roverControlIface_slowBackward(RoverControl* handle) {
	setServo(ENGINE, SLOW_BACKWARD);
	speed = SLOW_BACKWARD;
	logIt("Slow backward");
}

void roverControlIface_setSpeedGivenByRC(RoverControl* handle) {
	speed = getSpeedValue();
	setServo(ENGINE, -speed);
	char msg[50];
	sprintf(msg, "Speed set by RC: %d", speed);
	logIt(msg);
}

void roverControlIface_engineStop(RoverControl* handle) {
	setServo(ENGINE, STOP);
	speed = STOP;
	logIt("Engine: stop");
}

void roverControlIface_straight(RoverControl* handle) {
	setServo(REAR_STEERING, NEUTRAL_ANGLE);
	setServo(FRONT_STEERING, NEUTRAL_ANGLE);
	heading = NEUTRAL_ANGLE;

	logIt("Heading: straight");
}
		
void roverControlIface_left(RoverControl* handle, int angle) {
	setServo(REAR_STEERING, limitedSteeringAngle(-angle));
	setServo(FRONT_STEERING, limitedSteeringAngle(angle));
	heading = limitedSteeringAngle(angle);

	char msg[50];
	sprintf(msg, "Heading: left %d degrees", angle);
	logIt(msg);
}
		
void roverControlIface_right(RoverControl* handle, int angle) {
	setServo(REAR_STEERING, limitedSteeringAngle(angle));
	setServo(FRONT_STEERING, limitedSteeringAngle(-angle));
	heading = limitedSteeringAngle(-angle);

	char msg[50];
	sprintf(msg, "Heading: right %d degrees", angle);
	logIt(msg);
}

void roverControlIface_setFrontHeadingGivenByRC(RoverControl* handle) {
	heading = getFrontSteeringValue();
	setServo(FRONT_STEERING, limitedSteeringAngle(-heading));
	char msg[50];
	sprintf(msg, "Front heading set by RC: %d", heading);
	logIt(msg);
}

void roverControlIface_setRearHeadingGivenByRC(RoverControl* handle) {
	heading = getRearSteeringValue();
	setServo(REAR_STEERING, limitedSteeringAngle(-heading));
	char msg[50];
	sprintf(msg, "Rear heading set by RC: %d", heading);
	logIt(msg);
}
		
void roverControlIface_turnTo(RoverControl* handle, int angle) {
	setServo(REAR_STEERING, limitedSteeringAngle(-angle));
	setServo(FRONT_STEERING, limitedSteeringAngle(angle));
	heading = limitedSteeringAngle(angle);

	char msg[50];
	sprintf(msg, "Heading: %d degrees", angle);
	logIt(msg);
}

void roverControlIface_setMidFrontSensorAngle(RoverControl* handle, int angle) {
	setServo(FRONTSENSOR_MOVEMENT, angle);

	char msg[50];
	sprintf(msg, "Set Mid Front Sensor Angle: %d", angle);
	logIt(msg);
}

void roverControlIface_setRearSensorAngle(RoverControl* handle, int angle) {
	setServo(REARSENSOR_MOVEMENT, angle);

	char msg[50];
	sprintf(msg, "Set Rear Sensor Angle: %d", angle);
	logIt(msg);
}

int roverControlIface_getLeftFrontSensorDistanceInCm(RoverControl* handle) {
	return getDistanceInCmWithLog(TRIGLEFT, ECHOLEFT, "Left Front");
}

int roverControlIface_getRightFrontSensorDistanceInCm(RoverControl* handle) {
	return getDistanceInCmWithLog(TRIGRIGHT, ECHORIGHT, "Right Front");
}

int roverControlIface_getMidFrontSensorDistanceInCm(RoverControl* handle) {
	return getDistanceInCmWithLog(TRIGMID, ECHOMID, "Mid Front");
}

int roverControlIface_getFrontSensorsDistanceLowerThan(RoverControl* handle, int minDistance) {
	return roverControlIface_getRightFrontSensorDistanceInCm(handle) < minDistance
	|| roverControlIface_getMidFrontSensorDistanceInCm(handle) < minDistance
	|| roverControlIface_getLeftFrontSensorDistanceInCm(handle) < minDistance;
}

int roverControlIface_getMidRearSensorDistanceInCm(RoverControl* handle) {
	return getDistanceInCmWithLog(TRIGREAR, ECHOREAR, "Mid Rear");
}

int roverControlIface_getSpeed(RoverControl* handle) {
	int speedValue = getSpeedValue();
	char msg[50];
	sprintf(msg, "Speed: %d", speedValue);
	logIt(msg);
	return speedValue;
}

int roverControlIface_getHeading(RoverControl* handle) {
	heading = getFrontSteeringValue();
	char msg[50];
	sprintf(msg, "Heading: %d", heading);
	logIt(msg);
	return heading;
}

void roverControlIfaceRedLED_lEDOn(RoverControl* handle) {
	setPortTo0(REDLED);
	logIt("Set red LED On");
}

void roverControlIfaceRedLED_lEDOff(RoverControl* handle) {
	setPortTo1(REDLED);
	logIt("Set red LED Off");
}

int roverControlIfaceRedLED_getState(RoverControl* handle) {
	return getPortValue(REDLED);
}

int roverControlIface_rovercontrolSetup(RoverControl* handle) {
	int rc = rovercontrolSetup();
	if (rc < 0)
		return rc;

	roverControlIfaceRedLED_lEDOff(handle);
	roverControlIface_engineStop(handle);
	roverControlIface_straight(handle);
	roverControlIface_setMidFrontSensorAngle(handle, 0);
	roverControlIface_setRearSensorAngle(handle, 0);

	return 0;
}

