//
//  Ball.cpp
//  Soccer Simulation
//
//  Created by Carlos Toledo on 3/25/15.
//  Copyright (c) 2015 Carlos Toledo. All rights reserved.
//

#include "Ball.h"

Ball::Ball(int xb, int yb, int wb, int hb, const char* image){
    x = xb;
    y = yb;
    w = wb;
    h = hb;
    tex = glTexImageTGAFile(image);
}

void Ball::setPos(int xb, int yb){
    x = xb;
    y = yb;
}

int Ball::getX(){
    return x;
}

int Ball::getY(){
    return y;
}

int Ball::getVelX(){
    return y;
}

int Ball::getVelY(){
    return y;
}

void Ball::setVel(int xv, int yv){
    velX = xv;
    velY = yv;
}

void Ball::setX(int X)
{
    x = X;
}

void Ball::setY(int Y)
{
    y = Y;
}
GLuint Ball::getTex(){
    return tex;
}