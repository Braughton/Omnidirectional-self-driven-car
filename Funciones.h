int Distancia(int Tr,int Ec){
  digitalWrite(Tr,HIGH);
  delay(1);
  digitalWrite(Tr,LOW);
  pulso = pulseIn(Ec,HIGH);
  Serial.print("HC=");
  Serial.println(pulso/58.2);
  return pulso/58.2;
}
void Encoder(){
  ticks++;
}