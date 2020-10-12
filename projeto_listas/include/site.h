#ifndef SITE_H
	#define SITE_H

	#define TRUE 1
	#define FALSE 0
	#define boolean int
	#include "lista_pchave.h"


	typedef struct site_ SITE;

	SITE *site_criar_completo();
	SITE *site_criar();
	boolean site_apagar(SITE **site);
	void site_imprimir(SITE *site);
	int site_get_codigo(SITE *site);
	LISTA_PCHAVE *site_get_palavras_chave(SITE *site);
	boolean site_set_codigo(SITE *site, int chave);
	boolean site_set_nome(SITE *site, char *nome);
	boolean site_set_relevancia(SITE *site, int relevancia);
	boolean site_set_link(SITE *site, char *link);
	boolean site_set_palavras_chave(SITE *site, LISTA_PCHAVE *l);

#endif
