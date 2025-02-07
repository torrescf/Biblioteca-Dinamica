//Nomes: João Pedro Oliveira de Jesus Machado | Matricula :202411109 ; Ana Luísa Expedito de Andrade  Godinho | Matricula: 202410857
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Livros {
    string nome, nomeAutor, genero, editora;
    int numPaginas;
    int dataLancamento;
    bool removido;

    // Função para ler dados do arquivo CSV
    void entrada_arquivo(Livros *&livros, int &tamanho, int &capacidade, string &diretorio) {
        ifstream entrada("Livros.csv");
        if (!entrada.is_open()) {
            cout << "Erro ao abrir o arquivo: " << diretorio << endl;
            return;
        }
    
        string linha;
        getline(entrada, linha); // Lê e descarta a primeira linha (cabeçalho)
    
        // Ler os dados do arquivo
        while (getline(entrada, linha)) {
            if (linha.empty()) {
            } else {
                stringstream dados_linha(linha);
                string numPaginas, dataLancamento;
    
                // Ler cada campo separado por vírgula
                if (getline(dados_linha, livros[tamanho].nome, ',') &&
                    getline(dados_linha, livros[tamanho].nomeAutor, ',') &&
                    getline(dados_linha, numPaginas, ',') &&
                    getline(dados_linha, dataLancamento, ',') &&
                    getline(dados_linha, livros[tamanho].genero, ',') &&
                    getline(dados_linha, livros[tamanho].editora, ',')) {
    
                    // Verificar se as conversões são válidas
                    bool conversaoValida = true;
                    for (char c : numPaginas) {
                        if (!isdigit(c)) conversaoValida = false;
                    }
                    for (char c : dataLancamento) {
                        if (!isdigit(c)) conversaoValida = false;
                    }
    
                    if (conversaoValida) {
                        livros[tamanho].numPaginas = stoi(numPaginas);
                        livros[tamanho].dataLancamento = stoi(dataLancamento);
                        livros[tamanho].removido = false;
                        tamanho++;
    
                        // Redimensionar o vetor se necessário
                        if (tamanho >= capacidade) {
                            capacidade += 10; // Aumenta a capacidade em 10
                            Livros *novoVetor = new Livros[capacidade];
                            for (int i = 0; i < tamanho; i++) {
                                novoVetor[i] = livros[i];
                            }
                            delete[] livros;
                            livros = novoVetor;
                        }
                    } else {
                        cout << "Erro: Dados numéricos inválidos na linha: " << linha << endl;
                    }
                } else {
                    cout << "Erro ao ler linha do arquivo: " << linha << endl;
                }
            }
        }
    
        entrada.close();
    }
};

// Função para salvar os dados em um arquivo CSV
void salvarEmArquivoCSV(Livros *livros, int quantidade, string &diretorio) {
    //cout<<"Informe o diretorio para salvar o arquivo CSV: ";
    //cin>>diretorio;
    ofstream arquivo("Livros2.csv");
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    // Escreve o cabeçalho
    arquivo << "Nome,Autor,Número de Páginas,Data de Lançamento,Gênero,Editora\n";

    // Ordena os livros por nome antes de salvar (sem usar std::vector ou std::sort)
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = i + 1; j < quantidade; j++) {
            if (livros[i].nome > livros[j].nome) {
                swap(livros[i], livros[j]);
            }
        }
    }

    // Escreve os dados dos livros
    for (int i = 0; i < quantidade; i++) {
        if (!livros[i].removido) {
            arquivo << livros[i].nome << ","
                    << livros[i].nomeAutor << ","
                    << livros[i].numPaginas << ","
                    << livros[i].dataLancamento << ","
                    << livros[i].genero << ","
                    << livros[i].editora << "\n";
        }
    }

    arquivo.close();
    cout << "Dados salvos em " << diretorio << " com sucesso!\n";
}

