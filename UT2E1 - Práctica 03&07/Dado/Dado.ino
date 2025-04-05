#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int dado = 1;

// Pines del LED RGB (cátodo común)
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("Error: MPU6050 no conectado");
    while (1);
  }

  // Configurar pines del LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  apagarLED();
}

void loop() {
  int16_t ax, ay, az;
  float x, y, z;

  // Esperar a que se lance el dado
  while (true) {
    mpu.getAcceleration(&ax, &ay, &az);
    x = ax / 16384.0;
    y = ay / 16384.0;
    z = az / 16384.0;

    float magnitude = sqrt(x * x + y * y + z * z);
    if (abs(magnitude - 1.0) > 0.4) {
      break;
    }
    delay(50);
  }

  delay(1000); // Esperar que el dado se estabilice

  mpu.getAcceleration(&ax, &ay, &az);
  x = ax / 16384.0;
  y = ay / 16384.0;
  z = az / 16384.0;

  // Determinar la cara superior
  if (z > 0.7) dado = 1;
  else if (z < -0.7) dado = 6;
  else if (y > 0.7) dado = 3;
  else if (y < -0.7) dado = 4;
  else if (x > 0.7) dado = 2;
  else if (x < -0.7) dado = 5;
  else dado = 0;

  // Mostrar resultado
  if (dado != 0) {
    Serial.print("Resultado del dado: ");
    Serial.println(dado);
    mostrarColor(dado);
  } else {
    Serial.println("No se pudo determinar la cara.");
    apagarLED();
  }

  delay(2000); // Esperar antes de nuevo lanzamiento
}

// Función para mostrar el color correspondiente
void mostrarColor(int numero) {
  switch (numero) {
    case 1: setColor(255, 0, 0); break;       // Rojo
    case 2: setColor(0, 255, 0); break;       // Verde
    case 3: setColor(0, 0, 255); break;       // Azul
    case 4: setColor(255, 255, 0); break;     // Amarillo
    case 5: setColor(0, 255, 255); break;     // Cian
    case 6: setColor(255, 0, 255); break;     // Magenta
    default: apagarLED(); break;
  }
}

// Función para establecer el color del LED
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

// Apagar el LED
void apagarLED() {
  setColor(0, 0, 0);
}


