// If Quack is Defined in SetUp QuackPack will be Compiled with rest of MamaQuack
#ifdef MAMAQUACK
#include <Adafruit_BMP085_U.h>
#include "timer.h"

// Mama Sensor code

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
auto timer2 = timer_create_default(); // create a timer with default settings

typedef struct
{
  String     deviceID; //Should send as a char
  String    sensorVal;
} Quack;
Quack payload;

void setupQuack()
{
  QuackPack = true;
  payload.deviceID  = empty.duckID; //Should send as a char
  payload.sensorVal = "";

  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  timer2.every(5000, getSensorData);
  
  Serial.begin(115200);
  Serial.print("setupMamaQuack()");

  Serial.println("\n==============\n");
}

void loopQuack()
{
  timer2.tick();
}

bool getSensorData(void *){
  float T,P;
  
  bmp.getTemperature(&T);
  Serial.println(T);
  bmp.getPressure(&P);
  Serial.println(P);

  payload.sensorVal = "Temp: " + String(T) + " Pres: " + String(P); //Store Data
  
  sendQuacks(payload.deviceID, "message id here", payload.sensorVal); //Send data

  return true;
}

#endif
