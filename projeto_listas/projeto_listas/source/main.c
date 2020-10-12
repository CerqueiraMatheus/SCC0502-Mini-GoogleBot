#include <stdio.h>
#include <stdlib.h>

#include "listaencadeada.h"
#include "site.h"
#include "lista_pchave.h"

#define TRUE 1
#define FALSE 0

int main() {
    //fazer a leitura do arquivo googlebot.txt
    FILE *fp = fopen("googlebot.txt", "r");

    LISTA *lista_sites = lista_criar_encadeada_ler_csv(fp);

    SITE *site;
    int codigo;
    char *nome;
    int relevancia;
    char *link;
    char *auxname;
    PCHAVE *pchave;
    LISTA_PCHAVE *l;

    int escolha = 0;
    printf("=====MENU=====\n");
    printf("1. Inserir um site\n");
    printf("2. Remover um site\n");
    printf("3. Inserir palavra-chave\n");
    printf("4. Atualizar relevância\n");
    printf("5. Sair\n");

    while (escolha != 5) {
        printf("Digite sua escolha:\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                //pegar informações
                site = site_criar();
                scanf("%d", &codigo);
                scanf("%s", nome);
                scanf("%d", &relevancia);
                scanf("%s", link);
                scanf("%s", auxname);
                pchave = pchave_criar(auxname);
                site_set_codigo(site, codigo);
                site_set_nome(site, nome);
                site_set_relevancia(site, relevancia);
                site_set_link(site, link);
                lista_pchave_inserir(l, pchave);
                site_set_palavras_chave(site, l);
                lista_inserir_encadeada(lista_sites, site);
                break;
            case 2:
                scanf("%d", &codigo);
                lista_remover_site_encadeada(lista_sites, codigo);
                //fazer uma função para tratamento de erro
                break;
            case 3:
                scanf("%s", auxname);
                pchave = pchave_criar(auxname);
                lista_pchave_inserir(l, pchave);
                site_set_palavras_chave(site, l);
                break;
            case 4:
                scanf("%d", &relevancia);
                site_set_relevancia(site, relevancia);
                break;
            default:
                printf("ERRO\n");
        }
    }

    return 0;
}