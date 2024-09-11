//Visual do bonus
#include <GL/gl.h> // Include the appropriate header file for glRotatef
#include "bloco.h"

bool bonus_boat = false;
bool bonus_gun = false;
bool bonus_wall = false;
bool bonus_vida = false;
bool bonus_estrela = false;


int qtd_bonus_ativos = 0;

void visualBonus(float i, float j, int rotacao){
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (0.8, 0.8, 0.8);
		glRotatef(rotacao, 0.0, 0.0, 1.0);
		draw_object_smooth();
	glPopMatrix();
}