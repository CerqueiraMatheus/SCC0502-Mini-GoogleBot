#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER 2048

// Retorna uma linha a partir de um arquivo.
char *readLine(FILE *inputFile) {
    char *line = NULL;
    int pos = 0;

    do {
        if (pos % INPUT_BUFFER == 0) {
            line = (char *)realloc(line,
                                   (pos / INPUT_BUFFER + 1) * INPUT_BUFFER);
        }
        char aux = (char)fgetc(inputFile);
        if (aux != '\r') line[pos++] = aux;
    } while (line[pos - 1] != '\n' && !feof(inputFile));

    line[pos - 1] = '\0';

    return line;
}