#include <stdio.h>
#include <stdbool.h>

#define NUMEROS_PRIMOS 4

int main() {

  unsigned long a=0;
  unsigned long b=0;
  unsigned long c=0;
  unsigned long d=0;

  unsigned long cuatro_numeros_primos[NUMEROS_PRIMOS]={0, 0, 0, 0};
  unsigned long contador_primeros_numeros_primos=0;
  unsigned long numero=2;
  bool es_primo=true;
  unsigned long resto_primo=0;
  unsigned long i=0;
  unsigned long resto_division=0;
  unsigned long cuarto_primo=0;
  bool es_primo2=true;
  unsigned long numero2=0;
  unsigned long suma_numero_primos=2;
  unsigned long j=0;
  unsigned long resto_primo2=0;
  unsigned long contador_primos_2=1;


  while (contador_primeros_numeros_primos<4) {

    i=numero-1;
    while ((es_primo)&&(i>1)) {
      resto_primo=numero%i;
      if (resto_primo==0) {
        es_primo=false;
      }

      i--;

    }

    resto_division=numero%6000;

    if((es_primo)&&(resto_division==3109)){
      //cuatro_numeros_primos[contador_primeros_numeros_primos]=numero;
      if (contador_primeros_numeros_primos==3) {
        cuarto_primo=numero;
      }
      contador_primeros_numeros_primos++;
    }


    numero++;
    es_primo=true;

  }

  //a=cuatro_numeros_primos[3];
  a=cuarto_primo;


  b=(a%201)+60;

  c=b/5;

  numero2=3;

  while (contador_primos_2<c) {

    j=numero2-1;
    while ((es_primo2)&&(j>1)) {
      resto_primo2=numero2%j;
      if (resto_primo2==0) {
        es_primo2=false;
      }

      j--;

    }

    if (es_primo2) {
      suma_numero_primos+=numero2;
      contador_primos_2++;
    }

    numero2++;
    es_primo2=true;

  }

  d=(suma_numero_primos%543)-254;


  printf("b=%lu  d=%lu\n", b, d);

  return 0;
}
