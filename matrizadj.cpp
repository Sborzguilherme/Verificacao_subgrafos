#include "matrizadj.h"

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

void MatrizAdj::add_vertice(int origem, int destino)
{
    matriz[origem - 1][destino - 1] = 1;
}

void MatrizAdj::caminho_profundidade(int inicio)
{
    stack<int> pilha;
    list <int> hist_visita;                // Salva a ordem de vértices visitados
    bool visitado[vertices]={};            // Salva quais vértices foram visitados
    bool fim = false;
    int atual = inicio-1;                  // 1º vertice
    do{
        pilha.push(atual);                 //Empilha o vértice inicial (e vértice inicial desconexo)
        while(!pilha.empty()){
            atual = pilha.top();           // Vértice desempilhado é verificado
            pilha.pop();
            if(!visitado[atual]){
                visitado[atual] = true;                         // Marca o vértice como visitado
                hist_visita.push_back(atual);                   // Adiciona o vértice ao vetor de visitas
                for(int i = 0; i < vertices; i++){
                    if(this->matriz[atual][i]){ pilha.push(i);} // Empilha os adjascentes do vértice verificado
                }
            }
        }
        fim = true;
        for(int i = 0; i < vertices; i++){
            if(!visitado[i]){                   // Verifica se algum vértice não foi visitado
                fim = false;
                atual = i;                      // Vertice ainda não visitado é o novo vertice atual
                break;
            }
        }
    }while(!fim);

    cout<< endl << "PROFUNDIDADE" << endl;
    cout<< "Vetor de visitados: ";
    for(int i=0; i<vertices; i++) cout << "\t" << visitado[i];
    cout<< endl;
    cout<< "Historico de Visitas:   ";
    for(auto v : hist_visita) cout << v+1 << "\t" ;
}

void MatrizAdj::caminho_largura(int inicio)
{
    queue<int> fila;
    bool visitado[vertices]={};
    list <int> hist_visita;
    bool fim = false;
    int atual = inicio-1;
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

    cout<< endl << "LARGURA" << endl;
    cout<< "Vetor de visitados: ";
    for(int i=0; i<vertices; i++) cout << "\t" << visitado[i];
    cout<<endl;
    cout<< "Historico de Visitas:   ";
    for(auto v : hist_visita) cout << v+1 << "\t" ;
}

void MatrizAdj::fecho_transitivo(int vertice_inicial, bool direto)
{
    //Vetor de structs
    vector<vertice_nivel> vetor_niveis;         // Struct que da aos vértices duas propriedades : nivel e verificado
    int nivel_atual = 0;
    bool verifica = true;

    //Inicialização do vetor com um tipo vertice_nivel
    for(int i=0;i<vertices;i++){
        vertice_nivel aux;
        aux.nivel = -1;
        aux.verificado = false;
        vetor_niveis.push_back(aux);
    }

    //Valor passado como parâmetro é o vértice inicial (recebe nível 0)
    vetor_niveis.at(vertice_inicial).nivel = 0;
    vetor_niveis.at(vertice_inicial).verificado = true;
    nivel_atual++;                                      // nivel_atual = nivel do vertice atual+1
    do{
        if(direto == true){                             // Fecho Transitivo Direto
            for(int i=0;i<vertices;i++){
                if(this->matriz[vertice_inicial][i] == 1 && vetor_niveis.at(i).nivel == -1){
                    vetor_niveis.at(i).nivel = nivel_atual; // Marca os adjascentes do vértice verificado com o nivel atual
                }
            }
        }else{                                          // Fecho Transitivo Inverso
            for(int i=0;i<vertices;i++){
                if(this->matriz[i][vertice_inicial] == 1 && vetor_niveis.at(i).nivel == -1){
                    vetor_niveis.at(i).nivel = nivel_atual;
                }
            }
        }
        verifica = false;
        //Verificação do nível atual
        //(Garante que o nivel atual só seja incrementado quando todos os vértices cujo nivel = nivel atual ja tenham sido verificados)
        for(int i=0;i<vertices;i++){
            if(vetor_niveis.at(i).verificado == false){
                if((vetor_niveis.at(i).nivel < nivel_atual) && (vetor_niveis.at(i).nivel != -1)){
                    nivel_atual = vetor_niveis.at(i).nivel;
                }
            }
        }
        //Seleção do próximo vertice a ser verificado
        for(int i=0;i<vertices;i++){
            vertice_nivel atual = vetor_niveis.at(i);
            if((atual.nivel == nivel_atual) && (atual.verificado == false)){ // Próximo vértice verificado é aquele que ainda não foi verificado e possui nivel = nivel_atual
                vertice_inicial = i;
                //cout<<endl<<i<<endl;
                vetor_niveis.at(i).verificado = true;
                nivel_atual++;      // Nivel atual é incrementado para atualização dos niveis dos vértices adjascentes ao vértice sendo atualmente verificado
                verifica = true;
                break; // FOR EXIT
            }
        }
    }while(verifica);

    if(direto){
        cout<< endl << " FECHO TRANSITIVO DIRETO" << endl;
        cout<< "  -> Vetor de Niveis: ";
        for(int i=0;i<vertices;i++){
            setVet_transitivo_direto(vetor_niveis);
            cout << "\t" << this->getVet_transitivo_direto()[i].nivel;
        }
    }else{
        cout<< endl << endl << " FECHO TRANSITIVO INVERSO" << endl;
        cout<< "  -> Vetor de Niveis: ";
        for(int i=0; i<this->vertices; i++){
            setVet_transitivo_inverso(vetor_niveis);
            cout << "\t" << vet_transitivo_inverso[i].nivel;
        }
        cout<<endl;
    }
}

