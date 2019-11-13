//Sample quackpack sending BMP 180 data
#ifdef QUACKPACK
//Download the BMP 180 library here:
#include <Adafruit_BMP085_U.h>
//Use timer to send data at intervals without using delays!
//Download the Timer library here:
#include "timer.h"

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085); //This will be used to get your data

//Create a timer
//Calling it timer2 so it doesn't interfere with other timers
auto timer2 = timer_create_default();

typedef struct
{
  String     deviceID; //Will store your device ID
  String    sensorVal; //Stores your data
} Quack;
Quack payload;

//You can call this function whatever you want, just make sure your Duck calls it in setup()!
void setupQuack() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.print("setupQuack");

  //Temperature and pressure
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    QuackPack = false; //Device not detected, so switch to normal duck
    sendQuacks(payload.deviceID, uuidCreator(), "Sensor failed to start"); //Send error report
    delay(1000);
    sendQuacks(payload.deviceID, uuidCreator(), "Sensor failed to start"); //Send error report and continue working
  } else {
    QuackPack = true;
    Serial.println("BMP on");
  }

  payload.deviceID  = ""; //Put your device ID here as a String
  payload.sensorVal = "";

  if(QuackPack == true) {
    Serial.println("Start timer");
    timer2.every(5000, getSensorData);
  }

}

//Call this function whatever you want, just make sure you included it in your Duck's loop()!
void loopQuack() {
  timer2.tick(); //Moves the timer forward
}

//Reads and packages data to be sent
bool getSensorData(void *){
  float T,P;
  
  bmp.getTemperature(&T);
  Serial.println(T);
  bmp.getPressure(&P);
  Serial.println(P);
  
  payload.sensorVal = "Temp: " + String(T) + " Pres: " + String(P); //Record data
  
  offline.path = "";
  sendQuacks(payload.deviceID, uuidCreator(), payload.sensorVal); //Send data
  offline.path = "";
  
  return true;
}
#endif
