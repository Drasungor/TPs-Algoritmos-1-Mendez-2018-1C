
#include "quidditch.h"

#define BLUDGER_1 0
#define ULTIMA_COLUMNA_CAMPO 14
#define PRIMERA_COLUMNA_CAMPO 0
#define ULTIMA_FILA_CAMPO 24
#define PRIMERA_FILA_CAMPO 0
#define CANTIDAD_DESPLAZAMIENTOS_POSIBLES_DE_SNITCH 4
#define NO_HAY_CHOQUE -1
#define REDUCCION_RESISTENCIA_POR_CHOQUE 10
#define DISTANCIA_ENTRE_BLUDGERS 5
#define NO_HAY_ELEMENTOS 0
#define ADICION_DERECHA_BLUDGERS 1
#define ADICION_IZQUIERDA_BLUDGERS -1

//tipo de dato usado para asociar la posicion
//valida a su distancia del jugador
typedef struct movimiento_valido {
  coordenada_t posicion;
  int distancia_del_jugador;

}movimiento_valido_t;


//precondiciones:-
//postcondiciones: remplaza todos los elementos de la matriz por ESPACIO_VACIO
void limpiar_matriz(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]){
  for (int i = 0; i < CANTIDAD_FILAS; i++) {
    for (int j = 0; j < CANTIDAD_COLUMNAS; j++) {
      campo[i][j]=ESPACIO_VACIO;
    }
  }
}


//precondiciones:-
//postcondiciones: indica si las coordenadas enviadas son las mismas
bool posiciones_son_iguales(coordenada_t coordenada1, coordenada_t coordenada2){

  bool coordenadas_son_iguales=false;

  if ((coordenada1.fila==coordenada2.fila)&&(coordenada1.columna==coordenada2.columna)) {
    coordenadas_son_iguales=true;
  }
  return coordenadas_son_iguales;
}

//precondiciones:-
//devuelve cuánto avanza la bludger en cada turno (1 o -1)
//y cambia el estado de juego si es necesario
int determinar_sentido_bludgers(juego_t* juego) {

  int adicion_posicion_bludger;

  if ((*juego).bludgers_en_juego>NO_HAY_ELEMENTOS) {

    if ((*juego).posicion_bludgers[BLUDGER_1].columna==ULTIMA_COLUMNA_CAMPO) {
      (*juego).direccion=HACIA_IZQUIERDA;
    }

    if ((*juego).posicion_bludgers[BLUDGER_1].columna==PRIMERA_COLUMNA_CAMPO) {
      (*juego).direccion=HACIA_DERECHA;
    }
  }

  if ((*juego).direccion==HACIA_IZQUIERDA) {
    adicion_posicion_bludger=ADICION_IZQUIERDA_BLUDGERS;
  }

  if ((*juego).direccion==HACIA_DERECHA) {
    adicion_posicion_bludger=ADICION_DERECHA_BLUDGERS;
  }

  return adicion_posicion_bludger;
}



//precondicion: los valores que recibe deben ser positivos
//postcondicion: devuelve un entero que representa la distancia
//entre las dos pociciones
int calcular_distancia_manhattan(coordenada_t posicion1, coordenada_t posicion2){

  int distancia_filas=posicion2.fila-posicion1.fila;
  int distancia_columnas=posicion2.columna-posicion1.columna;
  int distancia_total=0;

  //se aplica el modulo a las distancias para que sean siempre positivas
  if (distancia_filas<0) {
    distancia_filas=-distancia_filas;
  }

  if (distancia_columnas<0) {
    distancia_columnas=-distancia_columnas;
  }

  distancia_total=distancia_filas+distancia_columnas;
  return distancia_total;
}



