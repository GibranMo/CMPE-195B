//
//  Layout.h
//  Soccer1
//
//  Created by Gibran Morales on 3/2/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#ifndef Soccer1_Layout_h
#define Soccer1_Layout_h

#include <vector>
#include <iostream>
#include "Player.h"
#include "Team.h"
#include "Ball.h"

using namespace std;

class Layout
{
private:
    int screenW = 1150;
    int screenH = 700;
    
    Team * homeTeam;
    Team * awayTeam;
    Player * playerHasBall;
    Ball * ball;
    bool someoneHasBall;
    
    void setSomeoneHasBall();
    double distance(Player * p1, Player * p2);
    
    void pass(Player * receivingPlayer);
    
    bool isRectangleAreaInFrontClear(Player * p, Player * p2);
    
    
public:
    Player * hasBall();
    Layout(Team * homeT, Team * awayT, Ball * b);
    void initialSetUp433();
    void hasBall(Player * p);
    Team * getHomeTeam();
    Team * getAwayTeam();
    Ball * getBall();
    //Player * hasBall();
    vector <Player *> getTeamMatesWithin(Player * p, int range);
    double getDistance(int x1, int x2, int y1, int y2);  //A distance between two specified points
    double getDistanceBall(Player * p); //A distance with respect to the ball and a speified point
    
    Team * getDefendingTeam();
    Team * getAttackingTeam();
    
    vector <Player *> getAvailablePlayers(Player * p);
    int countTeammatesInFront(Player * p); //Does not matter which direction player is facing
    int countTeamatesInDirection(Player * p); //Takes into consideration what direction player is facing
    void analyzeField(Player * p);
    void setPlayerWithPossBall(Player *p); //Pinpoints the ball at the tip of the Player
    double getShootingAngle(Player * p);
    
    
    
    
    //Test
    int testInt();
    
    
    
};


#endif