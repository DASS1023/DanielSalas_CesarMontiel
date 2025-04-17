#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("No se detecta el sensor BMP180.");
    while (1);
  }

  Serial.println("Sensor BMP180 detectado.");
}

void loop() {
  float pressure = bmp.readPressure();       // Presión en Pa
  float temperature = bmp.readTemperature(); // Temperatura en °C

  // Convertir temperatura a Kelvin
  float temperatureK = temperature + 273.15;

  // Constante específica del aire seco
  const float R = 287.05;

  // Calcular densidad
  float density = pressure / (R * temperatureK);

  // Mostrar resultados
  Serial.print("Presión (Pa): ");
  Serial.print(pressure);
  Serial.print(" | Temperatura (C): ");
  Serial.print(temperature);
  Serial.print(" | Densidad del aire (kg/m3): ");
  Serial.println(density);

  delay(2000);
}




