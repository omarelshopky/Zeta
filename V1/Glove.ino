#include <SPI.h>         //SPI library for communicate with the nRF24L01
#include <RF24.h>        //The library which helps us to control the radio modem (nRF24L01)
#include <nRF24L01.h>    //To handle nRF24L01 modem driver
#include <Wire.h>        //For communicate
#include <I2Cdev.h>      //For communicate with MPU6050
#include <MPU6050.h>     //The main library of the MPU6050

//nRF24L01 Wireless Module
#define SCK 13
#define MISO 12
#define MOSI 11
#define CSN 10
#define CE 9

//MPU6050 module
#define SCL A5
#define SDA A4
#define INT 2

RF24 RADIO (CE, CSN);
const byte ADDRESS[6] = "161202";

MPU6050 MPU;
int16_t Ax, Ay, Az;
int16_t Gx, Gy, Gz;

byte data[2];

void setup() 
{
  Wire.begin();
  MPU.initialize();
  
  Serial.begin(9600);
  
  RADIO.begin();
  RADIO.setRetries(10,5);
  RADIO.openWritingPipe(ADDRESS);
  RADIO.stopListening();

  // use the code below to change accel/gyro offset values
    /*
    Serial.println("Updating internal sensor offsets...");
    // -76  -2359 1688  0 0 0
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    accelgyro.setXGyroOffset(220);
    accelgyro.setYGyroOffset(76);
    accelgyro.setZGyroOffset(-85);
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    */
}

void loop() 
{
  MPU.getMotion6(&Ax,&Ay,&Az,&Gx,&Gy,&Gz);
  data[0] = map(Ax,-17000,17000,1,100);
  data[1] = map(Ay,-17000,17000,1,100);
  /*
  data[3] = map(Az,-17000,17000,1,100);
  data[4] = map(Gx,-17000,17000,1,100);
  data[5] = map(Gy,-17000,17000,1,100);
  data[6] = map(Gz,-17000,17000,1,100);
  */
  RADIO.write(data,sizeof(data));
}
