#include<stdio.h>
#include<stdbool.h>
#include<string.h>

typedef struct alumno {
  char padron[9];
  char nombre[33];
  char casa[17];
  int anio;
  int puntos;
} alumno_t;

int main(int argc, char const *argv[]) {

  alumno_t alumno_a_introducir;
  alumno_t ultimo_alumno;

  char ingresar_otro_alumno = 'y';
  FILE* alumnos = fopen(argv[1], "a+");

  if (!alumnos) {
    return 0;
  }

  FILE* otro_alumnos=fopen("otro_alumnos", "r");

  strcpy(ultimo_alumno.padron, "aaaa1111");
  strcpy(ultimo_alumno.nombre, "Prueba1");
  strcpy(ultimo_alumno.casa, "Gryffindor");
  ultimo_alumno.anio=1;
  ultimo_alumno.puntos=0;

  fwrite(&ultimo_alumno, sizeof(alumno_t), 1, alumnos);

  strcpy(ultimo_alumno.padron, "aaaa1112");
  strcpy(ultimo_alumno.nombre, "Prueba2");
  strcpy(ultimo_alumno.casa, "Gryffindor");
  ultimo_alumno.anio=1;
  ultimo_alumno.puntos=0;

  //fseek(alumnos, -(int)sizeof(alumno_t), SEEK_END);


  fwrite(&ultimo_alumno, sizeof(alumno_t), 1, alumnos);

/*
  if (fread(&ultimo_alumno, sizeof(alumno_t), 1, alumnos)!=1) {

    if (fwrite(&ultimo_alumno, sizeof(alumno_t), 1, alumnos)!=1) {
      printf("No pude introducir el primer elemento\n");
    }
  }
*/
/*

  while (ingresar_otro_alumno == 'y') {

    fseek(alumnos, -(int)sizeof(alumno_t), SEEK_END);
    fread(&ultimo_alumno, sizeof(alumno_t), 1, alumnos);

    do {
      printf("Casa del alumno: ");
      scanf(" %[^\n]", alumno_a_introducir.casa);
    } while(strcmp(alumno_a_introducir.casa, ultimo_alumno.casa)<0);

    do {
      printf("Anio del alumno: ");
      scanf(" %d", &(alumno_a_introducir.anio));
    } while(alumno_a_introducir.anio<ultimo_alumno.anio);

    do {
      printf("\n\nPadron del alumno: ");
      scanf(" %[^\n]", alumno_a_introducir.padron);
    } while(strcmp(alumno_a_introducir.padron, ultimo_alumno.padron)<0);


    printf("Nombre del alumno: ");
    scanf(" %[^\n]", alumno_a_introducir.nombre);

    printf("Puntos del alumno: ");
    scanf(" %d", &(alumno_a_introducir.puntos));

    fwrite(&alumno_a_introducir, sizeof(alumno_t), 1, alumnos);

    printf("Desea ingresar otro alumno (y/n)? ");
    scanf(" %c", &ingresar_otro_alumno);
    fgetc(stdin);
  }
  */

  fseek(alumnos, 0, SEEK_SET);

  while (!feof(otro_alumnos)) {

    fread(&alumno_a_introducir, sizeof(alumno_t), 1, otro_alumnos);

    printf("Nombre del alumno: %s\n", alumno_a_introducir.nombre);
    printf("Puntos del alumno: %d\n", alumno_a_introducir.puntos);
    printf("Padron del alumno: %s\n", alumno_a_introducir.padron);
    printf("Anio del alumno: %d\n", alumno_a_introducir.anio);
    printf("Casa del alumno: %s\n", alumno_a_introducir.casa);
    printf("\n\n\n\n\n\n");
  }

  fclose(otro_alumnos);
  fclose(alumnos);
  return 0;
}
