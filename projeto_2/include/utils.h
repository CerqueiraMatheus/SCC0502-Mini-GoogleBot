#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LER_LINHA 2048

char *ler_linha(FILE *entrada, int tamanho_maximo);
void limpa_entrada(FILE *entrada);
bool checa_strings(char *s1, char *s2);

#endif