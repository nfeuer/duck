// If Quack is Defined in SetUp QuackPack will be Compiled with rest of MamaQuack
#ifdef MAMAQUACK
//#include <Adafruit_BMP085_U.h>
//#include <Adafruit_BMP280.h>
#include "WaveshareSharpDustSensor.h"
#include "timer.h"

// Mama Sensor code

//Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
//Adafruit_BMP280 bmp;

//Dust setup
const int iled = 22; //drive the led of sensor
const int vout = 0;  //analog input
int   adcvalue;
WaveshareSharpDustSensor ds;

auto timer2 = timer_create_default(); // create a timer with default settings

typedef struct
{
  String     deviceID; //Should send as a char
  String    sensorVal;
} Quack;
Quack payload;

void setupQuack()
{
  payload.deviceID  = empty.duckID; //Should send as a char
  payload.sensorVal = "";
    
//  //Temperature and pressure
//  if(!bmp.begin())
//  {
//    /* There was a problem detecting the BMP085 ... check your connections */
//    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
//    QuackPack = false;
//    sendQuacks(payload.deviceID, uuidCreator(), "Sensor failed to start"); //Send data
//    delay(1000);
//    sendQuacks(payload.deviceID, uuidCreator(), "Sensor failed to start"); //Send data
//  } else {
//    QuackPack = true;
//    Serial.println("BMP on");
//  }

  //Dust sensor
  pinMode(iled, OUTPUT);
  digitalWrite(iled, LOW);  //iled default closed

  if(QuackPack == true) {
    Serial.println("Start timer");
    timer2.every(300000, getSensorData);
  }
  
  Serial.begin(115200);
  Serial.print("setupMamaQuack()");

  Serial.println("\n==============\n");
}

void loopQuack()
{
  timer2.tick();
}

bool getSensorData(void *){
//  float T,P;
//  
//  bmp.getTemperature(&T);
//  //T = bmp.readTemperature();
//  Serial.println(T);
//  bmp.getPressure(&P);
//  //P = bmp.readPressure();
//  Serial.println(P);
//  
//  payload.sensorVal = "Temp: " + String(T) + " Pres: " + String(P); //Store Data

  //Dust sensor
  digitalWrite(iled, HIGH);
  delayMicroseconds(280);
  adcvalue = analogRead(vout);
  digitalWrite(iled, LOW);  
  adcvalue = ds.Filter(adcvalue);
  float density = ds.Conversion(adcvalue);
  Serial.print("The current dust concentration is: ");
  Serial.print(density/2500);
  Serial.print(" ug/m3\n");

  payload.sensorVal = "Current dust concentration: " + String(density/2500/3000);
  
  offline.path = "";
  sendQuacks(payload.deviceID, uuidCreator(), payload.sensorVal); //Send data
  offline.path = empty.path;
  
  return true;
}

#endif
