#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

float presionBase = 0;
unsigned long tiempoAnterior = 0;
int conteoVehiculos = 0;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("No se detecta BMP180");
    while (1);
  }

  // Medir presión base
  presionBase = bmp.readPressure();
  Serial.print("Presión base: ");
  Serial.println(presionBase);
}

void loop() {
  float presionActual = bmp.readPressure();
  float delta = presionBase - presionActual;

  // Detectar cambio brusco (evento)
  if (abs(delta) > 20) { // Puedes ajustar este umbral
    unsigned long tInicio = millis();

    // Esperar a que el vehículo pase completamente
    while (abs(bmp.readPressure() - presionBase) > 10) {
      delay(10);
    }

    unsigned long tFin = millis();
    unsigned long duracion = tFin - tInicio;

    conteoVehiculos++;
    Serial.print("Vehículo ");
    Serial.print(conteoVehiculos);
    Serial.print(" detectado. Duración: ");
    Serial.print(duracion);
    Serial.print(" ms | ΔP: ");
    Serial.println(delta);

    // Clasificación básica por duración o delta de presión
    if (duracion < 500 && abs(delta) < 50) {
      Serial.println("→ Vehículo ligero (moto o bici)");
    } else if (duracion < 1500) {
      Serial.println("→ Vehículo medio (auto)");
    } else {
      Serial.println("→ Vehículo pesado (camión)");
    }

    delay(1000); // Tiempo para evitar múltiples conteos por el mismo vehículo
  }

  delay(100);
}
