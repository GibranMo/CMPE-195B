//
//  SPlayer.cpp
//  Soccer1
//
//  Created by Gibran Morales on 3/2/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#include "Player.h"
#include <vector>
#include <iostream>
#include "Team.h"


Player::Player(string n, int xp, int yp, GLuint texture)
{
    name = n;
    x = xp;
    y = yp;
    tex = texture;
}

string Player::getName()
{
    return name;
}

/*
    x
    |------------------>
y   |
    |
    |
    V
*/

// left most, right most, upper most, lower most
void Player::setAreaPosition(int x1, int x2, int y1, int y2)
{
    posX1 = x1;
    posX2 = x2;
    posY1= y1;
    posY2 = y2;
}

vector <int> Player:: getPosArea()
{
    vector <int> coordArea (4);
    
    coordArea.push_back(posX1);
    coordArea.push_back(posX2);
    coordArea.push_back(posY1);
    coordArea.push_back(posY2);
    
    return coordArea;
    
}

void Player::setPos( int xp, int yp)
{
    x = xp;
    y = yp;
}

int Player::getX(){
    return x;
}

int Player::getY(){
    return y;
}