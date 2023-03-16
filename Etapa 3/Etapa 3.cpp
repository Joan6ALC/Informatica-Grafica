////////////////////////////////////////////////////
//------------------- Etapa 3 --------------------// 
// -- Autor: Joan Alcover Lladó                   //
// -- DNI: 45187596W                              //
// -- Asignatura: 21714 - Informática Gráfica     //
// -- Curso: 2021-2022                            //
////////////////////////////////////////////////////


#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>

// Constantes de la ventana.
const int W_WIDTH = 600;
const int W_HEIGHT = 600;

float colFondo = 38.0f / 255.0f;

// Angulos de la lámpara
float angBrazoInf = 45.0f; // Subir y Bajar el Brazo inferior.
float angBrazoSup = 135.0f; // Subir y bajar Brazo superior.
float angVertFoco = 0.0f; // Subir y bajar Foco.
float angHorizFoco = 0.0f; // Derecha e izquierda Foco.
float angBrazo = 0.0f; // Giro del Brazo.

// Constantes para dibujar los circulos.
const double pi = M_PI;
const float radioJuntas = 0.03f;


// Propiedades de la lámpara
const float colLamp = 218.0f / 255.0f;
const float colBombilla = 204.0f / 255.0f;
const float longArms = 0.5f;
const float baseCono = 0.15f;
const float alturaCono = 0.3f;
const float baseBase = 0.3f;
const float alturaBase = 0.05f;
const float radioBombilla = 0.05f;


double toRadians(float i)
{
	double r = i * (pi / 180);
	return r;
}

void dibujar() {

	// Dibujamos los ejes.
	glPushMatrix();

	glTranslatef(-0.3f, -0.2f, -1.75f);

	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glLineWidth(1);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex3f(-3.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);


	glVertex3f(0.0f, -3.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, -3.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);

	glEnd();

	glPopMatrix();


	// Pelota
	glPushMatrix();

	glTranslatef(-0.7f, 0.0f, -2.5f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.3f, 75, 75);

	glPopMatrix();

	// Cono Superior
	glPushMatrix();

	glTranslatef(-0.3f, -0.2f + alturaBase, -1.75f);
	glRotatef(angBrazo, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(angBrazoInf)) * longArms + cos(toRadians(angBrazoSup)) * longArms, sin(toRadians(angBrazoInf)) * longArms + sin(toRadians(angBrazoSup)) * longArms, 0);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radioJuntas, 50, 50);

	glRotatef(45 + angVertFoco, 0.0f, 0.0f, 1.0f);
	glRotatef(angHorizFoco, 0.0f, 1.0f, 0.0f);
	glTranslatef(-alturaCono, 0.013f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glColor3f(colLamp, colLamp, colLamp);
	glutWireCone(baseCono, alturaCono, 80, 80);

	// Bombilla
	glTranslatef(0.0f, 0.0f, 0.18f);
	glColor3f(colBombilla, colBombilla, 0.0f);
	glutWireSphere(radioBombilla, 50, 50);

	glPopMatrix();

	// Brazo superior
	glPushMatrix();

	glTranslatef(-0.3f, -0.2f + alturaBase, -1.75f);
	glRotatef(angBrazo, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(angBrazoInf)) * longArms, sin(toRadians(angBrazoInf)) * longArms, 0);
	glRotatef(angBrazoSup, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);

	glColor3f(colLamp, colLamp, colLamp);
	glutWireCylinder(radioJuntas, longArms, 50, 50);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radioJuntas, 50, 50);

	glPopMatrix();

	// Brazo inferior
	glPushMatrix();

	glTranslatef(-0.3f, -0.2f, -1.75f);
	glRotatef(angBrazo, 0.0f, 1.f, 0.f);

	glTranslatef(0, alturaBase, 0);
	glRotatef(angBrazoInf, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);


	glColor3f(colLamp, colLamp, colLamp);
	glutWireCylinder(radioJuntas, longArms, 50, 50);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutWireSphere(radioJuntas, 50, 50);

	glPopMatrix();

	// Base lámpara
	glPushMatrix();

	glTranslatef(-0.3f, -0.2f, -1.75f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	glColor3f(colLamp, colLamp, colLamp);
	glutSolidCone(baseBase, alturaBase, 50, 50);

	glPopMatrix();

}

void Display(void)
{
	
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_MODELVIEW); // Selecciona la matriz del dibujado
	glLoadIdentity();

	
	dibujar();

	glFlush();
	glutSwapBuffers();
}


// Función que reescala la escena para evitar que se distorsione al cambiar las dimensiones de la ventana
void reshapeFunc(int x, int y)
{
	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}

void lecturaEsc(unsigned char key, int xmouse, int ymouse)
{
	

	switch (key) {

	case 'q': //Subir brazo inferior
		if (angBrazoInf < 100)
		{
			angBrazoInf += 1.0f;
		}
		break;
	case 'a': //Bajar brazo inferior
		if (angBrazoInf > 20)
		{
			angBrazoInf -= 1.0f;
		}
		break;

	case 'w': //Subir brazo inferior
		if (angBrazoSup < 165)
		{
			angBrazoSup += 1.0f;
		}
		break;
	case 's': //Bajar brazo superior
		if (angBrazoSup > 100)
		{
			angBrazoSup -= 1.0f;
		}
		break;

	case 'e': //Inclinar foco hacia arriba
		if (angVertFoco > -30)
		{
			angVertFoco -= 1.0f;
		}
		break;
	case 'd': //Inclinar foco hacia abajo
		if (angVertFoco < 30)
		{
			angVertFoco += 1.0f;
		}
		break;

	case 'r': 	//Girar foco hacia izquierda
		if (angHorizFoco < 45)
		{
			angHorizFoco += 1.0f;
		}
		break;

	case 'f': //Girar foco hacia derecha
		if (angHorizFoco > -45)
		{
			angHorizFoco -= 1.0f;
		}
		break;

	case 't': 	//Girar todo izquierda
		angBrazo += 1.0f;
		break;
	case 'g': 	//Girar todo derecha
		angBrazo -= 1.0f;
		break;
	default:
		break;
	}
}

// Función principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Etapa 3");
	glutDisplayFunc(Display);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(Display);
	glutKeyboardFunc(lecturaEsc);
	glClearColor(colFondo, colFondo, colFondo, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return(0);
}