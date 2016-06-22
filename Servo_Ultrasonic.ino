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

#include <Servo.h>
#include "IRremote.h"
#include <NewPing.h>

typedef enum{
 LEFT,
 RIGHT,
 FORWARD,
 BACKWARD
} Directions;

Directions direct;


typedef enum {
  
} RoboState;

typedef enum {
  MOVE,
  STOP,
  TURN
} MotorCommands;

MotorCommands motorCommand;
RoboState roboState;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;  // create servo object to control a servo
IRrecv irrecv(RECV_PIN);
decode_results results;
int DistanceCm;
int val = 0;    // variable to read the value from the analog pin
bool isCommandSet = false;
int newSignal;
int oldSignal;

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
   
    ReadIR();
    delay(100);
    Watch();
    if(!isCommandSet){
      RunMotorCommand();  
    }    
  }
  void Watch(){
    DistanceCm = sonar.ping_cm();
    delay(50);
    if(DistanceCm != 0 && IsObstacle()){
       Serial.println("---Watch---");
       Serial.println(sonar.ping_cm());
       motorCommand = STOP;
       isCommandSet = false;
    }
  }
  void Turn(int t){
   Serial.println("---Turn---");
    if(direct == LEFT){
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW); 
        digitalWrite (IN3, LOW);
        digitalWrite (IN4, HIGH);    
      }
    if(direct == RIGHT){
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, HIGH); 
        digitalWrite (IN3, LOW);
        digitalWrite (IN4, LOW);    
      }
      delay(t);
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, LOW); 
        digitalWrite (IN3, LOW);
        digitalWrite (IN4, LOW);
      direct = FORWARD;
  }
void ReadIR(){
  if (irrecv.decode(&results)) // Если данные пришли
    {
      newSignal = int(results.value);
      Serial.println(newSignal); 
      SetMotorsCommand(); 
      RunMotorCommand();
      irrecv.resume(); // Принимаем следующую команду
    }
 
  }
  
void SetMotorsCommand(){
     if(newSignal != oldSignal){
     isCommandSet = false;
     switch(newSignal){
        case -30601: //Master +
          motorCommand = MOVE;
          Serial.println("MOVE command is setted");
        break;
        case 18615: //Master -
          motorCommand = STOP;
          Serial.println("STOP command is setted");
        break;

        default:
          motorCommand = STOP;
        break;
      }
      oldSignal = newSignal;
      }
}

void RunMotorCommand(){
   Serial.println("---Run Motor Command---");
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
//Motor
void Move(){
   Serial.println("---Move---");
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW); 
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW); 

 }


void Stop(){
   Serial.println("---Stop---");
  digitalWrite (IN2, LOW);
  digitalWrite (IN1, LOW); 
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, LOW); 
  
  }
//HC-SR04
void Scan(){
   Serial.println("---Scan---");
    DistanceCm = sonar.ping_cm();
	if (IsObstacle()) {
		motorCommand = STOP;
    myservo.write(0);
    delay(200);
    DistanceCm = sonar.ping_cm();
      if(IsObstacle())
        {
          direct = RIGHT;
          Turn(3000);
          
        }
        else{
            myservo.write(180);
            delay(200);
            DistanceCm = sonar.ping_cm();
            if(IsObstacle())
            {
              direct = LEFT;
              Turn(3000);  
              
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


  void Faster(){
    for (i = 50; i <= 250; ++i)
    {
        analogWrite(ENA, i);
        analogWrite(ENB, i);
        delay(50);
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
  int SetScanningAngle(){
    return 90;
  }
  bool IsObstacle(){
    return DistanceCm <= 15;
  }
  bool CanMove(){
    return true;
  }

  bool ShouldStop(){
    return false;
   }



  


