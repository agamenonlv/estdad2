/*
 ============================================================================
 Name        : screen.h
 Author      : Agamenon L. do Vale
 Version     : 1.0
 Copyright   : GNU
 Description : Header para manipulação de monitor
 ============================================================================
 */

#ifndef HEADERS_SCREEN_H_
#define HEADERS_SCREEN_H_

	/*
	 * Protótipos das funções
	*/

	//Limpa a tela do console
	void clearScreen();
	//Cabeçalho dos menus
	void cabecalho();
	//Espera o <ENTER> se pressionado
	void tecleEnter();
	//Exibe o menu principal
	void menuPrincipal();
	// Exibe o menu para médicos
	void menuMedicos();
	// Exibe o menu para pacientes
	void menuPacientes();
	// Exibe o menu para exames
	void menuExames();

#endif /* HEADERS_SCREEN_H_ */
