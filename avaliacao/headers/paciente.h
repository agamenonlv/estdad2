/*
 ============================================================================
 Name        : paciente.h
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Header para manipulação de pacientes
 ============================================================================
 */

#ifndef HEADERS_PACIENTE_H_
#define HEADERS_PACIENTE_H_

#include "manager.h"

	// Tipo abstrado para pacientes
	typedef struct Paciente
	{
		int id;						// Identificador do paciente
		char name[100];				// Nome do paciente
		struct Data *dtNascimento;          // Data de nascimento do paciente
		char celular[15];           // Telefone de contato
		char email[100];			// E-mail de contato do paciente
		int height;					// Altura do nó na árvore
		struct Paciente *left;
		struct Paciente *right;
	} Paciente;

	/*
	 * Protótipos das funções
	*/

	// Procura o maior ID
	int searchMaxId(Paciente *paciente);
	// Remove um registro do arquivo de pacientes
	void removeFilePaciente(int crm);
	// Obtém a altura de um nó
	int heightPaciente(Paciente *paciente);
	// Obtém o fator de balanceamento do nó
	int getBalancePaciente(Paciente *paciente);
	//Rotação à direita
	Paciente *rightRotatePaciente(Paciente *Paciente);
	//Rotação à esquerda
	Paciente *leftRotatePaciente(Paciente *Paciente);
	// Função que cria um novo nó
	Paciente *newPacienteNode(int id, char name[], Data *dtNascimento, char celular[], char email[], char novo);
	// Encontra o menor nó (usado na remoção)
	Paciente *minNodePaciente(Paciente *paciente);
	// Remove um médico da árvore
	Paciente *removePaciente(Paciente *paciente, int id);
	// Função que insere um médico na árvore
	Paciente *insertPaciente(Paciente *paciente, int id, char name[], Data *dtNascimento, char celular[], char email[], char novo);
	// Pesquisa um ID específico na árvore
	Paciente *searchIndividualPaciente(Paciente *paciente, int id);
	// Pesquisa o ID de um paciente pelo seu nome
	int searchPacienteNome(Paciente *paciente, char nomePaciente[]);
	// Exibe a árvore AVL em ordem
	void inOrderPaciente(Paciente *paciente);
	// Principal função de inclusão de pacientes
	Paciente *pacienteManager(Paciente *paciente);
	// Principal função de alteração de pacientes
	Paciente *modifyPaciente(Paciente *paciente);
	// Principal função de remoção de pacientes
	Paciente *deletePaciente(Paciente *paciente);
	// Principal função de pesquisa de pacientes
	void searchPaciente(Paciente *paciente);
	// Principal função de listagem de pacientes
	void listPaciente(Paciente *paciente);

#endif /* HEADERS_PACIENTE_H_ */
