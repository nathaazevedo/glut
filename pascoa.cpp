#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1315926535898
#define janela_altura 400
#define janela_largura 600

void display(void);
void tela(GLsizei w, GLsizei h);

int main(int argc, char** argv)
{
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
	GLfloat circ_pnt = 400;
	GLfloat ang, raioX = 30.0f, raioY = 60.0f;
	int posX, posY;
	// ========================
	// Ovo 1
	// ========================
	posX = -200;
	posY = -100;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	// ========================
	// Ovo 2
	// ========================
	glColor3f(0.0, 0.0, 1.0);
	posX = +200;
	posY = -100;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	// ========================
	// Coelho
	// ========================
	// Cabeça
	// ========================
	raioX = 100.0f;
	raioY = 130.0f;
	circ_pnt = 400;
	glColor3f(1.0, 1.0, 1.0);
	posX = 0;
	posY = -200;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	// ========================
	// Bochecha left
	// ========================
	raioX = 50.0f;
	raioY = 50.0f;
	circ_pnt = 400;
	glColor3f(1.0, 1.0, 1.0);
	posX = -90;
	posY = -200;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	// ========================
	// Bochecha right
	// ========================
	raioX = 50.0f;
	raioY = 50.0f;
	circ_pnt = 400;
	glColor3f(1.0, 1.0, 1.0);
	posX = 90;
	posY = -200;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	// ========================
	// Orelha left
	// ========================
	raioX = 25.0f;
	raioY = 90.0f;
	circ_pnt = 400;
	glColor3f(1.0, 1.0, 1.0);
	glRotated(20, 0, 0, 1);
	posX = -100;
	posY = 0;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	glRotated(-20, 0, 0, 1); // Arrumar rotacao
	// ========================
	// Orelha right
	// ========================
	raioX = 25.0f;
	raioY = 90.0f;
	circ_pnt = 400;
	glColor3f(1.0, 1.0, 1.0);
	glRotated(-20, 0, 0, 1);
	posX = 100;
	posY = 0;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	glRotated(20, 0, 0, 1); // Arrumar rotacao
	// ========================
	// Pata left
	// ========================
	raioX = 50.0f;
	raioY = 30.0f;
	circ_pnt = 400;
	glColor3f(1.0, 1.0, 1.0);
	posX = -200;
	posY = -195;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	// ========================
	// Pata right
	// ========================
	raioX = 50.0f;
	raioY = 30.0f;
	circ_pnt = 400;
	glColor3f(1.0, 1.0, 1.0);
	posX = +200;
	posY = -195;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * raioX) + posX, (sin(ang) * raioY) + posY);
	}
	glEnd();
	// ========================
	// Olho Left
	// ========================
	glPointSize(15);	// Deixar o ponto redondo
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Desenhar o ponto
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-30, -120);
	glEnd();
	// ========================
	// Olho Right
	// ========================
	glPointSize(15);	// Deixar o ponto redondo
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Desenhar o ponto
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(30, -120);
	glEnd();
	// ========================
	//	Nariz
	// ========================
	glBegin(GL_TRIANGLES);
	glColor3f(0.98f, 0.44f, 0.62f);	// Cor
	glVertex2f(-25, -150);
	glVertex2f(0, -175);			// Vertice da ponta
	glVertex2f(25, -150);
	// OBS: a ordem dos pontos importa
	glEnd();
	// ========================
	//	Bigodes
	// ========================
	/*
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	// Fio 1
	glVertex2f( 22, -152);
	glVertex2f( 70, -147);
	// Fio 2
	glVertex2f( 12, -162);
	glVertex2f( 60, -157);
	// Fio 3
	glVertex2f(  2, -172);
	glVertex2f( 50, -167);
	// Fio 4
	glVertex2f( -22, -152);
	glVertex2f( -70, -147);
	// Fio 5
	glVertex2f( -12, -162);
	glVertex2f( -60, -157);
	// Fio 6
	glVertex2f( -2, -172);
	glVertex2f( -50, -167);
	glEnd();
	*/

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
