#include <MPU6050.h>
#include <Wire.h>

const int MPU_ADDR = 0x68; // Dirección I2C del MPU6050
char pitch[5], roll[5];  // Arreglos de caracteres para almacenar los valores formateados

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
  int int_pitch = (int)(atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI);
  int int_roll = (int)(atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI);

  // Normalizar valores de -180 a 180 → 0 a 1023
  int norm_pitch = map(int_pitch, -180, 180, 0, 1023);
  int norm_roll = map(int_roll, -180, 180, 0, 1023);

  // Convertir enteros a char con formato de 4 dígitos
  sprintf(pitch, "%04d", norm_pitch);
  sprintf(roll, "%04d", norm_roll);

  // Mostrar solo los datos en el formato requerido
  Serial.print("<");
  Serial.print(pitch);
  Serial.print(",");
  Serial.print(roll);
  Serial.print(">");

  delay(300);  // Retardo principal antes de la siguiente lectura
  delay(100);  // Retardo adicional después de imprimir en el monitor serie
}

