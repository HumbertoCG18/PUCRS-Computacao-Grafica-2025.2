void CriaTiro()

{

    int i = nInstancias;

    // pega a rotacao do personagem que vai atirar

    float ang = Personagens[0].Rotacao;

    

    // Calcula a posição de onde deve sair o tiro,

    // com base no envepole do personagem que vai atirar

    Personagens[i].Escala = Ponto (1,1);

    Personagens[i].Rotacao = ang;

    Personagens[i].IdDoModelo = 1;

    Personagens[i].modelo = DesenhaPersonagemMatricial;

    Personagens[i].Pivot = Ponto(0,0);

    Personagens[i].Direcao = Ponto(0,1); // direcao do movimento para a cima

    Personagens[i].Direcao.rotacionaZ(ang); // direcao alterada para a direita

    

    // Reposiciona o tiro para que fique no meio do personagem

    

    Ponto P = (Personagens[0].Envelope[1] + Personagens[0].Envelope[2])*0.5;

    Ponto V = (Personagens[0].Envelope[1] - P);

    V.versor();

    Personagens[i].Posicao = P + V * 0.5 + Personagens[i].Direcao *0.1;

    // O tiro se move mais rápido que o atirador

    Personagens[i].Velocidade = 3;

    

    // Salva os dados iniciais do tiro i na area de backup

    Personagens[i+AREA_DE_BACKUP] = Personagens[i];

    nInstancias++;

}