/*
 * ordenation.h
 *
 *  Created on: 4 de set. de 2024
 *      Author: agamenon
 */

#ifndef HEADERS_ORDENATION_H_
	#define HEADERS_ORDENATION_H_

	#define N 100000
	#define BUCKETS 10

	void inserctionSort(int arr[], int size);
	void swap(int *xPtr, int *yPtr);
	void selectionSort(int arr[], int size);
	void bubbleSort(int arr[], int size);
	int partition(int arr[], int low, int high);
	void quickSortUtil(int arr[], int low, int high);
	void quickSort(int arr[], int n);
	void merge(int arr[], int left, int mid, int right);
	void mergeSortUtil(int arr[], int left, int right);
	void mergeSort(int arr[], int n);
	void radixSort(int vector[], int size);
	void insertionSort(int arr[], int n);
	void bucketSort(int arr[], int n);
	void geraEntradasDesordenadas(int arr[], int n);
	void geraEntradasQuaseOrdenadas(int arr[], int n, int variacao);
	void geraEntradasOrdenadas(int arr[], int n);
	void imprimeVetor(int arr[], int n);

#endif /* HEADERS_ORDENATION_H_ */
