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
//Filtrado
int Rebote=0;
const int MaximoRebote=5;