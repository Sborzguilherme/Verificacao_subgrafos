#include "matrizadj.h"
vector<vertice_nivel> MatrizAdj::getVet_transitivo_direto() const
{
    return vet_transitivo_direto;
}

void MatrizAdj::setVet_transitivo_direto(const vector<vertice_nivel> &value)
{
    vet_transitivo_direto = value;
}

vector<vertice_nivel> MatrizAdj::getVet_transitivo_inverso() const
{
    return vet_transitivo_inverso;
}

void MatrizAdj::setVet_transitivo_inverso(const vector<vertice_nivel> &value)
{
    vet_transitivo_inverso = value;
}

MatrizAdj::MatrizAdj()
{

}

int MatrizAdj::getVertices() const
{
    return vertices;
}

void MatrizAdj::setVertices(int value)
{
    vertices = value;
}

bool MatrizAdj::getDirigida() const
{
    return dirigida;
}

void MatrizAdj::setDirigida(bool value)
{
    dirigida = value;
}

bool **MatrizAdj::getMatriz() const
{
    return matriz;
}

void MatrizAdj::setMatriz(bool **value)
{
    matriz = value;
}

void MatrizAdj::add_vertice(int origem, int destino)
{
    //cout << "test";
    matriz[origem - 1][destino - 1] = 1;
}

void MatrizAdj::caminho_profundidade()
{
    stack<int> pilha;
    list <int> hist_visita;
    bool visitado[vertices]={};
    bool fim = false;
    int atual = 0;                  // 1º vertice
    do{
        pilha.push(atual);
        while(!pilha.empty()){
            atual = pilha.top();
            //cout<< "Vertice" << atual << endl;
            pilha.pop();
            //cout<< "Pilha" << pilha.size() << endl;
            if(!visitado[atual]){
                visitado[atual] = true;
                hist_visita.push_back(atual);
                for(int i = 0; i < vertices; i++){
                    if(this->matriz[atual][i]){ pilha.push(i); /*cout<< "v add" << i << endl;*/}
                }
            }
        }
        fim = true;
        for(int i = 0; i < vertices; i++){
            if(!visitado[i]){
                fim = false;
                atual = i;
                break;
            }
        }
    }while(!fim);

    //cout<< endl <<"Vertice Atual: " << atual+1 << endl;
    cout<< endl;
    cout<< "Vetor de visitados: ";
    for(int i=0; i<vertices; i++) cout << "\t" << visitado[i];
    cout<< endl;
    cout<<"Historico de Visitas:   ";
    for(auto v : hist_visita) cout << v+1 << "\t" ;
}

void MatrizAdj::caminho_largura()
{
    queue<int> fila;
    bool visitado[vertices]={};
    list <int> hist_visita;
    bool fim = false;
    int atual = 0;
    do{
        fila.push(atual);
        while(!fila.empty()){
            atual = fila.front();
            fila.pop();

            if(!visitado[atual]){
                visitado[atual] = true;
                hist_visita.push_back(atual);
                for(int i = 0; i < vertices; i++){
                    if(this->matriz[atual][i]) fila.push(i);
                }
            }
        }

        fim = true;
        for(int i = 0; i < vertices; i++){
            if(!visitado[i]){
                fim = false;
                atual = i;
                break;
            }
        }
    }while(!fim);

    cout<<"BUSCA LARGURA"<<endl<<endl;
    //cout<< endl <<"Vertice Atual: " << atual+1 << endl;
    cout<< "Vetor de visitados: ";
    for(int i=0; i<vertices; i++) cout << "\t" << visitado[i];
    cout<<endl;
    cout<<"Historico de Visitas:   ";
    for(auto v : hist_visita) cout << v+1 << "\t" ;
}

/*vertice_nivel MatrizAdj::cria_vetor_fecho_transitivo(){

    vertice_nivel vet[vertices];
    for(int i=0;i<vertices;i++){
        vet[i].nivel = 0;
        vet[i].verficado = false;
    }
    return *vet;
}*/

void MatrizAdj::fecho_transitivo_direto(int vertice_inicial, bool direto){

// Vetor de structs
   vector<vertice_nivel> vetor_niveis;
    int nivel_atual = 0;
    bool verifica = true;

//// Inicialização do vetor
    for(int i=0;i<vertices;i++){
        vertice_nivel aux;
        aux.nivel = -1;
        aux.verficado = false;
        vetor_niveis.push_back(aux);
    }

// Valor passado como parâmetro é o vértice inicial (recebe nível 0)
    vetor_niveis.at(vertice_inicial).nivel = 0;
    vetor_niveis.at(vertice_inicial).verficado = true;
    nivel_atual++;

    do{
        if(direto == true){
            for(int i=0;i<vertices;i++){
                if(this->matriz[vertice_inicial][i] == 1 && vetor_niveis.at(i).nivel == -1){
                    vetor_niveis.at(i).nivel = nivel_atual;
                }
            }
        }else{
            for(int i=0;i<vertices;i++){
                if(this->matriz[i][vertice_inicial] == 1 && vetor_niveis.at(i).nivel == -1){
                    vetor_niveis.at(i).nivel = nivel_atual;
                }
            }
        }
        verifica = false;

 // Verificação do nível atual;
       for(int i=0;i<vertices;i++){
           if(vetor_niveis.at(i).verficado == false){
               if((vetor_niveis.at(i).nivel < nivel_atual) && (vetor_niveis.at(i).nivel != -1)){
                   nivel_atual = vetor_niveis.at(i).nivel;
               }
           }
       }

 //Seleção do próximo vertice a ser verificado

        for(int i=0;i<vertices;i++){
            vertice_nivel atual = vetor_niveis.at(i);

            if((atual.nivel == nivel_atual) && (atual.verficado == false)){
                vertice_inicial = i;
                vetor_niveis.at(i).verficado = true;
                nivel_atual++;
                verifica = true;
                break; // FOR EXIT
            }
        }
    }while(verifica);

    if(direto){
        cout<<"FECHO TRANSITIVO DIRETO"<<endl;
        cout<< "Vetor de Niveis: ";
        for(int i=0;i<this->vertices;i++){
            setVet_transitivo_direto(vetor_niveis);
            cout << "\t" << this->getVet_transitivo_direto()[i].nivel;
        }
    }else{
        cout<<endl;
        cout<<"FECHO TRANSITIVO INDIRETO"<<endl;
        cout<< "Vetor de Niveis: ";

        for(int i=0; i<this->vertices; i++){
            setVet_transitivo_inverso(vetor_niveis);
            cout << "\t" << vet_transitivo_inverso[i].nivel;
        }
    cout<<endl;
    }
}
void MatrizAdj::print_matriz()
{
    for (int i = 0; i < vertices; i++){
        cout<< endl;
        for(int j = 0; j < vertices; j++){
            cout<<" " << matriz[i][j];
        }
    }
}
