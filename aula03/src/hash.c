/*
 * hash.c
 *
 *  Created on: 19 de set. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>

#include "../headers/hash.h"

// Função Hash: Retorna o índice baseado no ID da leitura
int funcao_hash(int id) {
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função para inserir uma leitura na tabela hash
void inserir(TabelaHash *tabela, Sensor *sensor) {
    int indice = funcao_hash(sensor->id);  // Calcula o índice baseado no ID
    tabela->tabela[indice] = sensor;  // Insere a leitura na tabela
}

// Função para remover uma leitura na tabela hash
Sensor *remover(TabelaHash *tabela, int id){
	int indice = funcao_hash(id);
	Sensor *sensor = tabela->tabela[indice];
	tabela->tabela[indice] = NULL;
	return sensor;
}

// Função para buscar uma leitura na tabela hash pelo ID
Sensor *buscar(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);  // Calcula o índice para busca
    return tabela->tabela[indice];  // Retorna a leitura encontrada
}

// Função para exibir as leituras
void exibir_leituras(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela->tabela[i] != NULL) {
            printf("Leitura ID: %d, Medida: %.2f, Sensor: %s, Máquina: %s, Local: %s\n",
                   tabela->tabela[i]->id,
                   tabela->tabela[i]->medida,
                   tabela->tabela[i]->sensor,
                   tabela->tabela[i]->maquina,
				   tabela->tabela[i]->local);
        }
    }
}
