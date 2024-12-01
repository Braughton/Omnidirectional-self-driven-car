#include <Pixy2.h>
Pixy2 pixy;//Creando el objeto(Pixy)
#include <Servo.h>
Servo ServoCamara;
#include "Definiciones.h"
#include"Variables.h"
#include"Parametros.h"
#include"Banderas.h"
#include"FuncionesPixy.h"
#include"FuncionesMovimiento.h"
#include"Funciones.h"


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
    Rebote++;
    if(Rebote>MaximoRebote){
    modo=0;
    Rebote=0;
    }
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
    Frontal(Xresultante);
  }else if(!Alineado){
  Xresultante=detectarLineas() + offset;
  while(Xresultante!=0){
    Xresultante=detectarLineas() + offset;
    Serial.println(Xresultante);
    if (Xresultante<0){
      LateralD();
      Espera(1);
      Alto();
    }else{
      LateralI();
      Espera(1);
      Alto();
    }
  }
  Alineado=1;
  Serial.print("alineado");
    //alinear el vehiculo con el carril izquierdo , cambiar al modulo de deteccion de objetos y analizar el entorno en busqueda de un lugar de estacionamiento
  }
}
