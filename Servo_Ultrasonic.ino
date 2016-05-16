#define TRIGGER_PIN 13
#define ECHO_PIN     12
#define RECV_PIN     11
#define MAX_DISTANCE 200

#include <Servo.h>
#include <IRremote.h>
#include <NewPing.h>
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;  // create servo object to control a servo
IRrecv irrecv(RECV_PIN);
decode_results results;
int DistanceCm;
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(10);
  Serial.begin(9600);

}

void loop() {
 
  delay(100);// Wait 100ms between pings (about 10 pings/sec). 29ms should be the shortest delay between pings.
  DistanceCm = sonar.ping_cm();
  val = round(DistanceCm);
  
  val = map(DistanceCm, 0, 110, 0, 90);     // scale it to use it with the servo (value between 0 and 180) 
  Serial.println(val);
  myservo.write(45);                  // sets the servo position according to the scaled value 
  delay(100);

}
