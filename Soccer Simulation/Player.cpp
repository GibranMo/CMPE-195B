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

Player::Player(string n, int xp, int yp, const char* image, string teamN, string faceAngle)
{
    name = n;
    x = xp;
    y = yp;
    velY = 0;
    velX = 0;
    tex = glTexImageTGAFile(image);
    teamName = teamN;
    
    Player::setFaceAngle(faceAngle);
    
}

string Player::getTeamName()
{
    
    return teamName;
    
}
string Player::getName()
{
    return name;
}

void Player::setFaceAngle(string direction)
{
    
    angle = direction;
    
    if (angle == "N")
    {
        tex = glTexImageTGAFile("images/Nbarca.tga");
    }
    else if (angle == "NE")
    {
        tex = glTexImageTGAFile( "images/NEbarca.tga");
    }
    else if (angle == "E")
    {
        tex = glTexImageTGAFile( "images/Ebarca.tga");
    }
    else if (angle == "SE")
    {
        tex = glTexImageTGAFile( "images/SEbarca.tga");
    }
    else if (angle == "S")
    {
        tex = glTexImageTGAFile( "images/Sbarca.tga");
    }
    else if (angle == "SW")
    {
        tex = glTexImageTGAFile( "images/SWbarca.tga");
    }
    else if (angle == "W")
    {
        tex = glTexImageTGAFile( "images/Wbarca.tga");
    }
    else if (angle == "NW")
    {
        tex = glTexImageTGAFile( "images/NWbarca.tga");
    }
    else
    {
        cout << "something went wrong!" << endl;
    }
    
    
}

void Player::setAreaPosition(int x1, int x2, int y1, int y2)
{
    posX1 = x1;
    posX2 = x2;
    posY1 = y1;
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

int Player::getVelX(){
    return velX;
}

int Player::getVelY(){
    return velY;
}

void Player::setVelX(int vx){
    velX = vx;
}

void Player::setVelY(int vy){
    velY = vy;
}

string Player::getAngle()
{
    return angle;
}

GLuint Player::getTex()
{
    return tex;
}

