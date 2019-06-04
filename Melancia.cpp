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

	glutCreateWindow("GLUT Melancia ---- exercicio de glut");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);
	glutMainLoop(); // Redesenhar

	return(0);
}

void semi_circulo(float tamX, float tamY) {
	GLfloat circ_pnt = 500;
	GLfloat ang, raioX = tamX, raioY = tamY;

	glBegin(GL_POLYGON);
	for (int i = 0; i < (circ_pnt / 2) + 2; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();
}

void desenhar() {
	// ========================
	// Melancia
	// ========================
	glRotated(180, 0, 0, 1); // Girar semi circulo
	glColor3f(0.08f, 0.74f, 0.3f);// Cor verde
	semi_circulo(150, 130);	 // Desenha "Casca"
	glColor3f(1.0, 1.0, 1.0);// Cor branca
	semi_circulo(135, 115);	 // Desenha "Melancia"
	glColor3f(0.92f, 0.3f, 0.33f);// Cor vermelha
	semi_circulo(130, 110);	 // Desenha "Melancia"
	// ========================
	// Sementes
	// ========================
	glPointSize(2); // Aumentar o tamanho do ponto
	glEnable(GL_POINT_SMOOTH);  // Deixar o ponto redondo
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Desenhar o ponto
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 50; i++) {
		int randomX = rand() % 200;
		int randomY = rand() % 70;
		glVertex2f(randomX - 95, randomY + 3);
	}
	glEnd();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // cor do fundo
	glClearColor(0.31f, 0.7f, 1.0f, 0.0f);	// definir cor do fundo

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
