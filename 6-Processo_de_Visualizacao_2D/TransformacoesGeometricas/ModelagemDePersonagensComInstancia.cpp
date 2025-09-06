// **********************************************************************
// PUCRS/Escola Politécnica
// COMPUTAÇÃO GRÁFICA
//
// Programa basico para criar aplicacoes 2D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************

// Para uso no Xcode:
// Abra o menu Product -> Scheme -> Edit Scheme -> Use custom working directory
// Selecione a pasta onde voce descompactou o ZIP que continha este arquivo.

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>


using namespace std;

#ifdef WIN32
#include <windows.h>
#include <glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

#include "Ponto.h"
#include "Instancia.h"

#include "Temporizador.h"

Temporizador T;
double AccumDeltaT=0;

Instancia Universo[10];

// Limites lógicos da área de desenho
Ponto Min, Max;

bool desenha = false;

float angulo=0.0;
int nInstancias=0;

Poligono Mapa, MeiaSeta, Mastro;
// **********************************************************************
//
// **********************************************************************
void CarregaModelos()
{
    Mapa.LePoligono("EstadoRS.txt");
    MeiaSeta.LePoligono("MeiaSeta.txt");
    Mastro.LePoligono("Mastro.txt");
}
// **********************************************************************
// Esta função deve instanciar todos os personagens do cenário
// **********************************************************************
void CriaInstancias()
{
    Universo[0].posicao = Ponto (0,0);
    Universo[0].rotacao = 0;
    Universo[0].modelo = &Mapa;

    Universo[1].posicao = Ponto (10,10);
    Universo[1].rotacao = 45;
    Universo[1].modelo = &MeiaSeta;
    
    Universo[2].posicao = Ponto (-10,-10);
    Universo[2].rotacao = -45;
    Universo[2].modelo = &Mastro;
    
    nInstancias = 3;

}
// **********************************************************************
//
// **********************************************************************
void DesenhaCenario()
{
    for(int i=0; i< nInstancias;i++)
    {
        Universo[i].desenha();
    }
}
// **********************************************************************
//
// **********************************************************************
void init()
{
    // Define a cor do fundo da tela (AZUL)
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    
    //Min.x--;Min.y--;
    //Max.x++;Max.y++;
    
    CarregaModelos();
    CarregaInstancias();
    cout << "Vertices no Vetor: " << MeiaSeta.getNVertices() << endl;
    
    Min = Ponto(-50,-50);
    Max = Ponto(50,50);

}

