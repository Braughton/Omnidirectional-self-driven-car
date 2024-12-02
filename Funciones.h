#ifndef Funciones_h
#define Funciones_h
int Distancia(int Tr,int Ec){
  int distancia;
  digitalWrite(Tr,HIGH);
  delay(1);
  digitalWrite(Tr,LOW);
  pulso = pulseIn(Ec,HIGH);
  distancia = pulso/58.2;
  Serial.print("HC=");
  Serial.print(distancia);
  Serial.print("/t");
  return distancia;
}
void Encoder(){
  ticks++;
}
void Espera(int espera){
  ticks1=ticks+espera;
  while (ticks<ticks1){
    int restantes = ticks1 - ticks;
    Serial.print("Esperando ");
    Serial.print(espera);
    Serial.print("faltan");
    Serial.println(restantes);
  }
  Serial.print("Termino La Espera");
}
void ReiniciarVectorDistancias(){
  Serial.println("Reiniciando vectores de distancia");
    for(int i=0;i<4;i++){
    distanciaD[i]=2000000;
    distanciaI[i]=2000000;
  }
}
void CalcularDistanciaMaxima(){
  Serial.println("Calculando distancia minima entre objetos");
  for(int i=0;i<=2;i++){
    for(int j=i+1;j<=3;j++){
      if(j==i+1){
        if(x[i]<x[j]){
          distanciaD[i]=(x[j]-ancho[j]/2)-(x[i]+ancho[i]/2);
        }else if(x[j]<x[i]){
          distanciaI[i]=(x[i]-ancho[i]/2)-(x[j]+ancho[j]/2);
        }else{
          distanciaD[i]=0;
          distanciaI[i]=0;
        }
      }else{
        if(x[i]<x[j]){
          if(distanciaD[i]>(x[j]-ancho[j]/2)-(x[i]+ancho[i]/2)){
            distanciaD[i]=(x[j]-ancho[j]/2)-(x[i]+ancho[i]/2);  
          }
        }else if(x[j]<x[i]){
          if(distanciaI[i]>(x[i]-ancho[i]/2)-(x[j]+ancho[j]/2)){
            distanciaI[i]=(x[i]-ancho[i]/2)-(x[j]+ancho[j]/2);
          }
        }else{
          distanciaD[i]=0;
          distanciaI[i]=0;
        }
      }
    }
  }
  Serial.println("Distancia minima entre objetos calculada");
}
void ReiniciarDatosFrameAnterior(){
  Serial.println("Borrando datos cuadro anterior");
  for (int i = 0; i < 4; i++){
    x[i]=0;
    ancho[i]=0;
  }
}
void CalcularCentroDeCajon(){
  i=0;
  while(i<4&&CentroLugarEstacionamiento==0){
    if(distanciaD[i]>TamanoMinimoDelCajonDeEstacionamintoParalelo&&distanciaD[i]<1000){
      CentroLugarEstacionamiento=(x[i]+ancho[i]/2+distanciaD[i]/2);
      ModoDeEstacionamiento=0;
      Serial.println("Centro del cajon detectado");
    }else if(distanciaD[i]>EmEB&&distanciaD[i]<1000){
      CentroLugarEstacionamiento=(x[i]+ancho[i]/2+distanciaD[i]/2);
      ModoDeEstacionamiento=1;
      Serial.println("Centro del cajon detectado");
    }
    if(CentroLugarEstacionamiento<0||CentroLugarEstacionamiento>400){CentroLugarEstacionamiento=0;}
    if(distanciaI[i]>TamanoMinimoDelCajonDeEstacionamintoParalelo&&distanciaI[i]<1000&&CentroLugarEstacionamiento!=0){
      CentroLugarEstacionamiento=(x[i]-ancho[i]/2-distanciaI[i]/2);
      ModoDeEstacionamiento=0;
      Serial.println("Centro del cajon detectado");
    }else if(distanciaI[i]>EmEB&&distanciaI[i]<1000&&CentroLugarEstacionamiento!=0){
      CentroLugarEstacionamiento=(x[i]-ancho[i]/2-distanciaI[i]/2);
      ModoDeEstacionamiento=1;
      Serial.println("Centro del cajon detectado");
    }
    if(CentroLugarEstacionamiento<0||CentroLugarEstacionamiento>400){CentroLugarEstacionamiento=0;}
    if(i==3){
      Serial.println("No se encontro lugar");
    }
    i++;
  }
}
void RutinaEstacionadoParalelo(){
    if(CentroLugarEstacionamiento>=thredholdI&&CentroLugarEstacionamiento<=thredholdD){
      Serial.println("Entrando a cajon paralelo");
      LateralD();
      Espera(EstacionadoParalelo);
      Alto();
      Serial.println("Vehiculo estacionado");
      Estacionado=1;
    }else if(CentroLugarEstacionamiento!=0&&CentroLugarEstacionamiento<thredholdI&&CentroLugarEstacionamiento<thredholdD){
      Serial.println("Alineando vehiculo con el cajon de estacionamiento");
      Reversa();//***Moverse a la derecha
      Espera(5);
      Alto();
    }else if(CentroLugarEstacionamiento>thredholdI&&CentroLugarEstacionamiento>thredholdD){
      Serial.println("Alineando vehiculo con el cajon de estacionamiento");
      Frontal(15);//***Moverse a la izquierda
      Espera(5);
      Alto();
    }
}
void RutinaEstacionadoBateria(){
    if(CentroLugarEstacionamiento>=thredholdI&&CentroLugarEstacionamiento<=thredholdD){
      Serial.println("Entrando a cajon paralelo");
      LateralD();
      Espera(EstacionadoParalelo);
      Alto();
      Serial.println("Vehiculo estacionado");
      Estacionado=1;
    }else if(CentroLugarEstacionamiento!=0&&CentroLugarEstacionamiento<thredholdI&&CentroLugarEstacionamiento<thredholdD){
      Serial.println("Alineando vehiculo con el cajon de estacionamiento");
      Reversa();//***Moverse a la derecha
      Espera(5);
      Alto();
    }else if(CentroLugarEstacionamiento>thredholdI&&CentroLugarEstacionamiento>thredholdD){
      Serial.println("Alineando vehiculo con el cajon de estacionamiento");
      Frontal(15);//***Moverse a la izquierda
      Espera(5);
      Alto();
    }
}
#endif
