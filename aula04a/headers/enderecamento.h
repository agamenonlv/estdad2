/*
 * hash.h
 *
 *  Created on: 19 de set. de 2024
 *      Author: agamenon
 */

#ifndef HEADERS_ENDERECAMENTO_H_
#define HEADERS_ENDERECAMENTO_H_

	#define TAMANHO_HASH 10

	// Estrutura para representar uma leitura de algum sensor
	typedef struct
	{
		int id;                 // ID único da leitura
		float medida;           // Leitura do sensor
		char sensor[50];        // Tipo do sensor
		char maquina[50];       // Máquina no qual o sensor está instalado
		char local[50];         // Local onde o sensor está localizado
		int ocupada;            // Flag para indicar se o slot está ocupado
	} Sensor;

	// Estrutura da Tabela Hash
	typedef struct
	{
		Sensor tabela[TAMANHO_HASH];  // Array de ponteiros para armazenar leituras dos sensores
	} TabelaHash;

	// Função Hash: Retorna o índice baseado no ID da transação
	int funcao_hash(int id);

	// Função hash para duplo hashing
	int hash2(int id);

	// Sondagem linear
	int sondagem_linear(TabelaHash *tabela, int id);

	// Sondagem quadrática
	int sondagem_quadratica(TabelaHash *tabela, int id);

	// Duplo hashing
	int duplo_hashing(TabelaHash *tabela, int id);

	// Função para criar um nov0 sensor
	Sensor criar_sensor(int id, float medida, const char *sensor, const char *maquina ,const char *local);

	// Função para inserir uma leitura na tabela hash usando sondagem linear
	void inserir_linear(TabelaHash *tabela, Sensor sensor);

	// Função para inserir uma leitura na tabela hash usando sondagem quadrática
	void inserir_quadratica(TabelaHash *tabela, Sensor sensor);

	// Função para inserir uma leitura na tabela hash usando duplo hashing
	void inserir_duplo_hashing(TabelaHash *tabela, Sensor sensor);

	// Função para remover uma leitura na tabela hash
	void remover(TabelaHash *tabela, int id, char sondagem);

	// Função para buscar uma leitura na tabela hash pelo ID
	int buscar(TabelaHash *tabela, int id, char sondagem);

	// Função para exibir leituras
	void exibir_leituras(TabelaHash *tabela);

	// Função para inserir 20 sensores predefinidas na tabela hash
	void inserir_dados_predefinidos(TabelaHash *tabela, char tipo);

#endif /* HEADERS_ENDERECAMENTO_H_ */
