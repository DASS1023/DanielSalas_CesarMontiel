  #include <wire.h>
  #include <MPU6050.h>

  MPU6050 mpu;

  int pitch=0;
  int roll=0;
  unsigned long past:time=0;

  /////Red Neuronal 
  const int node = 2;
  const int input = 2;
  const int outputs = 2;
  float P[inputs][1];
  float W1[node][input]={{2.89075,4,4.252997},
                        {-0.64984,-2.85748}};
  
  float b1[node][1]={{1.2877},
                    {1.2359}};

  float a1[node][1];

  float W2[outputs][node]={{0.98084,2.19659},
                        {-3.42942,0.49034}};

  float b2[outputs][1];
  float aux=0.0;
  int maxValue = 1023;
  int minValue = 0;
  void setup() {
    //put your setup code here to run once
    while(!mpu.begin(MPU6050_SCALE_2000DSP,MPU6050_RANGE_26))
    {
      delay(500);
    }
  }  
  //Primera capa
  Vector normAcel = mpu.readNormalizeEccel();
  pitch = -(atan2(normalAccel.XAxis, sqrt(normAccel.Yaxis*n)))
  roll = ((atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)

  pitch=map(pitch,-180,180,0,1023);
  roll=map(roll,-180,180,0,1023);

  P[0][0]=dataNormalized((float) pitch,minValue,maxValue);
  P[1][0]=dataNormalized((float) roll,minValue,maxValue);

  //Segunda Capa

  for(int i = 0 ; i<node; i++) {
    aux=0.0;
    for(int j = 0 ; j < input ; j++ ) {
      aux=aux+W1[i][j]*P[i][j];
    }
    a1[i][0]=tansig(aux+b1[i][0]);
  }

  //Tercera capa
  for(int i = 0 ; i<outputs; i++) {
    aux=0.0;
    for(int j = 0 ; j < input ; j++ ) {
      aux=aux+W1[i][j]*P[j][0];
    }
    a2[i][0]=tansig(aux+b2[i][0]);
  }

  if(a2[0][0]<= && a2[1][0]<=0){
    Serial-printIn("Atras");
  }
  else if(a2[0][0]>0 && a2[1][0]>0){
    Serial-printIn("Izquierda");)
  }
  else if(a2[0][0]>0 && a2[1][0]<=0){
    Serial-printIn("Derecha");)
  }
  else
  {
    Serial.printIn("Adelante");
  }

  delay(50);

  float tansig(float n)
  {
    float a = exp(n);
    float b = exp(-n);
    return (a-b)/(a+b);
  }

  float dataNormalized(int inputData, int minData, int maxData)
  {
    float valueNorm;
    valueNorm =
  }
