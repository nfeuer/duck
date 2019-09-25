// If Quack is Defined in SetUp QuackPack will be Compiled with rest of MamaQuack
#ifdef QUACKPACK

int QuackPack = 1;

// // Simple Boilerplate for 3rd Party Devs (QuackHackers)
// #define QUACKPACK


void setupQuack()
{
    int     dustPin     = 0;
    float   dustVal     = 0; 
    int     ledPower    = 2;
    int     delayTime   = 280;
    int     delayTime2  = 40;
    float   offTime     = 9680;
    
    Serial.begin(9600);
    pinMode(ledPower,OUTPUT);
    pinMode(dustPin, INPUT);
}

void loopQuack()
{
    // ledPower is any digital pin on the arduino connected to Pin 2 on the sensor
    digitalWrite(ledPower,LOW); 
    delayMicroseconds(delayTime);
    dustVal = analogRead(dustPin); 
    delayMicroseconds(delayTime2);
    digitalWrite(ledPower,HIGH); 
    delayMicroseconds(offTime);
    
    delay(1000);
    if (dustVal>36.455)
    {
        Serial.println((float(dustVal/1024)-0.0356)*120000*0.035);
    }
}

int numPayloads = 1;

void QuackPayload()
{
  couple(quack_B, dustVal);
}

#endif

