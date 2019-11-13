//Use this to test your wiring!
//Download the BMP 180 library here:
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085); //This will be used to get your data

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.print("setupMamaQuack()");

  //Temperature and pressure
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");

    while(1); //Infinite loop! Ahhhhhhhhhhhhhhhhhh!
  } else {
    Serial.println("BMP on");
  }  

}

void loop() {
  // put your main code here, to run repeatedly:
  float T,P;
  
  bmp.getTemperature(&T);
  Serial.println(T);
  bmp.getPressure(&P);
  Serial.println(P);
  
  delay(1000);
  //Yay, data!
}
