#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Livros {
    string nome, nomeAutor, genero, editora;
    int numPaginas;
    int dataLancamento;
    bool removido;

    // Função para ler dados do arquivo CSV
    void entrada_arquivo(Livros*& livros, int& tamanho) {
        ifstream entrada("livros.csv");
        if (!entrada) {
            cerr << "Erro ao abrir o arquivo livros.csv\n";
            return;
        }

        string linha;
        getline(entrada, linha); // Lê e descarta a primeira linha (cabeçalho)

        int contador = 0;
        while (getline(entrada, linha)) {
            if (contador == tamanho) {
                // Redimensiona o vetor se necessário
                int tamanhoNovo = tamanho + 5;
                Livros* novoVetor = new Livros[tamanhoNovo];
                for (int i = 0; i < tamanho; i++) {
                    novoVetor[i] = livros[i];
                }
                delete[] livros;
                livros = novoVetor;
                tamanho = tamanhoNovo;
            }

            size_t pos = 0;
            size_t next_pos;

            // Lê cada campo da linha
            try {
                // Ignora o identificador
                next_pos = linha.find(',', pos);
                pos = next_pos + 1;

                // Nome do livro
                next_pos = linha.find(',', pos);
                livros[contador].nome = linha.substr(pos, next_pos - pos);
                pos = next_pos + 1;

                // Nome do autor
                next_pos = linha.find(',', pos);
                livros[contador].nomeAutor = linha.substr(pos, next_pos - pos);
                pos = next_pos + 1;

                // Número de páginas
                next_pos = linha.find(',', pos);
                string paginasStr = linha.substr(pos, next_pos - pos);
                if (!paginasStr.empty()) {
                    livros[contador].numPaginas = stoi(paginasStr);
                } else {
                    livros[contador].numPaginas = 0; // Valor padrão se o campo estiver vazio
                }
                pos = next_pos + 1;

                // Data de lançamento
                next_pos = linha.find(',', pos);
                string dataStr = linha.substr(pos, next_pos - pos);
                if (!dataStr.empty()) {
                    livros[contador].dataLancamento = stoi(dataStr);
                } else {
                    livros[contador].dataLancamento = 0; // Valor padrão se o campo estiver vazio
                }
                pos = next_pos + 1;

                // Gênero
                next_pos = linha.find(',', pos);
                livros[contador].genero = linha.substr(pos, next_pos - pos);
                pos = next_pos + 1;

                // Editora
                livros[contador].editora = linha.substr(pos);
                livros[contador].removido = false;

                contador++;
            } catch (const invalid_argument& e) {
                cerr << "Erro ao converter campo para inteiro na linha: " << linha << "\n";
                continue; // Ignora a linha e continua para a próxima
            }
        }

        tamanho = contador;
        entrada.close();
    }
};

// Funções auxiliares
void swap(Livros& a, Livros& b) {
    Livros temp = a;
    a = b;
    b = temp;
}

void quickSortPorNome(Livros* livros, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (livros[inicio].nome > livros[meio].nome)
            swap(livros[inicio], livros[meio]);
        if (livros[inicio].nome > livros[fim].nome)
            swap(livros[inicio], livros[fim]);
        if (livros[meio].nome > livros[fim].nome)
            swap(livros[meio], livros[fim]);

        string pivo = livros[meio].nome;
        swap(livros[meio], livros[fim - 1]);
        int i = inicio, j = fim - 1;

        while (true) {
            while (livros[++i].nome < pivo);
            while (livros[--j].nome > pivo);
            if (i >= j) break;
            swap(livros[i], livros[j]);
        }
        swap(livros[i], livros[fim - 1]);

        quickSortPorNome(livros, inicio, i - 1);
        quickSortPorNome(livros, i + 1, fim);
    }
}

void quickSortPorData(Livros* livros, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        int pivo = livros[meio].dataLancamento;

        if (livros[inicio].dataLancamento > livros[meio].dataLancamento)
            swap(livros[inicio], livros[meio]);
        if (livros[inicio].dataLancamento > livros[fim].dataLancamento)
            swap(livros[inicio], livros[fim]);
        if (livros[meio].dataLancamento > livros[fim].dataLancamento)
            swap(livros[meio], livros[fim]);

        pivo = livros[meio].dataLancamento;
        swap(livros[meio], livros[fim - 1]);
        int i = inicio, j = fim - 1;

        while (true) {
            while (livros[++i].dataLancamento < pivo);
            while (livros[--j].dataLancamento > pivo);
            if (i >= j) break;
            swap(livros[i], livros[j]);
        }
        swap(livros[i], livros[fim - 1]);

        quickSortPorData(livros, inicio, i - 1);
        quickSortPorData(livros, i + 1, fim);
    }
}

void exibirLivros(Livros* livros, int inicio, int fim) {
    for (int i = inicio; i < fim; i++) {
        if (!livros[i].removido) {
            cout << "Indice " << i << "\n";
            cout << "Nome: " << livros[i].nome << "\n";
            cout << "Autor: " << livros[i].nomeAutor << "\n";
            cout << "Páginas: " << livros[i].numPaginas << "\n";
            cout << "Data de Lançamento: " << livros[i].dataLancamento << "\n";
            cout << "Gênero: " << livros[i].genero << "\n";
            cout << "Editora: " << livros[i].editora << "\n\n";
        }
    }
}

