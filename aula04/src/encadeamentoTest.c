/*
 * encadeamentoTest.c
 *
 *  Created on: 26 de set. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>

#include "../headers/encadeamento.h"


int main(void)
{
	TabelaHash tabela = {NULL};

	//Insere os dados na tabela
	inserir_dados_predefinidos(&tabela);

    // Exibir todas as leituras inseridas
    printf("\nTodas as leituras inseridas: %d\n", contar_elementos(&tabela));
    exibir_leituras(&tabela);

    // Busca por uma leitura específica
	printf("\nBuscar uma leitura:\n");
	Sensor *t = buscar(&tabela, 102);
	if (t != NULL) {
		printf("Leitura encontrada: ID: %d, Medida: %.2f, Sensor: %s, Máquina %s, Local: %s\n",
			   t->id, t->medida, t->sensor, t->maquina, t->local);
	} else {
		printf("Leitura não encontrada.\n");
	}

	// Excluir as leitura selecionadas
	printf("\nLeituras excluidas:\n");
	remover(&tabela, 119);

	// Exibir todas as leituras alteradas
    printf("\nTodas as leituras alteradas: %d\n", contar_elementos(&tabela));
    exibir_leituras(&tabela);

	//Termina o program sem ocorrências.
	return 0;
}
