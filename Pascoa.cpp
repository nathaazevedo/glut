#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1315926535898
#define janela_altura 400
#define janela_largura 600

void display(void);
void tela(GLsizei w, GLsizei h);
void desenha_circulo(GLfloat pos_x, GLfloat pos_y, GLfloat tam_x, GLfloat tam_y, GLfloat  circ_pnt);
void detalhes_patas(GLfloat pos_x, GLfloat pos_y, GLfloat tam_x, GLfloat tam_y, GLfloat  circ_pnt);

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Natao ---- Pascoa");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);
	glutMainLoop(); // Redesenhar

	return(0);
}

void desenhar() {
	GLfloat circ_pnt = 800;
	GLfloat ang, raioX = 30.0f, raioY = 60.0f;
	int posX, posY;
	// ========================
	// Ovo 1
	// ========================
	glColor3f(1.0, 0.0, 0.0);
	desenha_circulo(-200, -95, 40, 70, circ_pnt);

	glRotated(-30,0,0,1);
	desenha_circulo(-170, -70, 15, 50, circ_pnt);
	glRotated(30, 0, 0, 1);
	desenha_circulo(-200, 30, 15, 50, circ_pnt);
	glRotated(30, 0, 0, 1);
	desenha_circulo(-180, 130, 15, 50, circ_pnt);
	glRotated(-30, 0, 0, 1);
	glColor3f(0.0, 0.0, 1.0);
	// ========================
	// LAÇO
	// ========================
	glBegin(GL_TRIANGLES);
	glVertex2d(-250, 5);
	glVertex2d(-250, -45);
	glVertex2d(-200, -20);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2d(-150, 5);
	glVertex2d(-150, -45);
	glVertex2d(-200, -20);
	glEnd();
	desenha_circulo(-200, -20, 15, 15,circ_pnt);
	// Ladinhos
	glBegin(GL_POLYGON);
	for (int i = 200; i < (circ_pnt / 2) + 200; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * 20) -250, (sin(ang) * 25) -20);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = -200; i < (circ_pnt / 2) - 200; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * 20) - 150, (sin(ang) * 25) - 20);
	}
	glEnd();
	// ========================
	// Ovo 2
	// ========================
	glColor3f(0.0, 0.0, 1.0);
	desenha_circulo(200, -95, 40, 70, circ_pnt);

	glRotated(-30, 0, 0, 1);
	desenha_circulo(180, 130, 15, 50, circ_pnt);
	glRotated(30, 0, 0, 1);
	desenha_circulo(200, 30, 15, 50, circ_pnt);
	glRotated(30, 0, 0, 1);
	desenha_circulo(165, -70, 15, 50, circ_pnt);
	glRotated(-30, 0, 0, 1);
	glColor3f(1.0, 0.0, 0.0);
	// ========================
	// LAÇO
	// ========================
	glBegin(GL_TRIANGLES);
	glVertex2d(250, 5);
	glVertex2d(250, -45);
	glVertex2d(200, -20);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2d(150, 5);
	glVertex2d(150, -45);
	glVertex2d(200, -20);
	glEnd();
	desenha_circulo(200, -20, 15, 15, circ_pnt);
	
	// Ladinhos
	glBegin(GL_POLYGON);
	for (int i = 200; i < (circ_pnt / 2) + 200; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * 20) + 150, (sin(ang) * 25) - 20);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = -200; i < (circ_pnt / 2) - 200; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * 20) + 250, (sin(ang) * 25) - 20);
	}
	glEnd();
	
	// ========================
	// Coelho
	// ========================
	glColor3f(1.0, 1.0, 1.0); // Setar cor branca
	// ========================
	// Cabeça
	// ========================
	//glLineWidth(2);
	desenha_circulo(0, -170, 65, 135, circ_pnt);
	// ========================
	// Bochecha left
	// ========================
	desenha_circulo(-60, -182, 50, 50, circ_pnt);
	// ========================
	// Bochecha right
	// ========================
	desenha_circulo(60, -182, 50, 50, circ_pnt);
	/*
	raioX = 35.0f;
	raioY = 35.0f;
	glColor3ub(112, 111, 111);
	posX = 65;
	posY = -180;
	glBegin(GL_LINE_STRIP);
	for (int i = circ_pnt; i > circ_pnt / 2 + 20; i--) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	*/
	// ========================
	// Orelhas
	// ========================
	glColor3f(1.0, 1.0, 1.0); // Cor branca
	// Orelha esquerda
	glRotated(20, 0, 0, 1);
	desenha_circulo(-60, 30, 30, 90, circ_pnt);
	glRotated(-20, 0, 0, 1); // Arrumar rotacao
	// Orelha Direita
	glRotated(-20, 0, 0, 1);
	desenha_circulo(60, 30, 30, 90, circ_pnt);
	glRotated(20, 0, 0, 1); // Arrumar rotacao
	// Dentro da orelha
	glColor3ub(249, 189, 242); // Cor rosa
	glRotated(20, 0, 0, 1);
	desenha_circulo(-60, 30, 17, 77, circ_pnt);// Esquerda
	glRotated(-40, 0, 0, 1); // Arrumar rotacao
	desenha_circulo(60, 30, 17, 77, circ_pnt); // Direita
	glRotated(20, 0, 0, 1);  // Arrumar rotacao
	// Dobra da orelha
	glColor3f(1.0, 1.0, 1.0);
	desenha_circulo(-93, 33, 25, 60, circ_pnt); // Esquerda
	desenha_circulo(93, 33, 25, 60, circ_pnt);	// Direita
	// ========================
	// Pata right
	// ========================
	raioX = 40.0f;
	raioY = 35.0f;
	glRotated(180, 0, 0, 0);
	posX = -200;
	posY = 165;
	glBegin(GL_POLYGON);
	for (int i = 0; i < (circ_pnt / 2) + 1; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	glRotated(-180, 0, 0, 1);

	glColor3f(0, 0, 0);
	detalhes_patas(210, -156, 20, 30, circ_pnt);
	detalhes_patas(190, -156, 20, 30, circ_pnt);
	detalhes_patas(170, -156, 20, 30, circ_pnt);
	// ========================
	// Pata left
	// ========================
	raioX = 40.0f;
	raioY = 35.0f;
	glColor3f(1.0, 1.0, 1.0);
	glRotated(180, 0, 0, 0);
	posX = 200;
	posY = 165;
	glBegin(GL_POLYGON);
	for (int i = 0; i < (circ_pnt / 2) + 1; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();

	glRotated(-180, 0, 0, 1);

	glColor3f(0, 0, 0);
	detalhes_patas(-230, -156, 20, 30, circ_pnt);
	detalhes_patas(-210, -156, 20, 30, circ_pnt);
	detalhes_patas(-190, -156, 20, 30, circ_pnt);
	// ========================
	// Olho Left
	// ========================
	/*
	glPointSize(15);	// Deixar o ponto redondo
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Desenhar o ponto
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-30, -120);
	glEnd();
	*/
	raioX = 15.0f;
	raioY = 10.0f;
	glColor3f(0, 0, 0);
	posX = -25;
	posY = -105;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < (circ_pnt / 2) + 1; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	// ========================
	// Olho Right
	// ========================
	/*
	glPointSize(15);	// Deixar o ponto redondo
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Desenhar o ponto
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(30, -120);
	glEnd();
	*/
	raioX = 15.0f;
	raioY = 10.0f;
	glColor3f(0, 0, 0);
	posX = 25;
	posY = -105;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < (circ_pnt / 2) + 1; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	// ========================
	//	Nariz
	// ========================
	glBegin(GL_TRIANGLES);
	glColor3f(0.98f, 0.44f, 0.62f);	// Cor
	glVertex2f(-25, -140);
	glVertex2f(0, -165);			// Vertice da ponta
	glVertex2f(25, -140);
	// OBS: a ordem dos pontos importa
	glEnd();
	// ========================
	// Boca
	// ========================
	raioX = 30.0f;
	raioY = 20.0f;
	circ_pnt = 400;
	glColor3f(0, 0, 0);
	glRotated(180, 0, 0, 0);
	posX = -30;
	posY = 165;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < (circ_pnt / 2) + 1; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	glRotated(-180, 0, 0, 0);

	raioX = 30.0f;
	raioY = 20.0f;
	circ_pnt = 400;
	glColor3f(0, 0, 0);
	glRotated(180, 0, 0, 0);
	posX = 30;
	posY = 165;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < (circ_pnt / 2) + 1; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	glRotated(-180, 0, 0, 0);

	/*
	Imagem como base
	https://www.google.com/search?biw=2560&bih=937&tbm=isch&sa=1&ei=5QGlXK6gGe6w5OUPr5q-qAk&q=coelho+da+pascoa&oq=coelho+da+pascoa&gs_l=img.3..0l10.706.2172..2312...0.0..0.152.1644.0j12......0....1..gws-wiz-img.......0i10j0i10i24j0i67.mS-aT3cwtEo#imgrc=C_u4Rb7zQbpN9M:
	*/

}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.25f, 1.0f, 0.66f, 1.0f);  // cor do fundo

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

void desenha_circulo(GLfloat pos_x, GLfloat pos_y, GLfloat tam_x, GLfloat tam_y, GLfloat circ_pnt) {
	GLfloat ang;

	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * tam_x) + pos_x, (sin(ang) * tam_y) + pos_y);
	}
	glEnd();
}

void detalhes_patas(GLfloat pos_x, GLfloat pos_y, GLfloat tam_x, GLfloat tam_y, GLfloat circ_pnt) {
	GLfloat ang;

	glBegin(GL_LINE_STRIP);
	for (int i = -150; i < (circ_pnt / 4) - 240; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * tam_x) + pos_x, (sin(ang) * tam_y) + pos_y);
	}
	glEnd();
}
