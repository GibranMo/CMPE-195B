//
//  DrawUtils.h
//  Soccer Simulation
//
//  Created by Carlos Toledo on 2/10/15.
//  Copyright (c) 2015 Carlos Toledo. All rights reserved.
//

#ifndef __Soccer_Simulation__DrawUtils__
#define __Soccer_Simulation__DrawUtils__

#include<SDL2/SDL.h>
#include<GL/glew.h>

GLuint glTexImageTGAFile(const char* filename, int* outWidth, int* outHeight);

void glDrawSprite(GLuint tex, int x, int y, int w, int h);

void glDrawSprite2(GLuint tex, int x, int y, int w, int h);

void glDrawLines();



#endif /* defined(__Soccer_Simulation__DrawUtils__) */



