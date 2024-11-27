/*
 * main.c
 *
 *  Created on: 21 de nov. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/arvorepatricia.h"

int main() {
    PatriciaNode *root = NULL;
    FILE *filePtr;

    char buffer[100]; // Buffer para exibição das palavras

    // Exemplo inserção de palavras  - substituir pelo arquivo dicionario.txt
    filePtr = fopen("../dictionary/dicionario.txt", "r+");
    root = insertPatricia(root, "carro");
    root = insertPatricia(root, "car");
    root = insertPatricia(root, "cat");
    root = insertPatricia(root, "dog");
    root = insertPatricia(root, "cart");

    // Busca de palavras - exemplo
    printf("Busca por 'car': %s\n", searchPatricia(root, "car") ? "Encontrada" : "Não encontrada");
    printf("Busca por 'dog': %s\n", searchPatricia(root, "dog") ? "Encontrada" : "Não encontrada");
    printf("Busca por 'bat': %s\n", searchPatricia(root, "bat") ? "Encontrada" : "Não encontrada");

    // Exibir todas as palavras
    printf("\nPalavras na árvore:\n");
    printPatricia(root, buffer, 0);

    freePatricia(root);

    fclose(filePtr);

    return 0;
}
