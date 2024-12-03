/*
 ============================================================================
 Name        : exames.c
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Funções para a manutenção de exames
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/exames.h"
#include "../headers/medico.h"
#include "../headers/paciente.h"
#include "../headers/screen.h"

// Procura o maior ID
int searchMaxIdExame(Exame *exame)
{
	if (exame == NULL)
		return 0;

	if (exame->right == NULL)
		return exame->id;

	return searchMaxIdExame(exame->right);
}

// Obtém a altura de um nó
int heightExame(Exame *exame)
{
	if (exame == NULL)
		return -1;

	return exame->height;
}

// Remove um registro do arquivo de exames
void removeFileExame(int id)
{
	FILE *original;

	original = fopen("../csv/exames.csv", "r");
	if (original == NULL)
	{
		printf("Erro ao abrir o arquivo de exames!\nTecle <ENTER> para continuar.");
		while(getchar() != '\n');
		exit(1);
	}

	FILE *temp;
	temp = fopen("../csv/temp.csv", "w");
	if (temp == NULL)
	{
		printf("Sem espaço para realizar a operação!\nTecle <ENTER> para continuar.");
		while(getchar() != '\n');
		fclose(original);
		exit(1);
	}

	//Ler o arquivo original linha por linha e remove o registro desejado

	char linha[250];
	int idExcluir;

	while (fgets(linha, sizeof(linha), original))
	{
		sscanf(linha, "%d", &idExcluir);

		if (idExcluir != id)
			fputs(linha, temp);
	}

	// Fecha os arquivos
	fclose(temp);
	fclose(original);

	//Remove o arquivo original
	if (remove("../csv/exames.csv") != 0)
	{
		printf("Erro ao remover o arquivo 'exames.csv'\nTecle <ENTER> para continuar");
		while(getchar() != '\n');
		exit(1);
	}

	//Renomeia o arquivo temporário
	if (rename("../csv/temp.csv","../csv/exames.csv") != 0)
	{
		printf("Erro ao renomear o arquivo temporário 'temp.csv' para 'exames.csv'\nTecle <ENTER> para continuar");
		while(getchar() != '\n');
		exit(1);
	}
}

//Rotação à direita
Exame *rightRotateExame(Exame *exame)
{
	Exame *node = exame->left;
	Exame *aux = node->right;

	node->right = exame;
	exame->left = aux;

	exame->height = max(heightExame(exame->left), heightExame(exame->right)) + 1;
	node->height = max(heightExame(node->left), heightExame(node->right)) + 1;

	return node;
}

//Rotação à esquerda
Exame *leftRotateExame(Exame *exame)
{
	Exame *node = exame->right;
	Exame *aux = node->left;

	node->left = exame;
	exame->right = aux;

	exame->height = max(heightExame(exame->left), heightExame(exame->right)) + 1;
	node->height = max(heightExame(node->left), heightExame(node->right)) + 1;

	return node;
}

// Obtém o fator de balanceamento do nó
int getBalanceExame(Exame *exame)
{
	if (exame == NULL)
		return 0;

	return heightExame(exame->left) - heightExame(exame->right);
}

// Função que cria um novo nó
Exame *newExameNode(int id, char name[], Paciente *paciente, Medico *medico, Data *realizacao, float resultado, char novo)
{
	Exame *newNode = (Exame*)malloc(sizeof(Exame));

	// Insere os dados dados na árvore
	newNode->id = id;
	strcpy(newNode->nome, name);
	newNode->idPaciente = paciente->id;
	newNode->crm = medico->crm;
	newNode->dtRealizacao = realizacao;
	newNode->resultado = resultado;

	//Insere os dados no arquivo
	if (novo == 's')
	{
		FILE *file;

		file = fopen("../csv/exames.csv", "a");
		fprintf(file, "%d;%s;%d;%d;%s;%.4f\n", id, name, paciente->id, medico->crm, getData(realizacao), resultado);
		fclose(file);
	}

	return newNode;
}

//Função que insere um médico na árvore
Exame *insertExame(Exame *exame, int id, char name[], Paciente *paciente, Medico *medico, Data *realizacao, float resultado, char novo)
{
	if (exame == NULL)
		return newExameNode(id, name, paciente, medico, realizacao, resultado, novo);

	// Comparação com o CRM do nó para decidir a posição na árvore
	if (id < exame->id)
		exame->left = insertExame(exame->left, id, name, paciente, medico, realizacao, resultado, novo);
	else if (id > exame->id)
		exame->right = insertExame(exame->right, id, name, paciente, medico, realizacao, resultado, novo);
	else // CRMs ducplicados não são permitidos na árvore
		return exame;

	//Atualiza a altura do nó ancestral
	exame->height = 1 + max(heightExame(exame->left), heightExame(exame->right));

	//Obtém o balanço do nó
	int balance = getBalanceExame(exame);

	/*
	 * Casos de rotação para balanceamento
	*/

	// Caso Esquerda->Esquerda
	if (balance > 1 && id < exame->left->id)
		return rightRotateExame(exame);

	// Caso Direita->Direita
	if (balance < -1 && id > exame->right->id)
		return leftRotateExame(exame);

	// Caso Esquerda->Direita
	if (balance > 1 && id > exame->left->id)
	{
		exame->left = leftRotateExame(exame->left);
		return rightRotateExame(exame);
	}

	// Caso Direita->Esquerda
	if (balance < -1 && id < exame->right->id)
	{
		exame->right = rightRotateExame(exame->right);
		return leftRotateExame(exame);
	}

	return exame;
}

