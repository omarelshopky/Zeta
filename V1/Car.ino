#include <SPI.h>         //SPI library for communicate with the nRF24L01
#include <nRF24L01.h>    //To handle nRF24L01 modem driver
#include <RF24.h>        //The main library of the nRF24L01


//HC-05 Bluetooth module
//#define TXD 0
//#define RXD 1

//HC-SR04 Ultrasonic Sensor
//#define ECHO 2
//#define TRIGGER 4

//L298 H-Bridge Motor Driver
#define MOT1FORWARD 7
#define MOT1BACKWARD 8
#define MOT2FORWARD 14
#define MOT2BACKWARD 6
#define ENB 3
#define ENA 5

//nRF24L01 Wireless Module
#define SCK 13
#define MISO 12
#define MOSI 11
#define CSN 10
#define CE 9
 
RF24 RADIO (CE, CSN);
const byte ADDRESS[6] = "161202";

// data[0] = Ax , data[1] = Ay
byte data[2];

void setup() 
{
  Serial.begin(9600);
  pinMode(MOT1FORWARD,OUTPUT);
  pinMode(MOT1BACKWARD,OUTPUT);
  pinMode(MOT2FORWARD,OUTPUT);
  pinMode(MOT2BACKWARD,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  RADIO.begin();
  RADIO.openReadingPipe(0, ADDRESS);
  RADIO.startListening();
}

void loop() 
{
  if (RADIO.available())
  {
    RADIO.read(data,sizeof(data));
    
    /*
    //Test
    Serial.print("Ax: ");
    Serial.print(data[0]);
    Serial.print("  /   ");
    Serial.print("Ay: ");
    Serial.println(data[1]);
    delay(500);
    
    Serial.print("/");
    Serial.print("Az: ");
    Serial.println(data[2]);
    Serial.print("Gx: ");
    Serial.print(data[3]);
    Serial.print("/");
    Serial.print("Gy: ");
    Serial.print(data[4]);
    Serial.print("/");
    Serial.print("Gz: ");
    Serial.println(data[5]);
    Serial.println("---------");
    delay(500);
    */
    //Forward
    if (data[0] <= 18)
    {
      digitalWrite(MOT1FORWARD,1);
      digitalWrite(MOT1BACKWARD,0);
      digitalWrite(MOT2FORWARD,1);
      digitalWrite(MOT2BACKWARD,0);
      analogWrite(ENA,255);
      analogWrite(ENB,255);
    }
    //Backward
    if (data[0] >= 40)
    {
      digitalWrite(MOT1FORWARD,0);
      digitalWrite(MOT1BACKWARD,1);
      digitalWrite(MOT2FORWARD,0);
      digitalWrite(MOT2BACKWARD,1);
      analogWrite(ENA,255);
      analogWrite(ENB,255);
    }
    //Turn Right
    if (data[1] < 48 && data[1] > 17)
    {
      digitalWrite(MOT1FORWARD,1);
      digitalWrite(MOT1BACKWARD,0);
      digitalWrite(MOT2FORWARD,0);
      digitalWrite(MOT2BACKWARD,0);
      analogWrite(ENA,255);
      analogWrite(ENB,255);
    }
    //Turn Lift
    if (data[1] > 74 && data[1] < 95)
    {
      digitalWrite(MOT1FORWARD,0);
      digitalWrite(MOT1BACKWARD,0);
      digitalWrite(MOT2FORWARD,1);
      digitalWrite(MOT2BACKWARD,0);
      analogWrite(ENA,255);
      analogWrite(ENB,255);
    }
    //Spin Right
    if (data[1] <= 17)
    {
      digitalWrite(MOT1FORWARD,1);
      digitalWrite(MOT1BACKWARD,0);
      digitalWrite(MOT2FORWARD,0);
      digitalWrite(MOT2BACKWARD,1);
      analogWrite(ENA,255);
      analogWrite(ENB,255);
    }
    //Spin Lift
    if (data[1] >= 95)
    {
      digitalWrite(MOT1FORWARD,0);
      digitalWrite(MOT1BACKWARD,1);
      digitalWrite(MOT2FORWARD,1);
      digitalWrite(MOT2BACKWARD,0);
      analogWrite(ENA,255);
      analogWrite(ENB,255);
    }
    //Stop
    if (data[0] >= 18 && data[0] <= 40 && data[1] <= 74 && data[1] >= 48)
    {
      digitalWrite(MOT1FORWARD,0);
      digitalWrite(MOT1BACKWARD,0);
      digitalWrite(MOT2FORWARD,0);
      digitalWrite(MOT2BACKWARD,0);
      analogWrite(ENA,0);
      analogWrite(ENB,0);
    }
    
  }
}
