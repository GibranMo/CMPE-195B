//
//  SPlayer.h
//  Soccer1
//
//  Created by Gibran Morales on 3/2/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#ifndef Soccer1_SPlayer_h
#define Soccer1_SPlayer_h

#include <string>
using namespace std;

class SPlayer
{
private:
    string name;
    int partOfWhich; // 1 or 2
    bool isControllingBall = false;
    bool isAttacking = false;
    bool isStationary = false;
    bool isGauging = false;
    
    
    /*
     The following set of 4 points represent a rectangular area, which in turn 
     represents that represents the position of the player.
     He can go outside this area, but spends most of its time inside it
     */
    
    int posUL; //upper left
    int posUR; //upper right
    int posLL; //lower left
    int posLR; //lower right
    
    /*
     A bunch of other attributs like all the skills from fifa.
     
     */
    
public:
    SPlayer(string n);
    void move(int x, int y); //
    void stop();
    void rotate(float degrees);
    int getYPos();
    int getXPos();
    
    int setPos(int x, int y);
    /*
     For clarity, the use of this method basically indicates that no one is in possesion after the ball.  
     The main function of this method is to use the move() method in Player.
     */
    void goAfterLooseBall();
    void setAreaPosition(int w, int x, int y, int z);
    string getName();
    
    void passBall();
    void shootBall();
    void runWithBall();
    void jogWithBll();
    void dribble();
    void tackle();
    
    void runBackwards();
    
    
    

};

#endif
