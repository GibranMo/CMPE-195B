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

int Layout::testInt()
{
    return 1;
    
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
    
    /*   A player having possession of the ball implies a certain position for the ball on the screen(At the tip of the player).
     */
    
    
    int x = playerHasBall->getX();
    int y = playerHasBall->getY();
    string s = playerHasBall->getAngle();
    
    int newBallX = 0;
    int newBallY = 0;
    
    if (s == "N")
    {
        newBallX = x+5;
        newBallY = y;
        
        ball->setPos(newBallX, newBallY);
        
    }
    else if (s == "S")
    {
        newBallX = x+8;
        newBallY = y+11;
        
        ball->setPos(newBallX, newBallY);
    }
    
    
    
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

/* Do not care is opposing players are obstructing the teammate. Just scanning for
 a teammate within specified radius
 */
vector <Player *> Layout::getTeamMatesWithin80(Player * p) {
    string team = p->getTeamName();
    vector<Player*> players;
    
    if(team == "homeTeam") {
        ///map<string, Player *> * list = this->getHomeTeam();
        for (std::map<string,Player*>::iterator it=homeTeam->getPlayers()->begin();
             it!=homeTeam->getPlayers()->end(); ++it ){
            
            if (it->second->getName() == p->getName() ) // I player does not care about himself
                continue;
            Player * p2 = it->second;
            
            if(distance(p, p2) < 80){
                cout << "YEEEES " << p2->getName() << endl;
                
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
            if(distance(p, p2) < 80){
                players.push_back(p2);
            }
        }
    }
    return players;
}

bool Layout::isRectangleAreaInFrontClear(Player *p)
{
    
    int x = p->getX();
    int y = p->getY();
    
    int yPlus = y + 20;
    int yMinus = y - 20;
    
    int XPlus = x + 35;
    
    if (XPlus >= 1105 )
        return false;
    
    
    string nameOfTeam = p->getTeamName();
    
    
    if (nameOfTeam == "homeTeam")
    {
        
        for (std::map<string,Player*>::iterator it=awayTeam->getPlayers()->begin(); it!=awayTeam->getPlayers()->end(); ++it )
        {
            
            Player * opponent = it->second;
            
            if (opponent->getY() < yMinus && opponent->getY() > yPlus && opponent->getX() < XPlus)
            {
                return false;
            }
        }
        
    }
    else
    {
        XPlus = x - 35;
        
        if (XPlus < 0 )
            return false;
        
        
        for (std::map<string,Player*>::iterator it=homeTeam->getPlayers()->begin(); it!=homeTeam->getPlayers()->end(); ++it )
        {
            
            Player * opponent = it->second;
            
            if (opponent->getY() < yMinus && opponent->getY() > yPlus && opponent->getX() < XPlus)
            {
                return false;
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

double Layout::distance(Player * p1, Player * p2)
{
    int x = p1->getX();
    int y = p1->getY();
    int p2X = p2->getX();
    int p2Y = p2->getY();
    return sqrt(  ((x - p2X) * (x - p2X)) +  ((y - p2Y) * (y - p2Y)) );
}

void Layout::analyzeField(Player * p)
{
    int x = p->getX();
    int y = p->getY();
    
    if(p->getTeamName() == "homeTeam"){
        if(p->getX() >= 1005){
            if(getShootingAngle(p) > 30){
                int l = sqrt( (abs ((x - archX) * (x - archX)) + abs( ((y - archTopY) * (y - archTopY)))));

                //shoot
            }
        }
    }
    if(p->getTeamName() == "awayTeam"){
        if(p->getX() <= 100){
            if(getShootingAngle(p) > 30){
                
                //shoot
            }
            
        }
        
    }
    
    
    
    
    
    vector<Player *> listOfCloseTeamMates = getTeamMatesWithin80(p);
    
    for (int k = 0; k < listOfCloseTeamMates.size(); k++)
        cout << ">> " << listOfCloseTeamMates.at(k)->getName() << endl;
    
    vector<Player *> listOfAvailableTeamMates;
    srand(time (NULL));
    
    int result = countTeammatesInFront(p);
    
    if (result == 0)
    {
        listOfAvailableTeamMates = getAvailablePlayers(p);
        
        //for (int k = 0; k < listOfAvailableTeamMates.size(); k++)
        //cout << ">> " << listOfAvailableTeamMates.at(k)->getName() << endl;
        
        
        for(int i = 0; i < listOfCloseTeamMates.size(); i++)
        {
            listOfAvailableTeamMates.push_back(listOfCloseTeamMates[i]);
        }
        
        
        
        unsigned long range = listOfAvailableTeamMates.size();
        int random = rand() % range;
        
        Player * destinationPlayer = listOfAvailableTeamMates.at(random);
        
        pass(destinationPlayer);
        
        cout << "*****<><><>" << endl;
        
    }
    
}

int Layout::getShootingAngle(Player * p){
    int angle = 0;
    int archLength = 60;
    
    int x = p->getX();
    int y = p->getY();
    
    
    int archX;
    
    if(p->getTeamName() == "homeTeam")
        archX = screenW - 50;
    else
        archX = 50;

    
    int archTopY = screenH / 2 - 30;
    int archBottomY = archTopY + 60;
    
    int side1 = sqrt( (abs ((x - archX) * (x - archX)) + abs( ((y - archTopY) * (y - archTopY)))));
    int side2 = sqrt( (abs ((x - archX) * (x - archX)) + abs( ((y - archBottomY) * (y - archBottomY)))));
    
    
    
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

