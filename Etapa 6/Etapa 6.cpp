////////////////////////////////////////////////////
//------------------- Etapa 6 --------------------// 
// -- Autor: Joan Alcover Lladó                   //
// -- DNI: 45187596W                              //
// -- Asignatura: 21714 - Informática Gráfica     //
// -- Curso: 2021-2022                            //
////////////////////////////////////////////////////


#include <windows.h>  
#include <GL/freeglut.h>  
#define _USE_MATH_DEFINES
#include <math.h> 
#include "tgload.h"
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

// Constantes de la ventana
const int W_WIDTH = 1000;
const int W_HEIGHT = 640;

//Ángulo de rotación
float angulo = 0.0f;
float anguloy = 0.1f;
float anguloRotate = 0.0f;

//Vector de la cámara de dirección
float lx = 0.0f, ly = 0.1f, lz = -1.0f;

//Posiciones X, Y, Z de la cámara
float x = 0.0f, y = 0.5f, z = 4.5f;

// Ángulo de la pelota
float anguloPelota;
float ruedaPelota;
boolean pauseBall = false;

// Ángulos de la lámpara
float angBrazoInf = 45.0f;	// Subir y Bajar el Brazo inferior
float angBrazoSup = 135.0f;	// Subir y bajar Brazo superior
float angVertFoco = 0.0f;	// Subir y bajar Foco
float angHorizFoco = 0.0f;	// Derecha e izquierda Foco
float angBrazo = 0.0f;		// Giro de lámpara completa

// Propiedades de la lámpara
const float colLamp = 218.0f / 255.0f;
const float colBombilla = 204.0f / 255.0f;
const float longArms = 0.5f;
const float baseCono = 0.15f;
const float alturaCono = 0.3f;
const float baseBase = 0.3f;
const float alturaBase = 0.05f;
const float radioBombilla = 0.05f;
const float radioJuntas = 0.03f;

// Propiedades de la pelota
const float radPelota = 0.25f;

// Constantes para dibujar los circulos.
const double pi = M_PI;

// Propiedades de las luces
GLfloat lightx = -0.2f, lighty = 0.3f, lightz = 0.4f;
float colAmarilloB = 90.0f / 255.0f; // (255, 255, amarillo)
float colAmarilloG = 245.0f / 255.0f;
int shade = 1;
GLboolean luz0closed = false;
GLboolean luz1closed = false;
GLboolean luz2closed = true;

GLfloat diffuseLightColor0[] = { 1.0f, colAmarilloG, colAmarilloB, 1.0f };
GLfloat specularLightColor0[] = { 1.0f, colAmarilloG, colAmarilloB, 1.0f };

GLfloat lightPos1[] = { 0.0f, 8.0f, 0.0f, 1.0f }; // Posición luz1

//Variables de la luz 0 (foco)
static float spotAngle = 70.0f; // Ángulo
static float spotExponent = 2.0; // Atenuación

//Niebla
static float fog_color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
float fogDensity = 0.02f;
GLboolean AntiAliActive = true;

//Texturas
#define MAX_NO_TEXTURES 8
GLuint tex[MAX_NO_TEXTURES];

double toRadians(float i)
{
	double r = i * (pi / 180);
	return r;
}

// Función que inicializa las luces con sus parámetros
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

