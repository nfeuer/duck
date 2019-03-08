// Please do not commit credentials to public GH

#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

//#define SSID        "Engine-4 IoT Lab" // Type your SSID
//#define PASSWORD    "playground4" // Type your Password
#define SSID        "ARRIS-2C52" // Type your SSID
#define PASSWORD    "34E4A7ED7AA43FAA" // Type your Password

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

#endif
