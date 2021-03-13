#include <NewPing.h>

//L298 H-Bridge Motor Driver
#define MOT1FORWARD 7
#define MOT1BACKWARD 8
#define MOT2FORWARD 14
#define MOT2BACKWARD 6
#define ENB 3
#define ENA 5

//HC-SR04 Ultrasonic Sensor
#define ECHO 2
#define TRIGGER 4

void FORWARD(void);
void STOP(void);
void AW3A(void);

NewPing EYES (TRIGGER, ECHO, 200);

void setup() {
  Serial.begin(9600);
  pinMode(MOT1FORWARD,OUTPUT);
  pinMode(MOT1BACKWARD,OUTPUT);
  pinMode(MOT2FORWARD,OUTPUT);
  pinMode(MOT2BACKWARD,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

}

void loop() {
  FORWARD();
  if (EYES.ping_cm() < 20 && EYES.ping_cm() != 0)
  {
    AW3A();
  }

}

void AW3A(void)
{
  STOP();
  digitalWrite(MOT1BACKWARD,1);
  analogWrite(ENA,255);
  delay(1000);
  STOP();
  if (EYES.ping_cm() < 20 && EYES.ping_cm() != 0)
  {
    digitalWrite(MOT2BACKWARD,1);
    analogWrite(ENB,255);
    delay(2000);
    STOP();
  }
}



void FORWARD(void)
{
  digitalWrite(MOT1FORWARD,1);
  digitalWrite(MOT1BACKWARD,0);
  digitalWrite(MOT2FORWARD,1);
  digitalWrite(MOT2BACKWARD,0);
  analogWrite(ENA,255);
  analogWrite(ENB,255);
}

void STOP(void)
{
  digitalWrite(MOT1FORWARD,0);
  digitalWrite(MOT1BACKWARD,0);
  digitalWrite(MOT2FORWARD,0);
  digitalWrite(MOT2BACKWARD,0);
  analogWrite(ENA,0);
  analogWrite(ENB,0);
}
