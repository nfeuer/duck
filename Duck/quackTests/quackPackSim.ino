// If Quack is Defined in SetUp QuackPack will be Compiled with rest of MamaQuack
#ifdef QUACKPACK

// // Simple Boilerplate for 3rd Party Devs (QuackHackers)

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
  Serial.println(payload.deviceID);

  // Serial.print(" - Sensor Val: ");
  // Serial.println(payload.sensorVal);
  // couple(quack_B, String(payload.sensorVal));

  String quacket = payload.sensorVal + ",";

  couple(quacket_B, payload.deviceID);
  couple(quacket_B, String(random(999)));
  couple(quacket_B, quacket);

  Serial.println("\n==============\n");

  delay(10000);
}

#endif
