#define TRIGGER_PIN  12
#define ECHO_PIN     13



#include <Servo.h>
Servo myservo;  // create servo object to control a servo


int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(9);
  Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

}

void loop() {
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  val = round(cmMsec);
  val = map(val, 0, 110, 0, 180);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);

}
