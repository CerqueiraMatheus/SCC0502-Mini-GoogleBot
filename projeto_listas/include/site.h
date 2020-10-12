#ifndef SITE_H
	#define SITE_H

	#define TRUE 1
	#define FALSE 0
	#define boolean int
	#include "lista_pchave.h"


	typedef struct site_ SITE;

	//funções de manipulação do TAD, começar com o nome do TAD
	SITE *site_criar();
	//passar a variável por referência 
	//pois está alterando os dados em si
	boolean site_apagar(SITE **site);
	//necessário por causa do information hiding
	//tenho que passar o ponteiro por causa do information hiding
	void site_imprimir(SITE *site);
	//retornar o conteúdo do site
	//(get para recuperar e set para alterar)
	int site_get_codigo(SITE *site);
	boolean site_set_codigo(SITE *site, int chave);
	boolean site_set_nome(SITE *site, char *nome);
	boolean site_set_relevancia(SITE *site, int relevancia);
	boolean site_set_link(SITE *site, char *link);
	boolean site_set_palavras_chave(SITE *site, char *auxname);

#endif
