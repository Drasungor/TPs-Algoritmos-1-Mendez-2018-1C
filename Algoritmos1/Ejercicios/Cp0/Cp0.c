#include <stdio.h>

#define ARCHIVO 1
#define LOCALIDAD_DESTINO 2
#define ERROR -1


int main(int argc, char const *argv[]) {

  char caracter;

  FILE* archivo=fopen(argv[ARCHIVO], "r");
  FILE* copia=fopen(argv[LOCALIDAD_DESTINO], "w");

  if (!archivo) {
    printf("Hubo un error al abrir el archivo o este no existe\n");
    return ERROR;
  }

  if (!copia) {
    printf("Hubo un error al ubicar la copia del archivo o la direccion no existe\n");
    return ERROR;
  }

  caracter=fgetc(archivo);

  while (caracter!=EOF) {
    fputc(caracter, copia);
    caracter=fgetc(archivo);
  }

  fclose(archivo);
  fclose(copia);

  return 0;
}
