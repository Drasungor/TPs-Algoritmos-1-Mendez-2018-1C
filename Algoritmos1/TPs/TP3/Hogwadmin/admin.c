#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "admin.h"



#define SE_OBTUVO_UN_ELEMENTO 1
#define UN_ALUMNO 1
#define CADENAS_SON_IGUALES 0

char const *CASAS[CANTIDAD_CASAS]={"Gryffindor", "Hufflepuff", "Ravenclaw", "Slytherin"};

//tipo de dato que almacena toda la informacion dada por una entrada de
//la bitacora
typedef struct entrada_bitacora{
  char padron[MAXIMO_ELEMENTOS_PADRON];
  char fecha[MAXIMO_ELEMENTOS_FECHA];
  int puntos;
  char comentario[MAXIMO_ELEMENTOS_COMENTARIOS];
}entrada_bitacora_t;



//precondiciones:-
//postcondiciones: inicializa las casas y los puntos de los mejores alumnos
// de hogwarts
void inicializar_mejores_alumnos(alumno_t mejores_alumnos[CANTIDAD_CASAS]){

  for (int i = 0; i < CANTIDAD_CASAS; i++) {
    strcpy(mejores_alumnos[i].casa, CASAS[i]);
    mejores_alumnos[i].puntos_obtenidos=0;
  }
}



//precondiciones:-
//postcondiciones: se devuelve un booleano que indica si los alumnos evaluados
//pertenecen a la misma casa
bool pertenecen_a_la_misma_casa(alumno_t alumno1, alumno_t alumno2){

  bool tienen_la_misma_casa=false;

  if (!strcmp(alumno1.casa, alumno2.casa)) {
    tienen_la_misma_casa=true;
  }

  return tienen_la_misma_casa;
}


//precondiciones:-
//postcondiciones: se devuelve un booleano que indica si los alumnos evaluados
//pertenecen a la misma casa y anio
bool pertenecen_a_la_misma_casa_y_anio(alumno_t alumno1, alumno_t alumno2){

  bool tienen_la_misma_casa_y_anio=true;

  if (!pertenecen_a_la_misma_casa(alumno1, alumno2)) {
    tienen_la_misma_casa_y_anio=false;
  }

  if (alumno1.anio_de_cursada!=alumno2.anio_de_cursada) {
    tienen_la_misma_casa_y_anio=false;
  }

  return tienen_la_misma_casa_y_anio;

}



//precondiciones:-
//postcondiciones: si los puntos de la casa enviados son mayores que los de la casa
//que va ganando, le asigna a la casa ganadora el nombre de la casa evaluada
void calcular_casa_ganadora(resumen_casa_t* casa_ganadora, unsigned long puntaje_casa, alumno_t alumno_anterior){

  if (puntaje_casa>(*casa_ganadora).puntos_casa) {
      strcpy((*casa_ganadora).casa, alumno_anterior.casa);
      (*casa_ganadora).puntos_casa=puntaje_casa;
  }

}



//precondiciones:-
//postcondiciones:introduce en la informacion de la casa ganadora el padron y los puntos del
//mejor alumno que pertenece a esa casa
void asignar_mejor_alumno(resumen_casa_t* casa_ganadora, alumno_t mejores_alumnos[CANTIDAD_CASAS]) {

  for (int i = 0; i < CANTIDAD_CASAS; i++) {

    if (!strcmp(mejores_alumnos[i].casa, (*casa_ganadora).casa)) {
      strcpy((*casa_ganadora).padron, mejores_alumnos[i].padron);
      (*casa_ganadora).puntos_alumno= (unsigned long)mejores_alumnos[i].puntos_obtenidos;
    }
  }

}



//precondiciones:-
//postcondiciones: introduce en el canal de impresion los valores de los
//atributos que posee la casa ganadora
void informar_sobre_casa_ganadora(FILE* canal_impresion, resumen_casa_t casa_ganadora){
  fprintf(canal_impresion, "La casa ganadora es: %s\n", casa_ganadora.casa);
  fprintf(canal_impresion, "Puntaje: %lu\n", casa_ganadora.puntos_casa);
  fprintf(canal_impresion, "Alumno con mayor puntaje de la casa: %s\n", casa_ganadora.padron);
  fprintf(canal_impresion, "Puntaje del alumno: %lu\n", casa_ganadora.puntos_alumno);
}



