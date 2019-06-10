#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define PI 3.1415926535898

#define janela_largura 800
#define janela_altura 600

#define player_altura 80
#define player_largura 16

// Auxiliares para que o tamanho da tela possa ser modular
GLfloat janela_x = (janela_largura / 2) - 5;
GLfloat janela_y = (janela_altura / 2) - 5;

// velocidade do jogo
int vel_game = 3;
// Variaveis com relacao ao jogador
GLfloat player1_posX = -janela_x + 20;
GLfloat player1_posY = 0;
int p1_score = 0;
GLfloat player2_posX = janela_x - 20;
GLfloat player2_posY = 0;
int p2_score = 0;
// Variaveis com relacao a bola
float ball_x = 0;
float ball_y = 0;
// Numero de passos movidos por Loop da animacao
float xStep = 1;
float yStep = 1;
// buffer para teclado
bool* keyStates = new bool[256];

void display(void);
void tela(GLsizei w, GLsizei h);
void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyOperations(void);
void desenhar();
void players(GLfloat pos_x, GLfloat pos_y);
void bola(GLfloat pos_x, GLfloat  pos_y);
void scores(char *string);
void animar_bola(int valor);

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.
	for (int i = 0; i < 256; i++) {
		keyStates[i] = false;
	}
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Natao ---- Pong");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);

	glutKeyboardFunc(keyPressed); // chama o "keyPressed" quando uma tecla for pressionada 
	glutKeyboardUpFunc(keyUp); // chama o "keyUp" quando uma tecla for solta

	glutTimerFunc(4*vel_game, animar_bola, 1); // chama animacao

	glutMainLoop(); // Redesenhar
	 
	return(0);
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true; // Set the state of the current key to pressed  
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed  
}

void keyOperations(void) {
	if (clock() > 3000) {
		if (keyStates['w']) {
			if (player1_posY < janela_y - player_altura / 2 - 10) {
				player1_posY += vel_game;
			}
		} else if (keyStates['s']) {
			if (player1_posY > -janela_y + player_altura / 2 + 10) {
				player1_posY -= vel_game;
			}
		}
		if (keyStates['o']) {
			if (player2_posY < janela_y - player_altura / 2 - 10) {
				player2_posY += vel_game;
			}
		} else if (keyStates['l']) {
			if (player2_posY > -janela_y + player_altura / 2 + 10) {
				player2_posY -= vel_game;
			}
		}
	}
}

void desenhar() {
		// Grossura das linhas
		glLineWidth(7);
		glColor3ub(255, 255, 255); // itens abaixo na cor branca
		// Limites da tela
		glBegin(GL_LINE_LOOP);
		glVertex2f(-janela_x, janela_y);
		glVertex2f(janela_x, janela_y);
		glVertex2f(janela_x, -janela_y);
		glVertex2f(-janela_x, -janela_y);
		glEnd(); // Fim quadrado
		// Linha central
		glBegin(GL_LINES);
		glVertex2f(0, janela_y); // Primeiro ponto
		glVertex2f(0, -janela_y); // Segundo ponto
		glEnd();
		// Players
		players(player1_posX, player1_posY);  // player 1 - w - s
		players(player2_posX, player2_posY);  // player 2 - o - l
		// Bola
		bola(ball_x, ball_y);
		// Pontos
		char pontos[100] = {0};
		sprintf_s(pontos, "%d\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%d", p1_score, p2_score);
		scores(pontos);
}

void players(GLfloat pos_x, GLfloat  pos_y) {
	glPushMatrix();
	glTranslatef(pos_x, pos_y, 0); // posiciona objeto
	glBegin(GL_QUADS);
	glVertex2f(-player_largura/2, player_altura/2);
	glVertex2f(player_largura/2, player_altura/2);
	glVertex2f(player_largura/2, -player_altura/2);
	glVertex2f(-player_largura/2, -player_altura/2);
	glEnd(); // Fim quadrado
	glPopMatrix();
}

void bola(GLfloat pos_x, GLfloat  pos_y) {
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Desenhar o ponto
	glBegin(GL_POINTS);
	glVertex2f(pos_x, pos_y);
	glEnd();
}

void animar_bola(int valor) {
	if(clock() > 3000){
		// Limites de tela superior e inferior
		if ((ball_y > janela_y - 10) || (ball_y < -janela_y + 10)) {
			yStep = -yStep;
		}
		// Quando um player marcar gol, centralizar a bola
		if (ball_x > janela_x) {
			ball_x = 0;
			p1_score++;
		} else if (ball_x < -janela_x) {
			ball_x = 0;
			p2_score++;
		}
		// Se colidir com algum player, mudar a direcao da bol
		if ((ball_y < player1_posY + player_altura / 2 && ball_y > player1_posY - player_altura / 2 && ball_x == player1_posX + 10) ||
			(ball_y < player2_posY + player_altura / 2 && ball_y > player2_posY - player_altura / 2 && ball_x == player2_posX - 10)) {
			xStep = -xStep;
		}

		ball_x += xStep;
		ball_y += yStep;

	}
	glutPostRedisplay();
	glutTimerFunc(2 * vel_game, animar_bola, 1);
}

void scores(char *string) {
	glRasterPos2f(-58, janela_y - 50);

	for (char* c = string; *c != '\0'; c++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c); // Updates the position
	}
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0, 0.0f); // cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo

	// Especificar o local onde o desenho acontece: bem no centro da janela
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);

	keyOperations();
	desenhar();

	glFlush(); // executa o desenho
}

void tela(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// cria a janela ( esq, dir, baixo, cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);
}

/*
	MultiKey on keyboard:
	http://www.swiftless.com/tutorials/opengl/keyboard.html
*/
