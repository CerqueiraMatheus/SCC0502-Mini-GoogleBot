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

## Justificativas para as escolhas das estruturas

- Escolhemos utilizar o TAD (Tipo Abstrato de Dados) pois, nessa aplicação queremos que o usuário só "enxergue” a interface, não a implementação.

## Justificativas para as implementações escolhidas para as estruturas e de seus métodos

- Utilizamos o TAD de lista sequencial para a lista de palavras chave de cada site pois, de acordo com o enuciado do problema, o número máximo de elementos dessa lista é 10, um valor imutável.
- Utilizamos o TAD de lista encadeada para a lista de sites. O número de sites é mutável, podendo-se facilmente aumentar ou diminuir de acordo com a necessidade do uśuário. 

## Integrantes

- Matheus Henrique de Cerqueira Pinto
- Raíssa Torres Barreira