//precondicion: el alumno a copiar debe estar inicializado
//postcondicion: copia los contenidos del alumno a copiar en el
//alumno a modificar
void copiar_alumno(alumno_t* alumno_a_modificar, alumno_t alumno_a_copiar){
  strcpy((*alumno_a_modificar).padron, alumno_a_copiar.padron);
  strcpy((*alumno_a_modificar).nombre, alumno_a_copiar.nombre);
  strcpy((*alumno_a_modificar).casa, alumno_a_copiar.casa);
  (*alumno_a_modificar).anio_de_cursada=alumno_a_copiar.anio_de_cursada;
  (*alumno_a_modificar).puntos_obtenidos=alumno_a_copiar.puntos_obtenidos;
}



//precondiciones:-
//postcondiciones: si el alumno evaluado tiene mas puntos que el mejor alumno hasta el momento
//de la casa a la que pertenece, el alumno evaluado pasa a ser el mejor alumno de su casa
void calcular_mejor_alumno(alumno_t mejores_alumnos[CANTIDAD_CASAS], alumno_t alumno_leido){

  for (int i = 0; i < CANTIDAD_CASAS; i++) {
      if (!strcmp(mejores_alumnos[i].casa, alumno_leido.casa)) {
          if (mejores_alumnos[i].puntos_obtenidos< alumno_leido.puntos_obtenidos) {
            copiar_alumno(&(mejores_alumnos[i]),alumno_leido);
          }
      }
  }

}



//precondiciones: la direccion del archivo a eliminar debe ser valida
//poscondiciones: elimina el archivo que se encuentra en la direccion indicada
//e indica si hubo un error al hacerlo
bool eliminar_archivo(char ruta_archivo_a_eliminar[]){

  bool se_elimino_archivo=false;

  if (!remove(ruta_archivo_a_eliminar)) {
    se_elimino_archivo=true;
  }

  return se_elimino_archivo;
}



//precondiciones: las rutas enviadas deben ser validas
//postcondiciones: cambia la ruta del archivo a la deseada e indica si
//hubo un error al hacerlo
bool renombrar_archivo(char ruta_vieja[], char ruta_nueva[]){

  bool se_renombro_archivo=false;

  if (!rename(ruta_vieja, ruta_nueva)) {
    se_renombro_archivo=true;
  }

  return se_renombro_archivo;
}



//precondiciones: el archivo del cual se quiere obtener un alumno debe existir y sus contenidos
//deben ser variables del tipo alumno_t
//postcondiciones: indica si se pudo leer un alumno y si se da el caso introduce en la variable
//pasada el alumno leido del archivo
bool obtener_alumno(FILE* archivo, alumno_t* alumno_a_obtener){

  int se_obtuvo_alumno=true;
  int cantidad_elementos_obtenidos;

  cantidad_elementos_obtenidos=(int)fread(alumno_a_obtener, sizeof(alumno_t), UN_ALUMNO, archivo);

  if (cantidad_elementos_obtenidos!=UN_ALUMNO) {
    se_obtuvo_alumno=false;
  }

  return se_obtuvo_alumno;
}



//precondiciones:-
//postcondiciones: inscribe un alumno en el archivo indicado
void introducir_alumno(FILE* archivo, alumno_t* alumno_a_inscribir){

  fwrite(alumno_a_inscribir, sizeof(alumno_t), UN_ALUMNO, archivo);

}



//precondiciones:el alumno a inscribir debe estar inicializado
//postcondiciones: pone en 0 los puntos iniciales del alumno que ingresa al colegio
//y lo introduce en nuevo_alumnos
void introducir_ingresante(FILE* nuevo_alumnos, alumno_t alumno_a_inscribir){

  alumno_a_inscribir.puntos_obtenidos=NO_TIENE_PUNTOS;
  introducir_alumno(nuevo_alumnos, &alumno_a_inscribir);
}



//precondiciones:-
//postcondiciones: introduce en el archivo de alunos a usar durante el anio
//(el que tiene los anios actualizados) los alumnos cuyo anio actualizado este
//dentro del rango de cursos de hogwarts (de 1 a 7)
void introducir_alumnos_no_egresados(FILE* informacion_vieja_alumnos, FILE* alumnos_con_anio_actualizado,alumno_t alumno_auxiliar, int* contador_alumnos_pasados) {

  alumno_auxiliar.anio_de_cursada++;

  if (alumno_auxiliar.anio_de_cursada<=CANTIDAD_ANIOS_DE_CURSADA) {
    alumno_auxiliar.puntos_obtenidos=NO_TIENE_PUNTOS;
    //introducir_alumno?
    fwrite(&alumno_auxiliar, sizeof(alumno_t), UN_ALUMNO, alumnos_con_anio_actualizado);
    (*contador_alumnos_pasados)++;
  }

}



