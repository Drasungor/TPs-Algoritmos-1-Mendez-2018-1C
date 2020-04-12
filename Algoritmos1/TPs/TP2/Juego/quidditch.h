#ifndef QUIDDITCH_H
#define QUIDDITCH_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CANTIDAD_INICIAL_BLUDGERS 5
#define CANTIDAD_INICIAL_DEMENTORES 4

#define CANTIDAD_FILAS 25
#define CANTIDAD_COLUMNAS 15
#define CENTRO_FILAS 12
#define CENTRO_COLUMNAS 7

#define JUGADOR 'J'
#define DEMENTOR 'D'
#define SNITCH 'S'
#define BLUDGER 'B'

#define RESISTENCIA_INICIAL 50
#define RESISTENCIA_MINIMA 0

#define COLUMNA_INICIAL_BLUDGERS 0

#define FILA_1_DEMENTORES 5
#define FILA_2_DEMENTORES 19
#define COLUMNA_1_DEMENTORES 3
#define COLUMNA_2_DEMENTORES 11

#define EN_EJECUCION 0
#define JUGADOR_GANO 1
#define JUGADOR_PERDIO 2

#define ARRIBA 'w'
#define ABAJO 's'
#define IZQUIERDA 'a'
#define DERECHA 'd'

#define DISTANCIA_MAXIMA_JUGADOR_A_SNITCH_CON_MOVIMIENTO 10
#define DISTANCIA_MINIMA_INICIAL_SNITCH_A_JUGADOR 5

#define HACIA_DERECHA 'D'
#define HACIA_IZQUIERDA 'I'

#define HUFFLEPUFF 'H'
#define GRYFFINDOR 'G'
#define SLYTHERIN 'S'
#define RAVENCLAW 'R'

#define PRIMER_MOVIMIENTO 1

#define ESPACIO_VACIO ' '


typedef struct coordenada {
	int fila;
	int columna;
} coordenada_t;

typedef struct juego {
	coordenada_t posicion_jugador;
	char casa;
	int resistencia;
	coordenada_t posicion_snitch;

	int bludgers_en_juego; // tope del vector posicion_bludgers
	coordenada_t posicion_bludgers[CANTIDAD_INICIAL_BLUDGERS];
	char direccion; // 'D': derecha – 'I': izquierda

	int dementores_en_juego; // tope del vector posicion_dementores
	coordenada_t posicion_dementores[CANTIDAD_INICIAL_DEMENTORES];

	int estado; // 0: en ejecucion – 1: jugador gano – 2: jugador perdio
} juego_t;



//------FUNCIONES PROPIAS-----

//precondiciones:-
//postcondiciones: imprime 100 líneas en blanco para dejar espacio entre
//las distintas matrices impresas a lo largo del juego
void dejar_espacio();


//precondiciones: todos los elementos de la matriz deben estar inicializados
//postcondiciones: imprimirá por pantalla la matriz campo, representando las
//posiciones de todos los elementos del juego
void imprimir_matriz(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]);



//------FUNCIONES DADAS------

//precondiciones:-
//postcondiciones: le otorga un valor inicial a cada propiedad de la estructura del juego
void inicializar_juego(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], char casa, juego_t *juego);

//precondición: el jugador debe estar dentro del campo de juego (sino
//tomará como validos movimientos fuera de este)
//postcondición: devuelve un caracter que representa un movimiento válido
//dentro del campo de juego
char pedir_movimiento(coordenada_t posicion_jugador);

//precondición:la función debe recibir como parámetro una dirección de movimiento válida
//postcondición: devuelve como parámetro la nueva posición del jugador
//una vez hecho el movimiento
void mover_jugador(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], char direccion, juego_t *juego);

//precondiciones: el campo de juego debe estar actualizado
//postcondiciones: actualiza el estado de juego de manera tal que la
//posicion a la que se moverá snitch siga las reglas del juego
void mover_snitch(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t *juego);

//precondiciones: la variable de juego que indica el sentido de movimiento de las
//bludgers debe estar inicializada
//postcondiciones: moverá todas las bludgers que estén en juego actualizando sus
//posiciones en la estructura de juego
void mover_bludgers(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t *juego);

//precondiciones:-
//postcondiciones: devolverá una coordenada que esté a una distancia mayor
//o igual a 5 del centro del campo de juego
coordenada_t posicion_inicial_snitch();

//precondiciones:-
//postcondiciones: indica si terminó o no el juego y actualiza las variables
//que indican la razón de la finalización del juego
bool finalizo_juego(juego_t *juego);

//precondiciones:-
//postcondiciones: imprimirá por pantalla la razón por la que finalizó el juego
void mostrar_resultado(juego_t juego);

#endif /* QUIDDITCH_H */
