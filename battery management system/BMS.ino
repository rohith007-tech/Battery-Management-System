#include <LiquidCrystal.h>
#include <DHT.h>

#define ANALOG_IN_PIN A2
#define CURRENT_SENSOR_PIN A3
#define DHTPIN A1
#define DHTTYPE DHT11

// Voltage Divider Constants
float R1 = 30000.0;
float R2 = 7500.0;
float ref_voltage = 5.0;
float Threshold_voltage = 7;

// Battery Specs
float battery_capacity_mAh = 15000.0; // 2200mAh
float SOC = 100.0; // Start fully charged

// Time tracking
unsigned long prevTime = 0;

// Current Sensor Calibration
float offset = 2.5; // Sensor offset at 0A (depends on sensor)
float sensitivity = 0.185; // For ACS712 5A = 185mV/A

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int relayChargingPin = 7;
const int relayLoadPin = 6;
const int tempThreshold = 37;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  pinMode(relayChargingPin, OUTPUT);
  pinMode(relayLoadPin, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  prevTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - prevTime) / 3600000.0; // in hours
  prevTime = currentTime;

  float temperature = dht.readTemperature();
  int adc_value = analogRead(ANALOG_IN_PIN);
  float adc_voltage = (adc_value * ref_voltage) / 1023.0;
  float voltage = (adc_voltage / (R2 / (R1 + R2))) - 0.3;

  // === SOC Estimation using Current Sensor ===
  int currentADC = analogRead(CURRENT_SENSOR_PIN);
  float currentVoltage = (currentADC * ref_voltage) / 1023.0;
  float current = (currentVoltage - offset) / sensitivity; // in Amps

  if (current < 0) current = 0; // Disallow negative current for safety

  float current_mA = current * 1000.0;
  float chargeUsed = current_mA * deltaTime; // mAh consumed
  SOC -= (chargeUsed / battery_capacity_mAh) * 100.0;

  if (SOC < 0) SOC = 0;
  if (SOC > 100) SOC = 100;

  Serial.print("Voltage: "); Serial.print(voltage, 2); Serial.println(" V");
  Serial.print("Temp: "); Serial.print(temperature); Serial.println(" C");
  Serial.print("Current: "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Battery percentage: "); Serial.print(SOC); Serial.println(" %");

  // === LCD Display ===
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("SOC:");
  lcd.print((int)SOC);
  lcd.print("% V:");
  lcd.print(voltage, 1);

  analogWrite(3, 0);
  analogWrite(5, 0);

  // === Control Logic ===
  if (temperature < tempThreshold && voltage < Threshold_voltage) {
    digitalWrite(relayChargingPin, LOW);
    digitalWrite(relayLoadPin, HIGH);
  }
  else if (temperature < tempThreshold && voltage >= Threshold_voltage) {
    digitalWrite(relayChargingPin, LOW);
    digitalWrite(relayLoadPin, LOW);
  }
  else if (temperature >= tempThreshold) {
    digitalWrite(relayChargingPin, LOW);
    digitalWrite(relayLoadPin, LOW);
    analogWrite(3, 3);
    analogWrite(5, 255);
  }

  delay(1000); // 1-second update cycle
}
