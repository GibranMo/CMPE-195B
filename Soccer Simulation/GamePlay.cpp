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
 void GamePlay :: playerAction(Player * p)
 {
 cout << "UP HERE" << endl;
 cout << layout->hasBall()->getName();
 
 }
 
 */

void GamePlay::testFoo(GLuint gl, Player * pl)
{
    cout << "QRS" << endl;
    glDrawSprite(gl, pl->getX(), pl->getY(), 20, 20);
    
}
void * GamePlay :: player_t(void * param)
{
    Player * p = (Player *) param;
    
    string name = p->getName();
    
    //cout << ">>" << name << endl;
    //
    if(name == "A")
        cout << "*}" << endl;
    
    
    
    cout << expLayout->testInt() << endl;
    
    int t = p->getX();
    
    cout << name << "'s current x pos is: " << t << endl;
    
    int i = 0;
    
    while (true)
    {
        //glDrawSprite3(player->getTex(), player->getX(), player->getY(), 20, 20);
        //glDrawSprite(p->getTex(), i, p->getY(), 20, 20);
        GLuint textr = glTexImageTGAFile("images/1.tga");
        cout << t << endl;
        testFoo(textr, p);
        
        //i++;
    }
    
    //string n = p->getName();
    //cout << ">" << n << endl;
    
    /*
     map <string, Player *> listOfPlayers = *expLayout->getHomeTeam()->getPlayers();
     for (std::map<string,Player*>::iterator it=listOfPlayers.begin(); it!=listOfPlayers.end(); ++it){
     glDrawSprite(it->second->getTex(), it->second->getX(), it->second->getY(), 20, 20);
     
     }
     */
    
    //GamePlay::drawingTest();
    
    
    
    
    //Layout * l  = layout;
    return NULL;
}



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
            
            glDrawSprite(it->second->getTex(), it->second->getX(), it->second->getY(), 16, 16);
        }
        
        glDrawSprite(layout->getBall()->getTex(), layout->getBall()->getX(), layout->getBall()->getY(), 10, 8);
        
        
        GLuint testTex = glTexImageTGAFile("images/1.tga");
        GLuint testTex2 = glTexImageTGAFile("images/3.tga");
        
        glDrawSprite(testTex2, 0, -10, 30, 50);
        glDrawSprite(testTex, 0, 50, 30, 50);
        
        
        //        glDrawLines();
        //        glDrawPoint();
        
    }
}

void GamePlay::moveTowardsBall(Player *p)
{
    int ballX = layout->getBall()->getX();
    int ballY = layout->getBall()->getY();
    
    string xdir = "";
    string ydir = "";
    
    if (ballX >= p->getX())
    {
        xdir = "right";
        p->setXPos(p->getX()+ 0.1 + (p->getPace()/1000));
        
    }
    else
    {
        xdir = "left";
        p->setXPos(p->getX() - 0.1 + (p->getPace()/1000) );
        
    }
    
    if (ballY >= p->getY())
    {
        
        ydir = "down";
        p->setYPos(p->getY() + 0.1 + (p->getPace()/1000) );
        
    }
    else
    {
        
        ydir = "up";
        p->setYPos(p->getY() -  0.1 + (p->getPace()/1000)) ;
        
    }
    
}


void GamePlay::MovePlayers()
{
    
    Team * defendingTeam = layout->getDefendingTeam();
    map <string, Player *> defendingPlayers = *defendingTeam->getPlayers();
    
    for (std::map<string,Player*>::iterator it = defendingPlayers.begin(); it!= defendingPlayers.end(); ++it)
    {
        Player * p = it->second;
        
        if (layout->getDistanceBall(p) <= 170)
        {
            
            moveTowardsBall(p);
            cout << "defending" << endl;
            
        }
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
                int speed = (100 - player2->getPace()) / 3;
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
                int speed = (100 - player2->getPace()) / 3;
                layout->getBall()->kick(speed, player2->getX(), player2->getY());
                cout << "<<<kicked to: " + player2->getName()  << endl;
                layout->hasBall(NULL);
            }
        }
        //take care of other player
        
        
        
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
    
    //move players
    for (std::map<string,Player*>::iterator it=layout->getHomeTeam()->getPlayers()->begin(); it!=layout->getHomeTeam()->getPlayers()->end(); ++it ){
        Player * player = it->second;
        if(checkCollision(ball, player)){
            ball->resetDest(0, 0);
            layout->hasBall(player);
            cout << "<<<Got ball: " + player->getName()  << endl;
        }
    }
}