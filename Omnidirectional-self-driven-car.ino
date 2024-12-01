//Bibliotecas
#include <Pixy2.h>
#include <Servo.h>
//Objetos
Pixy2 pixy;//Creando el objeto(Pixy)
Servo ServoCamara;
//Definiciones
//L298N
#define IN1 13
#define IN2 12
#define IN3 2
#define IN4 3
#define IN5 4
#define IN6 5
#define IN7 7
#define IN8 6
//HC-SR-04
#define Trigger1 14
#define Trigger2 15
#define Echo1 16
#define Echo2 17
//servo
#define Ser 8 
//Encoder
#define tacometro 21 
//Variables
//HC-SR-04
int pulso = 0;
//Distancia en cm medido por los sensores ultrasonicos
int HC1=0;
int HC2=0;
//Caracterizacion de los motores
const int PWMmin1 = 104;
const int PWMmin2 = 98;
const int PWMmin3 = 123;
const int PWMmin4 = 116;
//Encoder
int ticks=0;
//Seguimiento de linea
int x0[5]={};//Array de coordenadas iniciales de los vectores 
int y0[5]={};
int x1[5]={};//Array de coordenadas finales de los vectores 
int y1[5]={};
int x0t=0;//Coordenadas del inicio del vector resultante
int x1t=0;//Coordenadas del final del vector resultante
int Xresultante=0;//Magnitud del vector resultante
int CountL;//Contador de vectores detectados
//Parametros
//Distancia maxima para detectar un carrito en cm
const int DistanciaMaximaCajon=50;
//Banderas
bool modo=0;
bool modoPrevio=0;
void setup(){
  Serial.begin(115200);//Inicializando comunicacion serial
  pixy.init(); //inicializando la camara
  pixy.changeProg("line");//Cambiando el modo inicial de la camara a deteccion de lineas
  //Configurando los pines de control de los puentes H
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  // Configura el pin servo como salida
  pinMode(Ser, OUTPUT);
  ServoCamara.attach(Ser);
  ServoCamara.write(90);
  //Pines asociados a los sensores ultrasonicos
  pinMode(Trigger1, OUTPUT);
  pinMode(Trigger2, OUTPUT);
  pinMode(Echo1, INPUT);
  pinMode(Echo2, INPUT);
  //Configurando la interrupcion del encoder
  pinMode(tacometro,INPUT);
  attachInterrupt(digitalPinToInterrupt(tacometro),Encoder,FALLING);
}
void loop(){
  HC1=Distancia(Trigger1,Echo1);
  delay(3);
  HC2=Distancia(Trigger2,Echo2);
  if (HC1>DistanciaMaximaCajon && HC2 > DistanciaMaximaCajon) {
    modo=1;
  }else{
    modo=0;
  }
  if(modo!=modoPrevio){
    if(modo){
      Alto();
    }else{
      pixy.changeProg("line");
    }
    delay(50);
    modoPrevio=modo;
  }
  if(!modo){
    Xresultante=detectarLineas();
  }


}
void Frontal(int dir) {
  int FD=map(50,0,255,PWMmin1,255)-map(dir,-78,78,0,200);
  int FI=map(50,0,255,PWMmin2,255)+map(dir,-78,78,0,200);
  int TD=map(50,0,255,PWMmin3,255)-map(dir,-78,78,0,200);
  int TI=map(50,0,255,PWMmin4,255)+map(dir,-78,78,0,200);
  digitalWrite(IN1, FD); 
  digitalWrite(IN2, LOW); // Motor derecho frontal adelante
  digitalWrite(IN3, FI); 
  digitalWrite(IN4, LOW); // Motor izquierdo frontal adelante
  digitalWrite(IN5, TD); 
  digitalWrite(IN6, LOW); // Motor derecho trasero adelante
  digitalWrite(IN7, TI); 
  digitalWrite(IN8, LOW); // Motor izquierdo trasero adelante
}
void Reversa() {
  int FD=map(20,0,255,PWMmin1,255);
  int FI=map(20,0,255,PWMmin2,255);
  int TD=map(20,0,255,PWMmin3,255);
  int TI=map(20,0,255,PWMmin4,255);
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, FD); // Motor derecho frontal adelante
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, FI); // Motor izquierdo frontal adelante
  digitalWrite(IN5, LOW); 
  digitalWrite(IN6, TD); // Motor derecho trasero adelante
  digitalWrite(IN7, LOW); 
  digitalWrite(IN8, TI); // Motor izquierdo trasero adelante
}
void LateralD(){
  int FD=map(20,0,255,PWMmin1,255);
  int FI=map(20,0,255,PWMmin2,255);
  int TD=map(20,0,255,PWMmin3,255);
  int TI=map(20,0,255,PWMmin4,255);
  digitalWrite(IN1, FD);  // GIRO Reversa
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // GIRO Frente
  digitalWrite(IN4, FI);
  digitalWrite(IN5, TD);  // GIRO Frente
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW);  // GIRO Revers
  digitalWrite(IN8, TI);
}
void LateralI(){
  int FD=map(20,0,255,PWMmin1,255);
  int FI=map(20,0,255,PWMmin2,255);
  int TD=map(20,0,255,PWMmin3,255);
  int TI=map(20,0,255,PWMmin4,255);
  digitalWrite(IN1, LOW);  // GIRO Reversa
  digitalWrite(IN2, FD);
  digitalWrite(IN3, FI);  // GIRO Frente
  digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW);  // GIRO Frente
  digitalWrite(IN6, TD);
  digitalWrite(IN7, TI);  // GIRO Revers
  digitalWrite(IN8, LOW);
}
void Giro() {
  int FD=map(200,0,255,PWMmin1,255);
  int FI=map(200,0,255,PWMmin2,255);
  int TD=map(200,0,255,PWMmin3,255);
  int TI=map(200,0,255,PWMmin4,255);
  digitalWrite(IN1, FD); 
  digitalWrite(IN2, LOW); // Motor derecho frontal adelante
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, FI); // Motor izquierdo frontal atrás
  digitalWrite(IN5, TD); 
  digitalWrite(IN6, LOW); // Motor derecho trasero adelante
  digitalWrite(IN7, LOW); 
  digitalWrite(IN8, TI); // Motor izquierdo trasero atrás
}
void Alto() {
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW); 
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW); 
  digitalWrite(IN8, LOW);
}
int Distancia(int Tr,int Ec){
  digitalWrite(Tr,HIGH);
  delay(1);
  digitalWrite(Tr,LOW);
  pulso = pulseIn(Ec,HIGH);
  Serial.println(pulso/58.2);
  return pulso/58.2;
}
void Encoder(){
  ticks++;
}
int detectarLineas() {
  Xresultante=0;
  x0t=0;
  x1t=0;
  pixy.line.getAllFeatures();
  CountL=pixy.line.numVectors;
  for (int i=0; i<CountL; i++) {
    x0[i] = pixy.line.vectors[i].m_x0-39;
    x1[i] = pixy.line.vectors[i].m_x1-39;
  }
  for(int i=0;i<CountL;i++){
    x0t=x0t+x0[i];
    x1t=x1t+x1[i];
  }
  Xresultante=x1t-x0t;
  Serial.println(Xresultante);
  return(Xresultante);
}
