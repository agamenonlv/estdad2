/*
 ============================================================================
 Name        : exam.c
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Functions to use in project
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/manager.h"

// Obtém o valor máximo entre dois inteiros
int max(int a, int b)
{
	return (a > b)? a : b;
}

// Cia uma data
Data *setData(char data[])
{
	Data *retorno;
	int dia;
	int mes;
	int ano;

	retorno = (Data*)malloc(sizeof(Data));

	sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

	retorno->dia = dia;
	retorno->mes = mes;
	retorno->ano = ano;

	return retorno;
}

// Cria uma data
Data *setDataInt(int dia, int mes, int ano)
{
	Data *retorno;

	retorno = (Data*)malloc(sizeof(Data));

	retorno->dia = dia;
	retorno->mes = mes;
	retorno->ano = ano;

	return retorno;
}

// Exibe uma data
void printData(Data *data)
{
	printf("%02d/%02d/%04d\n", data->dia, data->mes, data->ano);
}


// Retorna uma string data
char *getData(Data *data)
{
	char *retorno = (char*)malloc(12*sizeof(char));

	sprintf(retorno, "%02d/%02d/%04d", data->dia, data->mes, data->ano);

	return retorno;
}
