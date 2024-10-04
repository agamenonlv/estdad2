/*
 * enderecamentoHash.c
 *
 *  Created on: 1 de out. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/enderecamento.h"

int main(void)
{
	//Inicializa a tabela hash
	TabelaHash tabelaLinear = {0};
	TabelaHash tabelaQuadratica = {0};
	TabelaHash tabelaDuploHash = {0};
	int indice;

	//Inicializa cada sensor como não ocupado
	for (int i = 0; i < TAMANHO_HASH; i++)
	{
		tabelaLinear.tabela[i].ocupada = 0;
		tabelaQuadratica.tabela[i].ocupada = 0;
		tabelaDuploHash.tabela[i].ocupada = 0;
	}

	//Inserir leituras na tabela hash usando sondagem linear
	printf("\nInserção com sondagem linear\n");
	inserir_dados_predefinidos(&tabelaLinear, 'l');

	exibir_leituras(&tabelaLinear);

	//Inserir leituras na tabela hash usando sondagem quadratica
	printf("\nInserção com sondagem quadratica\n");
	inserir_dados_predefinidos(&tabelaQuadratica, 'q');

	exibir_leituras(&tabelaQuadratica);

	//Inserir leituras na tabela hash usando sondagem dublo hash
	printf("\nInserção com sondagem dublo hash\n");
	inserir_dados_predefinidos(&tabelaDuploHash, 'd');

	exibir_leituras(&tabelaDuploHash);

	printf("\n\nBusca linear na tabela HASH\n\n");

	indice = buscar(&tabelaLinear, 102, 'l');

	if (indice == -1)
		printf("\nSensor com id: %d não está na tabela HASH\n", 102);
	else
		printf("\nSensor com id: %d está na posição %d da tabela HASH\n", 102, indice);

	indice = buscar(&tabelaLinear, 202, 'l');

	if (indice == -1)
		printf("\nSensor com id: %d não está na tabela HASH\n", 202);
	else
		printf("\nSensor com id: %d está na posição %d da tabela HASH\n", 202, indice);

	printf("\n\nBusca quadratica na tabela HASH\n\n");

	indice = buscar(&tabelaLinear, 102, 'q');

	if (indice == -1)
		printf("\nSensor com id: %d não está na tabela HASH\n", 102);
	else
		printf("\nSensor com id: %d está na posição %d da tabela HASH\n", 102, indice);

	indice = buscar(&tabelaLinear, 202, 'q');

	if (indice == -1)
		printf("\nSensor com id: %d não está na tabela HASH\n", 202);
	else
		printf("\nSensor com id: %d está na posição %d da tabela HASH\n", 202, indice);

	printf("\n\nBusca duplo hashing na tabela HASH\n\n");

	indice = buscar(&tabelaLinear, 102, 'd');

	if (indice == -1)
		printf("\nSensor com id: %d não está na tabela HASH\n", 102);
	else
		printf("\nSensor com id: %d está na posição %d da tabela HASH\n", 102, indice);

	indice = buscar(&tabelaLinear, 202, 'd');

	if (indice == -1)
		printf("\nSensor com id: %d não está na tabela HASH\n", 202);
	else
		printf("\nSensor com id: %d está na posição %d da tabela HASH\n", 202, indice);

	// Remove um item das listas

	printf("Remover itens das listas");

	remover(&tabelaLinear, 203, 'l');
	remover(&tabelaQuadratica, 203, 'q');
	remover(&tabelaDuploHash, 203, 'd');

	remover(&tabelaLinear, 103, 'l');
	remover(&tabelaQuadratica, 103, 'q');
	remover(&tabelaDuploHash, 103, 'd');

	printf("\n\n");
	exibir_leituras(&tabelaLinear);

	printf("\n\n");
	exibir_leituras(&tabelaQuadratica);

	printf("\n\n");
	exibir_leituras(&tabelaDuploHash);

	return 0;
}