// Encontra o menor nó (usado na remoção)
Exame *minNodeExame(Exame *exame)
{
	Exame *current = exame;

	while (current && current->left != NULL)
		current = current->left;
	return current;
}

// Remove um médico da árvore
Exame *removeExame(Exame *exame, int id)
{
	if (exame == NULL)
		return exame;

	// 1. Encontrar o nó a ser removido
	if (id < exame->id)
		exame->left = removeExame(exame->left, id);
	else if (id > exame->id)
		exame->right = removeExame(exame->right, id);
	else
	{
		// Caso 1: nós com um único filho ou nenhum filho
		if (exame->left == NULL)
		{
			Exame *temp = exame->right;
			removeFileExame(exame->id);
			free(exame);
			return temp;
		}
		else if (exame->right == NULL)
		{
			Exame *temp = exame->left;
			removeFileExame(exame->id);
			free(exame);
			return temp;
		}

		// Caso 2: nó com dois filhos
		// Encontre o menor nó da subárvore direita (sucessor em ordem)
		Exame *temp = minNodeExame(exame->right);

		//Copia o valor do sucessor para este nó
		exame->id = temp->id;
		strcpy(exame->nome, temp->nome);
		exame->idPaciente = temp->idPaciente;
		exame->crm = temp->crm;
		exame->dtRealizacao = temp->dtRealizacao;
		exame->resultado = temp->resultado;

		//Remove o sucessor
		exame->right = removeExame(exame->right, temp->id);
	}

	//Se a árvore tiver apenas um nó, retorna NULL
	if (exame == NULL)
		return exame;

	// 2. Atualiza a altura do nó
	exame->height = 1 + max(heightExame(exame->left), heightExame(exame->right));

	// 3. Verifique o fator de balanceamento e balanceie a árvore
	int balance = getBalanceExame(exame);

	/*
	 * Se necessário, rotaciona a árvore
	 */

	// Caso 1: Rotação à esquerda
	if (balance > 1 && getBalanceExame(exame->left) >= 0)
		return rightRotateExame(exame);

	// Caso 2: Rotação à direita
	if (balance < -1 && getBalanceExame(exame->right) <= 0)
		return leftRotateExame(exame);

	// Caso 3: Rotação dupla à esquerda
	if (balance > 1 && getBalanceExame(exame->left) < 0)
	{
		exame->left = leftRotateExame(exame->left);
		return rightRotateExame(exame);
	}

	// Caso 4: Rotação dupla à direita
	if (balance < -1 && getBalanceExame(exame->right) > 0)
	{
		exame->right = rightRotateExame(exame->right);
		return leftRotateExame(exame);
	}

	return exame;
}

