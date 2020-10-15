#include "lista_pchave.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A lista é composta por um array de itens, inicio e fim
struct lista_pchave_ {
    PCHAVE *lista[LIMITE_PALAVRAS];
    int inicio;
    int fim;
};

// Retorna uma lista de p_chave
LISTA_PCHAVE *lista_pchave_criar() {
    LISTA_PCHAVE *lista = (LISTA_PCHAVE *)malloc(sizeof(LISTA_PCHAVE));

    if (lista != NULL) {
        lista->inicio = 0;
        lista->fim = 0;
    }

    return lista;
}

// Verifica se s1 > s2
boolean lista_checa_strings(char *s1, char *s2) {
    int i = 0;

    //Percorre as duas palavras e compara letra por letra
    for (; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (tolower(s2[i]) > tolower(s1[i])) {
            return FALSE;
        } else if (tolower(s2[i]) < tolower(s1[i])) {
            return TRUE;
        }
    }

    //Caso termine de percorrer e as duas sejam iguais,
    //retorna a menor String
    return (s1[i] == '\0' && (s2[i] == '\0')) ? FALSE
                                              : ((s1[i] == '\0') ? FALSE : TRUE);
}

// Para inserir de acordo com a posição
boolean lista_inserir_posicao(LISTA_PCHAVE *lista, PCHAVE *pchave, int posicao) {
    for (int i = (lista->fim); i > posicao; i--)
        lista->lista[i] = lista->lista[i - 1];

    lista->lista[posicao] = pchave;
    lista->fim++;
    return TRUE;
}

//Insere uma palavra-chave ordenadamente
boolean lista_inserir_ordenado(LISTA_PCHAVE *lista, PCHAVE *pchave) {
    // Caso 1: lista vazia
    if (lista_pchave_tamanho(lista) == 0)
        return lista_inserir_posicao(lista, pchave, 0);

    // Caso 2: no meio da lista
    for (int i = lista->inicio; i < lista->fim; i++) {
        if (lista_checa_strings(pchave_get_string(lista->lista[i]),
                                pchave_get_string(pchave))) {
            return lista_inserir_posicao(lista, pchave, i);
        }
    }

    // Caso 3: no final da lista
    return lista_inserir_posicao(lista, pchave, lista->fim);
}

// Insere um item na lista
boolean lista_pchave_inserir(LISTA_PCHAVE *lista, PCHAVE *pchave) {
    if (lista != NULL && !lista_pchave_cheia(lista)) {
        if (!ORDENADA) {
            lista->lista[lista->fim] = pchave;
            lista->fim += 1;
            return TRUE;
        } else {
            return lista_inserir_ordenado(lista, pchave);
        }
    }
    return FALSE;
}

// Busca para lista não ordenada
int lista_busca_sequencial(LISTA_PCHAVE *lista, char *string) {
    for (int i = 0; i < lista->fim; i++)
        if (!strcmp(pchave_get_string(lista->lista[i]), string))
            return i;
    return ERRO;
}

// Busca binária para palavras-chave
int lista_busca_binaria(PCHAVE **lista, int inicio, int fim, char *string) {
    if (fim >= inicio) {
        int meio = (inicio + fim) / 2;

        //Caso 1: valor encontrado
        if (string == pchave_get_string(lista[meio])) return meio;

        //Caso 2: busca pela "direita"
        if (lista_checa_strings(string, pchave_get_string(lista[meio])))
            return lista_busca_binaria(lista, meio + 1, fim, string);

        //Caso 3: busca pela "esquerda"
        else
            return lista_busca_binaria(lista, inicio, meio - 1, string);
    } else {
        return ERRO;  //Caso 4: valor não encontrado
    }
}

// Busca para lista ordenada
int lista_busca_ordenada(LISTA_PCHAVE *lista, char *string) {
    return lista_busca_binaria(lista->lista, lista->inicio, lista->fim, string);
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
        pchave_apagar(&lista->lista[item_posicao]);

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
    printf("\tPalavras-chave:\n");
    for (int i = l->inicio; i < l->fim; i++) {
        printf("\t\t[%s]\n", pchave_get_string(l->lista[i]));
    }
    printf("\n");
}

// Remove item a item da lista e libera a lista
void lista_pchave_apagar(LISTA_PCHAVE **lista) {
    if (*lista != NULL) {
        for (int i = (*lista)->inicio; i < (*lista)->fim; i++)
            pchave_apagar(&(*lista)->lista[i]);
        free(*lista);
        *lista = NULL;
    }
}