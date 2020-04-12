#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "admin.h"

#define NO_SE_AGREGARON_ARGUMENTOS 1
#define COMANDO 1

#define ARGUMENTOS_LIMPIAR 4
#define ARGUMENTOS_ACTUALIZAR 4
#define ARGUMENTOS_APLICAR 4
#define ARGUMENTOS_RESUMIR 3

#define ALUMNOS_ANIO_ANTERIOR 2
#define ALUMNOS_ANIO_ACTUAL 3
#define INGRESANTES 3
#define BITACORA 3

#define MINIMO_VALOR_QUE_NO_INDICA_ERROR 0

//precondiciones:-
//postcondiciones: si el valor pasado a la funcion esta indicando
//un error, imprime por pantalla el error indicado
void indicar_error(int valor_a_evaluar){

  bool hubo_error=true;

  switch (valor_a_evaluar) {
    case NO_SE_ABRIO_EL_PRIMER_ARCHIVO:
    printf("Hubo un error al abrir el primer archivo\n");
    break;

    case NO_SE_ABRIO_EL_SEGUNDO_ARCHIVO:
    printf("Hubo un error al abrir el segundo archivo\n");
    break;

    case NO_SE_CREO_EL_ARCHIVO:
    printf("Hubo un error al crear el archivo de alumnos\n");
    break;

    case NO_SE_ELIMINO_EL_ARCHIVO:
    printf("Hubo un error al eliminar un archivo\n");
    break;

    case NO_SE_RENOMBRO_ARCHIVO:
    printf("Hubo un error al renombrar uno de los archivo\n");
    break;

    case NO_SE_CREO_EL_AUXILIAR:
    printf("Hubo un error al crear el archivo auxiliar\n");
    break;

    case EL_ARCHIVO_ESTA_VACIO:
    printf("El archivo de alumnos se encuentra vacio\n");
    break;

    default:
    hubo_error=false;
    break;
  }

  if (hubo_error) {
      printf("Escriba ./hogwadmin ayuda para ver el uso de los comandos\n");
  }

}


//precondiciones:-
//postcondiciones: le informa al usuario que ingreso una cantidad
//erronea de argumentos para el comando escrito y recomienda el comando ayuda
void indicar_cantidad_erronea_de_argumentos() {
  printf("Ingreso una cantidad erronea de argumentos, ejecute nuevamente el programa " );
  printf("con el argumento %s para ver el uso correcto del comando\n", COMANDO_AYUDA);
}

//precondiciones:-
//postcondiciones:imprime por pantalla el objetivo del comando y como debe invocarse
void informar_sobre_limpiar() {
  printf("%s: recibe como argumentos el archivo de datos del anio anterior y la", COMANDO_LIMPIAR);
  printf("ruta del archivo que se quiere generar para el anio (en ese orden), ");
  printf("remueve a los alumnos del anio egresado  e incrementa en 1 el anio de todos los ");
  printf("demas alumnos en la carrera, ademas deja en 0 los puntos acumulados del anio anterior\n");
  printf("Para invocar el comando debera escribir ./hogwadmin %s ", COMANDO_LIMPIAR);
  printf("ruta_archivo_a_limpiar ruta_archivo_limpio\n\n");
}

//precondiciones:-
//postcondiciones:imprime por pantalla el objetivo del comando y como debe invocarse
void informar_sobre_actualizar() {
  printf("%s: recibe como argumentos el archivo de alumnos a usar durante el anio ", COMANDO_ACTUALIZAR);
  printf("y el archivo en el que se encuentran los alumnos que ingresan este anio, incorpora ");
  printf("los ingresantes (que tendran puntaje 0) en el registro de alumnos\n");
  printf("Para invocar el comando debera escribir ./hogwadmin %s ", COMANDO_ACTUALIZAR);
  printf("ruta_archivo_de_alumnos ruta_archivo_de_ingresos\n\n");
}

//precondiciones:-
//postcondiciones:imprime por pantalla el objetivo del comando y como debe invocarse
void informar_sobre_aplicar() {
  printf("%s: recibe como argumentos el archivo de alumnos a usar durante el anio ", COMANDO_APLICAR);
  printf("y la bitacora, es decir, el archivo que contiene los puntos obtenidos por los alumnos ");
  printf("a lo largo del tiempo, modifica el archivo de alumnos con los puntos acumulados por cada alumno\n");
  printf("Para invocar el comando debera escribir ./hogwadmin %s ", COMANDO_APLICAR);
  printf("ruta_archivo_de_alumnos ruta_archivo_bitacora\n\n");
}

