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

Team::Team (map<string, Player*> list)
{

    listOfPlayers = list;

}

Player* Team::getPlayer (string name)
{
    return listOfPlayers[name];
    
}

<<<<<<< Updated upstream
map<string, Player*>* Team::getPlayers ()
{
    return &listOfPlayers;
    
}

void Team::setUp()
{

    
    
}
=======
>>>>>>> Stashed changes


