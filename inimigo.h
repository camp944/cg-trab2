//Implementa��o do inimigo, comandos, estruturas etc.
#ifndef INIMIGO_H
#define INIMIGO_H
#include "projetil.h"

typedef struct{
	float x;
	float y;
	float xInicial;
	float yInicial;
	float velocidade;
	float velocidadeInicial;
	float direcaoCano;
	float R;
	float G;
	float B;
	bool vivo;
	Projetil projetil;
}Inimigo;

#endif