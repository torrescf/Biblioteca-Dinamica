// NOMES: João Pedro Olivera de Jesus Machado; Luisa 

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Livro {
    string nomeAutor, nome, genero, editora;
    int numPaginas;
    int dataLancamento;
    bool removido;

    void escreverEmArquivoBinario(ofstream& arquivo) const {
        size_t tamanhoNome = nome.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoNome), sizeof(tamanhoNome));
        if (!arquivo) {
            cerr << "Erro ao escrever o tamanho do nome.\n";
            return;
        }
        arquivo.write(nome.c_str(), tamanhoNome);
        if (!arquivo) {
            cerr << "Erro ao escrever o nome.\n";
            return;
        }
        
        size_t tamanhoNomeAutor = nomeAutor.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoNomeAutor), sizeof(tamanhoNomeAutor));
        if (!arquivo) {
            cerr << "Erro ao escrever o tamanho do nome do autor.\n";
            return;
        }
        arquivo.write(nomeAutor.c_str(), tamanhoNomeAutor);
        if (!arquivo) {
            cerr << "Erro ao escrever o nome do autor.\n";
            return;
        }
        
        size_t tamanhoEditora = editora.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoEditora), sizeof(tamanhoEditora));
        if (!arquivo) {
            cerr << "Erro ao escrever o tamanho da editora.\n";
            return;
        }
        arquivo.write(editora.c_str(), tamanhoEditora);
        if (!arquivo) {
            cerr << "Erro ao escrever a editora.\n";
            return;
        }
        
        arquivo.write(reinterpret_cast<const char*>(&numPaginas), sizeof(numPaginas));
        if (!arquivo) {
            cerr << "Erro ao escrever o número de páginas.\n";
            return;
        }
        
        arquivo.write(reinterpret_cast<const char*>(&dataLancamento), sizeof(dataLancamento));
        if (!arquivo) {
            cerr << "Erro ao escrever a data de lançamento.\n";
            return;
        }
        
        size_t tamanhoGenero = genero.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoGenero), sizeof(tamanhoGenero));
        if (!arquivo) {
            cerr << "Erro ao escrever o tamanho do gênero.\n";
            return;
        }
        arquivo.write(genero.c_str(), tamanhoGenero);
        if (!arquivo) {
            cerr << "Erro ao escrever o gênero.\n";
            return;
        }
    }
    void lerDoArquivoBinario(ifstream& arquivo) {
        size_t tamanhoNome;
        arquivo.read(reinterpret_cast<char*>(&tamanhoNome), sizeof(tamanhoNome));
        nome.resize(tamanhoNome);
        arquivo.read(&nome[0], tamanhoNome);
        
        size_t tamanhoNomeAutor;
        arquivo.read(reinterpret_cast<char*>(&tamanhoNomeAutor), sizeof(tamanhoNomeAutor));
        nomeAutor.resize(tamanhoNomeAutor);
        arquivo.read(&nomeAutor[0], tamanhoNomeAutor);
        
        arquivo.read(reinterpret_cast<char*>(&numPaginas), sizeof(numPaginas));
        arquivo.read(reinterpret_cast<char*>(&dataLancamento), sizeof(dataLancamento));
        
        size_t tamanhoGenero;
        arquivo.read(reinterpret_cast<char*>(&tamanhoGenero), sizeof(tamanhoGenero));
        genero.resize(tamanhoGenero);
        arquivo.read(&genero[0], tamanhoGenero);
        
        size_t tamanhoEditora;
        arquivo.read(reinterpret_cast<char*>(&tamanhoEditora), sizeof(tamanhoEditora));
        editora.resize(tamanhoEditora);
        arquivo.read(&editora[0], tamanhoEditora);
    }
};

void quickSortPorNome(Livro* livros, int inicio, int fim) {
    if (inicio < fim) {
        string pivo = livros[fim].nome;
        int i = inicio - 1;

        for (int j = inicio; j < fim; j++) {
            if (livros[j].nome <= pivo) {
                i++;
                swap(livros[i], livros[j]);
            }
        }
        swap(livros[i + 1], livros[fim]);

        int pi = i + 1;
        quickSortPorNome(livros, inicio, pi - 1);
        quickSortPorNome(livros, pi + 1, fim);
    }
}

void quickSortPorData(Livro* livros, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = livros[fim].dataLancamento;
        int i = inicio - 1;

        for (int j = inicio; j < fim; j++) {
            if (livros[j].dataLancamento <= pivo) {
                i++;
                swap(livros[i], livros[j]);
            }
        }
        swap(livros[i + 1], livros[fim]);

        int pi = i + 1;
        quickSortPorData(livros, inicio, pi - 1);
        quickSortPorData(livros, pi + 1, fim);
    }
}

