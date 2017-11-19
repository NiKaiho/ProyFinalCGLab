#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "time.h"  
#include <windows.h>
#include <mmsystem.h>

#include "cmodel/CModel.h"


//Solo para Visual Studio 2015

#if (_MSC_VER == 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

CCamera objCamera; 
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;


//Variables para el asenso y desenso del elevador
bool anima_elevador = false;
bool anima_elevadorS = false;
bool anima_elevadorB = false;
bool estado0 = true;

float movElevadorY = -14.0;


//Variables para la animación de puertas del elevador
bool anima_puerta = false;
bool abre_puerta = true;
bool cierra_puerta = false;

float puertder = 0.0;
float puertizq = 360.0;


//Variable para la animación de la fuente
float mov2 = 0.0;
float fishbody = 0.0;
float fishtail = 0.0;


float posX = 0.0;
float posY = 0.0;
float posXini = 0.0;
float Vini = 20.0;
float angulo = 45.0*3.1416 / 180;
//float angulo = 90.0;
float t = 0.0;
float g = 9.81;
bool anima = true;



//Variables para la animación del columpio
float rotcuerda1 = 180.0;
float rotcuerda2 = 180.0;
bool anima_columpio = false;
bool sube_columpio = false;
bool baja_columpio = false;


//Variables de rotación de los monitos
float rotbraizq = 0.0;
float rotbrader = 0.0;
float rotpier1 = -90.0;
float rotpier2 = 0.0;
float rotpier3 = 0.0;

float columpiakike = 0.0;
float columpiadylan = 0.0;

bool anima_monito = false;
bool monito_arriba = true;
bool monito_abajo = false;



GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

CTexture t_techoEdif;
CTexture t_pisoEdif;
CTexture t_edif2;
CTexture t_edif;	
CTexture text4;	//Pavimento
CTexture tj_pasto;	//Pasto01
CTexture tj_barda;	//Jardinera
CTexture tree;
CTexture tree2;
CTexture calle;

//Cielo
CTexture dia;
CTexture diatapa;


//Pisos
CTexture plano;
CTexture pisolab;
CTexture pisoblanco;


//Elevador
CTexture puertaelev;
CTexture metal;
CTexture metaloscuro;


//Muros y cristales
CTexture planomuro;
CTexture cristal;
CTexture cristalazul;
CTexture vitral;
CTexture vitral2;
CTexture concreto;

//Fuente
CTexture piedra;
CTexture repisa;
CTexture alga3;
CTexture agua;

CTexture piedrita;
CTexture venta;
CTexture adorno1;
CTexture castillo1;


//Columpios
CTexture metalrojo;
CTexture cuerda;
CTexture madera;


//Monito Enrique
CTexture torso;
CTexture torso2;
CTexture brazos;
CTexture piernas;


//Monito Dylan
CTexture torso3;


//Pez
CTexture cabezapez;
CTexture colapez;
CTexture escamas;
CTexture cuerpopez;



CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;

CFiguras fig7; //Para el monito
CFiguras cuarto;


//Modelos animacion
CModel carro1;




/////////////////////////////////////////////////////////////////////////////////////
//Animación Keyframes
//*******Frames coches.***************///////////////////////
float movCocheX = 2267.5, movCocheZ = 2295.0, giroY = -90.0f;

#define MAX_FRAMESC 18
int i_max_steps2 = 80;
int i_curr_steps2 = 0;

typedef struct _frame2
{
	//Variables para GUARDAR Key Frames
	float movCocheX;
	float movCocheZ;
	float giroY;
	float incGiroY;
	float incCocheX;
	float incCocheZ;;

}FRAMEC;

FRAMEC KeyFrameCo[MAX_FRAMESC];
bool play2 = false;
int playIx2 = 0;

///////********* Metodos Frame Coche ***********/

void resetElementCo(void)
{
	movCocheX = KeyFrameCo[0].movCocheX;
	movCocheZ = KeyFrameCo[0].movCocheZ;
	giroY = KeyFrameCo[0].giroY;

}

