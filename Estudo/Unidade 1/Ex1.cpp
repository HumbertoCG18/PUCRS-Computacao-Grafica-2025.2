// Definição de uma classe para representar um ponto/vértice 2D
class Ponto {
public:
    float x, y; // Armazena as coordenadas

    // Construtor: permite criar um ponto facilmente
    Ponto(float x = 0.0, float y = 0.0) {
        this->x = x;
        this->y = y;
    }
};

// Como usar:
// Cria um vértice na origem do sistema de coordenadas (0,0)
Ponto vertice_A(0.0, 0.0);

Ponto vertice_B(100.0, 200.0);

Ponto vertice_A1(10.0, 10.0);

Ponto vertice_B1(50.0, 10.0);

Ponto vertice_C1(30.0, 40.0);