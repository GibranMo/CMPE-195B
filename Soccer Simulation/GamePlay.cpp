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



void GamePlay::DrawSprite()
{


        map<string, Player*>* map2 = layout->getAwayTeam()->getPlayers();
        map<string, Player*>* map = layout->getHomeTeam()->getPlayers();
    
    
        // start the game draw graphics (players & ball & gameplay background)
        glDrawSprite(fieldTex, 0, 0, 1150, 700);
    
        
        //map<string, Player*>* map = homeTeam.getPlayers();
        
        //iterate over each player on the home team
        for (std::map<string,Player*>::iterator it=map->begin(); it!=map->end(); ++it){ //iterating over the hometeam map
            
            
            glDrawSprite(glTexImageTGAFile("images/1.tga", 0, 0),
                         it->second->getX(), it->second->getY(), 20, 20); //Drawing the palyer
        }
        
        /*
        for (std::map<string,Player*>::iterator it=map2->begin(); it!=map2->end(); ++it){
            
            glDrawSprite(glTexImageTGAFile("images/1.tga", 0, 0),
            it->second->getX(), it->second->getY(), 20, 20);
        }
         */
        
        glDrawLines();
    

}