//devuelve por referencia los dos movimientos cuyas posiciones
//tienen asociadas las dos mayores distancias
void determinar_movimientos_mas_distantes(movimiento_valido_t movimientos[] ,movimiento_valido_t* movimiento_mas_distante, movimiento_valido_t* segundo_movimiento_mas_distante, int tope_movimientos) {

  (*movimiento_mas_distante)=movimientos[0];

  if (tope_movimientos>1) {
    (*segundo_movimiento_mas_distante)=movimientos[1];

    //se ve cuál es el movimiento que tiene asociada la mayor distancia
    for (int i = 1; i < tope_movimientos; i++) {
      if (movimientos[i].distancia_del_jugador>(*movimiento_mas_distante).distancia_del_jugador) {
        (*segundo_movimiento_mas_distante)=(*movimiento_mas_distante);
        (*movimiento_mas_distante)=movimientos[i];
      }else if(movimientos[i].distancia_del_jugador>(*segundo_movimiento_mas_distante).distancia_del_jugador){
        (*segundo_movimiento_mas_distante)=movimientos[i];
      }
    }
  }
}

//precondición:el tope debe ser menor o igual a la máxima cantidad de elementos del vector
// y mayor o igual a 0
void eliminar_elemento(coordenada_t obstaculos[], int posicion_elemento, int* tope){

  for (int i = posicion_elemento; i < (*tope)-1; i++) {
    obstaculos[i]=obstaculos[i+1];
  }
  (*tope)-=1;
}

//precondicion: las posiciones de las bludgers y la posicion del jugador deben
//estar inicializadas
//postcondición: devuelve el índice del obstáculo que haya chocado al jugador,
//si no hubo choque entonces devuelve -1
int elemento_que_choca_jugador(juego_t juego, coordenada_t posiciones_obstaculos[], int tope_obstaculos){

  bool hay_choque=false;
  int elemento_chocado=0;


  for (int i = 0; i < tope_obstaculos; i++) {
    if (posiciones_son_iguales(juego.posicion_jugador, posiciones_obstaculos[i])) {
      hay_choque=true;
      elemento_chocado=i;
    }
  }

  if (!hay_choque){
    return NO_HAY_CHOQUE;
  }

  return elemento_chocado;
}



//se fija si se dan las condiciones necesarias para que se presente un
//choque con una bludger y si se presenta actúa según las reglas del juego
void analizar_choque_con_bludger(juego_t* juego) {

  int bludger_chocada=0;

  if ((*juego).casa!=SLYTHERIN) {
    if (elemento_que_choca_jugador(*juego, (*juego).posicion_bludgers, (*juego).bludgers_en_juego)!=NO_HAY_CHOQUE) {
      bludger_chocada=elemento_que_choca_jugador(*juego, (*juego).posicion_bludgers, (*juego).bludgers_en_juego);
      (*juego).resistencia-=REDUCCION_RESISTENCIA_POR_CHOQUE;
      eliminar_elemento((*juego).posicion_bludgers, bludger_chocada, &((*juego).bludgers_en_juego));
    }
  }
}



//se fija si se dan las condiciones necesarias para que se presente un
//choque con un dementor y si se presenta actúa según las reglas del juego
void analizar_choque_con_dementor(juego_t* juego) {

  int dementor_chocado=0;

  if (elemento_que_choca_jugador(*juego, (*juego).posicion_dementores, (*juego).dementores_en_juego)!=NO_HAY_CHOQUE) {
    if ((*juego).casa==GRYFFINDOR) {
      dementor_chocado=elemento_que_choca_jugador(*juego, (*juego).posicion_dementores, (*juego).dementores_en_juego);
      eliminar_elemento((*juego).posicion_dementores, dementor_chocado, &((*juego).dementores_en_juego));
    }else{
      (*juego).resistencia=RESISTENCIA_MINIMA;
    }
  }

}



//precondición: las posiciones deben pertenecer a movimientos válidos
// ya que si no lo son puede devolver una posición no permitida
//postcondición: indica la posición que priorizará la snitch de las dos enviadas
coordenada_t determinar_posicion_prioritaria(coordenada_t posicion1, coordenada_t posicion2){

  coordenada_t posicion_prioritaria;

  if (posicion1.fila<posicion2.fila) {
    posicion_prioritaria=posicion1;
  }else if (posicion1.fila>posicion2.fila) {
    posicion_prioritaria=posicion2;
  }else{
    if (posicion1.columna<posicion2.columna) {
      posicion_prioritaria=posicion1;
    }else{
      posicion_prioritaria=posicion2;
    }
  }

  return posicion_prioritaria;
}



