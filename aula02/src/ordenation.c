/*
 * ordenation.c
 *
 *  Created on: 4 de set. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/ordenation.h"

void insertionSort(int arr[], int size)
{
	int key;
	int j;

	for (int i = 1; i < size; i++)
	{
		key = arr[i];
		j = i - 1;

		while ((j >= 0) && (arr[j] > key))
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}

void swap(int *xPtr, int *yPtr)
{
	int temp = *xPtr;
	*xPtr = *yPtr;
	*yPtr = temp;
}

void selectionSort(int arr[], int size)
{
	int minIdx;

	for (int i = 0; i< size - 1; i++)
	{
		minIdx = i;

		// Localiza o menor valor da lista
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[minIdx])
				minIdx = j;
		}

		swap(&arr[minIdx], &arr[i]);
	}
}

void bubbleSort(int arr[], int size)
{
	int swaped;

	for (int i = 0; i < size - 1; i++)
	{
		swaped = 0;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j+1]);
				swaped = 1;
			}
		}

		if (swaped == 0)
			break;
	}
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j  < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortUtil(int arr[], int low, int high)
{
    if (low >= high) {
        return;
    }

    int pivot = partition (arr, low, high);

    quickSortUtil(arr, low, pivot - 1);
    quickSortUtil(arr, pivot + 1, high);
}

void quickSort(int arr[], int n)
{
    quickSortUtil(arr, 0, n - 1);
}

void merge (int arr[], int left, int mid, int right)
{
    int sizeFirst = mid - left + 1;
    int sizeSecond = right - mid;

    int firstArr[sizeFirst];
    int secondArr[sizeSecond];

    for (int i = 0; i < sizeFirst; i++) {
        firstArr[i] = arr[left + i];
    }
    for (int i = 0; i < sizeSecond; i++) {
        secondArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < sizeFirst && j < sizeSecond) {
        if (firstArr[i] < secondArr[j]) {
            arr[k++] = firstArr[i++];
        } else {
            arr[k++] = secondArr[j++];
        }
    }
    while (i < sizeFirst) {
        arr[k++] = firstArr[i++];
    }
    while (j < sizeSecond) {
        arr[k++] = secondArr[j++];
    }
}

void mergeSortUtil(int arr[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int mid = left + (right - left)/2;

    mergeSortUtil(arr, left, mid);
    mergeSortUtil(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

void mergeSort(int arr[], int n)
{
    mergeSortUtil(arr, 0, n - 1);
}

void radixSort(int vector[], int size)
{
	int *b;
	int major = vector[0];
	int exp = 1;

	b = (int *) calloc(size, sizeof(int));

	for(int i = 0; i < size; i++)
		if(vector[i] > major)
			major = vector[i];

	while((major / exp) > 0){
		int bucket[10] = { 0 };

		for(int i = 0; i < size; i++)
			bucket[(vector[i] / exp) % 10]++;

		for(int i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];

		for(int i = size - 1; i >= 0; i--)
			b[--bucket[(vector[i] / exp) % 10]] = vector[i];

		for(int i = 0; i < size; i++)
			vector[i] = b[i];

		exp *= 10;
	}

	free(b);
}

void bucketSort(int arr[], int n)
{
    // Cria buckets (listas) vazios.
    int buckets[BUCKETS][N];
    int bucketCount[BUCKETS];

    // Inicializa o contador de elementos em cada bucket.
    for (int i = 0; i < BUCKETS; i++) {
        bucketCount[i] = 0;
    }

    // Encontra o valor máximo no array para normalizar os dados.
    int max_value = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    // Distribui os elementos nos buckets com base no valor.
    for (int i = 0; i < n; i++) {
        int bucketIndex = (arr[i] * BUCKETS) / (max_value + 1);
        buckets[bucketIndex][bucketCount[bucketIndex]++] = arr[i];
    }

    // Ordena cada bucket individualmente usando Insertion Sort.
    for (int i = 0; i < BUCKETS; i++) {
        if (bucketCount[i] > 0) {
            insertionSort(buckets[i], bucketCount[i]);
        }
    }

    // Junta os elementos ordenados de todos os buckets de volta no array original.
    int index = 0;
    for (int i = 0; i < BUCKETS; i++) {
        for (int j = 0; j < bucketCount[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

void geraEntradasDesordenadas(int arr[], int n)
{
    // Função que gera N números desordenados aleatoriamente.
    srand(time(0)); // Inicializa a semente do gerador de números aleatórios.
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Gera números entre 0 e 9999.
    }
}

void geraEntradasQuaseOrdenadas(int arr[], int n, int variacao)
{
     // Função que gera N números quase ordenados aleatoriamente.
    srand(time(0)); // Inicializa a semente do gerador de números aleatórios.

    // Gera um array quase ordenado.
    for (int i = 0; i < n; i++) {
        if (i % variacao == 0) {
            arr[i] = rand() % 2; // Apenas 1 em cada X valores está fora de ordem onde X = variacao
        } else {
            arr[i] = i; // Coloca o número em ordem.
        }
    }
}

void geraEntradasOrdenadas(int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void imprimeVetor(int arr[], int n)
{
    // Função simples para imprimir o vetor.
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