void interpolationCo(void)
{
	KeyFrameCo[playIx2].incGiroY = (KeyFrameCo[playIx2 + 1].giroY - KeyFrameCo[playIx2].giroY) / i_max_steps2;
	KeyFrameCo[playIx2].incCocheX = (KeyFrameCo[playIx2 + 1].movCocheX - KeyFrameCo[playIx2].movCocheX) / i_max_steps2;
	KeyFrameCo[playIx2].incCocheZ = (KeyFrameCo[playIx2 + 1].movCocheZ - KeyFrameCo[playIx2].movCocheZ) / i_max_steps2;

}



			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On
    
	//Configuración de texturas

	calle.LoadTGA("Texturas/calle.tga");
	calle.BuildGLTexture();
	calle.ReleaseImage();

	tree.LoadTGA("Texturas/tree01.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	tree2.LoadTGA("Texturas/tree02.tga");
	tree2.BuildGLTexture();
	tree2.ReleaseImage();

	dia.LoadTGA("Texturas/cielo.tga");
	dia.BuildGLTexture();
	dia.ReleaseImage();

	diatapa.LoadTGA("Texturas/tapa.tga");
	diatapa.BuildGLTexture();
	diatapa.ReleaseImage();

	// PISOS //

	plano.LoadTGA("Texturas/planoedificio.tga");
	plano.BuildGLTexture();
	plano.ReleaseImage();

	pisolab.LoadTGA("Texturas/piso2.tga");
	pisolab.BuildGLTexture();
	pisolab.ReleaseImage();

	pisoblanco.LoadTGA("Texturas/pisoblanco.tga");
	pisoblanco.BuildGLTexture();
	pisoblanco.ReleaseImage();

	// MUROS Y CRISTALES//

	cristal.LoadTGA("Texturas/cristal.tga");
	cristal.BuildGLTexture();
	cristal.ReleaseImage();

	cristalazul.LoadTGA("Texturas/cristalazul.tga");
	cristalazul.BuildGLTexture();
	cristalazul.ReleaseImage();

	planomuro.LoadTGA("Texturas/planomuro.tga");
	planomuro.BuildGLTexture();
	planomuro.ReleaseImage();

	concreto.LoadTGA("Texturas/concreto.tga");
	concreto.BuildGLTexture();
	concreto.ReleaseImage();

	vitral.LoadTGA("Texturas/vitral.tga");
	vitral.BuildGLTexture();
	vitral.ReleaseImage();

	vitral2.LoadTGA("Texturas/puerta.tga");
	vitral2.BuildGLTexture();
	vitral2.ReleaseImage();



	//Edificio
	t_techoEdif.LoadTGA("Texturas/piso2.tga");
	t_techoEdif.BuildGLTexture();
	t_techoEdif.ReleaseImage();

	t_pisoEdif.LoadTGA("Texturas/piso.tga");
	t_pisoEdif.BuildGLTexture();
	t_pisoEdif.ReleaseImage();

	t_edif.LoadTGA("Texturas/muro.tga");
	t_edif.BuildGLTexture();
	t_edif.ReleaseImage();

	t_edif2.LoadTGA("Texturas/muro2.tga");
	t_edif2.BuildGLTexture();
	t_edif2.ReleaseImage();



	//Jardineras
	tj_pasto.LoadTGA("Texturas/pasto.tga");
	tj_pasto.BuildGLTexture();
	tj_pasto.ReleaseImage();

	tj_barda.LoadTGA("Texturas/jardinera.tga");
	tj_barda.BuildGLTexture();
	tj_barda.ReleaseImage();


	//Elevador
	puertaelev.LoadTGA("Texturas/puertaelev.tga");
	puertaelev.BuildGLTexture();
	puertaelev.ReleaseImage();

	metal.LoadTGA("Texturas/metal.tga");
	metal.BuildGLTexture();
	metal.ReleaseImage();

	metaloscuro.LoadTGA("Texturas/metaloscuro.tga");
	metaloscuro.BuildGLTexture();
	metaloscuro.ReleaseImage();


	//Fuente
	piedra.LoadTGA("texturas/piedra4.tga");
	piedra.BuildGLTexture();
	piedra.ReleaseImage();

	repisa.LoadTGA("texturas/repisa.tga");
	repisa.BuildGLTexture();
	repisa.ReleaseImage();

	agua.LoadTGA("texturas/agua2.tga");
	agua.BuildGLTexture();
	agua.ReleaseImage();

	piedrita.LoadTGA("texturas/piedrita.tga");
	piedrita.BuildGLTexture();
	piedrita.ReleaseImage();

	venta.LoadTGA("texturas/venta.tga");
	venta.BuildGLTexture();
	venta.ReleaseImage();

	alga3.LoadTGA("texturas/alga3.tga");
	alga3.BuildGLTexture();
	alga3.ReleaseImage();

	adorno1.LoadTGA("texturas/adorno.tga");
	adorno1.BuildGLTexture();
	adorno1.ReleaseImage();

	castillo1.LoadTGA("texturas/castillo.tga");
	castillo1.BuildGLTexture();
	castillo1.ReleaseImage();

	//Columpios
	metalrojo.LoadTGA("Texturas/metalrojo.tga");
	metalrojo.BuildGLTexture();
	metalrojo.ReleaseImage();

	cuerda.LoadTGA("Texturas/cuerda.tga");
	cuerda.BuildGLTexture();
	cuerda.ReleaseImage();


	madera.LoadTGA("Texturas/madera.tga");
	madera.BuildGLTexture();
	madera.ReleaseImage();



	//Monito Enrique

	torso.LoadTGA("Texturas/torso.tga");
	torso.BuildGLTexture();
	torso.ReleaseImage();

	torso2.LoadTGA("Texturas/torso2.tga");
	torso2.BuildGLTexture();
	torso2.ReleaseImage();

	brazos.LoadTGA("Texturas/brazos.tga");
	brazos.BuildGLTexture();
	brazos.ReleaseImage();

	piernas.LoadTGA("Texturas/piernas.tga");
	piernas.BuildGLTexture();
	piernas.ReleaseImage();


	//Monito Dylan
	torso3.LoadTGA("Texturas/torso3.tga");
	torso3.BuildGLTexture();
	torso3.ReleaseImage();


	//Pez
	cabezapez.LoadTGA("Texturas/carapez.tga");
	cabezapez.BuildGLTexture();
	cabezapez.ReleaseImage();

	escamas.LoadTGA("Texturas/escamas.tga");
	escamas.BuildGLTexture();
	escamas.ReleaseImage();

	colapez.LoadTGA("Texturas/colapez.tga");
	colapez.BuildGLTexture();
	colapez.ReleaseImage();

	cuerpopez.LoadTGA("Texturas/cuerpopez.tga");
	cuerpopez.BuildGLTexture();
	cuerpopez.ReleaseImage();



	//Carga de Figuras
	carro1._3dsLoad("models/PoliceCar.3ds");
	carro1.LoadTextureImages();
	carro1.GLIniTextures();
	carro1.ReleaseTextureImages();
	

	///////////////////////////////////////////////////
	////////**********Coche****************/////////
	KeyFrameCo[0].movCocheX = 2267.50;
	KeyFrameCo[0].movCocheZ = 2295.0;
	KeyFrameCo[0].giroY = -90.0;

	KeyFrameCo[1].movCocheX = 2017.50;
	KeyFrameCo[1].movCocheZ = 2270.0;
	KeyFrameCo[1].giroY = -111.0;

	KeyFrameCo[2].movCocheX = 1837.0;
	KeyFrameCo[2].movCocheZ = 2132.50;
	KeyFrameCo[2].giroY = -130.50;

	KeyFrameCo[3].movCocheX = 1679.0;
	KeyFrameCo[3].movCocheZ = 1875.0;
	KeyFrameCo[3].giroY = -141.0;

	KeyFrameCo[4].movCocheX = 1465.50;
	KeyFrameCo[4].movCocheZ = 1627.50;
	KeyFrameCo[4].giroY = -127.50;

	KeyFrameCo[5].movCocheX = 1122.0;
	KeyFrameCo[5].movCocheZ = 1555.0;
	KeyFrameCo[5].giroY = -93.0;

	KeyFrameCo[6].movCocheX = 784.50;
	KeyFrameCo[6].movCocheZ = 1575.0;
	KeyFrameCo[6].giroY = -63.0;

	KeyFrameCo[7].movCocheX = 581.0;
	KeyFrameCo[7].movCocheZ = 1720.0;
	KeyFrameCo[7].giroY = -42.0;

	KeyFrameCo[8].movCocheX = 507.50;
	KeyFrameCo[8].movCocheZ = 1977.50;
	KeyFrameCo[8].giroY = -12.0;

	KeyFrameCo[9].movCocheX = 507.50;
	KeyFrameCo[9].movCocheZ = 2505.50;
	KeyFrameCo[9].giroY = 21.0;

	KeyFrameCo[10].movCocheX = 663.50;
	KeyFrameCo[10].movCocheZ = 2695.0;
	KeyFrameCo[10].giroY = 55.50;

	KeyFrameCo[11].movCocheX = 741.50;
	KeyFrameCo[11].movCocheZ = 2695.0;
	KeyFrameCo[11].giroY = 88.50;

	KeyFrameCo[12].movCocheX = 858.50;
	KeyFrameCo[12].movCocheZ = 2610.0;
	KeyFrameCo[12].giroY = 117.0;

	KeyFrameCo[13].movCocheX = 930.50;
	KeyFrameCo[13].movCocheZ = 2457.50;
	KeyFrameCo[13].giroY = 181.50;

	KeyFrameCo[14].movCocheX = 829.0;
	KeyFrameCo[14].movCocheZ = 2327.0;
	KeyFrameCo[14].giroY = 219.0;

	KeyFrameCo[15].movCocheX = 559.50;
	KeyFrameCo[15].movCocheZ = 2327.50;
	KeyFrameCo[15].giroY = 267.0;

	KeyFrameCo[16].movCocheX = 43.0;
	KeyFrameCo[16].movCocheZ = 2320.0;
	KeyFrameCo[16].giroY = 268.50;

	KeyFrameCo[17].movCocheX = -163.50;
	KeyFrameCo[17].movCocheZ = 2320.0;
	KeyFrameCo[17].giroY = 268.50;



	//////----------Camara--------//////////////7
	objCamera.Position_Camera(1060, 100, 2000, 1060, 100, 1997, 0, 1, 0);


}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}


	
void arbol_alpha(GLuint text)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void Enrique()
{
	//monito

	//Torso
	glPushMatrix();
	glTranslatef(0.0, -4.5, 0.0);
	fig1.prisma6(5.0, 2.0, 1.0, torso.GLindex, torso2.GLindex, torso2.GLindex, torso2.GLindex);
	glPopMatrix();

	//Hombros
	//Derecho
	glPushMatrix();
	glTranslatef(1.25, -3.0, 0.0);
	//glColor3f(0.0, 0.007, 0.337);
	fig1.prisma(1.0, 0.5, 0.25, torso2.GLindex);
	glPopMatrix();

	//Izquierdo
	glPushMatrix();
	glTranslatef(-1.25, -3.0, 0.0);
	//glColor3f(0.0, 0.007, 0.337);
	fig1.prisma(1.0, 0.5, 0.25, torso2.GLindex);
	glPopMatrix();

	//Brazos
	//Derecho
	glPushMatrix();
	glTranslatef(1.5, -3.0, 0.0);
	glRotatef(rotbrader, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	//glColor3f(1.0, 0.788, 0.239);
	fig1.prisma(1.0, 2.0, 0.25, brazos.GLindex);
	glPopMatrix();

	//Izquierdo
	glPushMatrix();
	glTranslatef(-1.5, -3.0, 0.0);
	glRotatef(rotbraizq, 0.0, 0.0, 1.0);
	glTranslatef(-1.0, 0.0, 0.0);
	//glColor3f(1.0, 0.788, 0.239);
	fig1.prisma(1.0, 2.0, 0.25, brazos.GLindex);
	glPopMatrix();


	//Piernas
	//Derecha
	glPushMatrix();
	glTranslatef(0.5, -7.5, 0.0);
	glRotatef(rotpier1, 1.0, 0.0, 0.0);
	glRotatef(rotpier2, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.75, 0.0);
	fig1.prisma3(3.5, 1.0, 1.0, piernas.GLindex, brazos.GLindex);
	glPopMatrix();


	//Izquierda
	glPushMatrix();
	glTranslatef(-0.5, -7.5, 0.0);
	glRotatef(rotpier1, 1.0, 0.0, 0.0);
	glRotatef(rotpier3, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.75, 0.0);
	/*glColor3f(0.478, 0.188, 0.011);*/
	fig1.prisma3(3.5, 1.0, 1.0, piernas.GLindex, brazos.GLindex);
	glPopMatrix();
}

void Dylan()
{
	//monito
	//Torso
	glPushMatrix();
	glTranslatef(0.0, -4.5, 0.0);
	fig1.prisma6(5.0, 2.0, 1.0, torso3.GLindex, 0, 0, 0);
	glPopMatrix();

	//Hombros
	//Derecho
	glPushMatrix();
	glTranslatef(1.25, -3.0, 0.0);
	//glColor3f(0.0, 0.007, 0.337);
	fig1.prisma(1.0, 0.5, 0.25, 0);
	glPopMatrix();

	//Izquierdo
	glPushMatrix();
	glTranslatef(-1.25, -3.0, 0.0);
	//glColor3f(0.0, 0.007, 0.337);
	fig1.prisma(1.0, 0.5, 0.25, 0);
	glPopMatrix();

	//Brazos
	//Derecho
	glPushMatrix();
	glTranslatef(1.5, -3.0, 0.0);
	glRotatef(rotbrader, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	//glColor3f(1.0, 0.788, 0.239);
	fig1.prisma(1.0, 2.0, 0.25, brazos.GLindex);
	glPopMatrix();

	//Izquierdo
	glPushMatrix();
	glTranslatef(-1.5, -3.0, 0.0);
	glRotatef(rotbraizq, 0.0, 0.0, 1.0);
	glTranslatef(-1.0, 0.0, 0.0);
	//glColor3f(1.0, 0.788, 0.239);
	fig1.prisma(1.0, 2.0, 0.25, brazos.GLindex);
	glPopMatrix();


	//Piernas
	//Derecha
	glPushMatrix();
	glTranslatef(0.5, -7.5, 0.0);
	glRotatef(rotpier1, 1.0, 0.0, 0.0);
	glRotatef(rotpier2, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.75, 0.0);
	fig1.prisma3(3.5, 1.0, 1.0, piernas.GLindex, brazos.GLindex);
	glPopMatrix();


	//Izquierda
	glPushMatrix();
	glTranslatef(-0.5, -7.5, 0.0);
	glRotatef(rotpier1, 1.0, 0.0, 0.0);
	glRotatef(rotpier3, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.75, 0.0);
	/*glColor3f(0.478, 0.188, 0.011);*/
	fig1.prisma3(3.5, 1.0, 1.0, piernas.GLindex, brazos.GLindex);
	glPopMatrix();
}

void columpios()
{
	glPushMatrix();
	//Columpio
	//Barrotes izquierdos
	glPushMatrix();
	glTranslatef(-10.0, 0.0, 0.0);
	glRotatef(170.0, 1.0, 0.0, 0.0);
	fig1.cilindro(0.25, 20.0, 50.0, metalrojo.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.0, 0.0, 0.0);
	glRotatef(-170.0, 1.0, 0.0, 0.0);
	fig1.cilindro(0.25, 20.0, 50.0, metalrojo.GLindex);
	glPopMatrix();

	//Barrotes derechos
	glPushMatrix();
	glTranslatef(10.0, 0.0, 0.0);
	glRotatef(170.0, 1.0, 0.0, 0.0);
	fig1.cilindro(0.25, 20.0, 50.0, metalrojo.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, 0.0, 0.0);
	glRotatef(-170.0, 1.0, 0.0, 0.0);
	fig1.cilindro(0.25, 20.0, 50.0, metalrojo.GLindex);
	glPopMatrix();

	//Barrote superior
	glPushMatrix();
	glTranslatef(10.0, 0.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	fig1.cilindro(0.25, 20.0, 50.0, metalrojo.GLindex);
	glPopMatrix();


	//Asientos
	//Cuerda. Columpio 1	
	glPushMatrix();
	glTranslatef(-2.0, 0.0, 0.0);
	glRotatef(rotcuerda1, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	fig1.cilindro(0.05, 12.5, 50.0, cuerda.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef(rotcuerda2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	fig1.cilindro(0.05, 12.5, 50.0, cuerda.GLindex);
	glPopMatrix();

	//Tabla
	glPushMatrix();
	glTranslatef(-4.0, 0.0, 0.0);
	glRotatef(rotcuerda1, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 12.5, 0.0);
	fig1.prisma(0.2, 4.5, 1.0, madera.GLindex);
	glPopMatrix();


	//Cuerda. Columpio 2
	glPushMatrix();
	glTranslatef(-6.0, 0.0, 0.0);
	glRotatef(rotcuerda1, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	fig1.cilindro(0.05, 12.5, 50.0, cuerda.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.0, 0.0, 0.0);
	glRotatef(rotcuerda2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	fig1.cilindro(0.05, 12.5, 50.0, cuerda.GLindex);
	glPopMatrix();

	//Tabla
	glPushMatrix();
	glTranslatef(4.0, 0.0, 0.0);
	glRotatef(rotcuerda2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 12.5, 0.0);
	fig1.prisma(0.2, 4.5, 1.0, madera.GLindex);
	glPopMatrix();

	//Monito Enrique
	glPushMatrix();
	glTranslatef(-3.8, 0.0, 0.0);
	glRotatef(columpiakike, 1.0, 0.0, 0.0);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glScalef(0.8, 0.8, 0.8);
	glTranslatef(0.0, -7.5, 0.0);
	Enrique();
	glPopMatrix();

	//Monito Dylan
	glPushMatrix();
	glTranslatef(3.8, 0.0, 0.0);
	glRotatef(columpiadylan, 1.0, 0.0, 0.0);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	glScalef(0.8, 0.8, 0.8);
	glTranslatef(0.0, -7.5, 0.0);
	Dylan();
	glPopMatrix();


	glPopMatrix();
}


void alga()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, alga3.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}


void adorno()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, adorno1.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}


void castillo()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, castillo1.GLindex);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}


void fuente()
{

	glPushMatrix();

	glPushMatrix();
	glTranslatef(1060, 473, 1040);
	glScalef(0.5, 1.0, 0.5);
	alga();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(1050, 473, 1085);
	glScalef(0.5, 1.0, 0.5);
	adorno();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1050, 473, 1060);
	glScalef(0.5, 1.0, 1.0);
	castillo();
	glPopMatrix();//////// estas lineas hay que ponerlas despues no van aqui

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 500, 1030);
	glTexCoord2f(0.0, 2.0); glVertex3f(1060, 560, 1030);
	glTexCoord2f(3.0, 2.0); glVertex3f(1060, 560, 1095);
	glTexCoord2f(3.0, 0.0); glVertex3f(1060, 500, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	////////////atras
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1065, 500, 1030);
	glTexCoord2f(0.0, 2.0); glVertex3f(1065, 560, 1030);
	glTexCoord2f(3.0, 2.0); glVertex3f(1065, 560, 1095);
	glTexCoord2f(3.0, 0.0); glVertex3f(1065, 500, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1065, 500, 1030);
	glTexCoord2f(0.0, 2.0); glVertex3f(1065, 560, 1030);
	glTexCoord2f(0.5, 2.0); glVertex3f(1060, 560, 1030);
	glTexCoord2f(0.5, 0.0); glVertex3f(1060, 500, 1030);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1065, 500, 1095);
	glTexCoord2f(0.0, 2.0); glVertex3f(1065, 560, 1095);
	glTexCoord2f(0.5, 2.0); glVertex3f(1060, 560, 1095);
	glTexCoord2f(0.5, 0.0); glVertex3f(1060, 500, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 560, 1030);
	glTexCoord2f(0.0, 1.0); glVertex3f(1065, 560, 1030);
	glTexCoord2f(1.0, 1.0); glVertex3f(1065, 560, 1095);
	glTexCoord2f(1.0, 0.0); glVertex3f(1060, 560, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 500, 1030);
	glTexCoord2f(0.0, 1.0); glVertex3f(1065, 500, 1030);
	glTexCoord2f(1.0, 1.0); glVertex3f(1065, 500, 1095);
	glTexCoord2f(1.0, 0.0); glVertex3f(1060, 500, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();


	///////////repisas-----------------------------------------------------
	glPushMatrix();///1
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 550, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 550, 1070);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 550, 1070);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 550, 1040);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//////////2
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 552, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 552, 1070);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 552, 1070);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 552, 1040);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////////////3
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 550, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 552, 1040);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 552, 1040);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 550, 1040);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//////////4
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 550, 1070);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 552, 1070);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 552, 1070);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 550, 1070);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////5
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1055, 550, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1055, 552, 1040);
	glTexCoord2f(2.0, 0.5); glVertex3f(1055, 552, 1070);
	glTexCoord2f(2.0, 0.0); glVertex3f(1055, 550, 1070);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();


	///////////repisas 2
	glPushMatrix();///////1
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 540, 1055);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 540, 1085);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 540, 1085);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 540, 1055);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//////////2
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 542, 1055);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 542, 1085);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 542, 1085);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 542, 1055);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////////////3
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 540, 1055);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 542, 1055);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 542, 1055);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 540, 1055);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////////////4
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 540, 1085);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 542, 1085);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 542, 1085);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 540, 1085);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////5
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1055, 540, 1055);
	glTexCoord2f(0.0, 0.5); glVertex3f(1055, 542, 1055);
	glTexCoord2f(2.0, 0.5); glVertex3f(1055, 542, 1085);
	glTexCoord2f(2.0, 0.0); glVertex3f(1055, 540, 1085);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	///////////repisas 3
	glPushMatrix();////////////1
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 530, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 530, 1070);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 530, 1070);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 530, 1040);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();/////////////2
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 532, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 532, 1070);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 532, 1070);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 532, 1040);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////////////3
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 530, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 532, 1040);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 532, 1040);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 530, 1040);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////////////4
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 530, 1070);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 532, 1070);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 532, 1070);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 530, 1070);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////5
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1055, 530, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1055, 532, 1040);
	glTexCoord2f(2.0, 0.5); glVertex3f(1055, 532, 1070);
	glTexCoord2f(2.0, 0.0); glVertex3f(1055, 530, 1070);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	///////////repisas 4
	glPushMatrix();//////////1
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 520, 1055);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 520, 1085);
	glTexCoord2f(1.0, 1.0); glVertex3f(1055, 520, 1085);
	glTexCoord2f(1.0, 0.0); glVertex3f(1055, 520, 1055);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//////////2
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 522, 1055);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 522, 1085);
	glTexCoord2f(1.0, 1.0); glVertex3f(1055, 522, 1085);
	glTexCoord2f(1.0, 0.0); glVertex3f(1055, 522, 1055);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////////////3
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 520, 1055);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 522, 1055);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 522, 1055);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 520, 1055);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////////////4
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 520, 1085);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 522, 1085);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 522, 1085);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 520, 1085);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////5
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1055, 520, 1055);
	glTexCoord2f(0.0, 0.5); glVertex3f(1055, 522, 1055);
	glTexCoord2f(2.0, 0.5); glVertex3f(1055, 522, 1085);
	glTexCoord2f(2.0, 0.0); glVertex3f(1055, 520, 1085);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	///////////repisas  5
	glPushMatrix();///////////1
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 510, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 510, 1070);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 510, 1070);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 510, 1040);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////2
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 512, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 512, 1070);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 512, 1070);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 512, 1040);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////////////3
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 510, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 512, 1040);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 512, 1040);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 510, 1040);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////////////4
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 510, 1070);
	glTexCoord2f(0.0, 0.5); glVertex3f(1060, 512, 1070);
	glTexCoord2f(0.5, 0.5); glVertex3f(1055, 512, 1070);
	glTexCoord2f(0.5, 0.0); glVertex3f(1055, 510, 1070);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();///////////5
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, repisa.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1055, 510, 1040);
	glTexCoord2f(0.0, 0.5); glVertex3f(1055, 512, 1040);
	glTexCoord2f(2.0, 0.5); glVertex3f(1055, 512, 1070);
	glTexCoord2f(2.0, 0.0); glVertex3f(1055, 510, 1070);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	///////////agua repisas

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 - mov2); glVertex3f(1060, 552.1, 1045);
	glTexCoord2f(0.0, 0.5 - mov2); glVertex3f(1060, 552.1, 1070.1);
	glTexCoord2f(0.5, 0.5 - mov2); glVertex3f(1055, 552.1, 1070.1);
	glTexCoord2f(0.5, 0.0 - mov2); glVertex3f(1055, 552.1, 1045);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 - mov2); glVertex3f(1060, 552.1, 1070.1);
	glTexCoord2f(0.0, 0.5 - mov2); glVertex3f(1060, 551.6, 1070.3);
	glTexCoord2f(0.5, 0.5 - mov2); glVertex3f(1055, 551.6, 1070.3);
	glTexCoord2f(0.5, 0.0 - mov2); glVertex3f(1055, 552.1, 1070.1);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 - mov2); glVertex3f(1060, 551.6, 1070.3);
	glTexCoord2f(0.0, 0.5 - mov2); glVertex3f(1060, 542.05, 1070.3);
	glTexCoord2f(0.5, 0.5 - mov2); glVertex3f(1055, 542.05, 1070.3);
	glTexCoord2f(0.5, 0.0 - mov2); glVertex3f(1055, 551.6, 1070.3);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1060, 542.05, 1054.8);
	glTexCoord2f(0.0, 0.5 + mov2); glVertex3f(1060, 542.05, 1070.3);
	glTexCoord2f(0.5, 0.5 + mov2); glVertex3f(1055, 542.05, 1070.3);
	glTexCoord2f(0.5, 0.0 + mov2); glVertex3f(1055, 542.05, 1054.8);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1060, 541.8, 1054.4);
	glTexCoord2f(0.0, 0.5 + mov2); glVertex3f(1060, 542.05, 1054.8);
	glTexCoord2f(0.5, 0.5 + mov2); glVertex3f(1055, 542.05, 1054.8);
	glTexCoord2f(0.5, 0.0 + mov2); glVertex3f(1055, 541.8, 1054.4);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 - mov2); glVertex3f(1060, 541.8, 1054.4);
	glTexCoord2f(0.0, 0.5 - mov2); glVertex3f(1060, 532.05, 1054.4);
	glTexCoord2f(0.5, 0.5 - mov2); glVertex3f(1055, 532.05, 1054.4);
	glTexCoord2f(0.5, 0.0 - mov2); glVertex3f(1055, 541.8, 1054.4);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 - mov2); glVertex3f(1060, 541.8, 1054.4);
	glTexCoord2f(0.0, 0.5 - mov2); glVertex3f(1060, 532.05, 1054.4);
	glTexCoord2f(0.5, 0.5 - mov2); glVertex3f(1055, 532.05, 1054.4);
	glTexCoord2f(0.5, 0.0 - mov2); glVertex3f(1055, 541.8, 1054.4);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 - mov2); glVertex3f(1060, 532.05, 1054.4);
	glTexCoord2f(0.0, 0.5 - mov2); glVertex3f(1060, 532.05, 1070.2);
	glTexCoord2f(0.5, 0.5 - mov2); glVertex3f(1055, 532.05, 1070.2);
	glTexCoord2f(0.5, 0.0 - mov2); glVertex3f(1055, 532.05, 1054.4);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 - mov2); glVertex3f(1060, 532.05, 1070.2);
	glTexCoord2f(0.0, 0.5 - mov2); glVertex3f(1060, 531.8, 1070.6);
	glTexCoord2f(0.5, 0.5 - mov2); glVertex3f(1055, 531.8, 1070.6);
	glTexCoord2f(0.5, 0.0 - mov2); glVertex3f(1055, 532.05, 1070.2);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1055, 522.05, 1070.6);
	glTexCoord2f(0.0, 0.5 + mov2); glVertex3f(1055, 532.05, 1070.6);
	glTexCoord2f(0.5, 0.5 + mov2); glVertex3f(1060, 532.05, 1070.6);
	glTexCoord2f(0.5, 0.0 + mov2); glVertex3f(1060, 522.05, 1070.6);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1060, 522.05, 1054.8);
	glTexCoord2f(0.0, 0.5 + mov2); glVertex3f(1060, 522.05, 1070.6);
	glTexCoord2f(0.5, 0.5 + mov2); glVertex3f(1055, 522.05, 1070.6);
	glTexCoord2f(0.5, 0.0 + mov2); glVertex3f(1055, 522.05, 1054.8);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1060, 521.8, 1054.6);
	glTexCoord2f(0.0, 0.5 + mov2); glVertex3f(1060, 522.05, 1054.8);
	glTexCoord2f(0.5, 0.5 + mov2); glVertex3f(1055, 522.05, 1054.8);
	glTexCoord2f(0.5, 0.0 + mov2); glVertex3f(1055, 521.8, 1054.6);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1060, 512.1, 1054.6);
	glTexCoord2f(0.0, 0.5 + mov2); glVertex3f(1060, 521.8, 1054.6);
	glTexCoord2f(0.5, 0.5 + mov2); glVertex3f(1055, 521.8, 1054.6);
	glTexCoord2f(0.5, 0.0 + mov2); glVertex3f(1055, 512.1, 1054.6);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 - mov2); glVertex3f(1060, 512.1, 1054.6);
	glTexCoord2f(0.0, 0.5 - mov2); glVertex3f(1060, 512.1, 1070.2);
	glTexCoord2f(0.5, 0.5 - mov2); glVertex3f(1055, 512.1, 1070.2);
	glTexCoord2f(0.5, 0.0 - mov2); glVertex3f(1055, 512.1, 1054.6);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1060, 511.8, 1070.4);
	glTexCoord2f(0.0, 0.5 + mov2); glVertex3f(1060, 512.1, 1070.2);
	glTexCoord2f(0.5, 0.5 + mov2); glVertex3f(1055, 512.1, 1070.2);
	glTexCoord2f(0.5, 0.0 + mov2); glVertex3f(1055, 511.8, 1070.4);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();




	////////////////////////////////////////////////////////////////


	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 470, 1030);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 500, 1030);
	glTexCoord2f(3.0, 1.0); glVertex3f(1060, 500, 1095);
	glTexCoord2f(3.0, 0.0); glVertex3f(1060, 470, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	////////////atras
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1065, 470, 1030);
	glTexCoord2f(0.0, 1.0); glVertex3f(1065, 500, 1030);
	glTexCoord2f(3.0, 1.0); glVertex3f(1065, 500, 1095);
	glTexCoord2f(3.0, 0.0); glVertex3f(1065, 470, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1065, 470, 1030);
	glTexCoord2f(0.0, 1.0); glVertex3f(1065, 500, 1030);
	glTexCoord2f(0.5, 1.0); glVertex3f(1060, 500, 1030);
	glTexCoord2f(0.5, 0.0); glVertex3f(1060, 470, 1030);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1065, 470, 1095);
	glTexCoord2f(0.0, 1.0); glVertex3f(1065, 500, 1095);
	glTexCoord2f(0.5, 1.0); glVertex3f(1060, 500, 1095);
	glTexCoord2f(0.5, 0.0); glVertex3f(1060, 470, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//////////////////-------------------------------------------------------------------------------------------------------------------------}

	////////////parte agua izq
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 470, 1030);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 500, 1030);
	glTexCoord2f(1.0, 1.0); glVertex3f(1045, 500, 1030);
	glTexCoord2f(1.0, 0.0); glVertex3f(1045, 470, 1030);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	////////////
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 470, 1035);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 500, 1035);
	glTexCoord2f(1.0, 1.0); glVertex3f(1045, 500, 1035);
	glTexCoord2f(1.0, 0.0); glVertex3f(1045, 470, 1035);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	/////////////frente
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1045, 500, 1030);
	glTexCoord2f(0.0, 1.0); glVertex3f(1045, 470, 1030);
	glTexCoord2f(0.5, 1.0); glVertex3f(1045, 470, 1035);
	glTexCoord2f(0.5, 0.0); glVertex3f(1045, 500, 1035);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//////////////arriba brazos

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1045, 500, 1030);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 500, 1030);
	glTexCoord2f(0.5, 1.0); glVertex3f(1060, 500, 1035);
	glTexCoord2f(0.5, 0.0); glVertex3f(1045, 500, 1035);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//////////// der
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 470, 1090);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 500, 1090);
	glTexCoord2f(1.0, 1.0); glVertex3f(1045, 500, 1090);
	glTexCoord2f(1.0, 0.0); glVertex3f(1045, 470, 1090);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	////////////
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1060, 470, 1095);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 500, 1095);
	glTexCoord2f(1.0, 1.0); glVertex3f(1045, 500, 1095);
	glTexCoord2f(1.0, 0.0); glVertex3f(1045, 470, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	////frente der
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1045, 470, 1095);
	glTexCoord2f(0.0, 1.0); glVertex3f(1045, 500, 1095);
	glTexCoord2f(0.5, 1.0); glVertex3f(1045, 500, 1090);
	glTexCoord2f(0.5, 0.0); glVertex3f(1045, 470, 1090);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedra.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1045, 500, 1090);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 500, 1090);
	glTexCoord2f(0.5, 1.0); glVertex3f(1060, 500, 1095);
	glTexCoord2f(0.5, 0.0); glVertex3f(1045, 500, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	///////////////////////////////////////////////////////////////////////

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, piedrita.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1045, 473, 1035);
	glTexCoord2f(0.0, 1.0); glVertex3f(1060, 473, 1035);
	glTexCoord2f(2.0, 1.0); glVertex3f(1060, 473, 1095);
	glTexCoord2f(2.0, 0.0); glVertex3f(1045, 473, 1095);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//////////////////agua    
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1045.2, 495, 1035);
	glTexCoord2f(0.0, 1.0 + mov2); glVertex3f(1060, 495, 1035);
	glTexCoord2f(1.0, 1.0 + mov2); glVertex3f(1060, 495, 1090);
	glTexCoord2f(1.0, 0.0 + mov2); glVertex3f(1045.2, 495, 1090);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//////////////////agua    
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1045.2, 473, 1035);
	glTexCoord2f(0.0, 1.0 + mov2); glVertex3f(1045.2, 495, 1035);
	glTexCoord2f(1.0, 1.0 + mov2); glVertex3f(1045.2, 495, 1090);
	glTexCoord2f(1.0, 0.0 + mov2); glVertex3f(1045.2, 473, 1090);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//////////////////vidrio 
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, venta.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1045, 473, 1035);
	glTexCoord2f(0.0, 1.0); glVertex3f(1045, 500, 1035);
	glTexCoord2f(1.0, 1.0); glVertex3f(1045, 500, 1090);
	glTexCoord2f(1.0, 0.0); glVertex3f(1045, 473, 1090);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, agua.GLindex);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0 + mov2); glVertex3f(1055, 495, 1070.2);
	glTexCoord2f(0.0, 0.5 + mov2); glVertex3f(1055, 511.8, 1070.2);
	glTexCoord2f(0.5, 0.5 + mov2); glVertex3f(1060, 511.8, 1070.2);
	glTexCoord2f(0.5, 0.0 + mov2); glVertex3f(1060, 495, 1070.2);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();





	glPopMatrix();

}

