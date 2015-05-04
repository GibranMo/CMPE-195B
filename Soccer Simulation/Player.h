//
//  SPlayer.h
//  Soccer1
//
//  Created by Gibran Morales on 3/2/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#ifndef Soccer1_Player_h
#define Soccer1_Player_h

#include <vector>
#include <string>
#include "DrawUtils.h"
using namespace std;


class Player
{
private:
    string name;
    int partOfWhich; // 1 or 2
    bool isControllingBall = false;
    bool isAttacking = false;
    bool isStationary = false;
    bool isGauging = false;
    bool defending = false;
    string teamName;
    enum facingAngle { E,  NE, N, NW, W, SW, S, SE};
    string angle; // this is alternative to the member 'facingAngle'. 'N' = north, 'NE' = northeast, ect.
    
    /*
     The following set of 4 points represent a rectangular area, which in turn
     represents that represents the position of the player.
     He can go outside this area, but spends most of its time inside it
     */
    
    int posX1; //right most
    int posX2; //left most
    int posY1; //upper most
    int posY2; //lower most
    
    double x;
    double y;
    int w;
    int h;
    int velX;
    int velY;
    GLuint tex;
    int destX;
    int destY;
    
    
    int counter;
    
    //These is the exact positon within the 'square area' each player is assigned. This is their default positions.
    int fieldX;
    int fieldY;
    
    /*
     A bunch of other attributes like all the skills from fifa.
     
     */
    
    int pace;
    int shot;
    int pass;
    int dribbling;
    int physical;
    int defense;
    int overall;
    
public:
    //constructor
    Player(string n, int xp, int yp, int wp, int hp, const char* image, string teamN, string faceAngle,
           int PAC, int SHO, int PAS, int DRI, int PHY, int DEF, int OVR);
    //getters / setters
    int getY();
    int getX();
    string getName();
    int getVelX();
    int getVelY();
    int getH();
    int getW();
    GLuint getTex();
    void setVelX(int vx);
    void setVelY(int vy);
    void setPos(int xp, int yp);
    vector <int> getPosArea();
    
    void incrementCounter();
    int getCounter();
    
    
    //actions
    //void rotate(float degrees);
    void goAfterLooseBall();
    void setXPos(int x);
    void setYPos(int y);
    void setAreaPosition(int x1, int x2, int y1, int y2);
    void passBall();
    
    void shootBall();
    void runWithBall();
    void jogWithBall();
    void dribble();
    void tackle();
    void runBackwards();
    void stop();
    void setIsDefending(bool mode);
    
    string getTeamName();
    void setFacingAngle(facingAngle); //change the direction a player points
    void setFaceAngle(string direction); //change the direction a player points (alternative)
    string getAngle();
    
    void setFieldPosition(int x, int y);
    
    bool isWithinArea();
    bool isDefending();
    
    int getDestX();
    int getDestY();
    
    /*
     get skill attribures methods
     */
    
    int getPace();
    int getShot();
    int getPass();
    int getDrib();
    int getDef();
    int getPhy();
    int getOverall();
    
    void dribble(int xp, int yp);
    void updatePos();
    
    
    
};


#endif
