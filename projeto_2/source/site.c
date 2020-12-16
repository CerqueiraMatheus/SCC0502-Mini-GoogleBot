#include "site.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

// Struct para sites
struct site_ {
    int codigo;
    char *nome;
    int relevancia;
    char *link;
    AVL_PCHAVE *palavras_chave;
};

// Cria um novo site em branco
// Retorna um SITE
SITE *site_criar() {
    SITE *site = (SITE *)malloc(sizeof(SITE));
    if (site != NULL) {
        site->codigo = 0;
        site->nome = NULL;
        site->relevancia = 0;
        site->link = NULL;
        site->palavras_chave = avl_pchave_criar();
    }

    return site;
}

// Apaga um site da lista a partir de seu endereço
// Retorna um boolean
boolean site_apagar(SITE **site) {
    // Se o site existir
    if (*site != NULL) {
        if ((*site)->nome != NULL)
            free((*site)->nome);

        if ((*site)->link != NULL)
            free((*site)->link);

        if ((*site)->palavras_chave != NULL)
            avl_pchave_apagar(&((*site)->palavras_chave));

        // Libera o site
        free(*site);
        *site = NULL;
        return TRUE;
    }
    return FALSE;
}

// Imprime um site
void site_imprimir(SITE *site) {
    // Se o site existir
    if (site != NULL) {
        printf("Site [%d]: \n ", site->codigo);
        printf("\tNome: [%s]\n ", site->nome);
        printf("\tRelevância: [%d]\n ", site->relevancia);
        printf("\tLink: [%s]\n ", site->link);
        avl_pchave_imprimir(site->palavras_chave);
        printf("==========\n");
    }
}

// Informa o código de um site
// Retorna um int
int site_get_codigo(SITE *site) {
    if (site != NULL)
        return (site->codigo);
    else {
        printf("\nERRO: item_get_codigo\n");
        exit(1);
    }
}

// Informa a relevância de um site
// Retorna um int
int site_get_relevancia(SITE *site) {
    if (site != NULL)
        return (site->relevancia);
    else {
        printf("\nERRO: item_get_relevancia\n");
        exit(1);
    }
}

// Informa as palavras-chave de um site
// Retorna uma AVL_PCHAVE
AVL_PCHAVE *site_get_palavras_chave(SITE *site) {
    if (site != NULL)
        return (site->palavras_chave);
    else {
        printf("\nERRO: item_get_chave\n");
        exit(1);
    }
}

// Define um código para o site
// Retorna um boolean
boolean site_set_codigo(SITE *site, int codigo) {
    if (site != NULL) {
        site->codigo = codigo;
        return (TRUE);
    }
    return (FALSE);
}

// Define um nome para o site
// Retorna um boolean
boolean site_set_nome(SITE *site, char *nome) {
    if (site != NULL) {
        site->nome = nome;
        return (TRUE);
    }
    return (FALSE);
}

// Define uma revelância para um site
// Retorna um boolean
boolean site_set_relevancia(SITE *site, int relevancia) {
    if (site != NULL) {
        site->relevancia = relevancia;
        return (TRUE);
    }
    return (FALSE);
}

// Define um link para um site
// Retorna um boolean
boolean site_set_link(SITE *site, char *link) {
    if (site != NULL) {
        site->link = link;
        return (TRUE);
    }
    return (FALSE);
}

// Define uma lista de palavras-chave para o site
// Retorna um boolean
boolean site_set_palavras_chave(SITE *site, AVL_PCHAVE *l) {
    if (site != NULL) {
        site->palavras_chave = l;
        return (TRUE);
    }
    return (FALSE);
}

// Verifica se um site contém uma palavra-chave
// Retorna um boolean
boolean site_contem_pchave(SITE *site, char *pchave) {
    if (site != NULL) {
        AVL_PCHAVE *avl_pchave = site_get_palavras_chave(site);
        return avl_pchave_buscar(avl_pchave, pchave) != NULL;
    }
    return FALSE;
}