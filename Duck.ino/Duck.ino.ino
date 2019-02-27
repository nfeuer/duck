#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <U8x8lib.h>

// Ducklink
#include <DNSServer.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "index.h"

/***************************************************
  un/comment lines to compile Ducklink/Mama/Papa
***************************************************/

// Recommendation First compile Mama board, then reverse and compile Papa board
//#define DL
//#define MD
#define PD

#define THIRTYMIN (1000UL * 60 * 30);
unsigned long rolltime = millis() + THIRTYMIN;

#define SS      18
#define RST     14
#define DI0     26
#define BAND    915E6

IPAddress apIP(192, 168, 1, 1);
WebServer webServer(80);

DNSServer dnsServer;
const byte DNS_PORT = 53;

/**
   Hotspot/Access Point (🐥 DuckLink 🆘 )
   Local DNS (duck.local)
*/
const char *AP   = " 🆘 EMERGENCY PORTAL";

const char *DNS  = "duck";

String portal = MAIN_page;
String id = "";
String iAm = "Civ";
String runTime;

/**
   Tracer for debugging purposes
   Toggle (trace = 1) to print offlineements in Serial
   Toggle (trace = 0) to turn off offlineements
*/
int trace         = 0;

byte msgCount     = 0;             // count of outgoing messages
int interval      = 2000;          // interval between sends
long lastSendTime = 0;             // time of last packet send


// Structure with message data
typedef struct
{
  // Duck
  String whoAmI;   // offline Classifier (Default is Civ for Civilian)
  String duckID;   // Duck (ESP32) Mac Address
  String whereAmI; // Geo-coordinates (Default in 0,0 - Null Island) - Under construction - Omer's App
  String runTime;  // How long have I been on?

  // Check to see if message is from Civilian or Duck
  String fromCiv;

  // Civilian
  String fname;
  String street;
  String phone;
  String occupants;
  String danger;
  String vacant;
  String firstaid;
  String water;
  String food;
  String msg;
} Data;

Data offline;

byte whoAmI_B     = 0xA1;
byte duckID_B     = 0xA2;
byte whereAmI_B   = 0xA3;
byte runTime_B    = 0xA4;

byte fromCiv_B    = 0xA5;

byte fname_B      = 0xB1;
byte street_B     = 0xB2;
byte phone_B      = 0xB3;
byte occupants_B  = 0xB4;
byte danger_B     = 0xC1;
byte vacant_B     = 0xC2;
byte firstaid_B   = 0xD1;
byte water_B      = 0xD2;
byte food_B       = 0xD3;
byte msg_B        = 0xE4;

// the OLED used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

void setupDisplay()
{
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
}

