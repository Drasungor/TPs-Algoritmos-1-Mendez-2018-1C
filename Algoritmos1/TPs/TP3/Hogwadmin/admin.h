#ifndef ADMIN_H
#define ADMIN_H

#define MAXIMO_ELEMENTOS_PADRON 9
#define MAXIMO_ELEMENTOS_COMENTARIOS 257
#define MAXIMO_ELEMENTOS_NOMBRE 33
#define MAXIMO_ELEMENTOS_CASA 17
#define CANTIDAD_ANIOS_DE_CURSADA 7
#define MAXIMO_ELEMENTOS_FECHA 11

#define OPERACION_EXITOSA 1
#define NO_SE_ABRIO_EL_PRIMER_ARCHIVO -1
#define NO_SE_ABRIO_EL_SEGUNDO_ARCHIVO -2
#define ARGUMENTOS_INSUFICIENTES -3// CAMBIAR NOMBRE
#define NO_SE_INSCRIBIO_ELEMENTO -5
#define NO_SE_CREO_EL_ARCHIVO -5
#define NO_SE_ELIMINO_EL_ARCHIVO -6
#define NO_SE_RENOMBRO_ARCHIVO -7
#define NO_SE_CREO_EL_AUXILIAR -8
#define EL_ARCHIVO_ESTA_VACIO -9

#define FORMATO_INGRESOS " %[^;];%[^;];%[^;];%d"
#define FORMATO_BITACORA " %[^;];%[^;];%d;%[^\n]"

#define ELEMENTOS_POR_ALUMNO_NUEVO 4
#define ELEMENTOS_POR_ENTRADA_BITACORA 4

#define  CANTIDAD_CASAS 4

#define COMANDO_LIMPIAR "limpiar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_APLICAR "aplicar"
#define COMANDO_RESUMIR "resumir"
#define COMANDO_AYUDA "ayuda"

#define AUXILIAR_ALUMNOS "alumnos_auxiliar"

#define NO_TIENE_PUNTOS 0

//tipo de dato que almacena las propiedades que posee un alumno
typedef struct alumno{
  char padron[MAXIMO_ELEMENTOS_PADRON];
  char nombre[MAXIMO_ELEMENTOS_NOMBRE];
  char casa[MAXIMO_ELEMENTOS_CASA];
  int anio_de_cursada;
  int puntos_obtenidos;
}alumno_t;


typedef struct resumen_casa{
  char casa[MAXIMO_ELEMENTOS_CASA];
  unsigned long puntos_casa;
  char padron[MAXIMO_ELEMENTOS_PADRON];
  unsigned long puntos_alumno;
}resumen_casa_t;



//precondiciones:-
//postcondiciones:le suma 1 al anio que cursan los alumnos del archivo
//de alumnos (ruta origen) y los introduce en el archivo de la ruta destino
//si el anio esta dentro del rango permitido en hogwarts (de primero a septimo)
int pasar_de_anio(char* ruta_origen, char* ruta_destino);


//precondiciones:ambos archivos deben estar ordenados ascendentemente por casa,
//anio y padron
//postcondiciones: insertara en el archivo de alumnos de manera ordenada los
//alumnos indicados en el archivo de ingresantes
int actualizar_alumnos(char* ruta_alumnos, char* ruta_actualizaciones);


//precondiciones: los alumnos que esten en la bitacora deben estar en el archivo
//de alumnos
//postcondiciones: se sumaran los puntos indicados en la bitacora a los alumnos
//que le correspondan en el archivo de alumnos
int aplicar(char* ruta_alumnos, char* ruta_bitacora);


//precondiciones:-
//postcondiciones:imprime en el canal de impresion los puntos de cada anio
//de cada casa y los puntos totales de cada cada, imprime tambien el nombre y
//puntaje de la casa ganadora y el padron y puntaje del mejor alumno de esa casa
resumen_casa_t resumir_puntos(char* ruta_alumnos, FILE* canal_impresion);

#endif
