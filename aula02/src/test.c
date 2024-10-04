/*
 * test.c
 *
 *  Created on: 4 de set. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/ordenation.h"

int main(void)
{
	int arr[N];
	int dataBubble[N];
	int dataSelection[N];
	int dataInsertion[N];
	int dataQuick[N];
	int dataMerge[N];
	int dataRadix[N];
	int dataBucket[N];

	system("clear||cls");

	//Inicializa o gerador de números aleatórios
	srand(time(NULL));

	//Gera dados aleatórios
	//geraEntradasDesordenadas(arr, size); // Gera as entradas desordenadas.
	geraEntradasQuaseOrdenadas(arr, N, 10);
	//geraEntradasOrdenadas(arr, N);

	//Copia o vetor de dados para os vetores de trabalho
	for (int i = 0; i < N; i++)
	{
		dataBubble[i] = arr[i];
		dataSelection[i] = arr[i];
		dataInsertion[i] = arr[i];
		dataQuick[i] = arr[i];
		dataMerge[i] = arr[i];
		dataRadix[i] = arr[i];
		dataBucket[i] = arr[i];
	}

	//Ordena o array usando o Bubble Sort
	clock_t startBubble = clock();
	bubbleSort(dataBubble, N);
	clock_t endBubble = clock();

	//Ordena o array usando o Selection Sort
	clock_t startSelection = clock();
	selectionSort(dataSelection, N);
	clock_t endSelection = clock();

	//Ordena o array usando o Insertion Sort
	clock_t startInsertion = clock();
	insertionSort(dataInsertion, N);
	clock_t endInsertion = clock();

	//Ordena o array usando o Quick Sort
	clock_t startQuick = clock();
	quickSort(dataQuick, N);
	clock_t endQuick = clock();

	//Ordena o array usando o Merge Sort
	clock_t startMerge = clock();
	mergeSort(dataMerge, N);
	clock_t endMerge = clock();

	//Ordena o array usando o Radix Sort
	clock_t startRadix = clock();
	radixSort(dataRadix, N);
	clock_t endRadix = clock();

	//Ordena o array usando o Bucket Sort
	clock_t startBucket = clock();
	bucketSort(dataBucket, N);
	clock_t endBucket = clock();

    // Calcula o tempo de execução em milissegundos
	printf("Número de elementos do array: %d\n", N);

    double cpuTimeUsedSelection = ((double) (endSelection - startSelection)) * 1000 / CLOCKS_PER_SEC;
    printf("\n Tempo de execução Selection Sort: %f milissegundos\n", cpuTimeUsedSelection);

    double cpuTimeUsedBubble = ((double) (endBubble - startBubble)) * 1000 / CLOCKS_PER_SEC;
    printf("\n Tempo de execução Bubble Sort: %f milissegundos\n", cpuTimeUsedBubble);

    double cpuTimeUsedInsertion = ((double) (endInsertion - startInsertion)) * 1000 / CLOCKS_PER_SEC;
    printf("\n Tempo de execução Insertion Sort: %f milissegundos\n", cpuTimeUsedInsertion);

    double cpuTimeUsedQuick = ((double) (endQuick - startQuick)) * 1000 / CLOCKS_PER_SEC;
    printf("\n Tempo de execução Quick Sort: %f milissegundos\n", cpuTimeUsedQuick);

    double cpuTimeUsedMerge = ((double) (endMerge - startMerge)) * 1000 / CLOCKS_PER_SEC;
    printf("\n Tempo de execução Merge Sort: %f milissegundos\n", cpuTimeUsedMerge);

    double cpuTimeUsedRadix = ((double) (endRadix - startRadix)) * 1000 / CLOCKS_PER_SEC;
    printf("\n Tempo de execução Radix Sort: %f milissegundos\n", cpuTimeUsedRadix);

    double cpuTimeUsedBucket = ((double) (endBucket - startBucket)) * 1000 / CLOCKS_PER_SEC;
    printf("\n Tempo de execução Bucket Sort: %f milissegundos\n", cpuTimeUsedBucket);

	return 0;
}