// Função para ler do arquivo binário
void lerArquivoBinario(Livros *&livros, int &capacidade, int &quantidade) {
    ifstream arquivo("livros.bin", ios::binary);
    if (!arquivo) {
        cout << "Nao existem dados binarios previos" << endl << endl;
        return;
    } else {
        cout << "Dados binarios carregados com sucesso!" << endl << endl;
    }

    quantidade = 0;

    while (arquivo.peek() != EOF) {
        if (quantidade >= capacidade) {
            // Redimensionar o vetor, adicionando mais 10 posições
            capacidade += 10;
            Livros *novoVetor = new Livros[capacidade];
            for (int i = 0; i < quantidade; ++i) {
                novoVetor[i] = livros[i];
            }
            delete[] livros;
            livros = novoVetor;
        }

        // Ler os dados do arquivo
        Livros livro;

        int tamanhoNome;
        arquivo.read(reinterpret_cast<char *>(&tamanhoNome), sizeof(tamanhoNome));
        livro.nome.resize(tamanhoNome);
        arquivo.read(&livro.nome[0], tamanhoNome);

        int tamanhoNomeAutor;
        arquivo.read(reinterpret_cast<char *>(&tamanhoNomeAutor), sizeof(tamanhoNomeAutor));
        livro.nomeAutor.resize(tamanhoNomeAutor);
        arquivo.read(&livro.nomeAutor[0], tamanhoNomeAutor);

        arquivo.read(reinterpret_cast<char *>(&livro.numPaginas), sizeof(livro.numPaginas));
        arquivo.read(reinterpret_cast<char *>(&livro.dataLancamento), sizeof(livro.dataLancamento));

        int tamanhoGenero;
        arquivo.read(reinterpret_cast<char *>(&tamanhoGenero), sizeof(tamanhoGenero));
        livro.genero.resize(tamanhoGenero);
        arquivo.read(&livro.genero[0], tamanhoGenero);

        int tamanhoEditora;
        arquivo.read(reinterpret_cast<char *>(&tamanhoEditora), sizeof(tamanhoEditora));
        livro.editora.resize(tamanhoEditora);
        arquivo.read(&livro.editora[0], tamanhoEditora);

        arquivo.read(reinterpret_cast<char *>(&livro.removido), sizeof(livro.removido));

        // Adicionar o livro ao vetor
        livros[quantidade++] = livro;
    }

    arquivo.close();
}

void escreverEmArquivoBinario(Livros *livros, int quantidade) {
    ofstream arquivo("livros.bin", ios::binary | ios::trunc);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    for (int i = 0; i < quantidade; ++i) {
        if (!livros[i].removido) {
            const Livros &livro = livros[i];

            int tamanhoNome = livro.nome.size();
            arquivo.write(reinterpret_cast<const char *>(&tamanhoNome), sizeof(tamanhoNome));
            arquivo.write(livro.nome.c_str(), tamanhoNome);

            int tamanhoNomeAutor = livro.nomeAutor.size();
            arquivo.write(reinterpret_cast<const char *>(&tamanhoNomeAutor), sizeof(tamanhoNomeAutor));
            arquivo.write(livro.nomeAutor.c_str(), tamanhoNomeAutor);

            arquivo.write(reinterpret_cast<const char *>(&livro.numPaginas), sizeof(livro.numPaginas));
            arquivo.write(reinterpret_cast<const char *>(&livro.dataLancamento), sizeof(livro.dataLancamento));

            int tamanhoGenero = livro.genero.size();
            arquivo.write(reinterpret_cast<const char *>(&tamanhoGenero), sizeof(tamanhoGenero));
            arquivo.write(livro.genero.c_str(), tamanhoGenero);

            int tamanhoEditora = livro.editora.size();
            arquivo.write(reinterpret_cast<const char *>(&tamanhoEditora), sizeof(tamanhoEditora));
            arquivo.write(livro.editora.c_str(), tamanhoEditora);

            arquivo.write(reinterpret_cast<const char *>(&livro.removido), sizeof(livro.removido));
        }
    }

    arquivo.close();
}

// Funções auxiliares
void swap(Livros &a, Livros &b) {
    Livros temp = a;
    a = b;
    b = temp;
}

