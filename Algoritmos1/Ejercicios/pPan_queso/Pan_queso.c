#include <stdio.h>


int main() {
  double pie1=0.0;
  double pie2=0.0;
  double distancia=0.0;
  double posicion_pie1=0.0;
  double posicion_pie2=0.0;
  double distanciacm=0.0;
  double posicion_final_pie2=0.0;

  printf("Inserte distancia entre pies en metros con decimales:");
  scanf("%lf", &distancia);
  distanciacm=distancia*100.0;
  posicion_pie2=distanciacm;
  printf("Inserte longitud del pie 1 en cm con decimales:");
  scanf("%lf", &pie1);
  printf("Inserte longitud del pie 2 en cm con decimales:");
  scanf("%lf", &pie2);

  while (posicion_pie2>posicion_pie1) {
    posicion_pie1+=pie1;
    posicion_pie2-=pie2;
  }

  posicion_final_pie2=posicion_pie2+pie2;

  if (posicion_final_pie2<=posicion_pie1) {
  printf("Ganó pie 1\n");
  }
  else{
  printf("Ganó pie 2\n");
  }

  return 0;
}
