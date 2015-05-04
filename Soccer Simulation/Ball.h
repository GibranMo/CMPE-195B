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
    int destX;
    int destY;
    GLuint tex;
    GLuint texf;
    int speed;
    int n;
    
    
public:
    Ball(int xb, int yb, int wb, int hb, const char* image);
    void setPos(int xb, int yb);
    int getX();
    int getY();
    int getVelX();
    int getVelY();
    int getH();
    int getW();
    int getDestX();
    int getDestY();
    void setVel(int xv, int yv);
    void kick(int vel, int xp, int yp);
    
    void setX(int x);
    void setY(int y);
    void setVelX(int xv);
    void setVelY(int yv);
    void updatePos();
    void resetDest(int x, int y);
    
    GLuint getTex();
    GLuint getTexf();
};


#endif
