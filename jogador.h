//Implementação do jogador, comandos, estruturas etc.
#ifndef JOGADOR_H
#define JOGADOR_H
#include "projetil.h"

typedef struct{
	float x;
	float y;
	float xInicial;
	float yInicial;
	float velocidade;
	float velocidadeInicial;
	int direcaoCano;
	float R;
	float G;
	float B;
	//Quantidade de vidas.
	int vida;
	//Vivo ou morto.
	bool vivo;
	Projetil projetil;
}Jogador;

#endif

