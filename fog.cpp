#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "fog.h"

bool isFogEnabled = false;
float fogDensity = 10.0f; // Start at .5f so it can be increased or decreased
float fogChangeRate = 2.0f;

void initFog(){
	float cor[] = { .5f, .5f, .5f };
	glClearColor(cor[0], cor[1], cor[2], 1.0f);
	glFogi(GL_FOG_MODE, GL_EXP);        
	glFogfv(GL_FOG_COLOR, cor);         
	glFogf(GL_FOG_DENSITY, fogDensity); 
	glHint(GL_FOG_HINT, GL_DONT_CARE);  
	glFogf(GL_FOG_START, -5.0f);         
	glFogf(GL_FOG_END, 5.0f);           
}

void toggleFog(){
	isFogEnabled = !isFogEnabled;
	if(isFogEnabled){
		glEnable(GL_FOG);
	}else{
		glDisable(GL_FOG);
	}
}

void increaseFog(){
	fogDensity += fogChangeRate;
	glFogf(GL_FOG_DENSITY, fogDensity); // Densidade
}

void decreaseFog(){
	fogDensity -= fogChangeRate;
	glFogf(GL_FOG_DENSITY, fogDensity); // Densidade
}