//si la posicion enviada está fuera de la matriz campo,
//la mete adentro de este
void introducir_dentro_del_campo(coordenada_t* posicion_objeto){

  if ((*posicion_objeto).fila<PRIMERA_FILA_CAMPO) {
    (*posicion_objeto).fila=PRIMERA_FILA_CAMPO;
  }

  if ((*posicion_objeto).columna<PRIMERA_COLUMNA_CAMPO) {
    (*posicion_objeto).columna=PRIMERA_COLUMNA_CAMPO;
  }

  if ((*posicion_objeto).fila>ULTIMA_FILA_CAMPO) {
    (*posicion_objeto).fila=ULTIMA_FILA_CAMPO;
  }

  if ((*posicion_objeto).columna>ULTIMA_COLUMNA_CAMPO) {
    (*posicion_objeto).columna=ULTIMA_COLUMNA_CAMPO;
  }
}



//preciondiciones: la posicion del jugador debe estar dentro del campo de juego,
//en adición a esto, la función solo resultará util para el caso en el que el
//jugador pertenezca a ravenclaw (no funcionará erróneamente pero no será de utilidad)
//postcondicion: devuelve un booleano que indica si la posición mandada
//está en las posiciones adyacentes al jugador
bool esta_en_submatriz_ravenclaw(coordenada_t posicion_objeto, juego_t juego){

  bool esta_en_submatriz=false;
  coordenada_t minima_coordenada_submatriz={juego.posicion_jugador.fila-1,juego.posicion_jugador.columna-1};
  coordenada_t maxima_coordenada_submatriz={juego.posicion_jugador.fila+1,juego.posicion_jugador.columna+1};

  introducir_dentro_del_campo(&minima_coordenada_submatriz);
  introducir_dentro_del_campo(&maxima_coordenada_submatriz);

  //se ve si la posicion está dentro de la submatriz
  for (int i= minima_coordenada_submatriz.fila; i <= maxima_coordenada_submatriz.fila; i++) {
    for (int j = minima_coordenada_submatriz.columna; j <= maxima_coordenada_submatriz.columna; j++) {
      if ((posicion_objeto.fila==i)&&(posicion_objeto.columna==j)) {
        esta_en_submatriz=true;
      }
    }
  }

  return esta_en_submatriz;
}



//precondición:recibe en posicion una de las posibles 4 nuevas posiciones posibles de la snitch
//postcondición: devuelve un booleano que indica si esa posicion cumple con las condiciones
//necesarias para que la snitch pueda desplazarse allí
bool es_posicion_valida(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], coordenada_t posicion, juego_t juego){

  bool es_valida=true;

  if (campo[posicion.fila][posicion.columna]!=ESPACIO_VACIO) {
    es_valida=false;
  }

  if ((posicion.fila>ULTIMA_FILA_CAMPO)||(posicion.fila<PRIMERA_FILA_CAMPO)||(posicion.columna>ULTIMA_COLUMNA_CAMPO)||(posicion.columna<PRIMERA_COLUMNA_CAMPO)) {
    es_valida=false;
  }

  if (posiciones_son_iguales(posicion, juego.posicion_jugador)) {
    es_valida=false;
  }

  if (juego.casa==RAVENCLAW) {
    if (esta_en_submatriz_ravenclaw(posicion, juego)) {
      es_valida=false;
    }
  }

  return es_valida;
}



//se fija si un movimiento es valido y en caso de serlo
//lo introduce dentro del vector movimientos_validos_snitch
void establecer_movimientos_validos(movimiento_valido_t movimientos_validos[CANTIDAD_DESPLAZAMIENTOS_POSIBLES_DE_SNITCH], int* tope_movimientos_validos, char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t juego, coordenada_t posicion) {

  if (es_posicion_valida(campo, posicion, juego)) {
    movimientos_validos[*tope_movimientos_validos].posicion=posicion;
    movimientos_validos[*tope_movimientos_validos].distancia_del_jugador=calcular_distancia_manhattan(juego.posicion_jugador, posicion);
    (*tope_movimientos_validos)++;
  }
}