void quickSortPorNome(Livros *livros, int inicio, int fim) {
    if (inicio >= fim)
        return;

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
        while (livros[++i].nome < pivo)
            ;
        while (livros[--j].nome > pivo)
            ;
        if (i >= j)
            return;
        swap(livros[i], livros[j]);
    }
    swap(livros[i], livros[fim - 1]);

    quickSortPorNome(livros, inicio, i - 1);
    quickSortPorNome(livros, i + 1, fim);
}

void quickSortPorData(Livros *livros, int inicio, int fim) {
    if (inicio >= fim)
        return;

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
        while (livros[++i].dataLancamento < pivo)
            ;
        while (livros[--j].dataLancamento > pivo)
            ;
        if (i >= j)
            return;
        swap(livros[i], livros[j]);
    }
    swap(livros[i], livros[fim - 1]);

    quickSortPorData(livros, inicio, i - 1);
    quickSortPorData(livros, i + 1, fim);
}

void exibirLivros(Livros *livros, int inicio, int fim) {
    for (int i = inicio; i < fim; i++) {
        if (!livros[i].removido) {
            cout << "Indice " << i + 1 << "\n";
            cout << "Nome: " << livros[i].nome << "\n";
            cout << "Autor: " << livros[i].nomeAutor << "\n";
            cout << "Paginas: " << livros[i].numPaginas << "\n";
            cout << "Data de Lancamento: " << livros[i].dataLancamento << "\n";
            cout << "Genero: " << livros[i].genero << "\n";
            cout << "Editora: " << livros[i].editora << "\n\n";
        }
    }
}

void menu() {
    cout << "                          <CATALOGO DE LIVROS>                 " << endl
         << endl
         << endl;
    cout << "1. Inserir Livro\n";
    cout << "2. Remover Livro\n";
    cout << "3. Buscar Livro por Nome\n";
    cout << "4. Buscar Livro por Data de Lancamento\n";
    cout << "5. Exibir Livros\n";
    cout << "6. Salvar em binario\n";
    cout << "7. Importar de arquivo CSV\n";
    cout << "8. Salvar em arquivo CSV\n";
    cout << "0. Sair\n";
}

int buscaBinariaPorNome(Livros *livros, int inicio, int fim, const string &nome) {
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        // Comparação de strings (case-sensitive)
        if (livros[meio].nome == nome) {
            return meio; // Retorna o índice do livro encontrado
        } else if (livros[meio].nome > nome) {
            fim = meio - 1; // Busca na metade esquerda
        } else {
            inicio = meio + 1; // Busca na metade direita
        }
    }
    return -1; // Livro não encontrado
}

void buscaBinariaPorData(Livros *livros, int tamanho, int data) {
    int menor = 0;
    int maior = tamanho - 1;
    bool encontrado = false;

    while (menor <= maior) {
        int meio = menor + (maior - menor) / 2;

        if (livros[meio].dataLancamento == data) {
            encontrado = true;
            int esquerda = meio;
            int direita = meio;

            while (esquerda >= 0 && livros[esquerda].dataLancamento == data) {
                cout << endl;
                cout << "livro: " << livros[esquerda].nome << endl;
                cout << "Autor: " << livros[esquerda].nomeAutor << endl;
                cout << "Paginas: " << livros[esquerda].numPaginas << endl;
                cout << "Lancamento: " << livros[esquerda].dataLancamento << endl;
                cout << "Genero: " << livros[esquerda].genero << endl;
                cout << "Editora: " << livros[esquerda].editora << endl;
                esquerda--;
            }

            while (direita < tamanho && livros[direita].dataLancamento == data) {
                if (direita != meio) {
                    cout << endl;
                    cout << "livro: " << livros[direita].nome << endl;
                    cout << "Autor: " << livros[direita].nomeAutor << endl;
                    cout << "Paginas: " << livros[direita].numPaginas << endl;
                    cout << "Lancamento: " << livros[direita].dataLancamento << endl;
                    cout << "Genero: " << livros[direita].genero << endl;
                    cout << "Editora: " << livros[direita].editora << endl;
                }
                direita++;
            }
            return;
        }

        if (livros[meio].dataLancamento > data) {
            maior = meio - 1;
        } else {
            menor = meio + 1;
        }
    }

    if (!encontrado) {
        cout << "Ano nao encontrado!" << endl;
    }
}

