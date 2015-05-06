//
//  GamePlay.cpp
//  Soccer1
//
//  Created by Gibran Morales on 3/25/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#include "GamePlay.h"
#include "Layout.h"
#include "Team.h"
#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#include <chrono>
#include <thread>

#include <unistd.h>

//using namespace std;



/*  Experimenting with the behavior of a globally declared Layout variable.
 Reason for this is that I cannot access the member variable 'layout' from inside
 the static function 'player_t'
 */
Layout * expLayout = NULL;
GLuint expFieldTex = NULL;

GamePlay::GamePlay(Layout * l, GLuint ft)
{
    
    layout = l;
    expLayout = l;
    
    //*************
    fieldTex = ft;
    expFieldTex = ft;
    //***************
    
    homeScore = 0;
    awayScore = 0;
    vector<GLuint> s(12);
    score = s;
    
    distanceKick = 0;
    
    score[0] = glTexImageTGAFile("images/0.tga");
    score[1] = glTexImageTGAFile("images/1.tga");
    score[2] = glTexImageTGAFile("images/2.tga");
    score[3] = glTexImageTGAFile("images/3.tga");
    score[4] = glTexImageTGAFile("images/4.tga");
    score[5] = glTexImageTGAFile("images/5.tga");
    score[6] = glTexImageTGAFile("images/6.tga");
    score[7] = glTexImageTGAFile("images/7.tga");
    score[8] = glTexImageTGAFile("images/8.tga");
    score[9] = glTexImageTGAFile("images/9.tga");
    score[10] = glTexImageTGAFile("images/h.tga");
    score[11] = glTexImageTGAFile("images/a.tga");
<<<<<<< HEAD
=======
    score[12] = glTexImageTGAFile("images/-.tga");

>>>>>>> origin/master
}


