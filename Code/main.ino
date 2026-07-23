 Arduino code: 
#define TDS_PIN A0  // TDS signal connected to analog pin A0

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("TDS Sensor Test - Arduino Uno");
}

void loop() {
  int analogValue = analogRead(TDS_PIN);  // 10-bit ADC (0–1023)
  float voltage = analogValue * (5.0 / 1023.0);  // Convert to voltage (based on 5V ref)

  // Estimate TDS in ppm using empirical formula (DFRobot reference)
  float tdsValue = (133.42 * voltage * voltage * voltage
                  - 255.86 * voltage * voltage
                  + 857.39 * voltage) * 0.5;

  // Output to Serial Monitor
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | TDS: ");
  Serial.print(tdsValue, 1);
  Serial.println(" ppm");

  delay(2000);  // Delay before next reading
}


esp32 code: 
#define TDS_PIN 18  // GPIO pin connected directly to TDS signal output

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // Use full 12-bit ADC resolution (0–4095)
  delay(1000);
  Serial.println("TDS Sensor (5V Power, No Voltage Divider)");
}

void loop() {
  int analogValue = analogRead(TDS_PIN);
  float voltage = analogValue * (3.3 / 4095.0);  // ESP32 ADC uses 3.3V reference

  // Estimate TDS in ppm (rough formula based on voltage)
  float tdsValue = (133.42 * voltage * voltage * voltage
                  - 255.86 * voltage * voltage
                  + 857.39 * voltage) * 0.5;

  // Print the result
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | TDS: ");
  Serial.print(tdsValue, 1);
  Serial.println(" ppm");

  delay(2000);
}