// Pesquisa um CRM específico na árvore
Exame *searchIndividualExame(Exame *exame, int id)
{
	if (exame == NULL)
		return exame;

	if (id == exame->id)
		return exame;
	else if (id < exame->id)
		return searchIndividualExame(exame->left, id);
	else
		return searchIndividualExame(exame->right, id);
}

// Pesquisa todos os exames pelo nome
void searchExamesName(Exame *exame, Paciente *paciente, Medico *medico, char nomeExame[])
{
	if (exame == NULL)
		return;

	Paciente *auxPaciente;
	Medico *auxMedico;

	if (strcmp(exame->nome, nomeExame) == 0)
	{
		printf("ID: %d\n", exame->id);
		printf("Nome: %s\n", exame->nome);
		auxPaciente = searchIndividualPaciente(paciente, exame->idPaciente);
		printf("Paciente: %s - ID: %d\n", auxPaciente->name, auxPaciente->id);
		auxMedico = searchIndividualMedical(medico, exame->crm);
		printf("Médico: %s\n", auxMedico->name);
		printf("CRM/UF: %d/%s\n", auxMedico->crm, auxMedico->uf);
		printf("Data de realização do exame: %s\n", getData(exame->dtRealizacao));
		printf("Resultado: %.4f\n", exame->resultado);
		printf("--------------------------\n");
	}

	searchExamesName(exame->left, paciente, medico, nomeExame);

	searchExamesName(exame->right, paciente, medico, nomeExame);
}

// Pesquisa todos os exames pela data
void searchExamesDate(Exame *exames, Paciente *pacientes, Medico *medicos, char dtExame[])
{
	if (exames == NULL)
		return;

	Paciente *auxPaciente;
	Medico *auxMedico;

	if (strcmp(getData(exames->dtRealizacao), dtExame) == 0)
	{
		printf("ID: %d\n", exames->id);
		printf("Nome: %s\n", exames->nome);
		auxPaciente = searchIndividualPaciente(pacientes, exames->idPaciente);
		printf("Paciente: %s - ID: %d\n", auxPaciente->name, auxPaciente->id);
		auxMedico = searchIndividualMedical(medicos, exames->crm);
		printf("Médico: %s\n", auxMedico->name);
		printf("CRM/UF: %d/%s\n", auxMedico->crm, auxMedico->uf);
		printf("Data de realização do exame: %s\n", getData(exames->dtRealizacao));
		printf("Resultado: %.4f\n", exames->resultado);
		printf("--------------------------\n");
	}

	searchExamesDate(exames->left, pacientes, medicos, dtExame);

	searchExamesDate(exames->right, pacientes, medicos, dtExame);
}

// Exibe a árvore AVL em ordem
void inOrderExame(Exame *exame, Paciente *paciente, Medico *medico)
{
	if (exame != NULL)
	{
		Paciente *auxPaciente;
		Medico *auxMedico;
		inOrderExame(exame->left, paciente, medico);
		printf("ID: %d\n", exame->id);
		printf("Nome: %s\n", exame->nome);
		auxPaciente = searchIndividualPaciente(paciente, exame->idPaciente);
		printf("Paciente: %s\n", auxPaciente->name);
		auxMedico = searchIndividualMedical(medico, exame->crm);
		printf("Médico: %s\n", auxMedico->name);
		printf("CRM/UF: %d/%s\n", auxMedico->crm, auxMedico->uf);
		printf("Data de realização do exame: %s\n", getData(exame->dtRealizacao));
		printf("Resultado: %.4f\n", exame->resultado);
		printf("--------------------------\n");
		inOrderExame(exame->right, paciente, medico);
	}
}

