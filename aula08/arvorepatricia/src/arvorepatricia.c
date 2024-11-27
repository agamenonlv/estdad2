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

// Função para criar um novo nó
PatriciaNode* createNode(const char *key, int isEndOfWord)
{
    PatriciaNode *node = (PatriciaNode *)malloc(sizeof(PatriciaNode));
    node->key = strdup(key); // Copia a chave
    node->isEndOfWord = isEndOfWord;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Função para encontrar o primeiro índice onde duas strings divergem
int findMismatchIndex(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i])
    {
        i++;
    }
    return i;
}

// Função para inserir uma palavra na Árvore Patricia
PatriciaNode* insertPatricia(PatriciaNode *root, const char *word)
{
    if (!root)
    {
        return createNode(word, 1);  // Novo nó para a palavra
    }

    int mismatchIndex = findMismatchIndex(root->key, word);

    // Caso 1: A palavra é um prefixo do nó atual
    if (mismatchIndex == strlen(root->key))
    {
        if (strlen(word) == mismatchIndex)
        {
            root->isEndOfWord = 1;  // Palavra já existe
        }
        else
        {
            // Inserir a parte restante na subárvore direita
            root->right = insertPatricia(root->right, word + mismatchIndex);
        }
        return root;
    }

    // Caso 2: O nó atual é um prefixo da palavra
    if (mismatchIndex == strlen(word))
    {
        PatriciaNode *newNode = createNode(word, 1);
        newNode->right = root;
        return newNode;
    }

    // Caso 3: Há um ponto de divergência
    // Criando um nó de divisão
    PatriciaNode *splitNode = createNode(strndup(root->key, mismatchIndex), 0);

    // Criando os nós filhos para a subárvore
    splitNode->left = root->left;  // Subárvore esquerda do nó original
    root->left = NULL;  // Desvincula o filho esquerdo original
    splitNode->right = createNode(word + mismatchIndex, 1);  // Novo nó para a palavra

    // Alterando o nó original para refletir o prefixo comum
    root->key = strndup(root->key, mismatchIndex);  // Preserva o prefixo comum
    root->isEndOfWord = 0;  // Não é mais o final de uma palavra

    return splitNode;  // Retorna o nó dividido
}


// Função para buscar uma palavra na Árvore Patricia
int searchPatricia(PatriciaNode *root, const char *word)
{
    if (!root)
    {
        return 0;  // Palavra não encontrada
    }

    int mismatchIndex = findMismatchIndex(root->key, word);

    // Se o índice de divergência for igual ao tamanho da palavra,
    // e o índice de divergência for menor ou igual ao tamanho da chave do nó
    if (mismatchIndex == strlen(word) && mismatchIndex <= strlen(root->key))
    {
        return root->isEndOfWord;
    }

    // Ir para a subárvore direita
    if (mismatchIndex == strlen(root->key))
    {
        return searchPatricia(root->right, word + mismatchIndex);
    }

    return 0;  // Palavra não encontrada
}


// Função para exibir as palavras na Árvore Patricia
void printPatricia(PatriciaNode *root, char *buffer, int depth)
{
    if (!root)
    {
        return;
    }

    // Copiar a chave atual no buffer
    strncpy(buffer + depth, root->key, strlen(root->key));
    depth += strlen(root->key);

    // Exibir a palavra se for um final válido
    if (root->isEndOfWord)
    {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    // Recursão para subárvores
    printPatricia(root->left, buffer, depth);
    printPatricia(root->right, buffer, depth);
}

// Função para liberar espaço de memória
void freePatricia(PatriciaNode *root) {
    if (!root) return;

    free(root->key);
    freePatricia(root->left);
    freePatricia(root->right);
    free(root);
}

