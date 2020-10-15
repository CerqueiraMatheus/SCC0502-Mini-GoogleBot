# Mini Googlebot

Projeto realizado para a disciplina de Algoritmos e Estrutura de Dados I do ICMC/USP.

## Objetivo

> O objetivo deste projeto é desenvolver um Mini Googlebot, isto é, uma simulação do algoritmo Google real para captação de informações. O Google utiliza um robô, chamado Googlebot, para varrer a web em busca de links que apontem para sites. O resultado é um conjunto de informações de cada site, permitindo que o algoritmo de busca do Google faça computações sobre as mesmas decidindo a relevância (ou não) de cada site para a busca do usuário. O projeto deverá então utilizar estruturas de dados adequadas para armazenar (em memória) e processar as informações de modo eficiente

## Compilador/plataforma utilizado

GCC

## Instruções de uso do programa

- Digite um número, dentre as opções apresentadas (1, 2, 3, 4 ou 5), para escolher entre:

1. Inserir um site;
2. Remover um site;
3. Inserir palavra-chave;
4. Atualizar relevância;
5. Sair.

- Digite os dados do site conforme o que for pedido na programa.

## Para ler o código

O arquivo principal é o main.c. Sob a pasta "include" estão todas as interfaces comentadas (exceto suas funções). Sob a pasta "source", encontram-se os códigos-fonte, com as funções devidamente comentadas.

## Justificativas para as implementações escolhidas para as estruturas e de seus métodos

- Utilizamos dois TADs para site, (com inserir, remover,configurar lista de palavras-chave e alterar relevância) e palavra-chave (com inserir, remover e configurar string), a fim de restringir as informações possíveis e "concentrar" as operações.
- Utilizamos o TAD de lista sequencial para a lista de palavras chave de cada site pois, de acordo com o enunciado do problema, o número máximo de elementos dessa lista é 10, um valor imutável.
- Utilizamos o TAD de lista encadeada para a lista de sites. O número de sites é mutável, podendo-se facilmente aumentar ou diminuir de acordo com a necessidade do usuário. Adicionamos uma função para que fosse possível ler diretamente um .csv.
- Ambos os TADs para as listas têm a opção "ordenada", uma vez que esta não foi especificada no problema.

## Funções externas

- No arquivo main são usadas quatro funções (imprimir menu, inserir site, remover site e atualizar relevância) que não são pertinentes aos TAD. As três últimas são utilizações das funções dos TADs desenvolvidos.
- Criamos um arquivo utils (com interface) para ler linhas e limpar o stdin. Foi necessário, uma vez que a operação se repete entre os TADs.

## Funções extras

Os TADs criados apresentam funções extras (conforme descritas no .h), que podem, em futuras implementações, serem úteis, bem como inversão, busca e comparação.

## Integrantes

- Matheus Henrique de Cerqueira Pinto (nUSP: 11911104)
- Raíssa Torres Barreira (nUSP: 11796336)
