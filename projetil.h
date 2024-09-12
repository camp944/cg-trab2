
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

GLfloat verticesProjetil[] = {
    // Frente
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    // Trás
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
};

// Índices para desenhar o cubo
GLubyte indices[] = {
    // Frente
    0, 1, 2, 3,
    // Trás
    4, 5, 6, 7,
    // Esquerda
    0, 3, 7, 4,
    // Direita
    1, 2, 6, 5,
    // Topo
    3, 2, 6, 7,
    // Fundo
    0, 1, 5, 4,
};

void desenhaProjetil(float xOrigem, float yOrigem, int direcao) {
    // Desabilita texturas
    glDisable(GL_TEXTURE_2D);

    // Salva o estado atual da matriz de transformações
    glPushMatrix();

    // Define a cor do projetil
    glColor3f(1.0, 0.5, 0.0);

    // Aplica transformações
    glTranslatef(yOrigem, xOrigem, 0.5);
    glRotatef(direcao, 0.0, 0.0, 1.0);
    glScalef(tam_projetil, tam_projetil, tam_projetil);

    // Habilita o uso de arrays de vértices
    glEnableClientState(GL_VERTEX_ARRAY);

    // Define os ponteiros para os arrays de vértices
    glVertexPointer(3, GL_FLOAT, 0, verticesProjetil);

    // Desenha o cubo usando os índices
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

    // Parte da frente do projetil
    glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glTranslatef(0.0, 0.5, 0.0);
        glScalef(1.0, 0.5, 1.0);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
    glPopMatrix();

    // Desabilita o uso de arrays de vértices
    glDisableClientState(GL_VERTEX_ARRAY);

    // Restaura a matriz de transformações
    glPopMatrix();

    // Habilita texturas novamente
    glEnable(GL_TEXTURE_2D);
}
#endif
