#ifndef AVL_PCHAVE_H
#define AVL_PCHAVE_H

#include "pchave.h"
#include "utils.h"

// Limite de palavras-chave
#define LIMITE_PALAVRAS 10

// Para usar booleanos
#define TRUE 1
#define FALSE 0
#define boolean int

#define PRE_ORDER 0
#define EM_ORDER 1
#define POS_ORDER 0

#define max(a, b) ((a > b) ? a : b)

// TAD da lista de p_chave
typedef struct avl_pchave AVL_PCHAVE;

AVL_PCHAVE *avl_pchave_criar(void);
boolean avl_pchave_inserir(AVL_PCHAVE *arvore, PCHAVE *pchave);
boolean avl_pchave_remover(AVL_PCHAVE *arvore, char *string);
void avl_pchave_apagar(AVL_PCHAVE **arvore);
PCHAVE *avl_pchave_busca(AVL_PCHAVE *arvore, char *string);

int avl_pchave_tamanho(AVL_PCHAVE *arvore);
boolean avl_pchave_vazia(AVL_PCHAVE *arvore);
boolean avl_pchave_cheia(AVL_PCHAVE *arvore);
void avl_pchave_imprimir(AVL_PCHAVE *arvore);

#endif