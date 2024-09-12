#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include<iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "mapa.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "audio.h"
#include "textos.h"
#include "fog.h"
#include <sstream>
using std::stringstream;
#include <string>
using std::string;

// Variaveis Globais
int h, w = 0;

//Partida


static int game_over_execucao = 0;
static int game_win_execucao = 0;
static int game_menu_execucao = 0;

//Bonus
bool bonus_ativo = false;
int posicaoBonus, tipo_bonus;
float bonusX, bonusY;
int rotacaoBonus;
int anima_bonus = 0;
float velocidade_bonus = 0;

//Movimentos Inimigos
int mov_inimigo1, mov_inimigo2, mov_inimigo3;

//TotalInimigos
int total_inimigos = 3; //Quantas vezes o inimigo pode respawnar.
int vidas_inimigos = 6; //O total de vidas dos inimigos.

//Instancia de Jogador.
//X, Y, Xinicial, Yinicial, Velocidade, Velocidade Inicial DirecaoCano, R, G, B, Vidas, Vivo. Projetil{ x, y, velocidade, distancia, direcao, tiro.}
Jogador jogador = {1, 4, 1, 4, 0.1, 0.1, 0, 1.0, 1.0, 0.0, 3, true, {1, 4, 0.25f, 5.0f, 0, false}};
float velocidade_inicial = jogador.velocidade;

//Instancia de Inimigo.
//X, Y, Xinicial, Yinicial, Velocidade, Velocidade Inicial DirecaoCano, R, G, B, vivo. Projetil{ x, y, velocidade, distancia, direcao, tiro.}
Inimigo inimigo1 = {13, 13, 13, 13, 0.1, 0.1, 180, 0.9, 1.0, 0.9, true, {13, 13, 0.25f, 5.0f, 0, false}};
Inimigo inimigo2 = {13, 6, 13, 6, 0.1, 0.1, 180, 1.0, 0.9, 0.9, true, {13, 13, 0.25f, 5.0f, 0, false}};
Inimigo inimigo3 = {13, 1, 13, 1, 0.1, 0.1, -90, 1.0, 1.0, 1.0, true, {13, 13, 0.25f, 5.0f, 0, false}};




void init(void);
void restart();
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
void atira(int value);
bool colidir(float jogadorX, float jogadorY, float tam_tank, float blocoX, float blocoY, float tam_bloco);
void bonus();
void aplicaBonus(int tipo_bonus);
void textura();
void manipulaInimigoAtingido(Jogador *jogador, Inimigo *inimigo);

void init(void){
  glClearColor (0.4, 0.4, 0.4, 0.0);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST); // Habilita o algoritmo Z-Buffer
  textura();
  // Ativa o modelo de sombreamento de Gouraud.
  glShadeModel(GL_SMOOTH);
	initFog();
}

