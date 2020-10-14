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
    LISTA_PCHAVE *palavras_chave;
};

//lê as informações do stdin e cria um novo site completo a partir delas
SITE *site_criar_completo() {
    SITE *site = NULL;
    PCHAVE *pchave;
    char *nome = NULL, *auxiliar = NULL, *link = NULL;
    int codigo, relevancia;

    site = site_criar();
    // leitura de variáveis
    printf("Digite o código do site:\n");
    scanf("%d", &codigo);

    printf("Digite o nome do site:\n");
    limpa_entrada(stdin);
    nome = ler_linha(stdin, LIMITE_STRING);

    printf("Digite a revelância do site:\n");
    scanf("%d", &relevancia);

    printf("Digite o link do site:\n");
    limpa_entrada(stdin);
    link = ler_linha(stdin, LIMITE_PAGINA_PRINCIPAL);

    site_set_codigo(site, codigo);
    site_set_nome(site, nome);
    site_set_relevancia(site, relevancia);
    site_set_link(site, link);

    return (site);
}

//cria um novo site em branco
SITE *site_criar() {
    SITE *site = (SITE *)malloc(sizeof(SITE));
    if (site != NULL) {
        site->codigo = 0;
        site->nome = NULL;
        site->relevancia = 0;
        site->link = NULL;
        site->palavras_chave = lista_pchave_criar();
    }

    return (site);
}

//apaga um site da lista a partir de seu endereço
boolean site_apagar(SITE **site) {
    //vê se o conteúdo é diferente de 0, ou seja se existe o site
    if (*site != NULL) {
        free((*site)->nome);
        free((*site)->link);
        lista_pchave_apagar(&((*site)->palavras_chave));
        free(*site);
        //precaução extra(altera o valor da variável)
        *site = NULL;
        return (TRUE);
    }
    return (FALSE);
}

//imprime o código, o nome, a revelancia, o link e
//as palavras-chave de um determinado site
void site_imprimir(SITE *site) {
    //se não for um ponteiro nulo, ou seja, se existir
    if (site != NULL) {
        printf("codigo: %d\n ", site->codigo);
        printf("nome: %s\n ", site->nome);
        printf("relevancia: %d\n ", site->relevancia);
        printf("link: %s\n ", site->link);
        lista_pchave_imprimir(site->palavras_chave);
    }
}

//retorna o código de um site
int site_get_codigo(SITE *site) {
    if (site != NULL)
        return (site->codigo);
    else {
        printf("\nERRO: item_get_chave\n");
        exit(1);
    }
}

//retorna a lista de palavras-chave de um site
LISTA_PCHAVE *site_get_palavras_chave(SITE *site) {
    if (site != NULL)
        return (site->palavras_chave);
    else {
        printf("\nERRO: item_get_chave\n");
        exit(1);
    }
}

//define um código para o site
boolean site_set_codigo(SITE *site, int codigo) {
    if (site != NULL) {
        site->codigo = codigo;
        return (TRUE);
    }
    return (FALSE);
}

//define um nome para o site
boolean site_set_nome(SITE *site, char *nome) {
    if (site != NULL) {
        site->nome = nome;
        return (TRUE);
    }
    return (FALSE);
}

//define uma revelância para um site
boolean site_set_relevancia(SITE *site, int relevancia) {
    if (site != NULL) {
        site->relevancia = relevancia;
        return (TRUE);
    }
    return (FALSE);
}

//define um link para um site
boolean site_set_link(SITE *site, char *link) {
    if (site != NULL) {
        site->link = link;
        return (TRUE);
    }
    return (FALSE);
}

//define uma palavra-chave para um site
boolean site_set_palavras_chave(SITE *site, LISTA_PCHAVE *l) {
    if (site != NULL) {
        site->palavras_chave = l;
        return (TRUE);
    }
    return (FALSE);
}
