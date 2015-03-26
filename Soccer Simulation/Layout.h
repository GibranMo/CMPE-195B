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
    
    
public:
    
    Layout(Team * homeT, Team * awayT, Ball * b);
    void initialSetUp433();
    void hasBall(Player * p);
    Team * getHomeTeam();
    Team * getAwayTeam();
    Ball * getBall();
    Player * hasBall();
    vector <Player *> getTeamMatesWithin40(Player * p);
    int distance(Player * p1, Player * p2);
    vector <Player *> getAvailablePlayers(Player * p);
    //Layout(){};
    
    
    
};


#endif