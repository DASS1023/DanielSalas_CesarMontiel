#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

// Parámetros del filtro EMA
float alpha = 0.25;  // Factor de suavizado (ajustable)
float filteredDistance = 0;  // Valor filtrado inicial

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!sensor.begin()) {
    Serial.println("Error: No se detecta VL53L0X");
    while (1);
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  
  sensor.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) { // 4 = Error
    float rawDistance = measure.RangeMilliMeter;

    // Aplicamos el filtro EMA
    filteredDistance = (alpha * rawDistance) + ((1 - alpha) * filteredDistance);

    Serial.print("Distancia sin filtrar: ");
    Serial.print(rawDistance);
    Serial.print(" mm | Distancia filtrada: ");
    Serial.print(filteredDistance);
    Serial.println(" mm");
  } else {
    Serial.println("Error en la medición");
  }

  delay(500);
}