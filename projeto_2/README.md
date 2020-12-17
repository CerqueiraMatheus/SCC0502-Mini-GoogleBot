# Mini Googlebot

Segundo trabalho da Disciplina de Algoritmos e Estruturas de Dados I, ministrada pelo professor Dr. Rudinei Goularte, no segundo semestre de 2020. O objetivo consiste em construir um sistema em C usando as estruturas de dados e conceitos vistos nas aulas para que sejam indexados, criados e pesquisados sites de acordo com palavras-chave e relevâncias.

## Informações preliminares

### Objetivo

> O objetivo deste projeto é desenvolver um Mini Googlebot, isto é, uma simulação do algoritmo Google real para captação de informações. O Google utiliza um robô, chamado Googlebot, para varrer a web em busca de links que apontem para sites. O resultado é um conjunto de informações de cada site, permitindo que o algoritmo de busca do Google faça computações sobre as mesmas decidindo a relevância (ou não) de cada site para a busca do usuário. O projeto deverá então utilizar estruturas de dados adequadas para armazenar (em memória) e processar as informações de modo eficiente.

### Implementação e estruturação do programa

Para construção do programa, utilizou-se a linguagem C-99, com o compilador GCC e, para visualização de erros, o Valgrind. Em conjunto, os autores, através do Git e GitHub, estruturaram o programa usando Tipos Abstratos de Dados, sendo que, em sua totalidade, foram criados 15 arquivos (entre .c e .h), divididos nas subpastas *source* e *include*, excluindo-se o arquivo principal *main.c*, disposto na raiz do projeto. Destarte, para atender os requisitos do trabalho, foram utilizadas as estruturas *SITE*, para os sites, *PCHAVE*, para as palavras-chave, *AVL-SITE*, para uma árvore AVL de sites, *AVL-PCHAVE*, para uma árvore AVL de palavras-chave, *LISTA-SITE*, para uma lista duplamente encadeada de sites, além das funções de uso geral contidas sob *UTILS*. Por fim, em *PROMPT-USUARIO*, há a aplicação dos TADs mencionados, junto das operações visuais necessárias.

### Funções do programa

- **Inserir um site**: O usuário informa as informações de um site (código, nome, relevância, link e conjunto de palavras-chave). O código informado não pode ser igual a um site já inserido no conjunto e deve conter, no máximo, quatro dígitos (não negativo); a relevância deve ser um número n tal que n esteja entre 0 e mil; o conjunto de palavras-chave deve conter, no máximo, **10** elementos. Ao final, o programa apresenta o conjunto de sites atualizado.

- **Remover um site**: O usuário informa o código de um site; caso o site esteja no conjunto de sites atual, executa a remoção. Ao final, o programa apresenta o conjunto de sites atualizado.

- **Inserir palavra-chave em um site**: O usuário informa o código de um site; caso o site esteja no conjunto de sites atual, recebe a nova relevância e atualiza o site. Ao final, o programa apresenta o conjunto de sites atualizado.

- **Atualizar relevância de um site**: O usuário informa o código de um site; caso o site esteja no conjunto de sites atual, recebe a nova palavra-chave e atualiza o site. Ao final, o programa apresenta o conjunto de sites atualizado.

- **Pesquisar por uma palavra-chave no conjunto atual de sites**: O usuário informa uma palavra-chave; caso haja um ou mais sites com a palavra-chave informada, o programa retorna a conjunto de sites ordenado por relevância.

- **Sugerir sites a partir de uma palavra-chave**: O usuário informa uma palavra-chave; caso haja um ou mais sites com a palavra-chave, o programa armazena o(s) site(s). Então, o programa extrai todas as palavras-chave contidas no novo conjunto armazenado de sites e, para cada uma delas, realiza uma busca no conjunto original de sites, armazenando cada site que contenha ao menos uma das palavras-chave extraídas. Por fim exibe, de acordo com a relevância, os cinco primeiros sites.  

### Execução do programa

Para o funcionamento do programa, é necessário um arquivo *googlebot.txt*, anexado na raiz da entrega. Com isso, basta executá-lo através de, num terminal aberto na raiz do projeto:

```./test```

## Justificativas para as implementações

### TADs SITE e PCHAVE

A partir da interpretação da descrição do projeto, entendemos que seria necessário utilizar um TAD item para cada site informado, com a chave *código* e os atributos *nome*, *relevância* e *link*. Além deles, cada site contém um conjunto de palavras-chave que, por ser fator fundamental em outras funções, tornou evidente que cada palavra-chave deveria ser tratada individualmente como, assim como site, em um TAD item.