//precondición: los movimientos enviados deben ser los dos que dejen a la snitch
// más lejanos al jugador lo más lejano posible del jugador
//postcondicion: devuelve la coordenada a la que se desplazará la snitch
coordenada_t determinar_posicion_definitiva(movimiento_valido_t movimiento_mas_distante, movimiento_valido_t segundo_movimiento_mas_distante){

  coordenada_t posicion_definitiva;

  if ((movimiento_mas_distante.distancia_del_jugador!=segundo_movimiento_mas_distante.distancia_del_jugador)) {
    posicion_definitiva=movimiento_mas_distante.posicion;
  }

  if (movimiento_mas_distante.distancia_del_jugador==segundo_movimiento_mas_distante.distancia_del_jugador) {
    posicion_definitiva= determinar_posicion_prioritaria(movimiento_mas_distante.posicion, segundo_movimiento_mas_distante.posicion);
  }

  return posicion_definitiva;
}



//precondicion: el movimiento otorgado debe ser un movimiento válido
//y el jugador debe estar dentro del campo de juego
//postcondicion: devuelve si el jugador está o no dentro del campo
//haciendo ese movimiento
bool esta_dentro_del_campo(char movimiento, coordenada_t posicion_jugador){

  bool esta_dentro=true;

  if ((posicion_jugador.fila==ULTIMA_FILA_CAMPO)&&(movimiento==ABAJO)) {
      esta_dentro=false;
  }

  if ((posicion_jugador.fila==PRIMERA_FILA_CAMPO)&&(movimiento==ARRIBA)) {
      esta_dentro=false;
  }

  if ((posicion_jugador.columna==PRIMERA_COLUMNA_CAMPO)&&(movimiento==IZQUIERDA)) {
      esta_dentro=false;
  }

  if ((posicion_jugador.columna==ULTIMA_COLUMNA_CAMPO)&&(movimiento==DERECHA)) {
      esta_dentro=false;
  }

  return esta_dentro;
}



//preciondiciones: -
//postcondicion: devuelve un booleano que indica si es
//una tecla valida(verdadero cuando no está habilitada y
//falso cuando está habilitada)
bool es_tecla_habilitada(char movimiento){

  bool esta_habilitada=true;

  if ((movimiento!=ARRIBA)&&(movimiento!=ABAJO)&&(movimiento!=IZQUIERDA)&&(movimiento!=DERECHA)) {
    esta_habilitada=false;
  }
  return esta_habilitada;
}



void dejar_espacio(){

  for (int i = 0; i < 100; i++) {
    printf("\n");
  }
}



//precondicion: las posiciones de los objetos del juego deben estar dentro de las
//dimensiones del campo
//postcondicion: la matriz tendrá sus elementos cambiados de manera tal que estos
//representen el estado de juego del momento
void actualizar_matriz(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t juego){

  limpiar_matriz(campo);

  //posicionamiento de las bludgers
  for (int i = 0; i < juego.bludgers_en_juego; i++) {
    campo[juego.posicion_bludgers[i].fila][juego.posicion_bludgers[i].columna]=BLUDGER;
  }

  //posicionamiento de la snitch
  campo[juego.posicion_snitch.fila][juego.posicion_snitch.columna]= SNITCH;

  //posicionamiento del jugador
  campo[juego.posicion_jugador.fila][juego.posicion_jugador.columna]= JUGADOR;

  //posicionamiento de los dementores
  for (int i = 0; i < juego.dementores_en_juego; i++) {
    campo[juego.posicion_dementores[i].fila][juego.posicion_dementores[i].columna]= DEMENTOR;
  }
}



void imprimir_matriz(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS]){

  for (int i = 0; i < CANTIDAD_COLUMNAS+2; i++) {
    printf("*");
  }

  printf("\n");

  for (int i = 0; i < CANTIDAD_FILAS; i++) {
    printf("*");
    for (int j = 0; j < CANTIDAD_COLUMNAS; j++) {
      printf("%c", campo[i][j]);
    }
    printf("*\n");
  }

  for (int i = 0; i < CANTIDAD_COLUMNAS+2; i++) {
    printf("*");
  }

  printf("\n");
}



