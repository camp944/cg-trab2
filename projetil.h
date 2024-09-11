//Implementa��o do projetil (muni��o)
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

void desenhaProjetil(float xOrigem, float yOrigem, int direcao) {
    // Desabilita o uso de texturas
    // glDisable(GL_TEXTURE_2D);

    // // Salva o estado atual da matriz de transformações
    // glPushMatrix();

    // // Define a cor do corpo do projetil
    // glColor3f(1.0, 0.5, 0.0); // Cor laranja

    // // Translada o projetil para a posição de origem
    // glTranslatef(xOrigem, yOrigem, 0.0);

    // // Rotaciona o projetil de acordo com a direção
    // glRotatef(direcao, 0.0, 0.0, 1.0);

    // // Escala o projetil para o tamanho especificado
    // glScalef(tam_projetil, tam_projetil, tam_projetil);

    // // Cria e inicializa o objeto quadrático
    // GLUquadric* quadric = gluNewQuadric();
    // if (quadric == nullptr) {
    //     std::cerr << "Erro ao criar objeto GLUquadric." << std::endl;
    //     glPopMatrix();
    //     return;
    // }

    // // Desenha o corpo do projetil como um cilindro
    // glPushMatrix();
    //     glColor3f(1.0, 0.5, 0.0); // Cor laranja
    //     gluCylinder(quadric, 0.1, 0.1, 1.0, 20, 20); // Cilindro para o corpo do projetil
    // glPopMatrix();

    // // Desenha a ponta do projetil como um cone
    
    // // Libera a memória usada pelo quadrico
    // //gluDeleteQuadric(quadric);

    // // Restaura o estado da matriz de transformações
    // glPopMatrix();

    // // Habilita novamente o uso de texturas
    // glEnable(GL_TEXTURE_2D);
}

#endif