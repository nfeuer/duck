#ifdef DETECTOR
#include "timer.h"

auto timer = timer_create_default(); // create a timer with default settings

void setup() {
  Serial.begin(115200);

  iAm = "duckDetector";
  empty.whoAmI = "duckDetector";
  setupDuck();

  setupLoRa();

  timer.every(5000, ping);

  Serial.print("Detector Online");
}

void loop() {
  timer.tick();

  receive(LoRa.parsePacket());

  if(offline.msg != "0") {
    //ledOn(offline.msg);
    Serial.print(offline.msg);
    offline.msg = "0";
  }
}

bool ping(void *) {

  LoRa.beginPacket();
  couple(iamhere, "0");
  LoRa.endPacket();

  return true;
}


#endif
