/*
 * arvorepatricia.c
 *
 *  Created on: 21 de nov. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/arvorepatricia.h"

// Função para criar um novo nó na árvore Patricia
PatriciaNode* createNode(char *key, int isEndOfWord) {
    PatriciaNode *newNode = (PatriciaNode *)malloc(sizeof(PatriciaNode));
    newNode->key = strdup(key);
    newNode->isEndOfWord = isEndOfWord;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir uma palavra na árvore Patricia
void insert(PatriciaNode **root, char *word) {
    if (*root == NULL) {
        *root = createNode(word, 1);  // Cria um novo nó com a palavra
        return;
    }

    PatriciaNode *current = *root;
    int index = 0;
    while (current != NULL) {
        // Verifica o ponto de divergência
        int commonPrefixLength = 0;
        while (word[index] == current->key[commonPrefixLength]) {
            commonPrefixLength++;
        }

        if (commonPrefixLength == strlen(current->key)) {
            // Se o prefixo atual é o mesmo, explore o filho da direita
            if (word[index + commonPrefixLength] == '\0') {
                current->isEndOfWord = 1;  // Marca como final de palavra
                return;
            }
            if (current->right == NULL) {
                current->right = createNode(&word[index + commonPrefixLength], 1);
                return;
            }
            current = current->right;
        } else {
            // Se o prefixo é diferente, cria um nó de divisão
            char *commonPrefix = strndup(word, commonPrefixLength);
            PatriciaNode *newNode = createNode(commonPrefix, 0);
            newNode->left = createNode(&word[commonPrefixLength], 0);
            newNode->right = current;
            *root = newNode;
            return;
        }
    }
}

// Função para realizar a busca por prefixo e sugerir palavras
void searchPrefix(PatriciaNode *root, const char *prefix) {
    if (root == NULL) {
        printf("Árvore vazia.\n");
        return;
    }

    PatriciaNode *current = root;
    int index = 0;
    while (current != NULL) {
        // Verifica o ponto de divergência
        int commonPrefixLength = 0;
        while (prefix[index] == current->key[commonPrefixLength]) {
            commonPrefixLength++;
        }

        if (commonPrefixLength == strlen(current->key)) {
            if (prefix[index + commonPrefixLength] == '\0') {
                // Encontramos o nó com o prefixo
                break;
            }
            current = current->right;
        } else {
            printf("Prefixo não encontrado.\n");
            return;
        }
    }

    // Agora que encontramos o nó com o prefixo, percorre as palavras possíveis
    if (current == NULL) {
        return;
    }

    if (current->isEndOfWord) {
        printf("%s\n", current->key);
    }

    if (current->left != NULL) {
        searchPrefix(current->left, prefix);
    }

    if (current->right != NULL) {
        searchPrefix(current->right, prefix);
    }
}

// Função para salvar a árvore Patricia em um arquivo de texto
void saveTreeToFile(PatriciaNode *root, FILE *file) {
    if (root == NULL) return;

    fprintf(file, "%s\n", root->key);
    if (root->left != NULL) saveTreeToFile(root->left, file);
    if (root->right != NULL) saveTreeToFile(root->right, file);
}

// Função para carregar a árvore Patricia de um arquivo de texto
PatriciaNode* loadTreeFromFile(FILE *file) {
    PatriciaNode *root = NULL;
    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        insert(&root, word);
    }
    return root;
}