void restart(){
	h, w = 0;

	//Partida


	game_over_execucao = 0;
	game_win_execucao = 0;
	game_menu_execucao = 0;

	//Bonus
	bonus_ativo = false;



	anima_bonus = 0;
	velocidade_bonus = 0;



	//TotalInimigos
	total_inimigos = 3; //Quantas vezes o inimigo pode respawnar.
	vidas_inimigos = 6; //O total de vidas dos inimigos.

	//Instancia de Jogador.
	//X, Y, Xinicial, Yinicial, Velocidade, Velocidade Inicial DirecaoCano, R, G, B, Vidas, Vivo. Projetil{ x, y, velocidade, distancia, direcao, tiro.}
	jogador = {1, 4, 1, 4, 0.1, 0.1, 0, 1.0, 1.0, 0.0, 3, true, {1, 4, 0.25f, 5.0f, 0, false}};
	velocidade_inicial = jogador.velocidade;

	//Instancia de Inimigo.
	//X, Y, Xinicial, Yinicial, Velocidade, Velocidade Inicial DirecaoCano, R, G, B, vivo. Projetil{ x, y, velocidade, distancia, direcao, tiro.}
	inimigo1 = {13, 13, 13, 13, 0.1, 0.1, 180, 0.9, 1.0, 0.9, true, {13, 13, 0.25f, 5.0f, 0, false}};
	inimigo2 = {13, 6, 13, 6, 0.1, 0.1, 180, 1.0, 0.9, 0.9, true, {13, 13, 0.25f, 5.0f, 0, false}};
	inimigo3 = {13, 1, 13, 1, 0.1, 0.1, -90, 1.0, 1.0, 1.0, true, {13, 13, 0.25f, 5.0f, 0, false}};


}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores
	glLoadIdentity();
    if (menu_inicial == false && game_over == false && game_win == false && menu_info == false){
	    playMenuAudio();
			playAudio();
	    background();
	    criaMapa(jogador, inimigo1, inimigo2, inimigo3);
	    desenhaVidasJogador(jogador.vida);
		
	    desenhaVidasInimigo(vidas_inimigos);
	    desenhaPlacarBonus();
		
	    if(bonus_ativo == true){
			bonus();
		}
	}
	else if (menu_inicial){
        
		game_menu_execucao++;
		if(game_menu_execucao >= 1){
			playMenuAudio();
		}
		menu(15);
	} 
	else if(game_over){
		game_over_execucao++;
		if(game_over_execucao == 1){
			playGameOverAudio();
		}
		menu(16);
	}
	else if(game_win){
		game_win_execucao++;
		gameWinAudio = true;
		if(game_win_execucao == 1){
			playGameWinAudio();
		}
        
		menu(17);
	}
	else if(menu_info){
		
		if(game_menu_execucao >= 1){
			playMenuAudio();
		}
		menu(18);
	}
    glutSwapBuffers();
}

void reshape (int w, int h){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    gluPerspective(45, (float)w/(float)h, 1.0, 100.0);
    gluLookAt(9.0,-5.0,15.0, 	// posi��o da c�mera (olho) 
			  9.0,6.0,0.0, 	// centro da cena
			  0.0,1.0,0.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
		//Atirar
		case 'q':
		case 'Q':
			if(game_over == false && game_win == false){
				if (jogador.projetil.tiro != true){
					#ifdef _WIN32
					mciSendString("play sounds/fire.wav", NULL, 0, NULL);
					#else
					loadWAV("sounds/fire.wav");
					SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
					SDL_PauseAudioDevice(audioDevice, 0);
					atiraAudio = false;
					
					#endif
					jogador.projetil.tiro = true;
					jogador.projetil.xOrigem = jogador.x;
					jogador.projetil.yOrigem = jogador.y;
					jogador.projetil.direcao = jogador.direcaoCano;
				}
			}
			break;
		case 'p':
		case 'P':
			if(menu_inicial){
				menu_inicial = false;
				menu_info = true;
			} 
			break;	
		case 'n':
			toggleFog();
			break;	
		case '+':
			increaseFog();
			break;
		case '-':
			decreaseFog();
			break;
		case 13:
			if(menu_inicial){
				menu_inicial = false;
			} else if(game_over){
				game_over = false;
			}
			break;
		case 8:
			if(menu_info || game_over || game_win){
				menu_inicial = true;
				menu_info = false;
				
				if(game_over || game_win){
					restart();
					game_over = false;
					game_win = false;
				}
			}
			break;	
		case 27:
			if(menu_inicial || game_over || game_win){
				exit(EXIT_SUCCESS); 
			}
			break;
		default:
			break;
	}
    glutPostRedisplay();
}

//************COLIS�ES DO JOGADOR ***********//

