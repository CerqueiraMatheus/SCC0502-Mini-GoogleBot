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

    //ler o arquivo de texto e adicionar os sites lidos em uma lista
    LISTA *lista_sites = lista_criar_encadeada_ler_csv(fp);

    //declaração de variáveis
    SITE *site;
    int codigo;
    int relevancia;
    char *auxname = malloc(200);
    PCHAVE *pchave;
    LISTA_PCHAVE *l = lista_pchave_criar();

    int flag = 1;

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
            //Inserir um site
            case 1:
                //pegar informações
                site = site_criar_completo();
                lista_inserir_encadeada(lista_sites, site);
                lista_imprimir_encadeada(lista_sites);
                break;
            //Remover um site
            case 2:
                printf("Digite o código do site:\n");
                scanf("%d", &codigo);
                flag = lista_remover_site_encadeada(lista_sites, codigo);
                if(flag == 0)
                    printf("código inexistente, não foi possível apagar o site\n");
                lista_imprimir_encadeada(lista_sites);
                break;
            //Inserir palavra-chave
            case 3:
                printf("Digite o código do site:\n");
                scanf("%d", &codigo);
                site = lista_busca_encadeada(lista_sites, codigo);
                printf("Digite a nova palavra-chave:\n");
                scanf("%s", auxname);
                pchave = pchave_criar(auxname);
                lista_pchave_inserir(site_get_palavras_chave(site), pchave);
                lista_imprimir_encadeada(lista_sites);
                break;
            //Atualizar relevância
            case 4:
                printf("Digite o código do site:\n");
                scanf("%d", &codigo);
                site = lista_busca_encadeada(lista_sites, codigo);
                printf("Digite a nova relevância:\n");
                scanf("%d", &relevancia);
                site_set_relevancia(site, relevancia);
                lista_imprimir_encadeada(lista_sites);
                break;
            //Sair
            default:
                printf("Programa terminado\n");
        }
    }

    return 0;
}
