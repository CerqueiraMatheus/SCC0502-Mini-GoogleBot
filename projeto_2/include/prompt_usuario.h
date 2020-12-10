#ifndef PROMPT_H
#define PROMPT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "lista_site.h"
#include "utils.h"

SITE *site_criar_completo();
void imprime_menu();
void inserir_site(LISTA_SITE *lista_sites);
void remover_site(LISTA_SITE *lista_sites);
void inserir_palavra_chave(LISTA_SITE *lista_sites);
void atualizar_relevancia(LISTA_SITE *lista_sites);

#endif