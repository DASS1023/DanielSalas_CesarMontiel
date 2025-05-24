// Definimos el pin donde está conectado el sensor MQ-2
int mq2Pin = A0;

// Definimos un umbral para diferenciar entre reposo y actividad
// Este valor deberás ajustarlo tú experimentalmente con pruebas reales
int umbralActividad = 450;

void setup() {
  // Inicia la comunicación serial a 9600 baudios
  Serial.begin(9600);
}

void loop() {
  // Leemos el valor analógico del sensor MQ-2
  int lectura = analogRead(mq2Pin);

  // Mostramos el valor de la lectura
  Serial.print("Valor MQ-2: ");
  Serial.print(lectura);

  // Evaluamos si el valor indica reposo o actividad
  if (lectura < umbralActividad) {
    Serial.println(" --> Estado: REPOSO");
  } else {
    Serial.println(" --> Estado: ACTIVIDAD");
  }

  // Esperamos medio segundo antes de tomar la siguiente lectura
  delay(500);
}
