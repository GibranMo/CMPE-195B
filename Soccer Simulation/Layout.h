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
    Team * homeTeam;
    Team * awayTeam;
    Player * playerHasBall;
    Ball * ball;
    bool someoneHasBall;
    
    void setSomeoneHasBall();
    double distance(Player * p1, Player * p2);
    
    void pass(Player * receivingPlayer);
    
public:
    
    Layout(Team * homeT, Team * awayT, Ball * b);
    void initialSetUp433();
    void hasBall(Player * p);
    Team * getHomeTeam();
    Team * getAwayTeam();
    Ball * getBall();
    Player * hasBall();
    vector <Player *> getTeamMatesWithin80(Player * p);
    
    vector <Player *> getAvailablePlayers(Player * p);
    int countTeammatesInFront(Player * p); //Does not matter which direction player is facing
    int countTeamatesInDirection(Player * p); //Takes into consideration what direction player is facing
    void analyzeField(Player * p);
    void setPlayerWithPossBall(Player *p); //Pinpoints the ball at the tip of the Player
    
    
    
    //Test
    int testInt();
    
    
    
};


#endif