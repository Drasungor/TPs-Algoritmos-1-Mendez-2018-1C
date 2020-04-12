#include <stdio.h>
#include <stdbool.h>


#define ERROR -1
#define MAXIMO_CARACTERES 100
#define ANIOS_DE_CURSADA_GUARDADOS 5
#define BUSQUEDA_EXITOSA 0
#define CANTIDAD_ALUMNOS 1500
#define MATERIAS_POR_ANIO 4


typedef struct fecha{
  int dia;
  int mes;
  int anio;
}fecha_t;


typedef struct materia{
  char nombre[MAXIMO_CARACTERES];
  float parcial;
  float recuperatorio1;
  float recuperatorio2;
}materia_t;


typedef struct anio_escolar{
  materia_t materias[MATERIAS_POR_ANIO];
  int anio;
}anio_escolar_t;


typedef struct varita{
  char madera[MAXIMO_CARACTERES];
  char nucleo[MAXIMO_CARACTERES];
}varita_t;



typedef struct alumno{
  int id;
  varita_t varita;
  char casa[MAXIMO_CARACTERES];
  char nombre_y_apellido[MAXIMO_CARACTERES];
  anio_escolar_t anios_de_cursada[ANIOS_DE_CURSADA_GUARDADOS];
  char color_de_pelo[MAXIMO_CARACTERES];
  long telefono_de_contacto;
  fecha_t fecha_de_nacimiento;
}alumno_t;


bool obtener_alumno(FILE* archivo, alumno_t* alumno_a_obtener){

  bool pudo_leerse;

  if (fread(alumno_a_obtener, sizeof(alumno_t), 1, archivo)==1) {
      pudo_leerse=true;
  }else{
    pudo_leerse=false;
  }
  return pudo_leerse;
}


