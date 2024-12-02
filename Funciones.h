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
#endif
