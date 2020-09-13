#include <stdio.h>
#include <stdlib.h>

#include "site.h"
#include "utils.h"

#define TRUE 1
#define FALSE 0

int main() {
    //fazer a leitura do arquivo googlebot.txt
    FILE *fp = fopen("googlebot.txt", "r");
    SITE **txt = readFile(fp);

    SITE *site;
    int codigo;
    char *nome;
    int relevancia;
    char *link;
    char **palavras_chave;
    char *nova_palavra;
    int nova_relevancia;
    int flag;

    int escolha = 0;
    printf("=====MENU=====\n");
    printf("1. Inserir um site\n");
    printf("2. Remover um site\n");
    printf("3. Inserir palavra-chave\n");
    printf("4. Atualizar relevância\n");
    printf("5. Sair\n");
    printf("Digite sua escolha:\n");
    scanf("%d", &escolha);

    while (escolha != 5) {
        switch (escolha) {
            case 1:
                //pegar informações
                site = inserir_site(codigo, nome, relevancia, link, palavras_chave);
                //tornar o site criado visível para todo o programa
                break;
            case 2:
                flag = remover_site(&site);
                //fazer uma função para tratamento de erro
                break;
            case 3:
                //ler a nova palavra
                inserir_palavra_chave(&site, nova_palavra);
                break;
            case 4:
                //ler a nova relevância
                atualizar_relevancia(&site, nova_relevancia);
                break;
            default:
                printf("ERRO\n");
        }
        printf("Digite sua escolha:\n");
        scanf("%d", &escolha);
    }

    return 0;
}
