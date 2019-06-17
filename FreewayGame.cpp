#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define PI 3.1415926535898

#define janela_largura 800
#define janela_altura 600

#define player_altura 12
#define player_largura 12

// Auxiliares para que o tamanho da tela possa ser modular
GLfloat janela_x = (janela_largura / 2) - 5;
GLfloat janela_y = (janela_altura / 2) - 5;

// velocidade do jogo
int vel_game = 3;
// Variaveis com relacao ao jogador
typedef struct {
	float posX;
	float posY = -janela_y + 20;
	int score = 0;
} Jogador;

Jogador player[2];
// Variaveis com relacao a bola
typedef struct{
	float x;
	float y;
	int vel = 1;
	int cor[3] = {255,255,255};
} Carro;

Carro car[10];
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
void linha_asfalto(GLfloat pos_x, GLfloat  pos_y, bool dashed);
void desenha_players(GLfloat pos_x, GLfloat pos_y);
void desenha_carro(GLfloat pos_x, GLfloat pos_y);
void scores(char *string);
void animar_carros(int valor);

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	for (int i = 0; i < 256; i++) { // Zerar buffer de teclado 
		keyStates[i] = false;
	}
	// Ajustas posicao inicial do jogador
	player[0].posX = -janela_x / 2;
	player[1].posX = janela_x / 2;

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
	if (clock() > 4000) {
		if (keyStates['w']) {
			if (player[0].posY < janela_y - player_altura / 2 - 70) {
				player[0].posY += vel_game;
			}
			else if (player[0].posY >= janela_y - player_altura / 2 - 70){  // Se atravessar a rua
				player[0].posY = -janela_y + 20;
				player[0].score++;
			}
		}
		if (keyStates['o']) {
			if (player[1].posY < janela_y - player_altura / 2 - 70) {
				player[1].posY += vel_game;
			} else if (player[1].posY >= janela_y - player_altura / 2 - 70) {  // Se atravessar a rua
				player[1].posY = -janela_y + 20;
				player[1].score++;;
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
		glVertex2f(-janela_x, janela_y-50);
		glVertex2f(janela_x, janela_y-50);
		glVertex2f(janela_x, -janela_y);
		glVertex2f(-janela_x, -janela_y);
		glEnd(); // Fim quadrado
		// Linhas
		glLineWidth(2);
		linha_asfalto(janela_x, -janela_y + 60, false);   // horizontal embaixo
		linha_asfalto(janela_x, janela_y - 110, false); // horizontal emcima
		glPushMatrix();
		glTranslatef(0, janela_y - 110, 0); // ajustar topo da tela
		for (int i = 0; i < 10; i++) {
			glTranslatef(0, -42, 0); // posiciona objeto
			if(i == 4){
				glColor3ub(255, 251, 68);  // item abaixo na cor amarela
			} else {
				glColor3ub(255, 255, 255); // itens abaixo na cor branca
			}
			linha_asfalto(-janela_x, 0, true); // horizontal central
		}
		glPopMatrix();
		// Carros
		glPushMatrix();
		glTranslatef(0, janela_y - 110, 0); // ajustar topo da tela
		for (int i = 0; i < 10; i++) {
			car[i].y = (float) -42 * (i + 1);	// deslocar
			if (i == 5) {				// girar desenho
				glScalef(-1, 1, 1);	
			}	
			glColor3ub(car[i].cor[0], car[i].cor[1], car[i].cor[2]);
			// pegar cor
			desenha_carro(car[i].x , car[i].y + 21); // fazer desenho
		}
		glPopMatrix();
		// Pontos
		char pontos[100] = {0};
		sprintf_s(pontos, "Score player1 = %d\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Score player2 = %d", player[0].score, player[1].score);
		scores(pontos);
		// Players
		for (int i = 0; i < 2; i++) {
			desenha_players(player[i].posX, player[i].posY);  // desenha galinhas
		}
}

void linha_asfalto(GLfloat pos_x, GLfloat  pos_y, bool dashed) {
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

void desenha_players(GLfloat pos_x, GLfloat  pos_y) {
	glPushMatrix();
	glColor3ub(244, 229, 66);
	glTranslatef(pos_x, pos_y, 0); // posiciona objeto
	// Corpo
	glBegin(GL_QUADS);
	glVertex2f(-player_largura/2, player_altura/2);
	glVertex2f(player_largura/2, player_altura/2);
	glVertex2f(player_largura/2, -player_altura/2);
	glVertex2f(-player_largura/2, -player_altura/2);
	glEnd(); // Fim quadrado
	// Cabeca
	glPushMatrix();
	glPointSize(12);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Desenhar Cabeca
	glBegin(GL_POINTS);
	glVertex2f(5, 10);
	glEnd();
	glPopMatrix();
	// Perna esq
	glBegin(GL_LINES);
	glVertex2f(-3, -8); // Primeiro ponto
	glVertex2f(-3, -13); // Segundo ponto
	glEnd();
	// Perna dir
	glBegin(GL_LINES);
	glVertex2f(3, -8); // Primeiro ponto
	glVertex2f(3, -13); // Segundo ponto
	glEnd();
	// Rabo
	glBegin(GL_LINE_LOOP);
	glVertex2f(-5, 5);
	glVertex2f(-15, 8);
	glVertex2f(-5, 3);
	glEnd();
	// Bico
	glBegin(GL_LINE_LOOP);
	glVertex2f(10, 8);
	glVertex2f(13, 7);
	glVertex2f(10, 5);
	glEnd();
	glPopMatrix();
}

void desenha_carro(GLfloat pos_x, GLfloat  pos_y) {
	glPushMatrix();
	glTranslatef(pos_x, pos_y, 0); // posiciona objeto
	// chassi
	glBegin(GL_QUADS);
	glVertex2f(-20, 10);
	glVertex2f(20, 10);
	glVertex2f(20, -10);
	glVertex2f(-20, -10);
	glEnd(); // Fim quadrado
	// objetos na cor preta
	glColor3ub(114, 117, 117);
	// vidros
	glBegin(GL_QUADS);
	glVertex2f( 5, 8);
	glVertex2f(15, 8);
	glVertex2f(15, -8);
	glVertex2f( 5, -8);
	glEnd(); // Fim quadrado
	// Pneu 1
	glBegin(GL_QUADS);
	glVertex2f(17, 15);
	glVertex2f(7, 15);
	glVertex2f(7, 10);
	glVertex2f(17, 10);
	glEnd(); // Fim quadrado
	// Pneu 2
	glBegin(GL_QUADS);
	glVertex2f(-17, 15);
	glVertex2f(-7, 15);
	glVertex2f(-7, 10);
	glVertex2f(-17, 10);
	glEnd(); // Fim quadrado
	// Pneu 3
	glBegin(GL_QUADS);
	glVertex2f(17, -15);
	glVertex2f(7, -15);
	glVertex2f(7, -10);
	glVertex2f(17, -10);
	glEnd(); // Fim quadrado
	// Pneu 4
	glBegin(GL_QUADS);
	glVertex2f(-17, -15);
	glVertex2f(-7, -15);
	glVertex2f(-7, -10);
	glVertex2f(-17, -10);
	glEnd(); // Fim quadrado
	// resetar cor
	glColor3ub(255, 255, 255);
	glPopMatrix();
}

void animar_carros(int valor) {
	int random[10];
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {		// São 10 carros, então
		random[i] = rand() % 500;		// Sotear uma posicao aleatoria
		if (car[i].x > janela_x - 20) {		// Se sair a pista
			for (int j = 0; j < 3; j++) {	// sortear nova cor
				car[i].cor[j] = rand() % 255; // sortear r,g,b
			}
			car[i].x = -janela_x - random[i];
			car[i].vel = 1 + rand() % 3;
		}
		car[i].x += xStep * car[i].vel; // Mover carro
		for (int j = 0; j < 2; j++) {	// Percorre os dois jogadores
			float colY = car[i].y + 200 < player[j].posY + 20 && car[i].y + 200 > player[j].posY - 20;
			float colX = car[i].x > player[j].posX - 20 && car[i].x < player[j].posX + 20;
			if (i > 4) {
				colX = -car[i].x > player[j].posX - 20 && -car[i].x < player[j].posX + 20;
			}
			// Se acontecer colisao com jogador
			if (colY && colX) {
					printf("%f %f %i\n", car[i].x, car[i].y + 200, i);
					printf("%f %f \n\n\n", player[0].posX, player[0].posY);
				//	system("pause");
					player[0].posY = -janela_y + 20;
			}
		}
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
