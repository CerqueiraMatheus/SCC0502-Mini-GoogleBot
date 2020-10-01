#ifndef PCHAVE_H
#define PCHAVE_H

#define TRUE 1
#define FALSE 0
#define boolean int

// Limite para string previsto
#define LIMITE_STRING 50

typedef struct pchave_ PCHAVE;

PCHAVE *pchave_criar(char *string);
boolean pchave_apagar(PCHAVE **pchave);
void pchave_imprimir(PCHAVE *pchave);
char *pchave_get_string(PCHAVE *pchave);
boolean pchave_set_string(PCHAVE *pchave, int string);

#endif