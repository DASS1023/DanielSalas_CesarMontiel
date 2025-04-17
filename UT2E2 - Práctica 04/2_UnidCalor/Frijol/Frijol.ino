#include <Wire.h>                    // Incluye la librería para comunicación I2C
#include <Adafruit_BMP085.h>         // Incluye la librería para controlar el sensor BMP085/BMP180

Adafruit_BMP085 bmp;                 // Crea un objeto llamado 'bmp' para acceder al sensor BMP180

float TB = 10.0;                     // Temperatura base o umbral para calcular Unidades Calor (UC)
float uc = 0;                        // UC acumuladas a lo largo de los días
float tMax = -1000;                 // Inicializa la temperatura máxima muy baja para poder actualizarla correctamente
float tMin = 1000;                  // Inicializa la temperatura mínima muy alta para poder actualizarla correctamente

unsigned long tiempoAnterior = 0;    // Guarda el tiempo (en milisegundos) de la última lectura
const unsigned long intervaloLectura = 60000; // Intervalo entre lecturas: 60,000 ms = 1 minuto

int lecturasPorDia = 1440;           // Número de lecturas por día (1 lectura por minuto durante 24 horas)
int contadorLecturas = 0;            // Contador de cuántas lecturas se han hecho en el día

int diasSimulados = 0;               // Contador de cuántos días simulados han pasado
String etapa = "";                   // Variable para guardar el nombre de la etapa fenológica actual

void setup() {
  Serial.begin(9600);                // Inicia la comunicación serial a 9600 baudios

  if (!bmp.begin()) {                // Verifica si el sensor BMP180 está conectado correctamente
    Serial.println("No se detecta el sensor BMP180.");
    while (1);                       // Si no se detecta, detiene el programa
  }

  // Mensajes iniciales al monitor serial
  Serial.println("== Sistema Fenológico - Frijol ==");
  Serial.println("Modo: Día fenológico");
}

void loop() {
  unsigned long tiempoActual = millis(); // Obtiene el tiempo actual en milisegundos desde que inició el programa

  // Verifica si ha pasado el tiempo suficiente desde la última lectura
  if (tiempoActual - tiempoAnterior >= intervaloLectura) {
    tiempoAnterior = tiempoActual;       // Actualiza el tiempo de la última lectura

    float temp = bmp.readTemperature();  // Lee la temperatura actual del sensor BMP180

    // Actualiza la temperatura máxima si la lectura actual es mayor
    if (temp > tMax) tMax = temp;

    // Actualiza la temperatura mínima si la lectura actual es menor
    if (temp < tMin) tMin = temp;

    contadorLecturas++;                  // Aumenta el contador de lecturas del día

    // Si ya se han hecho todas las lecturas del día (1440), se considera que ha pasado un día completo
    if (contadorLecturas >= lecturasPorDia) {
      diasSimulados++;                   // Aumenta el contador de días simulados

      // Calcula las Unidades Calor del día con la fórmula: UC = (Tmax + Tmin)/2 - TB
      float ucDia = ((tMax + tMin) / 2.0) - TB;
      if (ucDia < 0) ucDia = 0;          // Si UC diaria es menor que cero, se considera como cero

      uc += ucDia;                       // Acumula la UC diaria al total

      // Determina la etapa fenológica según la UC acumulada
      if (uc < 12.89) etapa = "Antes de Emergencia";
      else if (uc < 64.41) etapa = "Emergencia";
      else if (uc < 91.33) etapa = "Formación de Guías";
      else if (uc < 99.31) etapa = "Floración";
      else if (uc < 112.77) etapa = "Formación de Vaina";
      else if (uc < 153.24) etapa = "Llenado de Vainas";
      else etapa = "Maduración";

      // Muestra los resultados del día en el monitor serial
      Serial.println("=====================================");
      Serial.print("Día real registrado: "); Serial.println(diasSimulados);
      Serial.print("T. Máxima: "); Serial.print(tMax); Serial.println(" °C");
      Serial.print("T. Mínima: "); Serial.print(tMin); Serial.println(" °C");
      Serial.print("UC diaria: "); Serial.println(ucDia);
      Serial.print("UC acumulada: "); Serial.println(uc);
      Serial.print("Etapa fenológica: "); Serial.println(etapa);
      Serial.println("=====================================");

      // Reinicia variables para el siguiente día
      contadorLecturas = 0;              // Reinicia el contador de lecturas
      tMax = -1000;                      // Reinicia la temperatura máxima
      tMin = 1000;                       // Reinicia la temperatura mínima
    }
  }
}