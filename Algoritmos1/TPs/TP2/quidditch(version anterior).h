#ifndef QUIDDITCH_H
#define QUIDDITCH_H

#define CANTIDAD_BLUDGERS 5
#define CANTIDAD_DEMENTORES 4
#define CANTIDAD_FILAS 25
#define CANTIDAD_COLUMNAS 15

/* ACA VAN LAS CONSTANTES */

typedef struct coordenada {
	int fila;
	int columna;
} coordenada_t;

typedef struct juego {
	coordenada_t posicion_jugador;
	char casa;
	int resistencia;
	coordenada_t posicion_snitch;
	coordenada_t posicion_bludgers[CANTIDAD_BLUDGERS];
	char direccion; // 'D': derecha – 'I': izquierda
	coordenada_t posicion_dementores[CANTIDAD_DEMENTORES];
	int estado; // 0: en ejecucion – 1: jugador gano – 2: jugador perdio
} juego_t;

/*
 * ACA VAN LAS PRE Y POST CONDICIONES DE inicializar_juego
 */
void inicializar_juego(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], char casa, juego_t *juego);

/*
 * ACA VAN LAS PRE Y POST CONDICIONES DE pedir_movimiento
 */
char pedir_movimiento(coordenada_t posicion_jugador);

/*
 * ACA VAN LAS PRE Y POST CONDICIONES DE pedir_movimiento
 */
void mover_jugador(char campo[/* UNA CONSTANTE */][/* UNA CONSTANTE */], char direccion, juego_t *juego);

/*
 * ACA VAN LAS PRE Y POST CONDICIONES DE pedir_movimiento
 */
void mover_snitch(char campo[/* UNA CONSTANTE */][/* UNA CONSTANTE */], juego_t *juego);

/*
 * ACA VAN LAS PRE Y POST CONDICIONES DE pedir_movimiento
 */
void mover_bludgers(char campo[/* UNA CONSTANTE */][/* UNA CONSTANTE */], juego_t *juego);

/*
 * ACA VAN LAS PRE Y POST CONDICIONES DE pedir_movimiento
 */
coordenada_t posicion_inicial_snitch();

/*
 * ACA VAN LAS PRE Y POST CONDICIONES DE pedir_movimiento
 */
bool finalizo_juego(juego_t *juego);

/*
 * ACA VAN LAS PRE Y POST CONDICIONES DE pedir_movimiento
 */
void mostrar_resultado(juego_t juego);

#endif /* QUIDDITCH_H */
