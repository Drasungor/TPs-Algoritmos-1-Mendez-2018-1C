#include <stdio.h>

int main() {
  /* code */
  int personas=0;
  int edad=0;

  printf("Cantidad de personas: ");
  scanf("%i", &personas);

  for (int i = 1; i <= personas; i++) {
    printf("Edad: ");
    scanf("%i", &edad);
    if (edad>=18) {
      printf("%i puede pasar\n", i);
    }
    else {
      printf("%i no puede pasar\n", i);
    }

  }

  return 0;
}
