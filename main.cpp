#include <iostream>
#include <vector>
#include "matrizadj.h"
using namespace std;

const vector<string> explode(const string& s, const char& c);
void open_file(MatrizAdj grafo);
MatrizAdj cria_matriz();
void verifica_subgrafo(MatrizAdj grafo, int vertice_inicial, int nivel);
//vertice_nivel cria_vetor_fecho_transitivo(MatrizAdj grafo);

int main() {

    MatrizAdj grafo = cria_matriz();

    int interseccao[grafo.getVertices()];
    int nivel_subgrafo = 1;
    int cont = grafo.getVertices();
    int subgrafos[grafo.getVertices()];

    //grafo.caminho_profundidade();
    //grafo.caminho_largura();

    grafo.fecho_transitivo_direto(0,true);
    grafo.fecho_transitivo_direto(0,false);
    grafo.print_matriz();

    //vertice_nivel *vet_direto  = grafo.getVet_nivel_direto();
    //vertice_nivel *vet_inverso = grafo.getVet_nivel_inverso();

    // Monta vetor de instersecção
    for(int i=0; i<grafo.getVertices();i++){
        subgrafos[i] = 0; //inicialização do vetor subgrafos

        if(grafo.getVet_transitivo_direto().at(i).nivel != -1 && grafo.getVet_transitivo_inverso().at(i).nivel != -1){
            interseccao[i] = 1;
            subgrafos[i] = nivel_subgrafo; //Interseções iniciais formam o primeiro subgrafo
            cont--;                        // Decrementa a qtd de vértices restantes para serem verificados
        }else{
            interseccao[i] = 0;
        }
    }
    //Verifica se o grafo é conexo
    for(int i=0; i<grafo.getVertices();i++){
        if(interseccao[i] == 0){
            cout<<endl<<endl;
            cout<<"Grafo não conexo"<<endl<<endl;
            break;
        }else if(i == (grafo.getVertices())-1){
            cout<<endl<<endl;
            cout<<"Grafo Conexo"<<endl<<endl;
        }
    }

     // Define niveis para vetor subgrafo -> niveis iguais representam um subgrafo
    while(cont > 0){
        for(int i=0;i<grafo.getVertices();i++){
            if(subgrafos[i] == 0){
                nivel_subgrafo++;       //novo subgrafo será formado
                grafo.fecho_transitivo_direto(i,true);
                grafo.fecho_transitivo_direto(i,false);

                for(int i=0;i<grafo.getVertices();i++){
                    if(grafo.getVet_transitivo_direto().at(i).nivel != -1 && grafo.getVet_transitivo_inverso().at(i).nivel != -1){
                        subgrafos[i] = nivel_subgrafo;
                        cont--;
                    }
                }
            }
        }

    }

     int inicial = 1; // Primeiro nível de subgrafo
     int cont2 = grafo.getVertices();

     while(cont2 > 0){
         cout<<"Subgrafo"<<inicial<<endl;
         for(int i=0;i<grafo.getVertices();i++){
             if(subgrafos[i] == inicial){
                cont2--;
                cout<< "\t" << (i+1);
             }
         }
         inicial++;
         cout<<endl<<endl;
     }

    return 0;
}

const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s){
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);
    return v;
}

void open_file(MatrizAdj grafo){
    ifstream leitura;
    char linha[20];
    vector<string> read;
    string aux,caminho;
    int aux1,aux2;

    cout<<"Informe o caminho do arquivo"<<endl;
    cout<<"->> ";
    cin>>caminho;

    leitura.open("C:/Users/Guilherme/Documents/Univali/7 Periodo/Grafos/Busca_larg_prof/Busca_larg_prof/Grafos/m2.txt");
    if(!leitura.is_open( ))
    {
    cout<<"Não foi possível abrir arquivo!\n";
    leitura.clear( ); //reseta o objeto leitura, para limpar memória do sistema}
    }
    while (leitura.getline(linha,20)) {
        cout << linha <<"\n";
        read = explode(linha,',');
        aux = read.front(); aux1 = atoi(aux.c_str());
        aux = read.back(); aux2 = atoi(aux.c_str());
        cout << aux1 << " : " << aux2 << endl;
        grafo.add_vertice(aux1,aux2);
        if(!grafo.getDirigida())
            grafo.add_vertice(aux2,aux1);
    }
    leitura.close();
}

/*void verifica_subgrafo(MatrizAdj grafo, int vertice_inicial, int nivel){

       grafo.fecho_transitivo_direto(vertice_inicial,true);  //FTD
       grafo.fecho_transitivo_direto(vertice_inicial,false); //FTR

       for(int i=0;i<grafo.getVertices();i++){
           if(grafo.getVet_transitivo_direto().at(i).nivel != -1 && grafo.getVet_transitivo_inverso().at(i).nivel != -1){
               grafo.getSubgrafos().at(i) = nivel;
           }
       }
}*/

// Inicialização vetor de vertice_nivel

MatrizAdj cria_matriz(){
    MatrizAdj aux;
    int n_vert;
    cout<<"Quantidade de vertices: ";
    cin>>n_vert;

    char op;
    cout<<"A matriz e dirigida?[s/n]: ";
    cin>>op;


    bool **matriz = new bool* [n_vert];
    for (int i = 0; i < n_vert; i++){
        matriz[i] = new bool [n_vert];
        for(int j = 0; j < n_vert; j++){
            matriz[i][j] = 0;
        }
    }
    aux.setMatriz(matriz);
    aux.setVertices(n_vert);
    //grafo.print_matriz();
    if(op == 's')
        aux.setDirigida(true);
    else
        aux.setDirigida(false);

    int op_abre;
    cout<<"Abrir matriz em arquivo[1] ou informar valores[2]:";
    cin>>op_abre;

    if(op_abre == 2){
        int cont=1;
        string leitura;
        vector<string> v;
        int pos[2];
        do{
            cout<<"Ligacao [p para encerrar] "<<cont<<": ";
            cin>>leitura;
            if(leitura == "p") break;

            v = explode(leitura,',');
            leitura=v.front(); pos[0]=atoi(leitura.c_str());
            leitura=v.back(); pos[1]=atoi(leitura.c_str());

            aux.add_vertice(pos[0],pos[1]);
            if(op == 'n') aux.add_vertice(pos[1],pos[0]);

            cont++;
        }while(true);
    }else{
        open_file(aux);
    }

    return aux;
}

