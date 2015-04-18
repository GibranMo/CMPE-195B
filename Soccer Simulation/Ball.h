//
//  Ball.h
//  Soccer1
//
//  Created by Gibran Morales on 3/25/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#ifndef Soccer1_Ball_h
#define Soccer1_Ball_h

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
    
    void setX(int X);
    void setY(int Y);
    
    GLuint getTex();
};


#endif