// Función que dibuja la pelota con su textura
void pelota()
{
	glPushMatrix();

	glTranslatef(0.55f, 0.0f, 0.0f); // Para que gire entorno a las letras
	glRotatef(anguloPelota, 0.0, 1.0, 0.0);
	glTranslatef(-0.5f, 0.0f, 0.0f);

	glTranslatef(0.5f, radPelota, -1.5f); // Para que gire sobre si misma (simula movimiento real)
	glRotatef(ruedaPelota, 0.0, 0.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, (int)GL_DECAL);
	

	glBindTexture(GL_TEXTURE_2D, tex[0]); // Usamos la textrura que se desea

	glFrontFace(GL_CCW);

	GLUquadric* p = gluNewQuadric();
	gluQuadricDrawStyle(p, GLU_FILL);

	gluQuadricTexture(p, GL_TRUE);

	gluSphere(p, radPelota, 40, 40); // Pintamos la pelota
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

// Función que dibuja una esfera para ver dónde está la luz en móvil (luz 2)
void bolaLuz() {
	glPushMatrix();
	glTranslatef(lightx, lighty, lightz); // Nos situamos en la posición de la luz

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, (int)GL_DECAL);

	glBindTexture(GL_TEXTURE_2D, tex[2]); // Seleccionamos la textura

	glFrontFace(GL_CCW);

	GLUquadric* p = gluNewQuadric();
	gluQuadricDrawStyle(p, GLU_FILL);

	gluQuadricTexture(p, GL_TRUE);

	gluSphere(p, 0.02, 40, 40); // Dibujamos la esfera
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

// Función que dibuja un cubo con textura
void cube(GLuint nro_da_textura, float x, float y, float z)
{
	// Desenha Cubo 1
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex[nro_da_textura]); // Seleccionamos la textura indicada
	float texSize = 1;
	glBegin(GL_QUADS);

	// Dibujamos las caras del cubo
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y, z);
	glTexCoord2f(texSize, 0.0f); glVertex3f(x, -y, z);
	glTexCoord2f(texSize, texSize); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, texSize); glVertex3f(-x, y, z);
	// Back Face
	glTexCoord2f(texSize, 0.0f); glVertex3f(-x, -y, -z);
	glTexCoord2f(texSize, texSize); glVertex3f(-x, y, -z);
	glTexCoord2f(0.0f, texSize); glVertex3f(x, y, -z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -y, -z);
	// Top Face
	glTexCoord2f(0.0f, texSize); glVertex3f(-x, y, -z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, y, z);
	glTexCoord2f(texSize, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(texSize, texSize); glVertex3f(x, y, -z);
	// Bottom Face
	glTexCoord2f(texSize, texSize); glVertex3f(-x, -y, -z);
	glTexCoord2f(0.0f, texSize); glVertex3f(x, -y, -z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -y, z);
	glTexCoord2f(texSize, 0.0f); glVertex3f(-x, -y, z);
	// Right face
	glTexCoord2f(texSize, 0.0f); glVertex3f(x, -y, -z);
	glTexCoord2f(texSize, texSize); glVertex3f(x, y, -z);
	glTexCoord2f(0.0f, texSize); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -y, z);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x, -y, -z);
	glTexCoord2f(texSize, 0.0f); glVertex3f(-x, -y, z);
	glTexCoord2f(texSize, texSize); glVertex3f(-x, y, z);
	glTexCoord2f(0.0f, texSize); glVertex3f(-x, y, -z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// Función que dibuja la letra P
void letraP() {
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(-0.6f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCylinder(0.07f, 0.55f, 50, 50);
	glTranslatef(0.6f, 0.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.49f, 0.385f, 0.0f);

	glutSolidTorus(0.065f, 0.11f, 10, 10);
	glTranslatef(0.5f, -0.37f, 0.0f);
	glPopMatrix();

	glPopMatrix();
}

// Función que dibuja la letra I
void letraI() {

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(0.0f, 0.02f, 0.0f);
	glScalef(0.4f, 0.04f, 0.15f);
	glutSolidCube(1.0);
	glTranslatef(0.0f, -0.02f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCylinder(0.07f, 0.5f, 50, 50);
	glTranslatef(0.0f, -0.25f, 0.0f);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0f, 0.52f, 0.0f);
	glScalef(0.4f, 0.04f, 0.15f);
	glutSolidCube(1.0);
	glTranslatef(0.0f, -0.52f, 0.0f);
	glPopMatrix();

	glPopMatrix();
}

// Función que dibuja la letra X
void letraX() {

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(0.4f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(28.0, 0.0, 1.0, 0.0);
	glutSolidCylinder(0.05f, 0.59f, 50, 50);
	glTranslatef(-0.4f, 0.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.67f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(-28.0, 0.0, 1.0, 0.0);
	glutSolidCylinder(0.05f, 0.59f, 50, 50);
	glTranslatef(-0.67f, 0.0f, 0.0f);
	glPopMatrix();

	glPopMatrix();
}

// Función que dibuja la letra A
void letraA() {

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(0.88f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(20.0, 0.0, 1.0, 0.0);
	glutSolidCylinder(0.05f, 0.55f, 50, 50);
	glTranslatef(-0.88f, 0.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.25f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(-20.0, 0.0, 1.0, 0.0);
	glutSolidCylinder(0.05f, 0.55f, 50, 50);
	glTranslatef(-1.25f, 0.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.95f, 0.18f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glutSolidCylinder(0.02f, 0.2f, 50, 50);
	glTranslatef(-0.95f, -0.18f, 0.0f);
	glPopMatrix();

	glPopMatrix();
}

// Función que dibuja la letra R
void letraR() {


	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);

	glPushMatrix();
	glTranslatef(1.5f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCylinder(0.07f, 0.55f, 50, 50);
	glTranslatef(-1.5f, 0.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.61f, 0.385f, 0.0f);

	glutSolidTorus(0.065f, 0.11f, 10, 10);
	glTranslatef(-1.61f, -0.385f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.75f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(-35.0, 0.0, 1.0, 0.0);
	glutSolidCylinder(0.05f, 0.3f, 50, 50);
	glTranslatef(-1.75f, 0.0f, 0.0f);
	glPopMatrix();


	glPopMatrix();
}

// Función que llama a todas las letras
void letras() {
	glPushMatrix();
	letraP();
	glPopMatrix();

	glPushMatrix();
	letraI();
	glPopMatrix();

	glPushMatrix();
	letraX();
	glPopMatrix();

	glPushMatrix();
	letraA();
	glPopMatrix();

	glPushMatrix();
	letraR();
	glPopMatrix();
}

// Función que dibuja una cuchara con textura de oro
void cuchara() {

	glPushMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(1.0f, 0.03f, 2.1f);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, (int)GL_DECAL);


	glBindTexture(GL_TEXTURE_2D, tex[4]); // Usamos la textrura que se desea

	glFrontFace(GL_CCW);

	GLUquadric* p = gluNewQuadric();
	gluQuadricDrawStyle(p, GLU_FILL);

	gluQuadricTexture(p, GL_TRUE);
	glutSolidTeaspoon(0.6); // Dibujamos la cuchara
	glDisable(GL_TEXTURE_2D);
	

	glPopMatrix();
}

// Función que dibuja la lámpara
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
	GLfloat lightPos0[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Posición de la luz 0
	float spotDirection0[] = { sin(toRadians(angHorizFoco)), 0.0f, -cos(toRadians(angVertFoco + 45)) };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0); // Actualizamos la posición de la luz0

	// Si la luz está encendida, deshabilitamos la interacción con la luz para que la bombilla se vea amarilla
	if (luz0closed == false) {
		glDisable(GL_LIGHTING);
	}
	glColor3f(colBombilla, colBombilla, 0.0f);
	glutSolidSphere(radioBombilla, 50, 50);
	glEnable(GL_LIGHTING);

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

// Función encargada de dibujar la escena
void Display(void) {

	GLfloat lightPos2[] = { lightx, lighty, lightz, 1.0f }; // Posición luz 2


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	// Establecer la vista de la cámara
	gluLookAt(x, y, z, // Posición donde se encuentra la cámara
		x + lx, y + ly, z + lz, // Posición donde mira la camara una vez situada
		0.0f, 1.0f, 0.0f);

	glRotatef(anguloRotate, 0.0, 1.0, 0.0); // Cuando rotemos la cámara, rotará la escena completa

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1); // Asignamos la posición de la luz 1 (luz global)

	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2); // Asignamos la posición de la luz 2 (luz roja que se mueve)

	if (!pauseBall) { // Incrementamos los ángulos
		anguloPelota += 0.15f;
		ruedaPelota += 0.6f;
	}

	// Dibujamos una esfera para conocer la posición de la luz 2
	glPushMatrix();
	bolaLuz();
	glPopMatrix();

	// Dibujamos el suelo de la escena
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	cube(1, 4.2f, 0.0f, 4.2f);
	glPopMatrix();

	// Dibujamos la pelota (luxo ball)
	glPushMatrix();
	pelota();
	glPopMatrix();

	// Dibujamos una figura en forma de cuchara con textura
	glPushMatrix();
	cuchara();
	glPopMatrix();

	// Dibujamos la caja de madera
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-1.0f, 0.3f, 2.0f);
	glRotatef(45, 0.0, 1.0, 0.0);
	cube(3, 0.3f, 0.3f, 0.3f);
	glPopMatrix();

	// Dibujamos las letras "PIXAR"
	letras();

	// Dibujamos la lámpara
	lampara();
	glEnd();
	glutSwapBuffers();
}

// Lectura de movimiento por teclado (flechas de dirección)
void lecturaFlechas(int key, int xx, int yy) {

	float fraccion = 0.1f;

	switch (key) {

	case GLUT_KEY_LEFT:		// Paneo de la cámara a la izquierda
		angulo -= 0.01f;
		lx = sin(angulo);
		lz = -cos(angulo);
		break;

	case GLUT_KEY_RIGHT:	// Paneo de la cámara a la derecha
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

// Lectura de movimiento por teclado
void lecturaEsc(unsigned char key, int xmouse, int ymouse)
{
	float fraccion = 0.01f;

	switch (key) {

	// Movimientos de la lámpara

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

	// Movimientos de la cámara

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

	// Interacción con las luces

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

		// Mover la luz 2 en ejex x, y, z
	case 'b': // Hacia la derecha
		lightx += 0.01f;
		break;

	case 'v': // Hacia la izquierda
		lightx -= 0.01f;
		break;

	case 'n': // Hacia arriba
		lighty += 0.01f;
		break;

	case 'm': // Hacia abajo
		lighty -= 0.01f;
		break;

	case 'o': // Hacia adelante
		lightz -= 0.01f;
		break;

	case 'l': // Hacia atrás
		lightz += 0.01f;
		break;

	// Diferentes posiciones de la cámara

	case '1':	// Reset Cámara (posición inicial)
		x = 0.0f, y = 0.5f, z = 4.5f;
		lx = 0.0f, ly = 0.1f, lz = -1.0f;
		angulo = 0.0f;
		anguloy = 0.1f;
		anguloRotate = 0.0f;
		break;

	case '2':	// Cámara 1
		x = 0.0f, y = 0.5f, z = 3.0f;
		lx = 0.0f, ly = 0.1f, lz = -1.0f;
		angulo = 0.0f;
		anguloy = 0.1f;
		anguloRotate = 0.0f;
		break;

	case '3':	// Cámara 2

		x = 0.0f, y = 7.0f, z = 0.0f;
		lx = 0.0f, ly = -10.0f, lz = -1.0f;
		angulo = 0.0f;
		anguloy = 0.1f;
		anguloRotate = 0.0f;
		break;

	case '4':	// Cámara 3
		x = 3.0f, y = 3.0f, z = 3.0f;
		lx = -3.0f, ly = -3.0f, lz = -3.0f;
		angulo = 0.0f;
		anguloy = 0.1f;
		anguloRotate = 0.0f;
		break;

	// Interacción con la niebla

	case '5': // Aumentar niebla
		if (fogDensity < 1.0) {
			fogDensity += 0.03;
			glFogf(GL_FOG_DENSITY, fogDensity);
		}
		break;

	case '6': // Disminuir niebla
		if (fogDensity > 0.02) {
			fogDensity -= 0.03;
			glFogf(GL_FOG_DENSITY, fogDensity);
		}
		break;

	// Interacción Anti-aliasing

	case '7': // Activar/Desactivar Anti-aliasing
		if (AntiAliActive) {
			glDisable(GL_MULTISAMPLE);
			AntiAliActive = false;
		}
		else {
			glEnable(GL_MULTISAMPLE);
			AntiAliActive = true;
		}
		break;

	// Interacción pelota

	case 'p': // Pausar/Reanudar Pelota
		if (pauseBall) {
			pauseBall = false;
		}
		else {
			pauseBall = true;
		}
		break;

	// Interacción alisado de las figuras (espacio)

	case 32:
		if (shade == 1) {
			glShadeModel(GL_FLAT); // Sin alisado
			shade++;
		}
		else {
			glShadeModel(GL_SMOOTH); // Con alisado
			shade--;
		}
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

// Inicialización del render de la escena
void initRender() {

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST); // Habilitamos el depth testing
	glEnable(GL_COLOR_MATERIAL); // Habilitamos los colores de los materiales

	glEnable(GL_LIGHTING); // Habilitamos las luces
	setLights();

	// Habilitamos el foco y la luz estática
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Asignamos las propiedades de los materiales de la escena
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);																																		//glNormal3f(0, -1, 0);

	// Inicializamos la niebla
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, fogDensity);
	glFogfv(GL_FOG_COLOR, fog_color);

	// Inicializamos las normales de los objetos y los reflejos
	glEnable(GL_NORMALIZE);
	glEnable(GL_SHADE_MODEL);
	glShadeModel(GL_SMOOTH);
}

// Función que se encarga de reescalar la escena según el tamaño de la ventana
void myReshape(int x, int y) {

	// Evitamos que el ancho y el alto de la escena sea 0
	if (y == 0 || x == 0) return;

	// Uso de la matriz de proyección
	glMatrixMode(GL_PROJECTION);

	// Reseteo de la matriz
	glLoadIdentity();

	// Se establece la perspectiva
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);

	// Volvemos al modelview
	glMatrixMode(GL_MODELVIEW);

	// Ventana gráfica completa
	glViewport(0, 0, x, y);
}

// Función que se encarga de cargar las texturas que se van a utilizar
void cargarTexturas() {

	image_t temp_image;
	// Enable de las texturas
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Definimos cuantas texturas queremos generar
	glGenTextures(1, tex);
	tex[0] = 1001;
	tex[1] = 1002;
	tex[2] = 1003;
	tex[3] = 1004;
	tex[4] = 1005;

	glBindTexture(GL_TEXTURE_2D, tex[0]);
	tgaLoad("img/luxojrdef.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);	// Textura de la pelota
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	tgaLoad("img/floor.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);		// Textura del suelo
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	tgaLoad("img/sun.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);		// Textura de la luz que se mueve
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	tgaLoad("img/box.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);		// Textura de la caja
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	tgaLoad("img/gold.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);		// Textura de la cuchara
	glDisable(GL_TEXTURE_2D);
}

// Función principal
int main(int argc, char** argv) {

	// Inicialización del glut y creación de la ventana
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE); // GLUT_MULTISAMPLE --> Anti-aliasing

	glutInitWindowPosition(200, 200); // Posición de la ventana
	glutInitWindowSize(W_WIDTH, W_HEIGHT); // Tamaño de la ventana
	glutCreateWindow("Etapa 6");


	initRender();
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glutDisplayFunc(Display);
	glutReshapeFunc(myReshape);
	glutIdleFunc(Display);
	glutKeyboardFunc(lecturaEsc);
	glutSpecialFunc(lecturaFlechas);
	cargarTexturas();

	glutMainLoop();
	return 0;
}