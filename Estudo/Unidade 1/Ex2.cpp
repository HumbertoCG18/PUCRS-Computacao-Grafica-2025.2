// A classe Linha precisa saber o que é um Ponto
#include "Ponto.h"

class Linha {
public:
    Ponto inicio; // Armazena o vértice inicial da aresta
    Ponto fim;    // Armazena o vértice final da aresta

    // Construtor que recebe os dois pontos
    Linha(Ponto p1, Ponto p2) {
        inicio = p1;
        fim = p2;
    }
};

// Como usar, aproveitando os vértices que criamos antes:
Ponto vertice_A1(10.0, 10.0);
Ponto vertice_B1(50.0, 10.0);
Ponto vertice_C1(30.0, 40.0);

// Agora, criamos a aresta que conecta A e B
Linha aresta_AB(vertice_A1, vertice_B1);
Linha aresta_BC(vertice_B1, vertice_C1);
Linha aresta_CA(vertice_C1, vertice_A1);