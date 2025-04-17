#include <Wire.h>
#include <Adafruit_BMP085.h> // Compatible también con BMP180

Adafruit_BMP085 bmp;

const float v = 4.0;       // Velocidad del viento promedio en m/s
const float r = 1.0;       // Radio de la columna de aire en metros
const float A = PI * r * r; // Área transversal

void setup() {
  Serial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("No se detecta el sensor BMP180");
    while (1);
  }

  Serial.println("Iniciando cálculo de energía eólica...");
}

void loop() {
  // Leer temperatura en °C y presión en Pa
  float temperature = bmp.readTemperature(); // °C
  float pressure = bmp.readPressure();       // Pa

  // Calcular densidad del aire (ρ) en kg/m³ usando la ecuación de estado del gas ideal
  float R = 287.05; // Constante del gas para el aire seco (J/kg·K)
  float T_kelvin = temperature + 273.15; // Convertir a Kelvin
  float rho = pressure / (R * T_kelvin); // Densidad

  // Calcular potencia eólica (W)
  float P = 0.5 * rho * A * pow(v, 3);

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Presion: ");
  Serial.print(pressure / 100);
  Serial.println(" hPa");

  Serial.print("Densidad del aire: ");
  Serial.print(rho);
  Serial.println(" kg/m³");

  Serial.print("Potencia eólica disponible: ");
  Serial.print(P);
  Serial.println(" W");

  delay(5000);
}

