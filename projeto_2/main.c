#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "prompt_usuario.h"
#include "utils.h"

int main() {
    FILE *arquivo_entrada = NULL;
    AVL_SITE *lista_sites = NULL;
    int codigo, escolha = 0;

    //fazer a leitura do arquivo googlebot.txt
    arquivo_entrada = fopen("googlebot.txt", "r");

    //ler o arquivo de texto e adicionar os sites lidos em uma lista
    lista_sites = avl_site_ler_csv(arquivo_entrada);

    while (escolha != 7) {
        imprime_menu();
        printf("Digite sua escolha:\n");
        scanf("%d", &escolha);
        limpa_entrada(stdin);

        switch (escolha) {
            case 1:
                inserir_site(lista_sites);
                break;

            case 2:
                remover_site(lista_sites);
                break;

            case 3:
                inserir_palavra_chave(lista_sites);
                break;

            case 4:
                atualizar_relevancia(lista_sites);
                break;

            case 5:
                busca_pchave(lista_sites);
                break;

            default:
                break;
        }
    }

    printf("\nPrograma terminado\n");
    avl_site_apagar(&lista_sites);
    fclose(arquivo_entrada);

    return EXIT_SUCCESS;
}