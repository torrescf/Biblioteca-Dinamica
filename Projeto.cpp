
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Catalogo {
    int identificador;
    string nome;
    string nomeAutor;
    int numPaginas;
    int lancamento;
    string genero;
    string editora;

    void escreverEmArquivoBinario(ofstream& arquivo) const {
        arquivo.write(reinterpret_cast<const char*>(&identificador), sizeof(identificador));
        size_t tamanhoNome = nome.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoNome), sizeof(tamanhoNome));
        arquivo.write(nome.c_str(), static_cast<std::streamsize>(tamanhoNome));
        size_t tamanhoNomeAutor = nomeAutor.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoNomeAutor), sizeof(tamanhoNomeAutor));
        arquivo.write(nomeAutor.c_str(), static_cast<std::streamsize>(tamanhoNomeAutor));
        arquivo.write(reinterpret_cast<const char*>(&numPaginas), sizeof(numPaginas));
        arquivo.write(reinterpret_cast<const char*>(&lancamento), sizeof(lancamento));
        size_t tamanhoGenero = genero.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoGenero), sizeof(tamanhoGenero));
        arquivo.write(genero.c_str(), static_cast<std::streamsize>(tamanhoGenero));
        size_t tamanhoeditora = editora.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoeditora), sizeof(tamanhoeditora));
        arquivo.write(editora.c_str(), static_cast<std::streamsize>(tamanhoeditora));
    }

    void lerDoArquivoBinario(ifstream& arquivo) {
        arquivo.read(reinterpret_cast<char*>(&identificador), sizeof(identificador));
        size_t tamanhoNome;
        arquivo.read(reinterpret_cast<char*>(&tamanhoNome), sizeof(tamanhoNome));
        std::vector<char> bufferNome(tamanhoNome);
        arquivo.read(bufferNome.data(), static_cast<std::streamsize>(tamanhoNome));
        nome.assign(bufferNome.begin(), bufferNome.end());
        size_t tamanhoNomeAutor;
        arquivo.read(reinterpret_cast<char*>(&tamanhoNomeAutor), sizeof(tamanhoNomeAutor));
        std::vector<char> bufferNomeAutor(tamanhoNomeAutor);
        arquivo.read(bufferNomeAutor.data(), static_cast<std::streamsize>(tamanhoNomeAutor));
        nomeAutor.assign(bufferNomeAutor.begin(), bufferNomeAutor.end());
        arquivo.read(reinterpret_cast<char*>(&numPaginas), sizeof(numPaginas));
        arquivo.read(reinterpret_cast<char*>(&lancamento), sizeof(lancamento));
        size_t tamanhoGenero;
        arquivo.read(reinterpret_cast<char*>(&tamanhoGenero), sizeof(tamanhoGenero));
        std::vector<char> bufferGenero(tamanhoGenero);
        arquivo.read(bufferGenero.data(), static_cast<std::streamsize>(tamanhoGenero));
        genero.assign(bufferGenero.begin(), bufferGenero.end());
        //genero.resize(tamanhoGenero);
        size_t tamanhoeditora;
        arquivo.read(reinterpret_cast<char*>(&tamanhoeditora), sizeof(tamanhoeditora));
        std::vector<char> bufferEditora(tamanhoeditora);
        arquivo.read(bufferEditora.data(), static_cast<std::streamsize>(tamanhoeditora));
        editora.assign(bufferEditora.begin(), bufferEditora.end());
        editora.resize(tamanhoeditora);
    }
};

int buscaBinariaNome(Catalogo vet[], int tamanho, string nome) {
    int menor = 0;
    int maior = tamanho - 1;

    while (menor <= maior) {
        int media = menor + (maior - menor) / 2;
        if (vet[media].nome == nome)
            return media;
        if (vet[media].nome < nome)
            menor = media + 1;
        else
            maior = media - 1;
    }
    return -1;
}

