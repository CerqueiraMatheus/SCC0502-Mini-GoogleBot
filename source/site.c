#include "site.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

// Struct para sites
struct site_ {
    int codigo;
    char *nome;
    int relevancia;
    char *link;
    char **palavras_chave;
    int qtde_palavras_chave;
};

/*
	1.Inserir um site: a inserção deve ser ordenada pela chave primária, isto é, o código do
site. O sistema não deve aceitar valores de código já existentes;
	2. Remover um site: dado um código, deve-se excluir o site. Caso um código inexistente
seja inserido, uma mensagem deve ser printada ao usuário a respeito disso;
	3. Inserir palavra-chave: dado um código, pode-se adicionar uma nova palavra-chave.
	4. Atualizar relevância: dado um código, deve-se atualizar a relevância do site;
	5. Sair: finalizar o programa.
*/

SITE *inserir_site(int codigo, char *nome, int relevancia, char *link, char **palavra_chave) {
    printf("Estou na inserir site\n");
}

int remover_site(SITE **site) {
    printf("Estou na remover site\n");
}

void inserir_palavra_chave(SITE **site, char *nova_palavra) {
    printf("Estou na inserir palavra-chave\n");
}

void atualizar_relevancia(SITE *site, int nova_relevancia) {
    if (site != NULL)
        site->relevancia = nova_relevancia;
}

SITE **readFile(FILE *inputFile) {
    printf("Estou na readFile\n");

    SITE **sites = NULL;
    int pos = 0;

    while (!feof(inputFile)) {
        // Aloca a lista de sites e o site atual
        sites = realloc(sites, sizeof(SITE *) * (pos + 1));
        sites[pos] = calloc(1, sizeof(SITE));

        // Inicializa o contador de linhas
        int i = 0;

        //Recebe a linha
        char *insertionString = readLine(inputFile);

        //Recebe a string até a próxima vírgula
        char *pch;
        char aux_name[50];
        pch = strtok(insertionString, ",");

        do {
            // Caso não seja um número
            if ((i != 0) && (i != 2)) {
                strncpy(aux_name, pch - 1, strlen(pch) + 1);
                aux_name[strlen(pch) + 1] = '\0';
            }

            switch (i) {
                // Caso 0: código
                case 0:
                    sites[pos]->codigo = atoi(pch);
                    printf("\ni = %d pos = %d codigo = %d\n", i, pos, sites[pos]->codigo);

                    break;

                // Caso 1: nome
                case 1:
                    sites[pos]->nome = calloc(200, sizeof(char));
                    strcpy(sites[pos]->nome, aux_name);
                    printf("i = %d pos = %d nome = %s\n", i, pos, sites[pos]->nome);

                    break;

                // Caso 2: relevância
                case 2:
                    sites[pos]->relevancia = atoi(pch - 1);
                    printf("i = %d pos = %d relevancia = %d\n", i, pos, sites[pos]->relevancia);
                    break;

                // Caso 3: link
                case 3:
                    sites[pos]->link = calloc(strlen(aux_name) + 1, sizeof(char));
                    strcpy(sites[pos]->link, aux_name);
                    printf("i = %d pos = %d link = %s\n", i, pos, sites[pos]->link);

                    break;

                // Caso "padrão": palavras-chave
                default:
                    // Realoca o array de palavras-chave de acordo
                    // com a quantidade armazenada na struct (e incrementa)
                    sites[pos]->palavras_chave =
                        realloc(sites[pos]->palavras_chave,
                                ++(sites[pos]->qtde_palavras_chave) * sizeof(char *));

                    // Aloca a palavra de acordo com o tamanho da auxliar
                    sites[pos]->palavras_chave[sites[pos]->qtde_palavras_chave - 1] =
                        calloc(strlen(aux_name) + 1, sizeof(char));

                    //Copia o conteúdo da palavra auxiliar para a atual
                    strcpy(
                        sites[pos]->palavras_chave[sites[pos]->qtde_palavras_chave - 1],
                        aux_name);

                    printf("i = %d pos = %d palavra_chave[%d] = %s\n", i, pos, i - 4, sites[pos]->palavras_chave[i - 4]);

                    break;
            }
            pch = strtok(NULL, ",");
            if (pch != NULL) pch++;
            i++;

        } while (pch != NULL);

        pos++;
    }

    for (int i = 0; i < pos; i++) {
        printf("\n%d\n", sites[i]->codigo);
        printf("%s\n", sites[i]->nome);
        printf("%d\n", sites[i]->relevancia);
        printf("%s\n", sites[i]->link);
        for (int j = 0; j < 3; j++)
            printf("%s\n", sites[i]->palavras_chave[j]);
    }
    return NULL;
}