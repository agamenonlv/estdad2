/*
 ============================================================================
 Name        : Paciente.c
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Funções para a manutenção de pacientes
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/paciente.h"
#include "../headers/screen.h"

// Procura o maior ID
int searchMaxId(Paciente *paciente)
{
	if (paciente == NULL)
		return 0;

	if (paciente->right == NULL)
		return paciente->id;

	return searchMaxId(paciente->right);
}

// Obtém a altura de um nó
int heightPaciente(Paciente *paciente)
{
	if (paciente == NULL)
		return -1;

	return paciente->height;
}

// Remove um registro do arquivo de médicos
void removeFilePaciente(int id)
{
	FILE *original;

	original = fopen("../csv/pacientes.csv", "r");
	if (original == NULL)
	{
		printf("Erro ao abrir o arquivo de pacientes!\nTecle <ENTER> para continuar.");
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
	if (remove("../csv/pacientes.csv") != 0)
	{
		printf("Erro ao remover o arquivo 'pacientes.csv'\nTecle <ENTER> para continuar");
		while(getchar() != '\n');
		exit(1);
	}

	//Renomeia o arquivo temporário
	if (rename("../csv/temp.csv","../csv/pacientes.csv") != 0)
	{
		printf("Erro ao renomear o arquivo temporário 'temp.csv' para 'pacientes.csv'\nTecle <ENTER> para continuar");
		while(getchar() != '\n');
		exit(1);
	}
}

//Rotação à direita
Paciente *rightRotatePaciente(Paciente *paciente)
{
	Paciente *node = paciente->left;
	Paciente *aux = node->right;

	node->right = paciente;
	paciente->left = aux;

	paciente->height = max(heightPaciente(paciente->left), heightPaciente(paciente->right)) + 1;
	node->height = max(heightPaciente(node->left), heightPaciente(node->right)) + 1;

	return node;
}

//Rotação à esquerda
Paciente *leftRotatePaciente(Paciente *paciente)
{
	Paciente *node = paciente->right;
	Paciente *aux = node->left;

	node->left = paciente;
	paciente->right = aux;

	paciente->height = max(heightPaciente(paciente->left), heightPaciente(paciente->right)) + 1;
	node->height = max(heightPaciente(node->left), heightPaciente(node->right)) + 1;

	return node;
}

// Obtém o fator de balanceamento do nó
int getBalancePaciente(Paciente *paciente)
{
	if (paciente == NULL)
		return 0;

	return heightPaciente(paciente->left) - heightPaciente(paciente->right);
}

// Função que cria um novo nó
Paciente *newPacienteNode(int id, char name[], Data *dtNascimento, char celular[], char email[], char novo)
{
	Paciente *newNode = (Paciente*)malloc(sizeof(Paciente));

	// Insere os dados dados na árvore
	newNode->id = id;
	strcpy(newNode->name, name);
	newNode->dtNascimento = dtNascimento;
	strcpy(newNode->celular, celular);
	strcpy(newNode->email, email);

	//Insere os dados no arquivo
	if (novo == 's')
	{
		FILE *file;

		file = fopen("../csv/pacientes.csv", "a");
		fprintf(file, "%d;%s;%s;%s;%s\n", id, name, getData(dtNascimento), celular, email);
		fclose(file);
	}

	return newNode;
}

//Função que insere um médico na árvore
Paciente *insertPaciente(Paciente *paciente, int id, char name[], Data *dtNascimento, char celular[], char email[], char novo)
{
	if (paciente == NULL)
		return newPacienteNode(id, name, dtNascimento, celular, email, novo);

	// Comparação com o CRM do nó para decidir a posição na árvore
	if (id < paciente->id)
		paciente->left = insertPaciente(paciente->left, id, name, dtNascimento, celular, email, novo);
	else if (id > paciente->id)
		paciente->right = insertPaciente(paciente->right, id, name, dtNascimento, celular, email, novo);
	else // CRMs ducplicados não são permitidos na árvore
		return paciente;

	//Atualiza a altura do nó ancestral
	paciente->height = 1 + max(heightPaciente(paciente->left), heightPaciente(paciente->right));

	//Obtém o balanço do nó
	int balance = getBalancePaciente(paciente);

	/*
	 * Casos de rotação para balanceamento
	*/

	// Caso Esquerda->Esquerda
	if (balance > 1 && id < paciente->left->id)
		return rightRotatePaciente(paciente);

	// Caso Direita->Direita
	if (balance < -1 && id > paciente->right->id)
		return leftRotatePaciente(paciente);

	// Caso Esquerda->Direita
	if (balance > 1 && id > paciente->left->id)
	{
		paciente->left = leftRotatePaciente(paciente->left);
		return rightRotatePaciente(paciente);
	}

	// Caso Direita->Esquerda
	if (balance < -1 && id < paciente->right->id)
	{
		paciente->right = rightRotatePaciente(paciente->right);
		return leftRotatePaciente(paciente);
	}

	return paciente;
}

