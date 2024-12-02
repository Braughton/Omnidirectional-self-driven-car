#ifndef Funciones_h
#define Funciones_h
int Distancia(int Tr,int Ec){
  int distancia;
  digitalWrite(Tr,HIGH);
  delay(1);
  digitalWrite(Tr,LOW);
  pulso = pulseIn(Ec,HIGH);
  distancia = pulso/58.2;
  Serial.print("HC=" + distancia + "/t");
  return distancia;
}
void Encoder(){
  ticks++;
}
void Espera(int espera){
  ticks1=ticks+espera;
  while (ticks<ticks1){
    int restantes = ticks1 - ticks;
    Serial.println("Esperando " + espera + "faltan" + restantes);
  }
}
#endif