void colisaoTiroBlocoJogador(Jogador *jogador){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(jogador->projetil.xOrigem, jogador->projetil.yOrigem, tam_projetil, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				//Se for um bloco que deve colidir
				if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7)){
					jogador->projetil.tiro = false;
					//Se tiver com BonusGun, destroi metal.
					if(bonus_gun){
						if(mapa[i][j] == 3){
							mapa[i][j] = 0;
						}
					}
					else if((bonus_gun == false && mapa[i][j] == 3) || mapa[i][j] == 7){
						audioHitMetal = true;
					}
					
					//Se for tijolo.
					if(mapa[i][j] == 2){
						//Destroi o bloco.
						mapa[i][j] = 0;
					}
					if (mapa[i][j] == 6){
						mapa[i][j] = 0;
						//explosion = true;
						game_over = true;
						gameOverAudio = true;
					}
				}
			}
		}
	}
	glutPostRedisplay();
}


void colisaoTiroTanksJogador(Jogador *jogador, Inimigo *primeiroInimigo, Inimigo *segundoInimigo, Inimigo *terceiroInimigo){
	if (colidir(jogador->projetil.xOrigem, jogador->projetil.yOrigem, tam_projetil, primeiroInimigo->x * 1.0, primeiroInimigo->y * 1.0, 1.0) == true){
		manipulaInimigoAtingido(jogador, primeiroInimigo);
	}
	
	if (colidir(jogador->projetil.xOrigem, jogador->projetil.yOrigem, tam_projetil, segundoInimigo->x * 1.0, segundoInimigo->y * 1.0, 1.0) == true){
		manipulaInimigoAtingido(jogador, segundoInimigo);
	}
		
	if (colidir(jogador->projetil.xOrigem, jogador->projetil.yOrigem, tam_projetil, terceiroInimigo->x * 1.0, terceiroInimigo->y * 1.0, 1.0) == true){
		manipulaInimigoAtingido(jogador, terceiroInimigo);
	}
	glutPostRedisplay();
}

void manipulaInimigoAtingido(Jogador *jogador, Inimigo *inimigo){
	jogador->projetil.tiro = false;
	explosion = true;
	if(total_inimigos > 0){
		inimigo->x = inimigo->xInicial;
		inimigo->y = inimigo->yInicial;
		total_inimigos--;
		vidas_inimigos--;
		printf("Total Inimigos: %d\n", total_inimigos);
	}
	else{
		//Remove do tabuleiro
		vidas_inimigos--;
		inimigo->x = 99;
		inimigo->y = 99;
		inimigo->vivo = false;	
	}
}

//************ COLIS�ES DO INIMIGO ***********//

void colisaoTiroBlocoInimigo(Inimigo *inimigoAtual){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(inimigoAtual->projetil.xOrigem, inimigoAtual->projetil.yOrigem, tam_projetil, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				//Se for um bloco que deve colidir
				if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7)){
					inimigoAtual->projetil.tiro = false;
					//Se for tijolo.
					if(mapa[i][j] == 2){
						//Destroi o bloco.
						mapa[i][j] = 0;
					}
					if (mapa[i][j] == 6){
						mapa[i][j] = 0;
						explosion = true;
						game_over = true;
						gameOverAudio = true;
					}
				}
			}
		}
	}
	glutPostRedisplay();
}

void colisaoTiroTanksInimigo(Inimigo *inimigoAtual, Jogador *player){
	if (colidir(inimigoAtual->projetil.xOrigem, inimigoAtual->projetil.yOrigem, tam_projetil, player->x * 1.0, player->y * 1.0, 1.0) == true){
		inimigoAtual->projetil.tiro = false;
			//Decrementa a vida do jogador em 1.
			//Se ficar com 0 vidas, game over.
			printf("Vida: %d\n", player->vida);
			explosion = true;
			if(player->vida > 0){
				player->vida--;
				player->x = player->xInicial;
				player->y = player->yInicial;
			}
			else{
				//Remove do tabuleiro
				player->x = 99;
				player->y = 99;
				player->vivo = false;
				game_over = true;
				gameOverAudio = true;
			}
	}
	glutPostRedisplay();
}
	