//precondiciones:-
//postcondiciones:imprime por pantalla el objetivo del comando y como debe invocarse
void informar_sobre_resumir() {
  printf("%s: recibe como argumento el archivo de alumnos a usar durante el anio, ", COMANDO_RESUMIR);
  printf("muestra por anio y por casa los puntos obtenidos y un resumen con el nombre de la casa ");
  printf("ganadora y su puntaje obtenido, junto con el alumno que mas puntos sumo para esa casa y su puntaje\n");
  printf("Para invocar el comando debera escribir ./hogwadmin %s ruta_archivo_de_alumnos\n\n", COMANDO_RESUMIR);
}

//precondiciones:-
//postcondiciones:imprime por pantalla el objetivo del comando y como debe invocarse
void informar_sobre_ayuda() {
  printf("%s: no tiene argumentos, muestra todos los comandos que puede recibir el ", COMANDO_AYUDA);
  printf("programa, como se los invoca, argumentos que requieren, y su funcion\n");
  printf("Para invocar el comando debera escribir ./hogwadmin %s\n\n", COMANDO_AYUDA);
}



int main(int argc, char const *argv[]) {


  if (argc==NO_SE_AGREGARON_ARGUMENTOS) {
    printf("Debe ingresar algun argumento\n");
    return ARGUMENTOS_INSUFICIENTES;
  }

  if (!strcmp((char*)argv[COMANDO], COMANDO_LIMPIAR)) {
    if (argc!=ARGUMENTOS_LIMPIAR) {
      indicar_cantidad_erronea_de_argumentos();
      return ARGUMENTOS_INSUFICIENTES;
    }


    int alumnos_pasados=pasar_de_anio((char*)argv[ALUMNOS_ANIO_ANTERIOR],(char*)argv[ALUMNOS_ANIO_ACTUAL]);

    if (alumnos_pasados<MINIMO_VALOR_QUE_NO_INDICA_ERROR) {
      indicar_error(alumnos_pasados);
      return alumnos_pasados;
    }

  }else if(!strcmp(argv[COMANDO], COMANDO_ACTUALIZAR)){

    if (argc!=ARGUMENTOS_ACTUALIZAR) {
      indicar_cantidad_erronea_de_argumentos();
      return ARGUMENTOS_INSUFICIENTES;
    }


    int ingresantes=actualizar_alumnos((char*)argv[ALUMNOS_ANIO_ANTERIOR], (char*)argv[INGRESANTES]);

    if (ingresantes<MINIMO_VALOR_QUE_NO_INDICA_ERROR) {
      indicar_error(ingresantes);
      return ingresantes;
    }

  }else if(!strcmp(argv[COMANDO], COMANDO_APLICAR)){

    if (argc!=ARGUMENTOS_APLICAR) {
      indicar_cantidad_erronea_de_argumentos();
      return ARGUMENTOS_INSUFICIENTES;
    }


    int bitacoras_procesadas=aplicar((char*)argv[ALUMNOS_ANIO_ANTERIOR], (char*)argv[BITACORA]);


    if (bitacoras_procesadas<MINIMO_VALOR_QUE_NO_INDICA_ERROR) {
      indicar_error(bitacoras_procesadas);
      return bitacoras_procesadas;
    }

  }else if(!strcmp(argv[COMANDO], COMANDO_RESUMIR)){

    if (argc!=ARGUMENTOS_RESUMIR) {
      indicar_cantidad_erronea_de_argumentos();
      return ARGUMENTOS_INSUFICIENTES;
    }

    resumir_puntos((char*)argv[ALUMNOS_ANIO_ANTERIOR], stdout);

  }else if(!strcmp(argv[COMANDO], COMANDO_AYUDA)){

    printf("\nUsted puede utilizar el programa con los siguientes argumentos:\n\n");

    informar_sobre_limpiar();

    informar_sobre_actualizar();

    informar_sobre_aplicar();

    informar_sobre_resumir();

    informar_sobre_ayuda();

  }else{
    printf("Ingreso un comando inexistente, ejecute nuevamente el programa con el comando %s ", COMANDO_AYUDA);
    printf("para ver el uso correcto del programa\n");
  }


  return 0;
}
