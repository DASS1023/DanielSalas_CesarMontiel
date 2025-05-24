const int mq2Pin = A0;               // Pin analógico del sensor MQ-2
const int umbralAlcohol = 350;       // Umbral para detección de alcohol (ajustar según pruebas)

void setup() {
  Serial.begin(9600);                // Iniciar comunicación serie
  pinMode(mq2Pin, INPUT);            // Configurar el pin como entrada
  delay(2000);                       // Tiempo para estabilizar el sensor
  Serial.println("Sistema iniciado. Preparando sensor MQ-2...");
}

void loop() {
  Serial.println("Iniciando alcoholimetro...");

  int sumaLecturas = 0;
  const int numLecturas = 10;       // 10 lecturas en 5 segundos (~1 cada 500 ms)

  for (int i = 0; i < numLecturas; i++) {
    int lectura = analogRead(mq2Pin);
    sumaLecturas += lectura;

    Serial.print("Lectura ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(lectura);

    delay(1000); // 500 ms entre lecturas
  }

  int promedio = sumaLecturas / numLecturas;

  Serial.print("Promedio de lectura: ");
  Serial.println(promedio);

  if (promedio > umbralAlcohol) {
    Serial.println(">> Posible aliento con alcohol detectado.");
  } else {
    Serial.println(">> No se detecta aliento alcohólico.");
  }

  delay(10000); // Espera de 10 segundos antes de repetir
}
