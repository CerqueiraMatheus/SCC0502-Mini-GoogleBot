#include "utils.h"

#include <stdbool.h>

//Função para ler linha
char *ler_linha(FILE *entrada, int tamanho_maximo) {
    char *string = 0, aux;
    int posicao = 0;
    bool estouro_tamanho = false;

    do {
        if (posicao % BUFFER_LER_LINHA == 0) {
            string =
                (char *)realloc(string, (posicao / BUFFER_LER_LINHA + 1) * BUFFER_LER_LINHA);
        }
        aux = fgetc(entrada);

        if (aux != '\n' && aux != '\r' && !feof(entrada))
            string[posicao++] = aux;

        // Se exceder o tamanho máximo
        if (tamanho_maximo != 0 && posicao == tamanho_maximo)
            estouro_tamanho = true;

    } while (aux != '\n' && aux != '\r' && !feof(entrada) && !estouro_tamanho);

    string[posicao] = '\0';

    if (estouro_tamanho) {
        free(string);
        string = NULL;
        return NULL;
    } else {
        return string;
    }
}

// Função para limpar lixo de entrada
void limpa_entrada(FILE *entrada) {
    int c;

    if (entrada != NULL) {
        //Consome todos os caracteres de stdin
        while (((c = fgetc(entrada)) != '\n') && (c != EOF));
    }
}