//Implementa��o do mapa.

#ifndef MAPA_H
#define MAPA_H

#include <cstdio>
#include "bloco.h"
#include "texturas/textureLoader.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "bonus.h"
#include "audio.h"
#include <sstream>
using std::stringstream;
#include <string>
using std::string;


//Texturas dos blocos
#include "texturas/texturaTijolo.h"
#include "texturas/texturaAgua.h"
#include "texturas/texturaMetal.h"
#include "texturas/texturaGelo.h"
#include "texturas/texturaArbusto.h"
#include "texturas/texturaParede.h"
#include "texturas/texturaChao.h"
#include "texturas/texturaAguia.h"
//Texturas dos bonus
#include "texturas/texturaBonusGun.h"
#include "texturas/texturaBonusStone.h"
#include "texturas/texturaBonusLife.h"
#include "texturas/texturaBonusSpeed.h"
#include "texturas/texturaBonusBoat.h"
#include "texturas/texturaTank.h"
#include "texturas/texturaFundo.h"
#include "texturas/texturaMenu.h"
#include "texturas/texturaInfoMenu.h"
#include "texturas/texturaGameOver.h"
#include "texturas/texturaGameWin.h"

bool game_win = false;
bool game_over = false;
bool menu_inicial = true;
bool menu_info = false;


#define tamMapa 15

//Texturas
#define QUANT_TEX 19
int coluna = 0;
float tam_tank = 0.8;
unsigned int id_texturas[QUANT_TEX]; //nomes identificadores de textura

