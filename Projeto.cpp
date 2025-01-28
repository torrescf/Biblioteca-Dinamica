#include <iostream>
#include <fstream>
using namespace std;

struct Catalogo{
	int identificador;
	string nome;
	string nomeAutor;
	int numPaginas;
	int lancamento;
	string genero;
	string editora;

	    // Função para escrever o catalogo em um arquivo binário 
    void escreverEmArquivoBinario(ofstream& arquivo) const {
        arquivo.write(reinterpret_cast<const char*>(&identificador), sizeof(identificador));
        
        size_t tamanhoNome = nome.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoNome), sizeof(tamanhoNome));
        arquivo.write(nome.c_str(), tamanhoNome);
        
        size_t tamanhoNomeAutor = nomeAutor.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoNomeAutor), sizeof(tamanhoNomeAutor));
        arquivo.write(nomeAutor.c_str(), tamanhoNomeAutor);
       
        arquivo.write(reinterpret_cast<const char*>(&numPaginas), sizeof(numPaginas));
        arquivo.write(reinterpret_cast<const char*>(&lancamento), sizeof(lancamento));
        
        size_t tamanhoGenero = genero.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoGenero), sizeof(tamanhoGenero));
        arquivo.write(genero.c_str(), tamanhoGenero);
        
        size_t tamanhoeditora = editora.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoeditora), sizeof(tamanhoeditora));
        arquivo.write(editora.c_str(), tamanhoeditora);
    }

    // Função para ler o catalogo de um arquivo binário
    void lerDoArquivoBinario(ifstream& arquivo) {
        arquivo.read(reinterpret_cast<char*>(&identificador), sizeof(identificador));
        size_t tamanhoNome;
        arquivo.read(reinterpret_cast<char*>(&tamanhoNome), sizeof(tamanhoNome));
        nome.resize(tamanhoNome);
        arquivo.read(&nome[0], tamanhoNome);
        size_t tamanhoNomeAutor;
        arquivo.read(reinterpret_cast<char*>(&tamanhoNomeAutor), sizeof(tamanhoNomeAutor));
        nomeAutor.resize(tamanhoNomeAutor);
        arquivo.read(&nomeAutor[0], tamanhoNomeAutor);
        arquivo.read(reinterpret_cast<char*>(&numPaginas), sizeof(numPaginas));
        arquivo.read(reinterpret_cast<char*>(&lancamento), sizeof(lancamento));
        size_t tamanhoGenero;
        arquivo.read(reinterpret_cast<char*>(&tamanhoGenero), sizeof(tamanhoGenero));
        genero.resize(tamanhoGenero);
        arquivo.read(&genero[0], tamanhoGenero);
        size_t tamanhoeditora;
        arquivo.read(reinterpret_cast<char*>(&tamanhoeditora), sizeof(tamanhoeditora));
        editora.resize(tamanhoeditora);
        arquivo.read(&editora[0], tamanhoeditora);
    }
};

	// Função para busca binária pelo nome do livro
int buscaBinariaNome(Catalogo vet[], int tamanho, string nome) {
    int menor = 0;
    int maior = tamanho - 1;

    while (menor <= maior) {
        int media = menor + (maior - menor) / 2;

        // Verifica se o nome do meio é igual ao nome buscado
        if (vet[media].nome == nome)
            return media;

        // Se o nome no meio for menor, ignora a metade esquerda
        if (vet[media].nome < nome)
            menor = media + 1;

        // Se o nome no meio for maior, ignora a metade direita
        else
            maior = media - 1;
    }

    // Retorna -1 se o nome não for encontrado
    return -1;
}