void GamePlay::DrawSprite(bool playing)
{
    
    if(!playing) {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else {
        glDrawSprite(fieldTex, 0, 0, 1150, 700);
        
        //Basically, the way to get players is in the form of a map, which is done using a method call on a Team object.
        //In the following instance, a Team object is obtained by using the getHomeTeam() method on our member variable 'layout'
        map <string, Player *> listOfPlayers = *layout->getHomeTeam()->getPlayers();
        map <string, Player *> listOfPlayers2 = *layout->getAwayTeam()->getPlayers();
        
        for (std::map<string,Player*>::iterator it=listOfPlayers.begin(); it!=listOfPlayers.end(); ++it){
            glDrawSprite(it->second->getTex(), it->second->getX(), it->second->getY(), 20, 20);
        }
        for (std::map<string,Player*>::iterator it=listOfPlayers2.begin(); it!=listOfPlayers2.end(); ++it){
            
            glDrawSprite2(it->second->getTex(), it->second->getX(), it->second->getY(), 16, 16);
        }
        if(layout->getBall()->getDestY() == 350 &&
           (layout->getBall()->getX() == 1100 || layout->getBall()->getX() == 50))
            glDrawSprite2(layout->getBall()->getTexf(), layout->getBall()->getX(), layout->getBall()->getY(), 20, 20);
        
        else
            glDrawSprite2(layout->getBall()->getTex(), layout->getBall()->getX(), layout->getBall()->getY(), 10, 8);
        
        //score
        glDrawSprite(score[10], 0, 0, 20, 20);
<<<<<<< HEAD
        glDrawSprite(score[homeScore % 10], 25, 0, 20, 20);
        glDrawSprite(score[11], 50, 0, 20, 20);
=======
        glDrawSprite(score[12], 13, 0, 20, 20);
        glDrawSprite(score[homeScore % 10], 25, 0, 20, 20);
        glDrawSprite(score[11], 50, 0, 20, 20);
        glDrawSprite(score[12], 63, 0, 20, 20);
>>>>>>> origin/master
        glDrawSprite2(score[awayScore % 10], 75, 0, 20, 20);
    }

}

void GamePlay::setPointToBall(Player *p)
{
    int ballX = layout->getBall()->getX();
    int ballY = layout->getBall()->getY();
    /*
    cout << "HERERERERERER " << endl;
    cout << "*ballX: " << ballX << " ballY: " << ballY << endl;
    cout << "*pX:  " << p->getX() << " *pY: " << p->getY() << endl;
    */
    if (ballY < p->getY())
    {
        if (ballX < p->getX())
        {
            p->setFaceAngle("NW");
        }
        else if (ballX > p->getX())
        {
            p->setFaceAngle("NE");
        }
        else
        {
            p->setFaceAngle("N");
        }
        
        
    }
    else if (ballY > p->getY() )
    {
        if (ballX < p->getX())
        {
            p->setFaceAngle("SW");
        }
        else if (ballX > p->getX())
        {
            
            p->setFaceAngle("SE");
        }
        else
        {
            p->setFaceAngle("S");
        }
        
    }
    else
    {
        if (ballX > p->getX())
          {    p->setFaceAngle("E");
 
          }
        else
        {
            p->setFaceAngle("W");

        }
    }
    
    
}

int GamePlay::getAdjustSpeed(int PlayersPace)
{
    int defaultBaseSpeed = 162800;
    int scaledPace = PlayersPace * 1200;
    
    defaultBaseSpeed = defaultBaseSpeed - scaledPace;
    
    return  defaultBaseSpeed;
    
}

/*
 Gibran: Defending player is move towards the positon of the guy who has the ball
 */


void GamePlay::MoveDefendingPlayer(Player * p)
{
    /*
     
     Move towards the position of player who posseses ball
     */
    
    
    
    int ballX = layout->hasBall()->getX();
    int ballY = layout->hasBall()->getY();
    
    int deltaY = abs ( (p->getY() -  ballY ) );
    
    int deltaX = abs (p->getX() - ballX);
    
    
    int ratio;
    cout << "delta X: " << deltaX << " delta Y: " << deltaY << endl;
    if ( deltaY != 0 && (deltaX > deltaY))
        ratio = deltaX/deltaY;
    else
        ratio = 1;
    
    int ratio2;
    cout << "delta X: " << deltaX << " delta Y: " << deltaY << endl;
    if ( deltaX != 0 && (deltaY > deltaX))
        ratio2 = deltaY/deltaX;
    else
        ratio2 = 1;
    
    
    // *RIGHT/LEFT* //
    int Xstep = 0;
    if (ballX >= p->getX())
    {
        Xstep = 1;
    }
    else
    {
        Xstep = - 1;
    }
    
    // *UP/DOWN *//
    int Ystep = 0;
    
    if (ballY >= p->getY())
    {
        Ystep = 1;
    }
    else
    {
        Ystep = -1;
        
    }
    
    cout << "step 1: " << Xstep << " ratio1: " << ratio << endl;
    cout << "step 2: " << Ystep << " ratio2: " << ratio2 << endl;
    
    
    
    cout << "D: " << layout->distanceBetweenPlayers(p, layout->hasBall()) << endl;
    
    while (layout->distanceBetweenPlayers(p, layout->hasBall()) >= 1)
    {
        for (int x = 1; x <= ratio; x++)
        {
            for (int y = 1; y <= ratio2; y++)
            {
                p->setYPos(p->getY() + Ystep);
                cout << "inside 1 Y: " << p->getY() << endl;
                cout << "DDD: " << layout->distanceBetweenPlayers(p, layout->hasBall()) << endl;
                
            }
            p->setXPos(p->getX() + Xstep );
            cout << "inside 2 X: " << p->getX() << endl;
        }
        cout << "inside 3" << endl;
    }
    
    cout << "****" << endl;
    
}

void GamePlay::defend2(Player *p)
{
    static unsigned int callCtr = 0;
    
    callCtr++;
    int speed = p->getPace();
    
    speed = 100 - speed;
    
    
    
    p->incrementCounter();
    
    if ((p->getCounter()) % 2 == 0)
        defend(p);
    
}

void GamePlay::attackerMoveTowardsBall(Player * p)
{
    
    cout << "----" << p->getName() << "----" << endl;
    static unsigned int functionCallctr = 0;
    functionCallctr++;
    /*
     int ballX = layout->getBall()->getX();
     int ballY = layout->getBall()->getY();
     */
    
    int ballX = layout->getBall()->getX();
    int ballY = layout->getBall()->getY();
    
    
    
    
    
    
    // *RIGHT/LEFT* //
    if (ballX > p->getX())
    {
        p->setXPos(p->getX() + 1 );
    }
    else if (ballX < p->getX())
    {
        p->setXPos(p->getX() - 1 );
    }
    
    
    // *UP/DOWN* //
    
    
    if (ballY > p->getY())
    {
        p->setYPos(p->getY() + 1) ;
    }
    else if (ballY < p->getY())
        p->setYPos(p->getY() - 1) ;
    
    if (ballX == p->getX())
    {
        if (ballY > p->getY())
        {
            p->setYPos(p->getY() + 1) ;
        }
        else if (ballY < p->getY())
            p->setYPos(p->getY() - 1) ;
        
    }
    //Finally, change the angle of the player
    
    if (functionCallctr % 40 == 0)
        setPointToBall(p);

    
}

void GamePlay::defend(Player *p)
{
    
    cout << "**** " << p->getName() << " ****** " << endl;
    static unsigned int functionCallctr = 0;
    functionCallctr++;
    /*
     int ballX = layout->getBall()->getX();
     int ballY = layout->getBall()->getY();
     */
    
    int ballX = layout->getBall()->getX();
    int ballY = layout->getBall()->getY();
    
    
    
    
    
    
    // *RIGHT/LEFT* //
    if (ballX > p->getX())
    {
        p->setXPos(p->getX() + 1 );
    }
    else if (ballX < p->getX())
    {
        p->setXPos(p->getX() - 1 );
    }
    
    
    // *UP/DOWN* //
    
    
    if (ballY > p->getY())
    {
        p->setYPos(p->getY() + 1) ;
    }
    else if (ballY < p->getY())
        p->setYPos(p->getY() - 1) ;
    
    if (ballX == p->getX())
    {
        if (ballY > p->getY())
        {
            p->setYPos(p->getY() + 1) ;
        }
        else if (ballY < p->getY())
            p->setYPos(p->getY() - 1) ;
        
    }
    //Finally, change the angle of the player
    
    if (functionCallctr % 40 == 0)
        setPointToBall(p);
    
    //cout << "done x: " << p->getX() << " y: " << p->getY() <<  endl;
    
}



void GamePlay::moveTowardsBall(Player *p)
{
    
    
    static unsigned int functionCallctr = 0;
    functionCallctr++;
    /*
     int ballX = layout->getBall()->getX();
     int ballY = layout->getBall()->getY();
     */
    
    int ballX = layout->hasBall()->getX();
    int ballY = layout->hasBall()->getY();
    
    
    
    
    //if ( functionCallctr % 15 == 0)
    //   setPointToBall(p);
    
    
    
    int deltaY = abs ( (p->getY() -  ballY ) );
    
    int deltaX = abs (p->getX() - ballX);
    int ratio;
    //cout << "delta X: " << deltaX << " delta Y: " << deltaY << endl;
    if ( deltaY != 0 && (deltaX > deltaY))
        ratio = deltaX/deltaY;
    else
        ratio = 1;
    
    //cout << "deltaX: " << deltaX << endl;
    
    //if (ratio >= 7)
    //  ratio = 1;
    
    //cout << "RATIO:  " << ratio << endl;
    
    // *RIGHT/LEFT* //
    if (ballX >= p->getX())
    {
        p->setXPos(p->getX() + ratio );
    }
    else
    {
        p->setXPos(p->getX() - ratio );
    }
    
    
    // *UP/DOWN* //
    //int deltaY2 = abs ( (p->getY() -  layout->getBall()->getY() ) );
    
    //int deltaX2 = abs (p->getX() - layout->getBall()->getX());
    
    int ratio2;
    
    if (deltaX != 0 && (deltaY> deltaX))
        ratio2 = deltaY/deltaX;
    else
        ratio2 = 1;
    
    //if (ratio2 >= 7)
    //ratio2 = 1;
    
    //cout << "RATIO2:  " << ratio2 << endl;
    
    //cout << "deltaY: " << deltaY << endl;
    /*
     if (ratio > 1 || ratio2 > 1)
     {
     int max = 0;
     if (ratio > ratio2)
     max = ratio;
     else
     max = ratio2;
     
     max *=30000;
     
     //max -= (2500 * p->getPace() );
     cout << "HERE1 " << p->getName() << "  sleep time: " << max <<  endl;
     usleep(max);
     
     }
     */
    
    if (ballY >= p->getY())
    {
        p->setYPos(p->getY() + ratio2) ;
    }
    else
        p->setYPos(p->getY() - ratio2) ;
    
    
    int sleepTime = getAdjustSpeed(p->getPace());
    
    /*
     if (ratio == 1 && ratio2 == 1)
     {
     sleepTime -= 50000;
     cout << "HERE2  " << p->getName() << " sleep time: " << sleepTime << endl;
     
     //usleep(sleepTime);
     
     }
     else if (ratio == 0 || ratio2 == 0)
     */
    
    cout << "******" << endl;
    
}

bool GamePlay::shoot(Player * p){
    
    //    Ball * ball = layout->getBall();
    string team = p->getTeamName();
    
    if(team == "homeTeam"){
        if(p->getX() > 1000)
            return true;
    }
    else if(p->getX() < 150)
        return true;
    
    return false;
    
}

//For Defensive Players
void GamePlay::MovePlayers()
{
    unsigned static int ctr = 0;
    ctr++;
   
    Team * defendingTeam = layout->getDefendingTeam();
    map <string, Player *> defendingPlayers = *defendingTeam->getPlayers();
    
    for (std::map<string,Player*>::iterator it = defendingPlayers.begin(); it!= defendingPlayers.end(); ++it)
    {
        Player * p = it->second;
        p->setIsDefending(false);
        //if (p->getName() == "Casillas" || p->getName() == "Terstegen")
           // continue;
        //cout << ">> " << p->getName() << " p->getName(): " <<  p->getName() << " D:  " << layout->getDistanceBall(p);
        cout << "Potential defend: " << p->getName() << endl;
        
        if ( layout->getDistanceBall(p) <= 80   && p->getInPassRadius() == false)
        {
            cout << "<<<<>>>>>>" << p->getInPassRadius() << " ";
            cout << layout->getDistanceBall(p) << endl;
            defend2(p);
            p->setIsDefending(true);
            
        }
        
    }
    
    if (potentialRecipient != NULL)
    {
        Team * attacking = layout->getDefendingTeam();
        map <string, Player *> team = *attacking->getPlayers();
        for (std::map<string,Player*>::iterator it = defendingPlayers.begin(); it!= defendingPlayers.end(); ++it)
        {
            if (layout->getDistanceBall(potentialRecipient) <= 70)
            {
                attackerMoveTowardsBall(potentialRecipient);
            }
            
        }
        
    }
    
}

void GamePlay::resetFaceAngle(Player * player){
    string t = player->getTeamName();
    if(t == "homeTeam"){
        for (std::map<string,Player*>::iterator it=layout->getAwayTeam()->getPlayers()->begin(); it!=layout->getAwayTeam()->getPlayers()->end(); ++it ){
            Player * op = it->second;
            if(layout->distance(player, op) < 50){
                player->setFaceAngle("E");
                
                string a = player->getAngle();
                string ao = op->getAngle();
                if(player->getX() < op->getX()){
                    player->setFaceAngle("N");
                }
            }
        }
    }
    else{
        for (std::map<string,Player*>::iterator it=layout->getAwayTeam()->getPlayers()->begin(); it!=layout->getAwayTeam()->getPlayers()->end(); ++it ){
            Player * op = it->second;
            if(layout->distance(player, op) < 50){
                player->setFaceAngle("W");
                
                string a = player->getAngle();
                string ao = op->getAngle();
                if(player->getX() > op->getX()){
                    player->setFaceAngle("S");
                }
            }
        }
    }
}




void GamePlay::NextMove()
{
    
    int x = layout->getBall()->getX();
    int y = layout->getBall()->getY();
    Player * player = layout->hasBall();
    int numOfRecipients = 0;
    
    cout << "next move" << endl;
    vector<Player *> listOfCloseTeamMates;
    vector<Player *> listOfAvailableTeamMates;
    
    bool kickoff = false;
    if(x == 568 && y == 361){
        kickoff = true;
    }
    //receipi
    //someone has the ball
    if(player != NULL){
        cout << player->getName() + " has the ball" << endl;
        
        if(kickoff){
            listOfCloseTeamMates = layout->getTeamMatesWithin(player, 80);
            Player * player2 = listOfCloseTeamMates[0];
            setPointToPlayer(player, player2);
            layout->hasBall(player);
            int speed = (100 - player2->getPace()) / 5;
            layout->getBall()->kick(2, player2->getX() + (player2->getW()/2), player2->getY() + (player2->getH()/2));
            potentialRecipient = player2;
            //attackerMoveTowardsBall(player2);
            checkInPassRadius(player);
            layout->hasBall(NULL);
        }
        else {
            listOfAvailableTeamMates = layout->getAvailablePlayers(player);
            
            
            if (player->getName() == "Casillas" || player->getName() == "Terstegen")
                numOfRecipients = 1;
            else
                numOfRecipients = 6;
            
           
            if(shoot(player))
            {
                string team = player->getTeamName();
                int destX;
                if(team == "homeTeam")
                    destX = 1100;
                else
                    destX = 50;
                layout->getBall()->kick(1, destX, 350);
                checkInPassRadius(player);
                player->stop();
                layout->hasBall(NULL);
                cout << "<<<shot by: " + player->getName()  << endl;
            }
            //choose one teammate from list of available teammates
            else if(listOfAvailableTeamMates.size() > numOfRecipients || !dribble(player))
            {
                srand(time(NULL));
                int r = 0;
                for(int i = 0; i < listOfAvailableTeamMates.size(); i++){
                    Player * p1 = listOfAvailableTeamMates[i];
                    if(player->getTeamName() == "homeTeam"){
                        if(player->getX() < p1->getX())
                            r = i;
                    }
                    else if(player->getTeamName() == "awayTeam"){
                        if(player->getX() < p1->getX())
                            r = i;
                    }
                }
                if(r == 0)
                    r = rand() % listOfAvailableTeamMates.size();
                
                Player * player2 = listOfAvailableTeamMates[r];
                
                
                
                cout << "chose to pass to: " << player2->getName() << endl;
                setPointToPlayer(player, player2);
                layout->hasBall(player);
                int speed = (100 - player2->getPace()) / 5;
                //int speed = 50;
                cout << "speed: " << speed << endl;
                layout->getBall()->kick(2, player2->getX(), player2->getY());
                checkInPassRadius(player);
                passSourceX = player->getX();
                passSourceY = player->getY();
                cout << "<<<kicked to: " + player2->getName()  << endl;
                //attackerMoveTowardsBall(player2);
                potentialRecipient = player2;
                cout << "xX: " << player->getX() << " yY:" << player->getY() << endl;
                layout->hasBall(NULL);
            }
            else
                layout->hasBall(player);
        }
    }
    
    //Its travelling a trajectory
    calculateKickDistance();
    
    
}

void GamePlay::checkInPassRadius(Player * passer)
{
    cout << "HERE" << endl;
    Team * defense = layout->getDefendingTeam();
    for (std::map<string,Player*>::iterator it=defense->getPlayers()->begin(); it!=defense->getPlayers()->end(); ++it )
    {
        Player * defender = it->second;
        cout <<  "% " << defender->getName() <<  " " << layout->getDistance(defender->getX(), defender->getY(), passer->getX(), passer->getY()) << endl;
        
        cout << "x: " << defender->getX() << " y:" <<defender->getY() << endl;
        if (layout->getDistance(defender->getX(), defender->getY(), passer->getX(), passer->getY()) <= 110)
        {
            
            defender->setInPassRadius(true);
        }
    }
    
}

void GamePlay::resetInPassRadius()
{
    Team * defense = layout->getDefendingTeam();
    for (std::map<string,Player*>::iterator it=defense->getPlayers()->begin(); it!=defense->getPlayers()->end(); ++it )
    {
        Player * defender = it->second;
        defender->setInPassRadius(false);

    }
    
    //Do the other team just in case
    Team * attacking = layout->getAttackingTeam();
    for (std::map<string,Player*>::iterator it=attacking->getPlayers()->begin(); it!=attacking->getPlayers()->end(); ++it )
    {
        Player * attacker = it->second;
        attacker->setInPassRadius(false);
        
    }
  
}
void GamePlay::calculateKickDistance()
{
    travelledDistance = layout->getDistance(passSourceX, passSourceY, layout->getBall()->getX(), layout->getBall()->getY());
}

vector<Player *> GamePlay::rectangleFilter(Player * possessBall)
{
    vector <Player * > availableTeammate;
    
    //iterate through all the teammates
    for (std::map<string,Player*>::iterator it=layout->getHomeTeam()->getPlayers()->begin(); it!=layout->getHomeTeam()->getPlayers()->end(); ++it )
    {
        Player * teammate = it->second;
        if (possessBall->getName() == teammate->getName())
            continue;
        
        bool isClear = layout->isRectangleAreaInFrontClear2(possessBall, teammate);
        
        if (isClear)
            availableTeammate.push_back(teammate);
    }
    
    return availableTeammate;
    
}



void GamePlay::setPointToPlayer(Player *p, Player *p2)
{
    int ballX = p2->getX();
    int ballY = p2->getY();
    
    if (ballY < p->getY())
    {
        if (ballX < p->getX())
        {
            p->setFaceAngle("NW");
        }
        else if (ballX > p->getX())
        {
            p->setFaceAngle("NE");
        }
        else
        {
            p->setFaceAngle("N");
        }
        
        
    }
    else if (ballY > p->getY() )
    {
        if (ballX < p->getX())
        {
            p->setFaceAngle("SW");
        }
        else if (ballX > p->getX())
        {
            
            p->setFaceAngle("SE");
        }
        else
        {
            p->setFaceAngle("S");
        }
        
    }
    else
    {
        if (ballX > p->getX())
            p->setFaceAngle("W");
        else
            p->setFaceAngle("E");
    }
    
    
}

bool GamePlay::dribble(Player * p){
    
    int screenH = 700;
    int screenW = 1150;
    
    if (p->getName() == "Casillas" || p->getName() == "Terstegen")
    {
        int casillasX =  screenW - 50;
        int casillasY = screenH/2;
        
        int terstegenX = 50;
        int terstegenY = screenH/2;
        
        if (p->getName() == "Casillas")
        {
        
            if (layout->getDistance(casillasX, casillasY, p->getX(), p->getY()) <= 45)
                return false;
        }
        else
        {
            if (layout->getDistance(terstegenX, terstegenY, p->getX(), p->getY()) <= 45) {
                return false;
            }
        }
        
    }
    if(p->getDestX() != 0 && p->getDestY() != 0)
        return true;
    
    bool openSpace = true;
    int x = 0;
    int y = 0;
    if(p->getTeamName() == "homeTeam"){
        p->setFaceAngle("E");
        x = p->getX() + 50;
        y = p->getY();
    }
    else {
        p->setFaceAngle("W");
        x = p->getX() - 50;
        y = p->getY();
    }
    
    if(!layout->isRectangleAreaInFrontClear(p, x, y)){
        if(p->getTeamName() == "homeTeam"){
            p->setFaceAngle("SE");
            x = p->getX() + 50;
            y = p->getY() + 50;
        }
        else {
            p->setFaceAngle("SW");
            x = p->getX() - 50;
            y = p->getY() + 50;
        }
    }
    if(!layout->isRectangleAreaInFrontClear(p, x, y)){
        if(p->getTeamName() == "homeTeam"){
            p->setFaceAngle("NE");
            x = p->getX() + 50;
            y = p->getY() - 50;
        }
        else {
            p->setFaceAngle("NW");
            x = p->getX() - 50;
            y = p->getY() - 50;
        }
    }
    if(!layout->isRectangleAreaInFrontClear(p, x, y)){
        openSpace = false;
    }
    
    if(openSpace){
        p->dribble(x, y);
        cout << p->getName() << "is dribbling" <<endl;
    }
    
    return openSpace;
    
}


bool GamePlay::checkCollision(Ball * ball, Player * player)
{
    int bx = ball->getX();
    int by = ball->getY();
    int bh = ball->getH();
    int bw = ball->getW();
    int px = player->getX();
    int py = player->getY();
    int ph = player->getH();
    int pw = player->getW();
    
    //ball left
    if(px > bx && px < bx + bw){
        //collision if ball top or bottom is between player top and bottom.
        if(by >= py && by <= py + ph){
            return true;
        }
        if(by + bh > py && by + bh < py + ph){
            return true;
        }
    }
    //ball right between player left side and player right side.
    if(px <= bx && px + pw >= bx){
        //collision if ball top or bottom  is between player top and bottom.
        if(by >= py && by <= py + ph){
            return true;
        }
        if(by + bh > py && by + bh < py + ph){
            return true;
        }
    }
    
    return false;
}

void GamePlay::move(){
    
    //move ball
    Ball * ball = layout->getBall();
    ball->updatePos();
    //move players
    Player * player = layout->hasBall();
    Team * team;
    
    if(player != NULL){
        if(player->getTeamName() == "awayTeam")
            team = layout->getHomeTeam();
        else
            team = layout->getAwayTeam();
        for (std::map<string,Player*>::iterator it=team->getPlayers()->begin(); it!=team->getPlayers()->end(); ++it ){
            Player * player = it->second;
            if(checkCollision(ball, player)){
                potentialRecipient = NULL;
                resetInPassRadius();
                ball->resetDest(0, 0);
                layout->hasBall(player);
                distanceKick = 0;
                cout << "<<<Got ball: " + player->getName()  << endl;
                
            }
        }
    }
    else {
        for (std::map<string,Player*>::iterator it=layout->getHomeTeam()->getPlayers()->begin(); it!=layout->getHomeTeam()->getPlayers()->end(); ++it ){
            Player * player = it->second;
            if(checkCollision(ball, player)){
                potentialRecipient = NULL;
                resetFaceAngle(player);
                resetInPassRadius();
                ball->resetDest(0, 0);
                layout->hasBall(player);
                distanceKick = 0;
                cout << "<<<Got ball: " + player->getName()  << endl;
            }
        }
        
        for (std::map<string,Player*>::iterator it=layout->getAwayTeam()->getPlayers()->begin(); it!=layout->getAwayTeam()->getPlayers()->end(); ++it ){
            Player * player = it->second;
            if(checkCollision(ball, player)){
                potentialRecipient = NULL;
                resetFaceAngle(player);
                resetInPassRadius();
                ball->resetDest(0, 0);
                layout->hasBall(player);
                distanceKick = 0;
                cout << "<<<Got ball: " + player->getName()  << endl;
            }
        }
    }
    
    
    if(player != NULL){
        player->updatePos();
    }
    
    //move defenders (they go after ball)
    GamePlay::MovePlayers();
    
    
    /*
    //after moving anyone
    Player * ter = layout->getHomeTeam()->getPlayer("Terstegen");
    
    // original position for Terstegern
    int originalX = 50;
    int originalY = 700/2;
    
    goalieGetBack(ter, originalX, originalY);
    
    Player * casillas = layout->getAwayTeam()->getPlayer("Casillas");
    
    originalX = 1150 - 50;
    
    goalieGetBack(casillas, originalX, originalY);
    */
    if(ball->getY() == 350){
        if(ball->getX() == 1100){
            ball->resetDest(0, 0);
            homeScore++;
            layout->reset();
        }
        else if(ball->getX() == 50){
            ball->resetDest(0, 0);
            awayScore++;
            layout->reset();
        }
    }
}

void GamePlay::goalieGetBack(Player * goalie1, int originalX, int originalY)
{
    
    cout << "GOALIE: " << goalie1->getName() <<  " " << goalie1->isDefending() << endl;
    if (goalie1->isDefending() == false)
    {
        Player * playerHasBall = layout->hasBall();
        if (playerHasBall != NULL)
        {
            if (playerHasBall->getName() != goalie1->getName()) //check the player dribbling is not this goalie1
            {
                goalie1->dribble(originalX, originalY);
                cout << "&&&&&&&" << endl;
            }
        }
        else //ball is in a trajectory, i.e. no one has possesion of it
        {
            goalie1->dribble(originalX, originalY);
             cout << "2&&&&&&&" << endl;
        }
    }
    
    
}

void GamePlay::stopDefendersFromChasing(Player *p)
{
    int RANGE = 40;
    Team * team = layout->getDefendingTeam();
    
    for (std::map<string,Player*>::iterator it=team->getPlayers()->begin(); it!=team->getPlayers()->end(); ++it )
    {
        Player * opponent = it->second;
        
        if (layout->distanceBetweenPlayers(p, opponent) <= RANGE)
        {
            opponent->setChase(false);
        }
        
    }

}