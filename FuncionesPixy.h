#ifndef FuncionesPixy_h
#define FuncionesPixy_h
void AlmacenarCoordenadas(){
  Serial.println("Almacenando Coordenadas");
  for(int i=0;i<4;i++){
    x[i]=pixy.ccc.blocks[i].m_x;
    ancho[i]=pixy.ccc.blocks[i].m_width;
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
    Serial.println("Dos o mas objetos detectados");
    ReiniciarDatosFrameAnterior();
    AlmacenarCoordenadas();
    ReiniciarVectorDistancias();
    CalcularDistanciaMaxima();
    CalcularCentroDeCajon();
    if(ModoDeEstacionamiento==0){
      RutinaEstacionadoParalelo();
    }else if(ModoDeEstacionamiento==1){
      Giro();
      Espera(Giro90);
      Alto();
      ServoCamara.write(90);
      RutinaEstacionadoBateria();
    }
    Alto();
  }else{
    Serial.println("No hay suficientes objetos detectados");
  }
}
#endif
