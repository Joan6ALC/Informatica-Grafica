////////////////////////////////////////////////////
//------------------- Etapa 5 --------------------// 
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
float lx = 0.0f, ly = 0.1f, lz = -1.0f;

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

// Propiedades de las luces
GLfloat lightx = -0.5f, lighty = 1.0f, lightz = 0.0f;
float colAmarilloB = 90.0f / 255.0f; // (255, 255, amarillo)
float colAmarilloG = 245.0f / 255.0f;
int shade = 1;
GLboolean luz0closed = false;
GLboolean luz1closed = false;
GLboolean luz2closed = false;


GLfloat diffuseLightColor0[] = { 1.0f, colAmarilloG, colAmarilloB, 1.0f };
GLfloat specularLightColor0[] = { 1.0f, colAmarilloG, colAmarilloB, 1.0f };

GLfloat lightPos1[] = { 0.0f, 8.0f, 0.0f, 1.0f }; // Posición luz1


//GLfloat lightx = 1.0f, lighty = 1.0f, lightz = 0.0f;

//Variables de la luz spotlight
static float spotAngle = 70.0f; // Ángulo
static float spotExponent = 2.0; // Atenuación




double toRadians(float i)
{
	double r = i * (pi / 180);
	return r;
}


void myinit()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glNormal3f(0, -1, 0);
	//glEnable(GL_DEPTH_TEST);
}

void setLights() {

	float lightDifAndSpec1[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat diffuseLightColor2[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specularLightColor2[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	
	// Luz 0
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightColor0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightColor0);
	

	// Luz 1
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);

	// Luz 2
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightColor2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightColor2);

}

// Función que crea la pelota
void pelota() {

	glPushMatrix();

	glTranslatef(0.5f, radPelota, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(radPelota, 50, 50);

	glPopMatrix();
}

// Función que crea la letra I
void letraI() {

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(0.0f, 0.02f, 0.0f);
	glScalef(0.4, 0.04, 0.15);
	glutSolidCube(1.0);
	glTranslatef(0.0f, -0.02f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.25f, 0.0f);
	glScalef(0.15, 0.5, 0.15);
	glutSolidCube(1.0);
	glTranslatef(0.0f, -0.25f, 0.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0f, 0.52f, 0.0f);
	glScalef(0.4, 0.04, 0.15);
	glutSolidCube(1.0);
	glTranslatef(0.0f, -0.52f, 0.0f);
	glPopMatrix();

	glPopMatrix();
}

void cuchara() {

	glPushMatrix();

	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.8f, 0.1f, 1.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidTorus(0.1f, 0.3f, 10, 10);

	glPopMatrix();

}

// Función que crea la lámpara
void lampara() {
	glPushMatrix();
	// Cono Superior
	glPushMatrix();

	glTranslatef(0.0f, 0.54f + alturaBase, 0.0f);
	glRotatef(angBrazo, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(angBrazoInf)) * longArms + cos(toRadians(angBrazoSup)) * longArms, sin(toRadians(angBrazoInf)) * longArms + sin(toRadians(angBrazoSup)) * longArms, 0);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radioJuntas, 50, 50);

	glRotatef(45 + angVertFoco, 0.0f, 0.0f, 1.0f);
	glRotatef(angHorizFoco, 0.0f, 1.0f, 0.0f);
	glTranslatef(-alturaCono, 0.013f, 0.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glColor3f(colLamp, colLamp, colLamp);
	glutSolidCone(baseCono, alturaCono, 80, 80);

	// Bombilla
	glTranslatef(0.0f, 0.0f, 0.0f);
	
	// Luz del foco
	GLfloat lightPos0[] = { 0.0f, 0.0f, -0.07f, 1.0f }; //posicion de la luz0
	float spotDirection0[] = { sin(toRadians(angHorizFoco)), 0.0f, -cos(toRadians(angVertFoco + 45)) };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0); // Actualizamos la posición de la luz0

	glColor3f(colBombilla, colBombilla, 0.0f);
	glutSolidSphere(radioBombilla, 50, 50);

	glPopMatrix();

	// Brazo superior
	glPushMatrix();

	glTranslatef(0.0f, 0.54f + alturaBase, 0.0f);
	glRotatef(angBrazo, 0.0f, 1.f, 0.f);

	glTranslatef(cos(toRadians(angBrazoInf)) * longArms, sin(toRadians(angBrazoInf)) * longArms, 0);
	glRotatef(angBrazoSup, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);

	glColor3f(colLamp, colLamp, colLamp);
	glutSolidCylinder(radioJuntas, longArms, 50, 50);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radioJuntas, 50, 50);

	glPopMatrix();

	// Brazo inferior
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(angBrazo, 0.0f, 1.f, 0.f);

	glTranslatef(0.0f, 0.54f + alturaBase, 0.0f);
	glRotatef(angBrazoInf, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);


	glColor3f(colLamp, colLamp, colLamp);
	glutSolidCylinder(radioJuntas, longArms, 50, 50);

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(radioJuntas, 50, 50);

	glPopMatrix();

	// Base lámpara
	glPushMatrix();

	glTranslatef(0.0f, 0.54f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	glColor3f(colLamp, colLamp, colLamp);
	glutSolidCone(baseBase, alturaBase, 80, 80);

	glPopMatrix();
	glPopMatrix();
}



