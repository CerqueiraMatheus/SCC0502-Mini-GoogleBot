#include <stdio.h>
#include <stdlib.h>

#include "site.h"

// Struct para sites
struct site_ {
    int codigo;
    char *nome;
    int relevancia;
    char *link;
    LISTA_PCHAVE *palavras_chave;
};

SITE *site_criar(){
	SITE *site;

	site = (SITE *) malloc (sizeof(SITE));

	if (site != NULL){
		site->codigo = 0;
	    site->nome = NULL;
	    site->relevancia = 0;
	    site->link = NULL;
	    site->palavras_chave = lista_pchave_criar();
	}
		
	return (site);
}

boolean site_apagar(SITE **site){
	//vê se o conteúdo é diferente de 0, ou seja se existe o site
	if(*site != NULL){
		free((*site)->nome);
	    free((*site)->link);
	    lista_pchave_apagar(&(*site)->palavras_chave);
		free (*site);
		//precaução extra(altera o valor da variável) 
		*site = NULL;
		return (TRUE);
	}	
	return (FALSE);
}

void site_imprimir(SITE *site){
	//se não for um ponteiro nulo, ou seja, se existir
	if(site != NULL){
		printf("codigo: %d\n ", site->codigo);
		printf("nome: %s\n ", site->nome);
		printf("relevancia: %d\n ", site->relevancia);
		printf("link: %s\n ", site->link);
		lista_pchave_imprimir(site->palavras_chave);
	}
}

int site_get_codigo(SITE *site){
	if (site != NULL)
		return (site->codigo);
	else{
		printf("\nERRO: item_get_chave\n");
		exit(1);
	}	
}


boolean site_set_nome(SITE *site, char *nome){
        if(site != NULL){
			site->nome = nome;
                return (TRUE);
        }
        return (FALSE);
}


boolean site_set_relevancia(SITE *site, int relevancia){
        if(site != NULL){
			site->relevancia = relevancia;
                return (TRUE);
        }
        return (FALSE);
}

boolean site_set_link(SITE *site, char *link){
        if(site != NULL){
			site->link = link;
                return (TRUE);
        }
        return (FALSE);
}

boolean site_set_palavras_chave(SITE *site, char *aux_name){
        if(site != NULL){
			site->palavras_chave = lista_pchave_inserir(palavras_chave, pchave_criar(aux_name));
                return (TRUE);
        }
        return (FALSE);
}











