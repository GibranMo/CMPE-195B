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
#include "Ball.h"
#include <time.h>
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
    
    //x1, x2, y1, y2 (where x1 = leftmost, x2 = rightmost,  y1 = uppermost, y2 = lowermost )
    homeTeam->getPlayer("Alba")->setAreaPosition(45, 469, 20, 350 ); //This guy is the left back (LB), and his team attacks to the right
    homeTeam->getPlayer("Mathieu")->setAreaPosition(45, 469, 185, 515 ); //Left Center Back (LCB)
    homeTeam->getPlayer("Pique")->setAreaPosition(45, 469, 185, 515 ); //Right Center Back (RCB)
    homeTeam->getPlayer("Alves")->setAreaPosition(45, 469, 350, 680 );  //Right Back (RB)
    
    
    homeTeam->getPlayer("Iniesta")->setAreaPosition(363, 787, 20, 380 ); //Left Midfielder (LM)
    homeTeam->getPlayer("Busquets")->setAreaPosition(257, 893, 185, 515 ); //Center Midfeidlder (CM)
    homeTeam->getPlayer("Rakitic")->setAreaPosition(363, 787, 320, 680 ); //Right Midfielder
    
    // 681 - 40 = 641
    homeTeam->getPlayer("Neymar")->setAreaPosition(641, 1105, 20, 350 ); // Left Forward (LF)
    homeTeam->getPlayer("Messi")->setAreaPosition(681, 1105, 185, 515 ); // Center Forward (CF)
    homeTeam->getPlayer("Suarez")->setAreaPosition(641, 1105, 350, 680 ); // Right Forward (CF)
    
    
    //Away Team
    
    //Skip goalie, 'Z'
    
    //x1, x2, y1, y2 (where x1 is leftmost, y1 uppermost )
    awayTeam->getPlayer("Marcelo")->setAreaPosition(1105, 681, 20, 350 ); //This guy is the left back (LB), and his team attacks right
    awayTeam->getPlayer("Ramos")->setAreaPosition(1105, 681, 185, 515 ); //Left Center Back (LCB)
    awayTeam->getPlayer("Pepe")->setAreaPosition(1105, 681, 185, 515 ); //Right Center Back (RCB)
    awayTeam->getPlayer("Carvajal")->setAreaPosition(1105, 681, 350, 680 );  //Right Back (RB)
    
    
    awayTeam->getPlayer("Modric")->setAreaPosition(787, 363, 20, 380 ); //Left Midfielder (LM)
    awayTeam->getPlayer("Rodriguez")->setAreaPosition(893, 257, 185, 515 ); //Center Midfeidlder (CM)
    awayTeam->getPlayer("Kroos")->setAreaPosition(787, 363, 320, 680 ); //Right Midfielder
    
    // 681 - 40 = 641
    awayTeam->getPlayer("Ronaldo")->setAreaPosition(509, 45, 20, 350 ); // Left Forward (LF)
    awayTeam->getPlayer("Benzema")->setAreaPosition(469, 45, 185, 515 ); // Center Forward (CF)
    awayTeam->getPlayer("Bale")->setAreaPosition(509, 45, 350, 680 ); // Right Forward (CF)
    
    
    
    
}


void Layout::hasBall(Player * p)
{
    if(p == NULL){
        playerHasBall = NULL;
        return;
    }
    
    playerHasBall = p;
    
    /*   A player having possession of the ball implies a certain position for the ball on the screen(At the tip of the player).
     */
    
    
    int x = playerHasBall->getX();
    int y = playerHasBall->getY();
    int w = playerHasBall->getW();
    int h = playerHasBall->getH();
    int bw = ball->getW();
    int bh = ball->getH();
    
    string s = playerHasBall->getAngle();
    
    int newBallX = 0;
    int newBallY = 0;
    
    if (s == "N")
    {
        newBallX = x + (w/2);
        newBallY = y - bh - 1;
    }
    else if (s == "S")
    {
        newBallX = x + (w/2);
        newBallY = y + h + 1;
    }
    else if (s == "E")
    {
        newBallX = x + w + 1;
        newBallY = y + (h/2);
        
    }
    else if (s == "W")
    {
        newBallX = x - bw - 1;
        newBallY = y + (h/2);
    }
    else if (s == "SE")
    {
        newBallX = x + w + 1;
        newBallY = y + h + 1;
    }
    else if (s == "SW")
    {
        newBallX = x - bw - 1;
        newBallY = y + h + 1;
    }
    else if (s == "NE")
    {
        newBallX = x + w + 1;
        newBallY = y - bh - 1;
    }
    else if (s == "NW")
    {
        newBallX = x - bw - 1;
        newBallY = y - bh - 1;
    }
    ball->setPos(newBallX, newBallY);
    
    teamWhoHasBall = p->getTeamName();
}

