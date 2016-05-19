

#define TRIGGER_PIN 13
#define ECHO_PIN     12
#define RECV_PIN     11
#define MAX_DISTANCE 200

#include <Servo.h>
#include "IRremote.h"
#include <NewPing.h>
#include <Robo.h>
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;  // create servo object to control a servo
IRrecv irrecv(RECV_PIN);
decode_results results;
int DistanceCm;
int val = 0;    // variable to read the value from the analog pin
bool dir = true;
String signal;
bool   isForward, isStop;
Robo rob;
void setup() {
  myservo.attach(10);
  myservo.write(0);
  
  Serial.begin(9600);
  pinMode(RECV_PIN, INPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
ReadIR();
  
delay(200);
  
  

 
  }
void ReadIR(){
   String signal;
   if (irrecv.decode(&results)) // Если данные пришли
  {
    signal = String(results.value, HEX); 
    Serial.println(signal); // Отправляем полученную данную в консоль
    irrecv.resume(); // Принимаем следующую команду
    decode(signal);
    Serial.println(isForward); Serial.println(isStop);
  }
  }
void decode(String signal){
     
    if(signal == "ff8877"){
     isForward = true;
     isStop = false;
    }
    if(signal == "ff48b7"){
        isForward = false;
        isStop = true;
    }
}
//Motor
void Move(String direction){}
void Turn(String direction, int degree){}
void Stop(){}
//HC-SR04
void Scan(String direction, int degree){}
//IR
void GetCommand(String IrSignal){}
