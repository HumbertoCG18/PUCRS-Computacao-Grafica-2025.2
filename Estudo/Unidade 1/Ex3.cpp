// É necessário incluir a biblioteca vector e a definição de Ponto
#include <vector>
#include "Ponto.h"

class Poligono {
public:
    // Um polígono é definido por uma lista (vetor) de vértices
    std::vector<Ponto> vertices;

    // Um método para adicionar um vértice à lista do polígono
    void adicionaVertice(Ponto p) {
        vertices.push_back(p);
    }
};

// Como usar para criar o nosso triângulo:
// 1. Primeiro, definimos os vértices que já conhecemos
Ponto vertice_A(10.0, 10.0);
Ponto vertice_B(50.0, 10.0);
Ponto vertice_C(30.0, 40.0);

// 2. Criamos uma instância vazia da classe Poligono
Poligono meuTriangulo;

// 3. Adicionamos os vértices em ordem para formar o objeto "meuTriangulo"
meuTriangulo.adicionaVertice(vertice_A);
meuTriangulo.adicionaVertice(vertice_B);
meuTriangulo.adicionaVertice(vertice_C);