#ifndef LISTA_PCHAVE_H
#define LISTA_PCHAVE_H

#include "pchave.h"

#define LIMITE_PALAVRAS 10

#define TRUE 1
#define FALSE 0
#define boolean int

#define ERRO -32000
#define ORDENADA 1

typedef struct lista_pchave_ LISTA_PCHAVE;

LISTA_PCHAVE *lista_pchave_criar(void);
boolean lista_pchave_inserir(LISTA_PCHAVE *lista, PCHAVE *pchave); 
boolean lista_pchave_remover(LISTA_PCHAVE *lista, char *string);
void lista_pchave_apagar(LISTA_PCHAVE **lista);
PCHAVE *lista_pchave_busca(LISTA_PCHAVE *lista, char *string);

int lista_pchave_tamanho(LISTA_PCHAVE *lista);
boolean lista_pchave_vazia(LISTA_PCHAVE *lista);
boolean lista_pchave_cheia(LISTA_PCHAVE *lista);
void lista_pchave_imprimir(LISTA_PCHAVE *lista);

#endif