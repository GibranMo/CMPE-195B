//
//  Team.h
//  Soccer1
//
//  Created by Gibran Morales on 3/2/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#ifndef Soccer1_Team_h
#define Soccer1_Team_h

#include <vector>
#include <string>
#include "Player.h"
#include <map>

using namespace std;
class Team
{
private:
    string name;
    map <string, Player *> listOfPlayers;
    
public:
    
    Team (map<string, Player *> list);
    Team (){};
    void setUp();
    Player * getPlayer(string name);
    map<string, Player*>* getPlayers(); //returns a pointer to a  map
    
    
};
#endif
