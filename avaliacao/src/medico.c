/*
 ============================================================================
 Name        : medico.c
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Funções para a manutenção de médicos
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/medico.h"
#include "../headers/screen.h"

// Obtém a altura de um nó
int heightMedical(Medico *medico)
{
	if (medico == NULL)
		return -1;

	return medico->height;
}

// Remove um registro do arquivo de médicos
void removeFileMedical(int crm)
{
	FILE *original;

	original = fopen("../csv/medicos.csv", "r");
	if (original == NULL)
	{
		printf("Erro ao abrir o arquivo de médicos!\nTecle <ENTER> para continuar.");
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
	int crmExcluir;

	while (fgets(linha, sizeof(linha), original))
	{
		sscanf(linha, "%d", &crmExcluir);

		if (crmExcluir != crm)
			fputs(linha, temp);
	}

	// Fecha os arquivos
	fclose(temp);
	fclose(original);

	//Remove o arquivo original
	if (remove("../csv/medicos.csv") != 0)
	{
		printf("Erro ao remover o arquivo 'medicos.csv'\nTecle <ENTER> para continuar");
		while(getchar() != '\n');
		exit(1);
	}

	//Renomeia o arquivo temporário
	if (rename("../csv/temp.csv","../csv/medicos.csv") != 0)
	{
		printf("Erro ao renomear o arquivo temporário 'temp.csv' para 'medicos.csv'\nTecle <ENTER> para continuar");
		while(getchar() != '\n');
		exit(1);
	}
}

//Rotação à direita
Medico *rightRotateMedical(Medico *medico)
{
	Medico *node = medico->left;
	Medico *aux = node->right;

	node->right = medico;
	medico->left = aux;

	medico->height = max(heightMedical(medico->left), heightMedical(medico->right)) + 1;
	node->height = max(heightMedical(node->left), heightMedical(node->right)) + 1;

	return node;
}

//Rotação à esquerda
Medico *leftRotateMedical(Medico *medico)
{
	Medico *node = medico->right;
	Medico *aux = node->left;

	node->left = medico;
	medico->right = aux;

	medico->height = max(heightMedical(medico->left), heightMedical(medico->right)) + 1;
	node->height = max(heightMedical(node->left), heightMedical(node->right)) + 1;

	return node;
}

// Obtém o fator de balanceamento do nó
int getBalanceMedical(Medico *medico)
{
	if (medico == NULL)
		return 0;

	return heightMedical(medico->left) - heightMedical(medico->right);
}

// Função que cria um novo nó
Medico *newMedicalNode(int crm, char name[], char especialidade[], char uf[], char celular[], char email[], char novo)
{
	Medico *newNode = (Medico*)malloc(sizeof(Medico));

	// Insere os dados dados na árvore
	newNode->crm = crm;
	strcpy(newNode->name, name);
	strcpy(newNode->especialidade, especialidade);
	strcpy(newNode->uf, uf);
	strcpy(newNode->celular, celular);
	strcpy(newNode->email, email);

	//Insere os dados no arquivo
	if (novo == 's')
	{
		FILE *file;

		file = fopen("../csv/medicos.csv", "a");
		fprintf(file, "%d;%s;%s;%s;%s;%s\n", crm, name, especialidade, uf, celular, email);
		fclose(file);
	}

	return newNode;
}

//Função que insere um médico na árvore
Medico *insertMedico(Medico *medico, int crm, char name[], char especialidade[], char uf[], char celular[], char email[], char novo)
{
	if (medico == NULL)
		return newMedicalNode(crm, name, especialidade, uf, celular, email, novo);

	// Comparação com o CRM do nó para decidir a posição na árvore
	if (crm < medico->crm)
		medico->left = insertMedico(medico->left, crm, name, especialidade, uf, celular, email, novo);
	else if (crm > medico->crm)
		medico->right = insertMedico(medico->right, crm, name, especialidade, uf, celular, email, novo);
	else // CRMs ducplicados não são permitidos na árvore
		return medico;

	//Atualiza a altura do nó ancestral
	medico->height = 1 + max(heightMedical(medico->left), heightMedical(medico->right));

	//Obtém o balanço do nó
	int balance = getBalanceMedical(medico);

	/*
	 * Casos de rotação para balanceamento
	*/

	// Caso Esquerda->Esquerda
	if (balance > 1 && crm < medico->left->crm)
		return rightRotateMedical(medico);

	// Caso Direita->Direita
	if (balance < -1 && crm > medico->right->crm)
		return leftRotateMedical(medico);

	// Caso Esquerda->Direita
	if (balance > 1 && crm > medico->left->crm)
	{
		medico->left = leftRotateMedical(medico->left);
		return rightRotateMedical(medico);
	}

	// Caso Direita->Esquerda
	if (balance < -1 && crm < medico->right->crm)
	{
		medico->right = rightRotateMedical(medico->right);
		return leftRotateMedical(medico);
	}

	return medico;
}

