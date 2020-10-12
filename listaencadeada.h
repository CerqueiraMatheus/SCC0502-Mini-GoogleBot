#ifndef LISTA_H
#define LISTA_H

	#define TAM_MAX 100 /*estimativa do tamanho máximo da lista*/
	#define TRUE 1 
	#define FALSE 0
	#define boolean int /*define um tipo booleano*/
	#define inicial 0
	#define ERRO -32000
	#define ORDENADA 1

	#include "item.h"

	typedef struct lista_ LISTA;

	LISTA *lista_criar_encadeada(void);
	boolean lista_inserir_encadeada(LISTA *lista, ITEM *item);
	boolean lista_remover_encadeada(LISTA *lista, int chave);
	void lista_apagar_encadeada(LISTA **lista);
	ITEM *lista_busca_encadeada(LISTA *lista, int chave);

	int lista_tamanho_encadeada(LISTA *lista);
	boolean lista_vazia_encadeada(LISTA *lista);
	boolean lista_cheia_encadeada(LISTA *lista);
	void lista_imprimir_encadeada(LISTA *lista);
	void lista_inverter_encadeada(LISTA **lista);
	int lista_comparar_encadeada(LISTA *l1, LISTA *l2);
  
#endif
