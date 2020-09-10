#include <stdio.h>
#include <stdlib.h>

#include "Googlebot.h"

struct googlebot_ {
	int codigo;
	char *nome;
	int relevancia;
	char *link;
	char **palavra_chave;
};

/*
	1.Inserir um site: a inserção deve ser ordenada pela chave primária, isto é, o código do
site. O sistema não deve aceitar valores de código já existentes;
	2. Remover um site: dado um código, deve-se excluir o site. Caso um código inexistente
seja inserido, uma mensagem deve ser printada ao usuário a respeito disso;
	3. Inserir palavra-chave: dado um código, pode-se adicionar uma nova palavra-chave.
	4. Atualizar relevância: dado um código, deve-se atualizar a relevância do site;
	5. Sair: finalizar o programa.
*/


GOOGLEBOT *inserir_site(int codigo, char *nome, int relevancia, char *link, char **palavra_chave){

	printf("Estou na inserir site\n");
}

int remover_site(GOOGLEBOT **site){

	printf("Estou na remover site\n");
}

void inserir_palavra_chave(GOOGLEBOT **site, char *nova_palavra){

	printf("Estou na inserir palavra-chave\n");
}

void atualizar_relevancia(GOOGLEBOT **site, int nova_relevancia){

	printf("Estou na atualizar revelância\n");
}



