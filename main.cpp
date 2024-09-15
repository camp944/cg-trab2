#include "gameBase.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(250, 150);
    glutCreateWindow("Tank-1990 3D");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

    
    glEnable(GL_DEPTH_TEST);

    // Inicia as características gerais dos materiais
    GLfloat mat_ambient_diffuse[] = {0.0, 0.0, 0.0, 0.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_diffuse);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL); // Um ou mais parâmetros do material rastreiam a cor atual do glColor.
    if (!initAudio()) { // Inicializa o áudio
        std::cerr << "Falha ao inicializar o áudio." << std::endl;
        return -1;
    }

    // Define a cor com a qual a tela será apagada
    glClearColor(0.4, 0.4, 0.4, 0.0);
    glutTimerFunc(0, atira, 0); // (mseg, timer, value)
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