void textura(){
	/* Prepara a textura */
	//gera nomes identificadores de texturas

	//Texturas do tijolo
	loadTexture(tijolo_address,&id_texturas[0],TEXTURE_tijolo,TEXTURE_tijolo);

	//Texturas da agua
	loadTexture(agua_address,&id_texturas[1],TEXTURE_agua,TEXTURE_agua);
	
	//Texturas do metal
	loadTexture(metal_address,&id_texturas[2],TEXTURE_metal,TEXTURE_metal);
	
	//Texturas do gelo
	loadTexture(gelo_address,&id_texturas[3],TEXTURE_gelo,TEXTURE_gelo);
	
	//Texturas do arbusto
	loadTexture(arbusto_address,&id_texturas[4],TEXTURE_arbusto,TEXTURE_arbusto);
	
	//Texturas da parede
	loadTexture(parede_address,&id_texturas[5],TEXTURE_parede,TEXTURE_parede);
	
	//Texturas do background
	loadTexture(chao_address,&id_texturas[6],TEXTURE_chao,TEXTURE_chao);
	
	//Texturas da aguia
	loadTexture(aguia_address,&id_texturas[7],TEXTURE_aguia,TEXTURE_aguia);
	
	
	//Texturas dos bonus
	loadTexture(bonusgun_address,&id_texturas[8],TEXTURE_bonus_gun,TEXTURE_bonus_gun);
	
	loadTexture(bonusstone_address,&id_texturas[9],TEXTURE_bonus_stone,TEXTURE_bonus_stone);
	
	loadTexture(bonuslife_address,&id_texturas[10],TEXTURE_bonus_life,TEXTURE_bonus_life);
	
	loadTexture(bonusspeed_address,&id_texturas[11],TEXTURE_bonus_speed,TEXTURE_bonus_speed);
	
	loadTexture(bonusboat_address,&id_texturas[12],TEXTURE_bonus_boat,TEXTURE_bonus_boat);
	
	
	//Textura do Tank
	loadTexture(tank_address,&id_texturas[13],TEXTURE_tank,TEXTURE_tank);
	
	
	//Textura do Background
	loadTexture(background_address,&id_texturas[14],TEXTURE_fundo,TEXTURE_fundo);
	
	//Textura do Menu
	loadTexture(menu_address,&id_texturas[15],TEXTURE_menu,TEXTURE_menu);
  
	//Textura de Game Over
	loadTexture(gameover_address,&id_texturas[16],TEXTURE_gameover,TEXTURE_gameover);
	
	//Textura de Game Win
	loadTexture(gamewin_address,&id_texturas[17],TEXTURE_gamewin,TEXTURE_gamewin);

	//Textura de Game Win
	loadTexture(info_menu_address,&id_texturas[18],TEXTURE_menuinfo,TEXTURE_menuinfo);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

/*
- Detalhamento do Mapa
	- Ch�o: 0
	- Agua: 1
	- Tijolo: 2
	- Metal: 3
	- Arbusto: 4
	- Gelo: 5
	- Aguia: 6
	- Parede externa: 7
*/

int mapa[tamMapa][tamMapa] =   {{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
								{7, 2, 2, 2, 0, 0, 2, 6, 2, 0, 2, 2, 2, 2, 7},
								{7, 2, 3, 2, 0, 0, 2, 2, 2, 0, 2, 5, 5, 5, 7},
								{7, 5, 2, 2, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 7},			
								{7, 5, 3, 2, 0, 0, 0, 0, 0, 0, 5, 0, 0, 4, 7},
								{7, 5, 5, 5, 5, 0, 2, 3, 3, 0, 1, 3, 1, 4, 7},
								{7, 1, 1, 1, 5, 1, 1, 0, 2, 0, 1, 0, 0, 4, 7},	
								{7, 4, 4, 4, 5, 3, 1, 4, 4, 0, 1, 4, 4, 4, 7},
								{7, 5, 4, 2, 5, 2, 1, 1, 1, 0, 1, 2, 2, 4, 7},
								{7, 4, 4, 3, 0, 3, 1, 0, 2, 0, 3, 3, 2, 4, 7},
								{7, 4, 1, 1, 1, 1, 1, 0, 2, 2, 1, 1, 2, 3, 7},
								{7, 4, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 2, 7},
								{7, 0, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 7},
								{7, 0, 0, 0, 3, 0, 0, 0, 2, 2, 2, 0, 0, 0, 7},
								{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
};

// Plano de fundo
void background() {
    // Define a matriz de proje��o como matriz de trabalho atual
    glMatrixMode(GL_PROJECTION);
    // Salva a matriz de proje��o atual na pilha
    glPushMatrix();
    // Carrega a matriz identidade para a matriz de proje��o
    glLoadIdentity();
    // Define uma proje��o ortogr�fica 2D com coordenadas de recorte de (0,0) a (1,1) no plano XY
    glOrtho(0, 1, 0, 1, -1, 1);
    // Desabilita o teste de profundidade, para que a textura do plano de fundo n�o seja obscurecida por objetos 3D
    glDisable(GL_DEPTH_TEST);
    // Desabilita a ilumina��o, para que a textura do plano de fundo seja renderizada sem sombreamento
    glDisable(GL_LIGHTING);
    // Desabilita a escrita no buffer de profundidade, para que a textura do plano de fundo n�o afete outros objetos 3D
    glDepthMask(GL_FALSE);
    // Associa a textura com o ID id_texturas[14] ao plano de fundo
    glBindTexture(GL_TEXTURE_2D, id_texturas[14]);
    // Inicia a defini��o de um pol�gono (quadril�tero) para renderizar a textura
    glBegin(GL_QUADS);
    // Define a cor do pol�gono como branco
    glColor3f(1.0, 1.0, 1.0);
    // Define as coordenadas de textura e v�rtices do quadril�tero
    glTexCoord2i(0, 0); glVertex2i(-1, -1);
    glTexCoord2i(1, 0); glVertex2i(1, -1);
    glTexCoord2i(1, 1); glVertex2i(1, 1);
    glTexCoord2i(0, 1); glVertex2i(-1, 1);
    // Finaliza a defini��o do pol�gono
    glEnd();
    // Habilita novamente o teste de profundidade para objetos 3D futuros
    glEnable(GL_DEPTH_TEST);
    // Habilita novamente a ilumina��o para objetos 3D futuros
    glEnable(GL_LIGHTING);
    // Habilita novamente a escrita no buffer de profundidade para objetos 3D futuros
    glDepthMask(GL_TRUE);
    // Restaura a matriz de proje��o anterior que estava na pilha
    glPopMatrix();
    // Define a matriz de modelo e visualiza��o como matriz de trabalho atual
    glMatrixMode(GL_MODELVIEW);
}

/*
Menu Inicial, Menu Game Over e Menu Win
*/
void menu(int id){
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
    	glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
 		glDisable(GL_LIGHTING);
    	glDepthMask(GL_FALSE);
    	glBindTexture(GL_TEXTURE_2D, id_texturas[id]);
    	glBegin(GL_QUADS);
	    glColor3f(1.0, 1.0, 1.0);
	    glTexCoord2i(0, 0); glVertex2i(-1, -1);
	    glTexCoord2i(1, 0); glVertex2i(1, -1);
	    glTexCoord2i(1, 1); glVertex2i(1, 1);
	    glTexCoord2i(0, 1); glVertex2i(-1, 1);
	    glEnd();
	    glEnable(GL_DEPTH_TEST);
	    glEnable(GL_LIGHTING);
	    glDepthMask(GL_TRUE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void desenhaBonus(int tipo_bonus, float i, float j, int rotacao){
	switch(tipo_bonus){
	case 1:
		//Cria uma barreira de pedra ao redor da aguia.
		glBindTexture(GL_TEXTURE_2D, id_texturas[9]);
		visualBonus(i, j, rotacao);
		break;
	case 2:
		glBindTexture(GL_TEXTURE_2D, id_texturas[10]);
		//Adiciona uma vida ao jogador.
		visualBonus(i, j, rotacao);
		break;
	case 3:
		//Adiciona velocidade de movimento ao jogador e velocidade de tiro.
		glBindTexture(GL_TEXTURE_2D, id_texturas[11]);
		visualBonus(i, j, rotacao);
		break;
	case 4:
		//Permite andar na �gua.
		glBindTexture(GL_TEXTURE_2D, id_texturas[12]);
		visualBonus(i, j, rotacao);
		break;
	case 5:
		//Destroi blocos de metal.
		glBindTexture(GL_TEXTURE_2D, id_texturas[8]);
		visualBonus(i, j, rotacao);
		break;
	default:
		break;
	}
	
}

void desenhaTank(float i, float j, int direcao, float R, float G, float B){
	//Corpo do tank.
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, id_texturas[13]);
		glColor3f(R, G, B);
		glTranslatef (j*1, i*1, 0.5);
		glScalef (tam_tank, tam_tank, tam_tank);
		draw_object_smooth();
		glRotatef(direcao, 0.0 , 0.0 , 1.0);
		glDisable(GL_TEXTURE_2D);
		//Esteira direita.
		glPushMatrix();
			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(0.55, 0, 0);
			glScalef (0.3, 1.3, 0.6);
			draw_object_smooth();
		glPopMatrix();
		//Esteira esquerda.
		glPushMatrix();
			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(-0.55, 0, 0);
			glScalef (0.3, 1.3, 0.6);
			draw_object_smooth();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
		//Parte de cima do tank.
		glPushMatrix();
			glColor3f(R - 0.5, G - 0.5, B - 0.5);
			glTranslatef(0, 0, 0.5);
			glScalef(0.6, 0.6, 0.7);
			draw_object_smooth();
        glPopMatrix();
		//Cano do tank.
		glPushMatrix();
			glTranslatef(0, 0.5, 0.3);
			glScalef (0.3, 1.2, 0.3);
			draw_object_smooth();
		glPopMatrix();
    glPopMatrix();
}


 	

void criaMapa(Jogador jogador, Inimigo inimigo1, Inimigo inimigo2, Inimigo inimigo3){
	GLfloat w = 1.0, h = 1.0, x = 0, y = 0; 
	for (int i = 0; i < tamMapa; i++){
		for (int j = 0; j < tamMapa; j++){
			if (mapa[i][j] == 0.0){
				//Desenha o Ch�o.
				glBindTexture(GL_TEXTURE_2D, id_texturas[6]);
				chao(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 1.0){
				//Desenha a �gua.
				glBindTexture(GL_TEXTURE_2D, id_texturas[1]);
				agua(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 2.0){
				//Desenha o Tijolo.
				glBindTexture(GL_TEXTURE_2D, id_texturas[0]);
				tijolo(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 3.0){
				//Desenha o Metal.
				glBindTexture(GL_TEXTURE_2D, id_texturas[2]);
				metal(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 4.0){
				//Desenha o Arbusto.
				glBindTexture(GL_TEXTURE_2D, id_texturas[4]);
				arbusto(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 5.0){
				//Desenha o gelo.
				glBindTexture(GL_TEXTURE_2D, id_texturas[3]);
				gelo(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 6.0){
				//Desenha a Aguia.
				glBindTexture(GL_TEXTURE_2D, id_texturas[7]);
				aguia(i, j, x, y, h, w);
			}
			else if(mapa[i][j] == 7.0){
				//Parede.
				glBindTexture(GL_TEXTURE_2D, id_texturas[5]);
				parede(i, j, x, y, h, w);
			}
		}
	}
	
	//Se o jogador ainda estiver vivo, ele � desenhado.
	
	if(jogador.vivo && jogador.projetil.tiro && (game_over == false && game_win == false)){
		desenhaTank(jogador.x, jogador.y, jogador.direcaoCano, jogador.R, jogador.G, jogador.B);
		desenhaProjetil(jogador.projetil.xOrigem, jogador.projetil.yOrigem, jogador.projetil.direcao);
	}else{
		desenhaTank(jogador.x, jogador.y, jogador.direcaoCano, jogador.R, jogador.G, jogador.B);
	}
	
	if(inimigo1.vivo && inimigo1.projetil.tiro && (game_over == false && game_win == false)){
		desenhaTank(inimigo1.x, inimigo1.y, inimigo1.direcaoCano, inimigo1.R, inimigo1.G, inimigo1.B);
		desenhaProjetil(inimigo1.projetil.xOrigem, inimigo1.projetil.yOrigem, inimigo1.projetil.direcao);
	}else{
		desenhaTank(inimigo1.x, inimigo1.y, inimigo1.direcaoCano, inimigo1.R, inimigo1.G, inimigo1.B);
	}
	
	if(inimigo2.vivo && inimigo2.projetil.tiro &&  (game_over == false && game_win == false)){
		desenhaTank(inimigo2.x, inimigo2.y, inimigo2.direcaoCano, inimigo2.R, inimigo2.G, inimigo2.B);
		desenhaProjetil(inimigo2.projetil.xOrigem, inimigo2.projetil.yOrigem, inimigo2.projetil.direcao);
	}else{
		desenhaTank(inimigo2.x, inimigo2.y, inimigo2.direcaoCano, inimigo2.R, inimigo2.G, inimigo2.B);
	}
	
	if(inimigo3.vivo && inimigo3.projetil.tiro &&  (game_over == false && game_win == false)){
		desenhaTank(inimigo3.x, inimigo3.y, inimigo3.direcaoCano, inimigo3.R, inimigo3.G, inimigo3.B);
		desenhaProjetil(inimigo3.projetil.xOrigem, inimigo3.projetil.yOrigem, inimigo3.projetil.direcao);
	}else{
		desenhaTank(inimigo3.x, inimigo3.y, inimigo3.direcaoCano, inimigo3.R, inimigo3.G, inimigo3.B);	
	}

}
#endif