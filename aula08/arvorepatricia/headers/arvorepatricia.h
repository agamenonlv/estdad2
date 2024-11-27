/*
 * arvorepatricia.h
 *
 *  Created on: 21 de nov. de 2024
 *      Author: agamenon
 */

#ifndef HEADERS_ARVOREPATRICIA_H_
#define HEADERS_ARVOREPATRICIA_H_

#include <stdio.h>

// Estrutura do nó da Árvore Patricia
typedef struct PatriciaNode {
    char *key;                     // Chave armazenada (palavra ou parte dela)
    int isEndOfWord;               // Indica se é o final de uma palavra
    struct PatriciaNode *left;     // Filhos para prefixos diferentes
    struct PatriciaNode *right;    // Filhos para prefixos iguais
} PatriciaNode;

// Função para criar um novo nó
PatriciaNode* createNode(const char *key, int isEndOfWord);
// Função para encontrar o primeiro índice onde duas strings divergem
int findMismatchIndex(const char *str1, const char *str2);
// Função para inserir uma palavra na Árvore Patricia
PatriciaNode* insertPatricia(PatriciaNode *root, const char *word);
// Função para buscar uma palavra na Árvore Patricia
int searchPatricia(PatriciaNode *root, const char *word);
// Função para exibir as palavras na Árvore Patricia
void printPatricia(PatriciaNode *root, char *buffer, int depth);
// Função para liberar espaço de memória
void freePatricia(PatriciaNode *root);

#endif /* HEADERS_ARVOREPATRICIA_H_ */
