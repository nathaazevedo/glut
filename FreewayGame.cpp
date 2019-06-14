#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define PI 3.1415926535898

#define janela_largura 800
#define janela_altura 600

#define player_altura 20
#define player_largura 20

// Auxiliares para que o tamanho da tela possa ser modular
GLfloat janela_x = (janela_largura / 2) - 5;
GLfloat janela_y = (janela_altura / 2) - 5;

// velocidade do jogo
int vel_game = 2;
// Variaveis com relacao ao jogador
GLfloat player1_posX = -janela_x/2;
GLfloat player1_posY = -janela_y+20;
int p1_score = 0;
GLfloat player2_posX =  janela_x/2;
GLfloat player2_posY = -janela_y+20;
int p2_score = 0;
// Variaveis com relacao a bola
float ball_x = 0;
float ball_y = -4;
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
void linha(GLfloat pos_x, GLfloat  pos_y, bool dashed);
void players(GLfloat pos_x, GLfloat pos_y);
void carro(GLfloat pos_x, GLfloat  pos_y);
void scores(char *string);
void animar_carros(int valor);

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.
	for (int i = 0; i < 256; i++) {
		keyStates[i] = false;
	}
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Natao ---- Freeway");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);

	glutKeyboardFunc(keyPressed); // chama o "keyPressed" quando uma tecla for pressionada 
	glutKeyboardUpFunc(keyUp); // chama o "keyUp" quando uma tecla for solta

	glutTimerFunc(4*vel_game, animar_carros, 1); // chama animacao

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
//	if (clock() > 3000) {
		if (keyStates['w']) {
			if (player1_posY < janela_y - player_altura / 2 - 70) {
				player1_posY += vel_game;
			}
			else if (player1_posY >= janela_y - player_altura / 2 - 70){  // Se atravessar a rua
				player1_posY = -janela_y + 20;
				p1_score++;
			}
		}
		if (keyStates['o']) {
			if (player2_posY < janela_y - player_altura / 2 - 70) {
				player2_posY += vel_game;
			} else if (player2_posY >= janela_y - player_altura / 2 - 70) {  // Se atravessar a rua
				player2_posY = -janela_y + 20;
				p2_score++;
			}
		}
//	}
}

void desenhar() {
		// Grossura das linhas
		glLineWidth(7);
		glColor3ub(255, 255, 255); // itens abaixo na cor branca
		// Limites da tela
		glBegin(GL_LINE_LOOP);
		glVertex2f(-janela_x, janela_y-50);
		glVertex2f(janela_x, janela_y-50);
		glVertex2f(janela_x, -janela_y);
		glVertex2f(-janela_x, -janela_y);
		glEnd(); // Fim quadrado
		// Linhas
		glLineWidth(2);
		linha(janela_x, -janela_y + 60, false);   // horizontal embaixo
		linha(janela_x, janela_y - 110, false); // horizontal emcima
		glPushMatrix();
		glTranslatef(0, janela_y - 110, 0);
		for (int i = 0; i < 10; i++) {
			glTranslatef(0, -42, 0); // posiciona objeto
			if(i == 4){
				glPushMatrix();
				glColor3ub(255, 251, 68); // item abaixo na cor amarela
				linha(-janela_x, 0, true); // horizontal central
				glPopMatrix();
			} else {
				glColor3ub(255, 255, 255); // itens abaixo na cor branca
				linha(-janela_x, 0, true); // horizontal central
			}
		}
		glPopMatrix();
		// Players
		players(player1_posX, player1_posY);  // player 1 - w 
		players(player2_posX, player2_posY);  // player 2 - o 
		// Bola
		carro(ball_x, ball_y);
		// Pontos
		char pontos[100] = {0};
		sprintf_s(pontos, "Score player1 = %d\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Score player2 = %d", p1_score, p2_score);
		scores(pontos);
}

void linha(GLfloat pos_x, GLfloat  pos_y, bool dashed) {
	if (dashed == true) {
		glPushMatrix();
		glTranslatef(-janela_x, 0, 0);
		for (int i = 0; i < 16; i++) {
			glBegin(GL_LINES);
			glVertex2f(15, pos_y); // Primeiro ponto
			glVertex2f(50, pos_y); // Segundo ponto
			glEnd();
			glTranslatef(60, 0, 0);
		}
		glPopMatrix();
	}else {
		glBegin(GL_LINES);
		glVertex2f(-pos_x, pos_y); // Primeiro ponto
		glVertex2f(pos_x, pos_y); // Segundo ponto
		glEnd();
	}
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

void carro(GLfloat pos_x, GLfloat  pos_y) {
	glPushMatrix();
	glTranslatef(pos_x, pos_y, 0); // posiciona objeto
	glBegin(GL_QUADS);
	glVertex2f(-20, 10);
	glVertex2f(20, 10);
	glVertex2f(20, -10);
	glVertex2f(-20, -10);
	glEnd(); // Fim quadrado
	glPopMatrix();
}

void animar_carros(int valor) {
	if(clock() > 3000){
		// Quando um player marcar gol, centralizar a bola
		if (ball_x > janela_x) {
			ball_x = -janela_x + 10;
		} else if (ball_x < -janela_x) {
			ball_x = janela_x - 10;
		}
		// Se colidir com algum player, mudar a direcao da bol
		if ((ball_y < player1_posY + player_altura / 2 && ball_y > player1_posY - player_altura / 2 && ball_x == player1_posX + 10) ||
			(ball_y < player2_posY + player_altura / 2 && ball_y > player2_posY - player_altura / 2 && ball_x == player2_posX - 10)) {
			xStep = -xStep;
		}

		ball_x += xStep;
	}
	glutPostRedisplay();
	glutTimerFunc(2 * vel_game, animar_carros, 1);
}

void scores(char *string) {
	glRasterPos2f(-210, janela_y - 30);

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
https://www.youtube.com/watch?v=FPXQT_WXvd8
*/