void exibirLivros(Livro* livros, int tamanho, int inicio = 0, int fim = -1) {
    if (fim == -1) fim = tamanho;

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

void entrada_arquivo(Livro*& livros, int& tamanho) {
    ifstream entrada("Livros.csv");
    if (entrada) {
        string linha;
        getline(entrada, linha); 
        getline(entrada, linha); // Lê e descarta a primeira linha (cabeçalho)
    }
    int contador = 0;
    char delimitador = ',';
    string lixo;
    while (entrada && contador < tamanho) {
        getline(entrada, lixo, delimitador); // Ignora a numeração
        getline(entrada, livros[contador].nome,delimitador);
        getline(entrada, lixo, delimitador);
        entrada >> livros[contador].numPaginas;
        getline(entrada, lixo, delimitador);
        entrada >> livros[contador].dataLancamento;
        getline(entrada, lixo, delimitador);
        getline(entrada, livros[contador].genero,delimitador);
        getline(entrada, lixo, delimitador);
        getline(entrada, livros[contador].editora,delimitador);
        livros[contador].removido = false;
        contador++;

        // Se o contador chegar ao tamanho do vetor livros, será necessário redimensionar o vetor livros
        if (contador == tamanho) {
            int tamanhoNovo = tamanho + 5;
            Livro* vetorAux = new Livro[tamanhoNovo];
            // Preenchendo o vetorAux com os valores do vetor livros
            for (int i = 0; i < tamanho; i++) {
                vetorAux[i] = livros[i];
            }
            // Direcionar o vetor livros para o vetorAux redimensionado
            delete[] livros;
            livros = vetorAux;
            tamanho = tamanhoNovo;
        }
    }
    tamanho = contador - 1;
    entrada.close();
}

// Função que exibe o menu de opções para o usuário
void menu() {

    cout << "                          <CATALOGO DE LIVROS>                 " << endl << endl << endl;
    cout << "1. Inserir Livro\n";
    cout << "2. Remover Livro\n";
    cout << "3. Buscar Livro por Nome\n";
    cout << "4. Buscar Livro por Data de Lancamento\n";
    cout << "5. Exibir Livros\n";
    cout << "0. Sair\n";
}

int buscaBinariaPorNome(Livro* livros, int inicio, int fim, string nome) {
    if (fim >= inicio) {
        int meio = inicio + (fim - inicio) / 2;

        if (livros[meio].nome == nome)
            return meio;

        if (livros[meio].nome > nome)
            return buscaBinariaPorNome(livros, inicio, meio - 1, nome);

        return buscaBinariaPorNome(livros, meio + 1, fim, nome);
    }
    return -1;
}

// Assumes the array is sorted by dataLancamento
int buscaBinariaPorData(Livro* livros, int inicio, int fim, int data) {
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

void removerLivro(Livro* livros, int tamanho) {
    int indice;
    cout << "Informe o índice do livro a ser removido: ";
    cin >> indice;

    // Verifica se a entrada é válida
    if (cin.fail()) {
        cin.clear(); // Limpa o estado de erro
        cin.ignore(10000, '\n'); // Ignora a entrada inválida
        cout << "Entrada inválida. Por favor, insira um número inteiro.\n";
    } else if (indice >= 0 && indice < tamanho) {
        // Marca o livro como removido
        livros[indice].removido = true;
        cout << "Livro marcado como removido.\n";
    } else {
        // Índice fora do intervalo válido
        cout << "Índice inválido.\n";
    }
}

void inserirLivro(Livro*& livros, int& tamanho, int& capacidade) {
    if (tamanho == capacidade) {
        capacidade += 5; // Aumenta a capacidade em 5
        Livro* novoVetor = new Livro[capacidade];
        for (int i = 0; i < tamanho; i++) {
            novoVetor[i] = livros[i];
        }
        delete[] livros;
        livros = novoVetor;
    }
    Livro novoLivro;
    cout << "Nome do Autor: ";
    cin.ignore();
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

void cases(Livro*& livros, int& tamanho, int& capacidade, int& opcao){
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
                quickSortPorNome(livros, 0, tamanho - 1);
                int indice = buscaBinariaPorNome(livros, 0, tamanho - 1, nome);
                if (indice != -1) {
                    cout << "Livro encontrado:\n";
                    exibirLivros(livros, tamanho, indice, indice + 1);
                } else {
                    cout << "Livro não encontrado.\n";
                }
                break;
            }
            case 4: {
                int data;
                cout << "Informe a data de lançamento do livro: ";
                cin >> data;
                quickSortPorData(livros, 0, tamanho - 1);
                int indice = buscaBinariaPorData(livros, 0, tamanho - 1, data);
                if (indice != -1) {
                    cout << "Livro encontrado:\n";
                    exibirLivros(livros, tamanho, indice, indice + 1);
                } else {
                    cout << "Livro não encontrado.\n";
                }
                break;
            }
            case 5: {
                int inicio, fim;
                cout << "Informe o intervalo ( 1 a "<< capacidade << ")" << endl;
                cin >> inicio >> fim;
                exibirLivros(livros, tamanho, inicio, fim);
                break;
            }
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida.\n";
        }
    } while (opcao != 0);

}

int main() {
    int capacidade = 40;
    Livro* livros = new Livro[capacidade];
    int tamanho = 0, opcao = 0;

    entrada_arquivo(livros, tamanho);
    cases(livros, tamanho, capacidade, opcao);
    delete[] livros;
    return 0;
}
