/*
 * arvorepatricia.h
 *
 *  Created on: 21 de nov. de 2024
 *      Author: agamenon
 */

#ifndef HEADERS_ARVOREPATRICIA_H_
	#define HEADERS_ARVOREPATRICIA_H_

	// Estrutura do nó da Árvore Patricia
	typedef struct PatriciaNode {
		char *key;                     // Chave armazenada (palavra ou parte dela)
		int isEndOfWord;               // Indica se é o final de uma palavra
		struct PatriciaNode *left;     // Filhos para prefixos diferentes
		struct PatriciaNode *right;    // Filhos para prefixos iguais
	} PatriciaNode;

	// Função para criar um novo nó na árvore Patricia
	PatriciaNode* createNode(char *key, int isEndOfWord);
	// Função para inserir uma palavra na árvore Patricia
	void insert(PatriciaNode **root, char *word);
	// Função para realizar a busca por prefixo e sugerir palavras
	void searchPrefix(PatriciaNode *root, const char *prefix);
	// Função para salvar a árvore Patricia em um arquivo de texto
	void saveTreeToFile(PatriciaNode *root, FILE *file);
	// Função para carregar a árvore Patricia de um arquivo de texto
	PatriciaNode* loadTreeFromFile(FILE *file);

#endif /* HEADERS_ARVOREPATRICIA_H_ */
