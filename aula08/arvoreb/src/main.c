/*
 * main.c
 *
 *  Created on: 21 de nov. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/arvoreb.h"

int main(void) {
    BTreeNode *root = NULL;
    FILE *fileDictionaryPtr;
    char buffer[100];
    int opt;

    // Inserção de palavras na árvore B
    fileDictionaryPtr = fopen("../dictionary/dicionario.txt","r+");

    if (fileDictionaryPtr == NULL)
    {
    	fileDictionaryPtr = fopen("../dictionary/dicionario.txt", "w");

    	if (fileDictionaryPtr == NULL)
    	{
    		printf("Não há espaço necessário para criar o arquivo de dicionário\n");
    		return 1;
    	}
    }

    while (!feof(fileDictionaryPtr))
    {

		if (fscanf(fileDictionaryPtr, "%s", buffer))
    	{
    		insertBTree(&root, buffer);
    	}
    }

    fclose(fileDictionaryPtr);

    //Menu para interação com o usuário
    while(1)
    {
    	iniciar();
    	printf("Escolha uma opção:\n");
    	printf("1. Inserir uma palavra no dicionário.\n");
    	printf("2. Buscar uma palavra no dicionário.\n");
    	printf("3. Sugerir palavras (autocompletar).\n");
    	printf("0. Encerrar o programa\n");
    	printf("? ");

    	scanf("%d", &opt);
    	getchar();

    	switch (opt)
    	{
    		case (1):
				iniciar();
				printf("Entre com uma palavra para inserir no dicionário: ");
				scanf("%s", buffer);
				getchar();
				if (insertWord(root, buffer))
				{
					printf("Palavra %s inserida com sucesso!\nTecle <ENTER> para retornar\n? ", buffer);
					getchar();
				}
				else
				{
					printf("\nPalavra já cadastrada!\nTecle <ENTER> para retornar\n? ");
					getchar();
				}
				break;
    		case (2):
				iniciar();
				printf("Entre com uma palavra para pesquisar no dicionário: ");
				scanf("%s", buffer);
				getchar();
				printf("Busca: %s\n", searchWord(root, buffer) ? "Encontrada" : "Não encontrada");
				printf("Tecle <ENTER> para retornar.\n? ");
				getchar();
				break;
    		case (3):
				iniciar();
				printf("Entre com um prefixo pesquisar no dicionário: ");
				scanf("%s", buffer);
				getchar();
				printf("Sugestões para '%s':\n", buffer);
				suggestWords(root, buffer);
				printf("Tecle <ENTER> para retornar.\n? ");
				getchar();
				break;
    		case (0):
				return 0;
    		default:
    			clear();
    			printf("Opção inválida!\nTente novamente!\n? ");
    			getchar();
    	}
    }

    return 0;
}
