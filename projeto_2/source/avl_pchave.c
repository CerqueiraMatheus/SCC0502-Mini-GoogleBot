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
// Retorna uma AVL_PCHAVE
AVL_PCHAVE *avl_pchave_criar() {
    AVL_PCHAVE *arvore = (AVL_PCHAVE *)malloc(sizeof(AVL_PCHAVE));
    if (arvore != NULL) {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
        arvore->contador = 0;
    }
    return arvore;
}

// Apaga os nós da árvore recursivamente
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
// Retorna um int
int avl_pchave_altura_no(NO *raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

// Faz uma rotação para a direita
// Retorna um NO para a raiz
NO *avl_pchave_rodar_direita(NO *raiz) {
    NO *b = raiz->esq;
    raiz->esq = b->dir;
    b->dir = raiz;
    raiz->altura = max(avl_pchave_altura_no(raiz->esq),
                    avl_pchave_altura_no(raiz->dir)) +
                1;
    b->altura = max(avl_pchave_altura_no(b->esq),
                    raiz->altura) +
                1;
    return b;
}

// Faz uma rotação para a esquerda
// Retorna um NO para a raiz
NO *avl_pchave_rodar_esquerda(NO *raiz) {
    NO *b = raiz->dir;
    raiz->dir = b->esq;
    b->esq = raiz;
    raiz->altura = max(avl_pchave_altura_no(raiz->esq),
                    avl_pchave_altura_no(raiz->dir)) +
                1;
    b->altura = max(avl_pchave_altura_no(b->dir),
                    raiz->altura) +
                1;
    return b;
}

// Faz uma rotação para a esquerda e depois para a direita
// Retorna um NO para a raiz
NO *avl_pchave_rodar_esquerda_direita(NO *raiz) {
    raiz->esq = avl_pchave_rodar_esquerda(raiz->esq);
    return avl_pchave_rodar_direita(raiz);
}

// Faz uma rotação para a direita e depois para a esquerda
// Retorna um NO para a raiz
NO *avl_pchave_rodar_direita_esquerda(NO *raiz) {
    raiz->dir = avl_pchave_rodar_direita(raiz->dir);
    return avl_pchave_rodar_esquerda(raiz);
}

// Cria um novo nó a partir de um item
// Retorna um NO
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
// Retorna um NO para a raiz
NO *avl_pchave_inserir_no(NO *raiz, PCHAVE *pchave, boolean *inserido) {
    if (raiz == NULL) {
        raiz = avl_pchave_cria_no(pchave);
        *inserido = TRUE;
    }

    else if (!strcmp(pchave_get_string(pchave), pchave_get_string(raiz->pchave)))
        return NULL;

    else if (checa_strings(pchave_get_string(pchave), pchave_get_string(raiz->pchave))) {
        NO *aux = avl_pchave_inserir_no(raiz->dir, pchave, inserido);
        if (aux == NULL) return NULL;
        raiz->dir = aux;
    }

    else if (checa_strings(pchave_get_string(raiz->pchave), pchave_get_string(pchave))) {
        NO *aux = avl_pchave_inserir_no(raiz->esq, pchave, inserido);
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
// Retorna um boolean
boolean avl_pchave_inserir(AVL_PCHAVE *arvore, PCHAVE *pchave) {
    if (arvore->contador == LIMITE_PALAVRAS) return FALSE;

    boolean inserido = FALSE;
    NO *aux = avl_pchave_inserir_no(arvore->raiz, pchave, &inserido);

    if (inserido) {
        arvore->raiz = aux;
        arvore->contador++;
        return TRUE;
    }

    return FALSE;
}

// Realiza a troca a esquerda
void avl_pchave_troca_max_esq(NO *troca, NO *raiz, NO *ant) {
    if (troca->dir != NULL) {
        avl_pchave_troca_max_esq(troca->dir, raiz, troca);
        return;
    }
    if (raiz == ant)
        ant->esq = troca->esq;
    else
        ant->dir = troca->esq;

    pchave_apagar(&raiz->pchave);
    raiz->pchave = troca->pchave;
    free(troca);
    troca = NULL;
}

// Remove um nó a partir de uma chave e um endereço para a raiz
// Retorna um NO para a raiz
NO *avl_pchave_remover_aux(NO **raiz, char *chave, boolean *auxiliar) {
    NO *p;
    if (*raiz == NULL) {
        return NULL;
    }

    else if (strcmp(chave, pchave_get_string((*raiz)->pchave)) == 0) {
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            p = *raiz;
            *raiz = ((*raiz)->esq == NULL) ? ((*raiz)->dir) : ((*raiz)->esq);
            pchave_apagar(&p->pchave);
            free(p);
            p = NULL;
        } else {
            avl_pchave_troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
        }
        *auxiliar = TRUE;
    }

    else if (checa_strings(chave, pchave_get_string((*raiz)->pchave))) {
        (*raiz)->esq = avl_pchave_remover_aux(&(*raiz)->esq, chave, auxiliar);
        (*raiz)->altura = max(avl_pchave_altura_no((*raiz)->esq), avl_pchave_altura_no((*raiz)->dir)) + 1;
    }

    else if (checa_strings(pchave_get_string((*raiz)->pchave), chave)) {
        (*raiz)->dir = avl_pchave_remover_aux(&(*raiz)->dir, chave, auxiliar);
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
// Retorna um boolean
boolean avl_pchave_remover(AVL_PCHAVE *arvore, char *string) {
    boolean removido = FALSE;

    arvore->raiz = avl_pchave_remover_aux(&arvore->raiz, string, &removido);
    if (removido)
        return TRUE;

    return FALSE;
}

// Busca por um nó na AVL
// Retorna uma PCHAVE
PCHAVE *avl_pchave_busca_no(NO *raiz, char *string) {
    if (raiz == NULL)
        return NULL;

    // Caso 1: chave na posição atual
    if (!strcmp(string, pchave_get_string(raiz->pchave)))
        return (raiz->pchave);

    // Caso 2: chave na posição esquerda
    if (checa_strings(pchave_get_string(raiz->pchave), string))
        return (avl_pchave_busca_no(raiz->esq, string));

    // Caso 3: chave na posição direita
    return (avl_pchave_busca_no(raiz->dir, string));
}

// Faz uma busca na árvore através de uma chave e retorna o item procurado
// Retorna uma PCHAVE
PCHAVE *avl_pchave_buscar(AVL_PCHAVE *arvore, char *string) {
    return (avl_pchave_busca_no(arvore->raiz, string));
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

// Verifica o tamanho da AVL
// Retorna um int
int avl_pchave_tamanho(AVL_PCHAVE *arvore) {
    if (arvore)
        return arvore->contador;
}

// Verifica se uma AVL está vazia
// Retorna um boolean
boolean avl_pchave_vazia(AVL_PCHAVE *arvore) {
    if (arvore)
        return (arvore->contador == 0);
}

// Verifica se uma AVL está cheia
// Retorna um boolean
boolean avl_pchave_cheia(AVL_PCHAVE *arvore) {
    if (arvore)
        return (arvore->contador == LIMITE_PALAVRAS);
}

// Adiciona recursivamente as PCHAVES de uma AVL noutra AVL
void avl_pchave_adicionar_pchaves_rec(NO *raiz, AVL_PCHAVE *avl_fonte, AVL_PCHAVE *avl_destino) {
    if (raiz != NULL) {
        // Continua a esquerda
        avl_pchave_adicionar_pchaves_rec(raiz->esq, avl_fonte, avl_destino);

        // Insere se não existir
        char *aux = malloc(strlen(pchave_get_string(raiz->pchave)) + 1);
        strcpy(aux, pchave_get_string(raiz->pchave));
        PCHAVE *p = pchave_criar(aux);
        if (!avl_pchave_inserir(avl_destino, p))
            pchave_apagar(&p);

        // Continua a direita
        avl_pchave_adicionar_pchaves_rec(raiz->dir, avl_fonte, avl_destino);
    }
}

// Adiciona as PCHAVES de uma AVL noutra AVL
void avl_pchave_adicionar_pchaves(AVL_PCHAVE *avl_fonte, AVL_PCHAVE *avl_destino) {
    if (avl_fonte != NULL && avl_destino != NULL)
        avl_pchave_adicionar_pchaves_rec(avl_fonte->raiz, avl_fonte, avl_destino);
}

// Extrai a raiz de uma PCHAVE, removendo da AVL
// Retorna uma PCHAVE
PCHAVE *avl_pchave_get_raiz(AVL_PCHAVE *arvore) {
    // Verificações preliminares
    if (arvore == NULL) return NULL;
    if (arvore->raiz == NULL) return NULL;

    // Cria uma nova pchave a partir da raiz
    char *string_pchave = pchave_get_string(arvore->raiz->pchave);
    char *aux = malloc(strlen(string_pchave) + 1);
    strcpy(aux, string_pchave);
    PCHAVE *pchave = pchave_criar(aux);

    // Remove a raiz
    avl_pchave_remover(arvore, string_pchave);

    // Retorna a pchave
    return pchave;
}