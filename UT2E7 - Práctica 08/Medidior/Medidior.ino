volatile unsigned int pulsos = 0;
float caudal_Lmin = 0;
float volumen_L = 0;

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
  delay(1000); // Mide durante 1 segundo
  cli(); // Desactiva interrupciones temporalmente

  caudal_Lmin = pulsos / 7.5;
  volumen_L += caudal_Lmin / 60.0; // Acumula volumen cada segundo

  Serial.print("Caudal: ");
  Serial.print(caudal_Lmin);
  Serial.print(" L/min | ");
  
  Serial.print("Caudal: ");
  Serial.print(caudal_Lmin / 1000.0);
  Serial.print(" m³/min | ");

  Serial.print("Volumen acumulado: ");
  Serial.print(volumen_L);
  Serial.println(" L");
}

