#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535898

#define janela_largura 800
#define janela_altura 600

#define player_altura 80
#define player_largura 16

// Auxiliares para que o tamanho da tela possa ser modular
GLfloat janela_x = (janela_largura / 2) - 5;
GLfloat janela_y = (janela_altura / 2) - 5;

// velocidade do jogo
int vel_game = 5;
// Variaveis com relacao ao jogador
int player1_posY = 0;
int player2_posY = 0;
// Variaveis com relacao a bola
float ball_x = 0;
float ball_y = 0;
// Numero de passos movidos por Loop da animacao
float xStep = 1;
float yStep = 1;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void desenhar();
void players(GLfloat pos_x, GLfloat pos_y);
void bola(GLfloat pos_x, GLfloat  pos_y);
void animar_bola(int valor);

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Natao ---- Pong");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard); // chama o teclado
	glutTimerFunc(100, animar_bola, 1); // chama animacao
	glutMainLoop(); // Redesenhar

	return(0);
}

// Comandos do teclado
void keyboard(unsigned char tecla, int x, int y) {

	if (tecla == 'w') {
		if (player1_posY < janela_y - player_altura/2 - 10) {
			player1_posY += vel_game;
		}
	}
	if (tecla == 's') {
		if (player1_posY > -janela_y + player_altura/2 + 10) {
			player1_posY -= vel_game;
		}
	}
	if (tecla == 'o') {
		if (player2_posY < janela_y - player_altura/2 - 10) {
			player2_posY += vel_game;
		}
	}
	if (tecla == 'l') {
		if (player2_posY > -janela_y + player_altura/2 + 10) {
			player2_posY -= vel_game;
		}
	}
	glutPostRedisplay(); // atualizar tela
}

void desenhar() {
	// Grossura das linhas
	glLineWidth(7);
	glColor3ub(255, 255, 255); // itens abaixo na cor branca
	// Limites da tela
	glBegin(GL_LINE_LOOP);
	glVertex2f(-janela_x, janela_y);
	glVertex2f( janela_x, janela_y);
	glVertex2f( janela_x, -janela_y);
	glVertex2f(-janela_x, -janela_y);
	glEnd(); // Fim quadrado
	// Linha central
	glBegin(GL_LINES);
	glVertex2f(0, janela_y); // Primeiro ponto
	glVertex2f(0, -janela_y); // Segundo ponto
	glEnd();
	// Players
	players((GLfloat) -janela_x + 20, (GLfloat) player1_posY);  // player 1 - w - s
	players((GLfloat)  janela_x - 20, (GLfloat) player2_posY);  // player 2 - o - l
	// Bola
	bola(ball_x, ball_y);
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
	// Limites de tela superior e inferior
	if ((ball_y > janela_y - 10) || (ball_y < -janela_y + 10)) {
		yStep = -yStep;
	}
	// Quando um player marcar gol, centralizar a bola
	if ((ball_x > janela_x) || (ball_x < -janela_x)) {
		ball_x = 0;
	}
	// Caso bater na raquete, a bolinha volta
	if ((ball_y < player1_posY + player_altura/2 && ball_y < player1_posY - player_altura / 2) ||
		(ball_y < player2_posY + player_altura / 2 && ball_y < player2_posY - player_altura / 2)) {
		xStep = -xStep;
	}

	ball_x += xStep;
	ball_y += yStep;

	glutPostRedisplay();
	glutTimerFunc(10, animar_bola, 1);
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0, 0.0f); // cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo

	// Especificar o local onde o desenho acontece: bem no centro da janela
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);

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
