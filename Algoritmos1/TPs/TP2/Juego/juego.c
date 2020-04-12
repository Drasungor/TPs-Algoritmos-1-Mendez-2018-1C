#include <stdio.h>
#include <stdbool.h>

#include "sombrero.h"
#include "quidditch.h"


int main(int argc, char const *argv[]) {

  char casa=' ';
  juego_t informacion_juego;
  char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS];
  char movimiento;

  printf("Bienvenido al simulador de persecucion de snitch, para comenzar debera pasar por\n");
  printf("el sombrero seleccionador para obtener de esa manera su habilidad especial.\n");
  printf("Las reglas del juego son:\n");
  printf("Se ganara si se posa sobre la snitch\n");
  printf("Si la resistencia llega a 0, pierde\n");
  printf("Si es golpeado por una bludger, perdera 10 puntos de resistencia\n");
  printf("Si cae en un dementor, le absorbera toda su resistencia, por lo que perdera\n");
  printf("Hay 4 movimientos posibles: arriba(w), abajo(s), izquierda(a) y derecha(d)\n");
  printf("\n");

  casa= obtener_casa();

  switch (casa) {
    case GRYFFINDOR:
    printf("Como pertenece a Gryffindor, al caer sobre un dementor usted realizará el hechizo ");
    printf("Expecto patronus, por lo que lo eliminara\n");
    break;

    case HUFFLEPUFF:
    printf("Al pertenecer a Hufflepuff, usted realizara dos movimientos por turno debido a su ");
    printf("gran manejo de la escoba\n");
    break;

    case RAVENCLAW:
    printf("Al pertenecer a Ravenclaw, usted podra atrapar a la Snitch si esta se encuentra ");
    printf("en una posicion adyacente\n");
    break;

    case SLYTHERIN:
    printf("Al pertenecer a Slytherin, usted no se vera afectado por los golpes de las bludgers\n");
    break;
  }

  printf("\n");

  inicializar_juego(campo, casa, &informacion_juego);

  imprimir_matriz(campo);

  printf("Resistencia: %d\n", informacion_juego.resistencia);

  while (!finalizo_juego(&informacion_juego)) {

    movimiento= pedir_movimiento(informacion_juego.posicion_jugador);
    mover_jugador(campo, movimiento, &informacion_juego);

    if ((informacion_juego.casa==HUFFLEPUFF)&&(!finalizo_juego(&informacion_juego))) {
      dejar_espacio();
      imprimir_matriz(campo);
      printf("Resistencia: %d\n", informacion_juego.resistencia);

      movimiento= pedir_movimiento(informacion_juego.posicion_jugador);
      mover_jugador(campo, movimiento, &informacion_juego);
    }

    mover_bludgers(campo, &informacion_juego);
    mover_snitch(campo, &informacion_juego);
    dejar_espacio();
    imprimir_matriz(campo);

    printf("Resistencia: %d\n", informacion_juego.resistencia);
  }

  mostrar_resultado(informacion_juego);

  return 0;
}