// Encontra o menor nó (usado na remoção)
Paciente *minNodePaciente(Paciente *paciente)
{
	Paciente *current = paciente;

	while (current && current->left != NULL)
		current = current->left;
	return current;
}

// Remove um médico da árvore
Paciente *removePaciente(Paciente *paciente, int id)
{
	if (paciente == NULL)
		return paciente;

	// 1. Encontrar o nó a ser removido
	if (id < paciente->id)
		paciente->left = removePaciente(paciente->left, id);
	else if (id > paciente->id)
		paciente->right = removePaciente(paciente->right, id);
	else
	{
		// Caso 1: nós com um único filho ou nenhum filho
		if (paciente->left == NULL)
		{
			Paciente *temp = paciente->right;
			removeFilePaciente(paciente->id);
			free(paciente);
			return temp;
		}
		else if (paciente->right == NULL)
		{
			Paciente *temp = paciente->left;
			removeFilePaciente(paciente->id);
			free(paciente);
			return temp;
		}

		// Caso 2: nó com dois filhos
		// Encontre o menor nó da subárvore direita (sucessor em ordem)
		Paciente *temp = minNodePaciente(paciente->right);

		//Copia o valor do sucessor para este nó
		paciente->id = temp->id;
		strcpy(paciente->name, temp->name);
		strcpy(paciente->celular, temp->celular);
		strcpy(paciente->email, temp->email);

		//Remove o sucessor
		paciente->right = removePaciente(paciente->right, temp->id);
	}

	//Se a árvore tiver apenas um nó, retorna NULL
	if (paciente == NULL)
		return paciente;

	// 2. Atualiza a altura do nó
	paciente->height = 1 + max(heightPaciente(paciente->left), heightPaciente(paciente->right));

	// 3. Verifique o fator de balanceamento e balanceie a árvore
	int balance = getBalancePaciente(paciente);

	/*
	 * Se necessário, rotaciona a árvore
	 */

	// Caso 1: Rotação à esquerda
	if (balance > 1 && getBalancePaciente(paciente->left) >= 0)
		return rightRotatePaciente(paciente);

	// Caso 2: Rotação à direita
	if (balance < -1 && getBalancePaciente(paciente->right) <= 0)
		return leftRotatePaciente(paciente);

	// Caso 3: Rotação dupla à esquerda
	if (balance > 1 && getBalancePaciente(paciente->left) < 0)
	{
		paciente->left = leftRotatePaciente(paciente->left);
		return rightRotatePaciente(paciente);
	}

	// Caso 4: Rotação dupla à direita
	if (balance < -1 && getBalancePaciente(paciente->right) > 0)
	{
		paciente->right = rightRotatePaciente(paciente->right);
		return leftRotatePaciente(paciente);
	}

	return paciente;
}

