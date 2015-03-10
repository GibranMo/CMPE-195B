//
//  SPlayer.cpp
//  Soccer1
//
//  Created by Gibran Morales on 3/2/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#include "SPlayer.h"
#include <vector>
#include <iostream>
#include "Team.h"


SPlayer::SPlayer(string n)
{
    name = n;
}

string SPlayer::getName()
{
    return name;
}

void SPlayer::setAreaPosition(int w, int x, int y, int z)
{

    posUL = w;
    posUR = x;
    posLL = y;
    posLR = z;

}