void elevador()
{
	//Elevador
	glPushMatrix();

		glPushMatrix;
			fig1.prisma(1.0, 20.0, 20.0, metal.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 41.0, 0.0);
			fig1.prisma(1.0, 20.0, 20.0, metal.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-9.5, 20.5, 0.0);
			fig1.prisma(40.0, 1.0, 20.0, metal.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(9.5, 20.5, 0.0);
			fig1.prisma(40.0, 1.0, 20.0, metal.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 20.5, -9.5);
			fig1.prisma(40.0, 18.0, 1.0, metal.GLindex);
		glPopMatrix();

		//Puertas elevador
			//Izquierda
		glPushMatrix();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			glTranslatef(-9.5, 0.0, 9.5);
				glRotatef(puertizq, 0.0, 1.0, 0.0);
				glTranslatef(4.75, 8.0, 0.0);
				fig1.prisma(15.0, 9.5, 0.1, puertaelev.GLindex);
				glDisable(GL_ALPHA_TEST);
		glPopMatrix();


			//Derecha
		glPushMatrix();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			glTranslatef(9.5, 0.0, 9.5);
				glRotatef(puertder, 0.0, 1.0, 0.0);
				glTranslatef(-4.75, 8.0, 0.0);
				fig1.prisma(15.0, 9.5, 0.1, puertaelev.GLindex);
				glDisable(GL_ALPHA_TEST);
		glPopMatrix();

	glPopMatrix();
}

void muropalomas()
{
	//Muro de palomas

	glPushMatrix();
	fig1.prisma(4.0, 15.5, 0.5, t_edif.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13.25, 0.0, 0.0);
	fig1.prisma(4.0, 6.0, 0.5, t_edif.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13.25, 5.75, 0.0);
	fig1.prisma(15.5, 8.0, 0.5, t_edif.GLindex);
	glPopMatrix();



	//Concreto
	glPushMatrix();
	glTranslatef(0.0, 2.5, 0.25);
	fig1.prisma(1.0, 15.5, 1.0, t_edif2.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13.25, 2.5, 0.25);
	fig1.prisma(1.0, 6.0, 1.0, t_edif2.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.0, 5.75, 0.25);
	fig1.prisma(15.5, 2.5, 1.0, t_edif.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.5, 5.75, 0.25);
	fig1.prisma(15.5, 1.5, 1.0, t_edif.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -3.0, 0.5);
	fig1.prisma(2.0, 33.6, 0.5, t_edif2.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 14.5, 0.25);
	fig1.prisma(2.0, 33.6, 1.0, t_edif2.GLindex);
	glPopMatrix();




	//Ventanas
	//Protecciones
	glPushMatrix();
	glTranslatef(16.125, 8.0, -0.125);
	fig1.prisma(10.0, 0.25, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.38, 8.0, -0.125);
	fig1.prisma(10.0, 0.25, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13.25, 13.25, -0.125);
	fig1.prisma(0.5, 6.0, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13.25, 9.5, -0.125);
	fig1.prisma(0.5, 5.5, 0.25, metal.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(7.625, 8.0, -0.125);
	fig1.prisma(10.0, 0.25, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.625, 8.0, -0.125);
	fig1.prisma(10.0, 0.25, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 13.25, -0.125);
	fig1.prisma(0.5, 15.5, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 8.0, -0.125);
	fig1.prisma(10.0, 0.25, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, 8.0, -0.125);
	fig1.prisma(10.0, 0.25, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.3125, 9.5, -0.125);
	fig1.prisma(0.5, 4.375, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.3125, 9.5, -0.125);
	fig1.prisma(0.5, 4.375, 0.25, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 9.5, -0.125);
	fig1.prisma(0.5, 5.75, 0.25, metal.GLindex);
	glPopMatrix();
}

void ventana()
{
	//Ventana
	glPushMatrix();
		glPushMatrix();
			fig1.prisma(0.5, 5.0, 0.25, metal.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.375, 5.25, 0.0);
			fig1.prisma(10.0, 0.25, 0.25, metal.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 10.5, 0.0);
			fig1.prisma(0.5, 5.0, 0.25, metal.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-2.375, 5.25, 0.0);
			fig1.prisma(10.0, 0.25, 0.25, metal.GLindex);
		glPopMatrix();

		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glEnable(GL_BLEND);//PARA TRANSPARENCIA
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//PARA TRASNPARENCIA
			glBindTexture(GL_TEXTURE_2D, cristalazul.GLindex);
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(2.25, 10.5, -0.01);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(2.25, 0.0, -0.01);
				glTexCoord2f(-1.0f, 1.0f); glVertex3f(-2.25, 0.0, -0.01);
				glTexCoord2f(-1.0f, 0.0f); glVertex3f(-2.25, 10.5, -0.01);
			glEnd();
			glDisable(GL_BLEND);
		glPopMatrix();
	glPopMatrix();
}

void ventanal()
{
	//Ventanales
	glPushMatrix();
		glPushMatrix();
		ventana();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5.0, 0.0, 0.0);
		ventana();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-5.0, 0.0, 0.0);
		ventana();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 10.5, 0.0);
		ventana();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 21.0, 0.0);
		ventana();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5.0, 21.0, 0.0);
		ventana();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-5.0, 21.0, 0.0);
		ventana();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5.0, 10.5, 0.0);
		ventana();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-5.0, 10.5, 0.0);
		ventana();
		glPopMatrix();
	glPopMatrix();

}



