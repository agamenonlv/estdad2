/*
 * test.c
 *
 *  Created on: 4 de set. de 2024
 *      Author: agamenon
 */

#include <stdio.h>

#include "../headers/ordenation.h"

int main(void)
{
	int arr[] = {8,4,6,3,1,9,5};
	int n = sizeof(arr)/sizeof(arr[0]);

	selectionSort(arr, n);

	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}