void atira(int value){
	/*
	*Fun��o utilizada para fazer os tiros do jogador.
	*jogador.projetil.tiro verifica se o tiro foi efetuado.
	*jogador.projetil.direcao � a variavel que armazena a dire��o do tiro quando a tecla Q foi pressionada.	*
	*/
    if (jogador.projetil.tiro && jogador.vivo) {
    	switch(jogador.projetil.direcao){
			case 0:
				jogador.projetil.xOrigem += jogador.projetil.velocidade;
	        	if (jogador.projetil.xOrigem > jogador.x + jogador.projetil.distancia){
	            	jogador.projetil.tiro = false;
	            	jogador.projetil.xOrigem = jogador.x;
	        	}
				break;
			
			case 180:
				jogador.projetil.xOrigem -= jogador.projetil.velocidade;
				if (jogador.projetil.xOrigem < jogador.x - jogador.projetil.distancia){
		         	jogador.projetil.tiro = false;
		          	jogador.projetil.xOrigem = jogador.x;
				}
	        	break;
   	     
	        case -90:
				jogador.projetil.yOrigem += jogador.projetil.velocidade;
	        	if (jogador.projetil.yOrigem > jogador.y + jogador.projetil.distancia){
	            	jogador.projetil.tiro = false;
	            	jogador.projetil.yOrigem = jogador.y;
	        	}
	        	break;
	        
	        case 90:
				jogador.projetil.yOrigem -= jogador.projetil.velocidade;
	        	if (jogador.projetil.yOrigem < jogador.y - jogador.projetil.distancia){
	            	jogador.projetil.tiro = false;
	            	jogador.projetil.yOrigem = jogador.y;
	        	}
	        	break;
	        
			default:
				break;
		}
		colisaoTiroBlocoJogador(&jogador);
		colisaoTiroTanksJogador(&jogador, &inimigo1, &inimigo2, &inimigo3);
    }
    //Atualiza o tiro 60 frames por segundo, fazendo a anima��o da bala.
    glutPostRedisplay();
    glutTimerFunc(16, atira, 0);
}

void manipulaTiroInimigo(Jogador *jogador, Inimigo *inimigo){
	if (inimigo->projetil.tiro) {
    	switch(inimigo->projetil.direcao){
			case 0:
				inimigo->projetil.xOrigem += inimigo->projetil.velocidade;
	        	if (inimigo->projetil.xOrigem > inimigo->x + inimigo->projetil.distancia){
	            	inimigo->projetil.tiro = false;
	            	inimigo->projetil.xOrigem = inimigo->x;
	        	}
				break;
			
			case 180:
				inimigo->projetil.xOrigem -= inimigo->projetil.velocidade;
				if (inimigo->projetil.xOrigem < inimigo->x - inimigo->projetil.distancia){
		         	inimigo->projetil.tiro = false;
		          	inimigo->projetil.xOrigem = inimigo->x;
				}
	        	break;
   	     
	        case -90:
				inimigo->projetil.yOrigem += inimigo->projetil.velocidade;
	        	if (inimigo->projetil.yOrigem > inimigo->y + inimigo->projetil.distancia){
	            	inimigo->projetil.tiro = false;
	            	inimigo->projetil.yOrigem = inimigo->y;
	        	}
	        	break;
	        
	        case 90:
				inimigo->projetil.yOrigem -= inimigo->projetil.velocidade;
	        	if (inimigo->projetil.yOrigem < inimigo->y - inimigo->projetil.distancia){
	            	inimigo->projetil.tiro = false;
	            	inimigo->projetil.yOrigem = inimigo->y;
	        	}
	        	break;
	        
			default:
				break;
		}
		colisaoTiroBlocoInimigo(inimigo);
		colisaoTiroTanksInimigo(inimigo, jogador);
    }
}

