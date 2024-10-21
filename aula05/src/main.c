/*
 * main.c
 *
 *  Created on: 17 de out. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../headers/busca.h"

// Função principal
int main() {
    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios

    Product products[MAX_PRODUCTS]; // Array de produtos
	int numProducts = MAX_PRODUCTS; // Quantidade de produtos a serem gerados

	// Gera a lista de produtos
	generateProductList(products, numProducts);

	// Imprime a lista de produtos
	printProductList(products, 10); // Exibe apenas os 10 primeiros produtos

	// Define o produto alvo para busca
	char target[MAX_NAME_LENGTH] = "Notebook Dell Inspiron";

	// Espaço para realizar a busca sequencial
	printf("\nBusca sequencial pelo produto '%s':\n", target);
	clock_t startsequential = clock();
	int seqResult = sequentialSearch(products, numProducts, target);
	clock_t endsequential = clock();
	if (seqResult != -1) {
		printf("Produto encontrado na posição %d:\n", seqResult);
		printProduct(products[seqResult]);
	} else {
		printf("Produto não encontrado na busca sequencial.\n");
	}

	// Ordena a lista de produtos para a busca binária
	qsort(products, numProducts, sizeof(Product), compareProducts);

	// Espaço para o realizar a busca binária
	printf("\nBusca binária pelo produto '%s':\n", target);
	clock_t startbinary = clock();
	int binResult = binarySearch(products, 0, numProducts - 1, target);
	clock_t endbinary = clock();
	if (binResult != -1) {
		printf("Produto encontrado na posição %d:\n", binResult);
		printProduct(products[binResult]);
	} else {
		printf("Produto não encontrado na busca binária.\n");
	}

	//Tempo de execução
	printf("\nPara uma lista com %d", MAX_PRODUCTS);
	printf(" o tempo de execução de cada mecanismo de busca foi de:\n");
	double timesequential = ((double) (endsequential - startsequential)) * 1000 / CLOCKS_PER_SEC;
	double timebinary = ((double) (endbinary - startbinary)) * 1000 / CLOCKS_PER_SEC;
	printf("Sequencial: %f milisegundos\n", timesequential);
	printf("Binária: %f milisegundos\n", timebinary);

    return 0;
}
