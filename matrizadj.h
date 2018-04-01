#ifndef MATRIZADJ_H
#define MATRIZADJ_H

#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <fstream>

using namespace std;

struct vertice_nivel
{
    int nivel;
    bool verificado;
};

class MatrizAdj
{
private:
    int vertices;
    bool dirigida;
    bool **matriz;
    vector<vertice_nivel> vet_transitivo_direto;
    vector<vertice_nivel> vet_transitivo_inverso;

public:
    MatrizAdj();
    int getVertices() const;
    void setVertices(int value);
    bool getDirigida() const;
    void setDirigida(bool value);
    bool **getMatriz() const;
    void setMatriz(bool **value);

    vector<vertice_nivel> getVet_transitivo_direto() const;
    void setVet_transitivo_direto(const vector<vertice_nivel> &value);
    vector<vertice_nivel> getVet_transitivo_inverso() const;
    void setVet_transitivo_inverso(const vector<vertice_nivel> &value);

    void add_vertice(int origem, int destino);
    void caminho_profundidade(int inicio);
    void caminho_largura(int inicio);
    void fecho_transitivo(int vertice_inicial, bool direto);
    void determina_subgrafo();
    void print_matriz();

};

#endif // MATRIZADJ_H
