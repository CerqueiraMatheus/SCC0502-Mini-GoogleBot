#ifndef SITE_H
#include <stdio.h>

#include "utils.h"

#define SITE_H

#define TRUE 1
#define FALSE 0

typedef struct site_ SITE;

SITE *inserir_site(int codigo, char *nome, int relevancia, char *link, char **palavra_chave);

int remover_site(SITE **site);

void inserir_palavra_chave(SITE **site, char *nova_palavra);

void atualizar_relevancia(SITE **site, int nova_relevancia);

SITE **readFile(FILE *inputFile);

#endif