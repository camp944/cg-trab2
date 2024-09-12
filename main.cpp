#include "gameBase.h"

int main(int argc, char** argv){
	
	glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);                                                                                                                                                                                                           
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(250,150); 
    glutCreateWindow ("Tank-1990 3D");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat light_color[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING); //Ativa o modelo de iluminacao
    glEnable(GL_LIGHT0); //Ativa a Luz 0. O OpenGL suporta pelo menos 8 pontos de luz                                                        
    glEnable(GL_DEPTH_TEST);


    // Inicia as caracteristicas gerais dos materiais
	GLfloat mat_ambient_diffuse[] = {0.0, 0.0, 0.0, 0.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_diffuse);                                        
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL); //Um ou mais parametros do material rastreiam a cor atual do glColor.
    if (!initAudio()) {// Inicializa o audio                                                                                                                                                                        
        std::cerr << "Falha ao inicializar o áudio." << std::endl;
        return -1;
    }

    // define a cor com a qual a tela sera apagada
    glClearColor (0.4, 0.4, 0.4, 0.0);
    glutTimerFunc(0, atira, 0); //(mseg, timer, value)
    glutTimerFunc(0, esperaMovimento, 0);
    glutTimerFunc(0, atiraInimigo, 0);
    glutTimerFunc(0, verificaStatus, 0);
    glutTimerFunc(15000, sorteiaBonus, 0);
    glutTimerFunc(0, sorteiaMovimento, 0);
    glutTimerFunc(0, animacaoBonus, 0);
    restart();
    init();
    
    glutMainLoop();
    
	return EXIT_SUCCESS;
}