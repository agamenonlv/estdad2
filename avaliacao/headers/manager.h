/*
 ============================================================================
 Name        : exam.h
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Header
 ============================================================================
 */

#ifndef HEADERS_MANAGER_H_
#define HEADERS_MANAGER_H_

	// Tipos abstrados de dados para o sistema
	typedef struct Data
	{
		int dia;					// Dia do mês
		int mes;					// Mês do ano
		int ano;					// Ano
	} Data;

	/*
	 * Protótipos das funções
	*/
	// Obtém o valor máximo entre dois inteiros
	int max(int a, int b);
	// Cria uma data
	Data *setData(char data[]);
	// Cria uma data
	Data *setDataInt(int dia, int mes, int ano);
	// Exibe uma data
	void printData(Data *data);
	// Retorna uma string data
	char *getData(Data *data);

#endif /* HEADERS_MANAGER_H_ */
