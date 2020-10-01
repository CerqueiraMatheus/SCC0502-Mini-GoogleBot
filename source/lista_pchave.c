#include "lista_pchave.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A lista é composta por um array de itens, inicio e fim
struct lista_pchave_ {
    PCHAVE *lista[LIMITE_PALAVRAS];
    int inicio;
    int fim;
};

// Retorna uma lista
LISTA_PCHAVE *lista_pchave_criar() {
    LISTA_PCHAVE *lista = (LISTA_PCHAVE *)malloc(sizeof(LISTA_PCHAVE));

    if (lista != NULL) {
        lista->inicio = 0;
        lista->fim = 0;
    }
    return lista;
}

//TODO: implementar a função
boolean lista_pchave_inserir_ordenado(LISTA_PCHAVE *l, PCHAVE *pchave) {
}

// Para inserir de acordo com a posição
boolean lista_pchave_inserir_posicao(LISTA_PCHAVE *l, PCHAVE *pchave, int posicao) {
    if (!lista_cheia(l) && posicao <= l->fim - 1) {
        for (int i = (l->fim - 1); i >= posicao; i--) {
            l->lista[i + i] = l->lista[i];
        }

        l->lista[posicao] = pchave;
        l->fim++;
        return TRUE;
    }
    return FALSE;
}

// Insere um item na lista
boolean lista_pchave_inserir(LISTA_PCHAVE *l, PCHAVE *pchave) {
    if (!ORDENADA) {
        // Verifica se a lista está cheia
        if (l != NULL && !lista_cheia(l)) {
            // Insere o item e retorna TRUE
            l->lista[l->fim] = pchave;
            l->fim += 1;
            return TRUE;
        }
    } else {
        lista_inserir_ordenado(l, pchave);
    }
    return FALSE;
}

// Busca para lista não ordenada
int lista_pchave_busca_sequencial(LISTA_PCHAVE *l, char *string) {
    for (int i = 0; i < l->fim; i++)
        if (!strcmp(pchave_get_string(l->lista[i]), string))
            return i;
    return ERRO;
}

// Busca para lista ordenada
int lista_pchave_busca_ordenada(LISTA_PCHAVE *l, char *string) {
    for (int i = 0; i < l->fim; i++)
        if (!strcmp(pchave_get_string(l->lista[i]), string))
            return i;
        else if (item_get_chave(l->lista[i]) > chave)
            return ERRO;
    return ERRO;
}

// Procura um item na lista a partir de sua chave
PCHAVE *lista_pchave_busca(LISTA_PCHAVE *lista, char *string) {
    int posicao;
    if (ORDENADA)
        posicao = lista_busca_ordenada(lista, string);
    else
        posicao = lista_busca_sequencial(lista, string);

    if (posicao != ERRO)
        return lista->lista[posicao];
    return NULL;
}

// Remove um item da lista a partir de sua chave
boolean lista_pchave_remover(LISTA_PCHAVE *lista, char *string) {
    int item_posicao;

    // Atribui a posição do item
    if (ORDENADA)
        item_posicao = lista_busca_ordenada(lista, string);
    else
        item_posicao = lista_busca_sequencial(lista, string);

    if (item_posicao != ERRO) {
        // Remove o item da posição
        item_apagar(&lista->lista[item_posicao]);

        // Reposiciona os itens
        for (int i = item_posicao; i < lista->fim; i++)
            lista->lista[i] = lista->lista[i + 1];

        // Decrementa o fim
        lista->fim--;
        return TRUE;
    }

    return FALSE;
}

// Verifica se a lista está vazia.
// Retorna TRUE em caso positivo e FALSE caso contrário
boolean lista_pchave_vazia(LISTA_PCHAVE *lista) {
    return (lista->inicio == lista->fim);
}

// Verifica se a lista está cheia
// Retorna TRUE em caso positivo e FALSE caso contrário
boolean lista_pchave_cheia(LISTA_PCHAVE *lista) {
    if (lista->fim >= LIMITE_PALAVRAS)
        return (TRUE);
    return (FALSE);
}

// Retorna o tamanho da lista
int lista_pchave_tamanho(LISTA_PCHAVE *lista) {
    return (lista->fim);
}

// Imprime a lista
void lista_pchave_imprimir(LISTA_PCHAVE *l) {
    for (int i = l->inicio; i < l->fim; i++)
        printf("[%s] ", pchave_get_string(l->lista[i]));
    printf("\n");
}

// Remove item a item da lista e libera a lista
void lista_pchave_apagar(LISTA_PCHAVE **lista) {
    if (*lista != NULL) {
        for (int i = (*lista)->inicio; i < (*lista)->fim; i++)
            item_apagar(&(*lista)->lista[i]);
        free(*lista);
        *lista = NULL;
    }
}