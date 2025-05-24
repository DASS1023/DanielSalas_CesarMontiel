int mq2Pin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lectura = analogRead(mq2Pin);
  Serial.print("Valor MQ-2: ");
  Serial.println(lectura);
  delay(1000); // cada segundo
}
