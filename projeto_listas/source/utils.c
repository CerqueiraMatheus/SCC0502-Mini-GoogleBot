#include "utils.h"

//Função para ler linha
char *ler_linha(FILE *entrada) {
    char *string = 0;
    int posicao = 0;

    do {
        if (posicao % BUFFER_LER_LINHA == 0) {
            string =
                (char *)realloc(string, (posicao / BUFFER_LER_LINHA + 1) * BUFFER_LER_LINHA);
        }
        string[posicao] = (char)fgetc(entrada);

    } while (string[posicao++] != '\n' && !feof(entrada));

    string[posicao - 1] = '\0';
    string = (char *)realloc(string, posicao);

    return string;
}

// Função para limpar lixo de entrada
void limpa_entrada(FILE *entrada) {
    int c;

    //Consome todos os caracteres de stdin
    while (((c = fgetc(entrada)) != '\n') && (c != EOF));
}