void removerLivro(Livros *livros, int &tamanho) {
    if (tamanho == 0) {
        cout << "Nao ha livros para remover.\n";
        return;
    }

    int indice;
    cout << "Informe o indice do livro a ser removido: "<<"1 a "<<tamanho<<": ";
    cin >> indice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida. Por favor, insira um numero inteiro.\n";
    } else if (indice >= 0 && indice <= tamanho) {
        livros[indice - 1].removido = true;
        tamanho--;
        cout << "Livro marcado como removido.\n";
    } else {
        cout << "indice invalido.\n";
    }
}

void inserirLivro(Livros *&livros, int &tamanho, int &capacidade) {
    if (tamanho == capacidade) {
        capacidade += 50; // Aumenta a capacidade em 50
        Livros *novoVetor = new Livros[capacidade];
        for (int i = 0; i < tamanho; i++) {
            novoVetor[i] = livros[i];
        }
        delete[] livros;
        livros = novoVetor;
    }
    Livros novoLivro;
    cout << "Nome do Livro: ";
    getline(cin, novoLivro.nome);
    cout << "Nome do Autor: ";
    getline(cin, novoLivro.nomeAutor);
    cout << "Número de Paginas: ";
    while (!(cin >> novoLivro.numPaginas) or novoLivro.numPaginas <= 0) {
        cout << "Entrada invalida. Por favor, insira um numero valido de paginas: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Data de Lançamento: ";
    while (!(cin >> novoLivro.dataLancamento) or novoLivro.dataLancamento <= 0) {
        cout << "Entrada invalida. Por favor, insira uma data de lançamento valida: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Genero: ";
    cin.ignore();
    getline(cin, novoLivro.genero);
    cout << "Editora: ";
    getline(cin, novoLivro.editora);
    novoLivro.removido = false;

    livros[tamanho] = novoLivro;
    tamanho++;
}

void cases(Livros *&livros, int &tamanho, int &capacidade, int &opcao, string &diretorio) {
    do {
        menu();
        cout << endl << "Escolha uma opcao: " << endl;
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
                getline(cin, nome);

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

                quickSortPorData(livros, 0, tamanho - 1);
                buscaBinariaPorData(livros, tamanho, data);
                break;
            }
            case 5: {
                int inicio, fim;
                cout << "Informe o intervalo (1 a " << tamanho << "): ";
                cin >> inicio >> fim;
                exibirLivros(livros, inicio - 1, fim);
                break;
            }
            case 6:{
                escreverEmArquivoBinario(livros, tamanho);
                break;
            }
            case 7:{
                livros[0].entrada_arquivo(livros, tamanho, capacidade, diretorio);
                cout << "Dados importados com sucesso!" << endl << endl;
                break;
            }
            case 8:{
                salvarEmArquivoCSV(livros, tamanho, diretorio);
                break;
            }
            case 0:{
                cout << "Saindo...\n";
                delete[] livros;  // Liberar memória apenas uma vez
                livros = nullptr; // Boa prática para evitar dangling pointers
                break;
            }
            default:
                cout << "Opção inválida.\n";
        }
    } while (opcao != 0);

    // Remover a segunda liberação de memória
}


int main() {
    string diretorio = "";
    int capacidade = 40; // Capacidade inicial do vetor
    Livros *livros = new Livros[capacidade];
    int tamanho = 0, opcao = 0;

    lerArquivoBinario(livros, capacidade, tamanho);

    quickSortPorNome(livros, 0, tamanho - 1);
    cases(livros, tamanho, capacidade, opcao, diretorio);
    delete[] livros;
    return 0;
}