// Initial LoRa settings
void setupLoRa()
{
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DI0);

  //Initialize LoRa
  if (!LoRa.begin(BAND))
  {
    u8x8.clear();
    u8x8.drawString(0, 0, "Starting LoRa failed!");
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  else
  {
    Serial.println("LoRa On");
  }

  //  LoRa.setSyncWord(0xF3);         // ranges from 0-0xFF, default 0x34
  LoRa.enableCrc();             // Activate crc
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

/**
   readyData
   Reads WebServer Parameters and couples into Data Struct
   @return coupled Data Struct
*/
void readData()
{
  //  Data offlineA = offline;

  //Serial.println("Tracer -- ID: " + id + " Webserver: " + webServer.arg(0));

  String webId = webServer.arg(0);

  if (id != webId)
  {
    u8x8.clear();
    u8x8.drawString(0, 4, "New Response");

    //    for (int i = 0; i < webServer.args(); i++)
    //    {
    //      Serial.println(webServer.argName(i) + ": " + webServer.arg(i));
    //    }

    offline.fromCiv    = "yes";
    offline.fname      = webServer.arg(1);
    offline.street     = webServer.arg(2);
    offline.phone      = webServer.arg(3);
    offline.occupants  = webServer.arg(4);
    offline.danger     = webServer.arg(5);
    offline.vacant     = webServer.arg(6);
    offline.firstaid   = webServer.arg(7);
    offline.water      = webServer.arg(8);
    offline.food       = webServer.arg(9);
    offline.msg        = webServer.arg(10);

    u8x8.setCursor(0, 16);
    u8x8.print("Name: " + offline.fname);

    Serial.println("Before____ID: " + id + " Webserver: " + webServer.arg(0));

    id = webId;

    Serial.println("After_____ID: " + id + " Webserver: " + webServer.arg(0));


  }
  //  return offlineA;
}

/**
   sendPayload
   Sends Payload (offline Data Struct as Bytes)
   Shows Sent Data
*/

void sendPayload(Data offline)
{
  LoRa.beginPacket();
  couple(whoAmI_B, offline.whoAmI);
  couple(duckID_B, offline.duckID);
  couple(whereAmI_B, offline.whereAmI);
  couple(runTime_B, offline.runTime);

  couple(fromCiv_B, "no");

  couple(fname_B, offline.fname);
  couple(street_B, offline.street);
  couple(phone_B, offline.phone);
  couple(occupants_B, offline.occupants);

  couple(danger_B, offline.danger);
  couple(vacant_B, offline.vacant);

  couple(firstaid_B, offline.firstaid);
  couple(water_B, offline.water);
  couple(food_B, offline.food);

  couple(msg_B, offline.msg);
  LoRa.endPacket();

  msgCount++;                                   // increment message ID

  delay(5000);
}

void couple(byte byteCode, String outgoing)
{
  LoRa.write(byteCode);               // add byteCode
  LoRa.write(outgoing.length());      // add payload length
  LoRa.print(outgoing);               // add payload

  //   Displays Sent Data on OLED and Serial Monitor
  //   Serial.println("Parameter: " + outgoing);
}

//Send duckStat every 30 minutes
void sendDuckStat(Data offline)
{
  if ((long)(millis() - rolltime) >= 0)
  {

    LoRa.beginPacket();
    couple(whoAmI_B, offline.whoAmI);
    couple(duckID_B, offline.duckID);
    couple(whereAmI_B, offline.whereAmI);
    couple(runTime_B, offline.runTime);
    LoRa.endPacket();

    rolltime += THIRTYMIN;
  }
}


void setupDuck()
{
  offline.whoAmI   = iAm;
  offline.duckID   = WiFi.macAddress();
  offline.whereAmI = "0,0"; // Until further dev, default is null island
  offline.runTime  = millis();

  // Test - Print to serial
  //  Serial.println("Class: "        +  offline.whoAmI     );
  //  Serial.println("ID : "          +  offline.duckID    );
  //  Serial.println("Location: "     +  offline.whereAmI     );
  //  Serial.println("On for: "       +  offline.runTime + " milliseconds\n\n" );
}


// Mama and Papa

/**
   receive
   Reads and Parses Received Packets
   @param packetSize
*/
void receive(int packetSize)
{
  if (packetSize != 0)
  {
    byte byteCode, mLength;

    // read packet
    while (LoRa.available())
    {
      byteCode = LoRa.read();
      mLength  = LoRa.read();

      if (byteCode == whoAmI_B)
      {
        offline.whoAmI = readMessages(mLength);
      }
      else if (byteCode == duckID_B)
      {
        offline.duckID = readMessages(mLength);
      }
      else if (byteCode == whereAmI_B)
      {
        offline.whereAmI = readMessages(mLength);
      }
      else if (byteCode == runTime_B)
      {
        offline.runTime = readMessages(mLength);
      }
      else if (byteCode == fromCiv_B)
      {
        offline.fromCiv = readMessages(mLength);
      }
      else if (byteCode == fname_B)
      {
        offline.fname = readMessages(mLength);
      }
      else if (byteCode == street_B)
      {
        offline.street = readMessages(mLength);
      }
      else if (byteCode == phone_B)
      {
        offline.phone = readMessages(mLength);
      }
      else if (byteCode == occupants_B)
      {
        offline.occupants = readMessages(mLength);
      }
      else if (byteCode == danger_B)
      {
        offline.danger = readMessages(mLength);
      }
      else if (byteCode == vacant_B)
      {
        offline.vacant = readMessages(mLength);
      }
      else if (byteCode == firstaid_B)
      {
        offline.firstaid = readMessages(mLength);
      }
      else if (byteCode == water_B)
      {
        offline.water = readMessages(mLength);
      }
      else if (byteCode == food_B)
      {
        offline.food = readMessages(mLength);
      }
      else if (byteCode == msg_B)
      {
        offline.msg = readMessages(mLength);
      }
    }
    showReceivedData();
    //jsonify(offline);
  }
  else
  {
    return;
  }
}

String readMessages(byte mLength)
{
  String incoming = "";

  for (int i = 0; i < mLength; i++)
  {
    incoming += (char)LoRa.read();
  }
  return incoming;
}

/**
   showReceivedstat
   Displays Received stat on OLED and Serial Monitor
*/
void showReceivedData()
{
  /**
     The total time it took for PAPA to create a packet,
     send it to MAMA. MAMA parsing victim requests, and
     send it back to PAPA.
  */
  String waiting = String(millis() - lastSendTime);

  Serial.println("Class: "        +  offline.whoAmI     );
  Serial.println("ID : "          +  offline.duckID    );
  Serial.println("Location: "     +  offline.whereAmI     );
  Serial.println("On for: "       +  offline.runTime + " milliseconds\n" );

  Serial.println("Name: "         +  offline.fname     );
  Serial.println("Street: "       +  offline.street    );
  Serial.println("Phone: "        +  offline.phone     );
  Serial.println("Occupants: "    +  offline.occupants );
  Serial.println("Dangers: "      +  offline.danger    );
  Serial.println("Vacant: "       +  offline.vacant    );
  Serial.println("First Aid: "    +  offline.firstaid  );
  Serial.println("Water: "        +  offline.water     );
  Serial.println("Food: "         +  offline.food      );
  Serial.println("Mess: "         +  offline.msg       );
  Serial.println("Time: "         +  waiting + " milliseconds\n");
}
