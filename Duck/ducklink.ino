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
  // ⚠️ Parses Civilian Requests into Data Structure
  readData();
  if (offline.fromCiv == 1 && offline.fname != NULL && offline.fname != "")
  {
    Serial.println("Start send from DuckLink");
    sendPayload(offline);
    //showReceivedData();
    offline = empty;
    setupDuck();
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
