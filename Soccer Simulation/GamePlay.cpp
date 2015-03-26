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
#include<SDL2/SDL.h>
#include<GL/glew.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

using namespace std;


GamePlay::GamePlay(Layout * l, GLuint ft)
{
    
    layout = l;
    fieldTex = ft;
    
}



void GamePlay::DrawSprite(bool playing)
{
    
    if(!playing) {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else {
        glDrawSprite(fieldTex, 0, 0, 1150, 700);
        
        map <string, Player *> listOfPlayers = *layout->getHomeTeam()->getPlayers();
        
        map <string, Player *> listOfPlayers2 = *layout->getAwayTeam()->getPlayers();

    
        for (std::map<string,Player*>::iterator it=listOfPlayers.begin(); it!=listOfPlayers.end(); ++it){
            glDrawSprite(it->second->getTex(), it->second->getX(), it->second->getY(), 20, 20);
        }
        for (std::map<string,Player*>::iterator it=listOfPlayers2.begin(); it!=listOfPlayers2.end(); ++it){
        
            glDrawSprite(it->second->getTex(), it->second->getX(), it->second->getY(), 20, 20);
        }
  
    }
}

void GamePlay::NextMove(bool kickoff)
{
    int x = layout->getBall()->getX();
    int y = layout->getBall()->getY();
    Player * player = layout->hasBall();
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
    
    
    
    
}

//void GamePlay::CheckCollision()
//{
//    
//}
//
//void GamePlay::Move(){
//    
//}