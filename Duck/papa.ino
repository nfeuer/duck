#ifdef PD

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

WiFiClientSecure wifiClient;
PubSubClient client(server, 8883, wifiClient);

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
  // ⚠️ Parses Civilian Requests into Data Structure
  readData();
  if (!offline.fromCiv && offline.fromCiv == "yes" && !offline.fname)
  {
    jsonify(offline);
    Serial.print("Parsing Wifi Data");
  }

  receive(LoRa.parsePacket());
  if (!offline.fromCiv && offline.fromCiv == "yes")
  {
    jsonify(offline);
    duckData(offline);
    Serial.print("Parsing LoRa Data");
  }

}

/**
jsonify
Serializes and Parses stat Struct Values into JSON
@return JSON String
*/
void jsonify(Data offline)
{
  const int bufferSize = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 2 * JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(bufferSize);

  JsonObject& root = jsonBuffer.createObject();

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
  publishData(jsonstat);
}

void duckData(Data offline)
{
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(capacity);

  JsonObject& root = jsonBuffer.createObject();

  JsonArray& Duck_Data = root.createNestedArray("Duck Data");

  JsonObject& Duck_Stat     = Duck_Data.createNestedObject();
  Duck_Stat["Class"]        = offline.whoAmI;
  Duck_Stat["Duck ID"]      = offline.duckID;
  Duck_Stat["Time on"]      = offline.runTime;
  Duck_Stat["Coordinates"]  = offline.whereAmI;

  String jsonstat;
  root.printTo(jsonstat);
  publishData(jsonstat);
}

void publishData(String data)
{
  if (client.publish(topic, data.c_str()))
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

#endif
