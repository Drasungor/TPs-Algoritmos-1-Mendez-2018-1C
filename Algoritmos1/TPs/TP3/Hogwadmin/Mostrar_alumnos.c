#include <stdio.h>


#define MAXIMO_ELEMENTOS_PADRON 9
#define MAXIMO_ELEMENTOS_COMENTARIOS 257
#define MAXIMO_ELEMENTOS_NOMBRE 33
#define MAXIMO_ELEMENTOS_CASA 17


typedef struct alumno{
  char padron[MAXIMO_ELEMENTOS_PADRON];
  char nombre[MAXIMO_ELEMENTOS_NOMBRE];
  char casa[MAXIMO_ELEMENTOS_CASA];
  int anio_de_cursada;
  int puntos_obtenidos;
}alumno_t;

int main(int argc, char const *argv[]) {

  alumno_t alumno_a_leer;
  int alumnos_leidos;

  if (argc!=2) {
      printf("Metiste mal los argumentos\n");
      return 0;
  }

  FILE* alumnos = fopen(argv[1], "r");

  if (!alumnos) {
    printf("Error al abrir el archivo\n");
    return 0;
  }

  alumnos_leidos=fread(&alumno_a_leer, sizeof(alumno_t), 1, alumnos);

  while (!feof(alumnos)/*alumnos_leidos==1*/) {


    printf("Nombre del alumno: %s\n", alumno_a_leer.nombre);
    printf("Puntos del alumno: %d\n", alumno_a_leer.puntos_obtenidos);
    printf("Padron del alumno: %s\n", alumno_a_leer.padron);
    printf("Anio del alumno: %d\n", alumno_a_leer.anio_de_cursada);
    printf("Casa del alumno: %s\n", alumno_a_leer.casa);
    printf("\n\n\n\n\n\n");

    alumnos_leidos=fread(&alumno_a_leer, sizeof(alumno_t), 1, alumnos);
  }
  /*
  printf("Nombre del alumno: %s\n", alumno_a_leer.nombre);
  printf("Puntos del alumno: %d\n", alumno_a_leer.puntos_obtenidos);
  printf("Padron del alumno: %s\n", alumno_a_leer.padron);
  printf("Anio del alumno: %d\n", alumno_a_leer.anio_de_cursada);
  printf("Casa del alumno: %s\n", alumno_a_leer.casa);
  */

  fclose(alumnos);



  return 0;
}
