/*
 ============================================================================
 Name        : exames.h
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Header para manipulação de médicos
 ============================================================================
 */

#ifndef HEADERS_EXAMES_H_
#define HEADERS_EXAMES_H_

	#include "manager.h"
	#include "paciente.h"
	#include "medico.h"

	// Tipo abstrado para exames
	typedef struct Exame
	{
		int id;						// Identificador do exame
		char nome[100];  			// Nome do exame
		int idPaciente;				// Identificador do paciente
		int crm;					// Identificador do médico
		struct Data *dtRealizacao;			// Data de realização do exame
		float resultado;			// Resultado do exame
		int height;					// Altura do nó na árvore
		struct Exame *left;
		struct Exame *right;
	} Exame;

	/*
	 * Protótipos das funções
	*/

	// Procura o maior ID
	int searchMaxIdExame(Exame *exame);
	// Remove um registro do arquivo de exames
	void removeFileExame(int id);
	// Obtém a altura de um nó
	int heightExame(Exame *exame);
	// Obtém o fator de balanceamento do nó
	int getBalanceExame(Exame *exame);
	//Rotação à direita
	Exame *rightRotateExame(Exame *exame);
	//Rotação à esquerda
	Exame *leftRotateExame(Exame *exame);
	// Função que cria um novo nó
	Exame *newExameNode(int id, char name[], Paciente *paciente, Medico *medico, Data *dtRealizacao, float resultado, char novo);
	// Encontra o menor nó (usado na remoção)
	Exame *minNodeExame(Exame *exame);
	// Remove um médico da árvore
	Exame *removeExame(Exame *exame, int id);
	// Função que insere um médico na árvore
	Exame *insertExame(Exame *exame, int id, char name[], Paciente *paciente, Medico *medico, Data *dtRealizacao, float resultado, char novo);
	// Pesquisa um ID específico na árvore
	Exame *searchIndividualExame(Exame *exame, int id);
	// Pesquisa todos os exames pelo nome
	void searchExamesName(Exame *exame, Paciente *paciente, Medico *medico, char nomeExame[]);
	// Pesquisa todos os exames pela data
	void searchExamesDate(Exame *exames, Paciente *pacientes, Medico *medicos, char dtExame[]);
	// Exibe a árvore AVL em ordem
	void inOrderExame(Exame *exame, Paciente *paciente, Medico *medico);
	// Principal função de inclusão de exames
	Exame *exameManager(Exame *exame, Paciente *paciente, Medico *medico);
	// Principal função de alteração de exames
	Exame *modifyExame(Exame *exame, Paciente *paciente, Medico *medico);
	// Principal função de remoção de exames
	Exame *deleteExame(Exame *exame, Paciente *paciente, Medico *medico);
	// Principal função de pesquisa de exames
	void searchExame(Exame *exame, Paciente *paciente, Medico *medico);
	// Principal função de pesquisa de exames por nome
	void searchExameNome(Exame *exames, Paciente *pacientes, Medico *medicos);
	// Principal função de pesquisa de exames por data
	void searchExameData(Exame *exames, Paciente *pacientes, Medico *medicos);
	// Principal função de listagem de exames
	void listExame(Exame *exame, Paciente *paciente, Medico *medico);
	// Principal função que lista todos os exames de um paciente
	void listAllExamPaciente(Exame *exames, Paciente *pacientes, Medico *medicos);
	//Principal função que lista toso os exames de um médico
	void listAllExamMedical(Exame *exames, Paciente *pacientes, Medico *medicos);
	// Lista todos os exames de um paciente
	int listExamesPaciente(Exame *exames, Paciente *pacientes, Medico *medicos, int idPaciente);
	// Lista todos os exames solicitados por um médico
	int listExamesMedico(Exame *exames, Paciente *pacientes, Medico *medico);
#endif /* HEADERS_EXAMES_H_ */