// Pesquisa um ID específico na árvore
Paciente *searchIndividualPaciente(Paciente *paciente, int id)
{
	if (paciente == NULL)
		return paciente;

	if (id == paciente->id)
		return paciente;
	else if (id < paciente->id)
		return searchIndividualPaciente(paciente->left, id);
	else
		return searchIndividualPaciente(paciente->right, id);
}

// Pesquisa o ID de um paciente pelo seu nome
int searchPacienteNome(Paciente *paciente, char nomePaciente[])
{
	if (paciente == NULL)
		return -1;

	if (strcmp(paciente->name, nomePaciente) == 0)
	{
		return paciente->id;
	}

	int retorno = searchPacienteNome(paciente->left, nomePaciente);

	if (retorno != -1)
		return retorno;

	return searchPacienteNome(paciente->right, nomePaciente);
}

// Exibe a árvore AVL em ordem
void inOrderPaciente(Paciente *paciente)
{
	if (paciente != NULL)
	{
		inOrderPaciente(paciente->left);
		printf("ID: %d\n", paciente->id);
		printf("Nome: %s\n", paciente->name);
		printf("Data de nascimento: %s\n", getData(paciente->dtNascimento));
		printf("Celular: %s\n", paciente->celular);
		printf("E-maiil: %s\n", paciente->email);
		printf("--------------------------\n");
		inOrderPaciente(paciente->right);
	}
}

// Principal função de manipulação dos médicos
Paciente *pacienteManager(Paciente *paciente)
{
	char name[100];
	int id;
	Data *dtNascimento;
	int dia;
	int mes;
	int ano;
	char celular[15];
	char email[100];

	//Entra com os dados de cada Paciente
	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|     Inclusão de Pacientes      |\n");
		printf("+--------------------------------+\n");
		printf("Nome do paciente [<ENTER> para sair]: ");
		fgets(name, 100, stdin);
		if (strlen(name) == 1)
			break;
		name[strcspn(name, "\n")] = 0;
		printf("Data de nascimento:\n");
		printf("Dia: ");
		scanf("%d", &dia);
		getchar();
		printf("Mês: ");
		scanf("%d", &mes);
		getchar();
		printf("Ano: ");
		scanf("%d", &ano);
		getchar();
		printf("Celular: ");
		fgets(celular, 15, stdin);
		celular[strcspn(celular, "\n")] = 0;
		printf("e-mail: ");
		fgets(email, 100, stdin);
		email[strcspn(email, "\n")] = 0;

		dtNascimento = setDataInt(dia, mes, ano);

		id = 1 + searchMaxId(paciente);

		paciente = insertPaciente(paciente, id, name, dtNascimento, celular, email, 's');

		printf("Paciente incluído com sucesso! Tecle <ENTER> para incluir novo médico.");
		while (getchar() != '\n');
	}

	return paciente;
}

