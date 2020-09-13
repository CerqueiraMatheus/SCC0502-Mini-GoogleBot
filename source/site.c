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

void atualizar_relevancia(SITE **site, int nova_relevancia) {
    printf("Estou na atualizar revelância\n");
}

SITE **readFile(FILE *inputFile) {
    printf("Estou na readFile\n");

    int pos = 0;

    SITE **txt = malloc(sizeof(SITE **) * (pos + 1));
    txt[pos] = malloc(sizeof(SITE *));
    txt[pos]->palavras_chave = malloc(sizeof(char *) * 10);

    while (!feof(inputFile)) {
        int i = 0;
        char *insertionString = readLine(inputFile);

        char *pch;
        char auxName[50];
        pch = strtok(insertionString, ",");

        do {
            // Caso não seja um número
            if ((i != 0) && (i != 2)) {
                strncpy(auxName, pch - 1, strlen(pch) + 1);
                auxName[strlen(pch) + 1] = '\0';
            }

            switch (i) {
                // Caso 0: código
                case 0:
                    txt[pos]->codigo = atoi(pch);
                    printf("\ni = %d pos = %d codigo = %d\n", i, pos, txt[pos]->codigo);

                    break;

                // Caso 1: nome
                case 1:
                    txt[pos]->nome = malloc(sizeof(char) * strlen(auxName));
                    strcpy(txt[pos]->nome, auxName);
                    printf("i = %d pos = %d nome = %s\n", i, pos, txt[pos]->nome);

                    break;

                // Caso 2: relevância
                case 2:
                    txt[pos]->relevancia = atoi(pch - 1);
                    printf("i = %d pos = %d relevancia = %d\n", i, pos, txt[pos]->relevancia);
                    break;

                // Caso 3: link
                case 3:
                    txt[pos]->link = malloc(sizeof(char) * strlen(auxName));
                    strcpy(txt[pos]->link, auxName);
                    printf("i = %d pos = %d link = %s\n", i, pos, txt[pos]->link);

                    break;

                // Caso "padrão": palavras-chave
                default:
                    txt[pos]->palavras_chave = malloc(sizeof(char *) * 10);
                    txt[pos]->palavras_chave[i - 4] = malloc(sizeof(char) * strlen(auxName));
                    strcpy(txt[pos]->palavras_chave[i - 4], auxName);
                    printf("i = %d pos = %d palavra_chave[%d] = %s\n", i, pos, i - 4, txt[pos]->palavras_chave[i - 4]);

                    break;
            }

            pch = strtok(NULL, ",");
            if (pch != NULL) pch++;
            i++;
        } while (pch != NULL);

        pos++;
        txt = realloc(txt, sizeof(SITE **) * (pos + 1));
        txt[pos] = malloc(sizeof(SITE *));
        txt[pos]->palavras_chave = malloc(sizeof(char *) * 10);
    }

    for (int i = 0; i < pos; i++) {
        printf("\n%d\n", txt[i]->codigo);
        printf("%s\n", txt[i]->nome);
        printf("%d\n", txt[i]->relevancia);
        printf("%s\n", txt[i]->link);
        //for(int j = 0; j < 3; j++)
        //	printf("%s\n", txt[i]->palavra_chave[j]);
        printf("%s\n", txt[i]->palavras_chave[0]);
        //printf("%s\n", txt[i]->palavra_chave[1]);
        //printf("%s\n", txt[i]->palavra_chave[2]);
    }
}