string Layout::getTeamWhoHasBall()
{
    
    return teamWhoHasBall;
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

vector <Player *> Layout::getTeamMatesWithin(Player * p, int range) {
    string team = p->getTeamName();
    vector<Player*> players;
    
    if(team == "homeTeam") {
        ///map<string, Player *> * list = this->getHomeTeam();
        for (std::map<string,Player*>::iterator it=homeTeam->getPlayers()->begin();
             it!=homeTeam->getPlayers()->end(); ++it ){
            
            if (it->second->getName() == p->getName() ) // I player does not care about himself
                continue;
            Player * p2 = it->second;
            if(distance(p, p2) < range){
                players.push_back(p2);
            }
        }
    }
    else if(team == "awayTeam") {
        ///map<string, Player *> * list = this->getHomeTeam();
        for (std::map<string,Player*>::iterator it=awayTeam->getPlayers()->begin();
             it!=awayTeam->getPlayers()->end(); ++it ){
            
            if (it->second->getName() == p->getName() ) // I player does not care about himself
                continue;
            
            Player * p2 = it->second;
            if(distance(p, p2) < range){
                players.push_back(p2);
            }
        }
    }
    return players;
}

bool Layout::isRectangleAreaInFrontClear(Player * p, Player * p2)
{
    
    int p1x = p->getX();
    int p1y = p->getY();
    int p2x = p2->getX();
    int p2y = p2->getY();
    
    map<string, Player*> * players;
    if (p->getTeamName() == "homeTeam")
        players = awayTeam->getPlayers();
    else
        players = homeTeam->getPlayers();
    
    for (std::map<string,Player*>::iterator it=players->begin(); it!=players->end(); ++it ) {
        
        Player * opponent = it->second;
        int opx = opponent->getX();
        int opy = opponent->getY();
        
        //between x's
        if(opx > p1x && opx < p2x) {
            //player1 below player2
            if(p1y >= p2y){
                if (opy > p2y - 10 && opy < p1y + 10) {
                    int ypt = ( ( (p2y - p1y)/(p2x - p1x) ) * (opx - p1x) ) + p1y;
                    if(opy >ypt - 10 && opy < ypt + 10){
                        return false;
                    }
                }
            }
            //player2 below player1
            else {
                if (opy > p1y - 10 && opy < p2y + 10) {
                    int ypt = ( ( (p2y - p1y)/(p2x - p1x) ) * (opx - p1x) ) + p1y;
                    if(opy >ypt - 10 && opy < ypt + 10){
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
    
    
}


vector <Player *> Layout::getAvailablePlayers(Player * p)
{
    
    string team = p->getTeamName();
    vector<Player*> players;
    
    if(team == "homeTeam") {
        for (std::map<string,Player*>::iterator it=homeTeam->getPlayers()->begin(); it!=homeTeam->getPlayers()->end(); ++it )
        {
            Player * p1 = it->second;
            
            if (p1->getName() == p->getName())
                continue;
            
            bool available = true;
            
            for (std::map<string,Player*>::iterator it=awayTeam->getPlayers()->begin(); it!=awayTeam->getPlayers()->end(); ++it )
            {
                Player * p2 = it->second;
                
                if(distance(p1, p2) < 80){
                    cout << " <><> " << ( (p->getY() - p1->getY()) ) + p1->getX() << endl;
                    if(p2->getX() < ( ( (p2->getY() - p1->getY()) * (p1->getX() - p->getX()) ) / (p->getY() - p1->getY()) ) + p1->getX() )
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
                
                if(distance(p1, p2) < 80){
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

double Layout::getDistance(int x1, int x2, int y1, int y2)
{
    return sqrt(  ((x1 - x2) * (x1 - x2)) +  ((y1 - y2) * (y1 - y2)) );
}

double Layout::distance(Player * p1, Player * p2)
{
    int x = p1->getX();
    int y = p1->getY();
    int p2X = p2->getX();
    int p2Y = p2->getY();
    return sqrt(  ((x - p2X) * (x - p2X)) +  ((y - p2Y) * (y - p2Y)) );
}

double Layout::getDistanceBall(Player * p)
{
    int x = p->getX();
    int y = p->getY();
    
    return sqrt(  ((x - ball->getX()) * (x - ball->getX())) +  ((y - ball->getY()) * (y - ball->getY())) );
    
}



double Layout::distanceBetweenPlayers(Player * p1, Player * p2)
{
    int x = p1->getX();
    int y = p1->getY();
    int p2X = p2->getX();
    int p2Y = p2->getY();
    return sqrt(  ((x - p2X) * (x - p2X)) +  ((y - p2Y) * (y - p2Y)) );
}





double Layout::getShootingAngle(Player * p){
    double angle = 0;
    int archLength = 60;
    
    int x = p->getX();
    int y = p->getY();
    
    
    int archX;
    
    if(p->getTeamName() == "homeTeam")
        archX = screenW - 50;          //This is a point at the center of the goal (it also is where the goalie always is).
    else
        archX = 50;
    
    
    int archTopY = screenH / 2 - 30;      //top goal post
    int archBottomY = screenH / 2 + 30;  //bottom goal post
    
    int side1 = sqrt( (abs ((x - archX) * (x - archX)) + abs( ((y - archTopY) * (y - archTopY)))));
    int side2 = sqrt( (abs ((x - archX) * (x - archX)) + abs( ((y - archBottomY) * (y - archBottomY)))));
    
    /*
     int l =    sqrt( (abs ((x - archX) * (x - archX)) + abs( ((y - archTopY) * (y - archTopY)))));
     
     */
    
    
    angle = acos( ( ( (side1)^2 + (side2)^2 - archLength^2) / ( 2 * side1 * side2) ));
    
    return angle;
}

void Layout::pass(Player * receivingPlayer)
{
    
    
}

int Layout::countTeammatesInFront(Player *p)
{
    
    Player * player = p;
    Team * team = NULL;
    
    // count how many opponents in front of him
    
    int x = player->getX(); //The x position of the player in question
    
    string whatTeam = player->getTeamName();
    
    if (whatTeam == "awayTeam")
    {
        team = getAwayTeam();
    }
    else
    {
        team = getHomeTeam();
    }
    
    //First Home Team (Home Team attacks to the right)
    int count = 0; //For counting how many players are in front of the player in question
    if (whatTeam == "homeTeam")
    {
        map <string, Player *> listOfPlayers = *team->getPlayers();
        for (std::map<string,Player*>::iterator it=listOfPlayers.begin(); it!=listOfPlayers.end(); ++it){
            
            int teammateXPos = it->second->getVelX();
            if (x <= teammateXPos) //Teammate is in front or parallel
                count++;
            
        }
    }
    else
    {
        map <string, Player *> listOfPlayers = *team->getPlayers();
        for (std::map<string,Player*>::iterator it=listOfPlayers.begin(); it!=listOfPlayers.end(); ++it){
            
            int teammateXPos = it->second->getVelX();
            if (x >= teammateXPos)
                count++;
            
        }
        
    }
    
    return count;
    
}

Team * Layout::getDefendingTeam()
{
    if (teamWhoHasBall == "awayTeam")
        return homeTeam;
    else
        return awayTeam;
    
}

Team * Layout::getAttackingTeam()
{
    
    
    if (teamWhoHasBall == "homeTeam")
        return homeTeam;
    else
        return awayTeam;
    
}

