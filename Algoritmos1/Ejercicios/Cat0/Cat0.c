#include <stdio.h>

#define ARGUMENTO_1 1
#define PROBLEMA_DE_APERTURA "No se pudo abrir el archivo o no existe"
#define HAY_PROBLEMA -1

int main(int argc, char const *argv[]) {

  char caracter;

  FILE* archivo=fopen(argv[ARGUMENTO_1], "r");

  if (!archivo) {
      printf("%s\n", PROBLEMA_DE_APERTURA);
      return HAY_PROBLEMA;
  }

  caracter=fgetc(archivo);

  while (caracter!=EOF) {
      printf("%c", caracter);
      caracter=fgetc(archivo);
  }

  fclose(archivo);

  return 0;
}
