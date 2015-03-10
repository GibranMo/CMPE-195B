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
#include "SPlayer.h"
#include "Team.h"

using namespace std;

class Layout
{
    private:
    Team * homeTeam;
    Team * awayTeam;
    
    public:
    
    Layout(Team * homeT, Team * awayT);
    //Layout(){};
    
    
    
};


#endif
