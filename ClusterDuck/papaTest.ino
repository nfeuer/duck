// Copyright 2018 Bryan Knouse, Magus Pereira, Charlie Evans, Taraqur Rahman, Nick Feuer
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifdef PAPAT

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#define SSID        "nick_owl" // Type your SSID
#define PASSWORD    "dd21643da814" // Type your Password

//#define MQTT_MAX_PACKET_SIZE 1000;

#define ORG         "spzzrw"                  // "quickstart" or use your organisation
#define DEVICE_ID   "PAPA_THINK"
#define DEVICE_TYPE "PAPA"                // your device type or not used for "quickstart"
#define TOKEN       "RhqO+(QOilS_d1YqnZ"      // your device token or not used for "quickstart"#define SSID        "nick_owl" // Type your SSID

//-------- Customise the above values --------

char server[]           = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[]            = "iot-2/evt/status/fmt/json";
char authMethod[]       = "use-token-auth";
char token[]            = TOKEN;
char clientId[]         = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClientSecure wifiClient;
PubSubClient client(server, 8883, wifiClient);

long lastSendTime = 0;

Data data;

// Simulate MQTT
int simulate = 1;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  setupDisplay();
  setupLoRa();
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
  //    WiFi.begin(SSID);
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

  if (simulate != 1)
  {
    receive(LoRa.parsePacket());
    jsonify(data);
  }
  else
  {
    jsonSimulation();
  }
}

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

      if (byteCode == fname_B)
      {
        data.fname = readMessages(mLength);
      }
      else if (byteCode == street_B)
      {
        data.street = readMessages(mLength);
      }
      else if (byteCode == phone_B)
      {
        data.phone = readMessages(mLength);
      }
      else if (byteCode == occupants_B)
      {
        data.occupants = readMessages(mLength);
      }
      else if (byteCode == danger_B)
      {
        data.danger = readMessages(mLength);
      }
      else if (byteCode == vacant_B)
      {
        data.vacant = readMessages(mLength);
      }
      else if (byteCode == firstaid_B)
      {
        data.firstaid = readMessages(mLength);
      }
      else if (byteCode == water_B)
      {
        data.water = readMessages(mLength);
      }
      else if (byteCode == food_B)
      {
        data.food = readMessages(mLength);
      }
      else if (byteCode == msg_B)
      {
        data.msg = readMessages(mLength);
      }
    }
        showReceivedData();
    //    jsonify(data);
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
   showReceivedData
   Displays Received Data on OLED and Serial Monitor
*/
void showReceivedData()
{
  /**
     The total time it took for PAPA to create a packet,
     send it to MAMA. MAMA parsing victim requests, and
     send it back to PAPA.
  */
  String waiting = String(millis() - lastSendTime);

    u8x8.clear();
    u8x8.drawString(0, 0, (data.fname).c_str());
    u8x8.setCursor(0, 16);  u8x8.print("Phone: "   + data.phone);
    u8x8.setCursor(0, 32);  u8x8.print("Message: "   + data.msg);
    u8x8.setCursor(0, 48);  u8x8.print(waiting);


    Serial.println("Name: "         +  data.fname     );
    Serial.println("Street: "       +  data.street    );
    Serial.println("Phone: "        +  data.phone     );
    Serial.println("Occupants: "    +  data.occupants );
    Serial.println("Dangers: "      +  data.danger    );
    Serial.println("Vacant: "       +  data.vacant    );
    Serial.println("First Aid: "    +  data.firstaid  );
    Serial.println("Water: "        +  data.water     );
    Serial.println("Food: "         +  data.food      );
    Serial.println("Mess: "         +  data.msg       );
    Serial.println("Time: "         +  waiting        );
}

/**
   jsonify
   Serializes and Parses Data Struct Values into JSON
   @return JSON String
*/
void jsonify(Data data)
{
  const int capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 2 * JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(capacity);

  JsonObject& root = jsonBuffer.createObject();

  JsonObject& civilian = root.createNestedObject("civilian");

  JsonObject& civilian_info   = civilian.createNestedObject("info");
  civilian_info["name"]       = data.fname;
  civilian_info["phone"]      = data.phone;
  civilian_info["location"]   = data.street;
  civilian_info["occupants"]  = data.occupants;

  JsonObject& civilian_status = civilian.createNestedObject("status");
  civilian_status["danger"]   = data.danger;
  civilian_status["vacant"]   = data.vacant ;

  JsonObject& civilian_need   = civilian.createNestedObject("needs");
  civilian_need["first-aid"]  = data.firstaid;
  civilian_need["water"]      = data.water;
  civilian_need["food"]       = data.food;
  civilian["message"]         = data.msg;

  String jsonData;
  root.printTo(jsonData);

//  if (client.publish(topic, jsonData.c_str()))
//  {
//    Serial.println("Publish ok");
//    root.prettyPrintTo(Serial);
//    Serial.println("");
//  }
//  else
//  {
//    Serial.println("Publish failed");
//  }
}

// Simulating Sending JSON Data to IoT Platform


//int count = 1;
void jsonSimulation()
{
  const int capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 2 * JSON_OBJECT_SIZE(4);
  DynamicJsonBuffer jsonBuffer(capacity);

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
  root.prettyPrintTo(Serial);

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
