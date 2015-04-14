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

/*
 void GamePlay::setUpThreads ()
 {
 
 map <string, Player *> listOfPlayers = *layout->getHomeTeam()->getPlayers();
 
 vector <Player *> list;
 int r = 1;
 for (std::map<string,Player*>::iterator it2=listOfPlayers.begin(); it2!=listOfPlayers.end(); ++it2){
 //glDrawSprite(it2->second->getTex(), it2->second->getX(), it2->second->getY(), 20, 20);
 //cout << "r" << r << endl;
 list.push_back(it2->second);
 r++;
 
 }
 
 for (int i = 0; i <=1; i++)
 {
 //int index = i--; //
 pthread_attr_t playerAttr;
 pthread_attr_init(&playerAttr);
 //cout << "main() : creating thread, " << i << endl;
 cout << ">>: " <<list.at(i)->getName() << endl;
 int rc = pthread_create(&playerThreads[i], &playerAttr, player_t, list.at(i));
 if (rc){
 cout << "Error:unable to create thread," << rc << endl;
 //exit(-1);
 }
 //it++;
 
 }
 
 pthread_attr_t drawAttr;
 pthread_attr_init(&drawAttr);
 pthread_t drawThread;
 
 //int t = pthread_create(&drawThread, &drawAttr, draw_t, &fieldTex);
 
 // if (t){
 //   cout << "TError:unable to create thread," << t << endl;
 //exit(-1);
 // }
 
 
 
 }
 
 */

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
    
    if (ballY > p->getY())
    {
        if (ballX < p->getX())
            p->setFaceAngle("SW");
        
        if (ballX == p->getX())
            p->setFaceAngle("S");
    }
    
}



void GamePlay::moveTowardsBall(Player *p)
{
    static unsigned int functionCallctr = 0;
    functionCallctr++;
    
    int ballX = layout->getBall()->getX();
    int ballY = layout->getBall()->getY();
    
    string xdir = "";
    string ydir = "";
    
    
    if ( functionCallctr == 1)
        setPointToBall(p);
    
    //setPointToBall(p);
    //usleep(1500);
    
    //setPointToBall(p);
    
    //int ratio = abs(p->getX() - layout->getBall()->getX() ) >  (2 *  abs ( (p->getY() -  layout->getBall()->getY() ) )) ;
    
    /*
     
     if ( deltaX >= deltaY && deltaY != 0)
     ratio = deltaX/deltaY;
     else
     ratio = 1;
     
     cout << "RATIO:  " << ratio << endl;
     // *RIGHT/LEFT* //
     if (ballX >= p->getX())
     {
     
     p->setXPos(p->getX() + ratio );
     }
     else
     {
     p->setXPos(p->getX() -  ratio );
     
     int deltaY2 = abs ( (p->getY() -  layout->getBall()->getY() ) );
     
     int deltaX2 = abs (p->getX() - layout->getBall()->getX());
     
     int ratio2;
     
     if ( (deltaY2 >= deltaX2) && deltaX2 != 0)
     ratio2 = deltaY2/deltaX2;
     else
     ratio2 = 1;
     
     // *UP/DOWN* //
     cout << "RATIO2:  " << ratio2 << endl;
     if (ballY >= p->getY())
     {
     
     p->setYPos(p->getY() + ratio2) ;
     
     }
     else
     p->setYPos(p->getY() - ratio2) ;
     
     
     }
     
     */
    
    
    int deltaY = abs ( (p->getY() -  layout->getBall()->getY() ) );
    
    int deltaX = abs (p->getX() - layout->getBall()->getX());
    int ratio;
    cout << "delta X: " << deltaX << " delta Y: " << deltaY << endl;
    if ( deltaY != 0 && (deltaX > deltaY))
        ratio = deltaX/deltaY;
    else
        ratio = 1;
    
    if (ratio >= 8)
        ratio = 1;
    
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
    int deltaY2 = abs ( (p->getY() -  layout->getBall()->getY() ) );
    
    int deltaX2 = abs (p->getX() - layout->getBall()->getX());
    
    int ratio2;
    
    if (deltaX2 != 0 && (deltaY> deltaX))
        ratio2 = deltaY2/deltaX2;
    else
        ratio2 = 1;
    
    if (ratio2 >= 8)
        ratio2 = 1;
    
    cout << "RATIO2:  " << ratio2 << endl;
    
    if (ballY >= p->getY())
    {
        p->setYPos(p->getY() + ratio2) ;
    }
    else
        p->setYPos(p->getY() - ratio2) ;
    
    
    
}


void GamePlay::MovePlayers()
{
    
    Team * defendingTeam = layout->getDefendingTeam();
    map <string, Player *> defendingPlayers = *defendingTeam->getPlayers();
    
    for (std::map<string,Player*>::iterator it = defendingPlayers.begin(); it!= defendingPlayers.end(); ++it)
    {
        Player * p = it->second;
        
        if (layout->getDistanceBall(p) <= 1100)
        {
            if (p->getName() == "Bale")
            {
                moveTowardsBall(p);
                cout << "defending" << endl;
            }
            
        }
    }
    
    
}


void GamePlay::NextMove()
{
    
    int x = layout->getBall()->getX();
    int y = layout->getBall()->getY();
    Player * player = layout->hasBall();
    
    if (player == NULL)
    {
        
        cout << "no one has the ball" << endl;
        //Example: ball is travelling
    }
    else
    {
        GamePlay::MovePlayers();
        cout << "next move" << endl;
        
        
        
        //layout->analyzeField(player);
        
        /*
         vector<Player *> listOfCloseTeamMates = layout->getTeamMatesWithin80(player);
         vector<Player *> listOfAvailableTeamMates;
         
         bool kickoff = false;
         
         if(kickoff){
         //kick
         }
         else{
         listOfAvailableTeamMates = layout->getAvailablePlayers(player);
         for(int i = 0; i < listOfCloseTeamMates.size(); i++){
         listOfAvailableTeamMates.push_back(listOfCloseTeamMates[i]);
         }
         cout << "*****<><><>" << endl;
         }
         */
        //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
    
    
    /*
     vector<Player *> listOfCloseTeamMates = layout->getTeamMatesWithin40(player);
     vector<Player *> listOfAvailableTeamMates;
     
     
     
     
     
     if(kickoff){
     //kick
     }
     else{
     listOfAvailableTeamMates = layout->getAvailablePlayers(player);
     for(int i = 0; i < listOfCloseTeamMates.size(); i++){
     listOfAvailableTeamMates.push_back(listOfCloseTeamMates[i]);
     }
     }
     */
    
    
    
    
}

//void GamePlay::CheckCollision()
//{
//
//}
//
//void GamePlay::Move(){
//
//}