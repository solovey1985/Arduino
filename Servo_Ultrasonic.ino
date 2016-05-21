#define TRIGGER_PIN 13
#define ECHO_PIN     12
#define RECV_PIN     11
#define MAX_DISTANCE 200

typedef enum{
 LEFT,
 RIGHT,
 FORWARD,
 BACKWARD,
 STOP
} Directions;

Directions direct;

#include <Servo.h>
#include "IRremote.h"
#include <NewPing.h>
#include <Robo.h>

typedef enum {
  move,
  stop,
  turn
} MotorCommands;

MotorCommands motorCommand;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;  // create servo object to control a servo
IRrecv irrecv(RECV_PIN);
decode_results results;
int DistanceCm;
int val = 0;    // variable to read the value from the analog pin
bool dir = true;
int signal;
Robo rob;

void setup() {
  myservo.attach(10);
  myservo.write(0);
  Serial.begin(9600);
  pinMode(RECV_PIN, INPUT);
  irrecv.enableIRIn(); // Start the receiver
  motorCommand = stop;
}

void loop() {
  //Read IR commands
 signal =  ReadIR();
 SetMotorsCommand();
 Serial.println(motorCommand);
  //If Moving 
    //Get Distance to an obstacle
    //If Distance is critical
      //Stop Move
      //Find direction to turn
      //Make turn
      //Move forward

   //If Time to work is overlimit
   //Stop and wait for next command from IR controll
  
  
  
  }
int ReadIR(){
  if (irrecv.decode(&results)) // Если данные пришли
  {
    signal = int(results.value);
    Serial.println(signal); // Отправляем полученную данную в консоль
    irrecv.resume(); // Принимаем следующую команду
   // decode(signal);
   delay(500); 
  }
  return signal;
  }
void SetMotorsCommand(){
     
     switch(signal){
        case -30601: //Master +
          motorCommand = move;
        break;
        case 18613: //Master -
          motorCommand = stop;
        break;

        default:
          motorCommand = stop;
        break;
      }
}
//Motor
void Move(){
 
 }

void Turn(int degree){

  }
void Stop(){}
//HC-SR04
void Scan(int degree){}
//IR




