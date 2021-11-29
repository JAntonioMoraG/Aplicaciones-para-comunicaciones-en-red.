#include <stdio.h>
#include <stdlib.h>
// Biblioteca de hilos POSIX
#include <pthread.h>

// Biblioteca de matrices
#include "matriz.h"

// Variables globales
int numeroHilos,
    // Dimensiones de las matrices
    m,n,p;
int **matrizA,**matrizB,**matrizC;

void *multiplicacionMatrizHilo(void *lugarHilo){
    int x = 0,
        l =*(int*)lugarHilo,
        i = 0, j = 0, k = 0;

    // Loop que recorre las filas asignadas al hilo(Matriz A)
    for(i = numeroHilos*x + l ; i < n ; x++,i = numeroHilos*x + l){
        // Loop que recorre las columnas de la matriz B
        for(j = 0; j < p; j++){
            // Loop que recorre las columnas de A/filas de B
            for(k = 0; k < m; k++)
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
        }
    }

    //Se libera el valor pasado al hilo
    free(lugarHilo);
    pthread_exit(NULL);
}

int main(int argc,char *argv[]){
    /*
        Se obtiene de los argumentos de consola en la ejecución los valores de:
            Número de Hilos: 1° argumento
            n(# filas matriz A): 2° argumento
            m(# columnas de A/filas de B): 3° argumento
            p(# columnas de B): 4° argumento
    */
    numeroHilos = atoi(argv[1]);
    n = atoi(argv[2]);
    m = atoi(argv[3]);
    p = atoi(argv[4]);
    // Reserva de memoria para las matrices
    matrizA = crearMatriz(n,m);
    matrizB = crearMatriz(m,p);
    matrizC = crearMatriz(n,p);
    // Llenado de las matrices
    llenarMatrizAleatoriamente(matrizA,1,3,n,m);
    llenarMatrizAleatoriamente(matrizB,1,3,m,p);

    pthread_t hilos[numeroHilos];
    int* lugarHilo;

    for(int i=0;i<numeroHilos;i++){
        lugarHilo = (int*)malloc(sizeof(int)); 
        *lugarHilo = i;

        if(pthread_create(
                &hilos[i], 
                NULL,
                multiplicacionMatrizHilo,
                (void*)lugarHilo) < 0){
            printf("Error en la creación del hilo #%d",i);
            return EXIT_FAILURE;
        }
    }
    // Espera a que todos los hilos terminen su ejecución
    for(int i=0;i<numeroHilos;i++)
        pthread_join(hilos[i],NULL);

    printf("Matriz A:\n");
    imprimirMatriz(matrizA,n,m);
    printf("\nMatriz B:\n");
    imprimirMatriz(matrizB,m,p);
    printf("\n\nMatriz resultante(C)\n");
    imprimirMatriz(matrizC,n,p);
    // Se liberan las matrices
    liberarMatriz(matrizA,n);
    liberarMatriz(matrizB,m);
    liberarMatriz(matrizC,n);

    matrizA = NULL;
    matrizB = NULL;
    matrizC = NULL;
    lugarHilo = NULL;

    printf("\n[+] Tiempo de ejecución con %d hilos:", numeroHilos);

    return EXIT_SUCCESS;
}