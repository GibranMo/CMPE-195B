
//
//  GamePlay.h
//  Soccer1
//
//  Created by Gibran Morales on 3/9/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#ifndef Soccer1_GamePlay_h
#define Soccer1_GamePlay_h


#include "GamePlay.h"
#include "Layout.h"
#include "Team.h"
#include "DrawUtils.h"
#include "EventHandler.h"
#include <string>
#include <vector>
#include<SDL2/SDL.h>
#include<GL/glew.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>


using namespace std;

class GamePlay
{
    
private:
    Layout * layout;
    GLuint fieldTex;
    
    pthread_t playerThreads[2];
    static void *player_t(void * param);
    static void *draw_t(void *);
    static string foo();
    void playerAction(Player * p);
    int computePositionScore(int countInFront);
    
    
    //Test
    static void testFoo(GLuint gl, Player * pl);
    void drawingTest();
    
public:
    GamePlay(Layout * l, GLuint ft);
    void DrawSprite(bool playing);
    void NextMove();
    void setUpThreads();
    
    
    
    
};

#endif
