////////////////////////////////////////////////////
//------------------- Etapa 4 --------------------// 
// -- Autor: Joan Alcover Lladó                   //
// -- DNI: 45187596W                              //
// -- Asignatura: 21714 - Informática Gráfica     //
// -- Curso: 2021-2022                            //
////////////////////////////////////////////////////


#include <windows.h>  
#include <GL/freeglut.h>  
#define _USE_MATH_DEFINES
#include <math.h> 


// Constantes de la ventana
const int W_WIDTH = 640;
const int W_HEIGHT = 640;

float colFondo = 38.0f / 255.0f;

//Ángulo de rotación
float angulo = 0.0f;
float anguloy = 0.1f;
float anguloRotate = 0.0f;

//Vector de la cámara de dirección
float lx = 0.0f, ly = 0.0f, lz = -1.0f;

//Posiciones X, Y, Z de la cámara
float x = 0.0f, y = 0.5f, z = 3.0f;


// Angulos de la lámpara
float angBrazoInf = 45.0f;	// Subir y Bajar el Brazo inferior.
float angBrazoSup = 135.0f;	// Subir y bajar Brazo superior.
float angVertFoco = 0.0f;	// Subir y bajar Foco.
float angHorizFoco = 0.0f;	// Derecha e izquierda Foco.
float angBrazo = 0.0f;		// Giro del Brazo.


// Propiedades de la lámpara
const float colLamp = 218.0f / 255.0f;
const float colBombilla = 204.0f / 255.0f;
const float longArms = 0.5f;
const float baseCono = 0.15f;
const float alturaCono = 0.3f;
const float baseBase = 0.3f;
const float alturaBase = 0.05f;
const float radioBombilla = 0.05f;

// Propiedades de la pelota
const float radPelota = 0.25f;

// Constantes para dibujar los circulos.
const double pi = M_PI;
const float radioJuntas = 0.03f;

double toRadians(float i)
{
	double r = i * (pi / 180);
	return r;
}


// Función que crea la pelota
void pelota() {

	glPushMatrix();

	glTranslatef(-0.5f, radPelota, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(radPelota, 75, 75);

	glPopMatrix();
}

// Función que crea la lámpara
void lampara() {


	// Cono Superior
	glPushMatrix();

	glTranslatef(0.0f, 0.0f + alturaBase, 0.0f);
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

	glTranslatef(0.0f, 0.0f + alturaBase, 0.0f);
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

	glTranslatef(0.0f, 0.0f, 0.0f);
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

	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	glColor3f(colLamp, colLamp, colLamp);
	glutSolidCone(baseBase, alturaBase, 50, 50);

	glPopMatrix();
}

//Dibujar la escena
void Display(void) {

	//Buffers de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Reseteo de las transformaciones
	glLoadIdentity();

	//Establecer la vista de la cámara
	gluLookAt(x, y, z, //Posición donde se encuentra la cámara
		x + lx, y + ly, z + lz, //Posición donde mira la camara una vez situada
		0.0f, 1.0f, 0.0f);

	glRotatef(anguloRotate, 0.0, 1.0, 0.0);

	//Suelo
	glColor3f(0.0, 0.0, 0.8);
	glBegin(GL_LINES);
	for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
		glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
		glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
	}
	glEnd();


	//Dibujo de la figura principal
	pelota();
	lampara();

	glutSwapBuffers();
}

void myReshape(int w, int h) {

	//Evitamos que el ancho de la ventana sea 0
	if (h == 0)
		h = 1;
	float ratio = w * 1.0f / h;

	//Uso de la matriz de proyección
	glMatrixMode(GL_PROJECTION);

	//Reseteo de la matriz
	glLoadIdentity();

	//Ventana gráfica completa
	glViewport(0, 0, w, h);

	//Establecer la perspectiva
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//Volver al modelview
	glMatrixMode(GL_MODELVIEW);
}

