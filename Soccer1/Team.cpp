//
//  Team.cpp
//  Soccer1
//
//  Created by Gibran Morales on 3/3/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#include "Team.h"
#include <map>

using namespace std;

Team::Team (map<string, SPlayer*> list)
{

    listOfPlayers = list;

}

SPlayer* Team::getPlayer (string name)
{
    return listOfPlayers[name];
    
}

void Team::initialSetUp433()
{
    
    SPlayer* daniAlves = Team::getPlayer("Dani Alves");
    
    daniAlves->setAreaPosition(10, 20, 30, 40);
    
}


