#ifndef SITE_H
#define SITE_H

#include "avl_pchave.h"

// Para usar booleanos
#define TRUE 1
#define FALSE 0
#define boolean int

// Define o limite para código
#define LIMITE_CODIGO 9999

// Define o limite do link
#define LIMITE_LINK 100

// Define o limite para relevância
#define LIMITE_RELEVANCIA 1000

typedef struct site_ SITE;

SITE *site_criar_completo();
SITE *site_criar();
boolean site_apagar(SITE **site);
void site_imprimir(SITE *site);
int site_get_codigo(SITE *site);
AVL_PCHAVE *site_get_palavras_chave(SITE *site);

boolean site_set_codigo(SITE *site, int chave);
boolean site_set_nome(SITE *site, char *nome);
boolean site_set_relevancia(SITE *site, int relevancia);
boolean site_set_link(SITE *site, char *link);
boolean site_set_palavras_chave(SITE *site, AVL_PCHAVE *l);

boolean site_checa_pchave(SITE *site, char *pchave);

int site_get_relevancia(SITE *site);

#endif
