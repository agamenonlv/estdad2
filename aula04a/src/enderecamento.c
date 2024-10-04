/*
 * hash.c
 *
 *  Created on: 19 de set. de 2024
 *      Author: agamenon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/enderecamento.h"

// Função Hash: Retorna o índice baseado no ID da leitura
int funcao_hash(int id)
{
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função hash para duplo hashing
int hash2(int id) {
    return 7 - (id % 7);  // Segunda função hash para duplo hashing
}

// Sondagem linear
int sondagem_linear(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (indice + 1) % TAMANHO_HASH;  // Avança linearmente
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Sondagem quadrática
int sondagem_quadratica(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    int i = 1;
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (funcao_hash(id) + i * i) % TAMANHO_HASH;  // Avança quadraticamente
        i++;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Duplo hashing
int duplo_hashing(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    int step = hash2(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (indice + step) % TAMANHO_HASH;  // Usa duplo hashing
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Função para criar um novo sensor
Sensor criar_sensor(int id, float medida, const char *sensor, const char *maquina, const char *local)
{
	Sensor novoSensor;
	novoSensor.id = id;
	novoSensor.medida = medida;
	strcpy(novoSensor.sensor, sensor);
	strcpy(novoSensor.maquina, maquina);
	strcpy(novoSensor.local, local);
	novoSensor.ocupada = 1;
	return novoSensor;
}

// Função para inserir uma leitura na tabela hash usando sondagem linear
void inserir_linear(TabelaHash *tabela, Sensor sensor)
{
    int indice = funcao_hash(sensor.id);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = sensor;
    } else {
        // Se houver colisão, chama a sondagem linear
        int novo_indice = sondagem_linear(tabela, sensor.id);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = sensor;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para inserir uma leitura na tabela hash usando sondagem quadrática
void inserir_quadratica(TabelaHash *tabela, Sensor sensor)
{
    int indice = funcao_hash(sensor.id);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = sensor;
    } else {
        // Se houver colisão, chama a sondagem quadrática
        int novo_indice = sondagem_quadratica(tabela, sensor.id);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = sensor;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para inserir uma leitura na tabela hash usando duplo hashing
void inserir_duplo_hashing(TabelaHash *tabela, Sensor sensor)
{
    int indice = funcao_hash(sensor.id);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = sensor;
    } else {
        // Se houver colisão, chama o duplo hashing
        int novo_indice = duplo_hashing(tabela, sensor.id);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = sensor;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}


// Função para remover uma leitura na tabela hash
void remover(TabelaHash *tabela, int id, char sondagem)
{
    int indice = funcao_hash(id); // Calcula o índice inicial baseado no ID
    int tentativas = 0;

    while (tentativas < TAMANHO_HASH) {
        // Verifica se o slot está ocupado
        if (tabela->tabela[indice].ocupada) {
            // Verifica se o ID corresponde
            if (tabela->tabela[indice].id == id) {
                tabela->tabela[indice].ocupada = 0; // Libera o sensor
                return; // Sai da função após remoção
            }
        }

        // Se encontramos um slot vazio, o sensor não está na tabela
        if (!tabela->tabela[indice].ocupada) {
            printf("O sensor ID: %d não está na lista\n", id);
            return;
        }

        // Avança para o próximo índice, dependendo do método de sondagem
        switch (sondagem) {
            case 'l':
                indice = (indice + 1) % TAMANHO_HASH; // Sondagem linear
                break;
            case 'q':
                indice = (indice + (tentativas * tentativas)) % TAMANHO_HASH; // Sondagem quadrática
                break;
            case 'd':
                indice = (indice + hash2(id)) % TAMANHO_HASH; // Duplo hashing
                break;
        }
        tentativas++;
    }
    printf("O sensor ID: %d não está na lista\n", id);
}

// Função para buscar uma leitura na tabela hash pelo ID
int buscar(TabelaHash *tabela, int id, char sondagem)
{
    int indice = funcao_hash(id); // Calcula o índice inicial baseado no ID
    int tentativas = 0;

    while (tentativas < TAMANHO_HASH) {
        // Verifica se o slot está ocupado
        if (tabela->tabela[indice].ocupada) {
            // Verifica se o ID corresponde
            if (tabela->tabela[indice].id == id) {
                return indice; // Retorna o índice do sensor na tabela HASH
            }
        } else {
            // Se encontramos um slot vazio, o sensor não está na tabela
            break;
        }

        // Avança para o próximo índice, dependendo do método de sondagem
        switch (sondagem) {
            case 'l':
                indice = (indice + 1) % TAMANHO_HASH; // Sondagem linear
                break;
            case 'q':
                indice = (indice + (tentativas * tentativas)) % TAMANHO_HASH; // Sondagem quadrática
                break;
            case 'd':
                indice = (indice + hash2(id)) % TAMANHO_HASH; // Duplo hashing
                break;
        }
        tentativas++;
    }

    return -1; // Indica que não encontrou o sensor
}

// Função para exibir as leituras
void exibir_leituras(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
    	if (tabela->tabela[i].ocupada)
    	{
            printf("Leitura ID: %d, Medida: %.2f, Sensor: %s, Máquina: %s, Local: %s (Índice: %d)\n",
                   tabela->tabela[i].id,
                   tabela->tabela[i].medida,
                   tabela->tabela[i].sensor,
                   tabela->tabela[i].maquina,
				   tabela->tabela[i].local,
				   i);
        }
    }
}

// Função para inserir 20 sensores predefinidas na tabela hash
void inserir_dados_predefinidos(TabelaHash *tabela, char tipo)
{
	// Inserindo leituras dos sensores diretamente
	switch (tipo)
	{
		case ('l'):
		//{
			inserir_linear(tabela, criar_sensor(100, 5.25, "termometro", "Refrigerador", "Frigorifego"));
			inserir_linear(tabela, criar_sensor(101, 101.325, "barômetro", "Refrigerador", "Frigorifego"));
			inserir_linear(tabela, criar_sensor(102, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
			inserir_linear(tabela, criar_sensor(103, 5.20, "termometro", "Refrigerador", "Frigorifego"));
			inserir_linear(tabela, criar_sensor(104, 101.320, "barômetro", "Refrigerador", "Frigorifego"));
			inserir_linear(tabela, criar_sensor(105, 0.21, "higrômetro", "Refrigerador", "Frigorifego"));
			inserir_linear(tabela, criar_sensor(106, 5.23, "termometro", "Refrigerador", "Frigorifego"));
			inserir_linear(tabela, criar_sensor(107, 101.323, "barômetro", "Refrigerador", "Frigorifego"));
			inserir_linear(tabela, criar_sensor(108, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
			inserir_linear(tabela, criar_sensor(109, 5.25, "termometro", "Refrigerador", "Frigorifego"));
			break;
		//}
		case ('q'):
		//{
			inserir_quadratica(tabela, criar_sensor(100, 5.25, "termometro", "Refrigerador", "Frigorifego"));
			inserir_quadratica(tabela, criar_sensor(101, 101.325, "barômetro", "Refrigerador", "Frigorifego"));
			inserir_quadratica(tabela, criar_sensor(102, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
			inserir_quadratica(tabela, criar_sensor(103, 5.20, "termometro", "Refrigerador", "Frigorifego"));
			inserir_quadratica(tabela, criar_sensor(104, 101.320, "barômetro", "Refrigerador", "Frigorifego"));
			inserir_quadratica(tabela, criar_sensor(105, 0.21, "higrômetro", "Refrigerador", "Frigorifego"));
			inserir_quadratica(tabela, criar_sensor(106, 5.23, "termometro", "Refrigerador", "Frigorifego"));
			inserir_quadratica(tabela, criar_sensor(107, 101.323, "barômetro", "Refrigerador", "Frigorifego"));
			inserir_quadratica(tabela, criar_sensor(108, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
			inserir_quadratica(tabela, criar_sensor(109, 5.25, "termometro", "Refrigerador", "Frigorifego"));
			break;
		//}
		case ('d'):
			inserir_duplo_hashing(tabela, criar_sensor(100, 5.25, "termometro", "Refrigerador", "Frigorifego"));
			inserir_duplo_hashing(tabela, criar_sensor(101, 101.325, "barômetro", "Refrigerador", "Frigorifego"));
			inserir_duplo_hashing(tabela, criar_sensor(102, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
			inserir_duplo_hashing(tabela, criar_sensor(103, 5.20, "termometro", "Refrigerador", "Frigorifego"));
			inserir_duplo_hashing(tabela, criar_sensor(104, 101.320, "barômetro", "Refrigerador", "Frigorifego"));
			inserir_duplo_hashing(tabela, criar_sensor(105, 0.21, "higrômetro", "Refrigerador", "Frigorifego"));
			inserir_duplo_hashing(tabela, criar_sensor(106, 5.23, "termometro", "Refrigerador", "Frigorifego"));
			inserir_duplo_hashing(tabela, criar_sensor(107, 101.323, "barômetro", "Refrigerador", "Frigorifego"));
			inserir_duplo_hashing(tabela, criar_sensor(108, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
			inserir_duplo_hashing(tabela, criar_sensor(109, 5.25, "termometro", "Refrigerador", "Frigorifego"));
			break;

	}
	/*inserir_linear(tabela, criar_sensor(110, 104.539, "barômetro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(111, 0.22, "higrômetro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(112, 5.20, "termometro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(113, 102.398, "barômetro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(114, 0.19, "higrômetro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(115, 5.21, "termometro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(116, 101.323, "barômetro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(117, 0.20, "higrômetro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(118, 5.20, "termometro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(119, 101.319, "barômetro", "Refrigerador", "Frigorifego"));
	inserir_linear(tabela, criar_sensor(120, 0.19, "higrômetro", "Refrigerador", "Frigorifego"));*/
}