double nFrames=0;
double TempoTotal=0;
// **********************************************************************
//
// **********************************************************************
void animate()
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;
    TempoTotal += dt;
    nFrames++;


    if (AccumDeltaT > 1.0/30) // fixa a atualização da tela em 30
    {
        AccumDeltaT = 0;
        angulo+=1;
        glutPostRedisplay();
    }
    if (TempoTotal > 5.0)
    {
        cout << "Tempo Acumulado: "  << TempoTotal << " segundos. " ;
        cout << "Nros de Frames sem desenho: " << nFrames << endl;
        cout << "FPS(sem desenho): " << nFrames/TempoTotal << endl;
        TempoTotal = 0;
        nFrames = 0;
    }
}
// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela area OpenGL dentro da Janela
    glViewport(0, 0, w, h);
    // Define os limites logicos da area OpenGL dentro da Janela
    glOrtho(Min.x,Max.x,
            Min.y,Max.y,
            -10,+10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
// **********************************************************************
//
// **********************************************************************
void DesenhaEixos()
{
    Ponto Meio;
    Meio.x = (Max.x+Min.x)/2;
    Meio.y = (Max.y+Min.y)/2;
    Meio.z = (Max.z+Min.z)/2;

    glBegin(GL_LINES);
    //  eixo horizontal
        glVertex2f(Min.x,Meio.y);
        glVertex2f(Max.x,Meio.y);
    //  eixo vertical
        glVertex2f(Meio.x,Min.y);
        glVertex2f(Meio.x,Max.y);
    glEnd();
}

void DesenhaSeta()
{
    glPushMatrix();
        //glScaled(2, 1, 1);
        MeiaSeta.desenhaPoligono();
        glScaled(1,-1, 1);
        MeiaSeta.desenhaPoligono();
    glPopMatrix();
}
void DesenhaApontador()
{
    glPushMatrix();
        glTranslated(-4, 0, 0);
        //glScalef(1.2,1,1);
        DesenhaSeta();
    glPopMatrix();
}
void DesenhaHelice()
{
    glPushMatrix();
    for(int i=0;i < 4; i++)
    {
        glRotatef(90, 0, 0, 1);
        DesenhaApontador();
    }
    glPopMatrix();
}
void DesenhaHelicesGirando()
{
    glPushMatrix();
        glRotatef(angulo, 0, 0, 1);
        DesenhaHelice();
   glPopMatrix();
}
void DesenhaMastro()
{
    Mastro.desenhaPoligono();
}
void DesenhaCatavento()
{
    glPushMatrix();
        DesenhaMastro();
        glPushMatrix();
            glColor3f(1,0,0); // R, G, B  [0..1]
            glTranslated(0,3,0);
            glScaled(0.2, 0.2, 1);
            DesenhaHelicesGirando();
        glPopMatrix();
    glPopMatrix();
}

void DesenhaRetangulo()
{
    glBegin(GL_QUADS);
        glVertex2d(-1, -1);
        glVertex2d(-1, 1);
        glVertex2d(1, 1);
        glVertex2d(1, -1);
    glEnd();
}
void DesenhaPersonagem()  // modelo - veio de arquivo
{
    glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(-1, -1, 0);
        DesenhaRetangulo();

        glTranslatef(2, 0, 0);
        glColor3f(1, 0, 0);
        DesenhaRetangulo();

        glTranslatef(0, 2, 0);
        glColor3f(0, 0, 1);
        DesenhaRetangulo();

        glTranslatef(-2, 0, 0);
        glColor3f(1, 1, 0);
        DesenhaRetangulo();
    glPopMatrix();
}

// **********************************************************************
//  void display( void )
//
// **********************************************************************
void display( void )
{
    //cout << __FUNCTION__ << endl;
	// Limpa a tela coma cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

    // Define os limites lÛgicos da ·rea OpenGL dentro da Janela
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Coloque aqui as chamadas das rotinas que desenham os objetos
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	glLineWidth(1);
	glColor3f(1,1,1); // R, G, B  [0..1]
    DesenhaEixos();
    
    glLineWidth(2);
   
    //DesenhaCatavento();
    
    DesenhaCenario();

	glutSwapBuffers();
}
// **********************************************************************
// ContaTempo(double tempo)
//      conta um certo número de segundos e informa quanto frames
// se passaram neste período.
// **********************************************************************
void ContaTempo(double tempo)
{
    Temporizador T;

    unsigned long cont = 0;
    cout << "Inicio contagem de " << tempo << "segundos ..." << flush;
    while(true)
    {
        tempo -= T.getDeltaT();
        cont++;
        if (tempo <= 0.0)
        {
            cout << "fim! - Passaram-se " << cont << " frames." << endl;
            break;
        }
    }

}
// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
// **********************************************************************

void keyboard ( unsigned char key, int x, int y )
{

	switch ( key )
	{
		case 27:        // Termina o programa qdo
			exit ( 0 );   // a tecla ESC for pressionada
			break;
        case 't':
            ContaTempo(3);
            break;
        case ' ':
            desenha = !desenha;
        break;
		default:
			break;
	}
}
// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
		case GLUT_KEY_UP:       // Se pressionar UP
			glutFullScreen ( ); // Vai para Full Screen
			break;
	    case GLUT_KEY_DOWN:     // Se pressionar UP
								// Reposiciona a janela
            glutPositionWindow (50,50);
			glutReshapeWindow ( 700, 500 );
			break;
		default:
			break;
	}
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
// **********************************************************************
int  main ( int argc, char** argv )
{
    cout << "Programa OpenGL" << endl;

    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (0,0);

    // Define o tamanho inicial da janela grafica do programa
    glutInitWindowSize  ( 650, 500);

    // Cria a janela na tela, definindo o nome da
    // que aparecera na barra de tÌtulo da janela.
    glutCreateWindow    ( "Primeiro Programa em OpenGL" );

    // executa algumas inicializaÁıes
    init ();

    // Define que o tratador de evento para
    // o redesenho da tela. A funcao "display"
    // ser· chamada automaticamente quando
    // for necess·rio redesenhar a janela
    glutDisplayFunc ( display );

    // Define que o tratador de evento para
    // o invalidação da tela. A funcao "display"
    // ser· chamada automaticamente sempre que a
    // máquina estiver ociosa (idle)
    glutIdleFunc(animate);

    // Define que o tratador de evento para
    // o redimensionamento da janela. A funcao "reshape"
    // ser· chamada automaticamente quando
    // o usu·rio alterar o tamanho da janela
    glutReshapeFunc ( reshape );

    // Define que o tratador de evento para
    // as teclas. A funcao "keyboard"
    // ser· chamada automaticamente sempre
    // o usu·rio pressionar uma tecla comum
    glutKeyboardFunc ( keyboard );

    // Define que o tratador de evento para
    // as teclas especiais(F1, F2,... ALT-A,
    // ALT-B, Teclas de Seta, ...).
    // A funcao "arrow_keys" ser· chamada
    // automaticamente sempre o usu·rio
    // pressionar uma tecla especial
    glutSpecialFunc ( arrow_keys );

    // inicia o tratamento dos eventos
    glutMainLoop ( );

    return 0;
}
