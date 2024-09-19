/*
 * hash.h
 *
 *  Created on: 19 de set. de 2024
 *      Author: agamenon
 */

#ifndef HEADERS_HASH_H_
#define HEADERS_HASH_H_

	#define TAMANHO_HASH 10

	// Estrutura para representar uma leitura de algum sensor
	typedef struct {
		int id;               // ID único da leitura
		float medida;         // Leitura do sensor
		char sensor[50];      // Tipo do sensor
		char maquina[50];     // Máquina no qual o sensor está instalado
		char local[50];       // Local onde o sensor está localizado
	} Sensor;

	// Estrutura da Tabela Hash
	typedef struct {
		Sensor *tabela[TAMANHO_HASH];  // Array de ponteiros para armazenar leituras dos sensores
	} TabelaHash;

	// Função Hash: Retorna o índice baseado no ID da transação
	int funcao_hash(int id);

	// Função para inserir uma leitura na tabela hash
	void inserir(TabelaHash *tabela, Sensor *sensor);

	// Função para remover uma leitura na tabela hash
	Sensor *remover(TabelaHash *tabela, int id);

	// Função para buscar uma leitura na tabela hash pelo ID
	Sensor *buscar(TabelaHash *tabela, int id);

	// Função para exibir leituras
	void exibir_leituras(TabelaHash *tabela);

#endif /* HEADERS_HASH_H_ */
