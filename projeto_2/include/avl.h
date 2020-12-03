#ifndef AVL_H
	#define AVL_H
	
	#include <stdio.h>
	#include <stdlib.h>
	#include "site.h"
	#include "lista_pchave.h"

	#define TRUE 1
	#define FALSE 0
	#define boolean int
	#define PRE_ORDER 1
	#define EM_ORDER 0
	#define POS_ORDER 0

	#define max(a, b) ((a > b) ? a : b)


	typedef struct avl AVL;

	void avl_apagar(AVL **arvore);
	AVL *avl_criar(void);
	boolean avl_inserir(AVL *arvore, SITE *site);
	boolean avl_remover(AVL *T, int chave);
	SITE *avl_busca(AVL *T, int chave);
	void avl_imprimir_arvore(AVL *T);
	AVL *avl_site_ler_csv(FILE *arquivo);

#endif 