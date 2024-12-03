/*
 ============================================================================
 Name        : main.c
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : A short medical exam manager
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "../headers/exames.h"
#include "../headers/manager.h"
#include "../headers/medico.h"
#include "../headers/paciente.h"
#include "../headers/screen.h"

int main(void)
{
	//Menu inicial do sistema
	char opcao;			//Opção do usuário
	int flag = 1;		//1- verdadeiro, 0 - falso
	FILE *file;			//Ponteiro para a manipulação de arquivos

	// Prepara a árvore de Médicos
	Medico *medicos = NULL;

	file = fopen("../csv/medicos.csv","r");

	if (file == NULL)
	{
		file = fopen("../csv/medicos.csv","w");
		if (file == NULL)
		{
			printf("Sem espaço para criar o arquivo!\n");
			exit(1);
		}
	}
	else
	{
		int crm;
		char name[100] = "";
		char especialidade[30] = "";
		char uf[4] = "";
		char celular[15] = "";
		char email[100] = "";

		while (fscanf(file, "%d;%100[^;];%30[^;];%4[^;];%15[^;];%100[^\n]",
		        &crm, name, especialidade, uf, celular, email) == 6)
		{
		    medicos = insertMedico(medicos, crm, name, especialidade, uf, celular, email, 'n');
		}

	}

	fclose(file);

	//Prepara a árvore de Pacientes
	Paciente *pacientes = NULL;

	file = fopen("../csv/pacientes.csv","r");

	if (file == NULL)
	{
		file = fopen("../csv/pacientes.csv","w");
		if (file == NULL)
		{
			printf("Sem espaço para criar o arquivo!\n");
			exit(1);
		}
	}
	else
	{
		int id;
		char name[100] = "";
		Data *dtNascimento;
		char data[12];
		char celular[15] = "";
		char email[100] = "";

		while (fscanf(file, "%d;%100[^;];%12[^;];%15[^;];%100[^\n]",
		        &id, name, data, celular, email) == 5)
		{
			dtNascimento = setData(data);
		    pacientes = insertPaciente(pacientes, id, name, dtNascimento, celular, email, 'n');
		}
	}

	fclose(file);

	//Prepara a árvore de Exames
	Exame *exames = NULL;

	file = fopen("../csv/exames.csv","r");

	if (file == NULL)
	{
		file = fopen("../csv/exames.csv","w");
		if (file == NULL)
		{
			printf("Sem espaço para criar o arquivo!\n");
			exit(1);
		}
	}
	else
	{
		int id;
		char name[100] = "";
		int idPaciente;
		int crm;
		char data[12];
		float resultado;
		Data *dtRealizacao;
		Paciente *auxPaciente;
		Medico *auxMedico;
//1;hemograma;12;456516;05/03/1987;1423.1234
		while (fscanf(file, "%d;%100[^;];%d;%d;%12[^;];%f",
		        &id, name, &idPaciente, &crm, data, &resultado) == 6)
		{
			dtRealizacao = setData(data);
			auxPaciente = searchIndividualPaciente(pacientes, idPaciente);
			auxMedico = searchIndividualMedical(medicos, crm);
		    exames = insertExame(exames, id, name, auxPaciente, auxMedico, dtRealizacao, resultado,'n');
		}
	}

	fclose(file);

	//Entra no sistema
	while (flag)
	{
		menuPrincipal();
		scanf("%c", &opcao);
		if (opcao == '\n')
			continue;
		getchar();

		switch (opcao)
		{
			case ('1'): //Manipulação dos médicos
				while (flag)
				{
					menuMedicos();
					scanf("%c", &opcao);
					if (opcao == '\n')
						continue;
					getchar();
					switch (opcao)
					{
					case ('0'):
						flag = 0;
						break;
					case ('1'):
						medicos = medicalManager(medicos);
						break;
					case ('2'):
						medicos = modifyMedical(medicos);
						break;
					case ('3'):
						medicos = deleteMedical(medicos);
						break;
					case ('4'):
						searchMedical(medicos);
						break;
					case ('5'):
						listMedical(medicos);
						break;
					default:
						tecleEnter();
						break;
					}
				}
				flag = 1;
				break;
			case ('2'): //Manutenção de Pacientes
				while (flag)
				{
					menuPacientes();
					scanf("%c", &opcao);
					if (opcao == '\n')
						continue;
					getchar();
					switch (opcao)
					{
					case ('0'):
						flag = 0;
						break;
					case ('1'):
						pacientes = pacienteManager(pacientes);
						break;
					case ('2'):
						pacientes = modifyPaciente(pacientes);
						break;
					case ('3'):
						pacientes = deletePaciente(pacientes);
						break;
					case ('4'):
						searchPaciente(pacientes);
						break;
					case('5'):
						listPaciente(pacientes);
						break;
					default:
						tecleEnter();
						break;
					}
				}
				flag = 1;
				break;
			case ('3'):
				while (flag)
				{
					menuExames();
					scanf("%c", &opcao);
					if (opcao == '\n')
						continue;
					getchar();
					switch (opcao)
					{
					case ('0'):
						flag = 0;
						break;
					case ('1'):
						exames = exameManager(exames, pacientes, medicos);
						break;
					case ('2'):
						exames = deleteExame(exames, pacientes, medicos);
						break;
					case ('3'):
						searchExame(exames, pacientes, medicos);
						break;
					case ('4'):
						searchExameNome(exames, pacientes, medicos);
						break;
					case ('5'):
						searchExameData(exames, pacientes, medicos);
						break;
					case ('6'):
						listAllExamPaciente(exames, pacientes, medicos);
						break;
					case ('7'):
						listAllExamMedical(exames, pacientes, medicos);
						break;
					default:
						tecleEnter();
						break;
					}
				}
				flag = 1;
				break;
			case ('0'):	//Encerra o programa normalmente
				return 0;
			default:
				tecleEnter();
		}
	}

	return 0;
}
