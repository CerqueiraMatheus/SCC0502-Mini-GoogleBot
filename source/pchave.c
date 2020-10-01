#include "pchave.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pchave_ {
    char string[LIMITE_STRING];
};

// Cria palavra-chave
PCHAVE *pchave_criar(char *string) {
    PCHAVE *pchave;
    pchave = (PCHAVE *)malloc(sizeof(PCHAVE));

    if (pchave != NULL && strlen(string) < LIMITE_STRING)
        strcpy(pchave->string, string);

    return pchave;
}

// Apaga uma palavra-chave a partir de seu endereço
boolean pchave_apagar(PCHAVE **pchave) {
    if (*pchave) {
        free(*pchave);
        *pchave = NULL;
        return TRUE;
    }
    return FALSE;
}

// Imprime os dados de uma palavra-chave
void pchave_imprimir(PCHAVE *pchave) {
    if (pchave != NULL)
        printf("\n --> item %s", pchave->string);
}

// Retorna a string de uma palavra-chave
char *pchave_get_string(PCHAVE *pchave) {
    if (pchave != NULL)
        return pchave->string;
    // Saída não padronizada
    printf("ERRO!");
    exit(1);
}

// Configura a string de uma palavra-chave
boolean pchave_set_string(PCHAVE *pchave, int string) {
    if (pchave != NULL) {
        strcpy(pchave->string, string);
        return TRUE;
    }
    return FALSE;
}