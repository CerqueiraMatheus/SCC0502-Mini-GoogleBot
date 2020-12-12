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
LISTA_SITE *lista_site_criar() {
    LISTA_SITE *lista = (LISTA_SITE *)malloc(sizeof(LISTA_SITE));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return (lista);
}

// Insere um nó ao fim da lista de sites
boolean lista_site_inserir_fim(LISTA_SITE *lista, SITE *site) {
    if (lista != NULL) {
        // Cria o nó
        NO *pnovo = (NO *)malloc(sizeof(NO));

        // Caso a lista esteja vazia,
        // configura o início
        if (lista->inicio == NULL) {
            pnovo->site = site;
            lista->inicio = pnovo;
            pnovo->proximo = NULL;
        }
        // Caso contrário, apenas adiciona o nó
        else {
            lista->fim->proximo = pnovo;
            pnovo->site = site;
            pnovo->proximo = NULL;
        }

        // Configura o fim da lista
        lista->fim = pnovo;
        lista->tamanho++;
        return TRUE;
    }
    return FALSE;
}

// Insere um novo nó na lista de sites de forma que esta continue ordenada
boolean lista_site_inserir_posicao(LISTA_SITE *lista, SITE *site) {
    NO *no_atual;
    NO *no_proximo;
    NO *no_novo;

    if (lista != NULL) {
        // Caso a lista tenha sites
        if (lista->tamanho != 0) {
            no_atual = lista->inicio;
            no_proximo = NULL;

            // Percorre a lista
            while (no_atual != NULL) {
                // Caso seja a posição correta para inserção
                if (site_get_relevancia(no_atual->site) >= site_get_relevancia(site)) {
                    // Cria um novo nó e o adiciona
                    no_novo = (NO *)malloc(sizeof(NO));
                    no_proximo->proximo = no_novo;
                    no_novo->site = site;
                    no_novo->proximo = no_atual;

                    // Incrementa o tamanho
                    lista->tamanho++;
                    return TRUE;
                }

                // Caso não seja, continua a percorrer
                else {
                    no_proximo = no_atual;
                    no_atual = no_atual->proximo;
                }
            }

            // Caso o código do site a ser inserido seja o maior da lista
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
        while ((atual != NULL && !ORDENADA) ||
               (atual != NULL && site_get_relevancia(atual->site) <= codigo && ORDENADA)) {
            // Compara o elemento
            if (site_get_relevancia(atual->site) == codigo)
                return (atual->site);
            atual = atual->proximo;
        }
    }
    return NULL;
}

// Checa se a lista está vazia
boolean lista_site_vazia(LISTA_SITE *lista) {
    if ((lista != NULL) && lista->inicio == NULL)
        return (TRUE);
    return (FALSE);
}

// Checa se a lista está cheia
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

/// Remove um site da lista a partir de um código
boolean lista_site_remover(LISTA_SITE *lista, int codigo) {
    NO *no_anterior = NULL;
    NO *no_atual = NULL;

    // Caso a lista exista
    if (lista != NULL && lista->tamanho != 0) {
        // Percorre a lista
        no_atual = lista->inicio;
        while ((!ORDENADA && no_atual != NULL) ||
               (ORDENADA && no_atual != NULL) && (site_get_relevancia(no_atual->site) < codigo)) {
            no_anterior = no_atual;
            no_atual = no_atual->proximo;
        }

        if (no_atual != NULL && site_get_relevancia(no_atual->site) == codigo) {
            // Remove a referência de início
            if (no_atual == lista->inicio)
                lista->inicio = no_atual->proximo;

            // Remove a referência de meio
            else
                no_anterior->proximo = no_atual->proximo;

            // Retira a referência de próximo
            no_atual->proximo = NULL;

            // Fim
            if (no_atual == lista->fim)
                lista->fim = no_anterior;

            // Remove o site e atualiza a lista
            site_apagar(&(no_atual->site));
            free(no_atual);
            lista->tamanho--;

            return TRUE;
        }
    }
    return FALSE;
}

// Apaga a lista a partir de um item atual
void lista_site_apagar_recursivamente(LISTA_SITE **lista, NO *atual) {
    // Condição de parada
    if (atual == (*lista)->fim) {
        lista_site_remover(*lista, site_get_relevancia(atual->site));
        return;
    }

    // Chamada recursiva
    lista_site_apagar_recursivamente(lista, atual->proximo);

    // Remove o site
    lista_site_remover(*lista, site_get_relevancia(atual->site));
}

// Apaga a lista completamente a partir de seu endereço
void lista_site_apagar(LISTA_SITE **lista) {
    if (*lista != NULL) {
        if ((*lista)->tamanho != 0)
            lista_site_apagar_recursivamente(lista, (*lista)->inicio);
        free(*lista);
        *lista = NULL;
    }
}

//inverte os nós da lista
void lista_site_no_inverter(int *auxiliar, LISTA_SITE *lista) {
    NO *p = lista->inicio;
    NO *q = lista->inicio;

    // Caso base
    if ((*auxiliar) == 0)
        return;

    // Caso recursivo
    else {
        // O nó posterior(x+1) tem que receber o endereço que d nó anterior (x-1)
        for (int i = 1; i < (*auxiliar); i++) {
            p = p->proximo;
        }
        for (int i = 1; i < (*auxiliar) - 2; i++) {
            q = q->proximo;
        }
        // Caso seja o penúltimo nó
        if ((*auxiliar) == 2)
            p->proximo = lista->inicio;

        // Caso seja o último nó
        else if ((*auxiliar) == 1)
            p->proximo = NULL;

        // Demais casos
        else
            p->proximo = q->proximo;

        // Decrementa o auxiliar e continua a chamada
        (*auxiliar)--;
        lista_site_no_inverter(auxiliar, lista);
    }
}

// Inverte a lista
void lista_site_inverter(LISTA_SITE **lista) {
    int aux = (*lista)->tamanho;

    // Guarda os endereos do início e fim da lista
    NO *inicio = (*lista)->inicio;
    NO *fim = (*lista)->fim;

    // Inverte os nós
    lista_site_no_inverter(&aux, (*lista));

    // Inverte a estrutura da lista
    (*lista)->fim = inicio;
    (*lista)->inicio = fim;
}

//imprime todos os sites de uma lista
void lista_site_imprimir(LISTA_SITE *lista) {
    NO *atual;
    boolean imprimiu_valor = FALSE;

    printf("Lista de sites mais relevantes:\n");
    if (lista != NULL) {
        printf("\n");
        atual = lista->inicio;

        while (atual != NULL) {
            imprimiu_valor = TRUE;
            site_imprimir(atual->site);
            printf("\n");
            atual = atual->proximo;
        }

        if (!imprimiu_valor)
            printf("A lista não contém nenhum elemento!\n");
    } else
        printf("A lista é nula\n");
}

// Compara os nós de duas listas
void no_comparar(LISTA_SITE *l1, LISTA_SITE *l2, int *auxiliar, int *contador) {
    NO *p;
    NO *q;
    p = l1->inicio;
    q = l2->inicio;

    // Chega até o próximo endereço a ser apagado
    for (int i = 1; i < (*contador); i++) {
        p = p->proximo;
    }
    for (int i = 1; i < (*contador); i++) {
        q = q->proximo;
    }

    // Caso recursivo
    if ((p != NULL) && (q != NULL)) {
        // Se forem iguais, incrementa uma variável
        if (site_get_relevancia(p->site) == site_get_relevancia(q->site))
            (*auxiliar)++;
        else
            (*auxiliar) = 0;

        // Incrementa o contador
        (*contador)++;
        no_comparar(l1, l2, auxiliar, contador);
    }
    //caso base
    else
        return;
}

//compara se duas listas são iguais ou não
int lista_site_comparar(LISTA_SITE *l1, LISTA_SITE *l2) {
    int aux = 0, count = 0;
    no_comparar(l1, l2, &aux, &count);

    // As listas são iguais
    if (aux == count)
        return 1;
    else
        return 0;
}