void atiraInimigo(int value){
	/*
	*Fun��o utilizada para fazer os tiros do inimigo.
	*inimigo.projetil.tiro verifica se o tiro foi efetuado.
	*inimigo.projetil.direcao � a variavel que armazena a dire��o do tiro.
	*/
	//Para o inimigo 1.
    manipulaTiroInimigo(&jogador, &inimigo1);
    
    //Para o inimigo 2.
    manipulaTiroInimigo(&jogador, &inimigo2);
    
    //Para o inimigo 3.
    manipulaTiroInimigo(&jogador, &inimigo3);
    
    //Atualiza o tiro 60 frames por segundo, fazendo a anima��o da bala.
    glutPostRedisplay();
    glutTimerFunc(16, atiraInimigo, 0);
}

bool colidir(float jogadorX, float jogadorY, float tam_tank, float blocoX, float blocoY, float tam_bloco){
	if(jogadorY + tam_tank <= blocoY){
		return false;
	} 
	else if(jogadorY >= blocoY + tam_bloco){
		return false;
	} 
	else if(jogadorX + tam_tank <= blocoX){
		return false;
	} 
	else if(jogadorX >= blocoX + tam_bloco){
		return false;
	} 
	
	return true;
}

void colisaoBlocoMovimentoJogador(unsigned char key, Jogador *jogador){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if(colidir(jogador->x, jogador->y, tam_tank, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				//Se o bonus boat tiver sido pego.
				if(bonus_boat){
					//Colide com os blocos mas n�o com a �gua.
					if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7)){
						if(key==GLUT_KEY_UP) jogador->x -= jogador->velocidade;
				    	else if(key==GLUT_KEY_DOWN) jogador->x += jogador->velocidade;
				    	else if(key==GLUT_KEY_LEFT) jogador->y += jogador->velocidade;
				    	else if(key==GLUT_KEY_RIGHT) jogador->y -= jogador->velocidade;
					}
					
				}
				//Colide com os blocos e a agua.
				else{
					if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7) || mapa[i][j] == 1){
						if(key==GLUT_KEY_UP) jogador->x -= jogador->velocidade;
				    	else if(key==GLUT_KEY_DOWN) jogador->x += jogador->velocidade;
				    	else if(key==GLUT_KEY_LEFT) jogador->y += jogador->velocidade;
				    	else if(key==GLUT_KEY_RIGHT) jogador->y -= jogador->velocidade;
					}
					
				}
				//Andar mais r�pido no gelo.
				if(mapa[i][j] == 5){
					jogador->velocidade = jogador->velocidadeInicial*1.5;
				}
				else{
					if(jogador->velocidadeInicial > velocidade_bonus){
						jogador->velocidade = jogador->velocidadeInicial;
					}
					else{
						jogador->velocidade = velocidade_bonus;	
					}
				}
				//Obter um b�nus no mapa.
				if(bonus_ativo == true && bonusX == i && bonusY == j){
					bonus_ativo = false;
					audioPegaBonus = true;
					aplicaBonus(tipo_bonus);
				}
			}
		}
	}
}

void colisaoBlocoMovimentoInimigo(int movimentoInimigo, Inimigo *inimigoAtual){
	for(int i = 0; i < tamMapa; i++){
		for(int j = 0; j < tamMapa; j++){
			if (colidir(inimigoAtual->x, inimigoAtual->y, tam_tank, i * tam_bloco, j * tam_bloco, tam_bloco) == true){
				if((mapa[i][j] == 2) || (mapa[i][j] == 3) || (mapa[i][j] == 6) || (mapa[i][j] == 7) || mapa[i][j] == 1){
					if(movimentoInimigo==1) inimigoAtual->x -= inimigoAtual->velocidade;
				    else if(movimentoInimigo==2) inimigoAtual->x += inimigoAtual->velocidade;
				    else if(movimentoInimigo==4) inimigoAtual->y += inimigoAtual->velocidade;
				    else if(movimentoInimigo==3) inimigoAtual->y -= inimigoAtual->velocidade;
				}
				//Anda mais r�pido no gelo.
				if(mapa[i][j] == 5){
					inimigoAtual->velocidade = inimigoAtual->velocidadeInicial + (inimigoAtual->velocidadeInicial/2);
				}
				else{
					inimigoAtual->velocidade = inimigoAtual->velocidadeInicial;
				}
			}
		}
	}
}

int gerarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

void movimentaInimigo(Inimigo *inimigoAtual, int movimento){
	switch(movimento){
		case 1:
			inimigoAtual->x += inimigoAtual->velocidade;
			inimigoAtual->direcaoCano = 0;
			glutPostRedisplay();
			break;
		
		case 2:
			inimigoAtual->x -= inimigoAtual->velocidade;
			inimigoAtual->direcaoCano = 180;
			glutPostRedisplay();
			break;
		
		case 3:
			inimigoAtual->y += inimigoAtual->velocidade;
			inimigoAtual->direcaoCano = -90;
			glutPostRedisplay();
			break;
		
		case 4:
			inimigoAtual->y -= inimigoAtual->velocidade;
			inimigoAtual->direcaoCano = 90;
			glutPostRedisplay();
			break;
		
		default:
			break;
	}
	colisaoBlocoMovimentoInimigo(movimento, inimigoAtual);
}

void sorteiaMovimento(int value){
	mov_inimigo1 = gerarNumeroAleatorio(1,4);
	mov_inimigo2 = gerarNumeroAleatorio(1,4);
	mov_inimigo3 = gerarNumeroAleatorio(1,4);
	
	glutPostRedisplay();
	glutTimerFunc(2000, sorteiaMovimento, 0);
}

