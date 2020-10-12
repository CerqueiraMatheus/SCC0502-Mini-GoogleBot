#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "listaencadeada.h"


typedef struct no_ NO;
struct no_{
	ITEM *item;
	NO *proximo;
};

struct lista_{
	NO *inicio;
	NO *fim;
	int tamanho;
};

LISTA *lista_criar_encadeada(void){
	LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
	if(lista != NULL) {
		lista->inicio = NULL;
		lista->fim = NULL;
		lista->tamanho = 0;
	}
	return (lista);
}


 /*Insere um novo nó no fim da lista. PARA LISTAS NÃO ORDENADAS*/
boolean lista_inserir_fim_encadeada(LISTA *lista, ITEM *item){
	if (lista != NULL) {
		NO *pnovo = (NO *) malloc(sizeof (NO));
		if (lista->inicio == NULL){
			pnovo->item = item;
			lista->inicio = pnovo;
			pnovo->proximo = NULL;
		}
		else {
			lista->fim->proximo = pnovo;
			pnovo->item = item;
			pnovo->proximo = NULL;
		}
		lista->fim = pnovo;
		lista->tamanho++;
		return (TRUE);
	} else
		return (FALSE);
}

boolean lista_inserir_posicao_encadeada(LISTA *lista, ITEM *item){
	NO *p;
	NO *q;
	int i = 0;
	if (lista != NULL){
		if(lista->tamanho != 0){
			p = lista->inicio;
			q = lista->inicio;
			while (p != NULL) {
				if (item_get_chave(p->item) > item_get_chave(item)){
					NO *pnovo = (NO *) malloc(sizeof (NO));
					q->proximo = pnovo;
					pnovo->item = item;
					pnovo->proximo = p;
					lista->tamanho++;
					return (TRUE);
				}
				else{
					if(i == 1)	q = q->proximo; //sempre um endereço a menos que p
					i++;
					p = p->proximo;
				}
			}
			NO *pnew = (NO *) malloc(sizeof (NO));
			lista->fim->proximo = pnew;
			pnew->item = item;
			pnew->proximo = NULL;
			lista->fim = pnew;
			lista->tamanho++;
			return (TRUE);
		}
		else{
			NO *pnovo = (NO *) malloc(sizeof (NO));
			lista->inicio = pnovo;
			lista->fim = pnovo;
			pnovo->item = item;
			pnovo->proximo = NULL;
			lista->tamanho++;
			return (TRUE);
		}
	}
	return(FALSE);

}


boolean lista_inserir_encadeada(LISTA *lista, ITEM *item){
	int x = 0;
	if(ORDENADA)
		x = lista_inserir_posicao_encadeada(lista, item);
	else
		x = lista_inserir_fim_encadeada(lista, item);

	return x;
}



ITEM *lista_busca_sequencial_encadeada(LISTA *lista, int chave){
	NO *p;
	if (lista != NULL){
		p = lista->inicio;
		while (p != NULL) {
			if (item_get_chave(p->item) == chave)
				return (p->item);
			p = p->proximo;
		}
	}
	return(NULL);
}

ITEM *lista_busca_binaria_encadeada(LISTA *lista, int chave){

	int begin = 0;
    int end = lista->tamanho - 1;
    NO *p;
	while (begin <= end) {  /* Condição de parada */
    	p = lista->inicio;
        int i = (begin + end) / 2;  /* Calcula o meio do sub-vetor */
    	for(int j = 0; j < i; j++)	p = p->proximo;
        if (item_get_chave(p->item) == chave)
			return (p->item);
        if (item_get_chave(p->item) < chave) {  /* chave está no sub-vetor à direita */
            begin = i + 1;
        } else {  /* vector[i] > chave. Item está no sub-vetor à esquerda */
            end = i;
        }
    }

    return(NULL);
}

ITEM *lista_busca_encadeada(LISTA *lista, int chave){
	ITEM *x = malloc(sizeof(ITEM*));
	if(ORDENADA)
		x = lista_busca_binaria_encadeada(lista, chave);
	else
		x = lista_busca_sequencial_encadeada(lista, chave);

	return x;
}

boolean lista_vazia_encadeada(LISTA *lista){
	if((lista != NULL) && lista->inicio == NULL)
		return (TRUE);
	return (FALSE);
}

