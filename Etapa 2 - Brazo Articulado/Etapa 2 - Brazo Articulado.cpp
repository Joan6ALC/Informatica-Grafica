////////////////////////////////////////////////////
//---------- Etapa 2: Brazo Articulado -----------// 
// -- Autor: Joan Alcover Lladó                   //
// -- DNI: 45187596W                              //
// -- Asignatura: 21714 - Informática Gráfica     //
// -- Curso: 2021-2022                            //
////////////////////////////////////////////////////


#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

// Definimos el tamaño inicial de la ventana
const int W_WIDTH = 1000;
const int W_HEIGHT = 800;
int hombro = 0, codo = 0;

// Función que visualiza el brazo articulado
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix(); // Movimiento global

	glRotatef(-90, 0.0, 0.0, 1.0); // Rotamos para que el brazo aparezca en vertical

	glTranslatef(-2.0, 0.0, 0.0); // Movimiento del hombro
	glRotatef((GLfloat)hombro, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);

	glPushMatrix(); // Brazo
	glScalef(2.0, 0.4, 1.0);
	glColor3f(0.0f, 0.0f, 50.0f);
	glutSolidCube(1.0);
	glColor3f(50.0f, 0.0f, 0.0f);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(1.0, 0.0, 0.0); // Movimiento del antebrazo
	glRotatef((GLfloat)codo, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);

	glPushMatrix(); // Antebrazo
	glScalef(2.0, 0.4, 1.0);
	glColor3f(0.0f, 0.0f, 50.0f);
	glutSolidCube(1.0);
	glColor3f(50.0f, 0.0f, 0.0f);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(-1.0, 0.0, 0.0);

	glPushMatrix(); // Esfera (codo)
	glColor3f(50.0f, 0.0f, 0.0f);
	glutSolidSphere(0.3f, 100, 100);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

// Función de reescalado para el ajuste a la ventana
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

// Función de lectura del teclado para el movimiento del brazo
void lecturaEsc(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w': // Rotar el hombro a la izquierda
		hombro = (hombro + 5) % 360;
		glutPostRedisplay();
		break;
	case 'q': // Rotar el hombro a la derecha
		hombro = (hombro - 5) % 360;
		glutPostRedisplay();
		break;
	case 's': // Rotar el codo a la izquierda
		codo = (codo + 5) % 360;
		glutPostRedisplay();
		break;
	case 'a': // Rotar el codo a la derecha
		codo = (codo - 5) % 360;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Función principal
int main(int argc, char** argv)
{
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Etapa 2 - Brazo Articulado");
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glutDisplayFunc(Display);

	glutReshapeFunc(reshape);

	glutKeyboardFunc(lecturaEsc);


	glutMainLoop();
	return 0;
}