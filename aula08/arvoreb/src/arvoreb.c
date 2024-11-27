/*
 * arvoreb.c
 *
 *  Created on: 21 de nov. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/arvoreb.h"

// Função para criar um novo nó
BTreeNode* createBTreeNode(int isLeaf)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->numKeys = 0;
    node->isLeaf = isLeaf;
    for (int i = 0; i < MAX_KEYS + 1; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

// Função para dividir um nó cheio
void splitChild(BTreeNode *parent, int i)
{
    BTreeNode *fullChild = parent->children[i];
    BTreeNode *newChild = createBTreeNode(fullChild->isLeaf);

    newChild->numKeys = MAX_KEYS / 2;

    // Copia as últimas chaves para o novo nó
    for (int j = 0; j < MAX_KEYS / 2; j++)
    {
        newChild->keys[j] = fullChild->keys[j + MAX_KEYS / 2 + 1];
    }

    if (!fullChild->isLeaf)
    {
        // Copia os filhos também
        for (int j = 0; j <= MAX_KEYS / 2; j++)
        {
            newChild->children[j] = fullChild->children[j + MAX_KEYS / 2 + 1];
        }
    }

    fullChild->numKeys = MAX_KEYS / 2;

    // Move os filhos do pai para dar espaço
    for (int j = parent->numKeys; j >= i + 1; j--)
    {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = newChild;

    // Move as chaves do pai para dar espaço
    for (int j = parent->numKeys - 1; j >= i; j--)
    {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = fullChild->keys[MAX_KEYS / 2];
    parent->numKeys++;
}

// Função auxiliar para buscar uma palavra em um nó
int searchInNode(BTreeNode *node, const char *key)
{
    for (int i = 0; i < node->numKeys; i++)
    {
        if (strcmp(node->keys[i], key) == 0)
        {
            return 1; // Palavra encontrada
        }
    }
    return 0; // Palavra não encontrada
}

// Função para buscar uma palavra na Árvore B
int searchBTree(BTreeNode *root, const char *key)
{
    if (!root)
    {
        return 0; // Árvore vazia
    }

    int i = 0;
    while (i < root->numKeys && strcmp(key, root->keys[i]) > 0)
    {
        i++;
    }

    if (i < root->numKeys && strcmp(key, root->keys[i]) == 0)
    {
        return 1; // Palavra encontrada no nó atual
    }

    if (root->isLeaf)
    {
        return 0; // Palavra não encontrada
    }

    return searchBTree(root->children[i], key); // Busca no filho correspondente
}

// Função para bucar uma palavra pelo prefixo
int searchWord(BTreeNode *root, const char *key)
{
    if (!root)
    {
        return 0; // Árvore vazia
    }

    int i = 0;
    while (i < root->numKeys && strncmp(key, root->keys[i], strlen(key)) > 0)
    {
        i++;
    }

    if (i < root->numKeys && strncmp(key, root->keys[i], i+1) == 0)
    {
    	printf("%s, ", root->keys[i]);
        return 1; // Palavra encontrada no nó atual
    }

    if (root->isLeaf)
    {
        return 0; // Palavra não encontrada
    }

    return searchBTree(root->children[i], key); // Busca no filho correspondente
}

// Função para inserir uma palavra em um nó não cheio
void insertNonFull(BTreeNode *node, const char *key)
{
    int i = node->numKeys - 1;

    if (node->isLeaf)
    {
        // Insere a palavra no local correto
        while (i >= 0 && strcmp(key, node->keys[i]) < 0)
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = strdup(key);
        node->numKeys++;
    }
    else
    {
        // Encontra o filho onde a palavra deve ser inserida
        while (i >= 0 && strcmp(key, node->keys[i]) < 0)
        {
            i--;
        }
        i++;

        if (node->children[i]->numKeys == MAX_KEYS)
        {
            // Divide o filho se estiver cheio
            splitChild(node, i);
            if (strcmp(key, node->keys[i]) > 0)
            {
                i++;
            }
        }

        insertNonFull(node->children[i], key);
    }
}

// Função principal para inserir uma palavra na Árvore B
void insertBTree(BTreeNode **root, const char *key)
{
    if (*root == NULL)
    {
        *root = createBTreeNode(1); // Cria a raiz se não existir
    }

    if ((*root)->numKeys == MAX_KEYS)
    {
        // Divide a raiz se estiver cheia
        BTreeNode *newRoot = createBTreeNode(0);
        newRoot->children[0] = *root;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key);
        *root = newRoot;
    }
    else
    {
        insertNonFull(*root, key);
    }
}

// Função para inserir palavras no dicionário
int insertWord(BTreeNode *root, const char *key)
{
	if (!root)
		return 0;

	if (!searchBTree(root, key))
	{
		FILE *filePtr = fopen("../dictionary/dicionario.txt", "a+");


		insertBTree(&root, key);
		if (fprintf(filePtr, "\n%s", key) >= 0)
		{
			fclose(filePtr); // Fechar o arquivo após escrita

			return 1;
		}

		fclose(filePtr);
	}
	return 0;
}

// Função de Sugestão (Autocompletar)
void suggestWords(BTreeNode *root, const char *prefix)
{
    if (!root)
        return;

    int i = 0;

    // Itera pelas chaves do nó atual
    while (i < root->numKeys) {
        // Se a chave começa com o prefixo, sugere a palavra
        if (strncmp(prefix, root->keys[i], strlen(prefix)) == 0) {
            printf("%s, ", root->keys[i]);
        }
        i++;
    }

    // Se for uma folha, não há mais palavras para sugerir
    if (root->isLeaf)
        return;

    // Busca recursivamente nos filhos correspondentes ao prefixo
    i = 0;
    while (i < root->numKeys) {
        // Se o prefixo é menor ou igual à chave atual, pode ser que as palavras seguintes também comecem com o prefixo
        if (strncmp(prefix, root->keys[i], strlen(prefix)) <= 0) {
            suggestWords(root->children[i], prefix);
        }
        i++;
    }

    // Caso o último filho (após a última chave) também possa ter palavras que comecem com o prefixo
    suggestWords(root->children[root->numKeys], prefix);
}


// Função para imprimir as palavras em ordem lexicográfica
void printBTree(BTreeNode *root)
{
    if (!root)
    {
        return;
    }

    for (int i = 0; i < root->numKeys; i++)
    {
        if (!root->isLeaf)
        {
            printBTree(root->children[i]);
        }
        printf("%s\n", root->keys[i]);
    }

    if (!root->isLeaf)
    {
        printBTree(root->children[root->numKeys]);
    }
}

// Função que limpa a tela do console
void clear()
{
	printf("\033[H\033[2J");
}


// Função que exibe um cabeçalho
void iniciar()
{
	clear();
	printf("+----------------------+\n");
	printf("| CORRETOR ORTOGRÁFICO |\n");
	printf("+----------------------+\n\n");
}
