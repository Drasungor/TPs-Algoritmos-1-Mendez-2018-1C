#include <stdio.h>
#include <string.h>


#define MAXIMO_ELEMENTOS_PADRON 9
#define MAXIMO_ELEMENTOS_COMENTARIOS 257
#define MAXIMO_ELEMENTOS_NOMBRE 33
#define MAXIMO_ELEMENTOS_CASA 17
#define CANTIDAD_ANIOS_DE_CURSADA 7
#define MAXIMO_ELEMENTOS_FECHA 11

#define OPERACION_EXITOSA 1
#define NO_SE_ABRIO_EL_ARCHIVO -1
#define NO_SE_OBTUVO_ELEMENTO -2
#define ARGUMENTOS_INSUFICIENTES -3// CAMBIAR NOMBRE
#define NO_SE_INSCRIBIO_ELEMENTO -4
#define NO_SE_CREO_EL_ARCHIVO -4
#define NO_SE_ELIMINO_EL_ARCHIVO -5
#define NO_SE_RENOMBRO_ARCHIVO -6

#define FORMATO_INGRESOS " %[^;];%[^;];%[^;];%d"
#define FORMATO_BITACORA " %[^;];%[^;];%d;%[^\n]\n"

#define ELEMENTOS_POR_ALUMNO_NUEVO 4
#define ELEMENTOS_POR_ENTRADA_BITACORA 4

#define  CANTIDAD_CASAS 4

#define COMANDO_LIMPIAR "limpiar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_APLICAR "aplicar"
#define COMANDO_RESUMIR "resumir"
#define  COMANDO_AYUDA "ayuda"

#define AUXILIAR_ALUMNOS "nuevo_alumnos"

#define NO_TIENE_PUNTOS 0

typedef struct alumno{
  char padron[MAXIMO_ELEMENTOS_PADRON];
  char nombre[MAXIMO_ELEMENTOS_NOMBRE];
  char casa[MAXIMO_ELEMENTOS_CASA];
  int anio_de_cursada;
  int puntos_obtenidos;
}alumno_t;


int main(int argc, char const *argv[]) {

  int elementos_obtenidos=0;

  alumno_t alumno_a_introducir;

  FILE* ingresos=fopen("../Ingresos.txt", "r");

  if (!ingresos) {
    printf("No pude abrir ingresos\n");
    return 0;
  }

  elementos_obtenidos=fscanf(ingresos, FORMATO_INGRESOS, alumno_a_introducir.padron, alumno_a_introducir.nombre, alumno_a_introducir.casa, &(alumno_a_introducir.anio_de_cursada));


  while ((elementos_obtenidos==4)&&(!feof(ingresos))) {

    alumno_a_introducir.puntos_obtenidos=0;

    printf("Nombre del alumno: %s\n", alumno_a_introducir.nombre);
    printf("Puntos del alumno: %d\n", alumno_a_introducir.puntos_obtenidos);
    printf("Padron del alumno: %s\n", alumno_a_introducir.padron);
    printf("Anio del alumno: %d\n", alumno_a_introducir.anio_de_cursada);
    printf("Casa del alumno: %s\n", alumno_a_introducir.casa);
    printf("\n\n\n\n\n\n");

    elementos_obtenidos=fscanf(ingresos, FORMATO_INGRESOS, alumno_a_introducir.padron, alumno_a_introducir.nombre, alumno_a_introducir.casa, &(alumno_a_introducir.anio_de_cursada));
  }

  printf("Nombre del alumno: %s\n", alumno_a_introducir.nombre);
  printf("Puntos del alumno: %d\n", alumno_a_introducir.puntos_obtenidos);
  printf("Padron del alumno: %s\n", alumno_a_introducir.padron);
  printf("Anio del alumno: %d\n", alumno_a_introducir.anio_de_cursada);
  printf("Casa del alumno: %s\n", alumno_a_introducir.casa);
  printf("\n\n\n\n\n\n");

  //elementos_obtenidos=fscanf(ingresos, FORMATO_INGRESOS, alumno_a_introducir.padron, alumno_a_introducir.nombre, alumno_a_introducir.casa, &(alumno_a_introducir.anio_de_cursada));

  fclose(ingresos);

  return 0;
}