void muroscristal()
{
	//Muros
	//Cristal
	glPushMatrix();
	fig1.prisma(0.5, 5.0, 0.25, metaloscuro.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.375, 5.25, 0.0);
	fig1.prisma(10.0, 0.25, 0.25, metaloscuro.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 10.5, 0.0);
	fig1.prisma(0.5, 5.0, 0.25, metaloscuro.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.375, 5.25, 0.0);
	fig1.prisma(10.0, 0.25, 0.25, metaloscuro.GLindex);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_BLEND);//PARA TRANSPARENCIA
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//PARA TRASNPARENCIA     
	glBindTexture(GL_TEXTURE_2D, cristal.GLindex);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.25, 10.5, -0.01);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.25, 0.0, -0.01);
	glTexCoord2f(-1.0f, 1.0f); glVertex3f(-2.25, 0.0, -0.01);
	glTexCoord2f(-1.0f, 0.0f); glVertex3f(-2.25, 10.5, -0.01);
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();



	//Parte inferior
	glPushMatrix();
	glTranslatef(2.375, -3.75, 0.0);
	fig1.prisma(7.0, 0.25, 0.25, metaloscuro.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -7.5, 0.0);
	fig1.prisma(0.5, 5.0, 0.25, metaloscuro.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.375, -3.75, 0.0);
	fig1.prisma(7.0, 0.25, 0.25, metaloscuro.GLindex);
	glPopMatrix();


	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, planomuro.GLindex);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2.25, -7.25, -0.01);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.25, -0.25, -0.01);
	glTexCoord2f(-1.0f, 1.0f); glVertex3f(-2.25, -0.25, -0.01);
	glTexCoord2f(-1.0f, 0.0f); glVertex3f(-2.25, -7.25, -0.01);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glPushMatrix();

		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
			
		glPushMatrix(); //Creamos cielo
		           glDisable(GL_LIGHTING);

				   glTranslatef(1060, 735, 1560);
				   fig1.skybox(2120, 1500.0, 3120, dia.GLindex, diatapa.GLindex);//agregado para que siempre se pinte el skybox
			
		glPopMatrix();//Pop cielo

		
		
					

		//Piso skyblock
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, plano.GLindex);
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
			glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -14.8, 2120);
			glTexCoord2f(1.0, 0.0); glVertex3f(2120, -14.8, 2120);
			glTexCoord2f(1.0, 1.0); glVertex3f(2120, -14.8, 0.0);
			glTexCoord2f(0.0, 1.0); glVertex3f(0.0, -14.8, 0.0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();
		//Piso calle
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, calle.GLindex);
		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 1.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -14.8, 3120);
		glTexCoord2f(1.0, 0.0); glVertex3f(2120, -14.8, 3120);
		glTexCoord2f(1.0, 1.0); glVertex3f(2120, -14.8, 2120.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.0, -14.8, 2120.0);
		glEnd();
		glEnable(GL_LIGHTING);
		glPopMatrix();



		//EDIFICIO
		glPushMatrix();
			//torre derecha
			glPushMatrix();
				//Piso 1 con techo
				glPushMatrix();
				//Pared trasera
				glTranslatef(1453.1, 60.0, 527.5);
				glColor3f(1.0, 1.0, 1.0);
				fig1.prisma(150, 534.8, 15, t_edif.GLindex);
				//pared izquierda
				glTranslatef(259.9, 0.0, 294.7);
				glColor3f(1.0, 1.0, 1.0);
				fig1.prisma(150, 15, 574.4, t_edif.GLindex);
				//pared frontal
				glTranslatef(-259.9, 0.0, 294.7);
				glColor3f(1.0, 1.0, 1.0);
				fig1.prisma(150, 534.8, 15, t_edif.GLindex);
				//pared derecha
				/*glTranslatef(259.9, 0.0, -294.7);
				glColor3f(1.0, 0.0, 1.0);
				fig1.prisma(150, 15, 574.4, 0);*/
				glPushMatrix();
					glTranslatef(-259.9, 0.0, -332.0);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 15, 499.0, t_edif.GLindex);
					glPopMatrix();

					glTranslatef(0, 82.5, -294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma2(15, 534.8, 604.4, t_edif2.GLindex, t_pisoEdif.GLindex);

					glTranslatef(0, -150.0, 0.0);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(1, 504.8, 574.4, t_pisoEdif.GLindex);
				glPopMatrix();

				//Piso 2
				glPushMatrix();
				//Pared trasera
					glTranslatef(1453.1, 225.0, 527.5);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 534.8, 15, t_edif.GLindex);
					//pared izquierda
					glTranslatef(-259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 15, 574.4, t_edif.GLindex);
					//pared frontal
					glTranslatef(259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 534.8, 15, t_edif.GLindex);
					//pared derecha
					glTranslatef(259.9, 0.0, -294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 15, 574.4, t_edif.GLindex);
					//techo
					glTranslatef(-259.9, 82.5, 0);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma2(15, 534.8, 604.4, t_edif2.GLindex, t_pisoEdif.GLindex);
				glPopMatrix();

				//Piso 3
				glPushMatrix();
					//Pared trasera
					glTranslatef(1453.1, 390.0, 527.5);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 534.8, 15, t_edif.GLindex);
					//pared izquierda
					glTranslatef(-259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 15, 574.4, t_edif.GLindex);
					//pared frontal
					glTranslatef(259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 534.8, 15, t_edif.GLindex);
					//pared derecha
					glTranslatef(259.9, 0.0, -294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 15, 574.4, t_edif.GLindex);
					//techo
					glTranslatef(-259.9, 82.5, 0);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma2(15, 534.8, 604.4, t_edif2.GLindex, t_pisoEdif.GLindex);
				glPopMatrix();

				//Piso 4
				glPushMatrix();
				//Pared trasera
					glTranslatef(1453.1, 555.0, 527.5);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 534.8, 15, t_edif.GLindex);
					//pared izquierda
					glTranslatef(-259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 15, 574.4, t_edif.GLindex);
					//pared frontal
					glTranslatef(259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 534.8, 15, t_edif.GLindex);
					//pared derecha
					glTranslatef(259.9, 0.0, -294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 15, 574.4, t_edif.GLindex);
					//techo
					glTranslatef(-259.9, 82.5, 0);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma2(15, 534.8, 604.4, t_edif2.GLindex, t_pisoEdif.GLindex);
				glPopMatrix();

				//Piso 5
				glPushMatrix();
					//Pared trasera
					glTranslatef(1453.1, 720.0, 527.5);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 534.8, 15, t_edif.GLindex);
					//pared izquierda
					glTranslatef(-259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 15, 574.4, t_edif.GLindex);
					//pared frontal
					glTranslatef(259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 534.8, 15, t_edif.GLindex);
					//pared derecha
					glTranslatef(259.9, 0.0, -294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(150, 15, 574.4, t_edif.GLindex);
					//techo
					glTranslatef(-259.9, 82.5, 0);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(15, 534.8, 604.4, t_edif2.GLindex);
				glPopMatrix();

				//Barda
				glPushMatrix();
					//Pared trasera
					glTranslatef(1453.1, 847.5, 527.5);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(75, 534.8, 15, t_edif2.GLindex);
					//pared izquierda
					glTranslatef(-259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(75, 15, 574.4, t_edif2.GLindex);
					//pared frontal
					glTranslatef(259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(75, 534.8, 15, t_edif2.GLindex);
					//pared derecha
					glTranslatef(259.9, 0.0, -294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(75, 15, 574.4, t_edif2.GLindex);
				glPopMatrix();
			glPopMatrix();//Torre izqueirda

			//Entre edificios
			glPushMatrix();
				//Pared trasera
				glTranslatef(1065.1, 95.0, 542.5);
				glColor3f(1.0, 1.0, 1.0);
				fig1.prisma(225, 250.5, 15, vitral2.GLindex);
				//PAred enfrente
				glPushMatrix();
					//pared frontal
					glTranslatef(0.0, 0.0, 569.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(225, 250.5, 15, vitral2.GLindex);
				glPopMatrix();
				//techos
				glTranslatef(0, 132.0, 60.1);
				glColor3f(0.5, 0.5, 0.5);
				fig1.prisma(15, 240.5, 155.2, t_edif2.GLindex);

				glTranslatef(0, -15, 293.6);
				glColor3f(1.0, 1.0, 1.0);
				fig1.prisma(15, 239.5, 482.1, t_edif2.GLindex);
				
				
				
			glPopMatrix();//pop parte central

				
		glPopMatrix();//pop edificio
		
		//Jardinera izquierda
		//Lateral
		glPushMatrix();
		glTranslatef(212.15, 6.0, 712.2);
		glColor3f(1.0, 1.0, 1.0);
		fig1.prisma2(40, 130.0, 600.0, tj_barda.GLindex, tj_pasto.GLindex);

		glPushMatrix();
		glTranslatef(0.0, 20, 0.0);
		glScalef(10.0, 20, 10.0);
		arbol_alpha(tree.GLindex);
		glPopMatrix();


		//Jardinera lateral enfrente
		glPushMatrix();
		glTranslated(0.0, 0.0, 600.0);
		fig1.prisma2(40.0, 130, 300, tj_barda.GLindex, tj_pasto.GLindex);

		glPushMatrix();
		glTranslatef(0.0, 20, 300.0);
		glScalef(10.0, 20, 10.0);
		arbol_alpha(tree.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(265.0, 20.0, -50);
		glRotatef(-180, 0, 0, 1);
		fig1.circuContor(200, 40, 30, tj_barda.GLindex, tj_pasto.GLindex);
		glPopMatrix();

		glTranslatef(-65.0, -20.0, 150);
		fig1.cuartoCilindro(330, 40, 30, tj_barda.GLindex, tj_pasto.GLindex);
		glPopMatrix();

		glPopMatrix();
		//Trasera
		glPushMatrix();
		glTranslatef(677.4, 6.0, 327.5);
		glColor3f(1.0, 1.0, 1.0);
		fig1.prisma2(40, 400.0, 130.0, tj_barda.GLindex, tj_pasto.GLindex);

		glPushMatrix();
		glTranslatef(0.0, 20, 0.0);
		glScalef(10.0, 20, 10.0);
		arbol_alpha(tree2.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-200.0, -20.0, -65.);
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-90, 0, 1, 0);
		fig1.trianguloRect(40, 130.0, 130.0, tj_barda.GLindex, tj_pasto.GLindex);
		glPopMatrix();

		glTranslatef(200.0, -20.0, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(90, 0, 1, 0);
		fig1.medioCilindro(65, 40, 30, tj_barda.GLindex, tj_pasto.GLindex);
		glPopMatrix();
		


		//Jardinera derecha
		//Lateral
		glPushMatrix();
		glTranslatef(1913.0, 6.0, 712.2);
		glColor3f(1.0, 1.0, 1.0);
		fig1.prisma2(40, 130.0, 400.0, tj_barda.GLindex, tj_pasto.GLindex);

		glPushMatrix();
		glTranslatef(0.0, 20, -150.0);
		glScalef(10.0, 20, 10.0);
		arbol_alpha(tree2.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 20, 150.0);
		glScalef(10.0, 20, 10.0);
		arbol_alpha(tree.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(65.0, -20.0, -200.);
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-180, 1, 0, 0);
		glRotatef(-180, 0, 0, 1);
		fig1.trianguloRect(40, 130.0, 130.0, tj_barda.GLindex, tj_pasto.GLindex);
		glPopMatrix();
		//Jardinera lateral enfrente
		glPushMatrix();
		glTranslated(0.0, 0.0, 600.0);
		fig1.prisma2(40.0, 130, 300, tj_barda.GLindex, tj_pasto.GLindex);

		glPushMatrix();
		glTranslatef(0.0, 20, -100.0);
		glScalef(10.0, 20, 10.0);
		arbol_alpha(tree2.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-265.0, -20.0, -50);
		fig1.circuContor(200, 40, 30, tj_barda.GLindex, tj_pasto.GLindex);
		glPopMatrix();

		glTranslatef(65.0, 20.0, 150);
		glRotatef(180, 0, 0, 1);
		fig1.cuartoCilindro(330, 40, 30, tj_barda.GLindex, tj_pasto.GLindex);
		glPopMatrix();
		glPopMatrix();
		//Trasera
		glPushMatrix();
		glTranslatef(1453.1, 6.0, 327.5);
		glColor3f(1.0, 1.0, 1.0);
		fig1.prisma2(40, 400.0, 130.0, tj_barda.GLindex, tj_pasto.GLindex);

		glPushMatrix();
		glTranslatef(150.0, 20, 0.0);
		glScalef(10.0, 20, 10.0);
		arbol_alpha(tree.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-250.0, 20, 0.0);
		glScalef(10.0, 20, 10.0);
		arbol_alpha(tree.GLindex);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(200.0, 20.0, -65.);
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		fig1.trianguloRect(40, 130.0, 130.0, tj_barda.GLindex, tj_pasto.GLindex);
		glPopMatrix();


		glTranslatef(-200.0, -20.0, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		glRotatef(-90, 0, 1, 0);
		fig1.medioCilindro(65, 40, 30, tj_barda.GLindex, tj_pasto.GLindex);

		glPopMatrix();
		


		//***********Animacion**************///////////////////
		//Cohes
		glPushMatrix();
		glTranslatef(movCocheX, 14.0, movCocheZ);
		glScalef(0.05, 0.05, 0.05);
		glRotatef(giroY, 0, 1, 0);
		glColor3f(1.0, 1.0, 1.0);
		carro1.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();

///**

	//TORRE IZQUIERDA

		//Planta Baja 
			//Piso
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, pisoblanco.GLindex);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(435.0, -14.5, 1117.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(435.0, -14.5, 535.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(920.0, -14.5, 535.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(920.0, -14.5, 1117.0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();

//		//Pared frontal
		glPushMatrix();
			glTranslatef(687.5, 84.0, 1117.0);
			fig1.prisma(195.0, 505, 8.0, t_edif.GLindex);
		glPopMatrix();


		//División de Piso 
		glPushMatrix();
			glTranslatef(685.0, 196.0, 1118.0);
			fig1.prisma(29.5, 501, 4.0, t_edif2.GLindex);
		glPopMatrix();
//



//		//Pared trasera
		glPushMatrix();
			glTranslatef(684.0, 84.0, 536.0);
			fig1.prisma(195.0, 514, 8.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso 
		glPushMatrix();
			glTranslatef(687.0, 196.0, 537.0);
			fig1.prisma(28.5, 504.5, 4.0, t_edif2.GLindex);
		glPopMatrix();
//


//		//Pared lateral derecha
		glPushMatrix();
			glTranslatef(431.0, 84.0, 828.0);
			fig1.prisma(195.0, 8.0, 586, t_edif.GLindex);
		glPopMatrix();

		//División de Piso 
		glPushMatrix();
			glTranslatef(433.0, 196.5, 827.5);
			fig1.prisma(30.0, 4.0, 585, t_edif2.GLindex);
		glPopMatrix();
//


//	    //Pared lateral izquierda
		glPushMatrix();
			glTranslatef(942.5, 84.0, 783.5);
			fig1.prisma(195.0, 6.3, 503.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso 
		glPushMatrix();
			glTranslatef(941.0, 197.0, 784.0);
			fig1.prisma(28.5, 4.0, 498.0, t_edif2.GLindex);
		glPopMatrix();
//



		//Piso 1  
		glPushMatrix();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			glColor3f(1.0, 1.0, 1.0);
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, pisolab.GLindex);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(435.0, 178.0, 1117.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(435.0, 178.0, 535.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(939.0, 178.0, 535.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(939.0, 178.0, 1117.0);
			glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

//		//Pared frontal
		glPushMatrix();
			glTranslatef(687.0, 280.0, 1117.0);
			fig1.prisma(140.0, 505, 8.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso 
		glPushMatrix();
			glTranslatef(685.25, 364.0, 1118.0);
			fig1.prisma(28.5, 502, 4.0, t_edif2.GLindex);
		glPopMatrix();
//



//		//Pared trasera
		glPushMatrix();
			glTranslatef(686.0, 280.0, 536.0);
			fig1.prisma(140.0, 518.0, 8.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso
		glPushMatrix();
			glTranslatef(687.0, 364.0, 537.0);
			fig1.prisma(28.5, 504.5, 4.0, t_edif2.GLindex);
		glPopMatrix();
//



//		//Pared lateral derecha
		glPushMatrix();
			glTranslatef(431.0, 280.0, 828.0);
			fig1.prisma(140.0, 8.0, 586.0, t_edif.GLindex);
		glPopMatrix();
//



//	    //Pared lateral izquierda
		glPushMatrix();
			glTranslatef(942.5, 280.0, 783.5);
			fig1.prisma(140.0, 6.3, 503.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso 
		glPushMatrix();
			glTranslatef(941.0, 364.0, 784.0);
			fig1.prisma(28.5, 4.0, 498.0, t_edif2.GLindex);
		glPopMatrix();
//

		///*************************AQUI es el piso de la sala de tortura
		//Piso 2. CUarto tortura
		glPushMatrix();
		    glDisable(GL_LIGHTING);
		    glEnable(GL_ALPHA_TEST);//PARA TRANSPARENCIA
			glAlphaFunc(GL_GREATER, 0.1);//PARA TRASNPARENCIA
			glBindTexture(GL_TEXTURE_2D, pisolab.GLindex);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(435.0, 350.1, 1117.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(435.0, 350.1, 535.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(939.0, 350.1, 535.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(939.0, 350.1, 1117.0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();

//		//Pared frontal
		glPushMatrix();
			glTranslatef(686.0, 447.5, 1117.0);
			fig1.prisma(155.0, 505.0, 8.0, t_edif.GLindex);
		glPopMatrix();

		glPushMatrix();
		//AQUI PONES LOS ELEMENTOS DEL CUARTO DE TORTURA SOLO FIJATE EN LOS GLTRANSLATE
		glPopMatrix();

        //División de Piso 
		glPushMatrix();
			glTranslatef(685.0, 532.0, 1118.0);
			fig1.prisma(28.5, 501, 4.0, t_edif2.GLindex);
		glPopMatrix();
//


//		//Pared trasera
		glPushMatrix();
			glTranslatef(686.0, 447.5, 536.0);
			fig1.prisma(155.5, 519.5, 8.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso
		glPushMatrix();
			glTranslatef(687.0, 532.0, 537.0);
			fig1.prisma(28.5, 504.5, 4.0, t_edif2.GLindex);
		glPopMatrix();


//	    //Pared lateral izquierda
		glPushMatrix();
			glTranslatef(942.5, 447.0, 783.5);
			fig1.prisma(155.0, 6.4, 503.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso 
		glPushMatrix();
			glTranslatef(941.0, 532.0, 784.0);
			fig1.prisma(28.5, 4.0, 498.0, t_edif2.GLindex);
		glPopMatrix();
//

		


		//Piso  3
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, pisolab.GLindex);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(435.0, 532.25, 1117.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(435.0, 532.25, 535.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(939.0, 532.25, 535.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(939.0, 532.25, 1117.0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();


//		//Pared frontal
		glPushMatrix();
			glTranslatef(687.5, 616.0, 1117.0);
			fig1.prisma(140.0, 505, 8.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso 
		glPushMatrix();
			glTranslatef(685.0, 700.0, 1118.0);
			fig1.prisma(28.5, 501, 4.0, t_edif2.GLindex);
		glPopMatrix();
//


		//Pared trasera
		glPushMatrix();
			glTranslatef(686.0, 616.0, 535.0);
			fig1.prisma(140.0, 518.0, 8.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso
		glPushMatrix();
			glTranslatef(687.0, 700.0, 537.0);
			fig1.prisma(28.5, 504.5, 4.0, t_edif2.GLindex);
		glPopMatrix();



//		//Pared lateral derecha
		glPushMatrix();
			glTranslatef(431.0, 616.0, 828.0);
			fig1.prisma(140.0, 8.0, 586, t_edif.GLindex);
		glPopMatrix();

		//División de Piso 
		glPushMatrix();
			glTranslatef(433.0, 700.0, 826.0);
			fig1.prisma(28.5, 4.0, 590, t_edif2.GLindex);
		glPopMatrix();
//


//	    //Pared lateral izquierda
		glPushMatrix();
			glTranslatef(942.5, 616.0, 783.5);
			fig1.prisma(140.0, 6.4, 503.0, t_edif.GLindex);
		glPopMatrix();

		//División de Piso 
		glPushMatrix();
			glTranslatef(941.0, 700.0, 784.0);
			fig1.prisma(28.5, 4.0, 498.0, t_edif2.GLindex);
		glPopMatrix();
//


		//Piso  4
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, pisolab.GLindex);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(435.0, 700.0, 1117.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(435.0, 700.0, 535.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(939.0, 700.0, 535.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(939.0, 700.0, 1117.0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();


		//Pared frontal
		glPushMatrix();
			glTranslatef(687.5, 790.0, 1117.0);
			fig1.prisma(152.0, 505, 8.0, t_edif.GLindex);
		glPopMatrix();


		//Pared trasera
		glPushMatrix();
			glTranslatef(686.0, 790.0, 535.0);
			fig1.prisma(152.0, 518.0, 8.0, t_edif.GLindex);
		glPopMatrix();


		//Pared lateral derecha
		glPushMatrix();
			glTranslatef(431.0, 786.0, 828.0);
			fig1.prisma(143.0, 8.0, 586, t_edif.GLindex);
		glPopMatrix();


		//Pared lateral izquierda
		glPushMatrix();
			glTranslatef(942.5, 786.0, 783.5);
			fig1.prisma(143.0, 6.4, 503.0, t_edif.GLindex);
		glPopMatrix();

		



		//Techo
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, t_edif2.GLindex);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(430.0, 880.0, 1110.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(430.0, 880.0, 535.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(930.0, 880.0, 535.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(930.0, 880.0, 1110.0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();


		//Barda
			//Pared trasera
				glPushMatrix();
					glTranslatef(680, 880.0, 527.5);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(75, 534.8, 15, t_edif2.GLindex);

			//Pared izquierda
					glTranslatef(-259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(75, 15, 574.4, t_edif2.GLindex);

			//Pared frontal
					glTranslatef(259.9, 0.0, 294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(75, 534.8, 15, t_edif2.GLindex);

			//Pared derecha
					glTranslatef(259.9, 0.0, -294.7);
					glColor3f(1.0, 1.0, 1.0);
					fig1.prisma(75, 15, 574.4, t_edif2.GLindex);
				glPopMatrix();





		// LABORATORIO //



		//Muros vista exterior
		glPushMatrix();
			glTranslatef(430.0, 390.0, 821.5);
			glScalef(15.0, 10.0, 17.369);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			muropalomas();
		glPopMatrix();

		//Ventanales
		//Piso 1
		glPushMatrix();
			glTranslatef(938.0, 140.0, 1073.5);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glScalef(5.4, 6.8, 5.0);
			ventanal();
		glPopMatrix();

		//Piso 2. Laboratorio
		glPushMatrix();
			glTranslatef(938.0, 351.0, 1073.5);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glScalef(5.4, 5.7, 5.0);
			ventanal();
		glPopMatrix();

		//Piso 3
		glPushMatrix();
			glTranslatef(938.0, 531.0, 1073.5);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glScalef(5.4, 5.3, 5.0);
			ventanal();
		glPopMatrix();

		//Piso 3
		glPushMatrix();
			glTranslatef(938.0, 700.0, 1073.5);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glScalef(5.4, 4.5, 5.0);
			ventanal();
		glPopMatrix();




		//Elevador
			//Paredes del elevador
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, metaloscuro.GLindex);
			glBegin(GL_QUADS);
				glTexCoord2f(1.0, 0.0); glVertex3f(568.8, 867.75, 1110.0);
				glTexCoord2f(0.0, 0.0); glVertex3f(435.5, 867.75, 1110.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(435.5, -14.5, 1110.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(568.8, -14.5, 1110.0);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();


		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, metaloscuro.GLindex);
			glBegin(GL_QUADS);
				glTexCoord2f(1.0, 0.0); glVertex3f(568.8, 867.75, 1025.5);
				glTexCoord2f(0.0, 0.0); glVertex3f(435.5, 867.75, 1025.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(435.5, -14.5, 1025.5);
				glTexCoord2f(0.0, 1.0); glVertex3f(568.8, -14.5, 1025.5);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();


		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glDisable(GL_LIGHTING);
			glBindTexture(GL_TEXTURE_2D, metaloscuro.GLindex);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 1.0); glVertex3f(442, -14.5, 1110.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(442, 867.75, 1110.0);
				glTexCoord2f(0.0, 0.0); glVertex3f(442, 867.75, 1025.5);
				glTexCoord2f(1.0, 1.0); glVertex3f(442, -14.5, 1025.5);
			glEnd();
			glEnable(GL_LIGHTING);
		glPopMatrix();

				//Muros con cristal
				//Muros traseros
		glPushMatrix();
			glTranslatef(472.0, 426.0, 1023.0);
			glScalef(12.0, 9.7, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(532.0, 426.0, 1023.0);
			glScalef(12.0, 9.7, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(592.0, 426.0, 1023.0);
			glScalef(12.0, 9.7, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(729.0, 426.0, 1032.0);
			glScalef(12.0, 9.7, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(789.0, 426.0, 1032.0);
			glScalef(12.0, 9.7, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(849.0, 426.0, 1032.0);
			glScalef(12.0, 9.7, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(909.0, 426.0, 1032.0);
			glScalef(12.0, 9.7, 12.0);
			muroscristal();
		glPopMatrix();


			//Muros frontales
		glPushMatrix();
			glTranslatef(895.0, 426.0, 542.0);
			glScalef(17.0, 9.8, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(825.0, 426.0, 542.0);
			glScalef(12.0, 9.8, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(765.0, 426.0, 542.0);
			glScalef(12.0, 9.8, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(705.0, 426.0, 542.0);
			glScalef(12.0, 9.8, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(645.0, 426.0, 542.0);
			glScalef(12.0, 9.8, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(585.0, 426.0, 542.0);
			glScalef(12.0, 9.8, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(525.0, 426.0, 542.0);
			glScalef(12.0, 9.8, 12.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(465.0, 426.0, 542.0);
			glScalef(12.0, 9.8, 12.0);
			muroscristal();
		glPopMatrix();


		//Muros laterales derechos
		glPushMatrix();
			glTranslatef(937.0, 426.0, 1000.0);
			glScalef(12.0, 9.8, 12.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(937.0, 426.0, 940.0);
			glScalef(12.0, 9.8, 12.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(937.0, 426.0, 880.0);
			glScalef(12.0, 9.8, 12.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(937.0, 426.0, 820.0);
			glScalef(12.0, 9.8, 12.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(937.0, 426.0, 760.0);
			glScalef(12.0, 9.8, 12.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(937.0, 426.0, 700.0);
			glScalef(12.0, 9.8, 12.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(937.0, 426.0, 640.0);
			glScalef(12.0, 9.8, 12.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			muroscristal();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(937.0, 426.0, 575.0);
			glScalef(12.0, 9.8, 14.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			muroscristal();
		glPopMatrix();


		//Fuente
		glPushMatrix();
		glTranslatef(-1300, -1000, -1350);
		glScalef(2.1f, 2.1f, 2.1f);
		fuente();
		glPopMatrix();

		
		

	//Animación de lluvia
		

		//Columpios
		glPushMatrix();
			glTranslatef(1700.0, 123.5, 1280.0);
			glRotatef(150.0, 0.0, 1.0, 0.0);
			glScalef(10.0, 7.0, 10.0);
			columpios();
		glPopMatrix();

		
		//Caja Elevador
		glPushMatrix();
			glTranslatef(525.0, movElevadorY, 1070.0);
			glScalef(4.75, 4.25, 4.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			elevador();
		glPopMatrix();




		glColor3f(1.0, 1.0, 1.0);
		

	glPopMatrix();//pop dibujo

	glutSwapBuffers ( );

}



void animacion()
{
	//Animación en puertas de elevador
	if (anima_puerta)
	{
		if (abre_puerta)
		{
			puertder += 1.0;
			puertizq -= 1.0;
		}
		if (puertder == 90.0 || puertizq == 270.0)
		{
			abre_puerta = false;
			cierra_puerta = true;
		}
		if (cierra_puerta)
		{
			puertder -= 1.0;
			puertizq += 1.0;

		}
		if (puertder == 0.0 || puertizq == 360.0)
		{
			cierra_puerta = false;
			anima_puerta = false;
			abre_puerta = true;
			if (estado0)
			{
				movElevadorY++;
			}
			else{
				movElevadorY--;
			}
		}
	}

	//Animación de elevación y descenso del elevador
	if (anima_elevadorS)
	{
		if (movElevadorY < 178.0)
		{
			movElevadorY++;
			estado0 = true;
		}
		else if (movElevadorY == 178.0)
		{
			anima_puerta = true;
			estado0 = true;
		}
		else if (movElevadorY < 351.0)
		{
			movElevadorY++;
			estado0 = true;
		}
		else if (movElevadorY == 351.0)
		{
			anima_puerta = true;
			estado0 = true;
		}
		else if (movElevadorY < 532.0)
		{
			movElevadorY++;
			estado0 = true;
		}
		else if (movElevadorY == 532.0)
		{
			anima_puerta = true;
			estado0 = true;
		}
		else if (movElevadorY < 700.0)
		{
			movElevadorY++;
			estado0 = true;
		}
		else if (movElevadorY == 700.0)
		{
			movElevadorY = 701;
			anima_puerta = true;
			anima_elevadorS = false;
			anima_elevadorB = true;

		}

	}
	if (anima_elevadorB)
	{
		if (movElevadorY > 700.0)
		{
			movElevadorY--;
			estado0 = false;
		}
		else if (movElevadorY == 700.0)
		{
			anima_puerta = true;
			estado0 = false;
		}
		else if (movElevadorY > 532.0)
		{
			movElevadorY--;
			estado0 = false;
		}
		else if (movElevadorY == 532.0)
		{
			anima_puerta = true;
			estado0 = false;
		}
		else if (movElevadorY > 351.0)
		{
			movElevadorY--;
			estado0 = false;
		}
		else if (movElevadorY == 351.0)
		{
			anima_puerta = true;
			estado0 = false;
		}
		else if (movElevadorY > 178.0)
		{
			movElevadorY--;
			estado0 = false;
		}
		else if (movElevadorY == 178.0)
		{
			anima_puerta = true;
			anima_elevadorS = false;
			anima_elevadorB = false;
			movElevadorY = -14;
		}

	
			
	}
	fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;
	if (fig3.text_izq<-1)
		fig3.text_izq = 0;
	if (fig3.text_der<0)
		fig3.text_der = 1;

	

	//************ Animacion Keyrame Coche ***********//

	if (play2)
	{

		if (i_curr_steps2 >= i_max_steps2) //end of animation between frames?
		{
			playIx2++;
			if (playIx2>MAX_FRAMESC - 1)	//end of total animation?
			{
				printf("termina animacion\n");
				playIx2 = 0;
				resetElementCo();
				play2 = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps2 = 0; //Reset counter
				//Interpolation
				interpolationCo();
			}
		}
		else
		{
			//Draw animation

			movCocheX += KeyFrameCo[playIx2].incCocheX;
			movCocheZ += KeyFrameCo[playIx2].incCocheZ;
			giroY += KeyFrameCo[playIx2].incGiroY;
			i_curr_steps2++;

		}

	}
	//Animación fuente
	mov2 += 0.01;
	if (mov2 >= 2)
		mov2 = 0.0;

	//Animación del pez
	if (anima)
	{
		posX = posXini + Vini*t*cos(angulo);
		posY = Vini*t*sin(angulo) - 0.5*g*t*t;
	}

	if (posY <= 0.0 && posX > 1.0)
	{
		t = 0.0;

		Vini = Vini / 1.5;

		angulo = angulo / 1, 5;

		posXini = posX;
	}

	t -= 0.001;

	
	//Animación de columpios con monitos
	if (anima_monito)
	{
		if (monito_arriba)
			if (rotpier2 < 30.0 || rotbrader < 30.0)
			{
				rotpier1--;
				rotpier2++;
				rotpier3--;
				rotbraizq--;
				rotbrader++;
			}
		else if (monito_abajo)
			if (rotpier2 > 0.0 || rotbrader > -90.0)
			{
				rotpier1++;
				rotpier2--;
				rotpier3++;
				rotbraizq++;
				rotbrader--;
			}
	}

	if (anima_columpio)
	{
		if (sube_columpio)
		{
			if (columpiakike < 130.0)
			{
				baja_columpio = false;
				rotcuerda1++;
				rotcuerda2--;
				columpiakike++;
				columpiadylan--;
				anima_monito = true;

			}
			else {

				sube_columpio = false;
				baja_columpio = true;
			}
		}
		if (baja_columpio)
		{
			if (columpiakike > -130.0)
			{
				sube_columpio = false;
				rotcuerda2++;
				rotcuerda1--;
				columpiakike--;
				columpiadylan++;
				anima_monito = true;
			}
			else{
				sube_columpio = true;
				baja_columpio = false;
			}
		}
	}

	
	
	

	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum(-1, 1, -1, 1, 1, 5000);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 4.0);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 4.0));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 2.0));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 2.0);
		break;

		//case ' ':		//Poner algo en movimiento
		//	g_fanimacion^= true; //Activamos/desactivamos la animacíon
		//	break;

	case 'q':   //Animación del elevador
	case 'Q':
		anima_elevadorS ^= true;
		break;

		//Animación del columpio
	case 'h':
		rotcuerda1++;
		rotcuerda2--;
		break;

	case 'H':
		rotcuerda2++;
		rotcuerda1--;
		break;

		///////////////////////////////Animacion Coche
	case 'k':
	case 'K':
		if (play2 == false)
		{
			resetElementCo();
			//First Interpolation	

			interpolationCo();

			play2 = true;
			playIx2 = 0;
			i_curr_steps2 = 0;
		}
		else
		{
			play2 = false;
		}
		break;



	

		//Rotaciones del columpio
	case 'f':
		anima_columpio ^= true;
		sube_columpio ^= true;
		break;


	case '1':   //Posición inicial de los monitos
		rotbraizq = 0.0;
		rotbrader = 0.0;
		rotpier1 = -90.0;
		rotpier2 = 0.0;
		rotpier3 = 0.0;
		break;


	case 'u':
		if (fishtail < 50.0)
		{
			fishbody += 1.0;
			fishtail += 1.5;
		}
		break;

	case 'U':
		if (fishbody > -50.0)
		{
			fishbody -= 1.0;
			fishtail -= 1.5;
		}

		break;


	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;

	}

  glutPostRedisplay();
}

	void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
	{
		switch (a_keys) {
		case GLUT_KEY_PAGE_UP:
			objCamera.UpDown_Camera(CAMERASPEED);
			break;

		case GLUT_KEY_PAGE_DOWN:
			objCamera.UpDown_Camera(-CAMERASPEED);
			break;

		case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
			g_lookupdown -= 1.0f;
			break;

		case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
			g_lookupdown += 1.0f;
			break;

		case GLUT_KEY_LEFT:
			objCamera.Rotate_View(-CAMERASPEED);
			break;

		case GLUT_KEY_RIGHT:
			objCamera.Rotate_View(CAMERASPEED);
			break;

		default:
			break;


			glutPostRedisplay();
		}
	}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (1000, 600);	// Tamaño de la Ventana
  glutInitWindowPosition (100, 60);	//Posicion de la Ventana
  glutCreateWindow    ("PROYECTO FINAL"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  //Música
  PlaySound(NULL, NULL, 0);
//  PlaySound("ProyectoCG.wav", NULL, SND_LOOP | SND_ASYNC);

  glutMainLoop        ( );          // 


  


  return 0;
}
