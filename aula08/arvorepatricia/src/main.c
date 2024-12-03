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

// Função principal para interação com o usuário
int main() {
    PatriciaNode *root = NULL;

    // Carregar dicionário de um arquivo (caso exista)
    FILE *file = fopen("../dictionary/dicionario.txt", "r");
    if (file != NULL) {
        root = loadTreeFromFile(file);
        fclose(file);
    }

    // Inserir nova palavra
    char word[100];
    printf("Digite uma palavra para inserir no dicionário: ");
    scanf("%s", word);
    insert(&root, word);

    // Buscar palavras com um prefixo
    char prefix[100];
    printf("Digite um prefixo para sugerir palavras: ");
    scanf("%s", prefix);
    printf("Palavras com o prefixo '%s':\n", prefix);
    searchPrefix(root, prefix);

    // Salvar o dicionário de volta no arquivo
    file = fopen("../dictionary/dicionario.txt", "w");
    saveTreeToFile(root, file);
    fclose(file);

    return 0;
}
