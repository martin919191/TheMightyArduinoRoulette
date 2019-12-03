#include <Arduino.h>

void rollLights();
void blinkLights();
void modeRolling();

void setup()
{
  //pinMode(11, OUTPUT);
  //pinMode(2, INPUT_PULLUP);
  for (int i = 2; i < 8; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  if (digitalRead(10))
    modeRolling();

  blinkLights();
}

unsigned long previousMillisRoll = 0;
int currentLed = 2;
void rollLights()
{
  unsigned long currentMillisRoll = millis();
  if (currentMillisRoll - 250 >= previousMillisRoll)
  {
    digitalWrite(currentLed, LOW);
    currentLed++;
    if (currentLed == 8)
      currentLed = 2;
    digitalWrite(currentLed, HIGH);
  }
  previousMillisRoll = currentMillisRoll;
}

bool currentStatus = true;
void blinkLights()
{
  unsigned long currentMillisRoll = millis();
  if (currentMillisRoll - 250 >= previousMillisRoll)
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
  }
  previousMillisRoll = currentMillisRoll;
}

void modeRolling()
{
  randomSeed(analogRead(0));
  for (int i = 0; i < 255; i++)
  {
    analogWrite(11, i);
    blinkLights();
    delay(5);
  }
  int randTime = random(1000, 2000);
  unsigned long initialMillis = millis();
  while (millis() - initialMillis < randTime)
  {
    blinkLights();
  }
  while (digitalRead(10))
    blinkLights();

  for (int i = 255; i > 0; i--)
  {
    analogWrite(11, i);
    blinkLights();
    delay(30);
  }
}