//Lectura de movimiento por teclado
void lecturaFlechas(int key, int xx, int yy) {

	float fraccion = 0.1f;

	switch (key) {

	case GLUT_KEY_LEFT:		// Paneo a la izquierda
		angulo -= 0.01f;
		lx = sin(angulo);
		lz = -cos(angulo);
		break;

	case GLUT_KEY_RIGHT:	// Paneo a la derecha
		angulo += 0.01f;
		lx = sin(angulo);
		lz = -cos(angulo);
		break;

	case GLUT_KEY_UP:		// Inclinar la cámara hacia arriba (tilt)
		if (anguloy < 1.0f) {
			anguloy += 0.01f;
			ly = sin(anguloy);
		}
		break;

	case GLUT_KEY_DOWN:		// Inclinar la cámara hacia abajo (tilt)
		if (anguloy > -1.0f) {
			anguloy -= 0.01f;
			ly = sin(anguloy);
		}
		break;
	}
}

void lecturaEsc(unsigned char key, int xmouse, int ymouse)
{
	float fraccion = 0.01f;

	switch (key) {

	case 'q':	// Subir brazo inferior
		if (angBrazoInf < 100)
		{
			angBrazoInf += 1.0f;
		}
		break;
	case 'a':	// Bajar brazo inferior
		if (angBrazoInf > 20)
		{
			angBrazoInf -= 1.0f;
		}
		break;

	case 'w':	// Subir brazo inferior
		if (angBrazoSup < 165)
		{
			angBrazoSup += 1.0f;
		}
		break;
	case 's':	// Bajar brazo superior
		if (angBrazoSup > 100)
		{
			angBrazoSup -= 1.0f;
		}
		break;

	case 'e':	// Inclinar foco hacia arriba
		if (angVertFoco > -30)
		{
			angVertFoco -= 1.0f;
		}
		break;
	case 'd':	// Inclinar foco hacia abajo
		if (angVertFoco < 30)
		{
			angVertFoco += 1.0f;
		}
		break;

	case 'r': 	// Girar foco hacia izquierda
		if (angHorizFoco < 45)
		{
			angHorizFoco += 1.0f;
		}
		break;

	case 'f':	// Girar foco hacia derecha
		if (angHorizFoco > -45)
		{
			angHorizFoco -= 1.0f;
		}
		break;

	case 't':	// Girar todo izquierda
		angBrazo += 1.0f;
		break;

	case 'g':	// Girar todo derecha
		angBrazo -= 1.0f;
		break;

	case 'y':	// Subir la cámara
		y += fraccion;
		break;
	case 'h':	// Bajar la cámara
		y -= fraccion;
		break;

	case 'u':	// Rotar hacia la izquierda
		anguloRotate += 1.0f;
		break;
	case 'j':	// Rotar hacia la derecha
		anguloRotate -= 1.0f;
		break;

	case 'i':	// Zoom hacia adelante
		x += lx * fraccion;
		y += ly * fraccion;
		z += lz * fraccion;
		break;
	case 'k':	// Zoom hacia atrás
		x -= lx * fraccion;
		y -= ly * fraccion;
		z -= lz * fraccion;
		break;

	case '1':	// Reset cámara
		x = 0.0f, y = 0.5f, z = 3.0f;
		lx = 0.0f, ly = 0.0f, lz = -1.0f;
		angulo = 0.0;
		anguloy = 0.1;
		anguloRotate = 0.0;
		break;

	default:
		break;
	}
}

// Función principal
int main(int argc, char** argv) {
	// Inicialización del glut y creación de la ventana
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100); // Posición de la ventana
	glutInitWindowSize(W_WIDTH, W_HEIGHT); // Tamaño de la ventana
	glutCreateWindow("Etapa 4");
	glClearColor(colFondo, colFondo, colFondo, 0.0f);
	glutDisplayFunc(Display);
	glutReshapeFunc(myReshape);
	glutIdleFunc(Display);
	glutKeyboardFunc(lecturaEsc);
	glutSpecialFunc(lecturaFlechas);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}