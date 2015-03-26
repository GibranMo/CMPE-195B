//
//  main.cpp
//  Soccer Simulation
//
//  Created by Carlos Toledo on 2/10/15.
//  Copyright (c) 2015 Carlos Toledo. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "DrawUtils.h"
#include "EventHandler.h"
#include "Player.h"
#include "Team.h"
#include "Layout.h"
#include "Ball.h"
#include "GamePlay.h"
#include <map>


using namespace std;

int screenW = 1150;
int screenH = 700;


int main(void)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }
    // Create the window, OpenGL context
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Window* window = SDL_CreateWindow(
                                          "Soccer Simulation",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          screenW, screenH,
                                          SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_Quit();
        return 1;
    }
    SDL_GL_CreateContext(window);
    
    //Manage image rendering settings
    glViewport(0, 0, screenW, screenH);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, screenW, screenH, 0, 0, 1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.04);
    
    
    //Setup
    int quit = 0;
    //Setup actors
    const char* filename = "images/1.tga";
    map <string, Player *> listOfPlayers;
    Player p1("A", 50, screenH/2, filename, "homeTeam");
    listOfPlayers[p1.getName()] = &p1;
    Player p2("B", 250, screenH/2 + 100, filename, "homeTeam");
    listOfPlayers[p2.getName()] = &p2;
    Player p3("C", 250, screenH/2 + 200, filename, "homeTeam");
    listOfPlayers[p3.getName()] = &p3;
    Player p4("D", 250, screenH/2 - 100, filename, "homeTeam");
    listOfPlayers[p4.getName()] = &p4;
    Player p5("E", 250, screenH/2 - 200, filename, "homeTeam");
    listOfPlayers[p5.getName()] = &p5;
    Player p6("F", 400, screenH/2 - 100, filename, "homeTeam");
    listOfPlayers[p6.getName()] = &p6;
    Player p7("G", 400, screenH/2 + 100, filename, "homeTeam");
    listOfPlayers[p7.getName()] = &p7;
    Player p8("H", 400, screenH/2, filename, "homeTeam");
    listOfPlayers[p8.getName()] = &p8;
    Player p9("I", 450, screenH/2, filename, "homeTeam");
    listOfPlayers[p9.getName()] = &p9;
    Player p10("J", screenW/2, screenH/2 + 10, filename, "homeTeam");
    listOfPlayers[p10.getName()] = &p10;
    Player p11("K", screenW/2, screenH/2, filename, "homeTeam");
    listOfPlayers[p11.getName()] = &p11;
    Team homeTeam(listOfPlayers);
    
    map <string, Player *> listOfPlayers2;
    Player p21("Z", screenW - 50, screenH/2, filename, "awayTeam");
    listOfPlayers2[p21.getName()] = &p21;
    Player p22("Y", screenW - 250, screenH/2 + 100, filename, "awayTeam");
    listOfPlayers2[p22.getName()] = &p22;
    Player p23("X", screenW - 250, screenH/2 + 200, filename, "awayTeam");
    listOfPlayers2[p23.getName()] = &p23;
    Player p24("W", screenW - 250, screenH/2 - 100, filename, "awayTeam");
    listOfPlayers2[p24.getName()] = &p24;
    Player p25("V", screenW - 250, screenH/2 - 200, filename, "awayTeam");
    listOfPlayers2[p25.getName()] = &p25;
    Player p26("U", screenW - 400, screenH/2 - 100, filename, "awayTeam");
    listOfPlayers2[p26.getName()] = &p26;
    Player p27("T", screenW - 400, screenH/2 + 200, filename, "awayTeam");
    listOfPlayers2[p27.getName()] = &p27;
    Player p28("S", screenW - 400, screenH/2, filename, "awayTeam");
    listOfPlayers2[p28.getName()] = &p28;
    Player p29("R", screenW - 500, screenH/2, filename, "awayTeam");
    listOfPlayers2[p29.getName()] = &p29;
    Player p210("Q", screenW - 500, screenH/2 + 200, filename, "awayTeam");
    listOfPlayers2[p210.getName()] = &p210;
    Player p211("P", screenW - 500, screenH/2 - 200, filename, "awayTeam");
    listOfPlayers2[p211.getName()] = &p211;
    Team awayTeam(listOfPlayers2);

    Ball ball(screenW/2, screenH/2, 10,10, "images/1.tga");
    
    Layout layout(&homeTeam, &awayTeam, &ball);
    layout.initialSetUp433();
    layout.hasBall(&p11);

    //EventHandling.cpp
    initEventQueue();
    //set up textures and game
    GLuint fieldTex = glTexImageTGAFile("images/soccer.tga");

    GamePlay gamePlay(&layout, fieldTex);
    
    bool playing = false;
    
    
    //Frame handling
    //Current time
    float timeCurrentFrame = (float)SDL_GetTicks();
    float timeSinceLastFrame = 0;
    int ticksPerFrame = 1000 / 60; //< or whatever other framerate you want as a max
    int prevTick = SDL_GetTicks();
    int ticksPerPhysics = 1000 / 100;
    int prevPhysicsTick = prevTick;
    
    //Save pressed keys
    unsigned char kbPrevState[SDL_NUM_SCANCODES] = { 0 };
    const unsigned char* kbState = NULL;
    kbState = SDL_GetKeyboardState(NULL);
    
    while (!quit) {
        
        memcpy(kbPrevState, kbState, sizeof(kbPrevState));
        
        //Update frame time
        timeSinceLastFrame = SDL_GetTicks() - timeCurrentFrame;
        timeCurrentFrame = timeCurrentFrame + timeSinceLastFrame;
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
            }
        }
        
        //Handle game state. Playing, outside, foul. Start the game set up
        if (kbState[SDL_SCANCODE_SPACE]){
            playing = true;

        }
        
        
        // throttle framerate
        int tick = SDL_GetTicks();
        do {
            SDL_Delay(max(0, ticksPerFrame - (tick - prevTick)));//changed from MAX
            tick = SDL_GetTicks();
            
        } while (ticksPerFrame - (tick - prevTick) > 0);
        prevTick = tick;
        
        
        
        // Game logic

        //DRAWING
        gamePlay.DrawSprite(playing);
       
        
        gamePlay.NextMove(true);
        
        
        //PHYSICS
        while (tick > prevPhysicsTick + ticksPerPhysics) {
            //update physics
            
            if (playing){
                //check collisions and add any to the event handler queue
                //queueEvent(<#Event *ev#>)
                
            }
            prevPhysicsTick += ticksPerPhysics;
        }
        
        //EVENT HANLDLING
        updateEventQueue();
        
        //MOVEMENT
        if (playing){
            //Ball movement & PLAYER movements, update positions

            
        }
        
        //end game logic
        
        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}