//
//  Ball.h
//  Soccer Simulation
//
//  Created by Carlos Toledo on 3/25/15.
//  Copyright (c) 2015 Carlos Toledo. All rights reserved.
//

#ifndef __Soccer_Simulation__Ball__
#define __Soccer_Simulation__Ball__

#include <stdio.h>
#include "DrawUtils.h"

class Ball {

private:
    int w;
    int h;
    int x;
    int y;
    int velX;
    int velY;
    GLuint tex;
    
    
public:
    Ball(int xb, int yb, int wb, int hb, const char* image);
    void setPos(int xb, int yb);
    int getX();
    int getY();
    int getVelX();
    int getVelY();
    void setVel(int xv, int yv);
    GLuint getTex();
};


#endif /* defined(__Soccer_Simulation__Ball__) */