// Principal função de alteração de médicos
Paciente *modifyPaciente(Paciente *paciente)
{
	if (paciente == NULL)
	{
		printf("Não há nehum paciente cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return paciente;
	}


	Paciente *aux;
	char nome[100];
	Data *dtNascimento;
	char celular[15];
	char email[100];
	int id;
	int dia;
	int mes;
	int ano;

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|   Alterar dados dos pacientes  |\n");
		printf("+--------------------------------+\n");
		printf("ID do paciente [0 para sair]: ");
		scanf("%d", &id);
		getchar();

		if (id == 0)
			break;

		aux = searchIndividualPaciente(paciente, id);

		if (aux == NULL)
		{
			printf("Não há nenhum paciente com CRM %d cadastrado!\nTecle <ENTER> para continuar.", id);
			while(getchar() != '\n');
			continue;
		}

		printf("------------------------------------\n");
		printf("Dados do paciente\n\n");
		printf("Nome: %s\n", aux->name);
		printf("Data de nascimento: %s\n", getData(aux->dtNascimento));
		printf("Celular: %s\n", aux->celular);
		printf("E-mail: %s\n", aux->email);
		printf("------------------------------------\n");
		printf("\nDigite apenas o(s) dado(s) que será(ão) modificado(s)!\n\n");
		printf("Entre com os novos dados do paciente:\n\n");
		printf("Nome: ");
		fgets(nome, 100, stdin);
		nome[strcspn(nome, "\n")] = 0;
		printf("Data de nascimento: \n");
		printf("Dia: ");
		scanf("%d", &dia);
		getchar();
		printf("Mês: ");
		scanf("%d", &mes);
		getchar();
		printf("Ano: ");
		scanf("%d", &ano);
		getchar();
		printf("Celular: ");
		fgets(celular, 15, stdin);
		celular[strcspn(celular, "\n")] = 0;
		printf("e-mail: ");
		fgets(email, 100, stdin);
		email[strcspn(email, "\n")] = 0;

		//Prepara os dados para modificação
		if (strlen(nome) == 0)
			strcpy(nome, aux->name);
		if (strlen(celular) == 0)
			strcpy(celular, aux->celular);
		if (strlen(email) == 0)
			strcpy(email, aux->email);
		if (dia == 0)
			dtNascimento = aux->dtNascimento;
		else
		{
			dtNascimento = setDataInt(dia, mes, ano);
		}

		paciente = removePaciente(paciente, id);
		paciente = insertPaciente(paciente, id, nome, dtNascimento, celular, email, 's');

		printf("Os dados do paciente com ID nº %d foi alterado com sucesso!\nTecle <ENTER> para excluir outro paciente.", id);
		while (getchar() != '\n');
	}

	free(aux);
	return paciente;
}

// Principal função de remoção de médicos
Paciente *deletePaciente(Paciente *paciente)
{
	int id;

	if (paciente == NULL)
	{
		printf("Não há nehum paciente cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return paciente;
	}

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|      Remosão de Pacientes      |\n");
		printf("+--------------------------------+\n");
		printf("ID do paciente [0 para sair]: ");
		scanf("%d", &id);
		getchar();

		if (id == 0)
			break;

		paciente = removePaciente(paciente, id);

		printf("O paciente com ID nº %d foi removido com sucesso!\nTecle <ENTER> para excluir outro paciente.", id);
		while (getchar() != '\n');
	}

	return paciente;
}

// Principal função de pesquisa de médicos
void searchPaciente(Paciente *paciente)
{
	int id;

	if (paciente == NULL)
	{
		printf("Não há nehum pacientes cadastrado! Tecle <ENTER> para retornar.");
		while (getchar() != '\n');
		return;
	}

	Paciente *aux = NULL;

	while (1)
	{
		cabecalho();
		printf("+--------------------------------+\n");
		printf("|     Pesquisa de Pacientes      |\n");
		printf("+--------------------------------+\n");
		printf("ID do paciente [0 para sair]: ");
		scanf("%d", &id);
		getchar();

		if (id == 0)
			break;

		aux = searchIndividualPaciente(paciente, id);

		if (aux == NULL)
			printf("Não há nenhum paciente com ID %d cadastrado!", id);
		else
		{
			printf("Dados do paciente\n\n");
			printf("Nome: %s\n", aux->name);
			printf("Celular: %s\n", aux->celular);
			printf("E-mail: %s\n", aux->email);
		}

		printf("Tecle <ENTER> para continuar.");
		while(getchar() != '\n');
	}
}

// Principal função de listagem de médicos
void listPaciente(Paciente *paciente)
{
	if (paciente == NULL)
	{
		printf("Não há pacientes cadastrados! Tecle <ENTER> para continuar");
		while (getchar() != '\n');
		return;
	}

	cabecalho();
	printf("+--------------------------------+\n");
	printf("|     Relação de Pacientes       |\n");
	printf("+--------------------------------+\n");

	inOrderPaciente(paciente);
	printf("\nTecle <ENTER> para retornar.");
	while (getchar() != '\n');
}