void menu() {
    cout << "                          <CATALOGO DE LIVROS>                 " << endl << endl << endl;
    cout << "1. Inserir Livro\n";
    cout << "2. Remover Livro\n";
    cout << "3. Buscar Livro por Nome\n";
    cout << "4. Buscar Livro por Data de Lancamento\n";
    cout << "5. Exibir Livros\n";
    cout << "0. Sair\n";
}

int buscaBinariaPorNome(Livros* livros, int inicio, int fim, const string& nome) {
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (livros[meio].nome == nome) {
            // Livro encontrado: exibe os detalhes
            cout << "Livro encontrado:\n";
            cout << "Nome: " << livros[meio].nome << "\n";
            cout << "Autor: " << livros[meio].nomeAutor << "\n";
            cout << "Páginas: " << livros[meio].numPaginas << "\n";
            cout << "Ano de Lançamento: " << livros[meio].dataLancamento << "\n";
            cout << "Gênero: " << livros[meio].genero << "\n\n";
            return meio; // Retorna o índice do livro encontrado
        } else if (livros[meio].nome > nome) {
            fim = meio - 1; // Busca na metade esquerda
        } else {
            inicio = meio + 1; // Busca na metade direita
        }
    }

    cout << "Livro não encontrado.\n";
    return -1; // Livro não encontrado
}

int buscaBinariaPorData(Livros* livros, int inicio, int fim, int data) {
    if (fim >= inicio) {
        int meio = inicio + (fim - inicio) / 2;

        if (livros[meio].dataLancamento == data)
            return meio;

        if (livros[meio].dataLancamento > data)
            return buscaBinariaPorData(livros, inicio, meio - 1, data);

        return buscaBinariaPorData(livros, meio + 1, fim, data);
    }
    return -1;
}

void removerLivro(Livros* livros, int tamanho) {
    if (tamanho == 0) {
        cout << "Não há livros para remover.\n";
        return;
    }

    int indice;
    cout << "Informe o índice do livro a ser removido: ";
    cin >> indice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada inválida. Por favor, insira um número inteiro.\n";
    } else if (indice >= 0 && indice < tamanho) {
        livros[indice].removido = true;
        cout << "Livro marcado como removido.\n";
    } else {
        cout << "Índice inválido.\n";
    }
}

void inserirLivro(Livros*& livros, int& tamanho, int& capacidade) {
    if (tamanho == capacidade) {
        int tamanhoNovo = capacidade + 5;
        capacidade = tamanhoNovo;
        Livros* novoVetor = new Livros[capacidade];
        for (int i = 0; i < tamanho; i++) {
            novoVetor[i] = livros[i];
        }
        delete[] livros;
        livros = novoVetor;
        tamanho = tamanhoNovo;
    }
    Livros novoLivro;
    cout << "Nome do Livro: ";
    cin.ignore();
    getline(cin, novoLivro.nome);
    cout << "Nome do Autor: ";
    getline(cin, novoLivro.nomeAutor);
    cout << "Número de Páginas: ";
    while (!(cin >> novoLivro.numPaginas) || novoLivro.numPaginas <= 0) {
        cout << "Entrada inválida. Por favor, insira um número válido de páginas: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Data de Lançamento: ";
    while (!(cin >> novoLivro.dataLancamento) || novoLivro.dataLancamento <= 0) {
        cout << "Entrada inválida. Por favor, insira uma data de lançamento válida: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Gênero: ";
    cin.ignore();
    getline(cin, novoLivro.genero);
    cout << "Editora: ";
    getline(cin, novoLivro.editora);
    novoLivro.removido = false;

    livros[tamanho] = novoLivro;
    tamanho++;
}

void cases(Livros*& livros, int& tamanho, int& capacidade, int& opcao) {
    do {
        menu();
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1:
                inserirLivro(livros, tamanho, capacidade);
                break;
            case 2:
                removerLivro(livros, tamanho);
                break;
            case 3: {
                string nome;
                cout << "Informe o nome do livro: ";
                cin.ignore(10000, '\n');
                getline(cin, nome);

                // Ordena os livros pelo nome antes de buscar
                quickSortPorNome(livros, 0, tamanho - 1);

                int indice = buscaBinariaPorNome(livros, 0, tamanho - 1, nome);
                if (indice != -1) {
                    cout << "Livro encontrado:\n";
                    exibirLivros(livros, indice, indice + 1);
                } else {
                    cout << "Livro não encontrado.\n";
                }
                break;
            }
            case 4: {
                int data;
                cout << "Informe a data de lançamento do livro: ";
                cin >> data;

                // Ordena os livros pela data antes de buscar
                quickSortPorData(livros, 0, tamanho - 1);

                int indice = buscaBinariaPorData(livros, 0, tamanho - 1, data);
                if (indice != -1) {
                    cout << "Livro encontrado:\n";
                    exibirLivros(livros, indice, indice + 1);
                } else {
                    cout << "Livro não encontrado.\n";
                }
                break;
            }
            case 5: {
                int inicio, fim;
                cout << "Informe o intervalo (1 a " << capacidade << "): ";
                cin >> inicio >> fim;
                exibirLivros(livros, inicio - 1, fim);
                break;
            }
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida.\n";
        }
    } while (opcao != 0);
    delete[] livros;
}

int main() {
    int capacidade = 40;
    Livros* livros = new Livros[capacidade];
    int tamanho = 0, opcao = 0;

    livros[0].entrada_arquivo(livros, tamanho);
    quickSortPorNome(livros, 0, tamanho - 1);
    cases(livros, tamanho, capacidade, opcao);
    return 0;
}