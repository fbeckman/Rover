/*
 * main.c
 *
 *  Created on: 05.11.2016
 *      Author: Frank
 */

#include <stdio.h>
#include "wiringPi.h"
#include "..\include\rovercontrol.h"
#include "sc_timer_service.h"
#include "..\src-gen\RoverControl.h"
#include <unistd.h>

RoverControl handle;

//! As we make use of time triggers (after & every) we make use of a generic timer implementation and need a defined number of timers.
#define MAX_TIMERS 20
//! We allocate the desired array of timers.
static sc_timer_t timers[MAX_TIMERS];

//! The timers are managed by a timer service. */
static sc_timer_service_t timer_service;


void setup() {
	sc_timer_service_init(
				&timer_service,
				timers, MAX_TIMERS,
				(sc_raise_time_event_fp) &roverControl_raiseTimeEvent);
	roverControl_init(&handle);
	roverControl_enter(&handle);
}


#define CYCLE_PERIOD (10) //ms
static unsigned long cycle_count = 0L;
static unsigned long last_cycle_time = 0L;


void loop() {
	unsigned long current_millies = millis();

	if ( cycle_count == 0L || (current_millies >= last_cycle_time + CYCLE_PERIOD) ) {
		sc_timer_service_proceed(&timer_service, current_millies - last_cycle_time);
		last_cycle_time = current_millies;
		if (cycle_count % 10 == 0) roverControlIface_getExternalCommand(&handle);
		if (cycle_count % 100 == 0) roverControlIface_getExternalParameters(&handle);
		if (cycle_count % 2 == 0) roverControlIface_readFromSensors(&handle);
		if (cycle_count % 1 == 0) roverControlIface_readFromRemoteControl(&handle);
		roverControl_runCycle(&handle);
		if (cycle_count % 5 == 0) roverControlIface_writeToActuators(&handle);
		cycle_count++;
	}
}

void roverControl_setTimer(RoverControl* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic) {
	sc_timer_start(&timer_service, (void*) handle, evid, time_ms, periodic);;
}

void roverControl_unsetTimer(RoverControl* handle, const sc_eventid evid) {
	sc_timer_cancel(&timer_service, evid);
}


int main(void) {

	setup();
	while (1) {
		loop();
		usleep(5000);
	}
	return 0;
}


