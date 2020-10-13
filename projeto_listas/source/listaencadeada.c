#include "listaencadeada.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef struct no_ NO;
struct no_ {
    SITE *site;
    NO *proximo;
};

struct lista_ {
    NO *inicio;
    NO *fim;
    int tamanho;
};

//cria uma nova lista encadeada vazia
LISTA *lista_criar_encadeada(void) {
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return (lista);
}

//retorna uma lista de sites a partir da leitura de um arquivo csv
LISTA *lista_criar_encadeada_ler_csv(FILE *inputFile) {
    LISTA *lista_sites = lista_criar_encadeada();
    SITE *site = NULL;
    char *insertionString = NULL;
    int pos = 0;

    do {
        site = site_criar();
        PCHAVE *pchave;
        LISTA_PCHAVE *l = lista_pchave_criar();

        // Inicializa o contador de linhas
        int i = 0;

        //Recebe a linha
        insertionString = ler_linha(inputFile, 0);

        //Recebe a string até a próxima vírgula
        char *pch;

        char *aux_name = NULL;

        pch = strtok(insertionString, ",");
        do {
            // Caso não seja um número
            if ((i != 0) && (i != 2)) {
                aux_name = malloc(strlen(pch) + 2);
                strcpy(aux_name, pch - 1);
                aux_name[strlen(pch) + 1] = '\0';
            }
            switch (i) {
                // Caso 0: código
                case 0:
                    site_set_codigo(site, atoi(pch));
                    break;
                // Caso 1: nome
                case 1:
                    site_set_nome(site, aux_name);
                    break;

                // Caso 2: relevância
                case 2:
                    site_set_relevancia(site, atoi(pch - 1));
                    break;

                // Caso 3: link
                case 3:
                    site_set_link(site, aux_name);
                    break;

                // Caso "padrão": palavras-chave
                default:
                    pchave = pchave_criar(aux_name);
                    lista_pchave_inserir(l, pchave);
                    site_set_palavras_chave(site, l);
                    break;
            }
            pch = strtok(NULL, ",");
            if (pch != NULL) pch++;
            i++;
        } while (pch != NULL);
        pos++;
        lista_inserir_encadeada(lista_sites, site);
        free(insertionString);
    } while (!feof(inputFile));
    return lista_sites;
}

/*Insere um novo nó no fim da lista. PARA LISTAS NÃO ORDENADAS*/
boolean lista_inserir_fim_encadeada(LISTA *lista, SITE *site) {
    if (lista != NULL) {
        NO *pnovo = (NO *)malloc(sizeof(NO));
        if (lista->inicio == NULL) {
            pnovo->site = site;
            lista->inicio = pnovo;
            pnovo->proximo = NULL;
        } else {
            lista->fim->proximo = pnovo;
            pnovo->site = site;
            pnovo->proximo = NULL;
        }
        lista->fim = pnovo;
        lista->tamanho++;
        return (TRUE);
    } else
        return (FALSE);
}

//*Insere um novo nó na lista de forma que esta continue orddenada. PARA LISTAS ORDENADAS*
boolean lista_inserir_posicao_encadeada(LISTA *lista, SITE *site) {
    NO *p;
    NO *q;
    if (lista != NULL) {
        if (lista->tamanho != 0) {
            NO *p = lista->inicio;
            NO *q = NULL;
            while (p != NULL) {
                //Checa qual é a posição da lista que o site deve ser inserido
                if (site_get_codigo(p->site) > site_get_codigo(site)) {
                    NO *pnovo = (NO *)malloc(sizeof(NO));
                    q->proximo = pnovo;
                    pnovo->site = site;
                    pnovo->proximo = p;
                    lista->tamanho++;
                    return (TRUE);
                } else {
                    q = p;
                    /*aux - guarda posição anterior ao nó sendo pesquisado (p)*/
                    p = p->proximo;
                }
            }
            //caso o código do site a ser inserido seja o maior da lista
            //este é colocado ao final desta
            NO *pnew = (NO *)malloc(sizeof(NO));
            lista->fim->proximo = pnew;
            pnew->site = site;
            pnew->proximo = NULL;
            lista->fim = pnew;
            lista->tamanho++;
            return (TRUE);
        }
        //caso a lista não possua nenhum site ainda, este será inserido no início
        else {
            NO *pnovo = (NO *)malloc(sizeof(NO));
            lista->inicio = pnovo;
            lista->fim = pnovo;
            pnovo->site = site;
            pnovo->proximo = NULL;
            lista->tamanho++;
            return (TRUE);
        }
    } else
        printf("ia inserir mas a lista é nula\n");
    return (FALSE);
}

// Define se o site será obrigatóriamente inserido no fim ou não da lista,
// dependendo se esta é ordenada ou não
boolean lista_inserir_encadeada(LISTA *lista, SITE *site) {
    if (!lista_busca_encadeada(lista, site_get_codigo(site)))
        if (ORDENADA)
            return lista_inserir_posicao_encadeada(lista, site);
        else
            return lista_inserir_fim_encadeada(lista, site);
    else
        return FALSE;
}

//realiza a busca de um site numa lista de forma sequencial
//para listas não ordenadas
SITE *lista_busca_sequencial_encadeada(LISTA *lista, int chave) {
    NO *p;
    if (lista != NULL) {
        p = lista->inicio;
        while (p != NULL) {
            if (site_get_codigo(p->site) == chave)
                return (p->site);
            p = p->proximo;
        }
    }
    return (NULL);
}

