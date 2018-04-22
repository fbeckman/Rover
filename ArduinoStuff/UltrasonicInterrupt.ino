/*
Arduino Uno HC-SR04 ultrasonic range finder program using interrupts 
Author:  Steve Garratt 
Date:    19/10/13
 
Interrupts from timer 1 are used to schedule and deliver the sensor
trigger pulse.

The duration of the sensor echo signal is measured by generating an
external interrupt ervery time the echo signal changes state.

This sketch uses the TimerOne library downloadable from here:
http://code.google.com/p/arduino-timerone/downloads/detail?name=TimerOne-v9.zip&can=2&q=

Install the library using the following guide:
http://arduino.cc/en/Guide/Libraries

The measured distance is shown on an OLED display
*/

#include <TimerOne.h>                                 // Header file for TimerOne library
#include <PinChangeInterrupt.h>                       // PinChangeInterrupt by NicoHood

#include <font6x8.h>
#include <nano_gfx.h>
#include <nano_gfx_types.h>
#include <sprite_pool.h>
#include <ssd1306.h>
#include <ssd1306_fonts.h>
#include <ssd1331_api.h>
#include <tiny_buffer.h>
#include <tiny_ssd1306.h>


#define trigPin 12                                    // Pin 12 trigger output
#define echoPin1 11                                   // Pin 11 Echo input
#define echoPin2 10                                    // Pin 10 Echo input

#define TIMER_US 50                                   // 50 uS timer duration 
#define TICK_COUNTS 4000                              // 200 mS worth of timer ticks

volatile long echo_start1 = 0;                         // Records start of echo pulse 
volatile long echo_end1 = 0;                           // Records end of echo pulse
volatile long echo_duration1 = 0;                      // Duration - difference between end and start
volatile long echo_start2 = 0;                         // Records start of echo pulse 
volatile long echo_end2 = 0;                           // Records end of echo pulse
volatile long echo_duration2 = 0;                      // Duration - difference between end and start
volatile int trigger_time_count = 0;                  // Count down counter to trigger pulse time


// ----------------------------------
// setup() routine called first.
// A one time routine executed at power up or reset time.
// Used to initialise hardware.
// ----------------------------------
void setup() 
{
  pinMode(trigPin, OUTPUT);                           // Trigger pin set to output
  pinMode(echoPin1, INPUT);                            // Echo pin set to input
  pinMode(echoPin2, INPUT);                            // Echo pin set to input
  
  ssd1306_128x64_i2c_init();
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_fillScreen(0x00);
  
  Timer1.initialize(TIMER_US);                        // Initialise timer 1
  Timer1.attachInterrupt( timerIsr );                 // Attach interrupt to the timer service routine 
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(echoPin1), echo_interrupt1, CHANGE);  // Attach interrupt to the sensor echo input
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(echoPin2), echo_interrupt2, CHANGE);  // Attach interrupt to the sensor echo input
}

// ----------------------------------
// loop() Runs continuously in a loop.
// This is the background routine where most of the processing usualy takes place.
// Non time critical tasks should be run from here.
// ----------------------------------
void loop()
{
    char buf [15];
    sprintf (buf, "%d   ", echo_duration2 / 58);
    ssd1306_printFixedN (0, 16, buf, STYLE_NORMAL, FONT_SIZE_2X);
    sprintf (buf, "%d   ", echo_duration1 / 58);
    ssd1306_printFixedN (0, 36, buf, STYLE_NORMAL, FONT_SIZE_2X);

    delay(100);                                       // every 100 mS
}

// --------------------------
// timerIsr() 50uS second interrupt ISR()
// Called every time the hardware timer 1 times out.
// --------------------------
void timerIsr()
{
    trigger_pulse();                                 // Schedule the trigger pulses
}

// --------------------------
// trigger_pulse() called every 50 uS to schedule trigger pulses.
// Generates a pulse one timer tick long.
// Minimum trigger pulse width for the HC-SR04 is 10 us. This system
// delivers a 50 uS pulse.
// --------------------------
void trigger_pulse()
{
      static volatile int state = 0;                 // State machine variable

      if (!(--trigger_time_count))                   // Count to 200mS
      {                                              // Time out - Initiate trigger pulse
         trigger_time_count = TICK_COUNTS;           // Reload
         state = 1;                                  // Changing to state 1 initiates a pulse
      }
    
      switch(state)                                  // State machine handles delivery of trigger pulse
      {
        case 0:                                      // Normal state does nothing
            break;
        
        case 1:                                      // Initiate pulse
           digitalWrite(trigPin, HIGH);              // Set the trigger output high
           state = 2;                                // and set state to 2
           break;
        
        case 2:                                      // Complete the pulse
        default:      
           digitalWrite(trigPin, LOW);               // Set the trigger output low
           state = 0;                                // and return state to normal 0
           break;
     }
}

// --------------------------
// echo_interrupt() External interrupt from HC-SR04 echo signal. 
// Called every time the echo signal changes state.
//
// Note: this routine does not handle the case where the timer
//       counter overflows which will result in the occassional error.
// --------------------------
void echo_interrupt1()
{
  switch (digitalRead(echoPin1))                     // Test to see if the signal is high or low
  {
    case HIGH:                                      // High so must be the start of the echo pulse
      echo_end1 = 0;                                 // Clear the end time
      echo_start1 = micros();                        // Save the start time
      break;
      
    case LOW:                                       // Low so must be the end of the echo pulse
      echo_end1 = micros();                          // Save the end time
      echo_duration1 = echo_end1 - echo_start1;        // Calculate the pulse duration
      break;
  }
}

void echo_interrupt2()
{
  switch (digitalRead(echoPin2))                     // Test to see if the signal is high or low
  {
    case HIGH:                                      // High so must be the start of the echo pulse
      echo_end2 = 0;                                 // Clear the end time
      echo_start2 = micros();                        // Save the start time
      break;
      
    case LOW:                                       // Low so must be the end of the echo pulse
      echo_end2 = micros();                          // Save the end time
      echo_duration2 = echo_end2 - echo_start2;        // Calculate the pulse duration
      break;
  }
}
