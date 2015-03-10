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


Player::Player(string n, int xp, int yp)
{
    name = n;
    x = xp;
    y = yp;
}

string Player::getName()
{
    return name;
}

void Player::setAreaPosition(int w, int x, int y, int z)
{
    posUL = w;
    posUR = x;
    posLL = y;
    posLR = z;
}

void Player::setPos( int xp, int yp){
    x = xp;
    y = yp;
}

int Player::getX(){
    return x;
}

int Player::getY(){
    return y;
}