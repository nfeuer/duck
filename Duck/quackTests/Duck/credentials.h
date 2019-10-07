// Please do not commit credentials to public GH

#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

#define SSID        "La Vista Smoke House" // Type your SSID
#define PASSWORD    "Matthew1" // Type your Password
//
//#define SSID    "Hayley"
//#define PASSWORD "0t8ylihhrxye"



//#define MQTT_MAX_PACKET_SIZE 1000;

#define ORG         "9c6nfo"                  // "quickstart" or use your organisation
#define DEVICE_ID   "Villa_de_BBQ"
#define DEVICE_TYPE "PAPA"                // your device type or not used for "quickstart"
#define TOKEN       "gKjmrEE+TcgTa9WV&a"      // your device token or not used for "quickstart"#define SSID        "nick_owl" // Type your SSID

char server[]           = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[]            = "iot-2/evt/status/fmt/json";
char authMethod[]       = "use-token-auth";
char token[]            = TOKEN;
char clientId[]         = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

#endif
