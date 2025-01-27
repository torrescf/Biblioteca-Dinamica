# Biblioteca Dinâmica

## Descrição do Projeto

Este projeto implementa um sistema de gerenciamento de catálogo de livros. O sistema permite:

- Leitura de um arquivo CSV contendo informações sobre livros.
- Organização dos dados em um vetor de estruturas.
- Realização de diversas operações como busca, ordenação, inserção, sobrescrita e remoção de dados.

## Estrutura do Catálogo

A estrutura `Catalogo` contém os seguintes campos:

- **identificador**: Identificador único do livro.
- **nome**: Nome do livro.
- **nomeAutor**: Nome do autor do livro.
- **numPaginas**: Número de páginas do livro.
- **lancamento**: Ano de lançamento do livro.
- **genero**: Gênero do livro.
- **editora**: Editora do livro.

## Funções Principais

- **escreverEmArquivoBinario**: Escreve os dados do catálogo em um arquivo binário.
- **lerDoArquivoBinario**: Lê os dados do catálogo de um arquivo binário.
- **buscaBinariaNome**: Realiza uma busca binária pelo nome do livro.
- **buscaBinariaAno**: Realiza uma busca binária pelo ano de lançamento do livro.
- **quickSortNome**: Ordena o catálogo pelo nome dos livros usando o algoritmo Quick Sort.
- **quickSortAno**: Ordena o catálogo pelo ano de lançamento dos livros usando o algoritmo Quick Sort.
- **quicksortidentificador**: Ordena o catálogo pelo identificador dos livros usando o algoritmo Quick Sort.
- **main**: Função principal que gerencia a interação com o usuário e executa as operações solicitadas.
 
