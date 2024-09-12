
//Implementação do projetil (munição)
#ifndef PROJETIL_H
#define PROJETIL_H
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "bloco.h"

float tam_projetil = 0.2;

typedef struct{
	float xOrigem;
	float yOrigem;
	float velocidade;
	float distancia;
	int direcao;
	bool tiro;
	
}Projetil;

void desenhaProjetil(float xOrigem, float yOrigem, int direcao){
	//Projetil inteiro.
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
		glColor3f(1.0, 0.5, 0.0);
		glTranslatef (yOrigem*1, xOrigem*1, 0.5);
		glRotatef(direcao, 0.0 , 0.0 , 1.0);
		glScalef (tam_projetil, tam_projetil, tam_projetil);
		glutSolidCube(1.0);
		//Parte da frente do Projetil.
		glPushMatrix();
			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(0.0, 0.5, 0.0);
			glScalef (1.0, 0.5, 1.0);
			glutSolidCube(1.0);
		glPopMatrix();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}
#endif
