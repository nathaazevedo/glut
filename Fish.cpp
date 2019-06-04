#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1315926535898
#define janela_altura 400
#define janela_largura 600

void display(void);
void tela(GLsizei w, GLsizei h);
void desenha_aquario();
void desenha_circulo(GLfloat pos_x, GLfloat pos_y, GLfloat tam_x, GLfloat tam_y, GLfloat  circ_pnt);
void desenha_meio_circulo(GLfloat pos_x, GLfloat pos_y, GLfloat tam_x, GLfloat tam_y, GLfloat  circ_pnt);
void desenha_peixe();

GLfloat circ_pnt = 800;
GLfloat ang, raioX = 30.0f, raioY = 60.0f;
int posX, posY;

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Natao ---- Meu pexe");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);
	glutMainLoop(); // Redesenhar

	return(0);
}

void desenhar() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Aquario
//	glColor3ub(255,255,255);
	desenha_aquario();
	//Desenha pexe
	glColor3ub(0, 0, 0);
	desenha_peixe();
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

void desenha_aquario() {

	glColor3f(0.9, 0.85, 0.85);
	desenha_meio_circulo(0, 0, 150, 150, circ_pnt);
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

void desenha_meio_circulo(GLfloat pos_x, GLfloat pos_y, GLfloat tam_x, GLfloat tam_y, GLfloat circ_pnt) {
	GLfloat ang;

	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = 10 - (1.37f * PI * i) / circ_pnt;
		glVertex2d((cos(ang) * -tam_x) + pos_x, (sin(ang) * -tam_y) + pos_y);
	}
	glEnd();
}

void desenha_peixe(){ 
	// desenhar corpo
	desenha_circulo(50, 0, 35, 17, circ_pnt);
	// desenhar olhos
	glColor3ub(255, 255, 255);
	desenha_circulo(70, 5, 2, 2, circ_pnt);
	// desenhar
	glColor3ub(0, 0, 0);

	glBegin(GL_TRIANGLES);

	glVertex2f(0, 20);
	glVertex2f(20, 0);
	glVertex2f(0, -20);

	glEnd();


}
