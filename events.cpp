#include<GL/glew.h>
#include<GL/glut.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define janelaX 600
#define janelaY 400

#define PI 3.1415926535898

struct Vertices {
	int x;
	int y;
};

//Variables for circle drawing
GLfloat circ_pnt = 200;
GLfloat ang, Xaxis, Yaxis, ballAxis;

//position variables
struct Vertices v1;
struct Vertices v2 = { v2.x = 0,v2.y = 0 };

//Variables for ball colision
float a_value;
float b_value;
float c_value;
bool touch = false;

void display(void);
void tela(GLsizei w, GLsizei h);
void mouseMovement(int x, int y);
void circ();
void desenhar();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(janelaX, janelaY);

	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Natao ---- Colisao");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutReshapeFunc(tela);
	glutDisplayFunc(display);
	glutPassiveMotionFunc(mouseMovement);
	glutMainLoop();

	return(0);
}

void tela(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, janelaX, 0, janelaY);
	glMatrixMode(GL_MODELVIEW);

}

void mouseMovement(int x, int y) {
	v1.x = x - (janelaX / 2);
	v1.y = y - (janelaY / 2);

	float a_value = v1.x - v2.x;
	float b_value = v1.y - v2.y;
	float c_value = sqrt((a_value*a_value) + (b_value*b_value));

	if (c_value < (ballAxis * 2)) {
		touch = true;
		glEnable(GL_TEXTURE_2D);
	}
	else {
		touch = false;
		glDisable(GL_TEXTURE_2D);
	}

	printf("\nX: %i", v1.x);
	printf("\nY: %i", v1.y);
}

void desenhar() {
	glLoadIdentity();

	glPushMatrix();
	glTranslatef((janelaX) / 2, (janelaY) / 2, 0);
	glScalef(1, -1, 1);

	glPushMatrix();
	glTranslatef(v2.x, v2.y, 0);
	glColor3f(200, 200, 200);
	circ();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(v1.x, v1.y, 0);
	glColor3f(255, 255, 255);
	circ();
	glPopMatrix();

	if (touch == true) {
		glClearColor(0.31f, 0.7f, 1.0f, 0.0f);	// definir cor do fundo
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		for (int i = 0; i < 3; i++) {
			glRotated(10,0,0,1);
			glTranslatef(50, 50, 0);
			glColor3f(255, 255, 255);
			circ();
		}
		glPopMatrix();
	}

	glutPostRedisplay();
	glPopMatrix();
}

void circ() {
	ballAxis = 30;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI*i) / circ_pnt;
		glVertex2f(cos(ang)*ballAxis, sin(ang)*ballAxis);
	}
	glEnd();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, janelaX, janelaY);
	desenhar();

	glutSwapBuffers();
}
