#ifndef GOOGLEBOT_H
	#define GOOGLEBOT_H

	#define TRUE 1
	#define FALSE 0

	typedef struct googlebot_ GOOGLEBOT;


	GOOGLEBOT *inserir_site(int codigo, char *nome, int relevancia, char *link, char **palavra_chave);

	int remover_site(GOOGLEBOT **site);

	void inserir_palavra_chave(GOOGLEBOT **site, char *nova_palavra);

	void atualizar_relevancia(GOOGLEBOT **site, int nova_relevancia);

	
#endif