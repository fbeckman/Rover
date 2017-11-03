/* roverControl */

#include "../include/rovercontrol.h"
#include <stdio.h>
#include "../src-gen/RoverControl.h"

#define ENGINE 12  /* PWM channel of the engine controller */
#define REAR_STEERING 0  /* PWM channel of the rear steering servo */
#define FRONT_STEERING 14  /* PWM channel of the front steering servo */
#define FRONTSENSOR_MOVEMENT 15  /* PWM channel of the front sensor servo */
#define REARSENSOR_MOVEMENT 13  /* PWM channel of the rear sensor servo */

// The following GPIO pin numbers are for use with WiringPi.
// The numbers in comment are the respective standard GPIO pin numbers.
#define REDLED 7  // 4

#define TRIGFRONT 26 // 12
#define ECHOMID 23 // 13

#define TRIGREAR 21 // 5
#define ECHOREAR 22 // 6

// engine speed
#define SLOW_FORWARD -6
#define SLOW_BACKWARD 10
#define STOP 0

// servo positions (servos can have angles from -90 to 90 degree)
// the steering servos are reduced from -60 to 60 degrees
#define MIN_STEERING_ANGLE -60
#define MAX_STEERING_ANGLE 60
#define NEUTRAL_ANGLE 0

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

//predefined functions for engine control
void roverControlIfaceEngine_slowForward(RoverControl* handle) {
	handle->ifaceEngine.speed = handle->iface.slowForward;
	logIt("Slow forward");
}

void roverControlIfaceEngine_slowBackward(RoverControl* handle) {
	handle->ifaceEngine.speed = handle->iface.slowBackward;
	logIt("Slow backward");
}

void roverControlIfaceEngine_stop(RoverControl* handle) {
	handle->ifaceEngine.speed = STOP;
	logIt("Engine: stop");
}

//predefined functions for steering control
void roverControlIfaceSteering_turnTo(RoverControl* handle, int angle) {
	handle->ifaceSteering.frontHeading = angle;
	handle->ifaceSteering.rearHeading = -angle;
	char msg[50];
	sprintf(msg, "Heading: %d degrees", angle);
	logIt(msg);
}

void roverControlIfaceSteering_setFrontHeading(RoverControl* handle, int angle) {
	handle->ifaceSteering.frontHeading = angle;
	char msg[50];
	sprintf(msg, "Heading: %d degrees", angle);
	logIt(msg);
}

void roverControlIfaceSteering_setRearHeading(RoverControl* handle, int angle) {
	handle->ifaceSteering.rearHeading = angle;
	char msg[50];
	sprintf(msg, "Heading: %d degrees", angle);
	logIt(msg);
}

void roverControlIfaceSteering_straight(RoverControl* handle) {
	handle->ifaceSteering.frontHeading = NEUTRAL_ANGLE;
	handle->ifaceSteering.rearHeading = NEUTRAL_ANGLE;
	logIt("Heading: straight");
}

void roverControlIfaceSteering_left(RoverControl* handle, int angle) {
	handle->ifaceSteering.frontHeading = angle;
	handle->ifaceSteering.rearHeading = -angle;
	char msg[50];
	sprintf(msg, "Heading: left %d degrees", angle);
	logIt(msg);
}

void roverControlIfaceSteering_right(RoverControl* handle, int angle) {
	handle->ifaceSteering.frontHeading = -angle;
	handle->ifaceSteering.rearHeading = angle;
	char msg[50];
	sprintf(msg, "Heading: right %d degrees", angle);
	logIt(msg);
}

//predefined functions to move the sensor servos
void roverControlIface_setMidFrontSensorAngle(RoverControl* handle, int angle) {
	handle->ifaceSensors.midFrontSensorAngle = angle;
	char msg[50];
	sprintf(msg, "Set Mid Front Sensor Angle: %d", handle->ifaceSensors.midFrontSensorAngle);
	logIt(msg);
}

