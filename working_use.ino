
/*created 3 Nov 2008
  By David A. Mellis
  Modified 30 Aug 2011
  by Tom Igoe
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/Ping 
/* 
  This sketch reads a PING))) ultrasonic rangefinder and returns the distance
  to the closest object in range. To do this, it sends a pulse to the sensor to
  initiate a reading, then listens for a pulse to return. The length of the
  returning pulse is proportional to the distance of the object from the sensor */
  
/******************************************************************************************/

/* Treehouse Projects - www.treehouseprojects.ca
Ping HC-SR04 Tutorial
This program is adapted from the example Ping code from Arduino.
Modified by Dimitrios Tsartsanis http://www.instructables.com/member/Tsartsanis/
*/

/******************************************************************************************/
/*DESN37900 Interactive Objects and Environments 2: Physical Computing - Project 1 */
/*Purpose: When theres motion detected, makes a flower using servos and then unwraps */
/* Modified by Jimin Chung, Adriana Rodriguez, Isabella Sulle*/
/* Added in when theres motion within the specific SafeZone, it moves the servo into a clockwise rotation until the rose is completely underway */
/* Added in delays when the material unwraps, that it rotates back when there isn't any motion*/
/* Adjusted the servo #'s and pin numbers to what we set up on the breadboard   */

/******************************************************************************************/

#include<Servo.h>
#include "Timer.h"

Servo servo; 
Servo servo2;
const int pingPin = 7;    //pin which triggers ultrasonic sound
int inPin = 6;            //pin which delivers time to receive echo using pulseIn()
int safeZone = 10;        //range in cm which is considered safe to enter, anything coming within less than 10 cm triggers the toilet paper to unroll

void setup() {
  servo.attach(8);          //attach servo motor to pin 8
  servo2.attach(3);         // attach servo motor to pin 3
}
 
void loop()
{
  long duration, cm; //raw duration in milliseconds, cm is the
  //converted amount into a distance
 
  pinMode(pingPin, OUTPUT);  //sending the signal, starting with LOW for a clean signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
 
  
  pinMode(inPin, INPUT); //setting up the input pin, and receiving the duration in microseconds for the sound to bounce off the object infront
  duration = pulseIn(inPin, HIGH);
   
  cm = microsecondsToCentimeters(duration); // convert the time into a distance
  
  if (cm > safeZone)  //checking if anything is within the safezone
                              
  {
  clockw();
  delay (3500);
  counterw(); 
  
  servo.detach(); // turning off the servo when there's not motion
  servo2.detach();
  
  }
  else
  {
   servo2.attach(3); //Since the servo was detached, making sure it's still turned on 
   servo.attach(8);
   counterw(); // reversing what it was from the if statement 
   delay (3500);
   clockw();
  }

}
 
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

//clockwise
void clockw() {
servo.write(0);
servo2.write(180);
  
}

//counter clock-wise
void counterw() {
servo.write (180);
servo2.write (0);  
}