//precondiciones:-
//postcondiciones: si el alumno leido coincide con el alumno a actualizar, le suma
//los puntos indicados por la entrada de la bitacora
void sumar_puntos(alumno_t* alumno_leido,entrada_bitacora_t alumno_a_actualizar, int* bitacoras_procesadas) {

  if (!strcmp((*alumno_leido).padron, alumno_a_actualizar.padron)) {
    (*alumno_leido).puntos_obtenidos+=alumno_a_actualizar.puntos;
    (*bitacoras_procesadas)++;
  }

}



//precondiciones: el alumno_leido debe estar inicializado
//postcondiciones: sobreescribe el alumno anterior con la informacion
//del alumno leido
void actualizar_puntos_alumno(FILE* alumnos, alumno_t alumno_leido){

  fseek(alumnos, -(long)sizeof(alumno_t), SEEK_CUR);
  introducir_alumno(alumnos, &alumno_leido);

}



int pasar_de_anio(char* ruta_origen, char* ruta_destino){

  bool se_obtuvo_alumno;
  alumno_t alumno_auxiliar;
  int contador_alumnos_pasados=0;

  //si no existe el archivo de alumnos se crea y se verifica
  //que se haga correctamente, luego se lo abre en el modo
  //en el que se quiere operar
  FILE* informacion_vieja_alumnos=fopen(ruta_origen, "r");

  if (!informacion_vieja_alumnos) {
    informacion_vieja_alumnos=fopen(ruta_origen, "w");

    if (!informacion_vieja_alumnos) {
        return NO_SE_CREO_EL_ARCHIVO;
    }

    fclose(informacion_vieja_alumnos);
    informacion_vieja_alumnos=fopen(ruta_origen, "r");

    if (!informacion_vieja_alumnos) {
        return NO_SE_ABRIO_EL_PRIMER_ARCHIVO;
    }

  }

  FILE* alumnos_con_anio_actualizado=fopen(ruta_destino, "w");

  if (!alumnos_con_anio_actualizado) {
    fclose(informacion_vieja_alumnos);
    return NO_SE_ABRIO_EL_SEGUNDO_ARCHIVO;
  }


  se_obtuvo_alumno=obtener_alumno(informacion_vieja_alumnos, &alumno_auxiliar);

  while (se_obtuvo_alumno) {
    introducir_alumnos_no_egresados(informacion_vieja_alumnos, alumnos_con_anio_actualizado,alumno_auxiliar, &contador_alumnos_pasados);
    se_obtuvo_alumno=obtener_alumno(informacion_vieja_alumnos, &alumno_auxiliar);
  }


  fclose(informacion_vieja_alumnos);
  fclose(alumnos_con_anio_actualizado);

  return contador_alumnos_pasados;
}