boolean lista_cheia_encadeada(LISTA *lista){
	int count = 0;
	NO *p;
	if (lista != NULL){
		p = lista->inicio;
		while (p != NULL) {
			count++;
			p = p->proximo;
		}
	}
	if(lista->tamanho == count)	return (TRUE);
	else	return (FALSE);
}


boolean lista_remover_item_encadeada(LISTA *lista, int chave) {
	if (lista != NULL){
		NO *p = lista->inicio; NO *aux = NULL;
		while(p != NULL && (item_get_chave(p->item)) != chave) { /*procura até achar chave ou fim lista*/
			aux = p;
			/*aux - guarda posição anterior ao nó sendo pesquisado (p)*/
			p = p->proximo;
		}
		if(p != NULL) {
			if(p == lista->inicio) { /*se a chave está no 1o nó (Exceção a ser tratada!)*/
				lista->inicio = p->proximo;
				p->proximo = NULL;
			}
			else {
				aux->proximo = p->proximo;
				p->proximo = NULL;
			}
			if(p == lista->fim){
				/*se chave está no último nó*/
				lista->fim = aux;
				lista->tamanho--; free(p); return (TRUE);
			}
		}
		return (FALSE);
	}
}


void no_apagar(int *aux, LISTA *lista){
	NO *p = lista->inicio;
	//caso base
	if((*aux) == 0){
		return;
	}
	//caso recursivo
	else{
		//chega até o próximo endereço a ser apagado
		for(int i = 0; i < (*aux); i++){
			p = p->proximo;
		}
		free(p);
		(*aux)--;
		no_apagar(aux, lista);
	}
}

void lista_apagar_encadeada(LISTA **lista){
	int aux = (*lista)->tamanho;
	//apaga os nós
	no_apagar(&aux,(*lista));
	//apaga a lista
	free(*lista);
}


void no_inverter(int *aux, LISTA *lista){
	NO *p = lista->inicio;
	NO *q = lista->inicio;
	//caso base
	if((*aux) == 0){
		return;
	}
	//caso recursivo
	else{
		//o nó posterior(x+1) tem que receber o endereço que d nó anterior (x-1)
		for(int i = 1; i < (*aux); i++){
			p = p->proximo;
		}
		for(int i = 1; i < (*aux)-2; i++){
			q = q->proximo;
		}
		//caso seja o penúltimo nó 
		if((*aux) == 2)
			p->proximo = lista->inicio;
		//caso seja o último nó
		else if((*aux) == 1)
			p->proximo = NULL;
		//demais casos
		else
			p->proximo = q->proximo;
		(*aux)--;
		no_inverter(aux, lista);
	}
}

void lista_inverter_encadeada(LISTA **lista){
	int aux = (*lista)->tamanho;
	//guarda os endereos do início e fim da lista
	NO *inicio = (*lista)->inicio;
	NO *fim = (*lista)->fim;
	//inverte os nós
	no_inverter(&aux, (*lista));
	//inverte a estrutura da lista
	(*lista)->fim = inicio;
	(*lista)->inicio = fim;
}

void lista_imprimir_encadeada(LISTA *lista){
	NO *p;
	if (lista != NULL){
		p = lista->inicio;
		while (p != NULL) {
			printf("%d\n", item_get_chave(p->item));
			p = p->proximo;
		}
	}
	printf("\n");
}

void no_comparar(LISTA *l1, LISTA *l2, int *aux, int *count){
	NO *p;
	NO *q;
	p = l1->inicio;
	q = l2->inicio;
	//chega até o próximo endereço a ser apagado
	for(int i = 1; i < (*count); i++){
		p = p->proximo;
	}
	for(int i = 1; i < (*count); i++){
		q = q->proximo;
	}
	//caso recursivo
	if((p != NULL) && (q != NULL)){
		//se forem iguais, incrementa uma variável
		if (item_get_chave(p->item) == item_get_chave(q->item))
			(*aux)++;
		else
			(*aux) = 0;
		(*count)++;
		no_comparar(l1, l2, aux, count);
	}
	//caso base
	else return;

}

int lista_comparar_encadeada(LISTA *l1, LISTA *l2){
	int aux = 0, count = 0;
	no_comparar(l1, l2, &aux, &count);
	if (aux == count)//as listas são iguais
		return 1;
	else
		return 0;
}
