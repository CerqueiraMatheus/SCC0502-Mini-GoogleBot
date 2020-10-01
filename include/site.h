#ifndef SITE_H
#include <stdio.h>

#define SITE_H

// Para operações booleanas
#define boolean int
#define TRUE 1
#define FALSE 0

// Para ler linhas
#define INPUT_BUFFER 2048

// Definições de limite previstas pelo exercício
#define LIMITE_PALAVRAS 10
#define LIMITE_STRING 50

typedef struct site_ SITE;

SITE *site_inserir(int codigo, char *nome, int relevancia, char *link, char **palavras_chave);

int site_remover(SITE **site);

void site_inserir_pchave(SITE **site, char *nova_palavra);

// Atualiza a relevância de um site
void site_set_relevancia(SITE *site, int nova_relevancia);

// Lê uma lista de sites a partir de um csv
SITE **site_ler_csv(FILE *inputFile);

#endif