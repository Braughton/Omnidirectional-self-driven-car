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
