#ifndef AVL_SITE_H
#define AVL_SITE_H

#include <stdio.h>
#include <stdlib.h>

#include "avl_pchave.h"
#include "lista_site.h"
#include "site.h"

#define TRUE 1
#define FALSE 0
#define boolean int

#define PRE_ORDER 0
#define EM_ORDER 1
#define POS_ORDER 0

#define max(a, b) ((a > b) ? a : b)

typedef struct avl_site AVL_SITE;

void avl_site_apagar(AVL_SITE **arvore);
AVL_SITE *avl_site_criar(void);
boolean avl_site_inserir(AVL_SITE *arvore, SITE *site);
boolean avl_site_remover(AVL_SITE *arvore, int chave);
SITE *avl_site_busca(AVL_SITE *arvore, int chave);
void avl_site_imprimir(AVL_SITE *T);
AVL_SITE *avl_site_ler_csv(FILE *arquivo);

LISTA_SITE *avl_site_busca_pchave(AVL_SITE *arvore, char *pchave);

#endif