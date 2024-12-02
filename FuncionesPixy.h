#ifndef FuncionesPixy_h
#define FuncionesPixy_h
void AlmacenarCoordenadas(){
for(int i=0;i<4;i++){
    x[i]=pixy.ccc.blocks[i].m_x;
    ancho[i]=pixy.ccc.blocks[i].m_width;
  }
  Serial.println("14.3.-Reiniciando vectores de distancias");
}
void ReiniciarVectorDistancias(){
    for(int i=0;i<4;i++){
    distanciaD[i]=2000000;
    distanciaI[i]=2000000;
  }
}
void CalcularDistanciaMaxima(){
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
  return(Xresultante);
}
void RutinaEstacionado(){
  pixy.ccc.getBlocks();
  NumeroDeObjetosDetectados=pixy.ccc.numBlocks;
  if(NumeroDeObjetosDetectados>=2){
    AlmacenarCoordenadas();
    ReiniciarVectorDistancias();
    CalcularDistanciaMaxima();
    i=0;
    while(i<4&&CentroLugarEstacionamiento==0){
      if(distanciaD[i]>TamanoMinimoDelCajonDeEstacionamintoParalelo&&distanciaD[i]<1000){
        CentroLugarEstacionamiento=(x[i]+ancho[i]/2+distanciaD[i]/2);
        ModoDeEstacionamiento=0;
      }else if(distanciaD[i]>EmEB&&distanciaD[i]<1000){
        CentroLugarEstacionamiento=(x[i]+ancho[i]/2+distanciaD[i]/2);
        ModoDeEstacionamiento=1;
      }
      if(CentroLugarEstacionamiento<0||CentroLugarEstacionamiento>400){CentroLugarEstacionamiento=0;}
      if(distanciaI[i]>TamanoMinimoDelCajonDeEstacionamintoParalelo&&distanciaI[i]<1000&&CentroLugarEstacionamiento!=0){
        CentroLugarEstacionamiento=(x[i]-ancho[i]/2-distanciaI[i]/2);
        ModoDeEstacionamiento=0;
        Serial.println("14.8.-Modo de estacionamiento en Paralelo");
      }else if(distanciaI[i]>EmEB&&distanciaI[i]<1000&&CentroLugarEstacionamiento!=0){
        CentroLugarEstacionamiento=(x[i]-ancho[i]/2-distanciaI[i]/2);
        ModoDeEstacionamiento=1;

      }
      if(CentroLugarEstacionamiento<0||CentroLugarEstacionamiento>400){CentroLugarEstacionamiento=0;}
      if(i==3){
        Serial.println("No se encontro lugar");
      }
      i++;
    }
    if(CentroLugarEstacionamiento>=thredholdI&&CentroLugarEstacionamiento<=thredholdD&&ModoDeEstacionamiento==0){
      LateralD();
      Espera(EstacionadoParalelo);
      Alto();
    }else if(CentroLugarEstacionamiento!=0&&CentroLugarEstacionamiento<thredholdI&&CentroLugarEstacionamiento<thredholdD&&ModoDeEstacionamiento==0){
      Reversa();//***Moverse a la derecha
      Espera(5);
      Alto();
    }else if(CentroLugarEstacionamiento>thredholdI&&CentroLugarEstacionamiento>thredholdD&&ModoDeEstacionamiento==0){
      Frontal(15);//***Moverse a la izquierda
      Espera(5);
      Alto();
    }
    else if(ModoDeEstacionamiento==1){
    }
    Alto();
  }
}
#endif