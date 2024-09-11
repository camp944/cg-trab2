#ifndef TEXTOS_H
#define TEXTOS_H
#include "mapa.h"


void desenhaVidasJogador(int vidas){
	char texto1[19] = "Vidas do Jogador: ";
    glPushMatrix();
    	glTranslatef(15.6, -6, 0);
    	glColor3f(1.0, 1.0, 1.0);
    	glRasterPos2f(0.0,15);
    	for(int i = 0; i<=static_cast<int>(strlen(texto1)); i++){
    		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto1[i]);
		}
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(15.5, 7.0, 0.5);
    glScalef(0.8, 0.8, 0.8);
    float espaco = 1.5;

    for (int i = 0; i < vidas; i++){
        glPushMatrix();
        glTranslatef(i * espaco, 0.0, 0.0);
        desenhaTank(0.0, 0.0, 180, 1.0, 1.0, 0.0);
        glPopMatrix();
    }

glPopMatrix();
}

void desenhaVidasInimigo(int vidas){
	char texto[25] = "Inimigos: ";
	glPushMatrix();
		glTranslatef(16, -2, 0);
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(0.0,15);
		for(int i = 0; i<=static_cast<int>(strlen(texto)); i++){
    		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto[i]);
		}
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(15.8, 10.5, 0.5);
		glScalef(0.8, 0.8, 0.8);
		float espaco = 1.5;
		for (int i = 0; i < vidas; i++){
        	glPushMatrix();
        	glTranslatef(i * espaco, 0.0, 0.0);
        	desenhaTank(0.0, 0.0, 180, 1.0, 0.0, 0.0);
        	glPopMatrix();
    	}
    glPopMatrix();
}

void desenhaPlacarBonus(){
	char texto[25] = "Bonus Ativos:";
	glPushMatrix();
		glTranslatef(15.5, -9.5, 0);
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(0.0,15);
		for(int i = 0; i<=static_cast<int>(strlen(texto)); i++){
    		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto[i]);
		}
    glPopMatrix();
	glPushMatrix();
		glTranslatef(15.4, 4.0, 0.5);
		glScalef(0.8, 0.8, 0.8);
		float espaco = 1.5;
		if (bonus_wall){
			glPushMatrix();
			   	glTranslatef(0 * espaco, 0.0, 0.0);
			   	desenhaBonus(1, 0, 0, 0);
			glPopMatrix();
		}
		if (bonus_vida){
			glPushMatrix();
			   	glTranslatef(1 * espaco, 0.0, 0.0);
			   	desenhaBonus(2, 0, 0, 0);
			glPopMatrix();
		}
		if (bonus_estrela){
			glPushMatrix();
				glTranslatef(2 * espaco, 0.0, 0.0);
			   	desenhaBonus(3, 0, 0, 0);
			glPopMatrix();
		}
		if (bonus_boat){
			glPushMatrix();
				glTranslatef(3 * espaco, 0.0, 0.0);
				desenhaBonus(4, 0, 0, 0);
			glPopMatrix();
		}
		if (bonus_gun){
			glPushMatrix();
				glTranslatef(4 * espaco, 0.0, 0.0);
				desenhaBonus(5, 0, 0, 0);
			glPopMatrix();
		}
	glPopMatrix();
}

#endif