void esperaMovimento(int value){
	if (menu_inicial == false){
		movimentaInimigo(&inimigo1, mov_inimigo1);
		if (inimigo1.projetil.tiro != true && inimigo1.vivo == true){
			inimigo1.projetil.tiro = true;
			inimigo1.projetil.xOrigem = inimigo1.x;
			inimigo1.projetil.yOrigem = inimigo1.y;
			inimigo1.projetil.direcao = inimigo1.direcaoCano;
		}
		movimentaInimigo(&inimigo2, mov_inimigo2);
		if (inimigo2.projetil.tiro != true && inimigo2.vivo == true){
			inimigo2.projetil.tiro = true;
			inimigo2.projetil.xOrigem = inimigo2.x;
			inimigo2.projetil.yOrigem = inimigo2.y;
			inimigo2.projetil.direcao = inimigo2.direcaoCano;
		}
		movimentaInimigo(&inimigo3, mov_inimigo3);
		if (inimigo3.projetil.tiro != true && inimigo3.vivo == true){
			inimigo3.projetil.tiro = true;
			inimigo3.projetil.xOrigem = inimigo3.x;
			inimigo3.projetil.yOrigem = inimigo3.y;
			inimigo3.projetil.direcao = inimigo3.direcaoCano;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(16, esperaMovimento, 0);
}

//Movimentos do jogador.
void specialKeyboard(int key, int x, int y){
	if(game_over == false && game_win == false){
		switch(key){
			case GLUT_KEY_UP:
				jogador.x += jogador.velocidade;
				jogador.direcaoCano = 0;
				glutPostRedisplay();
				break;
			case GLUT_KEY_DOWN:
				jogador.x -= jogador.velocidade;
				jogador.direcaoCano = 180;
				glutPostRedisplay();
				break;
			case GLUT_KEY_RIGHT:
				jogador.y += jogador.velocidade;
				jogador.direcaoCano = -90;
				glutPostRedisplay();
				break;
			case GLUT_KEY_LEFT:
				jogador.y -= jogador.velocidade;
				jogador.direcaoCano = 90;
				glutPostRedisplay();
				break;
			default:
				break;
		}
		colisaoBlocoMovimentoJogador(key, &jogador);
	}
}

void verificaStatus(int value){
	//Verifica se ocorreu vit�ria.
	if(jogador.vivo && (inimigo1.vivo == false && inimigo2.vivo == false && inimigo3.vivo == false)){
		game_win = true;
	}
	glutPostRedisplay();
	glutTimerFunc(16, verificaStatus, 0);
}

//Preciso fazer uma fun��o pra remover a wall depois de 10 segundos.
void bonusWall(int value){
	if(bonus_wall){
		bonus_wall = false;
		qtd_bonus_ativos--;
		if(mapa[2][6] == 3){
			mapa[2][6] = 2;
		}
		if(mapa[1][6] == 3){
			mapa[1][6] = 2;
		}
		if(mapa[2][7] == 3){
			mapa[2][7] = 2;
		}
		if(mapa[2][8] == 3){
			mapa[2][8] = 2;
		}
		if(mapa[1][8] == 3){
			mapa[1][8] = 2;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(15000, bonusWall, 0);
}

//Fun��o que aplica o b�nus no jogador.
void aplicaBonus(int tipo_bonus){
	switch(tipo_bonus){
	case 1:
		if (bonus_wall != true){
			qtd_bonus_ativos++;
		}
		bonus_wall = true;
		printf("Paredes refor�adas para a aguia!\n");
		mapa[2][6] = 3;
		mapa[1][6] = 3;
		mapa[2][7] = 3;
		mapa[2][8] = 3;
		mapa[1][8] = 3;
		glutTimerFunc(15000, bonusWall, 0);
		glutPostRedisplay();
		break;
	case 2:
		if(bonus_vida !=  true){
			qtd_bonus_ativos++;
		}
		bonus_vida = true;
		jogador.vida++;
		audioLife = true;
		printf("Uma vida a mais, Vidas: %d", jogador.vida);
		break;
	case 3:
		if(bonus_estrela !=  true){
			qtd_bonus_ativos++;
		}
		bonus_estrela = true;
		jogador.velocidade += 0.1;
		jogador.projetil.velocidade += 0.2;
		velocidade_bonus = jogador.velocidade;
		printf("Velocidade de movimento e de projetil aumentadas!\nVelocidade de movimento: %f\nVelocidade de projetil: %f", jogador.velocidade, jogador.projetil.velocidade);
		break;
	case 4:
		if(bonus_boat !=  true){
			qtd_bonus_ativos++;
		}
		bonus_boat = true;
		printf("Agora e permitido andar sobre a �gua!\n");
		break;
	case 5:
		if(bonus_gun !=  true){
			qtd_bonus_ativos++;
		}
		bonus_gun = true;
		printf("Agora e permitido quebrar metal!\n");
		break;
	default:
		break;
	}
}

void animacaoBonus(int value){
	rotacaoBonus+=5;
	if(rotacaoBonus == 360){
		rotacaoBonus = 0;
	}
	glutPostRedisplay();
	glutTimerFunc(16, animacaoBonus,0);
}

//A cada 15 segundos sorteia um bonus em um lugar do mapa.
void sorteiaBonus(int value){
	if(bonus_ativo == false){
		audioApareceBonus = true;
		posicaoBonus = gerarNumeroAleatorio(1, 3);
		tipo_bonus = gerarNumeroAleatorio(1, 5);
		bonus_ativo = true;
	}
	glutPostRedisplay();
	glutTimerFunc(15000, sorteiaBonus, 0);
}

//Posiciona e renderiza a caixinha de bonus.
void bonus(){
	switch(posicaoBonus){
		case 1:
			bonusX = 5;
			bonusY = 4;
			desenhaBonus(tipo_bonus, bonusX, bonusY, rotacaoBonus);
			break;
		case 2:
			bonusX = 4;
			bonusY = 10;
			desenhaBonus(tipo_bonus, bonusX, bonusY, rotacaoBonus);
			break;
		case 3:
			bonusX = 9;
			bonusY = 7;
			desenhaBonus(tipo_bonus, bonusX, bonusY, rotacaoBonus);
			break;
		default:
			break;
	}
}