//chequea si se dan las condiciones para que el jugador gane o pierda y
//cambia el estado de juego segun al resultado
void analizar_estado_de_juego(juego_t* juego){

  if (posiciones_son_iguales((*juego).posicion_jugador, (*juego).posicion_snitch)) {
    (*juego).estado=JUGADOR_GANO;
  }

  if ((*juego).casa==RAVENCLAW) {
    if (esta_en_submatriz_ravenclaw((*juego).posicion_snitch,*juego)) {
      (*juego).estado=JUGADOR_GANO;
    }
  }

  if (((*juego).resistencia==RESISTENCIA_MINIMA)&&((*juego).estado!=JUGADOR_GANO)) {
      (*juego).estado=JUGADOR_PERDIO;
  }
}



void inicializar_juego(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], char casa, juego_t *juego){

  int diferencia_entre_filas_dementores= FILA_2_DEMENTORES - FILA_1_DEMENTORES;
  int diferencia_entre_columnas_dementores= COLUMNA_2_DEMENTORES - COLUMNA_1_DEMENTORES;
  int contador_dementores =0;

  (*juego).posicion_jugador.fila= CENTRO_FILAS;
  (*juego).posicion_jugador.columna= CENTRO_COLUMNAS;
  (*juego).resistencia= RESISTENCIA_INICIAL;
  (*juego).casa= casa;

  (*juego).direccion= HACIA_DERECHA;
  (*juego).bludgers_en_juego=  CANTIDAD_INICIAL_BLUDGERS;

  //inicializacion de bludgers
  for (int i = 0; i < CANTIDAD_INICIAL_BLUDGERS; i++) {
    (*juego).posicion_bludgers[i].fila=i*DISTANCIA_ENTRE_BLUDGERS+2;
    (*juego).posicion_bludgers[i].columna= COLUMNA_INICIAL_BLUDGERS;
  }

  (*juego).dementores_en_juego= CANTIDAD_INICIAL_DEMENTORES;

  //inicializacion de dementores
  for (int j = FILA_1_DEMENTORES; j <=FILA_2_DEMENTORES; j+=diferencia_entre_filas_dementores){
    for (int k = COLUMNA_1_DEMENTORES; k <=COLUMNA_2_DEMENTORES; k+=diferencia_entre_columnas_dementores){
      (*juego).posicion_dementores[contador_dementores].fila=j;
      (*juego).posicion_dementores[contador_dementores].columna=k;
      contador_dementores++;
    }
  }

  (*juego).estado=EN_EJECUCION;

  do {
    (*juego).posicion_snitch=posicion_inicial_snitch();
  } while(campo[(*juego).posicion_snitch.fila][(*juego).posicion_snitch.columna]==DEMENTOR);

  actualizar_matriz(campo, *juego);
}



char pedir_movimiento(coordenada_t posicion_jugador){

  char movimiento;

  do {
    printf("Inserte movimiento:");
    scanf(" %c", &movimiento);

    if (!(es_tecla_habilitada(movimiento))) {
      printf("Tecla incorrecta, por favor ingrese 'w', 'a','s' o 'd'.");
    }

    if (!(esta_dentro_del_campo(movimiento, posicion_jugador))) {
      printf("El movimiento lo deja fuera del campo de juego, por favor ingrese otra direccion");
    }
  } while(!(es_tecla_habilitada(movimiento))||(!(esta_dentro_del_campo(movimiento, posicion_jugador)))/*&&(strlen(movimiento)>1)*//*&&(agregar validacion para ver si el movimiento lo deja afuera de la matriz)*/);

  return movimiento;
}



void mover_jugador(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], char direccion, juego_t *juego){

  if (!finalizo_juego(juego)) {

    switch (direccion) {
      case ARRIBA:
      (*juego).posicion_jugador.fila--;
      break;

      case ABAJO:
      (*juego).posicion_jugador.fila++;
      break;

      case IZQUIERDA:
      (*juego).posicion_jugador.columna--;
      break;

      case DERECHA:
      (*juego).posicion_jugador.columna++;
      break;
    }

    (*juego).resistencia--;


    analizar_choque_con_dementor(juego);

    analizar_choque_con_bludger(juego);

    if ((*juego).resistencia<RESISTENCIA_MINIMA) {
      (*juego).resistencia=RESISTENCIA_MINIMA;
    }

    analizar_estado_de_juego(juego);

    actualizar_matriz(campo, *juego);
  }
}



