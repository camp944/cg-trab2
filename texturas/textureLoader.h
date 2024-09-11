#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <iostream>


// Variável global para armazenar a textura


void loadTexture(const char* filename, GLuint* texId, int width, int height) {
   
   glGenTextures(1, texId);

    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
    if (image == nullptr) {
        std::cerr << "Erro ao carregar a textura: " << SOIL_last_result() << std::endl;
        return;
    }

    glBindTexture(GL_TEXTURE_2D, (*texId));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SOIL_free_image_data(image);
}


#endif