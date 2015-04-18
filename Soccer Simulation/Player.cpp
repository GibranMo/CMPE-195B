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

Player::Player(string n, int xp, int yp, int wp, int hp, const char* image, string teamN, string faceAngle,
               int PAC, int SHO, int PAS, int DRI, int PHY, int DEF, int OVR)
{
    name = n;
    x = xp;
    y = yp;
    w = wp;
    h = hp;
    velY = 0;
    velX = 0;
    tex = glTexImageTGAFile(image);
    teamName = teamN;
    
    pace = PAC;
    shot = SHO;
    pass = PAS;
    dribbling = DRI;
    physical = PHY;
    defending = DEF;
    overall = OVR;
    
    
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
        if (this->getTeamName() == "homeTeam")
            tex = glTexImageTGAFile("images/Nbarca.tga");
        else
            tex = glTexImageTGAFile("images/madridPlayer3.tga");
    }
    else if (angle == "NE")
    {
        if (this->getTeamName() == "homeTeam")
            tex = glTexImageTGAFile("images/NEbarca.tga");
        else
            tex = glTexImageTGAFile("images/NEmadrid2.tga");
    }
    else if (angle == "E")
    {
        if (this->getTeamName() == "homeTeam")
            tex = glTexImageTGAFile("images/Ebarca.tga");
        else
            tex = glTexImageTGAFile("images/EmadridPlayer3.tga");
    }
    else if (angle == "SE")
    {
        if (this->getTeamName() == "homeTeam")
            tex = glTexImageTGAFile("images/SEbarca.tga");
        else
            tex = glTexImageTGAFile("images/SEmadrid2.tga");
    }
    else if (angle == "S")
    {
        if (this->getTeamName() == "homeTeam")
            tex = glTexImageTGAFile("images/Sbarca.tga");
        else
            tex = glTexImageTGAFile("images/SmadridPlayer3.tga");
    }
    else if (angle == "SW")
    {
        if (this->getTeamName() == "homeTeam")
            tex = glTexImageTGAFile("images/SWbarca.tga");
        else
            tex = glTexImageTGAFile("images/SWmadrid2.tga");
    }
    else if (angle == "W")
    {
        if (this->getTeamName() == "homeTeam")
            tex = glTexImageTGAFile("images/Wbarca.tga");
        else
            tex = glTexImageTGAFile("images/WmadridPlayer3copy.tga");
    }
    else if (angle == "NW")
    {
        if (this->getTeamName() == "homeTeam")
            tex = glTexImageTGAFile("images/NWbarca.tga");
        else
            tex = glTexImageTGAFile("images/NWmadrid2.tga");
    }
    else
    {
        cout << "something went wrong!" << endl;
    }
    
    
}

void Player::setXPos(int newX)
{
    x = newX;
}

void Player::setYPos(int newY)
{
    y = newY;
}

void Player::setAreaPosition(int x1, int x2, int y1, int y2)
{
    
    cout << "NAME: " << name << endl;
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

int Player::getH(){
    return h;
}

int Player::getW(){
    return w;
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

int Player::getPace()
{
    return pace;
}

int Player::getShot()
{
    return shot;
}

int Player::getPass()
{
    return pass;
}

int Player::getDef()
{
    return defending;
}

int Player::getDrib()
{
    return dribbling;
}

int Player::getPhy()
{
    return physical;
}

int Player::getOverall()
{
    return overall;
    
}


