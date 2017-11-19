//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Funcíon creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Funcíon creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Funcíon creacion movimiento
	void trianguloRect(float altura, float largo, float profundidad, GLuint text, GLuint text2);//Funcion creacion triangulo 90°
	void piramideRect(float altura, float largo, float profundidad, GLuint text);//Funcion piramide cuadrada 90°
	void prisma (float altura, float largo, float profundidad, GLuint text);//Funcíon creacion prisma
	void prisma2 (float altura, float largo, float profundidad, GLuint text, GLuint text2);
	void prisma3(float altura, float largo, float profundidad, GLuint text, GLuint text2);
    void prisma6(float altura, float largo, float profundidad, GLuint text, GLuint text1, GLuint text2, GLuint text3);
	void prisma7(float altura, float largo, float profundidad, GLuint text, GLuint text1);
	void skybox(float altura, float largo, float profundidad, GLuint text, GLuint text2);	//Funcion creacion cielo
	void skybox2 (float altura, float largo, float profundidad, GLuint text);
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);
	void medioCilindro(float radio, float altura, int resolucion, GLuint text, GLuint text2);
	void circuContor(float radio, float altura, int resolucion, GLuint text);
	void terCilindro(float radio, float altura, int resolucion, GLuint text);
	void circuContor(float radio, float altura, int resolucion, GLuint text, GLuint text2);
	void terCilindro(float radio, float altura, int resolucion, GLuint text, GLuint text2);
	void cuartoCilindro(float radio, float altura, int resolucion, GLuint text, GLuint text2);
	void cilindromitad(float radio, float altura, int resolucion, GLuint text); //Funcion creacion mitad de un cilindro
	void cilindrocuarto(float radio, float altura, int resolucion, GLuint text); //Funcion creacion mitad de un cilindro


};
