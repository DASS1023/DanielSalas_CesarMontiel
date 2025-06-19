volatile int pulsos = 0;

void contarPulsos() {
  pulsos++;
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), contarPulsos, RISING);
}

void loop() {
  pulsos = 0;
  sei(); // Habilita interrupciones
  delay(1000); // Espera 1 segundo
  cli(); // Desactiva interrupciones temporalmente

  float frecuencia = pulsos * 1.0; // Hz
  float caudal = frecuencia / 7.5; // L/min (aproximado)

  Serial.print("Frecuencia (Hz): ");
  Serial.print(frecuencia);
  Serial.print(" | Caudal: ");
  Serial.print(caudal);
  Serial.println(" L/min");

  delay(500);
}
