/*
 * hash.c
 *
 *  Created on: 19 de set. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/encadeamento.h"

// Função Hash: Retorna o índice baseado no ID da leitura
int funcao_hash(int id)
{
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função para criar um nov0 sensor
Sensor *criar_sensor(int id, float medida, const char *sensor, const char *maquina, const char *local)
{
	Sensor *novoSensor = (Sensor *)malloc(sizeof(Sensor));
	if (novoSensor == NULL) {
		printf("Erro ao alocar memória!\n");
		exit(1);
	}
	novoSensor->id = id;
	novoSensor->medida = medida;
	strcpy(novoSensor->sensor, sensor);
	strcpy(novoSensor->maquina, maquina);
	strcpy(novoSensor->local, local);
	novoSensor->proximo = NULL;
	return novoSensor;
}

// Função para inserir uma leitura na tabela hash
void inserir(TabelaHash *tabela, Sensor *sensor)
{
    int indice = funcao_hash(sensor->id);      // Calcula o índice baseado no ID
    sensor->proximo = tabela->tabela[indice];  // Insere no inicio da lista ligada
    tabela->tabela[indice] = sensor;           // Insere a leitura na tabela
}

// Função para remover uma leitura na tabela hash
void *remover(TabelaHash *tabela, int id){
	int indice = funcao_hash(id);
	Sensor *atual = tabela->tabela[indice];
	Sensor *anterior = NULL;

	while (atual != NULL)
	{
		if (atual->id == id)
		{
			if (anterior == NULL)
				tabela->tabela[indice] = atual->proximo;
			else
				anterior->proximo = atual->proximo;
			free(atual);
			printf("Sensor com ID %d foi excluida.\n", id);
			//return;
		}
		else
		{
			anterior = atual;
			atual = atual->proximo;
		}
	}

	printf("Sendor com ID %d não encontrado para exclusão.\n", id);
}

// Função para buscar uma leitura na tabela hash pelo ID
Sensor *buscar(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);            // Calcula o índice para busca
    Sensor *atual = tabela->tabela[indice];

    while (atual != NULL)
    {
    	if (atual->id == id)
    		return atual;		//Retorna o sensor, se encontrado
    	atual = atual->proximo;
    }
    return NULL;           // Retorna nulo se nada for encontrado
}

// Função para exibir as leituras
void exibir_leituras(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
    	Sensor *atual = tabela->tabela[i];
    	while (atual != NULL)
    	{
            printf("Leitura ID: %d, Medida: %.2f, Sensor: %s, Máquina: %s, Local: %s\n",
                   tabela->tabela[i]->id,
                   tabela->tabela[i]->medida,
                   tabela->tabela[i]->sensor,
                   tabela->tabela[i]->maquina,
				   tabela->tabela[i]->local);
            atual = atual->proximo;
        }
    }
}

// Função para contar o número total de sensores na tabela hash
int contar_elementos(TabelaHash *tabela)
{
	int total = 0;

	// Percorre todas as posições da tabela hash
	for (int i = 0; i < TAMANHO_HASH; i++) {
		Sensor *atual = tabela->tabela[i];

		// Percorre a lista ligada em cada posição
		while (atual != NULL) {
			total++;  // Incrementa o contador para cada sensor encontrado
			atual = atual->proximo;  // Vai para o próximo elemento na lista
		}
	}

	return total;
}

// Função para inserir 20 sensores predefinidas na tabela hash
void inserir_dados_predefinidos(TabelaHash *tabela)
{
	// Inserindo leituras dos sensores diretamente
	inserir(tabela, criar_sensor(100, 5.25, "termometro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(101, 101.325, "barômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(102, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(103, 5.20, "termometro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(104, 101.320, "barômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(105, 0.21, "higrômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(106, 5.23, "termometro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(107, 101.323, "barômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(108, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(109, 5.25, "termometro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(110, 104.539, "barômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(111, 0.22, "higrômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(112, 5.20, "termometro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(113, 102.398, "barômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(114, 0.19, "higrômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(115, 5.21, "termometro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(116, 101.323, "barômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(117, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(118, 5.20, "termometro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(119, 101.319, "barômetro", "Refrigerador", "Frigorifego"));
	inserir(tabela, criar_sensor(120, 0.19, "higrômetro", "Refrigerador", "Frigorifego"));
}
