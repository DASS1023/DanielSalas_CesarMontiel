#include <Wire.h> 
#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define LED_PIN 13

#define INPUTS 2
#define NODES 2
#define OUTPUTS 2

LiquidCrystal_I2C lcd(0x27, 16, 2); 
MPU6050 mpu;

float P[INPUTS][1];
float a1[NODES][1];
float a2[OUTPUTS][1];

float W1[NODES][INPUTS] = {
  {-5.971061067614598, -4.052199412276152},
  {1.0, 1.0}
};

float b1[NODES][1] = {
  {-1.026496914960414},
  {0.07435889453504886}
};

float W2[OUTPUTS][NODES] = {
  {0.8336965359193182, 0.425945679354389},
  {-3.323307250637575, 1.652875775072965}
};

float b2[OUTPUTS][1] = {
  {0.6817210240534946},
  {-2.433058310229936}
};

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  lcd.init();  
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  mpu.initialize();
  if (!mpu.testConnection()) {
    lcd.setCursor(0, 1);
    lcd.print("MPU no detectado");
    Serial.println("Error: MPU6050 no conectado");
    while (1);
  }

  lcd.setCursor(0, 1);
  lcd.print("Listo!");
  delay(1000);
  lcd.clear();
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  float norm_ax = ax / 16384.0;
  float norm_ay = ay / 16384.0;
  float norm_az = az / 16384.0;

  float pitch = -(atan2(norm_ax, sqrt(norm_ay * norm_ay + norm_az * norm_az)) * 180.0 / PI);
  float roll  = (atan2(norm_ay, norm_az) * 180.0 / PI);

  // 🔴 Detectar inclinación entre 10° y 15°
  if (pitch >= 10.0 && pitch <= 15.0) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  float pitch_mapped = mapFloat(pitch, -180.0, 180.0, 0.0, 1023.0);
  float roll_mapped  = mapFloat(roll, -180.0, 180.0, 0.0, 1023.0);

  P[0][0] = dataNormalized(pitch_mapped, 0.0, 1023.0);
  P[1][0] = dataNormalized(roll_mapped, 0.0, 1023.0);

  forwardPass();

  String tipoSoldadura;

  if (a2[0][0] <= 0 && a2[1][0] <= 0) {
    tipoSoldadura = "MediaLuna";
  } else if (a2[0][0] > 0 && a2[1][0] > 0) {
    tipoSoldadura = "ZigZag";
  } else if (a2[0][0] > 0 && a2[1][0] <= 0) {
    tipoSoldadura = "Espiral";
  } else {
    tipoSoldadura = "Indefinido";
  }

  Serial.println("Tipo: " + tipoSoldadura);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tipo:");
  lcd.setCursor(0, 1);
  lcd.print(tipoSoldadura);

  delay(300);
}

// ==== Funciones auxiliares ====

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float dataNormalized(float inputData, float minData, float maxData) {
  return (inputData - minData) / (maxData - minData);
}

float tansig(float n) {
  if (n > 20) n = 20;
  if (n < -20) n = -20;
  float a = exp(n);
  float b = exp(-n);
  return (a - b) / (a + b);
}

void forwardPass() {
  for (int i = 0; i < NODES; i++) {
    float sum = b1[i][0];
    for (int j = 0; j < INPUTS; j++) {
      sum += W1[i][j] * P[j][0];
    }
    a1[i][0] = tansig(sum);
  }

  for (int i = 0; i < OUTPUTS; i++) {
    float sum = b2[i][0];
    for (int j = 0; j < NODES; j++) {
      sum += W2[i][j] * a1[j][0];
    }
    a2[i][0] = tansig(sum);
  }
}


