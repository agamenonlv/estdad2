/*
 * newtest.c
 *
 *  Created on: 12 de set. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/ordenation.h"

int main(void)
{
	int arr[N];

	//Inicializa o gerador de números aleatórios
	srand(time(NULL));

	//Gera dados aleatórios
	//geraEntradasDesordenadas(arr, size); // Gera as entradas desordenadas.
	//geraEntradasQuaseOrdenadas(arr, N, 10);
	geraEntradasOrdenadas(arr, N);

	//Ordena o array usando o Bubble Sort
	clock_t start = clock();
	selectionSort(arr, N);
	clock_t end = clock();

    // Calcula o tempo de execução em milissegundos
	printf("Número de elementos do array: %d\n", N);

    double cpuTimeUsed = ((double) (end - start)) * 1000 / CLOCKS_PER_SEC;
    printf("\n Tempo de execução Selection Sort: %f milissegundos\n", cpuTimeUsed);

	return 0;
}
