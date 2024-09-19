/*
 * processamentoDadosSensoresSistemaMonitoramentoIoT.c
 *
 *  Created on: 19 de set. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>

#include "../headers/hash.h"

// Função principal para demonstrar o uso da tabela hash com leitura de sensores
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela = {NULL};

    // Criação de algumas leituras de sensores
    Sensor sensor1 = {101, 28.3, "Termômetro", "Frezadeira", "São Paulo"};
    Sensor sensor2 = {102, 28.5, "Termômetro", "Compressor", "Rio de Janeiro"};
    Sensor sensor3 = {103, 28.2, "Termômetro", "Cortadeira", "Miami"};

    // Insere as transações na tabela hash
    inserir(&tabela, &sensor1);
    inserir(&tabela, &sensor2);
    inserir(&tabela, &sensor3);

    // Busca por uma transação específica
    Sensor *t = buscar(&tabela, 102);
    if (t != NULL) {
        printf("Sensor encontrado: ID: %d, Medida: %.2f, Sensor: %s, Máquina: %s, Local: %s\n\n",
               t->id, t->medida, t->sensor, t->maquina,t->local);
    } else {
        printf("Sensor não encontrado.\n");
    }

    // Exibir todas as transações suspeitas
    printf("\nLista de leituras:\n");
    exibir_leituras(&tabela);

    Sensor *s = remover(&tabela, 102);
    if (s == NULL)
    {
    	printf("Sensor não encontrado.\n");
    }
    else
    {
    	printf("\nLista de leituras:\n");
		exibir_leituras(&tabela);
    }

    return 0;
}
