#include "lista_site.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef struct no_ NO;
// Define um nó de site
struct no_ {
    SITE *site;
    NO *proximo;
};
// Define a estrutura da lista_site
struct lista_site_ {
    NO *inicio;
    NO *fim;
    int tamanho;
};

// Cria uma nova lista de site vazia
// Retorna uma lista de sites
LISTA_SITE *lista_site_criar() {
    LISTA_SITE *lista = (LISTA_SITE *)malloc(sizeof(LISTA_SITE));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return (lista);
}

// Insere um novo nó na lista de sites de forma que esta continue ordenada
// Retorna um boolean
boolean lista_site_inserir_posicao(LISTA_SITE *lista, SITE *site) {
    NO *no_atual;
    NO *no_anterior;
    NO *no_novo;

    if (lista != NULL) {
        // Caso a lista tenha sites
        if (lista->tamanho != 0) {
            no_atual = lista->inicio;
            no_anterior = NULL;

            // Percorre a lista
            while (no_atual != NULL) {
                // Caso seja a posição correta para inserção
                if (site_get_relevancia(site) > site_get_relevancia(no_atual->site) ||
                    (site_get_codigo(site) <= site_get_codigo(no_atual->site) &&
                     site_get_relevancia(site) == site_get_relevancia(no_atual->site))) {
                    // Prevenção de sites iguais
                    if (site_get_codigo(site) == site_get_codigo(no_atual->site))
                        return FALSE;

                    // Cria um novo nó e o adiciona
                    no_novo = (NO *)malloc(sizeof(NO));
                    no_novo->site = site;
                    no_novo->proximo = no_atual;

                    if (no_anterior)
                        no_anterior->proximo = no_novo;
                    else
                        lista->inicio = no_novo;

                    // Incrementa o tamanho
                    lista->tamanho++;
                    return TRUE;
                }

                // Caso não seja, continua a percorrer
                else {
                    no_anterior = no_atual;
                    no_atual = no_atual->proximo;
                }
            }

            // Caso a relevância do site a ser inserido seja a menor da lista
            no_novo = (NO *)malloc(sizeof(NO));
            lista->fim->proximo = no_novo;
            no_novo->site = site;
            no_novo->proximo = NULL;
            lista->fim = no_novo;

            // Incrementa o tamanho
            lista->tamanho++;

            return TRUE;
        }

        // Caso a lista não possua nenhum site ainda
        else {
            no_novo = (NO *)malloc(sizeof(NO));
            lista->inicio = no_novo;
            lista->fim = no_novo;
            no_novo->site = site;
            no_novo->proximo = NULL;

            // Incrementa o tamanho
            lista->tamanho++;

            return TRUE;
        }
    }
    return FALSE;
}

// Insere um site na lista
// Retorna um boolean
boolean lista_site_inserir(LISTA_SITE *lista, SITE *site) {
    // Caso o site não exista
    if (!lista_site_buscar(lista, site_get_relevancia(site)))
        return lista_site_inserir_posicao(lista, site);

    else
        return FALSE;
}

// Busca um site binária ou sequencialmente
// Retorna um site
SITE *lista_site_buscar(LISTA_SITE *lista, int codigo) {
    NO *atual;

    // Caso a lista exista
    if (lista != NULL) {
        // Percorre a lista
        atual = lista->inicio;
        while (atual != NULL && site_get_relevancia(atual->site) <= codigo) {
            // Compara o elemento
            if (site_get_relevancia(atual->site) == codigo)
                return (atual->site);
            atual = atual->proximo;
        }
    }
    return NULL;
}

// Checa se a lista está vazia
// Retorna um boolean
boolean lista_site_vazia(LISTA_SITE *lista) {
    if ((lista != NULL) && lista->inicio == NULL)
        return (TRUE);
    return (FALSE);
}

// Checa se a lista está cheia
// Retorna um boolean
boolean lista_site_cheia(LISTA_SITE *lista) {
    int contador = 0;

    NO *atual;

    // Caso a lista exista
    if (lista != NULL) {
        // Percorre a lista
        atual = lista->inicio;
        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }
    }

    if (lista->tamanho == contador)
        return TRUE;
    else
        return FALSE;
}

// Remove recursivamente os nós
void lista_site_apagar_rec(LISTA_SITE *lista, NO *anterior, NO *atual) {
    // Caso a lista exista
    if (lista != NULL && lista->tamanho != 0) {
        if (site_get_codigo(atual->site) != site_get_codigo(lista->fim->site)) {
            lista_site_apagar_rec(lista, atual, atual->proximo);
        }

        free(atual);
        if (anterior) {
            anterior->proximo = NULL;
            lista->fim = anterior;
        } else {
            lista->inicio = NULL;
            lista->fim = NULL;
        }
        lista->tamanho--;
    }
}

// Apaga a lista completamente a partir de seu endereço
void lista_site_apagar(LISTA_SITE **lista) {
    if (*lista != NULL) {
        if ((*lista)->tamanho != 0)
            lista_site_apagar_rec(*lista, NULL, (*lista)->inicio);
        free(*lista);
        *lista = NULL;
    }
}

// Imprime todos os sites de uma lista
void lista_site_imprimir(LISTA_SITE *lista, int flag) {
    NO *atual;
    boolean imprimiu_valor = FALSE;

    printf("Lista de sites mais relevantes:\n");
    if (lista != NULL) {
        printf("\n");
        atual = lista->inicio;
        int i = 0;
        while (atual != NULL) {
            i++;
            imprimiu_valor = TRUE;
            if (!flag || i < 6) {
                site_imprimir(atual->site);
                printf("\n");
            }
            atual = atual->proximo;
        }

        if (!imprimiu_valor)
            printf("A lista não contém nenhum elemento!\n");
    } else
        printf("A lista é nula\n");
}

// Informa as palavras-chave de um site
// Retorna uma AVL_PCHAVE
AVL_PCHAVE *lista_site_get_pchaves(LISTA_SITE *lista) {
    AVL_PCHAVE *pchave_total = NULL;
    // Caso a lista exista
    if (lista != NULL) {
        pchave_total = avl_pchave_criar();

        NO *atual = lista->inicio;
        while (atual != NULL) {
            AVL_PCHAVE *pchave_site = site_get_palavras_chave(atual->site);
            avl_pchave_adicionar_pchaves(pchave_site, pchave_total);
            atual = atual->proximo;
        }
    }

    return pchave_total;
}

// Insere os sites de uma lista de sites origem numa lista de destino
void lista_site_inserir_sites(LISTA_SITE *lista_origem, LISTA_SITE *lista_destino) {
    NO *atual;

    // Caso a lista exista
    if (lista_origem != NULL) {
        // Percorre a lista
        atual = lista_origem->inicio;
        while (atual != NULL) {
            lista_site_inserir(lista_destino, atual->site);
            atual = atual->proximo;
        }
    }
}