// Principal função de manipulação dos exame
Exame *exameManager(Exame *exame, Paciente *paciente, Medico *medico)
{
	int id;
	char nomeExame[100];
	int idPaciente;
	int crm;
	Paciente *auxPaciente;
	Medico *auxMedico;
	int dia;
	int mes;
	int ano;
	float resultado;

	//Entra com os dados de cada exame
	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|       Inclusão de Exames       |\n");
		printf("+--------------------------------+\n");
		printf("Nome do exame [<ENTER> para sair]: ");
		fgets(nomeExame, 100, stdin);
		if (strlen(nomeExame) == 1)
			break;
		nomeExame[strcspn(nomeExame, "\n")] = 0;
		printf("Código do paciente: ");
		scanf("%d", &idPaciente);
		getchar();
		printf("CRM: ");
		scanf("%d", &crm);
		getchar();
		printf("Data da realização do exame:\n");
		printf("Dia: ");
		scanf("%d", &dia);
		getchar();
		printf("Mês: ");
		scanf("%d", &mes);
		getchar();
		printf("Ano: ");
		scanf("%d", &ano);
		getchar();
		printf("Resultado do exame: ");
		scanf("%f", &resultado);
		getchar();

		id = 1 + searchMaxIdExame(exame);
		auxPaciente = searchIndividualPaciente(paciente, idPaciente);
		auxMedico = searchIndividualMedical(medico, crm);

		exame = insertExame(exame, id, nomeExame, auxPaciente, auxMedico, setDataInt(dia, mes, ano), resultado, 's');

		printf("Exame incluído com sucesso! Tecle <ENTER> para incluir novo médico.");
		while (getchar() != '\n');
	}

	return exame;
}


// Principal função de alteração de exames
Exame *modifyExame(Exame *exame, Paciente *paciente, Medico *medico)
{
	if (exame == NULL)
	{
		printf("Não há nehum exame cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return exame;
	}


	Exame *aux;
	Paciente *auxPaciente;
	Medico *auxMedico;
	Data *data;
	int id;
	char nome[100];
	int dia;
	int mes;
	int ano;
	float resultado;

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|    Alterar dados dos exames    |\n");
		printf("+--------------------------------+\n");
		printf("ID do exame [0 para sair]: ");
		scanf("%d", &id);
		getchar();

		if (id == 0)
			break;

		aux = searchIndividualExame(exame, id);

		if (aux == NULL)
		{
			printf("Não há nenhum exame com ID %d cadastrado!\nTecle <ENTER> para continuar.", id);
			while(getchar() != '\n');
			continue;
		}

		auxPaciente = searchIndividualPaciente(paciente, exame->idPaciente);
		auxMedico = searchIndividualMedical(medico, exame->crm);

		printf("------------------------------------\n");
		printf("Dados do exame\n\n");
		printf("Nome: %s\n", aux->nome);
		printf("Paciente: %s - %d\n", auxPaciente->name, auxPaciente->id);
		printf("Médico: %s - %d/%s\n", auxMedico->name, auxMedico->crm, auxMedico->uf);
		printf("Data do exame: %s\n", getData(aux->dtRealizacao));
		printf("Resultado: %.4f\n", aux->resultado);
		printf("------------------------------------\n");
		printf("\nDigite apenas o(s) dado(s) que será(ão) modificado(s)!\n\n");
		printf("Entre com os novos dados do exame:\n\n");
		printf("Nome: ");
		fgets(nome, 100, stdin);
		nome[strcspn(nome, "\n")] = 0;
		printf("Data de realização do exame:\n");
		printf("Dia: ");
		scanf("%d", &dia);
		getchar();
		printf("Mês: ");
		scanf("%d", &mes);
		getchar();
		printf("Ano: ");
		scanf("%d", &ano);
		getchar();
		printf("Resultado: ");
		scanf("%f", &resultado);
		getchar();

		//Prepara os dados para modificação
		if (strlen(nome) == 0)
			strcpy(nome, aux->nome);
		if (dia == 0)
			data = exame->dtRealizacao;
		else
			data = setDataInt(dia, mes, ano);
		if (resultado == 0)
			resultado = aux->resultado;

		exame = removeExame(exame, id);
		exame = insertExame(exame, id, nome, paciente, medico, data, resultado, 's');

		printf("Os dados do exame com ID nº %d foi alterado com sucesso!\nTecle <ENTER> para excluir outro médico.", id);
		while (getchar() != '\n');
	}

	free(aux);
	return exame;
}

