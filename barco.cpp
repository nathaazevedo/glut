#include <stdlib.h>
#include <GL/glut.h>


void keyboard(unsigned char key, int x, int y);
void resize(GLsizei w, GLsizei h);
void display(void);


int main(int argc, char** argv)
{
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(400, 400);  // tamanho da janela

								   //glutFullScreen();  // full screen

	glutInitWindowPosition(10, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Test wagner---- exercicio de glut");   /// cria a janela

	glutKeyboardFunc(&keyboard);

	glutReshapeFunc(&resize); // 

	glutDisplayFunc(display);

	glutMainLoop();

	return EXIT_SUCCESS;
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	}
}

void resize(GLsizei w, GLsizei h)
{

	if (h == 0) h = 1;  // Evita a divisao por zero

	glViewport(0, 0, w, h);  // Especifica as dimensões da Viewport

							 // Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (left, right, bottom, top)
	if (w <= h)
	{
		gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f*h / w);
	}
	else
	{
		gluOrtho2D(0.0f, 250.0f*w / h, 0.0f, 250.0f);
	}
	glMatrixMode(GL_MODELVIEW);


}

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // cor do fundo

	glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo

	glBegin(GL_TRIANGLES); //arvore
	glColor3f(0.17f, 0.23f, 0.0f);
	glVertex2f(200, 120);
	glVertex2f(220, 200);
	glVertex2f(235, 120);
	glEnd();

	glBegin(GL_QUADS); //tronco
	glColor3f(0.35f, 0.19f, 0.0f);
	glVertex2f(210, 120);
	glVertex2f(225, 120);
	glVertex2f(225, 75);
	glVertex2f(210, 75);
	glEnd();

	glBegin(GL_QUADS); //GRAMA
	glColor3f(0.0f, 255.0f, 0.0f);
	glVertex2f(150, 75);
	glVertex2f(300, 75);
	glVertex2f(300, 10);
	glVertex2f(150, 10);
	glEnd();

	glBegin(GL_QUADS); //pier
	glColor3f(0.6f, 0.36f, 0.0f);
	glVertex2f(100, 78);
	glVertex2f(150, 78);
	glVertex2f(150, 10);
	glVertex2f(100, 10);
	glEnd();

	glBegin(GL_QUADS); //mar
	glColor3f(0.0f, 0.0f, 255.0f);
	glVertex2f(0, 40);
	glVertex2f(100, 40);
	glVertex2f(100, 0);
	glVertex2f(0, 0);
	glEnd();

	glBegin(GL_POLYGON); //barco
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(10, 55);
	glVertex2f(80, 55);
	glVertex2f(75, 40);
	glVertex2f(15, 40);
	glEnd();

	glBegin(GL_QUADS); //cabine barco
	glColor3f(255.0f, 255.0f, 0.0f);
	glVertex2f(15, 70);
	glVertex2f(50, 70);
	glVertex2f(50, 55);
	glVertex2f(15, 55);
	glEnd();

	glBegin(GL_QUADS); //janela 1
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(18, 53);
	glVertex2f(23, 53);
	glVertex2f(23, 48);
	glVertex2f(18, 48);
	glEnd();

	glBegin(GL_QUADS); //janela 2
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(60, 53);
	glVertex2f(65, 53);
	glVertex2f(65, 48);
	glVertex2f(60, 48);
	glEnd();

	glBegin(GL_QUADS); //janela 3
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(20, 67);
	glVertex2f(27, 67);
	glVertex2f(27, 62);
	glVertex2f(20, 62);
	glEnd();

	glBegin(GL_QUADS); //janela 4
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(29, 67);
	glVertex2f(36, 67);
	glVertex2f(36, 62);
	glVertex2f(29, 62);
	glEnd();

	glBegin(GL_QUADS); //chaminé barco
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(50, 85);
	glVertex2f(60, 85);
	glVertex2f(60, 55);
	glVertex2f(50, 55);
	glEnd();

	glBegin(GL_LINES); //faixas chaminé barco
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(50, 83);
	glVertex2f(60, 83);
	glVertex2f(50, 80);
	glVertex2f(60, 80);
	glEnd();

	glBegin(GL_LINES); //faixas PIER
	glColor3f(0.0f, 0.0f, 0.0f);
	int y = 10;
	do {
		glVertex2f(100, y);
		glVertex2f(150, y);
		y += 5;
	} while (y < 78);
	
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(300.00, 15.00);
	glVertex2f(295.00, 20);
	glVertex2f(290.00, 15);
	glVertex2f(285.00, 20);
	glVertex2f(280.0, 15);
	glVertex2f(285.00, 20);
	glVertex2f(290.00, 15);
	glVertex2f(295.00, 20);
	glVertex2f(300.00, 15);

	glEnd();


	glFlush(); // executa o desenho

}
