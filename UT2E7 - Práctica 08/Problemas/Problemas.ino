volatile int pulsos1 = 0;
volatile int pulsos2 = 0;

void contar1() { pulsos1++; }
void contar2() { pulsos2++; }

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);  // Sensor 1
  pinMode(3, INPUT_PULLUP);  // Sensor 2
  attachInterrupt(digitalPinToInterrupt(2), contar1, RISING);
  attachInterrupt(digitalPinToInterrupt(3), contar2, RISING);
}

void loop() {
  pulsos1 = 0;
  pulsos2 = 0;
  sei(); // Habilita interrupciones
  delay(1000); // Mide por 1 segundo
  cli(); // Desactiva interrupciones

  float caudal1 = pulsos1 / 7.5;
  float caudal2 = pulsos2 / 7.5;

  Serial.print("Sensor 1: ");
  Serial.print(caudal1);
  Serial.print(" L/min | Sensor 2: ");
  Serial.print(caudal2);
  Serial.print(" L/min | Diferencia: ");
  Serial.print(abs(caudal1 - caudal2));
  Serial.println(" L/min");
}
