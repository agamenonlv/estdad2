/*
 ============================================================================
 Name        : screen.c
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Functions to manipulate monitor
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "../headers/screen.h"

//Limpa a tela do console
void clearScreen()
{
	printf("\033[H\033[2J");
}

//Cabeçalho dos menus
void cabecalho()
{
	clearScreen();
	printf("+--------------------------------+\n");
	printf("| GESTÃO DE RESULTADOS DE EXAMES |\n");
	printf("+--------------------------------+\n");
}

//Espera o <ENTER> se pressionado
void tecleEnter()
{
	printf("\nAtenção! Opção inválida! Tecle <ENTER> para tentar novamente!.");
	while (getchar() != '\n');
}

//Exibe o menu principal
void menuPrincipal()
{
	cabecalho();
	printf("1 - Médicos\n");
	printf("2 - Pacientes\n");
	printf("3 - Exames\n");
	printf("0 - Encerrar\n");
	printf("? ");
}

// Exibe o menu para médicos
void menuMedicos()
{
	cabecalho();
	printf("+--------------------------------+\n");
	printf("|     Manutenção de Médicos      |\n");
	printf("+--------------------------------+\n");
	printf("1 - Incluir novo médico\n");
	printf("2 - Alterar dados de um médico\n");
	printf("3 - Excluir um médico\n");
	printf("4 - Pesquisar por um médico\n");
	printf("5 - Listar todos os médicos\n");
	printf("0 - Retornar ao menu principal\n");
	printf("? ");
}

// Exibe o menu para pacientes
void menuPacientes()
{
	cabecalho();
	printf("+--------------------------------+\n");
	printf("|     Manutenção de Pacientes    |\n");
	printf("+--------------------------------+\n");
	printf("1 - Incluir novo paciente\n");
	printf("2 - Alterar dados de um paciente\n");
	printf("3 - Excluir um paciente\n");
	printf("4 - Pesquisar por um paciente\n");
	printf("5 - Listar todos os pacientes\n");
	printf("0 - Retornar ao menu principal\n");
	printf("? ");
}

// Exibe o menu para exames
void menuExames()
{
	cabecalho();
	printf("+--------------------------------+\n");
	printf("|      Manutenção de Exames      |\n");
	printf("+--------------------------------+\n");
	printf("1 - Incluir novo exame\n");
	printf("2 - Excluir um exame\n");
	printf("3 - Pesquisar por um exame específico\n");
	printf("4 - Pesquisar exames por nome\n");
	printf("5 - Pesquisar exames por data\n");
	printf("6 - Listar todos os exames de um paciente\n");
	printf("7 - Listar todos os exames solicitados por um médico\n");
	printf("0 - Retornar ao menu principal\n");
	printf("? ");
}
