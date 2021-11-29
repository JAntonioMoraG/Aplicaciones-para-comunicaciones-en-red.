#include <stdio.h>
#include <stdlib.h>

int** crearMatriz(int filas, int columnas){
	int **matriz = NULL;
	int i,j;

	matriz = (int**) malloc( filas * sizeof(int *));
	if(matriz == NULL){
		printf("sin memoria\n");
		exit(EXIT_FAILURE);
		return NULL;
	}else{
		for(i=0;i<filas;i++){
			matriz[i] = (int*) malloc( columnas*sizeof(int));
			if(matriz[i] == NULL){
				printf("sin memoria para los elementos de la fila %d\n", i);
				do{
					i --;
					free(matriz[i]);
				}while(i>0);
				free(matriz);
				matriz = NULL;
				exit(EXIT_FAILURE);
				break;
			}
		}
	}

	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			matriz[i][j] = 0;
		}
	}

	return matriz;
}

void llenarMatrizAleatoriamente(int **matriz, int rangoInferior, int rangoSuperior, int filas, int columnas){
	int i,j;

	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++)
			matriz[i][j] = rand() %rangoSuperior + rangoInferior;
	}
}

void submatrizXFilas(int **matrizOrigen, int **matrizObjetivo, int filasOrigen, int rangoInferior, int rangoSuperior){
	int i;

	for(i=rangoInferior;i<=rangoSuperior;i++){
		matrizObjetivo[0] = matrizOrigen[i];
		matrizObjetivo ++;
	}
}

void multiplicarMatrices(int **matrizA, int **matrizB, int **matrizResultado, int n, int m, int x){
	int i,j,k;

	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			for(k=0;k<x;k++){
				matrizResultado[i][k] += matrizA[i][j] * matrizB[j][k];
			}
		}
	}
}

void imprimirMatriz(int **matriz, int filas, int columnas){
	int i,j;
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			printf("%d	", matriz[i][j]);
		}
		printf("\n");
	}
}

void liberarMatriz(int **matriz, int filas){
	int i;

	for(i=0;i<filas;i++){
		free(matriz[i]);
	}
	free(matriz);
	matriz = NULL;
}	