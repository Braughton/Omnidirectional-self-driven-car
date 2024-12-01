int Distancia(int Tr,int Ec){
  digitalWrite(Tr,HIGH);
  delay(1);
  digitalWrite(Tr,LOW);
  pulso = pulseIn(Ec,HIGH);

  return pulso/58.2;
}
void Encoder(){
  ticks++;
}
void Espera(int espera){
  ticks1=ticks+espera;
  while (ticks<ticks1){

  }
}
