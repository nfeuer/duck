#ifdef DL

void setup()
{
  Serial.begin(115200);

  iAm = "Ducklink";
  setupDuck();

  setupDisplay();
  setupLoRa();
  setupPortal();

  Serial.println("Ducklink Online");
  u8x8.drawString(0, 1, "Ducklink Online");
}


void loop()
{
  // Handles Captive Portal Requests
  dnsServer.processNextRequest();
  webServer.handleClient();

  // ⚠️ Parses Civilian Requests into Data Structure
  //offline = 
  readData();

  if (offline.fromCiv == "yes" && offline.fname != "")
  {
    sendPayload(offline);
    showReceivedData();
  }
  else
  {
    delay(500);
    Serial.print(".");
  }

  // Sends Duck Stat every 30 minutes
  sendDuckStat(offline);
}

#endif