void buscaBinariaAno(Catalogo vet[], int tamanho, int anoBusca) {
    int menor = 0;
    int maior = tamanho - 1;
    bool encontrado = false;

    while (menor <= maior) {
        int media = menor + (maior - menor) / 2;
        if (vet[media].lancamento == anoBusca) {
            encontrado = true;
            int esquerda = media;
            int direita = media;

            while (esquerda >= 0 && vet[esquerda].lancamento == anoBusca) {
                cout << endl;
                cout << "livro: " << vet[esquerda].nome << "; ";
                cout << "Autor: " << vet[esquerda].nomeAutor << "; ";
                cout << "Paginas: " << vet[esquerda].numPaginas << "; ";
                cout << "Lancamento: " << vet[esquerda].lancamento << "; ";
                cout << "Genero: " << vet[esquerda].genero << "; ";
                cout << "Editora: " << vet[esquerda].editora << "; ";
                esquerda--;
            }

            while (direita < tamanho && vet[direita].lancamento == anoBusca) {
                if (direita != media) {
                    cout << endl;
                    cout << "livro: " << vet[direita].nome << "; ";
                    cout << "Autor: " << vet[direita].nomeAutor << "; ";
                    cout << "Paginas: " << vet[direita].numPaginas << "; ";
                    cout << "Lancamento: " << vet[direita].lancamento << "; ";
                    cout << "Genero: " << vet[direita].genero << "; ";
                    cout << "Editora: " << vet[direita].editora << "; ";
                }
                direita++;
            }
            return;
        }

        if (vet[media].lancamento > anoBusca) {
            maior = media - 1;
        } else {
            menor = media + 1;
        }
    }

    if (!encontrado) {
        cout << "Ano nao encontrado!" << endl;
    }
}

void trocar(Catalogo &a, Catalogo &b) {
    Catalogo aux = a;
    a = b;
    b = aux;
}

int particao(Catalogo vet[], int menor, int maior) {
    string aux = vet[maior].nome;
    string pivot = vet[maior].nome;
    int i = menor - 1;
    for (int j = menor; j <= maior - 1; j++) {
        if (vet[j].nome < pivot) {
            i++;
            trocar(vet[i], vet[j]);
        }
    }
    trocar(vet[i + 1], vet[maior]);
}

void quickSortNome(Catalogo vet[], int menor, int maior) {
    if (menor < maior) {
        int pivo = particao(vet, menor, maior);
        quickSortNome(vet, menor, pivo - 1);
        quickSortNome(vet, pivo + 1, maior);
    }
}

int particaoPorAno(Catalogo vet[], int menor, int maior) {
    int pivo = vet[maior].lancamento;
    int i = menor - 1;

    for (int j = menor; j <= maior - 1; j++) {
        if (vet[j].lancamento > pivo) {
            i++;
            std::swap(vet[i], vet[j]);
        }
    }
    std::swap(vet[i + 1], vet[maior]);
    return (i + 1);
}

int particaoPorIdentificador(Catalogo Livro[], int menor, int maior) {
    int pivo = Livro[maior].identificador;
    int i = menor - 1;

    for (int j = menor; j <= maior - 1; j++) {
        if (Livro[j].identificador > pivo) {
            i++;
            trocar(Livro[i], Livro[j]);
        }
    }
    trocar(Livro[i + 1], Livro[maior]);
    return (i + 1);
}

void quickSortAno(Catalogo vet[], int menor, int maior) {
    if (menor < maior) {
        int pivo = particaoPorAno(vet, menor, maior);
        quickSortAno(vet, menor, pivo - 1);
        quickSortAno(vet, pivo + 1, maior);
    }
}

void quicksortidentificador(Catalogo Livro[], int menor, int maior) {
    if (menor < maior) {
        int pivo = particaoPorIdentificador(Livro, menor, maior);
        quicksortidentificador(Livro, menor, pivo - 1);
        quicksortidentificador(Livro, pivo + 1, maior);
    }
}

