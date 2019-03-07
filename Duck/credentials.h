// Please do not commit credentials to public GH

#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

#define SSID        "" // Type your SSID
#define PASSWORD    "" // Type your Password

#define ORG         "" // "quickstart" or use your organisation
#define DEVICE_ID   ""
#define DEVICE_TYPE "" // your device type or not used for "quickstart"
#define TOKEN       "" // your device token or not used for "quickstart"

//-------- Customise the above values --------

char server[]           = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[]            = "iot-2/evt/status/fmt/json";
char authMethod[]       = "use-token-auth";
char token[]            = TOKEN;
char clientId[]         = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

#endif
