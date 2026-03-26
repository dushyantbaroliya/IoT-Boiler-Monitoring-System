#include <WiFi.h>
#include <ThingSpeak.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ========== WiFi Credentials ==========
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ========== ThingSpeak ==========
unsigned long channelID = YOUR_CHANNEL_ID;
const char* writeAPIKey = "YOUR_WRITE_API_KEY";
WiFiClient client;

// ========== Pins ==========
#define ONE_WIRE_BUS 4   // DS18B20
#define BUZZER 26
#define LED 25

// ADC Pins for Pressure Sensors
#define PRESSURE1 34
#define PRESSURE2 35
#define PRESSURE3 32

// ========== OneWire Setup ==========
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ========== Variables ==========
float temperature[3];
float pressure[3];

// ========== Setup ==========
void setup() {
  Serial.begin(115200);

  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  sensors.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  ThingSpeak.begin(client);
}

// ========== Convert ADC to Pressure ==========
float readPressure(int pin) {
  int adcValue = analogRead(pin);

  float voltage = adcValue * (3.3 / 4095.0);  
  // ESP32 ADC range

  // 1–5V corresponds to 0–10 bar (example calibration)
  float pressureBar = (voltage - 1.0) * (10.0 / 4.0);

  if (pressureBar < 0) pressureBar = 0;

  return pressureBar;
}

// ========== Loop ==========
void loop() {

  // ---- Read Temperature ----
  sensors.requestTemperatures();

  for (int i = 0; i < 3; i++) {
    temperature[i] = sensors.getTempCByIndex(i);
  }

  // ---- Read Pressure ----
  pressure[0] = readPressure(PRESSURE1);
  pressure[1] = readPressure(PRESSURE2);
  pressure[2] = readPressure(PRESSURE3);

  // ---- Print Data ----
  Serial.println("---- DATA ----");

  for (int i = 0; i < 3; i++) {
    Serial.print("Vessel ");
    Serial.print(i + 1);
    Serial.print(" | Temp: ");
    Serial.print(temperature[i]);
    Serial.print(" °C | Pressure: ");
    Serial.print(pressure[i]);
    Serial.println(" bar");
  }

  // ---- Check Pressure Threshold ----
  bool alert = false;

  for (int i = 0; i < 3; i++) {
    if (pressure[i] > 3.5) {
      alert = true;
    }
  }

  if (alert) {
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);
    Serial.println("⚠️ ALERT: High Pressure!");
  } else {
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);
  }

  // ---- Send to ThingSpeak ----
  ThingSpeak.setField(1, temperature[0]);
  ThingSpeak.setField(2, pressure[0]);
  ThingSpeak.setField(3, temperature[1]);
  ThingSpeak.setField(4, pressure[1]);
  ThingSpeak.setField(5, temperature[2]);
  ThingSpeak.setField(6, pressure[2]);

  int status = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (status == 200) {
    Serial.println("Data sent to ThingSpeak ✅");
  } else {
    Serial.println("Error sending data ❌");
  }

  delay(5000); // 5 seconds
}