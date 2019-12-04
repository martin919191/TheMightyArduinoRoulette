#include <Arduino.h>

void rollLights();
void blinkLights();
void modeRolling();
void rollLights(int delay);

void setup()
{
  //pinMode(11, OUTPUT);
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
  for (int i = 2; i < 8; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  if (!digitalRead(10))
  {
    Serial.println("Read 10 - 1");
    modeRolling();
  }
  //Serial.println("Here comes the loop");
  blinkLights();
}

unsigned long previousMillisRoll = 0;
int currentLed = 7;
void rollLights()
{
  unsigned long currentMillisRoll = millis();
  if (currentMillisRoll - 50 >= previousMillisRoll)
  {
    digitalWrite(currentLed, LOW);
    currentLed--;
    if (currentLed == 1)
      currentLed = 7;
    digitalWrite(currentLed, HIGH);
    previousMillisRoll = currentMillisRoll;
  }
}

void rollLights(int delay)
{
  unsigned long currentMillisRoll = millis();
  if (currentMillisRoll - delay >= previousMillisRoll)
  {
    digitalWrite(currentLed, LOW);
    currentLed--;
    if (currentLed == 1)
      currentLed = 7;
    digitalWrite(currentLed, HIGH);
    previousMillisRoll = currentMillisRoll;
  }
}

bool currentStatus = true;
void blinkLights()
{
  unsigned long currentMillisRoll = millis();
  //Serial.println(currentMillisRoll);
  if (currentMillisRoll - previousMillisRoll >= 1000)
  {
    if (currentStatus)
    {
      for (int i = 2; i < 8; i++)
      {
        digitalWrite(i, HIGH);
      }
    }
    else
    {
      for (int i = 2; i < 8; i++)
      {
        digitalWrite(i, LOW);
      }
    }
    currentStatus = !currentStatus;
    previousMillisRoll = currentMillisRoll;
  }
}

void modeRolling()
{
  randomSeed(analogRead(0));
  for (int i = 0; i < 255; i++)
  {
    analogWrite(11, i);
    rollLights(270-i);
    delay(5);
  }
  unsigned int randTime = random(1000, 2000);
  unsigned long initialMillis = millis();
  while (millis() - initialMillis < randTime)
  {
    rollLights(25);
  }
  while (!digitalRead(10))
    rollLights(25);

  for (int i = 255; i > 0; i--)
  {
    analogWrite(11, i);
    rollLights(280-i);
    delay(20);
  }
}