int main() {
    int tamanho = 40;
    Catalogo *livro = new Catalogo[tamanho];

    ifstream entrada("Livros.csv");
    if (!entrada) {
        cout << "ERRO ao Abrir o Arquivo!" << endl;
        return -1;
    } else {
        if (entrada) {
            string linha;
            getline(entrada, linha);
        }
        int contador = 0;
        char delimitador = ';';
        string lixo;

        while (entrada && contador < tamanho) {
            entrada >> livro[contador].identificador;
            if (entrada.fail()) {
                cout << "Erro ao ler identificador!" << endl;
            }
            getline(entrada, lixo);
            getline(entrada, lixo, delimitador);
            getline(entrada, livro[contador].nome, delimitador);
            getline(entrada, livro[contador].nomeAutor, delimitador);
            entrada >> livro[contador].numPaginas;
            getline(entrada, lixo, delimitador);
            entrada >> livro[contador].lancamento;
            getline(entrada, lixo, delimitador);
            getline(entrada, livro[contador].genero, delimitador);
            getline(entrada, livro[contador].editora, delimitador);
            contador++;
        }

        entrada.close();

        if (contador == tamanho) {
            int tamanhoNovo = tamanho + 5;
            Catalogo *vetorAux = new Catalogo[tamanhoNovo];
            for (int i = 0; i < tamanho; i++) {
                vetorAux[i] = livro[i];
            }
            delete[] livro;
            livro = vetorAux;
            tamanho = tamanhoNovo;
        }

        tamanho = contador - 1;

        quickSortNome(livro, 0, tamanho - 1);

        int resposta = 0;
        while (resposta != 5) {
            cout << endl << "                                           CATALOGO DE LIVROS                                              " << endl;
            cout << endl << "O que deseja fazer, usuario?" << endl;
            cout << "1) Mostrar um Intervalo de livros" << endl;
            cout << "2) Buscar livros por algum filtro" << endl;
            cout << "3) Sobrescrever/Escrever dados" << endl;
            cout << "4) Remover Dados" << endl;
            cout << "5) Encerrar o Programa" << endl;
            cout << "Resposta (1 ate 5): ";
            cin >> resposta;
            if (resposta == 1) {
                cout << endl << "Deseja ver todo o catalogo?" << endl;
                cout << "1) Todo o catalogo" << endl;
                cout << "2) Selecionar o intervalo" << endl;
                int resposta1;
                cin >> resposta1;

                if (resposta1 == 1) {
                    cout << "Deseja ver em ordem alfabetica, genero ou ultimos lancamentos?" << endl;
                    cout << "1) Alfabetica" << endl;
                    cout << "2) Ultimos lancamentos" << endl;
                    cout << "3) Genero" << endl;
                    int resposta2;
                    cin >> resposta2;
                    if (resposta2 == 1) {
                        quickSortNome(livro, 0, tamanho - 1);
                        for (int i = 0; i < tamanho; i++) {
                            cout << "livro: " << livro[i].nome << "; ";
                            cout << "Autor: " << livro[i].nomeAutor << "; ";
                            cout << "Paginas: " << livro[i].numPaginas << "; ";
                            cout << "Lancamento: " << livro[i].lancamento << "; ";
                            cout << "Genero: " << livro[i].genero << "; ";
                            cout << "editora: " << livro[i].editora << endl;
                        }
                    } else if (resposta2 == 2) {
                        quickSortAno(livro, 0, tamanho - 1);
                        for (int i = 0; i < tamanho; i++) {
                            cout << "livro: " << livro[i].nome << "; ";
                            cout << "Autor: " << livro[i].nomeAutor << "; ";
                            cout << "Paginas: " << livro[i].numPaginas << "; ";
                            cout << "Lancamento: " << livro[i].lancamento << "; ";
                            cout << "Genero: " << livro[i].genero << "; ";
                            cout << "Editora: " << livro[i].editora << "; ";
                            cout << endl;
                        }
                    } else if (resposta2 == 3) {
                        cout << "Qual genero?" << endl;
                        cout << "1) Misterio" << endl;
                        cout << "2) Drama" << endl;
                        cout << "3) Romance" << endl;
                        cout << "4) Drama" << endl;
                        cout << "5) Ficcao cientifica" << endl;
                        cout << "6) Aventura" << endl;
                        cout << "7) Fantasia" << endl;
                        int numeroGenero;
                        cin >> numeroGenero;
                        string genero;
                        switch (numeroGenero) {
                            case 1: genero = "Misterio"; break;
                            case 2: genero = "Drama"; break;
                            case 3: genero = "Romance"; break;
                            case 4: genero = "Drama"; break;
                            case 5: genero = "Ficcao cientifica"; break;
                            case 6: genero = "Aventura"; break;
                            case 7: genero = "Fantasia"; break;
                            default: cout << "Genero invalido!" << endl; continue;
                        }

                        for (int i = 0; i < tamanho; i++) {
                            if (livro[i].genero == genero) {
                                cout << "livro: " << livro[i].nome << "; ";
                                cout << "Autor: " << livro[i].nomeAutor << "; ";
                                cout << "Paginas: " << livro[i].numPaginas << "; ";
                                cout << "Lancamento: " << livro[i].lancamento << "; ";
                                cout << "Genero: " << livro[i].genero << "; ";
                                cout << "editora: " << livro[i].editora << endl;
                            }
                        }
                    } else {
                        cout << "RESPOSTA INVALIDA, retornando ao comeco do codigo!" << endl;
                    }
                } else if (resposta1 == 2) {
                    cout << "Insira o intervalo desejado (2 valores): " << endl;
                    cout << "Valor Minimo = 0 e Valor Maximo= " << contador << endl;
                    int intervaloInicial, intervaloFinal;
                    cin >> intervaloInicial >> intervaloFinal;
                    if (intervaloInicial != intervaloFinal && intervaloInicial >= 0 && intervaloInicial < contador && intervaloFinal > intervaloInicial && intervaloFinal < contador) {
                        cout << "Deseja ver em ordem Alfabetica ou pelos Ultimos Lancamentos?" << endl << "1) Alfabetica" << endl << "2) Data de Lancamento" << endl;
                        int resposta2;
                        cin >> resposta2;
                        if (resposta2 == 1) {
                            quickSortNome(livro, 0, tamanho - 1);
                            for (int i = intervaloInicial - 1; i < intervaloFinal; i++) {
                                cout << endl;
                                cout << "livro: " << livro[i].nome << "; ";
                                cout << "Autor: " << livro[i].nomeAutor << "; ";
                                cout << "Paginas: " << livro[i].numPaginas << "; ";
                                cout << "Lancamento: " << livro[i].lancamento << "; ";
                                cout << "Genero: " << livro[i].genero << "; ";
                                cout << "Editora: " << livro[i].editora << "; ";
                                cout << endl;
                            }
                        } else if (resposta2 == 2) {
                            quickSortAno(livro, 0, tamanho - 1);
                            for (int i = intervaloInicial - 1; i < intervaloFinal; i++) {
                                cout << endl;
                                cout << "livro: " << livro[i].nome << "; ";
                                cout << "Autor: " << livro[i].nomeAutor << "; ";
                                cout << "Paginas: " << livro[i].numPaginas << "; ";
                                cout << "Lancamento: " << livro[i].lancamento << "; ";
                                cout << "Genero: " << livro[i].genero << "; ";
                                cout << "Editora: " << livro[i].editora << "; ";
                                cout << endl;
                            }
                        } else {
                            cout << "RESPOSTA INVALIDA, retornando ao comeco do codigo!" << endl;
                        }
                    } else if (intervaloInicial == intervaloFinal) {
                        cout << endl;
                        cout << "livro: " << livro[intervaloInicial].nome << "; ";
                        cout << "Autor: " << livro[intervaloInicial].nomeAutor << "; ";
                        cout << "Paginas: " << livro[intervaloInicial].numPaginas << "; ";
                        cout << "Lancamento: " << livro[intervaloInicial].lancamento << "; ";
                        cout << "Genero: " << livro[intervaloInicial].genero << "; ";
                        cout << "Editora: " << livro[intervaloInicial].editora << "; ";
                        cout << endl;
                    } else {
                        cout << "Intervalo invalido, retornando ao comeco do codigo!" << endl;
                    }
                } else {
                    cout << "Valor inserido INVALIDO!, retornando ao comeco do codigo!" << endl;
                }
            } else if (resposta == 2) {
                cout << "Deseja fazer a buscar por qual tipo de filtro? " << endl;
                cout << "1) Nome " << endl << "2) Ano de Lancamento" << endl << "3) Genero" << endl;
                int resposta2 = 0;
                cout << "Resposta(1 ate 3): ";
                cin >> resposta2;
                if (resposta2 == 1) {
                    cout << "Insira o nome do livro desejado: " << endl << "livro: ";
					string nomelivro;
					cin.ignore();
					getline(cin,nomelivro);
					int poslivroDesejado;
					poslivroDesejado = buscaBinariaNome(livro, tamanho, nomelivro);
					if(poslivroDesejado!=-1){
						cout << endl;
					    cout << "livro: " << livro[poslivroDesejado].nome << " ";
					    cout << "Autor: " << livro[poslivroDesejado].nomeAutor << "; ";
					    cout << "Paginas: " << livro[poslivroDesejado].numPaginas << "; ";
					    cout << "Lancamento: " << livro[poslivroDesejado].lancamento << "; ";
					    cout << "Genero: " << livro[poslivroDesejado].genero << "; ";
					    cout << "Editora" << livro[poslivroDesejado].editora << endl << " ";
					    cout << endl;
					}else{
						cout << "Nome nao encontrado no catalogo!, retornando ao comeco do codigo!" << endl;
				    }
				}else if(resposta2==2){ // filtrar por ano de lançamento
					quickSortAno(livro,0,tamanho-1);
					cout << "Insira o ano de lancamento que desejada: " << endl;
					int anoBusca;
					cin>>anoBusca;
					buscaBinariaAno(livro, tamanho, anoBusca);
					}else if (resposta2 == 3) { // filtrar por genero
                cout << "Qual genero?" << endl;
                cout << "1) Misterio" << endl;
                cout << "2) Drama" << endl;
                cout << "3) Romance" << endl;
                cout << "4) Drama" << endl;
                cout << "5) Ficcao cientifica" << endl;
                cout << "6) Aventura" << endl;
                cout << "7) Fantasia" << endl;
                int numeroGenero;
                cin >> numeroGenero;
                string genero;
                switch (numeroGenero) {
                    case 1: genero = "Misterio"; break;
                    case 2: genero = "Drama"; break;
                    case 3: genero = "Romance"; break;
                    case 4: genero = "Drama"; break;
                    case 5: genero = "Ficcao cientifica"; break;
                    case 6: genero = "Aventura"; break;
                    case 7: genero = "Fantasia"; break;
                    default: cout << "Genero invalido!" << endl; continue;
                }

                for (int i = 0; i < tamanho; i++) {
                    if (livro[i].genero == genero) {
                        cout << "livro: " << livro[i].nome << "; ";
                        cout << "Autor: " << livro[i].nomeAutor << "; ";
                        cout << "Paginas: " << livro[i].numPaginas << "; ";
                        cout << "Lancamento: " << livro[i].lancamento << "; ";
                        cout << "Genero: " << livro[i].genero << "; ";
                        cout << "editora: " << livro[i].editora << endl;
                    }
                }
            } else {
                cout << "Valor inserido INVALIDO! Retornando ao comeco do codigo!" << endl;
            }
				}else if(resposta==3){ // Sobrescrever/Escrever dados
					 cout << "1)Escrever dados" << endl << "2)Sobrescrevrer dados " << endl;
					 int resposta3=0;
					 cout << "Resposta (1 ou 2): ";
					 cin >> resposta3;
					     if(resposta3==1){ // deseja escrever novos dados no final do catálogo
						 cout << "Quantos novos dados deseja escrever?" << endl;
						 int respostaE=0;
						 cin >> respostaE;
						 int tamanhoAntigo = tamanho; // para fins de preencher as novas posições é necessário saber o tamanho antigo do catálogo
						 int tamanhoNovo = tamanho+respostaE;
						 
						 Catalogo *vetorAux3= new Catalogo[tamanhoNovo];
						 //Preenchendo o vetorAux3 com os valores do catálogo
						 for(int i=0; i<tamanho; i++){
						 vetorAux3[i]=livro[i];
						 }
						 delete[] livro;
						 livro = vetorAux3;
						 tamanho = tamanhoNovo;
			             int contadorE =tamanhoAntigo+1;
						 if(respostaE==1){
							 cout << "Insira os dados do livro: " << endl;
							 }else{
			                  cout << "Insira os dados dos " << respostaE << ": "<< endl;
							  }
						 for(int i=tamanhoAntigo; i<tamanho ; i++){
							 cin.ignore();
							 cout << endl<< "Nome: ";
							 getline(cin,livro[i].nome);
							 cout << endl << "Nome do Autor: ";
							 cin >> livro[i].nomeAutor;
							 cout << endl << "Numero de Paginas: ";
							 cin >> livro[i].numPaginas;
							 cout << endl << "Ano de Lancamento: "; 
							 cin >> livro[i].lancamento;
							 cin.ignore();
							 cout << endl << "Genero Principal: ";
							 getline(cin,livro[i].genero);
							 cout << endl << "editora: ";
							 getline(cin,livro[i].editora);
							 contadorE++;
					     }
						 cout << "Deseja salvar as alteracoes feitas?" << endl;
						 cout << "1)Sim" << endl << "2)Nao" << endl;
						 int respostaE1=0;
						 cout << "Resposta (1 ou 2): ";
						 cin >> respostaE1;
						 
						 if(respostaE1==1){ //deseja salvar as alterações
						 quicksortidentificador(livro, 0, tamanho - 1);
						   ofstream saida ("teste.txt");
				           int contadorE2=0;// contador para saber quando deverá parar de escrever dados na saída
				           saida << "# identificador Nome Número_Temporadas Número_Episódios Ano_Lançamento Ano_Finalização Gênero_Principal editora" << endl;
				           //saida << "OBS:(lancamento=0 sera quando o livro ainda nao estiver finalizado)" << endl;
				           while(contadorE2<tamanho){
							     saida << livro[contadorE2].identificador << " ";
								 saida << livro[contadorE2].nome << " ";
							     saida << livro[contadorE2].nomeAutor << " ";
								 saida << livro[contadorE2].numPaginas << " ";
							     saida << livro[contadorE2].lancamento << " ";
								 saida << livro[contadorE2].genero	<< " ";									    
							     saida << livro[contadorE2].editora << " ";
								 saida << endl;
								 contadorE2++;
						  }
							 
						  cout << "Catalogo atualizado com sucesso acima!" << endl; 
						  }else if(respostaE1==2){ // não deseja salvar as alterações = redimensionar o vetor para o tamanho antigo, excluíndo os novos dados
							      tamanhoNovo= tamanho-respostaE;
								  Catalogo *vetorAux4= new Catalogo[tamanhoNovo];
								  for(int i=0; i<tamanhoNovo; i++){
								  vetorAux4[i]=livro[i];
								  }
								  delete[] livro;
								  livro = vetorAux4;
								  tamanho = tamanhoNovo;
							      cout << "Resposta nao salva, catalogo retornando ao antigo!" << endl;
						}
						
					 }else if(resposta3==2){ // usuário deseja sobrescrever dados já existentes no catálogo
						 cout << endl << "Qual identificador do catalogo deseja sobrescrever? " << endl;
						 int identificadorDesejada=0;
						 cout << "Resposta: (1 ate " << tamanho-2 << ")" << endl; 
						 cin >> identificadorDesejada;
						 cout << "Insira os dados livro: " << endl;
						 //declarando as variáveis que vão armazanar os dados escritos pelo usuário para sobrescrever os já existentes
						 string nomeAux;
						 char nomeAutorAux;
						 int numPaginasAux;
						 int lancamentoAux;
						 string generoAux;
						 string editoraAux;
						 cout << "Nome: ";
						 cin.ignore();
						 getline(cin,nomeAux);
						 cout << endl << "Nome do Autor: ";
						 cin >> nomeAutorAux;
						 cout << endl << "Numero de Paginas: ";
						 cin >> numPaginasAux;
						 cout << endl << "Ano de Lancamento: ";
						 cin >> lancamentoAux;
						 cout << endl << "Genero Principal: ";
						 cin.ignore();
						 getline(cin,generoAux);
						  cout << endl << "editora: ";
						 cin.ignore();
						 getline(cin,editoraAux);
						 int respostaS=0;
						 cout << endl << "Deseja salvar as alteracoes?" << endl;
						 cout << "1)Sim" << endl << "2)Nao" << endl;
						 cout << "Resposta(1 ou 2): ";
						 cin >> respostaS; // resposta Sobrescrever
						 if(respostaS==1){ //deseja salvar as alteracoes
						 for(int i=0; i<tamanho; i++){
							 if(livro[i].identificador==identificadorDesejada){
								 livro[i].nome=nomeAux;
								 livro[i].nomeAutor=nomeAutorAux;
								 livro[i].numPaginas=numPaginasAux;
								 livro[i].lancamento=lancamentoAux;
								 livro[i].genero=generoAux;
								 livro[i].editora=editoraAux;
								 int contadorS=0;
								 quicksortidentificador(livro, 0, tamanho - 1);
								 ofstream saida ("teste.txt");
								 saida << "# identificador Nome Número_Temporadas Número_Episódios Ano_Lançamento Ano_Finalização Gênero_Principal editora" << endl;
								 //saida << "OBS:(lancamento=0 sera quando o livro ainda nao estiver finalizado)" << endl;
								 while(contadorS<tamanho-2){
									 saida << livro[contadorS].identificador << " ";
									 saida << livro[contadorS].nome << " ";
							     	 saida << livro[contadorS].nomeAutor << " ";
								 	 saida << livro[contadorS].numPaginas << " ";
							     	 saida << livro[contadorS].lancamento << " ";
    ofstream saida("Livros.csv");
							     	 saida << livro[contadorS].editora << " ";
								 	 saida << endl;
								 	 contadorS++;
									 }
								 
								 }
						 }
						 cout << "Valores Atualizados com Sucesso!"	 << endl;
					     }else if(respostaS==2){ //nao deseja salvar as alteracoes
							      cout << "Resposta nao salva, catalogo retornando ao antigo!" << endl;
						  }
						 
					 }
				 
				}	 
				else if(resposta==4){ // Remover Dados
					    cout << "Qual a posicao do catalogo que deseja remover?" << endl;
					    cout << "Resposta (1 ate " << tamanho << "): ";
					    int respostaRemover=0;
					    cin >> respostaRemover;
		
					    cout << "Deseja salvar as alteracoes?"<< endl;
					    cout << "1)Sim " << endl << "2)Nao" << endl;
					    cout << "Resposta(1 ou 2):";
int respostaRemover2 = 0;
cin >> respostaRemover2;
if (respostaRemover2 == 1) {
    int novoTamanho = tamanho - 1; // novo tamanho do catalogo removendo um livro dele
    Catalogo *auxRemover = new Catalogo[novoTamanho];
    int contadorRemover = 0;

    for (int i = 0; i < tamanho; i++) {
        if (i != respostaRemover - 1) {
            auxRemover[contadorRemover] = livro[i];
            contadorRemover++;
        }
    }

    for (int i = respostaRemover - 1; i < novoTamanho; i++) {
        auxRemover[i].identificador -= 1;
    }

    delete[] livro;
    tamanho = novoTamanho;
    livro = auxRemover;
    quicksortidentificador(livro, 0, tamanho - 1);
    ofstream saida("teste.txt");
    int contadorR2 = 0;
    saida << "# identificador Nome Numero_Temporadas Numero_Episódios Ano_Lançamento Ano_Finalizacao Genero_Principal editora" << endl;
    // saida << "OBS:(lancamento=0 sera quando o livro ainda nao estiver finalizado)" << endl;
    char aux1 = ';';
    char aux2 = '"';
						   while(contadorR2<tamanho){
				  			     saida << livro[contadorR2].identificador << aux1 << aux2;
				  			     saida << livro[contadorR2].nome << aux2 << aux1;
				  			     saida << livro[contadorR2].nomeAutor << aux1;
				  			     saida << livro[contadorR2].numPaginas << aux1;
				  			     saida << livro[contadorR2].lancamento << aux1 << aux2;
				  			     saida << livro[contadorR2].genero << aux2 << aux1 << aux2;									    
				  			     saida << livro[contadorR2].editora << aux2 << aux1;
				  			     saida << endl;
				  			     contadorR2++;
						  }
						  
						   cout << "Catalogo atualizado com sucesso, retornando ao comeco do codigo!" << endl;
		    
					   }else if(respostaRemover2==2){
				                cout << "Alteracoes nao salvas, retornando ao comeco do codigo!" << endl;
					    }else{
					         cout << "Resposta invalida, retornando ao comeco do codigo!" << endl;
					     }
						
			    }
}if(resposta==5){
	cout << endl << "Programa Encerrado!" << endl;
	}else if(resposta>5){
		     cout << "RESPOSTA INVALIDA, retornando ao comeco do codigo!" << endl;
	 }
	}
 return 0;
}

