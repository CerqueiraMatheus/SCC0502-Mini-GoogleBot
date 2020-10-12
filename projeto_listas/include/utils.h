#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LER_LINHA 2048

char *ler_linha(FILE *entrada);
void limpa_entrada(FILE *entrada);

#endif