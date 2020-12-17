#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "prompt_usuario.h"
#include "utils.h"

int main() {
    FILE *arquivo_entrada = NULL;
    AVL_SITE *sites = NULL;
    int codigo, escolha = 0;

    // Lê o arquivo googlebot.txt
    arquivo_entrada = fopen("googlebot.txt", "r");

    // Lê arquivo de texto e adicionar os sites lidos em uma lista
    sites = avl_site_ler_csv(arquivo_entrada);

    while (escolha != 7) {
        imprime_menu();
        printf("Digite sua escolha:\n");
        scanf("%d", &escolha);
        limpa_entrada(stdin);

        switch (escolha) {
            case 1:
                inserir_site(sites);
                break;

            case 2:
                remover_site(sites);
                break;

            case 3:
                inserir_palavra_chave(sites);
                break;

            case 4:
                atualizar_relevancia(sites);
                break;

            case 5:
                busca_pchave(sites);
                break;

            case 6:
                sugestao_sites(sites);
                break;

            default:
                break;
        }
    }

    // Termina o programa
    printf("\nPrograma terminado\n");
    avl_site_apagar(&sites);
    fclose(arquivo_entrada);

    return EXIT_SUCCESS;
}