// Função para busca binária pelo ano de lançamento do livro
void buscaBinariaAno(Catalogo vet[], int tamanho, int anoBusca) {
    int menor = 0;
    int maior = tamanho - 1;
    int cont = 0;

    while (menor <= maior) {
        int media = menor + (maior - menor) / 2;

        // Verifica se o ano de lançamento no meio é igual ao ano buscado
        if (vet[media].lancamento == anoBusca) {
            // Encontra todos os livros com o mesmo ano de lançamento
            int esquerda = media;
            int direita = media;

            // Expande para a esquerda
            while (esquerda >= 0 && vet[esquerda].lancamento == anoBusca) {
                cont++;
                cout << endl;
				cout << "livro: " << vet[esquerda].nome << "; ";
				cout << "Autor: " << vet[esquerda].nomeAutor << "; ";
				cout << "Paginas: " << vet[esquerda].numPaginas << "; ";
				cout << "Lancamento: " << vet[esquerda].lancamento << "; ";
				cout << "Genero: " << vet[esquerda].genero << "; ";
				cout << "Editora " << vet[esquerda].editora << "; ";
                esquerda--;
            }

            // Expande para a direita
            while (direita < tamanho && vet[direita].lancamento == anoBusca) {
                if (direita != media) {  // Evita duplicar a impressão do elemento central
                    cont++;
                    cout << endl;
				cout << "livro: " << vet[direita].nome << "; ";
				cout << "Autor: " << vet[direita].nomeAutor << "; ";
				cout << "Paginas: " << vet[direita].numPaginas << "; ";
				cout << "Lancamento: " << vet[direita].lancamento << "; ";
				cout << "Genero: " << vet[direita].genero << "; ";
				cout << "Editora" << vet[direita].editora << "; ";
                }
                direita++;
            }
            return;  // Sai da função após encontrar e exibir todos os livros com o ano buscado
        }

        // Se o ano no meio for maior, ignora a metade direita (já que é decrescente)
        if (vet[media].numPaginas > anoBusca) {
            menor = media + 1;
        }
        // Se o ano no meio for menor, ignora a metade esquerda
        else {
            maior = media - 1;
        }
    }

    // Se o contador cont for 0, o ano não foi encontrado
    if (cont == 0) {
        cout << "Ano nao encontrado!" << endl;
    }
}

// Função para trocar dois elementos
void trocar(Catalogo &a, Catalogo &b) {
    Catalogo aux = a;
    a = b;
    b = aux;
}

// Partição do Quick Sort
int particao(Catalogo vet[], int menor, int maior) {
    string aux = vet[maior].nome;
    int i = menor - 1;
    for (int j = menor; j <= maior - 1; j++) {
        if (vet[j].nome < aux) {
            i++;
            trocar(vet[i], vet[j]);
        }
    }
    trocar(vet[i + 1], vet[maior]);
    return (i + 1);
}

// Função Quick Sort
void quickSortNome(Catalogo vet[], int menor, int maior) {
    if (menor < maior) {
        int pivo = particao(vet, menor, maior);

        quickSortNome(vet, menor, pivo - 1);
        quickSortNome(vet, pivo + 1, maior);
    }
}

// Partição do Quick Sort para ordenar pelo ano de lançamento (decrescente)
int particaoPornumPaginas(Catalogo vet[], int menor, int maior) {
    int pivo = vet[maior].numPaginas;  
    int i = menor - 1;

    for (int j = menor; j <= maior - 1; j++) {
        if (vet[j].numPaginas > pivo) { 
            i++;
            trocar(vet[i], vet[j]);
        }
    }
    trocar(vet[i + 1], vet[maior]);
    return (i + 1);
}

