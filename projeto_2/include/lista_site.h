#ifndef LISTA_SITE_H
#define LISTA_SITE_H

#include <stdio.h>

#include "site.h"

// Para usar booleanos
#define TRUE 1
#define FALSE 0
#define boolean int

// Define código de erro
#define ERRO -32000

// Opcional: caso queira que a lista seja ordenada
#define ORDENADA 1

typedef struct lista_site_ LISTA_SITE;

LISTA_SITE *lista_site_criar(void);
LISTA_SITE *lista_site_ler_csv(FILE *inputFile);

boolean lista_site_inserir(LISTA_SITE *lista, SITE *item);
boolean lista_site_remover(LISTA_SITE *lista, int chave);
void lista_site_apagar(LISTA_SITE **lista);

SITE *lista_site_buscar(LISTA_SITE *lista, int chave);

int lista_site_tamanho(LISTA_SITE *lista);
boolean lista_site_vazia(LISTA_SITE *lista);
boolean lista_site_cheia(LISTA_SITE *lista);

void lista_site_imprimir(LISTA_SITE *lista);
void lista_site_inverter(LISTA_SITE **lista);
int lista_site_comparar(LISTA_SITE *l1, LISTA_SITE *l2);

#endif
