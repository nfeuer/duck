#ifdef MAMAPING

#include <DNSServer.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "index.h"

IPAddress apIP(192, 168, 1, 1);
WebServer webServer(80);

DNSServer dnsServer;
const byte DNS_PORT = 53;

/**
   Hotspot/Access Point (🐥 DuckLink 🆘 )
   Local DNS (duck.local)
*/
const char *AP   = " 🆘 EMERGENCY PORTAL";
//const char *AP   = " 🎅DUCK YOU HUMAN";

const char *DNS  = "duck";

String portal = MAIN_page;
String id = "";

/**
   Tracer for debugging purposes
   Toggle (trace = 1) to print statements in Serial
   Toggle (trace = 0) to turn off statements
*/
int trace         = 0;

byte msgCount     = 0;             // count of outgoing messages
int interval      = 2000;          // interval between sends
long lastSendTime = 0;             // time of last packet send

Data victim;

void setup()
{
  Serial.begin(115200);

  setupDisplay();
  setupLoRa();
  setupPortal();

  Serial.println("MAMA-Ping Online");
  u8x8.drawString(0, 1, "MAMA-Ping Online");
}

///**
//    setupPortal
//    Creates:
//    Hotspot (🐥 DuckLink 🆘 )
//    Captive Portal
//    Local DNS (duck.local)
//*/
void setupPortal()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  WiFi.softAP(AP);
  Serial.println("Created Hotspot");

  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.onNotFound([]()
  {
    webServer.send(200, "text/html", portal);
  });
  webServer.begin();

  if (!MDNS.begin(DNS))
  {
    Serial.println("Error setting up MDNS responder!");
  }
  else
  {
    Serial.println("Created local DNS");
    MDNS.addService("http", "tcp", 80);
  }
}

void loop()
{
  //  // Handles Captive Portal Requests
  //  dnsServer.processNextRequest();
  //  webServer.handleClient();
  //
  //  // ⚠️ Parses Civilian Requests into Data Structure
  //  victim = readData();
  //
  //  if (victim.phone != "")
  //  {
  //    sendPayload(victim);
  //  }
  //  else
  //  {
  //    delay(500);
  //    Serial.print(".");
  //  }

  for (int i = 1; i <= 250; i++) {
    Serial.print("Hello der: ");
    Serial.print(i);
    Serial.println(" ");
    u8x8.clear();
    u8x8.setCursor(0, 0);
    u8x8.print("Ping: ");
    u8x8.setCursor(6, 0);
    u8x8.print(i);

    Data victim;
    victim.fping = i;

    sendPayload(victim);

    delay(1000);
    u8x8.setCursor(9, 0);
    u8x8.print(".");

    delay(1000);
    u8x8.setCursor(10, 0);
    u8x8.print(".");

    delay(1000);
    u8x8.setCursor(11, 0);
    u8x8.print(".");

    delay(1000);
    u8x8.setCursor(12, 0);
    u8x8.print(".");

    delay(1000);
    u8x8.setCursor(13, 0);
    u8x8.print(".");

    delay(1000);
  }
}

/**
   readyData
   Reads WebServer Parameters and Parses into Data Struct
   @return Parsed Data Struct
*/
Data readData()
{
  Data victim;

  victim.fping = webServer.arg(0);

  return victim;
}

/**
   sendPayload
   Sends Payload (Victim Data Struct as Bytes)
   Shows Sent Data
*/

void sendPayload(Data victim)
{
  LoRa.beginPacket();
  sendMessage(fping_B, victim.fping);
  LoRa.endPacket();

  msgCount++;                                   // increment message ID

  delay(2000);
}

void sendMessage(byte byteCode, String outgoing)
{
  LoRa.write(byteCode);               // add byteCode
  LoRa.write(outgoing.length());      // add payload length
  LoRa.print(outgoing);               // add payload

  //   Displays Sent Data on OLED and Serial Monitor
  Serial.println("Parameter: " + outgoing);
}


#endif
