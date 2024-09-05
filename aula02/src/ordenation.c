/*
 * ordenation.c
 *
 *  Created on: 4 de set. de 2024
 *      Author: agamenon
 */

#include "../headers/ordenation.h"

void inserctionSort(int arr[], int size)
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

void selectionSort(int arr[], int size)
{
	int small;
	int pos;

	for (int i = 0; i< size; i++)
	{
		small = arr[i];

		// Localiza o menor valor da lista
		for (int j = i + 1; j < size; j++)
		{
			if (small > arr[j])
			{
				small = arr[j];
				pos = j;
			}
		}

		arr[pos] = arr[i];
		arr[i] = small;
	}
}
