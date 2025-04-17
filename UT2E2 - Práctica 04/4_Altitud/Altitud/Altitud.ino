#include <Wire.h>                    // Incluye la librería para comunicación I2C
#include <Adafruit_BMP085.h>         // Incluye la librería para el sensor BMP085/BMP180

Adafruit_BMP085 bmp;                 // Crea un objeto llamado 'bmp' para controlar el sensor

unsigned long tiempoAnterior = 0;   // Guarda el tiempo (en milisegundos) de la última lectura
const unsigned long intervalo = 3000; // Intervalo de 3 segundos (3000 ms) entre lecturas

void setup() {
  Serial.begin(9600);                // Inicia la comunicación serial a 9600 baudios

  if (!bmp.begin()) {               // Intenta iniciar el sensor BMP180
    Serial.println("No se detecta el sensor BMP180."); // Mensaje si falla
    while (1);                      // Si falla, se detiene el programa en un bucle infinito
  }

  // Mensajes iniciales de bienvenida al usuario
  Serial.println("Inicio de lectura de altitud (BMP180)");
  Serial.println("Coloca el sensor en distintas ubicaciones y observa la altitud...");
  Serial.println("---------------------------------------------------");
}

void loop() {
  unsigned long tiempoActual = millis(); // Obtiene el tiempo actual en milisegundos desde que inició el programa

  // Verifica si ya pasaron 3 segundos desde la última lectura
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual; // Actualiza el tiempo de la última lectura

    float altitud = bmp.readAltitude();            // Calcula la altitud estimada en metros (usa 1013.25 hPa como presión al nivel del mar por defecto)
    float presion = bmp.readPressure() / 100.0;    // Lee la presión atmosférica (dividido entre 100 para convertir de Pa a hPa)
    float temperatura = bmp.readTemperature();     // Lee la temperatura en grados Celsius

    // Muestra los valores leídos en el monitor serial
    Serial.print("Altitud estimada: ");
    Serial.print(altitud);
    Serial.print(" m | Presión: ");
    Serial.print(presion);
    Serial.print(" hPa | Temp: ");
    Serial.print(temperatura);
    Serial.println(" °C");
  }
}