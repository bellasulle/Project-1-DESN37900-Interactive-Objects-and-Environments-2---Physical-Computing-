
#include<Servo.h>

Servo servo; // create servo object to control a servo
Servo servo2;

const int trigPin = 7;

const int echoPin = 6;

void setup() {

// initialize serial communication:

Serial.begin(9600);

servo.attach(8); // attaches the servo on pin 9 to the servo object
servo2.attach (3);
}
void loop() {

// and the distance result in centimeters:

long duration, cm;

pinMode(trigPin, OUTPUT);

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(20);

digitalWrite(trigPin, LOW);

pinMode(echoPin, INPUT);

duration = pulseIn(echoPin, HIGH);

// convert the time into a distance

cm = microsecondsToCentimeters(duration);

// the condition for the distance

//FORWARD - CLOSE
if ( cm > 2 && cm < 10)

{
  

servo.attach(8); // turning off the servo when there's not motion
servo2.attach(3);
servo.write(180); // sets the servo position according to the scaled value
servo2.write (180); 

delay(4000);

servo.write(0); // sets the servo position according to the scaled value
servo2.write (0);
servo.detach(); // turning off the servo when there's not motion
servo2.detach();


}
//OPPOSITE - FAR AWAY
else if (cm >10 && cm < 20 )

{
servo.attach(8); // turning off the servo when there's not motion
servo2.attach(3);
servo.write(0); // sets the servo position according to the scaled value
servo2.write (0); 

delay(4000);

servo.write(180); // sets the servo position according to the scaled value
servo2.write (180);
servo.detach(); // turning off the servo when there's not motion
servo2.detach();


  
}

else

{
 
servo.detach(); // turning off the servo when there's not motion
servo2.detach();

}


Serial.print(cm);

Serial.print("cm");

Serial.println();

delay(100);

}

long microsecondsToCentimeters(long microseconds) {

// The speed of sound is 340 m/s or 29 microseconds per centimeter.

// The ping travels out and back, so to find the distance of the

// object we take half of the distance travelled.

return microseconds / 29 / 2;

}

