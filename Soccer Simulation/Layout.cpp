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
    homeTeam->getPlayer("Alba")->setFieldPosition( 250 , screenH/2 -  200);
    
    homeTeam->getPlayer("Mathieu")->setAreaPosition(45, 469, 185, 515 ); //Left Center Back (LCB)
    homeTeam->getPlayer("Mathieu")->setFieldPosition(250, screenH/2 - 100 + 25);
    
    
    homeTeam->getPlayer("Pique")->setAreaPosition(45, 469, 185, 515 ); //Right Center Back (RCB)
    homeTeam->getPlayer("Pique")->setFieldPosition(250, screenH/2 + 100 - 25);
    
    
    homeTeam->getPlayer("Alves")->setAreaPosition(45, 469, 350, 680 );  //Right Back (RB)
    homeTeam->getPlayer("Alves")->setFieldPosition(250, screenH/2 + 200);
    
    
    
    
    
    homeTeam->getPlayer("Iniesta")->setAreaPosition(363, 787, 20, 380 ); //Left Midfielder (LM)
    homeTeam->getPlayer("Iniesta")->setFieldPosition(400 + 185, screenH/2 - 100 - 63);
    
    homeTeam->getPlayer("Busquets")->setAreaPosition(257, 893, 185, 515 ); //Center Midfeidlder (CM)
    homeTeam->getPlayer("Busquets")->setFieldPosition(400 + 190, screenH/2);
    
    
    
    homeTeam->getPlayer("Rakitic")->setAreaPosition(363, 787, 320, 680 ); //Right Midfielder
    homeTeam->getPlayer("Rakitic")->setFieldPosition(400 + 185, screenH/2 + 163); //Right Midfielder
    
    
    
    // 681 - 40 = 641
    homeTeam->getPlayer("Neymar")->setAreaPosition(641, 1105, 20, 350 ); // Left Forward (LF)
    homeTeam->getPlayer("Neymar")->setFieldPosition( ((1105 - 641)/2) + 641 - 45 , ((350 - 20) / 2) + 20);
    
    
    homeTeam->getPlayer("Messi")->setAreaPosition(681, 1105, 185, 515 ); // Center Forward (CF)
    homeTeam->getPlayer("Messi")->setFieldPosition(((1105 - 681)/2) + 681, ((515 - 185) / 2) + 185);
    
    
    homeTeam->getPlayer("Suarez")->setAreaPosition(641, 1105, 350, 680 ); // Right Forward (CF)
    homeTeam->getPlayer("Suarez")->setFieldPosition( ((1105 - 641)/2) + 641 - 45 , ((350 - 20) / 2) + 340);
    
    //Away Team
    
    //Skip goalie, 'Z'
    
    //x1, x2, y1, y2 (where x1 = leftmost, x2 = rightmost,  y1 = upper most, y2 = lower most )
    awayTeam->getPlayer("Marcelo")->setAreaPosition(681, 1105, 350, 680 ); //This guy is the left back (LB), and his team attacks right
    awayTeam->getPlayer("Marcelo")->setFieldPosition( screenW - 258, screenH/2 + 200);
    
    awayTeam->getPlayer("Ramos")->setAreaPosition(681, 1105, 185, 515 ); //Left Center Back (LCB)
    awayTeam->getPlayer("Ramos")->setFieldPosition(screenW - 258, screenH/2 + 100 - 45 + 15  );
    
    awayTeam->getPlayer("Pepe")->setAreaPosition(681, 1105, 185, 515 ); //Right Center Back (RCB)
    awayTeam->getPlayer("Pepe")->setFieldPosition(screenW - 258, screenH/2 - 100 + 45 - 15);
    
    
    awayTeam->getPlayer("Carvajal")->setAreaPosition(681, 1105, 20, 350);  //Right Back (RB)
    awayTeam->getPlayer("Carvajal")->setFieldPosition(screenW - 258, screenH/2 - 200);
    
    
    awayTeam->getPlayer("Modric")->setAreaPosition(363, 787, 320, 680); //Left Midfielder (LM)
    awayTeam->getPlayer("Modric")->setFieldPosition( 530, screenH/2 + 110);
    
    awayTeam->getPlayer("Rodriguez")->setAreaPosition(257, 893, 185, 515); //Center Midfeidlder (CM)
    awayTeam->getPlayer("Rodriguez")->setFieldPosition( 530 , screenH/2); //Left Midfielder (LM)
    
    awayTeam->getPlayer("Kroos")->setAreaPosition(363, 787, 20, 380); //Right Midfielder (RM)
    awayTeam->getPlayer("Kroos")->setFieldPosition(530 , screenH/2-110); //Left Midfielder (LM)
    
    // 681 - 40 = 641
    awayTeam->getPlayer("Ronaldo")->setAreaPosition(45, 509, 350, 680 ); // Left Forward (LF)
    awayTeam->getPlayer("Ronaldo")->setFieldPosition( (509 - 45)/2 + 45, (680 - 350)/ 2 + 350 );
    
    
    awayTeam->getPlayer("Benzema")->setAreaPosition(45, 469, 185, 515 ); // Center Forward (CF)
    awayTeam->getPlayer("Benzema")->setFieldPosition( (460 - 45)/2 + 45, (515 - 185)/ 2 + 185 );
    
    awayTeam->getPlayer("Bale")->setAreaPosition(45, 509, 20, 350 ); // Right Forward (CF)
    awayTeam->getPlayer("Bale")->setFieldPosition( (509 - 45)/2 + 45, (350 - 20)/ 2 + 20 );
    
    
    
    
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