//realiza a busca de um site numa lista de forma binária
//para listas ordenadas
SITE *lista_busca_binaria_encadeada(LISTA *lista, int chave) {
    int begin = 0;
    int end = lista->tamanho - 1;
    NO *p;

    while (begin <= end) { /* Condição de parada */
        p = lista->inicio;
        int i = (begin + end) / 2; /* Calcula o meio do sub-vetor */

        for (int j = 0; j < i; j++) p = p->proximo;

        if (site_get_codigo(p->site) == chave)
            return (p->site);

        if (site_get_codigo(p->site) < chave) /* chave está no sub-vetor à direita */
            begin = i + 1;
        else /* vector[i] > chave. Item está no sub-vetor à esquerda */
            end = i;
    }

    return (NULL);
}

//define se o site será obrigatóriamente buscado de forma binária
//ou sequencialmente, dependendo se esta é ordenada ou não
SITE *lista_busca_encadeada(LISTA *lista, int chave) {
    if (ORDENADA)
        return lista_busca_binaria_encadeada(lista, chave);
    else
        return lista_busca_sequencial_encadeada(lista, chave);
}

//checa se a lista está vazia
boolean lista_vazia_encadeada(LISTA *lista) {
    if ((lista != NULL) && lista->inicio == NULL)
        return (TRUE);
    return (FALSE);
}

//checa se a lista está cheia
boolean lista_cheia_encadeada(LISTA *lista) {
    int count = 0;
    NO *p;
    if (lista != NULL) {
        p = lista->inicio;
        while (p != NULL) {
            count++;
            p = p->proximo;
        }
    }
    if (lista->tamanho == count)
        return (TRUE);
    else
        return (FALSE);
}

/// Remove um site da lista a partir de um código
boolean lista_remover_site_encadeada(LISTA *lista, int codigo) {
    NO *aux = NULL;
    NO *p = NULL;

    if (lista != NULL) {
        p = lista->inicio;

        while (p != NULL && site_get_codigo(p->site) != codigo) {
            aux = p;
            p = p->proximo;
        }

        if (p != NULL) {
            // Início
            if (p == lista->inicio)
                lista->inicio = p->proximo;
            //Meio
            else
                aux->proximo = p->proximo;
            
            p->proximo = NULL;

            // Fim
            if (p == lista->fim)
                lista->fim = aux;

            site_apagar(&(p->site));
            free(p);
            lista->tamanho--;
            return TRUE;
        }
    }
    return FALSE;
}

// Apaga a lista a partir de um item atual
void lista_apagar_recursivamente(LISTA **lista, NO *atual) {
    if (atual == (*lista)->fim) {
        lista_remover_site_encadeada(*lista, site_get_codigo(atual->site));
        return;
    }

    lista_apagar_recursivamente(lista, atual->proximo);
    lista_remover_site_encadeada(*lista, site_get_codigo(atual->site));

    if ((*lista)->tamanho == 0) {
        free(*lista);
        *lista = NULL;
    }
}

// Apaga a lista completamente
void lista_apagar_encadeada(LISTA **lista) {
    if (*lista != NULL)
        lista_apagar_recursivamente(lista, (*lista)->inicio);
}

//inverte os nós da lista
void no_inverter(int *aux, LISTA *lista) {
    NO *p = lista->inicio;
    NO *q = lista->inicio;
    //caso base
    if ((*aux) == 0) {
        return;
    }
    //caso recursivo
    else {
        //o nó posterior(x+1) tem que receber o endereço que d nó anterior (x-1)
        for (int i = 1; i < (*aux); i++) {
            p = p->proximo;
        }
        for (int i = 1; i < (*aux) - 2; i++) {
            q = q->proximo;
        }
        //caso seja o penúltimo nó
        if ((*aux) == 2)
            p->proximo = lista->inicio;
        //caso seja o último nó
        else if ((*aux) == 1)
            p->proximo = NULL;
        //demais casos
        else
            p->proximo = q->proximo;
        (*aux)--;
        no_inverter(aux, lista);
    }
}

//inverte a lista
void lista_inverter_encadeada(LISTA **lista) {
    int aux = (*lista)->tamanho;
    //guarda os endereos do início e fim da lista
    NO *inicio = (*lista)->inicio;
    NO *fim = (*lista)->fim;
    //inverte os nós
    no_inverter(&aux, (*lista));
    //inverte a estrutura da lista
    (*lista)->fim = inicio;
    (*lista)->inicio = fim;
}

//imprime todos os sites de uma lista
void lista_imprimir_encadeada(LISTA *lista) {
    NO *p;
    boolean imprimiu_valor = FALSE;

    if (lista != NULL) {
        printf("\n");
        p = lista->inicio;

        while (p != NULL) {
            imprimiu_valor = TRUE;
            site_imprimir(p->site);
            printf("\n");
            p = p->proximo;
        }

        if (!imprimiu_valor)
            printf("A lista não contém nenhum elemento!\n");
    } else
        printf("A lista é nula\n");
}

//compara os nós de duas listas
void no_comparar(LISTA *l1, LISTA *l2, int *aux, int *count) {
    NO *p;
    NO *q;
    p = l1->inicio;
    q = l2->inicio;
    //chega até o próximo endereço a ser apagado
    for (int i = 1; i < (*count); i++) {
        p = p->proximo;
    }
    for (int i = 1; i < (*count); i++) {
        q = q->proximo;
    }
    //caso recursivo
    if ((p != NULL) && (q != NULL)) {
        //se forem iguais, incrementa uma variável
        if (site_get_codigo(p->site) == site_get_codigo(q->site))
            (*aux)++;
        else
            (*aux) = 0;
        (*count)++;
        no_comparar(l1, l2, aux, count);
    }
    //caso base
    else
        return;
}

//compara se duas listas são iguais ou não
int lista_comparar_encadeada(LISTA *l1, LISTA *l2) {
    int aux = 0, count = 0;
    no_comparar(l1, l2, &aux, &count);
    if (aux == count)  //as listas são iguais
        return 1;
    else
        return 0;
}
