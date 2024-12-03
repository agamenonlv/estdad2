/*
 ============================================================================
 Name        : medico.h
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Header para manipulação de médicos
 ============================================================================
 */

#ifndef HEADERS_MEDICO_H_
#define HEADERS_MEDICO_H_

	#include "manager.h"

	// Tipo abstrado para médicos
	typedef struct Medico
	{
		int crm;					// Número do CRM do médico
		char name[100];				// Nome do médico
		char especialidade[30];		// Especialidade médica do médico
		char uf[4];					// Unidade da federação do CRM do médico
		char celular[15];           // Celular do médico
		char email[100];           	// E-mail do médico
		int height;					// Altura do nó na árvore
		struct Medico *left;
		struct Medico *right;
	} Medico;

	/*
	 * Protótipos das funções
	*/

	// Remove um registro do arquivo de médicos
	void removeFileMedical(int crm);
	// Obtém a altura de um nó
	int heightMedical(Medico *medico);
	// Obtém o fator de balanceamento do nó
	int getBalanceMedical(Medico *medico);
	//Rotação à direita
	Medico *rightRotateMedical(Medico *medico);
	//Rotação à esquerda
	Medico *leftRotateMedical(Medico *medico);
	// Função que cria um novo nó
	Medico *newMedicalNode(int crm, char name[], char especialidade[], char uf[], char celular[], char email[], char novo);
	// Encontra o menor nó (usado na remoção)
	Medico *minNodeMedical(Medico *medico);
	// Remove um médico da árvore
	Medico *removeMedical(Medico *medico, int crm);
	// Função que insere um médico na árvore
	Medico *insertMedico(Medico *medico, int crm, char name[], char especialidade[], char uf[], char celular[], char email[], char novo);
	// Pesquisa um CRM específico na árvore
	Medico *searchIndividualMedical(Medico *medico, int crm);
	// Exibe a árvore AVL em ordem
	void inOrderMedical(Medico *medico);
	// Principal função de inclusão de médicos
	Medico *medicalManager(Medico *medico);
	// Principal função de alteração de médicos
	Medico *modifyMedical(Medico *medico);
	// Principal função de remoção de médicos
	Medico *deleteMedical(Medico *medico);
	// Principal função de pesquisa de médicos
	void searchMedical(Medico *medico);
	// Principal função de listagem de médicos
	void listMedical(Medico *medico);
#endif /* HEADERS_MEDICO_H_ */
