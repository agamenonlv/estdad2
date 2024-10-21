/*
 * busca.h
 *
 *  Created on: 17 de out. de 2024
 *      Author: agamenon
 */

#ifndef HEADERS_BUSCA_H_
#define HEADERS_BUSCA_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#define MAX_PRODUCTS 1000  // Número de produtos
	#define MAX_NAME_LENGTH 50 // Tamanho máximo do nome do produto

	// Estrutura que representa um produto no e-commerce
	typedef struct {
		int id;                  // ID único do produto
		char name[MAX_NAME_LENGTH];  // Nome do produto
		float price;             // Preço do produto
	} Product;

	// Função para gerar um nome de produto aleatório a partir da lista predefinida
	void generateProductName(char *name);

	// Função para gerar uma lista de produtos com preços aleatórios
	void generateProductList(Product products[], int numProducts);

	// Função para imprimir um produto
	void printProduct(Product product);

	// Função para imprimir a lista de produtos
	void printProductList(Product products[], int numProducts);

	// Espaço para implementar a busca sequencial
	int sequentialSearch(Product products[], int numProducts, const char* target);

	// Espaço para implementar a busca binária
	int binarySearch(Product products[], int low, int high, const char* target);

	// Função de ordenação para os produtos (usada para a busca binária)
	int compareProducts(const void* a, const void* b);

#endif /* HEADERS_BUSCA_H_ */
