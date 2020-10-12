#include <stdio.h>
#include <stdlib.h>

#include "item.h"

struct item_ {
	int chave;
	/*outros componentes*/
};

ITEM *item_criar(int ch){
	ITEM *item;

	item = (ITEM *) malloc (sizeof(ITEM));

	if (item != NULL)
		item->chave = ch;
		
	return (item);
}

boolean item_apagar(ITEM **item){
	//vê se o conteúdo é diferente de 0, ou seja se existe o item
	if(*item != NULL){
		free (*item);
		//precaução extra(altera o valor da variável) 
		*item = NULL;
		return (TRUE);
	}	
	return (FALSE);
}

void item_imprimir(ITEM *item){
	//se não for um ponteiro nulo, ou seja, se existir
	if(item != NULL)
		printf("\n --> item: %d", item->chave);
}

int item_get_chave(ITEM *item){
	if (item != NULL)
		return (item->chave);
	else{
		printf("\nERRO: item_get_chave\n");
		exit(1);
	}	
}

/*
boolean item_set_chave(ITEM **item, int chave){
	if(*item != NULL){
		//o conteúdo de item é um ponteiro para a struct
		(*item)->chave = chave;
		return (TRUE);
	}
	return (FALSE);
}
*/
boolean item_set_chave(ITEM *item, int chave){
        if(item != NULL){
		item->chave = chave;
                return (TRUE);
        }
        return (FALSE);
}











