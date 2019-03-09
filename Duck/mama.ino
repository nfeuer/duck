#ifdef MD

void setup()
{
  Serial.begin(115200);

  iAm = "Mama";
  empty.whoAmI = "Mama";
  setupDuck();

  setupDisplay();
  setupLoRa();
  setupPortal();

  Serial.println("Mama Online");
  u8x8.drawString(0, 1, "Mama Online");
}

void loop()
{
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
  if (offline.fromCiv == 0 && offline.phone != NULL && offline.phone != "" && !checkPath(offline.path, empty.duckID))
  {
    offline.path = offline.path + "," + empty.duckID;
    offline.whoAmI = "Mama+Duck";
    delay(2000);
    sendPayload(offline);
    Serial.print("I'm here");
    offline = empty;
  }

  // Sends Duck Stat every 30 minutes
  sendDuckStat(offline);
}

#endif
