#include <stdio.h>



int mayor (int vector[], int tope){
	int maximo = vector[0];
	for (int i=0; i<tope; i++){
		if (maximo<vector[i]){
			maximo = vector[i];
		}
	}
	return maximo;
}


int main(){

  int numeros[]={1,2,3,4,5};

	int resultado = mayor(numeros, 5);
	printf("%d \n", resultado );
	return 0;
}
