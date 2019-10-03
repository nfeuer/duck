#ifdef MD
#include "timer.h"

auto timer = timer_create_default(); // create a timer with default settings

void setup()
{
  Serial.begin(115200);

  iAm = "mama-duck";
  empty.whoAmI = "mama-duck";
  setupDuck();
  offline.duckID = "A";
  empty.duckID = "A";

  //Setup interfaces
  setupDisplay(); //Should probably turn off
  setupLoRa();
  setupPortal();

  #ifdef MAMAQUACK
  QuackPack = true;
  setupQuack();
  Serial.println("MamaQuack - Setup");
  #endif

  if(QuackPack == false) timer.every(1800000, imAlive); //Report still running
  //timer.every(43200000, reboot);
  timer.every(10800000, reboot);

  Serial.println("Mama Online");
  u8x8.drawString(0, 1, "Mama Online");
}

void loop()
{
  if(QuackPack == true) {
    //loopQuack();
  } else {
    timer.tick();
  }

  //Parses Civilian Requests into Data Structure
  readData();
  if (offline.fromCiv == 1 && offline.phone != NULL && offline.phone != "")
  {
    Serial.println("Start Send");
    sendPayload(offline);
    Serial.print("Sending Wifi Data from Mama\n");
    offline = empty;
    offline.fromCiv = 0;
  }

  receive(LoRa.parsePacket());
  if(offline.whoAmI == "quackpack" && offline.path.indexOf(empty.duckID) < 0)
  {
    sendQuacks(qtest.deviceID, qtest.messageID, qtest.payload);
    offline.whoAmI = empty.whoAmI;
  }
  else if (offline.fromCiv == 0 && offline.phone != NULL && offline.phone != "" && offline.path.indexOf(empty.duckID) < 0) {
    offline.path = offline.path + "," + empty.duckID;
    sendPayload(offline);
    Serial.print("I'm here");
    delay(random(0,2500));
    sendPayload(offline);
    offline = empty;
  }
  
}

bool imAlive(void *){
  
  sendQuacks(empty.duckID, uuidCreator(), "1"); //Send data
  Serial.print("alive");
  return true;
}


#endif