// Principal função de remoção de exame
Exame *deleteExame(Exame *exame, Paciente *paciente, Medico *medico)
{
	int id;

	if (exame == NULL)
	{
		printf("Não há nehum exame cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return exame;
	}

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|       Remosão de Exames        |\n");
		printf("+--------------------------------+\n");
		printf("ID do exame [0 para sair]: ");
		scanf("%d", &id);
		getchar();

		if (id == 0)
			break;

		exame = removeExame(exame, id);

		printf("O exame com ID nº %d foi removido com sucesso!\nTecle <ENTER> para excluir outro médico.", id);
		while (getchar() != '\n');
	}

	return exame;
}

// Principal função de pesquisa de exame
void searchExame(Exame *exame, Paciente *paciente, Medico *medico)
{
	int id;

	if (exame == NULL)
	{
		printf("Não há nehum exame cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return;
	}

	Exame *aux = NULL;
	Paciente *auxPaciente = NULL;
	Medico *auxMedico = NULL;

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|      Pesquisa de Exames        |\n");
		printf("+--------------------------------+\n");
		printf("ID do exame [0 para sair]: ");
		scanf("%d", &id);
		getchar();

		if (id == 0)
			break;

		aux = searchIndividualExame(exame, id);

		if (aux == NULL)
			printf("Não há nenhum exame com ID %d cadastrado!", id);
		else
		{
			auxPaciente = searchIndividualPaciente(paciente, exame->idPaciente);
			auxMedico = searchIndividualMedical(medico, exame->crm);
			printf("Dados do exame\n\n");
			printf("Nome: %s\n", aux->nome);
			printf("Paciente: %s - Matrícula: %d\n", auxPaciente->name, auxPaciente->id);
			printf("Médico: %s - CRM: %d/%s\n", auxMedico->name, auxMedico->crm, auxMedico->uf);
			printf("Data do exame: %s\n", getData(aux->dtRealizacao));
			printf("Resultado: %.4f\n", aux->resultado);
		}

		printf("Tecle <ENTER> para continuar.");
		while(getchar() != '\n');
	}
}

// Principal função de pesquisa de exames por nome
void searchExameNome(Exame *exame, Paciente *pacientes, Medico *medicos)
{
	if (exame == NULL)
	{
		printf("Não há nehum exame cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return;
	}

	char nomeExame[100];

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|  Pesquisa de Exames por Nome   |\n");
		printf("+--------------------------------+\n");
		printf("Nome do exame [<ENTER> para sair]: ");
		fgets(nomeExame, 100, stdin);

		if (strcmp(nomeExame,"\n") == 0)
			break;

		nomeExame[strcspn(nomeExame, "\n")] = 0;

		searchExamesName(exame, pacientes, medicos, nomeExame);

		printf("Tecle <ENTER> para continuar.");
		while(getchar() != '\n');
	}
}

// Principal função de pesquisa de exames por data
void searchExameData(Exame *exames, Paciente *pacientes, Medico *medicos)
{
	if (exames == NULL)
	{
		printf("Não há nehum exame cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return;
	}

	int dia;
	int mes;
	int ano;

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|  Pesquisa de Exames por Data   |\n");
		printf("+--------------------------------+\n");
		printf("Data de realização do exame:\n");
		printf("Dia [0 para sair]: ");
		scanf("%d", &dia);
		getchar();

		if (dia == 0)
			break;

		printf("Mês: ");
		scanf("%d", &mes);
		getchar();
		printf("Ano: ");
		scanf("%d", &ano);
		getchar();

		searchExamesDate(exames, pacientes, medicos, getData(setDataInt(dia, mes, ano)));

		printf("Tecle <ENTER> para continuar.");
		while(getchar() != '\n');
	}
}

// Principal função de listagem de exames
void listExame(Exame *exame, Paciente *paciente, Medico *medico)
{
	if (exame == NULL)
	{
		printf("Não há exames cadastrados! Tecle <ENTER> para continuar");
		while (getchar() != '\n');
		return;
	}

	cabecalho();
	printf("+--------------------------------+\n");
	printf("|      Relação de Exames         |\n");
	printf("+--------------------------------+\n");

	inOrderExame(exame, paciente, medico);
	printf("\nTecle <ENTER> para retornar.");
	while (getchar() != '\n');
}