int main(int argc, char const *argv[]) {

  alumno_t alumno_a_introducir;
  alumno_t ultimo_alumno;
  alumno_t alumno_a_imrpimir;
  int id = 0;
  int alumnos_a_almacenar;


  FILE* informacion_alumnos=fopen("Base_de_datos_alumnos", "a+");

  if (!informacion_alumnos) {
    printf("Hubo un error\n");
    return ERROR;
  }

  if(fseek(informacion_alumnos, -(long int)sizeof(alumno_t),SEEK_END)==BUSQUEDA_EXITOSA){
    if(obtener_alumno(informacion_alumnos, &ultimo_alumno)){
      id=ultimo_alumno.id;
    }
  }

  do {
    if ((id+alumnos_a_almacenar)>CANTIDAD_ALUMNOS) {
        printf("Quiere ingresar mas alumnos que los enlistados en el colegio,");
        printf("el limite es %d alumnos y por ahora estan almacenados %d\n", CANTIDAD_ALUMNOS, id);
    }

    printf("Ingrese la cantidad de alumnos cuya informacio desea guardar:");
    scanf(" %i", &alumnos_a_almacenar);
  } while((id+alumnos_a_almacenar)>CANTIDAD_ALUMNOS);



  for (int i = 0; i < alumnos_a_almacenar; i++) {
    id++;
    alumno_a_introducir.id=id;

    printf("Nombre y apellido:");
    scanf(" %s", alumno_a_introducir.nombre_y_apellido);

    printf("Casa:");
    scanf(" %s", alumno_a_introducir.casa);

    printf("Madera de la varita:");
    scanf(" %s", alumno_a_introducir.varita.madera);

    printf("Nucleo de la varita:");
    scanf(" %s", alumno_a_introducir.varita.nucleo);

    printf("Color de pelo:");
    scanf(" %s", alumno_a_introducir.color_de_pelo);

    printf("Dia de nacimiento:");
    scanf(" %d", &(alumno_a_introducir.fecha_de_nacimiento.dia));

    printf("Mes de nacimiento:");
    scanf(" %d", &(alumno_a_introducir.fecha_de_nacimiento.mes));

    printf("Anio de nacimiento:");
    scanf(" %d", &(alumno_a_introducir.fecha_de_nacimiento.anio));

    printf("Telefono de contacto (sin caracteres entre numeros)");
    scanf(" %lu", &(alumno_a_introducir.telefono_de_contacto));

    for (int i = 0; i < ANIOS_DE_CURSADA_GUARDADOS; i++) {

      printf("Anio de cursada:");
      scanf(" %d", &(alumno_a_introducir.anios_de_cursada[i].anio));

      for (int j = 0; j < MATERIAS_POR_ANIO; j++) {
        printf("Nombre de la materia %d:", (j+1));
        scanf(" %s", alumno_a_introducir.anios_de_cursada[i].materias[j].nombre);
        printf("Nota del parcial:");
        scanf(" %f", &(alumno_a_introducir.anios_de_cursada[i].materias[j].parcial));
        printf("Nota del primer recuperatorio:");
        scanf(" %f", &(alumno_a_introducir.anios_de_cursada[i].materias[j].recuperatorio1));
        printf("Nota del segundo recuperatorio:");
        scanf(" %f", &(alumno_a_introducir.anios_de_cursada[i].materias[j].recuperatorio2));
      }
    }

    fwrite(&alumno_a_introducir, sizeof(alumno_t), 1, informacion_alumnos);
  }



  if (fseek(informacion_alumnos, -(long int)sizeof(alumno_t), SEEK_END)!=0) {
      return  ERROR;
  }

  if (fread(&ultimo_alumno, sizeof(alumno_t), 1, informacion_alumnos)!=1) {
    return ERROR;
  }

  if (fseek(informacion_alumnos, 0, SEEK_SET)!=0) {
    return  ERROR;
  }

  if (fread(&alumno_a_imrpimir, sizeof(alumno_t), 1, informacion_alumnos)!=1) {
    return ERROR;
  }

  for (int i = 1; i <= ultimo_alumno.id; i++) {

    printf("Nombre y apellido: %s", alumno_a_imrpimir.nombre_y_apellido);

    printf("\n");

    printf("Casa: %s", alumno_a_imrpimir.casa);

    printf("\n");

    printf("Madera de la varita: %s", alumno_a_imrpimir.varita.madera);

    printf("\n");

    printf("Nucleo de la varita: %s", alumno_a_imrpimir.varita.nucleo);

    printf("\n");

    printf("Color de pelo: %s", alumno_a_imrpimir.color_de_pelo);

    printf("\n");

    printf("Dia de nacimiento: %d", alumno_a_imrpimir.fecha_de_nacimiento.dia);

    printf("\n");

    printf("Mes de nacimiento: %d", alumno_a_imrpimir.fecha_de_nacimiento.mes);

    printf("\n");

    printf("Anio de nacimiento: %d", alumno_a_imrpimir.fecha_de_nacimiento.anio);

    printf("\n");

    printf("Telefono de contacto (sin caracteres entre numeros): %lu", alumno_a_imrpimir.telefono_de_contacto);

    printf("\n");

    for (int i = 0; i < ANIOS_DE_CURSADA_GUARDADOS; i++) {

      printf("Anio de cursada: %d", alumno_a_imrpimir.anios_de_cursada[i].anio);

      printf("\n");

      for (int j = 0; j < MATERIAS_POR_ANIO; j++) {
        printf("Nombre de la materia %d: %s", (j+1), alumno_a_imrpimir.anios_de_cursada[i].materias[j].nombre);

        printf("\n");

        printf("Nota del parcial: %f", alumno_a_imrpimir.anios_de_cursada[i].materias[j].parcial);

        printf("\n");

        printf("Nota del primer recuperatorio: %f", alumno_a_imrpimir.anios_de_cursada[i].materias[j].recuperatorio1);

        printf("\n");

        printf("Nota del segundo recuperatorio: %f", alumno_a_imrpimir.anios_de_cursada[i].materias[j].recuperatorio2);

        printf("\n");
      }

    }

    printf("\n");
    printf("\n");
    printf("\n");

    if (fread(&alumno_a_imrpimir, sizeof(alumno_t), 1, informacion_alumnos)!=1) {
      return ERROR;
    }

  }

  fclose(informacion_alumnos);

  return 0;
}
