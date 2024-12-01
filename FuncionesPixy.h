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
