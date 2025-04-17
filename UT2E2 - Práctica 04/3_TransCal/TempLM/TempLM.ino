#include <Wire.h>
#include <Adafruit_BMP085.h>  // Librería para BMP180

Adafruit_BMP085 bmp;

const int lm35Pin = A0; // Pin analógico donde está conectado el LM35

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!bmp.begin()) {
    Serial.println("No se encontró el sensor BMP180.");
    while (1);
  }

  Serial.println("Tiempo (s), Temp_BMP180 (°C), Temp_LM35 (°C)");
}

void loop() {
  static unsigned long startTime = millis();
  float tempBMP = bmp.readTemperature(); // Lee temperatura del BMP180
  int adcValue = analogRead(lm35Pin); // Lee voltaje del LM35
  float voltage = adcValue * (5.0 / 1023.0);
  float tempLM35 = voltage * 100.0; // Conversión a grados C

  unsigned long elapsed = (millis() - startTime) / 1000;

  Serial.print(elapsed);
  Serial.print(", ");
  Serial.print(tempBMP, 2);
  Serial.print(", ");
  Serial.println(tempLM35, 2);

  delay(1000); // Cada segundo
}