void MatrizAdj::determina_subgrafo()
{
    int interseccao[this->vertices];
    int nivel_subgrafo = 1;
    int cont = this->vertices;
    int subgrafos[this->vertices];

    //Chama fecho transitivo direto e inverso do primeiro vértice do grafo
    fecho_transitivo(0,true);
    fecho_transitivo(0,false);

    //Monta vetor de instersecção
    for(int i=0; i<this->vertices; i++){
        subgrafos[i] = 0; //inicialização do vetor subgrafos
        if(this->vet_transitivo_direto.at(i).nivel != -1 && this->vet_transitivo_inverso.at(i).nivel != -1){ // Verifica os vértices retornados pela função de fecho transitivo (direto e inverso)
            interseccao[i] = 1;
            subgrafos[i] = nivel_subgrafo; //Interseções iniciais formam o primeiro subgrafo
            cont--;                        // Decrementa a qtd de vértices restantes para serem verificados
        }else{
            interseccao[i] = 0;
        }
    }
    //Verifica se o grafo é conexo
    for(int i=0; i<this->vertices; i++){
        if(interseccao[i] == 0){            // Se algum vértice não for retornado sabe-se que o grafo não é conexo
            cout<<endl<<endl;
            cout<<" ->> Grafo não conexo"<<endl<<endl;
            break;
        }else if(i == (this->vertices)-1){
            cout<<endl<<endl;
            cout<<" ->> Grafo Conexo"<<endl<<endl;
        }
    }
    //Define niveis para vetor subgrafo -> niveis iguais representam um subgrafo
    while(cont > 0){
        for(int i=0;i<this->vertices;i++){
            if(subgrafos[i] == 0){
                nivel_subgrafo++;       //novo subgrafo será formado
                // Funções de fecho transitivo são chamadas para um dos vértices não retornados
                fecho_transitivo(i,true);
                fecho_transitivo(i,false);

                for(int i=0;i<this->vertices;i++){
                    if(this->vet_transitivo_direto.at(i).nivel != -1 && this->vet_transitivo_inverso.at(i).nivel != -1){
                        subgrafos[i] = nivel_subgrafo;
                        cont--;
                    }
                }
            }
        }
    }
    int inicial = 1; //Primeiro nível de subgrafo
    int cont2 = this->vertices;
    while(cont2 > 0){
        cout<< endl << " -> Subgrafo " << inicial << endl;
        for(int i=0;i<this->vertices;i++){
            if(subgrafos[i] == inicial){
                cont2--;
                cout<< "\t" << (i+1);
            }
        }
        inicial++;
        cout<< endl << endl;
    }
}

void MatrizAdj::print_matriz()
{
    for(int i = 0; i < vertices; i++){
        cout<< endl;
        for(int j = 0; j < vertices; j++){
            cout<<" " << matriz[i][j];
        }
    }
}