// Encontra o menor nó (usado na remoção)
Medico *minNodeMedical(Medico *medico)
{
	Medico *current = medico;

	while (current && current->left != NULL)
		current = current->left;
	return current;
}

// Remove um médico da árvore
Medico *removeMedical(Medico *medico, int crm)
{
	if (medico == NULL)
		return medico;

	// 1. Encontrar o nó a ser removido
	if (crm < medico->crm)
		medico->left = removeMedical(medico->left, crm);
	else if (crm > medico->crm)
		medico->right = removeMedical(medico->right, crm);
	else
	{
		// Caso 1: nós com um único filho ou nenhum filho
		if (medico->left == NULL)
		{
			Medico *temp = medico->right;
			removeFileMedical(medico->crm);
			free(medico);
			return temp;
		}
		else if (medico->right == NULL)
		{
			Medico *temp = medico->left;
			removeFileMedical(medico->crm);
			free(medico);
			return temp;
		}

		// Caso 2: nó com dois filhos
		// Encontre o menor nó da subárvore direita (sucessor em ordem)
		Medico *temp = minNodeMedical(medico->right);

		//Copia o valor do sucessor para este nó
		medico->crm = temp->crm;
		strcpy(medico->name, temp->name);
		strcpy(medico->especialidade, temp->especialidade);
		strcpy(medico->celular, temp->celular);
		strcpy(medico->email, temp->email);
		strcpy(medico->uf, temp->uf);

		//Remove o sucessor
		medico->right = removeMedical(medico->right, temp->crm);
	}

	//Se a árvore tiver apenas um nó, retorna NULL
	if (medico == NULL)
		return medico;

	// 2. Atualiza a altura do nó
	medico->height = 1 + max(heightMedical(medico->left), heightMedical(medico->right));

	// 3. Verifique o fator de balanceamento e balanceie a árvore
	int balance = getBalanceMedical(medico);

	/*
	 * Se necessário, rotaciona a árvore
	 */

	// Caso 1: Rotação à esquerda
	if (balance > 1 && getBalanceMedical(medico->left) >= 0)
		return rightRotateMedical(medico);

	// Caso 2: Rotação à direita
	if (balance < -1 && getBalanceMedical(medico->right) <= 0)
		return leftRotateMedical(medico);

	// Caso 3: Rotação dupla à esquerda
	if (balance > 1 && getBalanceMedical(medico->left) < 0)
	{
		medico->left = leftRotateMedical(medico->left);
		return rightRotateMedical(medico);
	}

	// Caso 4: Rotação dupla à direita
	if (balance < -1 && getBalanceMedical(medico->right) > 0)
	{
		medico->right = rightRotateMedical(medico->right);
		return leftRotateMedical(medico);
	}

	return medico;
}

// Pesquisa um CRM específico na árvore
Medico *searchIndividualMedical(Medico *medico, int crm)
{
	if (medico == NULL)
		return medico;

	if (crm == medico->crm)
		return medico;
	else if (crm < medico->crm)
		return searchIndividualMedical(medico->left, crm);
	else
		return searchIndividualMedical(medico->right, crm);
}

// Exibe a árvore AVL em ordem
void inOrderMedical(Medico *medico)
{
	if (medico != NULL)
	{
		inOrderMedical(medico->left);
		printf("CRM: %d\n", medico->crm);
		printf("Nome: %s\n", medico->name);
		printf("Especialidade: %s\n", medico->especialidade);
		printf("--------------------------\n");
		inOrderMedical(medico->right);
	}
}

// Principal função de manipulação dos médicos
Medico *medicalManager(Medico *medico)
{
	char name[100];
	char especialidade[30];
	int crm;
	char uf[4];
	char celular[15];
	char email[100];

	//Entra com os dados de cada medico
	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|      Inclusão de Médicos       |\n");
		printf("+--------------------------------+\n");
		printf("Nome do médico [<ENTER> para sair]: ");
		fgets(name, 100, stdin);
		if (strlen(name) == 1)
			break;
		name[strcspn(name, "\n")] = 0;
		printf("Especialidade: ");
		fgets(especialidade, 30, stdin);
		especialidade[strcspn(especialidade, "\n")] = 0;
		printf("CRM: ");
		scanf("%d", &crm);
		getchar();
		printf("UF: ");
		fgets(uf, 4, stdin);
		uf[strcspn(uf, "\n")] = 0;
		printf("Celular: ");
		fgets(celular, 15, stdin);
		celular[strcspn(celular, "\n")] = 0;
		printf("e-mail: ");
		fgets(email, 100, stdin);
		email[strcspn(email, "\n")] = 0;

		medico = insertMedico(medico, crm, name, especialidade, uf, celular, email, 's');

		printf("Médico incluído com sucesso! Tecle <ENTER> para incluir novo médico.");
		while (getchar() != '\n');
	}

	return medico;
}