### AVL-PCHAVE

Havíamos implementado, na parte I, um *array* ordenado para armazenar as palavras-chave, uma vez que a quantidade de elementos é limitada, com custos (nos piores casos) para inserção e remoção de **O(n)** e, para buscas, de **O(n)**. No entanto, dadas as novas operações, a limitação deixou de existir: para realizarmos a operação de sugestão, um número indefinido de palavras-chave deveria ser armazenado; além disso, tanto na operação de busca, quanto na de sugestão (em escala indefinidamente maior), são executadas buscas no conjunto de palavras-chave de um determinado site.

Portanto, dadas as necessidades de inserção, busca e memória, além do fato de que, num conjunto de palavras-chave não há repetição, optou-se por usar um TAD AVL para o conjunto, mantendo a eficiência na busca quando comparada às demais árvores para o caso. Acrescentamos uma função para executar parte da operação de sugestão: a cópia das palavras-chave de uma lista a outra. Obtivemos, então, nos piores casos, para inserção, remoção e busca, de palavras-chave **O(n)**. Além disso, por usar uma estrutura de nós, solveu o problema de realocação da memória sequencial na primeira implementação. Por fim, implementamos uma nova função para retirar um elemento qualquer (no caso, a raiz), para a função de sugestão.

### LISTA-SITE

Ainda na parte I, havíamos implementado uma lista encadeada de sites (com opção de ordenação), uma vez que o número de sites lidos era indefinido e, consequentemente, uma implementação não encadeada acarretaria em problemas de memória no que diz respeito às realocações proporcionalmente ao número de elementos.

Decidimos utilizar a mesma implementação com alterações (fixando a ordenação e colocando como chave a relevância dos sites) para as novas funções de busca e de sugestão, uma vez que não seria possível usar as estruturas de árvores vistas em razão da possibilidade de repetição de sites com relevâncias iguais. Dessa forma, a lista permite sites com chaves iguais, mas não com códigos iguais, para evitar duplicação.

Vale ressaltar que, assim como na estrutura para o conjunto das palavras-chave, criamos uma função para adicionar os sites de uma lista em outra. Além disso, a remoção de apenas um único item não ocorre durante a execução, tornando a operação não relevante. Obtivemos, portanto, na estrutura, complexidades (nos piores casos) de busca e inserção de um item e remoção de todos os itens de **O(n)**.

### AVL-SITE

Como mencionado anteriormente, na primeira implementação foi utilizada uma lista encadeada para o conjunto geral de sites. No entanto, como são indefinidos os números de inserção e remoção e, principalmente, de buscas, além do fato de que cada código no conjunto é único, optou-se por utilizar uma árvore AVL para armazenar o conjunto de sites.

Dessa forma, combinamos a eficiência obtida na busca de uma estrutura sequencial com a melhoria de memória advinda de encadeamentos, mesmo após indefinidas operações. Como complexidades, assim como na estrutura para o conjunto das palavras-chave, obtivemos, nos piores casos, **O(n)**, tanto para inserção, busca e remoção de elementos.

### PROMPT-USUARIO

Por último, para *centralizar* o uso dos TADs criados, desenvolveu-se uma interface exclusiva como *meio-termo* entre os TADs e o usuário, sendo responsável pelas exibições. Poderia ter sido suprimida, mas, por escolha dos autores visando legibilidade e melhor compreensão do código desenvolvido, foi mantida.

## Considerações finais

Quanto às estruturas utilizadas, ficou evidente que, havendo um conjunto sem repetições, de tamanho indefinido e ordenado por uma chave única, a estrutura AVL é consideravelmente eficiente. No entanto, o presente trabalho (considerando a primeira e a segunda parte) mostrou que pode não ser uma *solução universal*. Cada situação exige uma análise criteriosa diferente.

Trabalhar em dupla facilitou todo o processo, uma vez que agregou dois pontos de vista diferentes às análises e diminuiu substancialmente a carga de trabalho. Por fim, para além do escopo da disciplina, trabalhar em equipe, especialmente no cenário atual, proporciona interação, discussões e até mesmo momentos de diversão, reduzidos no nosso dia-a-dia.

## Integrantes

- Matheus Henrique de Cerqueira Pinto (nUSP: 11911104)
- Raíssa Torres Barreira (nUSP: 11796336)
