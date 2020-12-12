#include "avl_site.h"

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

struct avl_site {
    NO *raiz;
    int profundidade;
    int contador;
};

// Cria uma avl inicializando sua raiz como NULL e sua profundidade como -1
AVL_SITE *avl_site_criar() {
    AVL_SITE *arvore = (AVL_SITE *)malloc(sizeof(AVL_SITE));
    if (arvore != NULL) {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
        arvore->contador = 0;
    }
    return arvore;
}

// Apaga os nós da árvore
void avl_site_apagar_aux(NO **raiz) {
    if (*raiz != NULL) {
        avl_site_apagar_aux(&((*raiz)->esq));
        avl_site_apagar_aux(&((*raiz)->dir));
        site_apagar(&(*raiz)->site);
        free(*raiz);
        *raiz = NULL;
    }
}

// Apaga a árvore
void avl_site_apagar(AVL_SITE **arvore) {
    avl_site_apagar_aux(&(*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

// Calcula a altura de determinado nó
int avl_site_altura_no(NO *raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

// Faz uma rotação para a direita
NO *avl_site_rodar_direita(NO *a) {
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    a->altura = max(avl_site_altura_no(a->esq),
                    avl_site_altura_no(a->dir)) +
                1;
    b->altura = max(avl_site_altura_no(b->esq),
                    a->altura) +
                1;
    return b;
}

// Faz uma rotação para a esquerda
NO *avl_site_rodar_esquerda(NO *a) {
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    a->altura = max(avl_site_altura_no(a->esq),
                    avl_site_altura_no(a->dir)) +
                1;
    b->altura = max(avl_site_altura_no(b->dir),
                    a->altura) +
                1;
    return b;
}

// Faz uma rotação para a esquerda e depois para a direita
NO *avl_site_rodar_esquerda_direita(NO *a) {
    a->esq = avl_site_rodar_esquerda(a->esq);
    return avl_site_rodar_direita(a);
}

// Faz uma rotação para a direita e depois para a esquerda
NO *avl_site_rodar_direita_esquerda(NO *a) {
    a->dir = avl_site_rodar_direita(a->dir);
    return avl_site_rodar_esquerda(a);
}

// Cria um novo nó a partir de um item
NO *avl_site_cria_no(SITE *site) {
    NO *no = (NO *)malloc(sizeof(NO));
    if (no != NULL) {
        no->altura = 0;
        no->dir = NULL;
        no->esq = NULL;
        no->site = site;
    }
    return no;
}

// Insere um nó de forma balanceada
NO *avl_site_inserir_no(NO *raiz, SITE *site) {
    if (raiz == NULL) {
        raiz = avl_site_cria_no(site);
    }

    else if (site_get_codigo(site) == site_get_codigo(raiz->site))
        return NULL;

    else if (site_get_codigo(site) > site_get_codigo(raiz->site)) {
        NO *aux = avl_site_inserir_no(raiz->dir, site);
        if (aux == NULL) return NULL;
        raiz->dir = aux;
    }

    else if (site_get_codigo(site) < site_get_codigo(raiz->site)) {
        NO *aux = avl_site_inserir_no(raiz->esq, site);
        if (aux == NULL) return NULL;
        raiz->esq = aux;
    }

    raiz->altura = max(avl_site_altura_no(raiz->esq), avl_site_altura_no(raiz->dir)) + 1;

    if (avl_site_altura_no(raiz->esq) - avl_site_altura_no(raiz->dir) == -2) {
        if (site_get_codigo(site) > site_get_codigo(raiz->dir->site))
            raiz = avl_site_rodar_esquerda(raiz);
        else
            raiz = avl_site_rodar_direita_esquerda(raiz);
    }

    if (avl_site_altura_no(raiz->esq) - avl_site_altura_no(raiz->dir) == 2) {
        if (site_get_codigo(site) < site_get_codigo(raiz->esq->site))
            raiz = avl_site_rodar_direita(raiz);
        else
            raiz = avl_site_rodar_esquerda_direita(raiz);
    }

    return raiz;
}

// Insere um nó na árvore
boolean avl_site_inserir(AVL_SITE *arvore, SITE *site) {
    NO *aux = avl_site_inserir_no(arvore->raiz, site);

    if (aux != NULL) {
        arvore->raiz = aux;
        arvore->contador++;
        return TRUE;
    }

    return FALSE;
}

void avl_site_troca_max_esq(NO *troca, NO *raiz, NO *ant) {
    if (troca->dir != NULL) {
        avl_site_troca_max_esq(troca->dir, raiz, troca);
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

NO *avl_site_remover_aux(NO **raiz, int chave, boolean *aux) {
    NO *p;
    if (*raiz == NULL)
        return NULL;

    else if (chave == site_get_codigo((*raiz)->site)) {
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
            p = *raiz;
            *raiz = ((*raiz)->esq == NULL) ? ((*raiz)->dir) : ((*raiz)->esq);
            site_apagar(&p->site);
            free(p);
            p = NULL;
            *aux = TRUE;
        } else {
            avl_site_troca_max_esq((*raiz)->esq, (*raiz), (*raiz));
        }
    }

    else if (chave < site_get_codigo((*raiz)->site)) {
        (*raiz)->esq = avl_site_remover_aux(&(*raiz)->esq, chave, aux);
        (*raiz)->altura = max(avl_site_altura_no((*raiz)->esq), avl_site_altura_no((*raiz)->dir)) + 1;
    }

    else if (chave > site_get_codigo((*raiz)->site)) {
        (*raiz)->dir = avl_site_remover_aux(&(*raiz)->dir, chave, aux);
        (*raiz)->altura = max(avl_site_altura_no((*raiz)->esq), avl_site_altura_no((*raiz)->dir)) + 1;
    }

    if (*raiz != NULL) {
        if (avl_site_altura_no((*raiz)->esq) - avl_site_altura_no((*raiz)->dir) == -2) {
            if (avl_site_altura_no((*raiz)->dir->esq) - avl_site_altura_no((*raiz)->dir->dir) <= 0) {
                *raiz = avl_site_rodar_esquerda(*raiz);
            } else {
                *raiz = avl_site_rodar_direita_esquerda(*raiz);
            }
        }

        if (avl_site_altura_no((*raiz)->esq) - avl_site_altura_no((*raiz)->dir) == 2) {
            if (avl_site_altura_no((*raiz)->esq->esq) - avl_site_altura_no((*raiz)->esq->dir) >= 0) {
                *raiz = avl_site_rodar_direita(*raiz);
            } else {
                *raiz = avl_site_rodar_esquerda_direita(*raiz);
            }
        }
    }

    return *raiz;
}

// Remove um nó a partir de sua chave, mas continua deixando a árvore final balanceada
boolean avl_site_remover(AVL_SITE *arvore, int chave) {
    boolean removido = FALSE;
    arvore->raiz = avl_site_remover_aux(&arvore->raiz, chave, &removido);

    if (removido) {
        arvore->contador--;
        return TRUE;
    }

    return FALSE;
}

SITE *avl_site_busca_no(NO *raiz, int chave) {
    if (raiz == NULL)
        return NULL;

    // Caso 1: chave na posição atual
    if (chave == site_get_codigo(raiz->site))
        return (raiz->site);

    // Caso 2: chave na posição esquerda
    if (chave < site_get_codigo(raiz->site))
        return (avl_site_busca_no(raiz->esq, chave));

    // Caso 3: chave na posição direita
    return (avl_site_busca_no(raiz->dir, chave));
}

// Faz uma busca na árvore através de uma chave e retorna o item procurado
SITE *avl_site_busca(AVL_SITE *arvore, int chave) {
    return (avl_site_busca_no(arvore->raiz, chave));
}

// Realiza o percurso pré-ordem recursivamente
void avl_site_preordem(NO *raiz) {
    if (raiz != NULL) {
        site_imprimir(raiz->site);
        printf("\n");
        avl_site_preordem(raiz->esq);
        avl_site_preordem(raiz->dir);
    }
}

// Realiza o percurso em-ordem recursivamente
void avl_site_emordem(NO *raiz) {
    if (raiz != NULL) {
        avl_site_emordem(raiz->esq);
        site_imprimir(raiz->site);
        avl_site_emordem(raiz->dir);
    }
}

// Realiza o percurso pos-ordem recursivamente
void avl_site_posordem(NO *raiz) {
    if (raiz != NULL) {
        avl_site_posordem(raiz->esq);
        avl_site_posordem(raiz->dir);
        site_imprimir(raiz->site);
    }
}

// Imprime a árvore seguindo o percurso escolhido
void avl_site_imprimir(AVL_SITE *arvore) {
    if (arvore->contador != 0) {
        if (PRE_ORDER)
            avl_site_preordem(arvore->raiz);

        if (EM_ORDER)
            avl_site_emordem(arvore->raiz);

        if (POS_ORDER)
            avl_site_posordem(arvore->raiz);
    } else {
        printf("Não há elementos na lista! :(\n");
    }
}

// Lê um arquivo .csv
// Retorna uma lista de sites
AVL_SITE *avl_site_ler_csv(FILE *arquivo) {
    AVL_SITE *avl = avl_site_criar();
    SITE *site = NULL;
    char *linha_lida = NULL;
    int pos = 0;

    do {
        //Recebe a linha
        linha_lida = ler_linha(arquivo, 0);

        // Estrutura para adaptar a parte que será lida
        char *auxiliar = NULL;

        //Recebe a string até a próxima vírgula
        char *linha_parte;
        linha_parte = strtok(linha_lida, ",");

        if (linha_parte == NULL) {
            free(linha_parte);
            free(linha_lida);
            break;
        }

        site = site_criar();
        PCHAVE *pchave;

        // Inicializa o contador de linhas
        int i = 0;

        // Enquanto a parte for diferente de NULL
        while (linha_parte != NULL) {
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
                    avl_pchave_inserir(site_get_palavras_chave(site), pchave);
                    break;
            }
            // Parte para a próxima parte da linha
            linha_parte = strtok(NULL, ",");
            if (linha_parte != NULL) linha_parte++;
            i++;
        }

        // Parte para um novo site
        pos++;

        // Insere o site na lista
        avl_site_inserir(avl, site);

        // Libera a linha
        free(linha_lida);

    } while (!feof(arquivo));

    return avl;
}

void avl_site_busca_pchave_no(NO *raiz, char *pchave, LISTA_SITE **lista_site) {
    if (raiz != NULL) {
        avl_site_busca_pchave_no(raiz->esq, pchave, lista_site);

        if (site_checa_pchave(raiz->site, pchave))
            lista_site_inserir(*lista_site, raiz->site);

        avl_site_busca_pchave_no(raiz->dir, pchave, lista_site);
    }
}

LISTA_SITE *avl_site_busca_pchave(AVL_SITE *arvore, char *pchave) {
    if (arvore != NULL) {
        LISTA_SITE *lista_site = lista_site_criar();
        avl_site_busca_pchave_no(arvore->raiz, pchave, &lista_site);
        return lista_site;
    }

    return NULL;
}