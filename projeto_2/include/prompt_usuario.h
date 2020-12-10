#ifndef PROMPT_H
#define PROMPT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "utils.h"

SITE *site_criar_completo();
void imprime_menu();
void inserir_site(AVL *lista_sites);
void remover_site(AVL *lista_sites);
void inserir_palavra_chave(AVL *lista_sites);
void atualizar_relevancia(AVL *lista_sites);

#endif