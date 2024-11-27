/*
 * arvoreb.h
 *
 *  Created on: 21 de nov. de 2024
 *      Author: agamenon
 */

#ifndef HEADERS_ARVOREB_H_
#define HEADERS_ARVOREB_H_

	#define MAX_KEYS 3 // Ordem da árvore B (número máximo de chaves por nó)

	typedef struct BTreeNode {
		char *keys[MAX_KEYS];        			  // Chaves armazenadas (palavras)
		struct BTreeNode *children[MAX_KEYS + 1]; // Filhos do nó
		int numKeys;                 			  // Número atual de chaves no nó
		int isLeaf;                  			  // Indica se o nó é folha
	} BTreeNode;

	// Função para criar um novo nó
	BTreeNode* createBTreeNode(int isLeaf);
	// Função para dividir um nó cheio
	void splitChild(BTreeNode *parent, int i);
	// Função auxiliar para buscar uma palavra em um nó
	int searchInNode(BTreeNode *node, const char *key);
	// Função para buscar uma palavra na Árvore B
	int searchBTree(BTreeNode *root, const char *key);
	// Função para bucar uma palavra pelo prefixo
	int searchWord(BTreeNode *root, const char *key);
	// Função para inserir uma palavra em um nó não cheio
	void insertNonFull(BTreeNode *node, const char *key);
	// Função principal para inserir uma palavra na Árvore B
	void insertBTree(BTreeNode **root, const char *key);
	// Função para inserir palavras no dicionário
	int insertWord(BTreeNode *root, const char *key);
	//Função de Sugestão (Autocompletar)
	void suggestWords(BTreeNode *root, const char *prefix);
	// Função para imprimir as palavras em ordem lexicográfica
	void printBTree(BTreeNode *root);
	// Função que limpa a tela do console
	void clear();
	// Função que exibe um cabeçalho
	void iniciar();

#endif /* HEADERS_ARVOREB_H_ */
