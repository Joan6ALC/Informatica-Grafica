////////////////////////////////////////////////////
//--------- Etapa2: Triángulo y Cuadrado ---------// 
// -- Autor: Joan Alcover Lladó                   //
// -- DNI: 45187596W                              //
// -- Asignatura: 21714 - Informática Gráfica     //
// -- Curso: 2021-2022                            //
////////////////////////////////////////////////////


#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Definimos el tamaño inicial de la ventana
const int W_WIDTH = 500;
const int W_HEIGHT = 500;

GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 

// Función que crea un cuadrado
void Cuadrado(void)
{
	glPushMatrix();

	glBegin(GL_POLYGON);
	glColor3f(0.7f, 0.5f, 0.5f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glColor3f(0.7f, 0.5f, 0.5f);
	glVertex3f(0.15f, -0.15f, 0.0f);
	glColor3f(0.7f, 0.5f, 0.5f);
	glVertex3f(0.15f, 0.15f, 0.0f);
	glColor3f(0.7f, 0.5f, 0.5f);
	glVertex3f(-0.15f, 0.15f, 0.0f);
	glEnd();

	glPopMatrix();
	glFlush();
}

// Función que crea los tres triángulos
void Triangulos(void) {

	glPushMatrix();
	// Rotamos las proximas primitivas
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);

	// Creamos a continuación dibujamos los tres poligonos
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.866f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.866f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-0.5f, 0.866f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.866f, 0.0f);
	glEnd();

	glPopMatrix();
	glFlush();

}
// Función que visualiza los triángulos y el cuadrado
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	Triangulos();
	Cuadrado();
	glutSwapBuffers();

}

// Función que reescala la escena para evitar que se distorsione al cambiar las dimensiones de la ventana
void myReshape(int w, int h)
{
	GLfloat formato;

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	formato = (GLfloat)w / (GLfloat)h;

	if (w <= h)
		glOrtho(-1.0f, 1.0f, -1.0f / formato, 1.0f / formato, 1.0f, -1.0f);
	else
		glOrtho(-1.0f * formato, 1.0f * formato, -1.0f, 1.0f, 1.0f, -1.0f);

}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	// Incrementamos el ángulo
	fAngulo += 0.3f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360)
		fAngulo -= 360;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

// Función principal
int main(int argc, char** argv)
{
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Etapa 2 - Triangulo y Cuadrado");

	// Indicamos cuales son las funciones de redibujado e idle
	glutReshapeFunc(myReshape);

	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}