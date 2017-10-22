/* rovercontrol */

#include "../include/wiringPi.h"
#include "../include/pca9685.h"
#include "../include/pigpio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Sensors
// Ultrasonic Sensors
int getDistanceInCm(int trig, int echo) {
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
	//Send trig pulse
	digitalWrite(trig, HIGH);
	delayMicroseconds(20);
	digitalWrite(trig, LOW);

	//Wait for echo start
	while(digitalRead(echo) == LOW);

	//Wait for echo end
	long startTime = micros();
	while(digitalRead(echo) == HIGH);
	long travelTime = micros() - startTime;

	//Get distance in cm
	int distance = travelTime / 58;

	return distance;
}
// End Ultrasonic Sensors
// End Sensors

// Actuators
// Servos
#define PIN_BASE 300
#define HERTZ 60

#define SERVOMIN 160
#define SERVOMAX 610

int pwmSetup() {
	int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		return fd;
	}
	// Reset all output 
	pca9685PWMReset(fd);
	return fd;
}	

int convertDegreeToPulseLength(int degree)
{
	int pulseLength;
	
	if (degree > 90) { degree = 90; };
	if (degree < -90) { degree = -90; };
	pulseLength = (int)((SERVOMAX + SERVOMIN) / 2) + (int)(degree) * ((SERVOMAX + SERVOMIN) / 180);
	if (pulseLength < SERVOMIN) { pulseLength = SERVOMIN; }
	else if (pulseLength > SERVOMAX) { pulseLength = SERVOMAX; };
	//printf("pulseLength %d\n", pulseLength);
	return pulseLength;
}

void setServo(int channel, int degree) {
	//printf("Degree %d\n", degree);
	pwmWrite(PIN_BASE + channel, convertDegreeToPulseLength(degree));
}
// End Servos
// End Actuators

// GPIO
void setPortTo0(int port) {
	pinMode(port, OUTPUT);
	digitalWrite(port, 0);
} 

void setPortTo1(int port) {
	pinMode(port, OUTPUT);
	digitalWrite(port, 1);
}

int getPortValue(int port) {
	pinMode(port, INPUT);
	return digitalRead(port);
}

#define ZEROTICKSFRONT 1480
int lastLevelFront = -1;
int startTickFront = 0;
int endTickFront = 0;
int ticksFront = ZEROTICKSFRONT;
void frontSteeringPWM(int gpio, int level, uint32_t tick) {
	if (lastLevelFront == -1) {
		lastLevelFront = level;
		return;
	}
	if (lastLevelFront == 0 && level == 1) {
		startTickFront = tick;
	}
	if (lastLevelFront == 1 && level == 0) {
		endTickFront = tick;
		ticksFront = endTickFront - startTickFront;
		//printf("FrontSteeringTicks %d\n", ticksFront);
		if (ticksFront < 980 || ticksFront > 2050) {
			ticksFront = ZEROTICKSFRONT;
		}
	}
	lastLevelFront = level;
}

int getFrontSteeringTicks() {
	return ticksFront;
}
int getFrontSteeringValue() {
	return (int)((ZEROTICKSFRONT - ticksFront) * 18 / 100);
}

#define ZEROTICKSREAR 1620
int lastLevelRear = -1;
int startTickRear = 0;
int endTickRear = 0;
int ticksRear = ZEROTICKSREAR;
void rearSteeringPWM(int gpio, int level, uint32_t tick) {
	if (lastLevelRear == -1) {
		lastLevelRear = level;
		return;
	}
	if (lastLevelRear == 0 && level == 1) {
		startTickRear = tick;
	}
	if (lastLevelRear == 1 && level == 0) {
		endTickRear = tick;
		ticksRear = endTickRear - startTickRear;
		//printf("RearSteeringTicks %d\n", ticksRear);
		if (ticksRear < 1080 || ticksRear > 2170) {
			ticksRear = ZEROTICKSREAR;
		}
	}
	lastLevelRear = level;
}
int getRearSteeringTicks() {
	return ticksRear;
}
int getRearSteeringValue() {
	return (int)((ZEROTICKSREAR - ticksRear) * 18 / 100);
}

#define ZEROTICKSSPEED 1490
int lastLevelSpeed = -1;
int startTickSpeed = 0;
int endTickSpeed = 0;
int ticksSpeed = ZEROTICKSSPEED;
void speedPWM(int gpio, int level, uint32_t tick) {
	if (lastLevelSpeed == -1) {
		lastLevelSpeed = level;
		return;
	}
	if (lastLevelSpeed == 0 && level == 1) {
		startTickSpeed = tick;
	}
	if (lastLevelSpeed == 1 && level == 0) {
		endTickSpeed = tick;
		ticksSpeed = endTickSpeed - startTickSpeed;
		//printf("SpeedTicks %d\n", ticksSpeed);
		if (ticksSpeed < 1000 || ticksSpeed > 2000) {
			ticksSpeed = ZEROTICKSSPEED;
		}
	}
	lastLevelSpeed = level;
}
int getSpeedTicks() {
	return ticksSpeed;
}
int getSpeedValue() {
	return (int)((ZEROTICKSSPEED - ticksSpeed) * 18 / 93);
}

// End GPIO

int getExternalCommand() {
//	return 1;
	FILE *externalCommandFile;
	char buff[255];
	externalCommandFile = fopen("/var/local/rovercontrol/command", "r");
	fscanf(externalCommandFile, "%s", buff);
	fclose(externalCommandFile);
	if (strcmp(buff, "Stop") == 0) return 0;
	if (strcmp(buff, "Explore") == 0) return 1;
	if (strcmp(buff, "Park") == 0) return 2;
	if (strcmp(buff, "RemoteControl") == 0) return 3;
	return 0;
}

int getExternalParameter(char* parameterName) {
	FILE *externalParametersFile;
	char buff[255];
	char *parameter;
	int result = 0;
	externalParametersFile = fopen("/var/local/rovercontrol/parameters", "r");
	while (fgets(buff, sizeof(buff), externalParametersFile) != NULL)
	{
		buff[strlen(buff)] = 0;
		if (strncmp(buff, parameterName, strlen(parameterName)) == 0) {
			strtok(buff, "="); parameter = strtok(NULL, "=");
			if (parameter != NULL) {
				result = atoi(parameter);
				break;
			}
		}
	}
	fclose(externalParametersFile);
	return result;
}


int rovercontrolSetup() {
	int rc = wiringPiSetup();
	if (rc < 0)
		return rc;
	rc = pwmSetup();
	if (rc < 0)
		return rc;
	rc = gpioInitialise();
	if (rc <0)
		return rc;
	gpioSetAlertFunc(21, frontSteeringPWM);
	gpioSetAlertFunc(20, rearSteeringPWM);
	gpioSetAlertFunc(19, speedPWM);
	return 0;
}