void mover_snitch(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t *juego){

  if (!finalizo_juego(juego)) {

    //se agregan estas variables para que no queden argumenos locales
    //demasiado largos
    movimiento_valido_t movimiento_mas_distante;
    movimiento_valido_t segundo_movimiento_mas_distante;



    coordenada_t coordenadas_snitch= (*juego).posicion_snitch;
    coordenada_t coordenadas_jugador= (*juego).posicion_jugador;

    movimiento_valido_t movimientos_validos_snitch[CANTIDAD_DESPLAZAMIENTOS_POSIBLES_DE_SNITCH];

    int tope_movimientos_validos=0;
    int distancia_jugador_a_snitch=calcular_distancia_manhattan(coordenadas_jugador, coordenadas_snitch);
    coordenada_t coordenada_a_analizar;

    if (distancia_jugador_a_snitch<=DISTANCIA_MAXIMA_JUGADOR_A_SNITCH_CON_MOVIMIENTO) {

      //se buscan los movimientos que la snitch tiene habilitados para realizar
      for (int i = coordenadas_snitch.fila-1; i <= coordenadas_snitch.fila+1; i+=2) {
        for (int j = coordenadas_snitch.columna-1; j <= coordenadas_snitch.columna+1; j+=2) {
          coordenada_a_analizar.fila=i; //{i,j};
          coordenada_a_analizar.columna=j;
          establecer_movimientos_validos(movimientos_validos_snitch, &tope_movimientos_validos, campo, *juego, coordenada_a_analizar);
        }
      }

      if (tope_movimientos_validos>NO_HAY_ELEMENTOS) {

        determinar_movimientos_mas_distantes(movimientos_validos_snitch ,&movimiento_mas_distante, &segundo_movimiento_mas_distante, tope_movimientos_validos);

        (*juego).posicion_snitch=determinar_posicion_definitiva(movimiento_mas_distante, segundo_movimiento_mas_distante);
      }
    }

    actualizar_matriz(campo, *juego);
  }
}



void mover_bludgers(char campo[CANTIDAD_FILAS][CANTIDAD_COLUMNAS], juego_t *juego){

  if (!finalizo_juego(juego)) {

    int adicion_posicion_bludger=determinar_sentido_bludgers(juego);

    for (int i = 0; i < (*juego).bludgers_en_juego; i++) {
      (*juego).posicion_bludgers[i].columna+=adicion_posicion_bludger;
    }

    analizar_choque_con_bludger(juego);

    if ((*juego).resistencia<RESISTENCIA_MINIMA) {
      (*juego).resistencia=RESISTENCIA_MINIMA;
    }

    analizar_estado_de_juego(juego);

    finalizo_juego(juego);

    actualizar_matriz(campo, *juego);
  }
}



coordenada_t posicion_inicial_snitch(){

  coordenada_t centro_del_campo={CENTRO_FILAS, CENTRO_COLUMNAS};
  coordenada_t posicion_inicial;

  srand((unsigned int)clock());

  do {
    posicion_inicial.fila=rand()%ULTIMA_FILA_CAMPO;
    posicion_inicial.columna=rand()%ULTIMA_COLUMNA_CAMPO;
  } while((calcular_distancia_manhattan(posicion_inicial, centro_del_campo)<DISTANCIA_MINIMA_INICIAL_SNITCH_A_JUGADOR));

  return posicion_inicial;
}



bool finalizo_juego(juego_t *juego){

  bool termino_juego=false;

  if ((*juego).estado!=EN_EJECUCION) {
      termino_juego=true;
  }

  return termino_juego;
}



void mostrar_resultado(juego_t juego){

  if (juego.estado==JUGADOR_PERDIO) {
    printf("Perdio, se acabó la resistencia\n");
  }

  if (juego.estado==JUGADOR_GANO) {
    printf("Gano, pudo atrapar la snitch\n");
  }
}