// Função Quick Sort para ordenar pelo ano de lançamento
void quickSortAno(Catalogo vet[], int menor, int maior) {
    if (menor < maior) {
        int pivo = particaoPornumPaginas(vet, menor, maior);
        quickSortAno(vet, menor, pivo - 1);
        quickSortAno(vet, pivo + 1, maior);
    }
}
int main () {
	int tamanho=40;
	Catalogo *livro= new Catalogo[tamanho];
	
	
	ifstream entrada ("Livros.csv");
	//Preenchendo o "vetor livro" com os dados fornecidos pelo arquivo "Livros - Copia.csv"

	if (!entrada){
        cout << "ERRO ao Abrir o Arquivo!" << endl;
		return -1;

    } else {
	 if (entrada) {
        string linha;
        getline(entrada, linha);// Lê e descarta a primeira linha (cabeçalho)
	}
	    int contador=0;
	    char delimitador = ',';
	    string lixo;
	   
	    while(entrada && contador < tamanho){
			  
			  entrada >> livro[contador].identificador;
			  if (entrada.fail()) {
 			  	 cout << "Erro ao ler identificador!" << endl;
				}
			  getline(entrada,lixo);

			  getline(entrada , lixo , delimitador);
			  
		      getline(entrada,livro[contador].nome, delimitador);

			  getline(entrada, livro[contador].nomeAutor, delimitador);
		      
		      entrada >> livro[contador].numPaginas;
		      
		      getline(entrada , lixo , delimitador);
		      entrada >> livro[contador].lancamento;
		      
		      getline(entrada , lixo , delimitador);

		      getline(entrada , livro[contador].genero , delimitador);

		      getline(entrada , livro[contador].editora , delimitador);
		      contador++;
		}

		entrada.close();
		      
		  //Se o contador chegar ao tamanho do vetor livro, será necessário redimensionar o vetor livro
		      if(contador==tamanho){
		         int tamanhoNovo = tamanho+5;
			     Catalogo *vetorAux= new Catalogo[tamanhoNovo];
		         //Preenchendo o vetorAux com os valores do vetor livro
		         for(int i=0; i<tamanho; i++){
				     vetorAux[i]=livro[i];
			     }
			         //direcionar o vetor livro para o vetorAux redimensionado
			         delete[] livro;
			         livro = vetorAux;
			         tamanho = tamanhoNovo;
		      }
	     
	tamanho= contador-1; // correção do tamanho
	

	quickSortNome(livro, 0, tamanho - 1);
	
	int resposta=0;
	while (resposta != 5) {
    cout << endl << "                                           CATALOGO DE LIVROS                                              " << endl;
    cout << endl << "O que deseja fazer, usuario?" << endl;
    cout << "1) Mostrar um Intervalo de livros" << endl;
    cout << "2) Buscar livros por algum filtro" << endl;
    cout << "3) Sobrescrever/Escrever dados" << endl;
    cout << "4) Remover Dados" << endl;
    cout << "5) Encerrar o Programa" << endl;
    cout << "Resposta (1 ate 5): ";	     
		cin >> resposta; //resposta sobre o que sera feito pelo programa
if (resposta == 1) { // Mostrar um Intervalo
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
				for (int i = 0; i < tamanho-1; i++) {
                cout << "livro: " << livro[i].nome << "; ";
                cout << "Autor: " << livro[i].nomeAutor << "; ";
                cout << "Paginas: " << livro[i].numPaginas << "; ";
                cout << "Lancamento: " << livro[i].lancamento << "; ";
                cout << "Genero: " << livro[i].genero << "; ";
                cout << "editora: " << livro[i].editora << endl;
            }} else if (resposta2 == 2) {
                quickSortAno(livro, 0, tamanho - 1);
					for(int i=0; i<tamanho-2 ; i++){
						cout << endl;
						cout << "livro: " << livro[i].nome << "; ";
						cout << "Autor: " << livro[i].nomeAutor << "; ";
						cout << "Paginas: " << livro[i].numPaginas << "; ";
						cout << "Lancamento: " << livro[i].lancamento << "; ";
						cout << "Genero: " << livro[i].genero << "; ";
						cout << "Editora" << livro[i].editora << "; ";
						cout << endl;
					}
				}else if (resposta2 == 3) {
                cout << "Qual genero?" << endl;
                cout << "1) Fantasia" << endl;
                cout << "2) Distopia" << endl;
                cout << "3) Romance" << endl;
                cout << "4) Infantojuvenil" << endl;
                cout << "5) Aventura" << endl;
                cout << "6) Biografia" << endl;
                cout << "7) Horror" << endl;
                cout << "8) Romance psicologico" << endl;
                cout << "9) Misterio" << endl;
                cout << "10) Drama" << endl;
                cout << "11) Ficcao cientifica" << endl;
                cout << "12) Filosofia" << endl;
                cout << "13) Ficcao contemporanea" << endl;
                cout << "14) Ciencia" << endl;
                cout << "15) Natureza" << endl;
                cout << "16) Filosofia politica" << endl;
                cout << "17) Fabula" << endl;
                cout << "18) Psicologico" << endl;
                cout << "19) Thriller" << endl;
                cout << "20) Suspense" << endl;
                cout << "21) Literatura classica" << endl;
                cout << "22) Historico" << endl;
                int numeroGenero;
                cin >> numeroGenero;
                string genero;
                switch (numeroGenero) {
                    case 1: genero = "Fantasia"; break;
                    case 2: genero = "Distopia"; break;
                    case 3: genero = "Romance"; break;
                    case 4: genero = "Infantojuvenil"; break;
                    case 5: genero = "Aventura"; break;
                    case 6: genero = "Biografia"; break;
                    case 7: genero = "Horror"; break;
                    case 8: genero = "Romance psicologico"; break;
                    case 9: genero = "Misterio"; break;
                    case 10: genero = "Drama"; break;
                    case 11: genero = "Ficcao cientifica"; break;
                    case 12: genero = "Filosofia"; break;
                    case 13: genero = "Ficcao contemporanea"; break;
                    case 14: genero = "Ciencia"; break;
                    case 15: genero = "Natureza"; break;
                    case 16: genero = "Filosofia politica"; break;
                    case 17: genero = "Fabula"; break;
                    case 18: genero = "Psicologico"; break;
                    case 19: genero = "Thriller"; break;
                    case 20: genero = "Suspense"; break;
                    case 21: genero = "Literatura classica"; break;
                    case 22: genero = "Historico"; break;
                    default: cout << "Genero invalido!" << endl;break;
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
				}else{
					cout << "RESPOSTA INVALIDA, retornando ao comeco do codigo!" << endl;
				}
		}else if(resposta1==2){ //mostrar um certo intervalo informado pelo usuário
			cout << "Insira o intervalo desejado (2 valores): " << endl;
			cout << "Valor Minimo = 0 e Valor Maximo= " << contador << endl;
			int intervaloInicial,intervaloFinal; //inserindo os valores do intervalo desejado
			cin >> intervaloInicial >> intervaloFinal;
			if(intervaloInicial!=intervaloFinal and intervaloInicial>=0 and intervaloInicial<contador and intervaloFinal>intervaloInicial and intervaloFinal<contador){ // limitar os valores possiveis de serem inseridos
			cout << "Deseja ver em ordem Alfabetica ou pelos Ultimos Lancamentos?" << endl << "1) Alfabetica" << endl << "2) Data de Lancamento" << endl;
				int resposta2;
				cin >> resposta2;
					if (resposta2==1){
					quickSortNome(livro, 0, tamanho - 1);
					for(int i=intervaloInicial-1; i<intervaloFinal ;i++){
						cout << endl;
						cout << "livro: " << livro[i].nome << "; ";
						cout << "Autor: " << livro[i].nomeAutor << "; ";
						cout << "Paginas: " << livro[i].numPaginas << "; ";
						cout << "Lancamento: " << livro[i].lancamento << "; ";
						cout << "Genero: " << livro[i].genero << "; ";
						cout << "Editora" << livro[i].editora << "; ";
						cout << endl;
						 }
					 }else if (resposta2==2){
					quickSortAno(livro, 0, tamanho - 1);
						for(int i=intervaloInicial-1; i<intervaloFinal ;i++){
						cout << endl;
						cout << "livro: " << livro[i].nome << "; ";
						cout << "Autor: " << livro[i].nomeAutor << "; ";
						cout << "Paginas: " << livro[i].numPaginas << "; ";
						cout << "Lancamento: " << livro[i].lancamento << "; ";
						cout << "Genero: " << livro[i].genero << "; ";
						cout << "Editora" << livro[i].editora << "; ";
						cout << endl;
						 }
					 }else{
					cout << "RESPOSTA INVALIDA, retornando ao comeco do codigo!" << endl;
					}
				 }else if(intervaloInicial==intervaloFinal){ // se houver apenas 1 item que deseja ver do catálogo
						cout << endl;
						cout << "livro: " << livro[intervaloInicial].nome << "; ";
						cout << "Autor: " << livro[intervaloInicial].nomeAutor << "; ";
						cout << "Paginas: " << livro[intervaloInicial].numPaginas << "; ";
						cout << "Lancamento: " << livro[intervaloInicial].lancamento << "; ";
						cout << "Genero: " << livro[intervaloInicial].genero << "; ";
						cout << "Editora" << livro[intervaloInicial].editora << "; ";
						cout << endl;
					 }else{
						 cout << "Intervalo invalido, retornando ao comeco do codigo!" << endl;
						 }
			 }else{
				 cout << "Valor inserido INVALIDO!, retornando ao comeco do codigo!" << endl;
				 }
			 }else if(resposta==2){ //filtar os livros 
				 cout << "Deseja fazer a buscar por qual tipo de filtro? " << endl;
				 cout << "1) Nome " << endl << "2) Ano de Lancamento" << endl;
				 int resposta2=0;
				 cout << "Resposta(1 ate 2): " ;
				 cin >> resposta2;
				 if(resposta2==1){ // filtrar por nome
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
					cout << "Insira o ano de lancamento que deseja: " << endl;
					int anoBusca = 0;
                    bool nao_existe = false;
					cin>>anoBusca;
					for(int i=0; i<tamanho; i++){
                       if(anoBusca==livro[i].lancamento){
                             cout << endl << "livro: " << livro[i].nome << "; ";
                             cout << "Autor: " << livro[i].nomeAutor << "; ";
                             cout << "Paginas: " << livro[i].numPaginas << "; ";
                             cout << "Lancamento: " << livro[i].lancamento << "; ";
                             cout << "Genero: " << livro[i].genero << "; ";
                             cout << "Editora: " << livro[i].editora << "; ";
                       }else{ nao_existe = true;}
                     
                    }if(nao_existe == true){
                            cout << "Ano nao encontrado no catalogo!, retornando ao comeco do codigo!" << endl;
                       }
				}else{
					cout<< "Valor inserido INVALIDO! Retornando ao comeco do codigo!" << endl;
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
						 
			             Catalogo *vetorAux2= new Catalogo[tamanhoNovo];
		                 //Preenchendo o vetorAux2 com os valores do catálogo
		                 for(int i=0; i<tamanho; i++){
				         vetorAux2[i]=livro[i];
			             }
			             delete[] livro;
			             livro = vetorAux2;
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
						   ofstream saida ("Livros - Copia.csv");
				           int contadorE2=0;// contador para saber quando deverá parar de escrever dados na saída
				           saida << "# identificador Nome Número_Temporadas Número_Episódios Ano_Lançamento Ano_Finalização Gênero_Principal editora" << endl;
				           saida << "OBS:(lancamento=0 sera quando o livro ainda nao estiver finalizado)" << endl;
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
							      Catalogo *vetorAux2= new Catalogo[tamanhoNovo];
		                          for(int i=0; i<tamanhoNovo; i++){
				                  vetorAux2[i]=livro[i];
			                      }
			                      delete[] livro;
			                      livro = vetorAux2;
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
								 ofstream saida ("Livros - Copia.csv");
								 saida << "# identificador Nome Número_Temporadas Número_Episódios Ano_Lançamento Ano_Finalização Gênero_Principal editora" << endl;
								 saida << "OBS:(lancamento=0 sera quando o livro ainda nao estiver finalizado)" << endl;
								 while(contadorS<tamanho-2){
									 saida << livro[contadorS].identificador << " ";
									 saida << livro[contadorS].nome << " ";
							     	 saida << livro[contadorS].nomeAutor << " ";
								 	 saida << livro[contadorS].numPaginas << " ";
							     	 saida << livro[contadorS].lancamento << " ";
								 	 saida << livro[contadorS].genero	<< " ";									    
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
					    int respostaRemover2=0;
					    cin >> respostaRemover2;
					    if(respostaRemover2==1){
						   int novoTamanho=tamanho-1; // novo tamanho do catalogo removendo um livro dele
		    			   Catalogo *auxRemover = new Catalogo[novoTamanho];
		    			   int contadorRemover=0;
		    			   for(int i=0; i<novoTamanho ;i++){
			    			   if(livro[i].identificador != respostaRemover){
				   			   auxRemover[contadorRemover]=livro[i];
				   			   contadorRemover++;
			    			   }
		    			   }
		    			   for(int i=respostaRemover-1; i<novoTamanho; i++){
			   			    auxRemover[i].identificador -=1;
		    			   }
		    			   delete[] livro;
		    			   tamanho = novoTamanho; 
		    			   livro = auxRemover;
		    			   ofstream saida ("Livros - Copia.csv");
						   int contadorR2=0;
						   saida << "# identificador Nome Número_Temporadas Número_Episódios Ano_Lançamento Ano_Finalização Gênero_Principal editora" << endl;
						   saida << "OBS:(lancamento=0 sera quando o livro ainda nao estiver finalizado)" << endl;
						   char aux1 = ';';
						   char aux2 = '"';
						   while(contadorR2<tamanho-1){
				  			     saida << livro[contadorR2].identificador << aux1 << aux2;
				  			     saida << livro[contadorR2].nome << aux2 << aux1;
				  			     saida << livro[contadorR2].nomeAutor << aux1;
				  			     saida << livro[contadorR2].numPaginas << aux1;
				  			     saida << livro[contadorR2].lancamento << aux1 << aux2;
				  			     saida << livro[contadorR2].genero << aux2 << aux1 << aux2;									    
				  			     saida << livro[contadorR2].editora << aux2;
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

