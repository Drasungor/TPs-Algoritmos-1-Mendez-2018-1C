#include <stdio.h>
#include <ctype.h>

int main() {
  char letra_1= 97;
  char letra_1_mayuscula= toupper(letra_1);
  char letra_2= letra_1+1;

  printf("%c, %c, %c\n", letra_1, letra_1_mayuscula, letra_2);

  return 0;
}
