#include <Wire.h>

const int MPU_ADDR = 0x68; // Dirección I2C del MPU6050
int pitch, roll;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Activar el MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();
}

void loop() {
  // Leer datos del acelerómetro
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  
  int16_t accel_x = Wire.read() << 8 | Wire.read();
  int16_t accel_y = Wire.read() << 8 | Wire.read();
  int16_t accel_z = Wire.read() << 8 | Wire.read();

  // Convertir a valores en "g"
  float ax = accel_x / 16384.0;
  float ay = accel_y / 16384.0;
  float az = accel_z / 16384.0;

  // Calcular pitch y roll (grados)
  pitch = (int)(atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI);
  roll = (int)(atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI);

  // Normalizar valores de -180 a 180 → 0 a 1023
  int norm_pitch = map(pitch, -180, 180, 0, 1023);
  int norm_roll = map(roll, -180, 180, 0, 1023);

  // Formatear los valores con 4 dígitos
  char pitchStr[6], rollStr[6];
  sprintf(pitchStr, "%04d", norm_pitch);
  sprintf(rollStr, "%04d", norm_roll);

  // Determinar la posición del sensor
  String position = "Base";

  if (pitch > 30) {
    position = "Arriba";
  } else if (pitch < -30) {
    position = "Abajo";
  } else if (roll > 30) {
    position = "Derecha";
  } else if (roll < -30) {
    position = "Izquierda";
  }

  // Mostrar resultados en formato normalizado
  Serial.print("Pitch: ");
  Serial.print(pitchStr);
  Serial.print(" | Roll: ");
  Serial.print(rollStr);
  Serial.print(" | Posición: ");
  Serial.println(position);

  delay(500);
}