int actualizar_alumnos(char* ruta_alumnos, char* ruta_actualizaciones){

  alumno_t alumno_ya_inscripto;
  alumno_t alumno_a_inscribir;

  int elementos_obtenidos=0;
  int alumnos_introducidos=0;
  int se_obtuvo_alumno=0;

  //si no existe el archivo de alumnos se crea y se verifica
  //que se haga correctamente, luego se lo abre en el modo
  //en el que se quiere operar
  FILE* alumnos=fopen(ruta_alumnos, "r");

  if (!alumnos){
    alumnos=fopen(ruta_alumnos, "w");

    if (!alumnos) {
        return NO_SE_CREO_EL_ARCHIVO;
    }

    fclose(alumnos);
    alumnos=fopen(ruta_alumnos, "r");

    if (!alumnos) {
        return NO_SE_ABRIO_EL_PRIMER_ARCHIVO;
    }
  }

  FILE* ingresos=fopen(ruta_actualizaciones, "r");

  if (!ingresos){
    fclose(alumnos);
    return NO_SE_ABRIO_EL_SEGUNDO_ARCHIVO;
  }

  FILE* nuevo_alumnos=fopen(AUXILIAR_ALUMNOS, "w");

  if (!nuevo_alumnos) {
    fclose(alumnos);
    fclose(ingresos);
    return NO_SE_CREO_EL_AUXILIAR;
  }


  elementos_obtenidos=fscanf(ingresos, FORMATO_INGRESOS, alumno_a_inscribir.padron, alumno_a_inscribir.nombre, alumno_a_inscribir.casa, &(alumno_a_inscribir.anio_de_cursada));
  se_obtuvo_alumno=obtener_alumno(alumnos,&alumno_ya_inscripto);

  //se insertan de manera ordenada los elementos de ambos archivos en el archivo auxiliar nuevo_alumnos
  //por casa, anio y padron, en ese orden

  //caso en el que ambos archivos no terminaron
  while ((elementos_obtenidos==ELEMENTOS_POR_ALUMNO_NUEVO)&&(se_obtuvo_alumno)) {

    if (pertenecen_a_la_misma_casa(alumno_ya_inscripto, alumno_a_inscribir)) {

      if (alumno_ya_inscripto.anio_de_cursada==alumno_a_inscribir.anio_de_cursada) {

        if (strcmp(alumno_ya_inscripto.padron, alumno_a_inscribir.padron)<CADENAS_SON_IGUALES) {

          introducir_alumno(nuevo_alumnos, &alumno_ya_inscripto);
          se_obtuvo_alumno=obtener_alumno(alumnos, &alumno_ya_inscripto);

        }else if(strcmp(alumno_ya_inscripto.padron, alumno_a_inscribir.padron)>CADENAS_SON_IGUALES){

          introducir_ingresante(nuevo_alumnos, alumno_a_inscribir);
          alumnos_introducidos++;
          elementos_obtenidos=fscanf(ingresos, FORMATO_INGRESOS, alumno_a_inscribir.padron, alumno_a_inscribir.nombre, alumno_a_inscribir.casa, &(alumno_a_inscribir.anio_de_cursada));

        }

      }else if (alumno_ya_inscripto.anio_de_cursada<alumno_a_inscribir.anio_de_cursada) {

        introducir_alumno(nuevo_alumnos, &alumno_ya_inscripto);
        se_obtuvo_alumno=obtener_alumno(alumnos, &alumno_ya_inscripto);

      }else if (alumno_ya_inscripto.anio_de_cursada>alumno_a_inscribir.anio_de_cursada) {

        introducir_ingresante(nuevo_alumnos, alumno_a_inscribir);
        alumnos_introducidos++;
        elementos_obtenidos=fscanf(ingresos, FORMATO_INGRESOS, alumno_a_inscribir.padron, alumno_a_inscribir.nombre, alumno_a_inscribir.casa, &(alumno_a_inscribir.anio_de_cursada));

      }

    }


    if (strcmp(alumno_ya_inscripto.casa, alumno_a_inscribir.casa)<CADENAS_SON_IGUALES) {
      introducir_alumno(nuevo_alumnos, &alumno_ya_inscripto);
      se_obtuvo_alumno=obtener_alumno(alumnos, &alumno_ya_inscripto);
    }


    if (strcmp(alumno_ya_inscripto.casa, alumno_a_inscribir.casa)>CADENAS_SON_IGUALES) {
      introducir_ingresante(nuevo_alumnos, alumno_a_inscribir);
      alumnos_introducidos++;
      elementos_obtenidos=fscanf(ingresos, FORMATO_INGRESOS, alumno_a_inscribir.padron, alumno_a_inscribir.nombre, alumno_a_inscribir.casa, &(alumno_a_inscribir.anio_de_cursada));
    }

  }

  //caso en el que solo termino el archivo alumnos
  while (elementos_obtenidos==ELEMENTOS_POR_ALUMNO_NUEVO) {
    introducir_ingresante(nuevo_alumnos, alumno_a_inscribir);
    alumnos_introducidos++;
    elementos_obtenidos=fscanf(ingresos, FORMATO_INGRESOS, alumno_a_inscribir.padron, alumno_a_inscribir.nombre, alumno_a_inscribir.casa, &(alumno_a_inscribir.anio_de_cursada));
  }

  //caso en el que solo termino el archivo de ingresantes
  while (se_obtuvo_alumno) {
    introducir_alumno(nuevo_alumnos, &alumno_ya_inscripto);
    se_obtuvo_alumno=obtener_alumno(alumnos, &alumno_ya_inscripto);
  }

  fclose(alumnos);
  fclose(ingresos);
  fclose(nuevo_alumnos);


  //en las siguientes dos funciones se cambia el archivo alumnos
  //por nuevo_alumnos
  if (!eliminar_archivo(ruta_alumnos)) {
      return NO_SE_ELIMINO_EL_ARCHIVO;
  }

  if (!renombrar_archivo(AUXILIAR_ALUMNOS, ruta_alumnos)) {
      return NO_SE_RENOMBRO_ARCHIVO;
  }


  return alumnos_introducidos;
}



