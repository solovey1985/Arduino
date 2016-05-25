//#include "solorob.h"
#define TRIGGER_PIN 13
#define ECHO_PIN     12
#define RECV_PIN     11
#define MAX_DISTANCE 200
//Motors
#define IN1 2  
#define IN2 3
#define IN3 4 //2
#define IN4 5 //3
#define ENA 9
#define ENB 6

typedef enum{
 LEFT,
 RIGHT,
 FORWARD,
 BACKWARD
} Directions;

Directions direct;

#include <Servo.h>
#include "IRremote.h"
#include <NewPing.h>


typedef enum {
  MOVE,
  STOP,
  TURN
} MotorCommands;

MotorCommands motorCommand;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;  // create servo object to control a servo
IRrecv irrecv(RECV_PIN);
decode_results results;
int DistanceCm;
int val = 0;    // variable to read the value from the analog pin
bool isCommandSet = false;
int signal;

int i;
void setup() {
  //Motors
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  //END Motors
  
  myservo.attach(10);
  myservo.write(0);
  Serial.begin(9600);
  pinMode(RECV_PIN, INPUT);
  irrecv.enableIRIn(); // Start the receiver
  motorCommand = STOP;
 
}
/**/
void loop() {

int pos;
  //Read IR commands
 ReadIR();
 
  Serial.println(motorCommand);
  RunMotorCommand();
  Scan(90);
  Serial.println(sonar.ping_cm());
   //If Moving 
    //Get Distance to an obstacle
    //If Distance is critical
      //Stop Move
      //Find direction to turn
      //Make turn
      //Move forward

   //If Time to work is overlimit
   //Stop and wait for next command from IR controll
  
    /**/
  
  }
void ReadIR(){
  if (irrecv.decode(&results)) // Если данные пришли
  {
    signal = int(results.value);
    SetMotorsCommand();
    RunMotorCommand();
    // Отправляем полученную данную в консоль
    irrecv.resume(); // Принимаем следующую команду
   // decode(signal);
    
  }
 
  }
void SetMotorsCommand(){
     isCommandSet = false;
     switch(signal){
        case -30601: //Master +
          motorCommand = MOVE;
        break;
        case 18613: //Master -
          motorCommand = STOP;
        break;

        default:
          motorCommand = STOP;
        break;
      }
}
//Motor
void Move(){
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW); 
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW); 

 }

void Turn(){
    if(direct == LEFT){
        digitalWrite (IN1, HIGH);
        digitalWrite (IN2, LOW); 
        digitalWrite (IN3, LOW);
        digitalWrite (IN4, HIGH);    
      }
    if(direct == RIGHT){
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, HIGH); 
        digitalWrite (IN3, HIGH);
        digitalWrite (IN4, LOW);    
      }
      direct = FORWARD;
  }
void Stop(){
  
  digitalWrite (IN2, LOW);
  digitalWrite (IN1, LOW); 
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, LOW); 
  
  }
//HC-SR04
void Scan(int degree){
    DistanceCm = sonar.ping_cm();
	if (DistanceCm < 10) {
		motorCommand = STOP;
    myservo.write(0);
    delay(1000);
    DistanceCm = sonar.ping_cm();
      if(DistanceCm >= 25)
        {
          direct = RIGHT;
          Turn();
          
        }
        else{
            myservo.write(180);
            delay(1000);
            DistanceCm = sonar.ping_cm();
            if(DistanceCm>=25)
            {
              direct = LEFT;
              Turn();  
              
            }
          }
	}
	else {
		motorCommand = MOVE;
	}
	isCommandSet = false;
  myservo.write(90);
  delay(200);
  }
//IR
void RunMotorCommand(){
    if(!isCommandSet){
    switch (motorCommand){
      case 0:
        Move();
      break;
      case 1:
        Stop();
       break;
       default:
        Stop();
       break;
      }
      isCommandSet = true;
     }
  }

  void Faster(){
    for (i = 50; i <= 250; ++i)
    {
        analogWrite(ENA, i);
        analogWrite(ENB, i);
        delay(30);
    }
  }

  void Slower(){
    for (i = 180; i >= 50; --i)
    {
        analogWrite(ENA, i);
        analogWrite(ENB, i);
        delay(30);
    }  
  }



