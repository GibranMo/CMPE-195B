#ifndef DrawUtils_H
#define DrawUtils_H

#include<SDL2/SDL.h>
#include<GL/glew.h>

GLuint glTexImageTGAFile(const char* filename, int* outWidth, int* outHeight);

void glDrawSprite(GLuint tex, int x, int y, int w, int h);

#endif