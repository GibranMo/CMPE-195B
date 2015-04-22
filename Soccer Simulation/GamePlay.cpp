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
        
        glDrawSprite2(layout->getBall()->getTex(), layout->getBall()->getX(), layout->getBall()->getY(), 10, 8);
        
        
        GLuint testTex = glTexImageTGAFile("images/1.tga");
        GLuint testTex2 = glTexImageTGAFile("images/3.tga");
        
        glDrawSprite(testTex2, 0, -10, 30, 50);
        glDrawSprite(testTex, 0, 50, 30, 50);
        
        
        //        glDrawLines();
        //        glDrawPoint();
        
    }
}

void GamePlay::setPointToBall(Player *p)
{
    int ballX = layout->getBall()->getX();
    int ballY = layout->getBall()->getY();
    
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
            cout << "<Name>: " << p->getY() << "SET SW SET SWSET SWSET SWSET SWSET SWSET SWSET SWSET SWSET SW" << endl;
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
    cout << "CTRdefend2:  " << callCtr << endl;

    
    int speed = p->getPace();
    
    speed = 100 - speed;
    
    
    
    p->incrementCounter();
   
    if ((p->getCounter()) % 2 == 0)
        defend(p);
    
    cout << "end defend2" << endl;
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
    
    cout << "done x: " << p->getX() << " y: " << p->getY() <<  endl;
    
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
    
    cout << "deltaX: " << deltaX << endl;
    
    //if (ratio >= 7)
      //  ratio = 1;
    
    cout << "RATIO:  " << ratio << endl;
    
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
        
    cout << "RATIO2:  " << ratio2 << endl;
    
    cout << "deltaY: " << deltaY << endl;
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


void GamePlay::MovePlayers()
{
    unsigned static int ctr = 0;
    ctr++;
    cout << "counter " << ctr << endl;
    Team * defendingTeam = layout->getDefendingTeam();
    map <string, Player *> defendingPlayers = *defendingTeam->getPlayers();
    
    for (std::map<string,Player*>::iterator it = defendingPlayers.begin(); it!= defendingPlayers.end(); ++it)
    {
        Player * p = it->second;
        if (p->getName() == "Casillas")
            continue;
        //cout << ">> " << p->getName() << " p->getName(): " <<  p->getName() << " D:  " << layout->getDistanceBall(p);
         //cout << " x: " << p->getX() << " y: " << p->getY() << endl;
        if (layout->getDistanceBall(p) <= 150 || (layout->getClosestDefenderToBall()->getName() == p->getName()))
        {
            
            
                    //cout << "Name: " << p->getName() << " x: " << p->getX() << " y: " << p->getY() << endl;
                    defend2(p);
                
             
         }
        
       // p
    }
    
}




void GamePlay::NextMove()
{
    
    int x = layout->getBall()->getX();
    int y = layout->getBall()->getY();
    Player * player = layout->hasBall();
    
    if (player == NULL) {
        cout << "no one has the ball" << endl;
        //Example: ball is travelling
    }
    else {
        cout << "next move" << endl;
        cout << player->getName() + " has the ball" << endl;
        vector<Player *> listOfCloseTeamMates;
        vector<Player *> listOfAvailableTeamMates;
        
        bool kickoff = false;
        if(x == 568 && y == 361){
            kickoff = true;
        }
        
        //someone has the ball
        if(player != NULL){
            if(kickoff){
                listOfCloseTeamMates = layout->getTeamMatesWithin(player, 80);
                Player * player2 = listOfCloseTeamMates[0];
                setPointToPlayer(player, player2);
                layout->hasBall(player);
                int speed = (100 - player2->getPace()) / 5;
                layout->getBall()->kick(speed, player2->getX() + (player2->getW()/2), player2->getY() + (player2->getH()/2));
                cout << "<<<kicked to: " + player2->getName()  << endl;
                layout->hasBall(NULL);
            }
            else {
                listOfCloseTeamMates = layout->getTeamMatesWithin(player, 100);
                listOfAvailableTeamMates = layout->getAvailablePlayers(player);
                for(int i = 0; i < listOfCloseTeamMates.size(); i++){
                    listOfAvailableTeamMates.push_back(listOfCloseTeamMates[i]);
                }
                
                //choose one teammate from list of available teammates
                srand(time(NULL));
                int r = rand() % listOfAvailableTeamMates.size();
                Player * player2 = listOfAvailableTeamMates[r];
                setPointToPlayer(player, player2);
                layout->hasBall(player);
                int speed = (100 - player2->getPace()) / 5;
                layout->getBall()->kick(speed, player2->getX(), player2->getY());
                cout << "<<<kicked to2: " + player2->getName()  << endl;
                layout->hasBall(NULL);
            }
        }
        //take care of other player
        
        //GamePlay::MovePlayers();

        
        //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
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
        if(by > py && by < py + ph){
            return true;
        }
        if(by + bh > py && by + bh < py + ph){
            return true;
        }
    }
    //ball right between player left side and player right side.
    if(px < bx && px + pw > bx){
        //collision if ball top or bottom  is between player top and bottom.
        if(by > py && by < py + ph){
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
    cout << "xx: " << ball->getX() << " yy: " << ball->getY() << endl;
    
    //move players
    for (std::map<string,Player*>::iterator it=layout->getHomeTeam()->getPlayers()->begin(); it!=layout->getHomeTeam()->getPlayers()->end(); ++it ){
        Player * player = it->second;
        if(checkCollision(ball, player)){
            ball->resetDest(0, 0);
            layout->hasBall(player);
            cout << "<<<Got ball: " + player->getName()  << endl;
        }
    }
    for (std::map<string,Player*>::iterator it=layout->getAwayTeam()->getPlayers()->begin(); it!=layout->getAwayTeam()->getPlayers()->end(); ++it ){
        Player * player = it->second;
        if(checkCollision(ball, player)){
            ball->resetDest(0, 0);
            layout->hasBall(player);
            cout << "<<<Got ball: " + player->getName()  << endl;
        }
    }
    
    GamePlay::MovePlayers();
}