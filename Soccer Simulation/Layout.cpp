//
//  Layout.cpp
//  Soccer1
//
//  Created by Gibran Morales on 3/2/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#include "Layout.h"
#include "Team.h"
#include "Player.h"
#include <vector>

using namespace std;

/*Home Team is Real Madrid. Away is Barcelone

 
 */
Layout::Layout(Team * homeT, Team * awayT)
{
    homeTeam = homeT;
    awayTeam = awayT;
    
    cout << "hereererere" << endl;
}


void Layout::initialSetUp433()
{
    homeTeam->getPlayer("A")->setAreaPosition(10, 20, 30, 40);

    

    
}