// Lista todos os exames de um paciente
void listAllExamPaciente(Exame *exames, Paciente *pacientes, Medico *medicos)
{
	if (exames == NULL)
	{
		printf("Não há exames cadastrados! Tecle <ENTER> para continuar");
		while (getchar() != '\n');
		return;
	}

	char nomePaciente[100];
	int idPaciente;

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("| Relação de Exames por Paciente |\n");
		printf("+--------------------------------+\n");
		printf("Nome do paciente [<ENTER> para sair]: ");
		fgets(nomePaciente, 100, stdin);

		if (strcmp(nomePaciente,"\n") == 0)
			break;

		nomePaciente[strcspn(nomePaciente, "\n")] = 0;
		idPaciente = searchPacienteNome(pacientes, nomePaciente);

		if (idPaciente == -1)
			printf("Não há nenhum paciente com o nome '%s'.\n", nomePaciente);
		else
		{
			Paciente *auxPaciente;
			auxPaciente = searchIndividualPaciente(pacientes, exames->idPaciente);
			printf("\nPaciente: %s - ID: %d\n\n", auxPaciente->name, auxPaciente->id);
			listExamesPaciente(exames, pacientes, medicos, idPaciente);
		}

		printf("Tecle <ENTER> para continuar.");
		while(getchar() != '\n');
	}
}

// Lista todos os exames de um paciente
int listExamesPaciente(Exame *exames, Paciente *pacientes, Medico *medicos, int idPaciente)
{
	if (exames == NULL)
		return -1;

	Medico *auxMedico;

	if (exames->idPaciente == idPaciente)
	{
		printf("ID: %d\n", exames->id);
		printf("Nome: %s\n", exames->nome);
		auxMedico = searchIndividualMedical(medicos, exames->crm);
		printf("Médico: %s\n", auxMedico->name);
		printf("CRM/UF: %d/%s\n", auxMedico->crm, auxMedico->uf);
		printf("Data de realização do exame: %s\n", getData(exames->dtRealizacao));
		printf("Resultado: %.4f\n", exames->resultado);
		printf("--------------------------\n");
	}

	int retorno;

	retorno = listExamesPaciente(exames->left, pacientes, medicos, idPaciente);

	if (retorno != -1)
		return retorno;

	return listExamesPaciente(exames->right, pacientes, medicos, idPaciente);
}

//Principal função que lista toso os exames de um médico
void listAllExamMedical(Exame *exames, Paciente *pacientes, Medico *medicos)
{
	if (exames == NULL)
	{
		printf("Não há exames cadastrados! Tecle <ENTER> para continuar");
		while (getchar() != '\n');
		return;
	}

	int crm;
	Medico *auxMedico;

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|  Relação de Exames por Médico  |\n");
		printf("+--------------------------------+\n");
		printf("CRM do médico [<0> para sair]: ");
		scanf("%d", &crm);
		getchar();

		if (crm == 0)
			break;

		auxMedico = searchIndividualMedical(medicos, crm);

		if (auxMedico == NULL)
			printf("Não há nenhum médico com o CRM '%d'.\n", crm);
		else
		{
			printf("\nMédico: %s - CRM/UF: %d/%s\n\n", auxMedico->name, auxMedico->crm, auxMedico->uf);
			listExamesMedico(exames, pacientes, auxMedico);
		}

		printf("Tecle <ENTER> para continuar.");
		while(getchar() != '\n');
	}
}

// Lista todos os exames solicitados por um médico
int listExamesMedico(Exame *exames, Paciente *pacientes, Medico *medico)
{
	if (exames == NULL)
		return -1;

	Paciente *paciente;

	if (exames->crm == medico->crm)
	{
		printf("ID: %d\n", exames->id);
		printf("Nome: %s\n", exames->nome);
		paciente = searchIndividualPaciente(pacientes, exames->idPaciente);
		printf("Paciente: %s - ID: %d\n", paciente->name, paciente->id);
		printf("Data de realização do exame: %s\n", getData(exames->dtRealizacao));
		printf("Resultado: %.4f\n", exames->resultado);
		printf("--------------------------\n");
	}

	int retorno;

	retorno = listExamesMedico(exames->left, pacientes, medico);

	if (retorno != -1)
		return retorno;

	return listExamesMedico(exames->right, pacientes, medico);
}
