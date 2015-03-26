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

/*Home Team is Real Madrid. Away is Barcelona
 
 
 */
Layout::Layout(Team * homeT, Team * awayT, Ball * b)
{
    homeTeam = homeT;
    awayTeam = awayT;
    ball = b;
    cout << "hereererere" << endl;
}


void Layout::initialSetUp433()
{
    //Skip goalie, 'A'
    
    //x1, x2, y1, y2 (where x1 is leftmost, y1 uppermost )
    homeTeam->getPlayer("B")->setAreaPosition(45, 469, 20, 350 ); //This guy is the left back (LB), and his team attacks right
    homeTeam->getPlayer("C")->setAreaPosition(45, 469, 185, 515 ); //Left Center Back (LCB)
    homeTeam->getPlayer("D")->setAreaPosition(45, 469, 185, 515 ); //Right Center Back (RCB)
    homeTeam->getPlayer("E")->setAreaPosition(45, 469, 350, 680 );  //Right Back (RB)
    
    
    homeTeam->getPlayer("F")->setAreaPosition(363, 787, 20, 380 ); //Left Midfielder (LM)
    homeTeam->getPlayer("G")->setAreaPosition(257, 893, 185, 515 ); //Center Midfeidlder (CM)
    homeTeam->getPlayer("H")->setAreaPosition(363, 787, 320, 680 ); //Right Midfielder
    
    // 681 - 40 = 641
    homeTeam->getPlayer("I")->setAreaPosition(641, 1105, 20, 350 ); // Left Forward (LF)
    homeTeam->getPlayer("J")->setAreaPosition(681, 1105, 185, 515 ); // Center Forward (CF)
    homeTeam->getPlayer("K")->setAreaPosition(641, 1105, 350, 680 ); // Right Forward (CF)
    
    
    //Away Team
    
    //Skip goalie, 'Z'
    
    //x1, x2, y1, y2 (where x1 is leftmost, y1 uppermost )
    awayTeam->getPlayer("Y")->setAreaPosition(1105, 681, 20, 350 ); //This guy is the left back (LB), and his team attacks right
    awayTeam->getPlayer("X")->setAreaPosition(1105, 681, 185, 515 ); //Left Center Back (LCB)
    awayTeam->getPlayer("W")->setAreaPosition(1105, 681, 185, 515 ); //Right Center Back (RCB)
    awayTeam->getPlayer("V")->setAreaPosition(1105, 681, 350, 680 );  //Right Back (RB)
    
    
    awayTeam->getPlayer("U")->setAreaPosition(787, 363, 20, 380 ); //Left Midfielder (LM)
    awayTeam->getPlayer("T")->setAreaPosition(893, 257, 185, 515 ); //Center Midfeidlder (CM)
    awayTeam->getPlayer("S")->setAreaPosition(787, 363, 320, 680 ); //Right Midfielder
    
    // 681 - 40 = 641
    awayTeam->getPlayer("R")->setAreaPosition(509, 45, 20, 350 ); // Left Forward (LF)
    awayTeam->getPlayer("Q")->setAreaPosition(469, 45, 185, 515 ); // Center Forward (CF)
    awayTeam->getPlayer("P")->setAreaPosition(509, 45, 350, 680 ); // Right Forward (CF)
    
    
    
    
}



void Layout::hasBall(Player * p)
{
    playerHasBall = p;
}

Team * Layout::getHomeTeam()
{
    
    return homeTeam;
}

Team * Layout::getAwayTeam()
{
    
    return awayTeam;
}

Ball * Layout::getBall(){
    return ball;
}

Player * Layout::hasBall(){
    return playerHasBall;
}

vector <Player *> Layout::getTeamMatesWithin40(Player * p) {
    string team = p->getTeamName();
    vector<Player*> players;
    
    if(team == "homeTeam") {
        ///map<string, Player *> * list = this->getHomeTeam();
        for (std::map<string,Player*>::iterator it=homeTeam->getPlayers()->begin();
             it!=homeTeam->getPlayers()->end(); ++it ){
            Player * p2 = it->second;
            if(distance(p, p2) < 40){
                players.push_back(p2);
            }
        }
    }
    else if(team == "awayTeam") {
        ///map<string, Player *> * list = this->getHomeTeam();
        for (std::map<string,Player*>::iterator it=awayTeam->getPlayers()->begin();
             it!=awayTeam->getPlayers()->end(); ++it ){
            Player * p2 = it->second;
            if(distance(p, p2) < 40){
                players.push_back(p2);
            }
        }
    }
    return players;
}

vector <Player *> Layout::getAvailablePlayers(Player * p){
    
    string team = p->getTeamName();
    vector<Player*> players;
    
    if(team == "homeTeam") {
        for (std::map<string,Player*>::iterator it=homeTeam->getPlayers()->begin();
             it!=homeTeam->getPlayers()->end(); ++it ){
            Player * p1 = it->second;
            bool available = true;
            
            for (std::map<string,Player*>::iterator it=awayTeam->getPlayers()->begin();
                 it!=awayTeam->getPlayers()->end(); ++it ){
                Player * p2 = it->second;
                
                if(distance(p1, p2) < 40){
                    if(p2->getX() < ( ( ( (p2->getY() - p1->getY()) * (p1->getX() - p->getX()) ) / (p->getY() - p1->getY()) ) + p1->getX() ) )
                    available = false;
                }
            }
            if(available)
                players.push_back(p1);
        }
    }
    else if(team == "awayTeam") {
        for (std::map<string,Player*>::iterator it=awayTeam->getPlayers()->begin();
             it!=awayTeam->getPlayers()->end(); ++it ){
            Player * p1 = it->second;
            bool available = true;
            
            for (std::map<string,Player*>::iterator it=homeTeam->getPlayers()->begin();
                 it!=homeTeam->getPlayers()->end(); ++it ){
                Player * p2 = it->second;
                
                if(distance(p1, p2) < 40){
                    if(p2->getX() < ( ( ( (p2->getY() - p1->getY()) * (p1->getX() - p->getX()) ) / (p->getY() - p1->getY()) ) + p1->getX() ) )
                        available = false;
                }
            }
            if(available)
                players.push_back(p1);
        }

    }
    return players;
}

int Layout::distance(Player * p1, Player * p2){
    int x = p1->getX();
    int y = p1->getY();
    int p2X = p2->getX();
    int p2Y = p2->getY();
    return sqrt( (abs ((x - p2X) * (x - p2X)) + abs( ((y - p2Y) * (y - p2Y)))));
}
