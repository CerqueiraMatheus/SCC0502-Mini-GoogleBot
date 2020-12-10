#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "site.h"
#include "utils.h"

typedef struct no NO;
struct no {
    SITE *site;
    NO *esq;
    NO *dir;
    int altura;
};

struct avl {
    NO *raiz;
    int profundidade;
};

//cria uma avl inicializando sua raiz como NULL e sua profundidade como -1
AVL *avl_criar(void) {
    AVL *arvore = (AVL *)malloc(sizeof(AVL));
    if (arvore != NULL) {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
    }
    return arvore;
}

//apaga os nós da árvore
void avl_apagar_aux(NO **raiz) {
    if (*raiz != NULL) {
        avl_apagar_aux(&((*raiz)->esq));
        avl_apagar_aux(&((*raiz)->dir));
        site_apagar(&(*raiz)->site);
        free(*raiz);
        *raiz = NULL;
    }
}

//apaga a árvore
void avl_apagar(AVL **arvore) {
    avl_apagar_aux(&(*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

//calcula a altura de determinado nó
int avl_altura_no(NO *raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

//faz uma rotação para a direita
NO *rodar_direita(NO *a) {
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    a->altura = max(avl_altura_no(a->esq),
                    avl_altura_no(a->dir)) +
                1;
    b->altura = max(avl_altura_no(b->esq),
                    a->altura) +
                1;
    return b;
}

//faz uma rotação para a esquerda
NO *rodar_esquerda(NO *a) {
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    a->altura = max(avl_altura_no(a->esq),
                    avl_altura_no(a->dir)) +
                1;
    b->altura = max(avl_altura_no(b->dir),
                    a->altura) +
                1;
    return b;
}

//faz uma rotação para a esquerda e depois para a direita
NO *rodar_esquerda_direita(NO *a) {
    a->esq = rodar_esquerda(a->esq);
    return rodar_direita(a);
}

//faz uma rotação para a direita e depois para a esquerda
NO *rodar_direita_esquerda(NO *a) {
    a->dir = rodar_direita(a->dir);
    return rodar_esquerda(a);
}

//cria um novo nó a partir de um item
NO *avl_cria_no(SITE *site) {
    NO *no = (NO *)malloc(sizeof(NO));
    if (no != NULL) {
        no->altura = 0;
        no->dir = NULL;
        no->esq = NULL;
        no->site = site;
    }
    return no;
}

//insere um nó de forma balanceada
NO *avl_inserir_no(NO *raiz, SITE *site) {
    if (raiz == NULL) {
        raiz = avl_cria_no(site);
        if (raiz == NULL) {
            printf("raiz nula dps do inserir no\n");
        }
    } else if (site_get_codigo(site) > site_get_codigo(raiz->site))
        raiz->dir = avl_inserir_no(raiz->dir, site);
    else if (site_get_codigo(site) < site_get_codigo(raiz->site))
        raiz->esq = avl_inserir_no(raiz->esq, site);

    raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;

    if (avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir) == -2) {
        if (site_get_codigo(site) > site_get_codigo(raiz->dir->site))
            raiz = rodar_esquerda(raiz);
        else
            raiz = rodar_direita_esquerda(raiz);
    }

    if (avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir) == 2) {
        if (site_get_codigo(site) < site_get_codigo(raiz->esq->site))
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }

    return raiz;
}

//insere um nó na árvore
boolean avl_inserir(AVL *arvore, SITE *site) {
    arvore->raiz = avl_inserir_no(arvore->raiz, site);
    if (arvore->raiz != NULL)
        return 1;
    else {
        printf("raiz nula dps do inserir no\n");
        return 0;
    }
}

void troca_max_esq(NO *troca, NO *raiz, NO *ant) {
    if (troca->dir != NULL) {
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }
    if (raiz == ant)
        ant->esq = troca->esq;
    else
        ant->dir = troca->esq;

    raiz->site = troca->site;
    free(troca);
    troca = NULL;
}

NO *avl_remover_aux(NO **raiz, int chave) {
    NO *p;
    if (*raiz == NULL)
        return NULL;
    else if (chave == site_get_codigo((*raiz)->site)) {
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            p = *raiz;
            if ((*raiz)->esq == NULL)
                *raiz = (*raiz)->dir;
            else
                *raiz = (*raiz)->esq;
            free(p);
            p = NULL;
        } else
            troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
    } else if (chave < site_get_codigo((*raiz)->site)) {
        (*raiz)->esq = avl_remover_aux(&(*raiz)->esq, chave);
        (*raiz)->altura = max(avl_altura_no((*raiz)->esq), avl_altura_no((*raiz)->dir)) + 1;
    } else if (chave > site_get_codigo((*raiz)->site)) {
        (*raiz)->dir = avl_remover_aux(&(*raiz)->dir, chave);
        (*raiz)->altura = max(avl_altura_no((*raiz)->esq), avl_altura_no((*raiz)->dir)) + 1;
    }

    if (*raiz != NULL) {
        if (avl_altura_no((*raiz)->esq) - avl_altura_no((*raiz)->dir) == -2) {
            if (avl_altura_no((*raiz)->dir->esq) - avl_altura_no((*raiz)->dir->dir) <= 0) {
                *raiz = rodar_esquerda(*raiz);
            } else {
                *raiz = rodar_direita_esquerda(*raiz);
            }
        }
        if (avl_altura_no((*raiz)->esq) - avl_altura_no((*raiz)->dir) == 2) {
            if (avl_altura_no((*raiz)->esq->esq) - avl_altura_no((*raiz)->esq->dir) >= 0) {
                *raiz = rodar_direita(*raiz);
            } else {
                *raiz = rodar_esquerda_direita(*raiz);
            }
        }
    }

    return *raiz;
}

//remove um nó a partir de sua chave, mas continua deixando a árvore final balanceada
boolean avl_remover(AVL *T, int chave) {
    return ((T->raiz = avl_remover_aux(&T->raiz, chave)) != NULL);
}

SITE *avl_busca2(NO *raiz, int chave) {
    if (raiz == NULL) {
        return NULL;
    } else {
        if (chave == site_get_codigo(raiz->site)) {
            return (raiz->site);
        } else {
            if (chave < site_get_codigo(raiz->site)) {
                return (avl_busca2(raiz->esq, chave));
            } else {
                return (avl_busca2(raiz->dir, chave));
            }
        }
    }
}

//faz uma busca na árvore através de uma chave e retorna o item procurado
SITE *avl_busca(AVL *T, int chave) {
    return (avl_busca2(T->raiz, chave));
}

//realiza o percurso pré-ordem recursivamente
void avl_preordem(NO *raiz) {
    if (raiz != NULL) {
        site_imprimir(raiz->site);
        printf("\n");
        avl_preordem(raiz->esq);
        avl_preordem(raiz->dir);
    }
}

//realiza o percurso em-ordem recursivamente
void avl_emordem(NO *raiz) {
    if (raiz != NULL) {
        avl_emordem(raiz->esq);
        site_imprimir(raiz->site);
        avl_emordem(raiz->dir);
    }
}

//realiza o percurso pos-ordem recursivamente
void avl_posordem(NO *raiz) {
    if (raiz != NULL) {
        avl_posordem(raiz->esq);
        avl_posordem(raiz->dir);
        site_imprimir(raiz->site);
    }
}

//imprime a árvore seguindo o percurso escolhido
void avl_imprimir_arvore(AVL *T) {
    if (PRE_ORDER) {
        avl_preordem(T->raiz);
    }
    if (EM_ORDER)
        avl_emordem(T->raiz);
    if (POS_ORDER)
        avl_posordem(T->raiz);
}

// Lê um arquivo .csv
// Retorna uma lista de sites
AVL *avl_site_ler_csv(FILE *arquivo) {
    AVL *avl = avl_criar();
    SITE *site = NULL;
    char *linha_lida = NULL;
    int pos = 0;

    do {
        site = site_criar();
        PCHAVE *pchave;

        // Inicializa o contador de linhas
        int i = 0;

        //Recebe a linha
        linha_lida = ler_linha(arquivo, 0);

        // Estrutura para adaptar a parte que será lida
        char *auxiliar = NULL;

        //Recebe a string até a próxima vírgula
        char *linha_parte;
        linha_parte = strtok(linha_lida, ",");

        // Enquanto a parte for diferente de NULL
        do {
            // Caso a parte não seja um número,
            // trata a string e adiciona à auxiliar
            if ((i != 0) && (i != 2)) {
                auxiliar = malloc(strlen(linha_parte) + 2);
                strcpy(auxiliar, linha_parte - 1);
                auxiliar[strlen(linha_parte) + 1] = '\0';
            }
            switch (i) {
                // Caso 0: código
                case 0:
                    site_set_codigo(site, atoi(linha_parte));
                    break;
                // Caso 1: nome
                case 1:
                    site_set_nome(site, auxiliar);
                    break;

                // Caso 2: relevância
                case 2:
                    site_set_relevancia(site, atoi(linha_parte - 1));
                    break;

                // Caso 3: link
                case 3:
                    site_set_link(site, auxiliar);
                    break;

                // Caso "padrão": palavras-chave
                default:
                    pchave = pchave_criar(auxiliar);
                    lista_pchave_inserir(site_get_palavras_chave(site), pchave);
                    break;
            }
            // Parte para a próxima parte da linha
            linha_parte = strtok(NULL, ",");
            if (linha_parte != NULL) linha_parte++;
            i++;

        } while (linha_parte != NULL);

        // Parte para um novo site
        pos++;

        // Insere o site na lista
        avl_inserir(avl, site);

        // Libera a linha
        free(linha_lida);
    } while (!feof(arquivo));

    return avl;
}
