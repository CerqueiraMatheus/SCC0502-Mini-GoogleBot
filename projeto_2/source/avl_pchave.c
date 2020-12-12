#include "avl_pchave.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pchave.h"
#include "utils.h"

typedef struct no NO;
struct no {
    PCHAVE *pchave;
    NO *esq;
    NO *dir;
    int altura;
};

struct avl_pchave {
    NO *raiz;
    int profundidade;
    int contador;
};

// Cria uma avl inicializando sua raiz como NULL e sua profundidade como -1
AVL_PCHAVE *avl_pchave_criar() {
    AVL_PCHAVE *arvore = (AVL_PCHAVE *)malloc(sizeof(AVL_PCHAVE));
    if (arvore != NULL) {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
        arvore->contador = 0;
    }
    return arvore;
}

// Apaga os nós da árvore
void avl_apagar_aux(NO **raiz) {
    if (*raiz != NULL) {
        avl_apagar_aux(&((*raiz)->esq));
        avl_apagar_aux(&((*raiz)->dir));
        pchave_apagar(&(*raiz)->pchave);
        free(*raiz);
        *raiz = NULL;
    }
}

// Apaga a árvore
void avl_pchave_apagar(AVL_PCHAVE **arvore) {
    avl_apagar_aux(&(*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

// Calcula a altura de determinado nó
int avl_pchave_altura_no(NO *raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

// Faz uma rotação para a direita
NO *avl_pchave_rodar_direita(NO *a) {
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    a->altura = max(avl_pchave_altura_no(a->esq),
                    avl_pchave_altura_no(a->dir)) +
                1;
    b->altura = max(avl_pchave_altura_no(b->esq),
                    a->altura) +
                1;
    return b;
}

// Faz uma rotação para a esquerda
NO *avl_pchave_rodar_esquerda(NO *a) {
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    a->altura = max(avl_pchave_altura_no(a->esq),
                    avl_pchave_altura_no(a->dir)) +
                1;
    b->altura = max(avl_pchave_altura_no(b->dir),
                    a->altura) +
                1;
    return b;
}

// Faz uma rotação para a esquerda e depois para a direita
NO *avl_pchave_rodar_esquerda_direita(NO *a) {
    a->esq = avl_pchave_rodar_esquerda(a->esq);
    return avl_pchave_rodar_direita(a);
}

// Faz uma rotação para a direita e depois para a esquerda
NO *avl_pchave_rodar_direita_esquerda(NO *a) {
    a->dir = avl_pchave_rodar_direita(a->dir);
    return avl_pchave_rodar_esquerda(a);
}

// Cria um novo nó a partir de um item
NO *avl_pchave_cria_no(PCHAVE *pchave) {
    NO *no = (NO *)malloc(sizeof(NO));
    if (no != NULL) {
        no->altura = 0;
        no->dir = NULL;
        no->esq = NULL;
        no->pchave = pchave;
    }
    return no;
}

// Insere um nó de forma balanceada
NO *avl_pchave_inserir_no(NO *raiz, PCHAVE *pchave) {
    if (raiz == NULL) {
        raiz = avl_pchave_cria_no(pchave);
    }

    else if (!strcmp(pchave_get_string(pchave), pchave_get_string(raiz->pchave)))
        return NULL;

    else if (checa_strings(pchave_get_string(pchave), pchave_get_string(raiz->pchave))) {
        NO *aux = avl_pchave_inserir_no(raiz->dir, pchave);
        if (aux == NULL) return NULL;
        raiz->dir = aux;
    }

    else if (checa_strings(pchave_get_string(raiz->pchave), pchave_get_string(pchave))) {
        NO *aux = avl_pchave_inserir_no(raiz->esq, pchave);
        if (aux == NULL) return NULL;
        raiz->esq = aux;
    }

    raiz->altura = max(avl_pchave_altura_no(raiz->esq), avl_pchave_altura_no(raiz->dir)) + 1;

    if (avl_pchave_altura_no(raiz->esq) - avl_pchave_altura_no(raiz->dir) == -2) {
        if (checa_strings(pchave_get_string(pchave), pchave_get_string(raiz->pchave)))
            raiz = avl_pchave_rodar_esquerda(raiz);
        else
            raiz = avl_pchave_rodar_direita_esquerda(raiz);
    }

    if (avl_pchave_altura_no(raiz->esq) - avl_pchave_altura_no(raiz->dir) == 2) {
        if (checa_strings(pchave_get_string(raiz->pchave), pchave_get_string(pchave)))
            raiz = avl_pchave_rodar_direita(raiz);
        else
            raiz = avl_pchave_rodar_direita_esquerda(raiz);
    }

    return raiz;
}

// Insere um nó na árvore
boolean avl_pchave_inserir(AVL_PCHAVE *arvore, PCHAVE *pchave) {
    if (arvore->contador == LIMITE_PALAVRAS) return FALSE;

    NO *aux = avl_pchave_inserir_no(arvore->raiz, pchave);

    if (aux != NULL) {
        arvore->raiz = aux;
        arvore->contador++;
        return TRUE;
    }

    return FALSE;
}

void avl_pchave_troca_max_esq(NO *troca, NO *raiz, NO *ant) {
    if (troca->dir != NULL) {
        avl_pchave_troca_max_esq(troca->dir, raiz, troca);
        return;
    }
    if (raiz == ant)
        ant->esq = troca->esq;
    else
        ant->dir = troca->esq;

    raiz->pchave = troca->pchave;
    free(troca);
    troca = NULL;
}

NO *avl_pchave_remover_aux(NO **raiz, char *chave) {
    NO *p;
    if (*raiz == NULL)
        return NULL;

    else if (strcmp(chave, pchave_get_string((*raiz)->pchave))) {
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            p = *raiz;
            *raiz = ((*raiz)->esq == NULL) ? ((*raiz)->dir) : ((*raiz)->esq);
            free(p);
            p = NULL;
        } else {
            avl_pchave_troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
        }
    }

    else if (checa_strings(chave, pchave_get_string((*raiz)->pchave))) {
        (*raiz)->esq = avl_pchave_remover_aux(&(*raiz)->esq, chave);
        (*raiz)->altura = max(avl_pchave_altura_no((*raiz)->esq), avl_pchave_altura_no((*raiz)->dir)) + 1;
    }

    else if (checa_strings(pchave_get_string((*raiz)->pchave), chave)) {
        (*raiz)->dir = avl_pchave_remover_aux(&(*raiz)->dir, chave);
        (*raiz)->altura = max(avl_pchave_altura_no((*raiz)->esq), avl_pchave_altura_no((*raiz)->dir)) + 1;
    }

    if (*raiz != NULL) {
        if (avl_pchave_altura_no((*raiz)->esq) - avl_pchave_altura_no((*raiz)->dir) == -2) {
            if (avl_pchave_altura_no((*raiz)->dir->esq) - avl_pchave_altura_no((*raiz)->dir->dir) <= 0) {
                *raiz = avl_pchave_rodar_esquerda(*raiz);
            } else {
                *raiz = avl_pchave_rodar_direita_esquerda(*raiz);
            }
        }

        if (avl_pchave_altura_no((*raiz)->esq) - avl_pchave_altura_no((*raiz)->dir) == 2) {
            if (avl_pchave_altura_no((*raiz)->esq->esq) - avl_pchave_altura_no((*raiz)->esq->dir) >= 0) {
                *raiz = avl_pchave_rodar_direita(*raiz);
            } else {
                *raiz = avl_pchave_rodar_esquerda_direita(*raiz);
            }
        }
    }

    return *raiz;
}

// Remove um nó a partir de sua chave, mas continua deixando a árvore final balanceada
boolean avl_pchave_remover(AVL_PCHAVE *arvore, char *chave) {
    return ((arvore->raiz = avl_pchave_remover_aux(&arvore->raiz, chave)) != NULL);
}

PCHAVE *avl_pchave_busca_no(NO *raiz, char *chave) {
    if (raiz == NULL)
        return NULL;

    // Caso 1: chave na posição atual
    if (!strcmp(chave, pchave_get_string(raiz->pchave)))
        return (raiz->pchave);

    // Caso 2: chave na posição esquerda
    if (checa_strings(pchave_get_string(raiz->pchave), chave))
        return (avl_pchave_busca_no(raiz->esq, chave));

    // Caso 3: chave na posição direita
    return (avl_pchave_busca_no(raiz->dir, chave));
}

// Faz uma busca na árvore através de uma chave e retorna o item procurado
PCHAVE *avl_pchave_busca(AVL_PCHAVE *arvore, char *chave) {
    return (avl_pchave_busca_no(arvore->raiz, chave));
}

// Realiza o percurso pré-ordem recursivamente
void avl_pchave_preordem(NO *raiz) {
    if (raiz != NULL) {
        pchave_imprimir(raiz->pchave);
        avl_pchave_preordem(raiz->esq);
        avl_pchave_preordem(raiz->dir);
    }
}

// Realiza o percurso em-ordem recursivamente
void avl_pchave_emordem(NO *raiz) {
    if (raiz != NULL) {
        avl_pchave_emordem(raiz->esq);
        pchave_imprimir(raiz->pchave);
        avl_pchave_emordem(raiz->dir);
    }
}

// Realiza o percurso pos-ordem recursivamente
void avl_pchave_posordem(NO *raiz) {
    if (raiz != NULL) {
        avl_pchave_posordem(raiz->esq);
        avl_pchave_posordem(raiz->dir);
        pchave_imprimir(raiz->pchave);
    }
}

// Imprime a árvore seguindo o percurso escolhido
void avl_pchave_imprimir(AVL_PCHAVE *arvore) {
    printf("\t");

    if (PRE_ORDER)
        avl_pchave_preordem(arvore->raiz);

    if (EM_ORDER)
        avl_pchave_emordem(arvore->raiz);

    if (POS_ORDER)
        avl_pchave_posordem(arvore->raiz);

    printf("\n");
}

int avl_pchave_tamanho(AVL_PCHAVE *arvore) {
    if (arvore)
        return arvore->contador;
}

boolean avl_pchave_vazia(AVL_PCHAVE *arvore) {
    if (arvore)
        return (arvore->contador == 0);
}

boolean avl_pchave_cheia(AVL_PCHAVE *arvore) {
    if (arvore)
        return (arvore->contador == LIMITE_PALAVRAS);
}