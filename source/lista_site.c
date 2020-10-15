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
LISTA_SITE *lista_site_criar(void) {
    LISTA_SITE *lista = (LISTA_SITE *)malloc(sizeof(LISTA_SITE));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return (lista);
}

// Lê um arquivo .csv
// Retorna uma lista de sites
LISTA_SITE *lista_site_ler_csv(FILE *arquivo) {
    LISTA_SITE *lista_site = lista_site_criar();
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
        lista_site_inserir(lista_site, site);

        // Libera a linha
        free(linha_lida);
    } while (!feof(arquivo));

    return lista_site;
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
                if (site_get_codigo(no_atual->site) > site_get_codigo(site)) {
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
    if (!lista_site_buscar(lista, site_get_codigo(site)))
        if (ORDENADA)
            return lista_site_inserir_posicao(lista, site);
        else
            return lista_site_inserir_fim(lista, site);
    else
        return FALSE;
}

// Realiza busca sequencial (lista não ordenada)
// Retorna um site
SITE *lista_site_busca_sequencial(LISTA_SITE *lista, int codigo) {
    NO *atual;

    // Caso a lista exista
    if (lista != NULL) {
        // Percorre a lista
        atual = lista->inicio;
        while (atual != NULL) {
            // Compara o elemento
            if (site_get_codigo(atual->site) == codigo)
                return (atual->site);
            atual = atual->proximo;
        }
    }
    return NULL;
}

// Realiza busca binária (lista ordenada)
// Retorna um site
SITE *lista_site_busca_binaria(LISTA_SITE *lista, int codigo) {
    int inicio = 0;
    int fim = lista->tamanho - 1;
    NO *atual;

    // Parada
    while (inicio <= fim) {
        atual = lista->inicio;

        // Calcula o meio do sub-vetor
        int i = (inicio + fim) / 2;

        for (int j = 0; j < i; j++) atual = atual->proximo;

        // Caso seja a posição procurada
        if (site_get_codigo(atual->site) == codigo)
            return (atual->site);

        // Continua a procurar a direita
        if (site_get_codigo(atual->site) < codigo)
            inicio = i + 1;

        // Continua a procurar pela esquerda
        else
            fim = i;
    }

    // Caso não encontrado
    return NULL;
}

// Busca um site binária ou sequencialmente
// Retorna um site
SITE *lista_site_buscar(LISTA_SITE *lista, int codigo) {
    if (ORDENADA)
        return lista_site_busca_binaria(lista, codigo);
    else
        return lista_site_busca_sequencial(lista, codigo);
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
    if (lista != NULL) {
        // Percorre a lista
        no_atual = lista->inicio;
        while (no_atual != NULL && site_get_codigo(no_atual->site) != codigo) {
            no_anterior = no_atual;
            no_atual = no_atual->proximo;
        }

        if (no_atual != NULL) {
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
        lista_site_remover(*lista, site_get_codigo(atual->site));
        return;
    }

    // Chamada recursiva
    lista_site_apagar_recursivamente(lista, atual->proximo);

    // Remove o site
    lista_site_remover(*lista, site_get_codigo(atual->site));

    // Se o tamanho for 0, libera a lista
    if ((*lista)->tamanho == 0) {
        free(*lista);
        *lista = NULL;
    }
}

// Apaga a lista completamente a partir de seu endereço
void lista_site_apagar(LISTA_SITE **lista) {
    if (*lista != NULL)
        lista_site_apagar_recursivamente(lista, (*lista)->inicio);
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

    printf("Lista de sites atual:\n");
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
        if (site_get_codigo(p->site) == site_get_codigo(q->site))
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
