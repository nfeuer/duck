#ifdef MD

void setup()
{
  Serial.begin(115200);

  iAm = "Mama";
  setupDuck();

  setupDisplay();
  setupLoRa();
  setupPortal();

  Serial.println("Mama Online");
  u8x8.drawString(0, 1, "Mama Online");
}


void loop()
{
  // Handles Captive Portal Requests
  dnsServer.processNextRequest();
  webServer.handleClient();

  // ⚠️ Parses Civilian Requests into Data Structure
  readData();
  if (offline.fromCiv != "" && offline.fromCiv == "yes" && offline.fname != "")
  {
    sendPayload(offline);
    Serial.print("Sending Wifi Data from Mama\n");
  }

  receive(LoRa.parsePacket());
  if (offline.fromCiv != "" && offline.fromCiv == "yes")
  {
    sendPayload(offline);
    Serial.print("I'm here");
  }

  // Sends Duck Stat every 30 minutes
  sendDuckStat(offline);
}

#endif
