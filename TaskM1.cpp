#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>

const int PIR_PIN = 9;
const int DHT_PIN = 4;
const int LED_PIN = 6;
const int LIGHT_ADDRESS = 0x23;

#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);

volatile bool pirChanged = false;

float temperature = 0;
float humidity = 0;
float light = 0;

unsigned long lastDhtRead = 0;
unsigned long lastLightRead = 0;
unsigned long lastStatus = 0;

// I use this when my PIR sensor changes.
void pirISR() {
  pirChanged = true;
}

void startLightSensor() {
  Wire.beginTransmission(LIGHT_ADDRESS);
  Wire.write(0x10);
  Wire.endTransmission();
}

void readLight() {
  Wire.requestFrom(LIGHT_ADDRESS, 2);

  if (Wire.available() == 2) {
    int raw = Wire.read() << 8 | Wire.read();
    light = raw / 1.2;
  }
}

void readDht() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  Wire.begin();
  dht.begin();

  startLightSensor();

  attachInterrupt(digitalPinToInterrupt(PIR_PIN), pirISR, CHANGE);

  Serial.println("System started");
}

void loop() {
  unsigned long now = millis();

  if (now - lastDhtRead >= 2000) {
    lastDhtRead = now;
    readDht();
  }

  if (now - lastLightRead >= 1000) {
    lastLightRead = now;
    readLight();
  }

  if (pirChanged) {
    noInterrupts();
    pirChanged = false;
    interrupts();

    Serial.println("PIR interrupt");
  }

  bool motion = digitalRead(PIR_PIN) == HIGH;
  bool dark = light < 30;
  bool hot = temperature > 28;
  bool ledOn = motion && (dark || hot);

  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);

  if (now - lastStatus >= 1000) {
    lastStatus = now;

    Serial.print("PIR: ");
    Serial.print(motion);

    Serial.print(" | Light: ");
    Serial.print(light);
    Serial.print(" lux");

    Serial.print(" | Temperature: ");
    Serial.print(temperature);
    Serial.print(" C");

    Serial.print(" | Humidity: ");
    Serial.print(humidity);
    Serial.print(" %");

    Serial.print(" | LED: ");
    Serial.println(ledOn ? "ON" : "OFF");
  }
}
