#ifdef MD

void setup()
{
  Serial.begin(115200);

  iAm = "mama-duck";
  empty.whoAmI = "mama-duck";
  setupDuck();

  setupDisplay();
  setupLoRa();
  setupPortal();

  if(QuackPack == 1)
  {
    setupQuack();
  }

  Serial.println("Mama Online");
  u8x8.drawString(0, 1, "Mama Online");
}

void loop()
{

  if(QuackPack == 1)
  {
    loopQuack();
    sendPayload();
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
  if (offline.fromCiv == 0 && offline.phone != NULL && offline.phone != "" && offline.path.indexOf(empty.duckID) < 0) {
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

#endif
