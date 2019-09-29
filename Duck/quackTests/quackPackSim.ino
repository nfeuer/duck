// If Quack is Defined in SetUp QuackPack will be Compiled with rest of MamaQuack
#ifdef QUACKPACK

// // Simple Boilerplate for 3rd Party Devs (QuackHackers)

#ifdef PAYLOADSIZE
#undef PAYLOADSIZE
#define PAYLOADSIZE 2//redefine it with the new value
#endif

typedef struct
{
  String deviceID;
  int    sensorVal;
} Quack;
Quack payload;

void setupQuack()
{
  QuackPack = true;

  payload.deviceID  = "20seven";
  payload.sensorVal = 0;

  Serial.begin(115200);
  Serial.print("setupQuack()");
  Serial.println(" - Sensor Val: " + payload.deviceID);

  Serial.println("\n==============\n");
}

void loopQuack()
{
  Serial.println("loopQuack()");

  payload.sensorVal += 5;

  Serial.print(" - Sensor Val: ");
  Serial.println(payload.sensorVal);

  Serial.println("\n==============\n");
}

void QuackPayload()
{
  Serial.println("QuackPayload()");

  Serial.print(" - Payload ID: ");
  // Serial.println(payload.deviceID);
  couple(quack_B, payload.deviceID);

  // Serial.print(" - Sensor Val: ");
  // Serial.println(payload.sensorVal);
  // couple(quack_B, String(payload.sensorVal));
  long randNumber = random(300);

  couple(quack_B, String(payload.sensorVal));

  Serial.println("\n==============\n");

  delay(10000);
}

#endif
