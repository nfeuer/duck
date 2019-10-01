#ifdef MD
#include "timer.h"

auto timer2 = timer_create_default(); // create a timer with default settings


void setup()
{
  Serial.begin(115200);

  iAm = "mama-duck";
  empty.whoAmI = "mama-duck";
  setupDuck();
  offline.duckID = "A";
  empty.duckID = "A";

  setupDisplay();
  setupLoRa();
  setupPortal();

  #ifdef MAMAQUACK
  QuackPack = true;
  setupQuack();
  Serial.println("MamaQuack - Setup");
  #endif

  if(QuackPack == false) timer2.every(1800000, imAlive); //Report still running
  //if(QuackPack == false) timer2.every(5000, imAlive); //Report still running test

  Serial.println("Mama Online");
  u8x8.drawString(0, 1, "Mama Online");
}

void loop()
{
  if(QuackPack == true)
  {
    loopQuack();
  } else {
    timer2.tick();
  }

  // ⚠️ Parses Civilian Requests into Data Structure
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
  //  strstr(offline.path.toCharArray, empty.duckID) != NULL
  if(offline.whoAmI == "quackpack")
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

  // Sends Duck Stat every 30 minutes
  sendDuckStat(offline);
}

bool imAlive(void *){
  
  sendQuacks(empty.duckID, "message id here", "1"); //Send data
  Serial.print("alive");
  return true;
}

#endif