void roverControlIface_setMidRearSensorAngle(RoverControl* handle, int angle) {
	handle->ifaceSensors.midRearSensorAngle = angle;
	char msg[50];
	sprintf(msg, "Set Rear Sensor Angle: %d", handle->ifaceSensors.midRearSensorAngle);
	logIt(msg);
}

//TODO
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


//get command to execute from file (e.g written by Web Service)
void roverControlIface_getExternalCommand(RoverControl *handle) {
	handle->iface.externalCommand = getExternalCommand();
	char msg[50];
	sprintf(msg, "External Command: %d", handle->iface.externalCommand);
	logIt(msg);
}

//get external parameter values from file
void roverControlIface_getExternalParameters(RoverControl *handle) {
	char msg[50];
	handle->iface.minFrontDistance = getExternalParameter("minFrontDistance");
	sprintf(msg, "External Parameter minFrontDistance: %d", handle->iface.minFrontDistance);
	logIt(msg);
	handle->iface.minRearDistance = getExternalParameter("minRearDistance");
	sprintf(msg, "External Parameter minRearDistance: %d", handle->iface.minRearDistance);
	logIt(msg);
	handle->iface.slowForward = getExternalParameter("slowForward");
	sprintf(msg, "External Parameter slowForward: %d", handle->iface.slowForward);
	logIt(msg);
	handle->iface.slowBackward = getExternalParameter("slowBackward");
	sprintf(msg, "External Parameter slowBackward: %d", handle->iface.slowBackward);
	logIt(msg);
	handle->iface.minLengthParkingSpace = getExternalParameter("minLengthParkingSpace");
	sprintf(msg, "External Parameter minLengthParkingSpace: %d", handle->iface.minLengthParkingSpace);
	logIt(msg);
	handle->iface.minWidthParkingSpace = getExternalParameter("minWidthParkingSpace");
	sprintf(msg, "External Parameter minWidthParkingSpace: %d", handle->iface.minWidthParkingSpace);
	logIt(msg);

}

//basic sensors read
void roverControlIface_readFromSensors(RoverControl *handle) {
	handle->ifaceSensors.midFrontSensorDistanceInCm = getDistanceInCmWithLog(TRIGFRONT, ECHOMID, "Mid Front");
	handle->ifaceSensors.midRearSensorDistanceInCm = getDistanceInCmWithLog(TRIGREAR, ECHOREAR, "Mid Rear");
}

//read PWM values from remote control receiver
void roverControlIface_readFromRemoteControl(RoverControl *handle) {
	handle->ifaceRemoteControl.speed = -getSpeedValue();
	handle->ifaceRemoteControl.frontHeading = -getFrontSteeringValue();
	handle->ifaceRemoteControl.rearHeading = -getRearSteeringValue();
}

//basic actuators write
void roverControlIface_writeToActuators(RoverControl *handle) {
	setServo(FRONT_STEERING, limitedSteeringAngle(handle->ifaceSteering.frontHeading));
	setServo(REAR_STEERING, limitedSteeringAngle(handle->ifaceSteering.rearHeading));
	setServo(FRONTSENSOR_MOVEMENT, handle->ifaceSensors.midFrontSensorAngle);
	setServo(REARSENSOR_MOVEMENT, handle->ifaceSensors.midRearSensorAngle);
	setServo(ENGINE, handle->ifaceEngine.speed);
}

int roverControlIface_rovercontrolSetup(RoverControl* handle) {
	int rc = rovercontrolSetup();
	if (rc < 0)
		return rc;

	roverControlIfaceRedLED_lEDOff(handle);
	roverControlIfaceEngine_stop(handle);
	roverControlIfaceSteering_straight(handle);
	handle->ifaceSensors.midFrontSensorAngle = 0;
	handle->ifaceSensors.midRearSensorAngle = 0;

	return 0;
}

