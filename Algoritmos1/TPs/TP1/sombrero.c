#include <stdio.h>
#include <stdbool.h>


#define LIMITE_ATRIBUTO_NORMAL 8
#define MAXIMA_CANTIDAD_SUPERATRIBUTOS 2
#define STRING_FUERZA "Fuerza"
#define STRING_VALOR "Valor"
#define STRING_INTELIGENCIA "Inteligencia"
#define STRING_INGENIO "Ingenio"
#define STRING_DEDICACION "Dedicacion"


int contar_super_atributos (int fuerza, int valor, int ingenio, int dedicacion, int inteligencia){
  int contador_super_atributos=0;

  if (fuerza>LIMITE_ATRIBUTO_NORMAL) {
    contador_super_atributos++;
  }

  if (valor>LIMITE_ATRIBUTO_NORMAL) {
    contador_super_atributos++;
  }

  if (ingenio>LIMITE_ATRIBUTO_NORMAL) {
    contador_super_atributos++;
  }

  if (dedicacion>LIMITE_ATRIBUTO_NORMAL) {
    contador_super_atributos++;
  }

  if (inteligencia>LIMITE_ATRIBUTO_NORMAL) {
    contador_super_atributos++;
  }

  return contador_super_atributos;
}



//en los sigueintes 3 bool
//se analizan los valores de los atributos
// y se ve si se pertenece a la casa cuyas
//condiciones están siendo comparadas

bool es_slytherin(int fuerza, int valor, int ingenio, int inteligencia, int dedicacion) {
  return (inteligencia>5)&&(inteligencia<8)&&(ingenio>8);
}

bool es_ravenclaw(int fuerza, int valor, int ingenio, int inteligencia, int dedicacion) {
      return (ingenio>8)&&(inteligencia>8);
}

bool es_gryffindor(int fuerza, int valor, int ingenio, int inteligencia, int dedicacion) {
  return (fuerza>8)&&(valor>8)&&(ingenio<5);
}

void mostrar_casa(int fuerza, int valor,int ingenio, int inteligencia, int dedicacion){
  bool pertenece_a_gryffindor = es_gryffindor(fuerza, valor, ingenio, inteligencia, dedicacion);
  bool pertenece_a_ravenclaw = es_ravenclaw(fuerza, valor, ingenio, inteligencia, dedicacion);
  bool pertenece_a_slytherin = es_slytherin(fuerza, valor, ingenio, inteligencia, dedicacion);

  if (pertenece_a_gryffindor) {
    printf("Su casa es Gryffindor\n");
  }
  else if (pertenece_a_ravenclaw) {
    printf("Su casa es Ravenclaw\n");
  }
  else if (pertenece_a_slytherin) {
    printf("Su casa es Slytherin\n");
  }
  else {
    printf("Su casa es Hufflepuff\n");
  }
}

void listar_super_atributos(int fuerza, int valor, int ingenio, int dedicacion, int inteligencia) {

  if (fuerza>LIMITE_ATRIBUTO_NORMAL) {
    printf("Fuerza\n");
  }
  if (valor>LIMITE_ATRIBUTO_NORMAL) {
    printf("Valor\n");
  }
  if (ingenio>LIMITE_ATRIBUTO_NORMAL) {
    printf("Ingenio\n");
  }
  if (dedicacion>LIMITE_ATRIBUTO_NORMAL) {
    printf("Dedicacion\n");
  }
  if (inteligencia>LIMITE_ATRIBUTO_NORMAL) {
    printf("Inteligencia\n");
  }
}


//la funcion se encarga de obtener el valor
//de un atributo específico y se asegura de que este esté
//dentro del rango pedido
void determinar__atributo(int* indice_atributo, char nombre_atributo[]){
  do {
    printf("%s:", nombre_atributo);
    scanf("%i", indice_atributo);
    if ((*indice_atributo<0)||(*indice_atributo>10)) {
      printf("Valor del atributo fuera del rango asignado,\n");
      printf("por favor ingrese un número de 0 a 10\n");
    }
  } while((*indice_atributo<0)||(*indice_atributo>10));

}


int main() {

  int fuerza, valor, inteligencia, ingenio, dedicacion;
  int cantidad_super_atributos=0;

  printf("Bienvenido al sombrero seleccionador, para que su casa sea\n");
  printf("elegida, deberá introducir valores de 0 a 10 para los\n");
  printf("atributos que serán presentados. No debe haber más de dos\n");
  printf("super atributos, que son aquellos con un valor de 9 o 10:\n");

  do {
    //codigo para pedido de atributos y determinación de super atributos

    determinar__atributo(&fuerza, STRING_FUERZA);

    determinar__atributo(&valor, STRING_VALOR);

    determinar__atributo(&inteligencia, STRING_INTELIGENCIA);

    determinar__atributo(&ingenio, STRING_INGENIO);

    determinar__atributo(&dedicacion, STRING_DEDICACION);

    cantidad_super_atributos = contar_super_atributos(fuerza, valor, ingenio, dedicacion, inteligencia);

    if (cantidad_super_atributos>MAXIMA_CANTIDAD_SUPERATRIBUTOS) {
      printf("Superó la cantidad de super atributos, los suyos fueron:\n");
      listar_super_atributos(fuerza, valor, ingenio, dedicacion, inteligencia);
      printf("Por favor, reingrese sus atributos:\n");
    }

  } while(cantidad_super_atributos>2);

  mostrar_casa(fuerza, valor, ingenio, inteligencia, dedicacion);

  return 0;
}
