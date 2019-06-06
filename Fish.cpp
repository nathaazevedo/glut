#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1315926535898
#define janela_largura 800
#define janela_altura 500

#define tam_aquario 200

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void anim(int value);
void desenhar();
void desenha_aquario();
void desenha_circulo(GLfloat pos_x, GLfloat pos_y, GLfloat tam_x, GLfloat tam_y, GLfloat  circ_pnt);
void desenha_meio_circulo(GLfloat pos_x, GLfloat pos_y, GLfloat tam_x, GLfloat tam_y, GLfloat  circ_pnt);
void desenha_peixe();

GLfloat circ_pnt = 800;
GLfloat ang, raioX = 30.0f, raioY = 60.0f;
int posX, posY;

//variaveis para animacao
float tx = 0.0;
float ty = 0.0;
float xStep = 4;
float yStep = 4;
// Cores
int r = 0, g = 0, b = 0;

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Natao ---- Meu pexe");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard); // chama o teclado
	glutTimerFunc(100, anim, 1); // chama animacao
	glutMainLoop(); // Redesenhar

	return(0);
}

void keyboard(unsigned char tecla, int x, int y) {
	// quadrado
	if (tecla == '1') {
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
		printf("%i %i %i \n", r, g, b);
		glutPostRedisplay(); // atualiza a tela
	}
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

void anim(int value) {
	int limit = (tam_aquario - 10) / 2;
	if ((tx) > (limit) || (tx) < (-limit)) {
		xStep = -xStep;
	}
	if ((ty) > (limit) || (ty) < (-limit)) {
		yStep = -yStep;
	}
	tx += xStep;
	ty += yStep;

	glutPostRedisplay();
	glutTimerFunc(100, anim, 1);
}

void desenhar() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Aquario
	desenha_aquario();
	//Desenha pexe
	glTranslatef(tx, ty, 0);
	desenha_peixe();
}

void desenha_aquario() {
	glColor3ub(230, 215, 216);
	desenha_meio_circulo(0, 0, tam_aquario, tam_aquario, circ_pnt);
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

void desenha_peixe() {
	glColor3ub(r, g, b);
	// desenhar corpo
	desenha_circulo(0, 0, 35, 17, circ_pnt);
	// desenhar cauda
	glBegin(GL_TRIANGLES);

	glVertex2f(-50, 20);
	glVertex2f(-30, 0);
	glVertex2f(-50, -20);

	glEnd();

	// desenhar olhos
	glColor3ub(255, 255, 255);
	desenha_circulo(20, 5, 2, 2, circ_pnt);
}
