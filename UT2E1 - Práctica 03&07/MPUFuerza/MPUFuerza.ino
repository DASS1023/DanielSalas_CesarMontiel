#include <Wire.h>      // Librería para comunicación I2C
#include <MPU6050.h>   // Librería para manejar el sensor MPU6050

MPU6050 mpu;  // Crear objeto para manejar el sensor MPU6050

// Definimos la masa del objeto (peso aprox de una mini protoboard)
const float masa = 0.15;  // Masa en kg

// Constantes de aceleración
const float gravedad = 9.81;        // Aceleración de la gravedad en m/s²
const float sensibilidad = 16384.0; // MPU6050: 1g = 16384 unidades

void setup() {
  Serial.begin(9600);  // Iniciar comunicación serie a 9600 baudios
  Wire.begin();        // Iniciar comunicación I2C
  mpu.initialize();    // Inicializar el sensor MPU6050

  // Verificar si el sensor está conectado
  if (!mpu.testConnection()) {
    Serial.println("Error: MPU6050 no conectado");
    while (1);  // Si no hay conexión, detener el programa
  }
}

void loop() {
  int16_t ax, ay, az;  // Variables para almacenar la aceleración en bruto
  mpu.getAcceleration(&ax, &ay, &az);  // Leer aceleraciones del sensor

  // Convertimos la aceleración del eje X a m/s²
  float aceleracionX = (ax / sensibilidad) * gravedad;

  // Detectamos si hay un empuje significativo
  if (aceleracionX > 0.2) {  // Umbral mínimo para detectar empuje
    float distancia = calcularDistancia(aceleracionX);  // Calcular la distancia del empuje

    // Verificamos si la distancia está en el rango de 3 a 10 cm
    if (distancia >= 0.03 && distancia <= 0.10) {
      float fuerza = masa * aceleracionX;  // Segunda Ley de Newton: F = m * a

      // Imprimir la fuerza detectada en el monitor serie
      Serial.print("Fuerza aplicada: ");
      Serial.print(fuerza);
      Serial.println(" N");
    }
  }
  delay(100);  // Pequeño retraso antes de la siguiente lectura
}

// Función para calcular la distancia recorrida durante el empuje
float calcularDistancia(float aceleracion) {
  float tiempo = 0.2;  // Estimación de tiempo de contacto en segundos
  return 0.5 * aceleracion * tiempo * tiempo;  // Ecuación de movimiento: d = 0.5 * a * t^2
}
