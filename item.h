#ifndef ITEM_H
	#define ITEM_H

	#define TRUE 1
	#define FALSE 0
	#define boolean int

	//deixar nome do TAD em maiúsculo
	typedef struct item_ ITEM;

	//funções de manipulação do TAD, começar com o nome do TAD
	ITEM *item_criar(int chave);
	//passar a variável por referência 
	//pois está alterando os dados em si
	boolean item_apagar(ITEM **item);
	//necessário por causa do information hiding
	//tenho que passar o ponteiro por causa do information hiding
	void item_imprimir(ITEM *item);
	//retornar o conteúdo do item
	//(get para recuperar e set para alterar)
	int item_get_chave(ITEM *item);
	boolean item_set_chave(ITEM *item, int chave);
	
#endif
