#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP085.h>

// Sensores
Adafruit_AHTX0 aht;
Adafruit_BMP085 bmp; // compatible con BMP180

const int lm35Pin = A0;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Wire.begin();

  // Inicializar AHT20
  if (!aht.begin()) {
    Serial.println("¡No se detectó el sensor AHT20!");
    while (1);
  }

  // Inicializar BMP180
  if (!bmp.begin()) {
    Serial.println("¡No se detectó el sensor BMP180!");
    while (1);
  }

  Serial.println("Sistema de monitoreo de humedad y temperatura iniciado.");
}

void loop() {
  sensors_event_t tempAHT, humidity;
  aht.getEvent(&humidity, &tempAHT);

  float humedad = humidity.relative_humidity;
  float temp_aht20 = tempAHT.temperature;

  float temp_bmp = bmp.readTemperature(); // en °C

  int lecturaLM35 = analogRead(lm35Pin);
  float voltaje = lecturaLM35 * (5.0 / 1023.0);
  float temp_lm35 = voltaje * 100.0;

  // Mostrar datos
  Serial.print("Temp AHT20: ");
  Serial.print(temp_aht20);
  Serial.print(" °C | HR: ");
  Serial.print(humedad);
  Serial.print(" % | Temp BMP180: ");
  Serial.print(temp_bmp);
  Serial.print(" °C | Temp LM35: ");
  Serial.print(temp_lm35);
  Serial.println(" °C");

  // Verificar si HR llega a 100%
  if (humedad >= 99.0) {
    Serial.println("¡Humedad máxima alcanzada (≈100%)!");
    while (1); // detener el sistema
  }

  delay(2000); // Espera antes de siguiente lectura
}