int aplicar(char* ruta_alumnos, char* ruta_bitacora){

  bool se_obtuvo_alumno;
  int elementos_obtenidos=0;
  alumno_t alumno_leido;
  entrada_bitacora_t alumno_a_actualizar;
  int bitacoras_procesadas=0;

  //si no existe el archivo de alumnos se crea y se verifica
  //que se haga correctamente
  FILE* alumnos=fopen(ruta_alumnos, "r+");

  if (!alumnos){
    alumnos=fopen(ruta_alumnos, "w+");

    if (!alumnos) {
        return NO_SE_CREO_EL_ARCHIVO;
    }
  }

  FILE* bitacora=fopen(ruta_bitacora, "r");

  if (!bitacora){
    fclose(alumnos);
    return NO_SE_ABRIO_EL_SEGUNDO_ARCHIVO;
  }


  se_obtuvo_alumno=obtener_alumno(alumnos, &alumno_leido);

  if (!se_obtuvo_alumno) {
    fclose(alumnos);
    fclose(bitacora);
    return EL_ARCHIVO_ESTA_VACIO;
  }

  while (se_obtuvo_alumno) {

    elementos_obtenidos=fscanf(bitacora, FORMATO_BITACORA, alumno_a_actualizar.padron, alumno_a_actualizar.fecha, &(alumno_a_actualizar.puntos), alumno_a_actualizar.comentario);

    while (elementos_obtenidos==ELEMENTOS_POR_ENTRADA_BITACORA) {

      sumar_puntos(&alumno_leido, alumno_a_actualizar, &bitacoras_procesadas);

      elementos_obtenidos=fscanf(bitacora, FORMATO_BITACORA, alumno_a_actualizar.padron, alumno_a_actualizar.fecha, &(alumno_a_actualizar.puntos), alumno_a_actualizar.comentario);
    }

    actualizar_puntos_alumno(alumnos, alumno_leido);
    se_obtuvo_alumno=obtener_alumno(alumnos, &alumno_leido);
    rewind(bitacora);
  }


  fclose(alumnos);
  fclose(bitacora);

  return bitacoras_procesadas;
}


resumen_casa_t resumir_puntos(char* ruta_alumnos, FILE* canal_impresion){

  bool se_obtuvo_alumno=false;
  alumno_t alumno_leido;
  alumno_t alumno_anterior;

  resumen_casa_t casa_ganadora;

  int puntaje_casa=0;
  int puntaje_anio=0;


  //vector que contendra el mejor alumno de cada casa
  alumno_t mejores_alumnos[CANTIDAD_CASAS];

  inicializar_mejores_alumnos(mejores_alumnos);


  casa_ganadora.puntos_casa=0;
  casa_ganadora.puntos_alumno=0;



  //si no existe el archivo de alumnos se crea y se verifica
  //que se haga correctamente, luego se lo abre en el modo
  //en el que se quiere operar
  FILE* alumnos=fopen(ruta_alumnos, "r");

  if (!alumnos) {
    alumnos=fopen(ruta_alumnos, "w");
    fclose(alumnos);
    alumnos=fopen(ruta_alumnos, "r");
  }


  se_obtuvo_alumno=obtener_alumno(alumnos, &alumno_leido);


  //se hace un corte de control para imprimir por pantalla los puntos de cada
  //anio de cada casa y los puntos puntos totales de cada casa
  copiar_alumno(&alumno_anterior, alumno_leido);

  while (se_obtuvo_alumno) {

    fprintf(canal_impresion, "%s:\n", alumno_leido.casa);
    copiar_alumno(&alumno_anterior, alumno_leido);

    while ((se_obtuvo_alumno)&&(pertenecen_a_la_misma_casa(alumno_anterior, alumno_leido))) {

      copiar_alumno(&alumno_anterior, alumno_leido);

      while ((se_obtuvo_alumno)&&(pertenecen_a_la_misma_casa_y_anio(alumno_anterior, alumno_leido))) {

        calcular_mejor_alumno(mejores_alumnos, alumno_leido);
        puntaje_anio+=alumno_leido.puntos_obtenidos;
        copiar_alumno(&alumno_anterior, alumno_leido);
        se_obtuvo_alumno=obtener_alumno(alumnos, &alumno_leido);

      }

      fprintf(canal_impresion, "El puntaje del anio %d es: %d\n", alumno_anterior.anio_de_cursada, puntaje_anio);
      puntaje_casa+=puntaje_anio;
      puntaje_anio=0;
    }

    fprintf(canal_impresion, "El puntaje de la casa es: %d\n\n", puntaje_casa);
    calcular_casa_ganadora(&casa_ganadora, (unsigned long)puntaje_casa, alumno_anterior);
    asignar_mejor_alumno(&casa_ganadora, mejores_alumnos);
    puntaje_casa=0;
  }

  informar_sobre_casa_ganadora(canal_impresion, casa_ganadora);
  fclose(alumnos);

  return casa_ganadora;
}
