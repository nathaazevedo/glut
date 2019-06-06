#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define janela_altura 600
#define janela_largura 800

float rotacao = 0;
float zoom = 1;
float trans = 0;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Rotacao/Zoom/Translacao ---- exercicio de glut");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard); // chama o teclado
	glutMainLoop(); // Redesenhar

	return(0);
}

void keyboard(unsigned char tecla, int x, int y) {
	// quadrado
	if (tecla == 'a') {
		rotacao = rotacao + 0.5;
	}
	else if (tecla == 'b') {
		rotacao = rotacao - 0.5;
	}
	//retangulo
	if (tecla == 'e') {
		trans = trans + 0.5;
	} else if (tecla == 'd') {
		trans = trans - 0.5;
	}
	// tiangulo
	if (tecla == '+') {
		zoom = zoom + 0.05;
	}
	else if (tecla == '-' && zoom > 0.1) {
		zoom = zoom - 0.05;
	}
	glutPostRedisplay();
}

void desenhar() {
	// QUADRADO
	glPushMatrix(); // salva as transformações atuais na pilha
	glRotated(rotacao, 0, 0, 1); // (ang, x, y, z)

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0); // Cor
	glVertex2f(-25, -25);
	glVertex2f(25, -25);
	glVertex2f(25, 25);
	glVertex2f(-25, 25);
	glEnd();

	glPopMatrix(); // restaura as transformações anteriores
	glPushMatrix(); // salva as transformações atuais na pilha
	// RETANGULO
	glTranslatef(trans, trans, 0);

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0); // Cor
	glVertex2f(200, 50);
	glVertex2f(100, 50);
	glVertex2f(100, 90);
	glVertex2f(200, 90);
	glEnd();

	glTranslatef(-trans, -trans, 0);
	glPopMatrix(); // restaura as transformações anteriores
	glPushMatrix(); // salva as transformações atuais na pilha
	// TRIANGULO
	glScalef(zoom, zoom, 0);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 0.0); // Cor
	glVertex2f(-300, -100);
	glVertex2f(-200, 0);
	glVertex2f(-100, -100);
	glEnd();

	glPopMatrix(); // restaura as transformações anteriores
}

void display() {
	glMatrixMode(GL_MODELVIEW); // coordernadas do desenho
	glLoadIdentity();

	glClearColor(0.31f, 0.7f, 1.0f, 0.0f);	// definir cor do fundo
	glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo

	// Especificar o local onde o desenho acontece: bem no centro da janela
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();

	glFlush(); // execute o desenho
}

void tela(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// cria a janela (esq, dir, baixo, cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);
}