//Dibujar la escena
void Display(void) {
	GLfloat lightPos2[] = { lightx, lighty, lightz, 1.0f }; // Posición luz2
	
	//Buffers de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_MODELVIEW);
	//Reseteo de las transformaciones
	glLoadIdentity();


	//Establecer la vista de la cámara
	gluLookAt(x, y, z, //Posición donde se encuentra la cámara
		x + lx, y + ly, z + lz, //Posición donde mira la camara una vez situada
		0.0f, 1.0f, 0.0f);

	glRotatef(anguloRotate, 0.0, 1.0, 0.0);

	// Inicializamos las normales de los objetos, así como los reflejos de las luces
																											//glEnable(GL_NORMALIZE);
																											//glEnable(GL_SHADE_MODEL);
	//glShadeModel(GL_SMOOTH);

	setLights();

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	//luz roja que se mueve con el teclado
	
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	
	//esfera para conocer la posicion de la luz
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(lightx, lighty, lightz);
	glutSolidSphere(0.02, 10, 10);
	glPopMatrix();

	glPushMatrix();
	//Dibujamos un cuadrado por debajo de la cuadrícula
	glColor4f(0.8, 0.8, 0.8, 1.0);

	//glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(4.0, 0.01, 4.0);
	glutSolidCube(1.0);
	//glTranslatef(0.0f, -0.52f, 0.0f);
	glPopMatrix();


	

																													//glEnable(GL_LIGHTING);
	

	glPushMatrix();
	pelota();
	glPopMatrix();

	glPushMatrix();
	cuchara();
	glPopMatrix();

	glPushMatrix();
	letraI();
	glPopMatrix();

	glPushMatrix();
	lampara();
	glPopMatrix();


	glutSwapBuffers();
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
		if (angHorizFoco < 80)
		{
			angHorizFoco += 1.0f;
		}
		break;

	case 'f':	// Girar foco hacia derecha
		if (angHorizFoco > -80)
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
		lx = 0.0f, ly = 0.1f, lz = -1.0f;
		angulo = 0.0f;
		anguloy = 0.1f;
		anguloRotate = 0.0f;
		break;

	case 'z':
		if (luz0closed) {
			luz0closed = false;
			glEnable(GL_LIGHT0);
		}
		else {
			luz0closed = true;
			glDisable(GL_LIGHT0);
		}
		break;

	case 'x':
		if (luz1closed) {
			luz1closed = false;
			glEnable(GL_LIGHT1);
		}
		else {
			luz1closed = true;
			glDisable(GL_LIGHT1);
		}
		break;

	case 'c':
		if (luz2closed) {
			luz2closed = false;
			glEnable(GL_LIGHT2);
		}
		else {
			luz2closed = true;
			glDisable(GL_LIGHT2);
		}
		break;

		//Moverse la luz en ejex x y z
	case 'b': //hacia la derecha
		lightx += 0.01f;
		break;
	case 'v': //hacia la izquierda
		lightx -= 0.01f;
		break;

	case 'n': //hacia arriba
		lighty += 0.01f;
		break;
	case 'm': //hacia abajo
		lighty -= 0.01f;
		break;
	case 'l': //hacia adelante
		lightz += 0.01f;
		break;
	case 'o': //hacia atras
		lightz -= 0.01f;
		break;

		// Espacio
	case 32:
		if (shade == 1) {
			glShadeModel(GL_FLAT); 
			shade++;
		}
		else {
			glShadeModel(GL_SMOOTH); 
			shade--;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void initRender() {

	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	
	glEnable(GL_LIGHTING); //Enable lighting
	// Luz del gancho
	
	glEnable(GL_LIGHT0); 
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glEnable(GL_NORMALIZE);
	glEnable(GL_SHADE_MODEL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void myReshape(int x, int y) {

	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}

// Función principal
int main(int argc, char** argv) {
	// Inicialización del glut y creación de la ventana
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutCreateWindow("Etapa 5");
	initRender();
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glutDisplayFunc(Display);
	glutReshapeFunc(myReshape);
	myinit();
	glutIdleFunc(Display);
	glutKeyboardFunc(lecturaEsc);
	glutSpecialFunc(lecturaFlechas);
	glutMainLoop();
	return 0;
}