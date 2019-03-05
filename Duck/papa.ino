#ifdef PD

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#define SSID        "nick_owl" // Type your SSID
#define PASSWORD    "dd21643da814" // Type your Password

//#define MQTT_MAX_PACKET_SIZE 1000;

#define ORG         "zoad0c"                  // "quickstart" or use your organisation
#define DEVICE_ID   "puerto-rico-papa-duck"
#define DEVICE_TYPE "papa-duck"                // your device type or not used for "quickstart"
#define TOKEN       "rN52(-Ey_28mXmVHgR"      // your device token or not used for "quickstart"#define SSID        "nick_owl" // Type your SSID

char server[]           = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[]            = "iot-2/evt/status/fmt/json";
char authMethod[]       = "use-token-auth";
char token[]            = TOKEN;
char clientId[]         = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClientSecure wifiClient;
PubSubClient client(server, 8883, wifiClient);

int simulate = 0;

void setup()
{
  Serial.begin(115200);

  iAm = "Papa";
  setupDuck();

  pinMode(LED_BUILTIN, OUTPUT);

  setupDisplay();
  setupLoRa();
  setupPortal(); // Test

  setupWiFi();

  //delay(15000);

  Serial.println("PAPA Online");
  u8x8.drawString(0, 1, "PAPA Online");
}

/**
   setupWiFi
   Connects to local SSID
*/
void setupWiFi()
{
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(SSID);

  // Connect to Access Poink
  WiFi.begin(SSID, PASSWORD);
  u8x8.drawString(0, 1, "Connecting...");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Connected to Access Point
  Serial.println("");
  Serial.println("WiFi connected - PAPA ONLINE");
  u8x8.drawString(0, 1, "PAPA Online");
}

/**
   setupMQTT
   Sets Up MQTT
*/
void setupMQTT()
{
  if (!!!client.connected())
  {
    Serial.print("Reconnecting client to "); Serial.println(server);
    while ( ! (ORG == "quickstart" ? client.connect(clientId) : client.connect(clientId, authMethod, token)))
    {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
  }
}

void loop()
{
  setupMQTT();

  // Handles Captive Portal Requests
  dnsServer.processNextRequest();
  webServer.handleClient();

  // ⚠️ Parses Civilian Requests into Data Structure
  readData();
  if (offline.fromCiv == 1 && offline.phone != NULL && offline.phone != "")
  {
    jsonify(offline);
    Serial.print("Parsing Wifi Data");
    offline = empty;
    offline.fromCiv = 0;
  }

  receive(LoRa.parsePacket());
  if (offline.fromCiv == 0 && offline.phone != NULL && offline.phone != "")
  {
    jsonify(offline);
    u8x8.drawString(0, 4, "New Response");
    Serial.print("Parsing LoRa Data");
    offline = empty;
  }

  if(simulate == 1) {
    jsonSimulation();
  }

}

/**
   jsonify
   Serializes and Parses stat Struct Values into JSON
   @return JSON String
*/
void jsonify(Data offline)
{
  const int bufferSize = 2 * JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 3 * JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.createObject();

  JsonObject& bot = root.createNestedObject("bot");

  JsonObject& bot_info = bot.createNestedObject("info");
  bot_info["whoAmI"] = offline.whoAmI;
  bot_info["duckID"] = offline.duckID;
  bot_info["whereAmI"] = offline.whereAmI;
  bot_info["runTime"] = offline.runTime;

  JsonObject& civilian = root.createNestedObject("civilian");

  JsonObject& civilian_info   = civilian.createNestedObject("info");
  civilian_info["name"]       = offline.fname;
  civilian_info["phone"]      = offline.phone;
  civilian_info["location"]   = offline.street;
  civilian_info["occupants"]  = offline.occupants;

  JsonObject& civilian_status = civilian.createNestedObject("status");
  civilian_status["danger"]   = offline.danger;
  civilian_status["vacant"]   = offline.vacant ;

  JsonObject& civilian_need   = civilian.createNestedObject("needs");
  civilian_need["first-aid"]  = offline.firstaid;
  civilian_need["water"]      = offline.water;
  civilian_need["food"]       = offline.food;
  civilian["message"]         = offline.msg;

  String jsonstat;
  root.printTo(jsonstat);

  if (client.publish(topic, jsonstat.c_str()))
  {
    Serial.println("Publish ok");
    root.prettyPrintTo(Serial);
    Serial.println("");
  }
  else
  {
    Serial.println("Publish failed");
  }
}

void jsonSimulation()
{
  const int bufferSize = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 2 * JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(4000);

  JsonObject& root = jsonBuffer.createObject();

  JsonObject& civilian = root.createNestedObject("civilian");

  JsonObject& civilian_info   = civilian.createNestedObject("info");
  civilian_info["name"]       = "John Doe";
  civilian_info["phone"]      = random(1000000000, 9999999999);
  civilian_info["location"]   = "2725 E 14th St";
  civilian_info["occupants"]  = random(1, 10);

  int danger = random(0, 2);
  int vac    = 0;
  if (danger == 0)
  {
    vac++;
  }

  JsonObject& civilian_status = civilian.createNestedObject("status");
  civilian_status["danger"]   = danger;
  civilian_status["vacant"]   = vac;

  JsonObject& civilian_need   = civilian.createNestedObject("needs");
  civilian_need["first-aid"]  = random(0, 2);
  civilian_need["water"]      = random(0, 2);
  civilian_need["food"]       = random(0, 2);
  civilian["message"]         = "Please send help";

  String jsonData;
  root.printTo(jsonData);

  if (client.publish(topic, jsonData.c_str()))
  {
    Serial.println("Publish ok");
    root.prettyPrintTo(Serial);
    Serial.println("");
  }
  else
  {
    Serial.println("Publish failed");
  }

  delay(10000);
}

#endif