// Principal função de alteração de médicos
Medico *modifyMedical(Medico *medico)
{
	if (medico == NULL)
	{
		printf("Não há nehum médico cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return medico;
	}


	Medico *aux;
	char nome[100];
	char especialidade[30];
	char celular[15];
	char email[100];
	int crm;

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|    Alterar dados dos médicos   |\n");
		printf("+--------------------------------+\n");
		printf("CRM do médico [0 para sair]: ");
		scanf("%d", &crm);
		getchar();

		if (crm == 0)
			break;

		aux = searchIndividualMedical(medico, crm);

		if (aux == NULL)
		{
			printf("Não há nenhum médico com CRM %d cadastrado!\nTecle <ENTER> para continuar.", crm);
			while(getchar() != '\n');
			continue;
		}

		printf("------------------------------------\n");
		printf("Dados do médico\n\n");
		printf("Nome: %s\n", aux->name);
		printf("Especialidade: %s\n", aux->especialidade);
		printf("UF do CRM: %s\n", aux->uf);
		printf("CRM: %d\n", aux->crm);
		printf("Celular: %s\n", aux->celular);
		printf("E-mail: %s\n", aux->email);
		printf("------------------------------------\n");
		printf("\nDigite apenas o(s) dado(s) que será(ão) modificado(s)!\n\n");
		printf("Entre com os novos dados do médico:\n\n");
		printf("Nome: ");
		fgets(nome, 100, stdin);
		nome[strcspn(nome, "\n")] = 0;
		printf("Especialidade: ");
		fgets(especialidade, 30, stdin);
		especialidade[strcspn(especialidade, "\n")] = 0;
		printf("Celular: ");
		fgets(celular, 15, stdin);
		celular[strcspn(celular, "\n")] = 0;
		printf("e-mail: ");
		fgets(email, 100, stdin);
		email[strcspn(email, "\n")] = 0;

		//Prepara os dados para modificação
		if (strlen(nome) == 0)
			strcpy(nome, aux->name);
		if (strlen(especialidade) == 0)
			strcpy(especialidade, aux->especialidade);
		if (strlen(celular) == 0)
			strcpy(celular, aux->celular);
		if (strlen(email) == 0)
			strcpy(email, aux->email);

		//Altera os dados do médico na árvore
		strcpy(aux->name, nome);
		strcpy(aux->especialidade, especialidade);
		strcpy(aux->celular, celular);
		strcpy(aux->email, email);

		medico = removeMedical(medico, crm);
		medico = insertMedico(medico, crm, nome, especialidade, aux->uf, celular, email, 's');

		printf("Os dados do médico com CRMnº %d foi alterado com sucesso!\nTecle <ENTER> para excluir outro médico.", crm);
		while (getchar() != '\n');
	}

	free(aux);
	return medico;
}

// Principal função de remoção de médicos
Medico *deleteMedical(Medico *medico)
{
	int crm;

	if (medico == NULL)
	{
		printf("Não há nehum médico cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return medico;
	}

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|       Remosão de Médicos       |\n");
		printf("+--------------------------------+\n");
		printf("CRM do médico [0 para sair]: ");
		scanf("%d", &crm);
		getchar();

		if (crm == 0)
			break;

		medico = removeMedical(medico, crm);

		printf("O médico com CRMnº %d foi removido com sucesso!\nTecle <ENTER> para excluir outro médico.", crm);
		while (getchar() != '\n');
	}

	return medico;
}

// Principal função de pesquisa de médicos
void searchMedical(Medico *medico)
{
	int crm;

	if (medico == NULL)
	{
		printf("Não há nehum médico cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return;
	}

	Medico *aux = NULL;

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|      Pesquisa de Médicos       |\n");
		printf("+--------------------------------+\n");
		printf("CRM do médico [0 para sair]: ");
		scanf("%d", &crm);
		getchar();

		if (crm == 0)
			break;

		aux = searchIndividualMedical(medico, crm);

		if (aux == NULL)
			printf("Não há nenhum médico com CRM %d cadastrado!", crm);
		else
		{
			printf("Dados do médico\n\n");
			printf("Nome: %s\n", aux->name);
			printf("Especialidade: %s\n", aux->especialidade);
			printf("UF do CRM: %s\n", aux->uf);
			printf("CRM: %d\n", aux->crm);
			printf("Celular: %s\n", aux->celular);
			printf("E-mail: %s\n", aux->email);
		}

		printf("Tecle <ENTER> para continuar.");
		while(getchar() != '\n');
	}
}

// Principal função de listagem de médicos
void listMedical(Medico *medico)
{
	if (medico == NULL)
	{
		printf("Não há médicos cadastrados! Tecle <ENTER> para continuar");
		while (getchar() != '\n');
		return;
	}

	cabecalho();
	printf("+--------------------------------+\n");
	printf("|      Relação de Médicos        |\n");
	printf("+--------------------------------+\n");

	inOrderMedical(medico);
	printf("\nTecle <ENTER> para retornar.");
	while (getchar() != '\n');
}