bool Layout::isRectangleAreaInFrontClear(Player * p, int x, int y)
{
    
    int p1x = p->getX();
    int p1y = p->getY();
    int p2x = x;
    int p2y = y;
    
    map<string, Player*> * players;
    if (p->getTeamName() == "homeTeam")
        players = awayTeam->getPlayers();
    else
        players = homeTeam->getPlayers();
    
    for (std::map<string,Player*>::iterator it=players->begin(); it!=players->end(); ++it ) {
        
        Player * opponent = it->second;
        int opx = opponent->getX();
        int opy = opponent->getY();
        
        //check if opponent X position is between p1 and p2
        if(opx > p1x && opx < p2x) {
            
            if(p1y >= p2y){ //player1 below player2 (teammates) p1 has the ball
                if (opy > p2y - 20 && opy < p1y + 20) {
                    int ypt = ( ( (p2y - p1y)/(p2x - p1x) ) * (opx - p1x) ) + p1y;
                    if(opy >ypt - 20 && opy < ypt + 20){
                        return false;
                    }
                }
            }
            //player2 below player1
            else {
                if (opy > p1y - 20 && opy < p2y + 20) {
                    int ypt = ( ( (p2y - p1y)/(p2x - p1x) ) * (opx - p1x) ) + p1y;
                    if(opy >ypt - 20 && opy < ypt + 20){
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
    
    
}

bool Layout::isRectangleAreaInFrontClear2(Player * ballPlayer, Player * teammate)
{
    
    int RANGE = 40;
    
    map<string, Player*> * players;
    if (ballPlayer->getTeamName() == "homeTeam")
        players = awayTeam->getPlayers();
    else
        players = homeTeam->getPlayers();
    
    for (std::map<string,Player*>::iterator it=players->begin(); it!=players->end(); ++it ) {
        
        Player * opponent = it->second;
        
        
        // *Down*
        //
        //  ballPlayer       |------>x
        //      |            |
        //      |            |
        //      opp          |
        //      |            |
        //      V            Vy
        //  teammate
        //
        // (same X)
        if ( teammate->getX() == ballPlayer->getX())
        {
            if (ballPlayer->getY() < teammate->getY() )
            {
                if (opponent->getY() > ballPlayer->getY() && opponent->getY() < teammate->getY())
                {
                    if ( (opponent->getX() < ballPlayer->getX() && opponent->getX() > ballPlayer->getX()- RANGE) || (opponent->getX() > ballPlayer->getX() && opponent->getX() <
                                                                                                                     ballPlayer->getX() + RANGE ))
                    {
                        return false;
                    }
                }
            }
            // *UP*
            //  teammate
            //   ^
            //   |
            //   |
            //  oop
            //   |
            //  ballPlayer
            
            else if ( ballPlayer->getY() > teammate->getY() )
            {
                
                if (ballPlayer->getY() > teammate->getY() )
                {
                    if (opponent->getY() < ballPlayer->getY() && opponent->getY() > teammate->getY())
                    {
                        if ( (opponent->getX() < ballPlayer->getX() && opponent->getX() > ballPlayer->getX()- RANGE) || (opponent->getX() > ballPlayer->getX() && opponent->getX() <
                                                                                                                         ballPlayer->getX() + RANGE ))
                        {
                            return false;
                        }
                    }
                }
            }
        }
        
        //
        //
        //
        //
        // ballPlayer ---- opp ------> teammate
        // (straight; no slope)
        
        if (ballPlayer->getY() == teammate->getY())
        {
            
            if (ballPlayer->getX() < teammate->getX())
            {
                if (ballPlayer->getX() < opponent->getX() && opponent->getX() < teammate->getX()) //check if opponent is in between the X's
                {
                    if ( (opponent->getY() < ballPlayer->getY() && opponent->getY() > ballPlayer->getY() - RANGE )  || (opponent->getY() > ballPlayer->getY() && opponent->getY()
                                                                                                                        < ballPlayer->getY() + RANGE))
                        return false;
                }
                
            }
            /// teammate <----- opp --------- ballPlayer
            else if (ballPlayer->getX() > teammate->getX())
            {
                if (ballPlayer->getX() > opponent->getX() && opponent->getX() > teammate->getX()) //check if opponent is in between the X's
                {
                    if ( (opponent->getY() < ballPlayer->getY() && opponent->getY() > ballPlayer->getY() - RANGE )  || (opponent->getY() > ballPlayer->getY() && opponent->getY()
                                                                                                                        < ballPlayer->getY() + RANGE))
                        return false;
                }
            }
            
        }
        
        
        
        
        //check if opponent X position is between ballPlayer's X and teammate's X
        // teammate  ----->   opponent  ------> ballPlayer
        //
        if(opponent->getX() > ballPlayer->getX() && opponent->getX() < teammate->getX())
        {
            
            // *NORTH EAST * //
            
            //check if ballPlayer is below teammate
            if(ballPlayer->getY() > teammate->getY())
            {
                //check if they Y position of the opponent is between ballPlayer's Y and teammate's Y
                if (opponent->getY() > teammate->getY() && opponent->getY() < ballPlayer->getY())
                {
                    //get slope of line (should increase in North East direction)
                    double slope = (teammate->getY() - ballPlayer->getY()) / (teammate->getX() - ballPlayer->getX()); // slope could be a neg. value
                    
                    //get '+ b' part of the equation y = mx + b
                    
                    double b = getB(slope, teammate->getX(), teammate->getY()); //chose to use the teammates coordinates. Could have also used ballPlayers's
                    
                    double resultY = mxPlusbOutput(slope, opponent->getX(), b);
                    
                    //check if this resultY is ON the line traced by y = mx + b
                    
                    
                    if ( (opponent->getY() >= resultY && opponent->getY() <= resultY + RANGE ) ||  (opponent->getY() >= resultY - RANGE  && opponent->getY() <= resultY) )
                        return false;
                    
                }
            }
            /*
             *SOUTH EAST*
             */
            else  // maybe don't need 'else if'; just 'else' At this juncture, it would imply a South East pass
            {
                // check if the Y of opponent is within right range
                if (opponent->getY() > ballPlayer->getY() && opponent->getY() < teammate->getY())
                {
                    //get slope of line (should increase in North East direction)
                    double slope = (teammate->getY() - ballPlayer->getY()) / (teammate->getX() - ballPlayer->getX()); // slope could be a neg. value
                    
                    //get '+ b' part of the equation y = mx + b
                    
                    double b = getB(slope, teammate->getX(), teammate->getY()); //chose to use the teammates coordinates. Could have also used ballPlayers's
                    
                    double resultY = mxPlusbOutput(slope, opponent->getX(), b);
                    
                    //check if this resultY is ON the line traced by y = mx + b
                    
                    
                    if ( (opponent->getY() >= resultY && opponent->getY() <= resultY + RANGE ) ||  (opponent->getY() >= resultY - RANGE  && opponent->getY() <= resultY) )
                        return false;
                    
                    
                }
                
            }
        }
        //   |------> x
        //   |
        //   |
        //   V
        //    y
        //
        // The following 'else if' is for:
        //  teammate  <-----   opponent  <------  ballPlayer
        //   (checking for a potential  pass from right to left
        //
        else if (teammate->getX() < opponent->getX() && opponent->getX() < ballPlayer->getX())// ** maybe don't need the if clause; just else;
        {
            //check if ballPlayer is below teammate
            if (ballPlayer->getY() > teammate->getY() )
            {
                /*
                 *NORTH WEST*
                 //   teammate
                 //         *
                 //          *
                 //           *
                 //            *   ballPlayer
                 //  (temmate is above ballPlayer)
                 //   (At this point, checking for a potential North West pas
                 */
                
                //check if the Y position of opponeent is between the Y of teammate and Y of ballPlayer
                if (opponent->getY() > teammate->getY() && opponent->getY() < ballPlayer->getY())
                {
                    //get the slope in  North West direction
                    double slope = (ballPlayer->getY() - teammate->getY()) / (ballPlayer->getX() - teammate->getX());
                    
                    //get '+ b' part of the equation y = mx + b
                    
                    double b = getB(slope, teammate->getX(), teammate->getY()); //chose to use the teammates coordinates. Could have also used ballPlayers's
                    
                    double resultY = mxPlusbOutput(slope, opponent->getX(), b);
                    
                    //check if this resultY is ON the line traced by y = mx + b
                    
                    
                    if ( (opponent->getY() <= resultY && opponent->getY() >= resultY - RANGE)  || (opponent->getY() <= resultY + RANGE  && opponent->getY() >= resultY) )
                        return false;
                }
                
            }
            //  *South West Pass*
            //  (At this point, it's already knonwn that opponent X positoin is between X position of teammate and ballPlayer)
            //
            //              ballPlayer
            //             *
            //            *
            //           *
            //          *
            //  teammate
            else if (teammate->getY() > ballPlayer->getY()) //check if teammate is below ballPlayer
            {
                
                // check if the Y of opponent is within the right Y range
                if (opponent->getY() > ballPlayer->getY() && opponent->getY() < teammate->getY())
                {
                    //get the slope of South East direction
                    double slope = (ballPlayer->getY() - teammate->getY()) / (ballPlayer->getX() - teammate->getX());
                    
                    //get '+ b' part of the equation y = mx + b
                    
                    double b = getB(slope, teammate->getX(), teammate->getY()); //chose to use the teammates coordinates. Could have also used ballPlayers's
                    
                    double resultY = mxPlusbOutput(slope, opponent->getX(), b);
                    
                    //check if this resultY is ON the line traced by y = mx + b
                    
                    if ( (opponent->getY() <= resultY + RANGE && opponent->getY() >= resultY ) || (opponent->getY() >= resultY - RANGE  && opponent->getY() <= resultY) )
                        return false;
                    
                }
                
                
            }
            
        }
    }
    
    return true;
    
    
}

double Layout::mxPlusbOutput(double slope, int x, int b)
{
    // get y = mx + b
    
    return ( (slope * x) ) + b;
    
}

double Layout::getB(double slope, int x, int y)
{
    // y = mx + b
    
    // given in arguments are m, x, and y
    
    // y - mx = b
    
    int b = y - (slope * x);
    
    return b;
    
}
// The radius kind
vector <Player *> Layout::getAvailablePlayers2(Player * ballPlayer, int RANGE)
{
    
    Team * defendingTeam = getDefendingTeam();
    Team * attackingTeam = getAttackingTeam();
    
    vector <Player *> availableTeammates;
    
    
    for (std::map<string,Player*>::iterator it=attackingTeam->getPlayers()->begin(); it!=attackingTeam->getPlayers()->end(); ++it )
    {
        Player * teammate = it->second;
        bool available = true;
        
        
        for (std::map<string,Player*>::iterator it=defendingTeam->getPlayers()->begin(); it!=defendingTeam->getPlayers()->end(); ++it )
        {
            Player * opponent = it->second;
            
            if (ballPlayer->getX() == teammate->getX()) //check if vertical pass
            {
                if (ballPlayer->getY() > teammate->getY()) //check if up is going straight UP
                {
                    // teammate
                    //  ^
                    //  |
                    //  |
                    //  |
                    // ballPlayer
                    if (distance(teammate, opponent) <= RANGE)
                    {
                        if (opponent->getY() > teammate->getY())
                            available = false;
                    }
                }
                else// *STRAIGHT DOWN PASS*
                {
                    if (distance(teammate, opponent) <= RANGE)
                    {
                        if (opponent->getY() < teammate->getY())
                            available = false;
                    }
                }
                
            }
            if (ballPlayer->getY() == teammate->getY()) //check if pass is horizontal
            {
                
                if (ballPlayer->getX() < teammate->getX()) //check if pass is straight to the right
                {
                    //ballPlayer --------------> teammate
                    
                    if (distance(teammate, opponent) <= RANGE)
                    {
                        if (opponent->getX() < teammate->getX())
                            available = false;
                    }
                    
                    
                }
                else //pass is the left
                {
                    //teammate <-------------- ballPlayer
                    if (distance(teammate, opponent) <= RANGE)
                    {
                        if (opponent->getX() > teammate->getX())
                            available = false;
                    }
                }
            }
            
            // Now with slopes (difficult part)
            
            
            
            if (ballPlayer->getX() < teammate->getX()) //ballPlayer ------------> teammate
            {
                if (teammate->getY() < ballPlayer->getY())
                {
                    //                  tammate
                    //                 ^
                    //                *
                    //               *
                    //              *
                    // ballPlayer  *
                    int slope =  getSlope(teammate->getY(), ballPlayer->getY(), teammate->getX(), ballPlayer->getX());
                    int b = getB(slope, teammate->getX(), teammate->getY());
                    // need to slope negative
                    slope *= -1;
                    
                    if (distance(opponent, teammate) <= RANGE) //check if opponent is within the circle at all
                    {
                        //check if opponennt is below the line descibled by y = mx + b
                        
                        int resultY = mxPlusbOutput(slope, opponent->getX(), b);
                        if (opponent->getY() > resultY)
                            available = false;
                    }
                }
                // ballPlayer *
                //              *
                //                *
                //                 > teammate
                //
                else
                {
                    int slope = getSlope(teammate->getY(), ballPlayer->getY(), teammate->getX(), ballPlayer->getX());
                    int b = getB(slope, teammate->getX(), teammate->getY());
                    
                    slope *= -1;
                    
                    if (distance(opponent, teammate) <= RANGE)
                    {
                        int resultY = mxPlusbOutput(slope, opponent->getX(), b);
                        if (opponent->getY() < resultY)
                            available = false;
                    }
                    
                }
                
                
            }
            
            if (available == true)
                availableTeammates.push_back(teammate);
            
            
        }
        
    }
    
    return availableTeammates;
}

double Layout::getSlope(int y1, int y2, int x1, int x2)
{
    int deltaY = y2 - y1;
    int deltaX = x2 - x1;
    
    return deltaY/deltaX;
    
}

//p = player who has ball, p1 = potential available player, p2 = opposing player
vector <Player *> Layout::getAvailablePlayers(Player * p) {
    string team = p->getTeamName();
    vector<Player*> players;
    Team * t;
    Team * op;
    
    if(team == "homeTeam") {
        t = homeTeam;
        op = awayTeam;
    }
    else {
        t = awayTeam;
        op = homeTeam;
    }
    
    for (std::map<string,Player*>::iterator it=t->getPlayers()->begin(); it!=t->getPlayers()->end(); ++it) {
        Player * p1 = it->second;
        cout << "p1: " << p1->getName() << endl;
        
        if (p1->getName() == p->getName())
            continue;
        
        bool available = true;
        
        for (std::map<string,Player*>::iterator it=op->getPlayers()->begin(); it!=op->getPlayers()->end(); ++it) {
            Player * p2 = it->second;
            
            if(distance(p1, p2) < 80){
                cout << p2->getName()  << "<><> " <<  p->getY() - p1->getY() << endl;
                if(p->getY() != p1->getY()){
                    if(p2->getX() < ( ( (p2->getY() - p1->getY()) * (p1->getX() - p->getX()) ) / ( p->getY() - p1->getY()) ) + p1->getX() )
                        available = false;
                    if(!isRectangleAreaInFrontClear(p, p1->getX(), p1->getY()))
                       available = false;
                    
                }
                else {
                    if((p->getY() > p1->getY() && p2->getY() < p->getY() && p2->getY() > p1->getY()) ||
                       (p1->getY() > p->getY() && p2->getY() < p1->getY() && p2->getY() > p->getY()))
                        available = false;
                }
            }
        }
        if(available)
            players.push_back(p1);
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

Player * Layout:: getClosestDefenderToBall()
{
    Player * closest = nullptr;
    Team * team = getDefendingTeam();
    map <string, Player *> listOfPlayers = *team->getPlayers();
    
    unsigned int minDistance = 10000000; //infinity
    for (std::map<string,Player*>::iterator it=listOfPlayers.begin(); it!=listOfPlayers.end(); ++it)
    {
        
        Player * p = it->second;
        
        if (p->getName() == "Casillas" || p->getName() == "Terstegen")
            continue;
        
        if (getDistanceBall(p) < minDistance)
        {
            minDistance = getDistanceBall(p);
            closest = p;
        }
    }
    
    
    return closest;
}

Team * Layout::getAttackingTeam()
{
    
    if (teamWhoHasBall == "homeTeam")
        return homeTeam;
    else
        return awayTeam;
}



Team * Layout::getDefendingTeam()
{
    if (teamWhoHasBall == "awayTeam")
        return homeTeam;
    else
        return awayTeam;
    
}

