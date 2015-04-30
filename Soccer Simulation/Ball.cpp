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
    velX = 0;
    velY = 0;
    destX = 0;
    destY = 0;
    n = 10;
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

void Ball::setX(int X)
{
    x = X;
}

void Ball::setY(int Y)
{
    y = Y;
}

int Ball::getVelX(){
    return velX;
}

int Ball::getVelY(){
    return velY;
}

void Ball::setVel(int xv, int yv){
    velX = xv;
    velY = yv;
}

void Ball::setVelX(int xv)
{
    velX = xv;
}

void Ball::setVelY(int yv)
{
    velY = yv;
}


int Ball::getH(){
    return h;
}

int Ball::getW(){
    return w;
}

GLuint Ball::getTex(){
    return tex;
}

void Ball::resetDest(int x, int y){
    destX = x;
    destY = y;
}

//destination point = (xp, yp)
void Ball::kick(int s, int xp, int yp){
    destX = xp;
    destY = yp;
    speed = s;
}

void Ball::updatePos(){
    
    if(destX == 0 && destY == 0)
        return;
    
    int vel;
    if(n % speed == 0){
        vel = 1;
    }
    else {
        vel = 0;
    }
    n++;
    
    if(x == destX)
        setVelX(0);
    else if(x > destX)
        setVelX(-vel);
    else if(x < destX)
        setVelX(vel);
    if(y == destY)
        setVelY(0);
    if(y > destY)
        setVelY(-vel);
    else if(y < destY)
        setVelY(vel);
    
    x += velX;
    y += velY;
    
}