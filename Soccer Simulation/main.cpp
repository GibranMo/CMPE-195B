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
    const char* filename = "images/dotBlackArrow.tga";
    map <string, Player *> listOfPlayers;
    Player p1("Terstegen", 51, screenH/2, 20, 20, filename, "homeTeam", "E", 0, 0, 0, 0, 0, 0, 0);
    listOfPlayers[p1.getName()] = &p1;
    Player p2("Mathieu", 250, screenH/2 - 100 + 25, 20, 20, filename, "homeTeam", "E", 76, 64, 66, 55, 82, 81, 80);
    listOfPlayers[p2.getName()] = &p2;
    Player p3("Alba", 250 , screenH/2 -  200, 20, 20, filename, "homeTeam", "E", 92, 69, 75, 81, 78, 76, 81);
    listOfPlayers[p3.getName()] = &p3;
    Player p4("Pique", 250, screenH/2 + 100 - 25, 20, 20, filename, "homeTeam", "E", 66, 54, 69, 60, 86, 76, 84);
    listOfPlayers[p4.getName()] = &p4;
    Player p5("Alves", 250, screenH/2 + 200, 20, 20, filename, "homeTeam", "E", 86, 70, 79, 83, 76, 68, 83);
    listOfPlayers[p5.getName()] = &p5;
    Player p6("Iniesta", 400 + 185, screenH/2 - 100 - 63, 20, 20, filename, "homeTeam", "E", 75, 72, 89, 91, 59, 63, 89);
    listOfPlayers[p6.getName()] = &p6;
    Player p7("Rakitic", 400 + 185, screenH/2 + 163, 20, 20, filename, "homeTeam", "NW", 69, 82, 87, 81, 55, 67, 83);
    listOfPlayers[p7.getName()] = &p7;
    Player p8("Busquets",screenW/2, screenH/2, 20, 20, filename, "homeTeam", "E", 56, 59, 78, 75, 81, 80, 85);
    listOfPlayers[p8.getName()] = &p8;
    Player p9("Neymar", ( (1105 - 641)/2) + 641 - 45 , ((350 - 20) / 2) + 20, 20, 20, filename, "homeTeam", "E", 90, 80, 72, 92, 30, 58, 86);
    listOfPlayers[p9.getName()] = &p9;
    Player p10("Messi", ((1105 - 681)/2) + 681, ((515 - 185) / 2) + 185, 20, 20, filename, "homeTeam", "N", 93, 89, 86, 96, 27, 62, 93);
    listOfPlayers[p10.getName()] = &p10;
    Player p11("Suarez", ( (1105 - 641)/2) + 641 - 45 , ((350 - 20) / 2) + 340, 20, 20, filename, "homeTeam", "W", 83, 87, 79, 88, 42, 79, 89);
    listOfPlayers[p11.getName()] = &p11;
    Team homeTeam(listOfPlayers);
    
    filename = "images/madridPlayer.tga";
    
    map <string, Player *> listOfPlayers2;
    Player p21("Casillas", screenW - 51, screenH/2, 20, 20, filename, "awayTeam", "W", 0, 0, 0, 0, 0, 0, 0);
    listOfPlayers2[p21.getName()] = &p21;
    Player p22("Ramos", screenW - 258, screenH/2 + 100 - 45 + 15  , 20, 20, filename, "awayTeam", "W", 79, 60, 71, 66, 87, 82, 87);
    listOfPlayers2[p22.getName()] = &p22;
    Player p23("Marcelo", screenW - 258, screenH/2 + 200, 20, 20, filename, "awayTeam", "W", 81, 67, 78, 84, 77, 79, 82);
    listOfPlayers2[p23.getName()] = &p23;
    Player p24("Pepe", screenW - 258, screenH/2 - 100 + 45 - 15, 20, 20, filename, "awayTeam", "W", 73, 50, 58, 59, 84, 83, 83);
    listOfPlayers2[p24.getName()] = &p24;
    Player p25("Carvajal", screenW - 258, screenH/2 - 200, 20, 20, filename, "awayTeam", "W", 83, 40, 73, 78, 76, 82, 79);
    listOfPlayers2[p25.getName()] = &p25;
    Player p26("Kroos", screenW/2  - 25 , screenH/2 - 160, 20, 20, filename, "awayTeam", "W", 58, 81, 89, 84, 58, 69, 85);
    listOfPlayers2[p26.getName()] = &p26;
    Player p27("Modric", screenW/2 - 25 , screenH/2 + 160, 20, 20, filename, "awayTeam", "W", 76, 74, 85, 89, 71, 70, 87);
    listOfPlayers2[p27.getName()] = &p27;
    Player p28("Rodriguez", 700 , screenH/2, 20, 20, filename, "awayTeam", "W", 80, 80, 84, 85, 40, 72, 86);
    listOfPlayers2[p28.getName()] = &p28;
    Player p29("Benzema", screenW/2 - 363 + 30, screenH/2, 20, 20, filename, "awayTeam", "NW", 84, 84, 75, 82, 30, 74, 85);
    listOfPlayers2[p29.getName()] = &p29;
    Player p210("Ronaldo", screenW/2 - 265, screenH/2 + 180, 20, 20, filename, "awayTeam", "E", 93, 93, 81, 91, 32, 79, 92);
    listOfPlayers2[p210.getName()] = &p210;
    Player p211("Bale", screenW/2 - 265, screenH/2 - 180, 20, 20, filename, "awayTeam", "E", 94, 83, 83, 84, 63, 81, 87);
    listOfPlayers2[p211.getName()] = &p211;
    Team awayTeam(listOfPlayers2);
    
    Ball ball(100 , 100, 10, 8, "images/ball 2.tga");
   
    //good one:
    //Ball ball(screenW/2 - 12 , screenH/2 - 13, 10, 8, "images/ball 2.tga");
    
    Layout layout(&homeTeam, &awayTeam, &ball);
     layout.initialSetUp433();
    
    layout.hasBall(&p2);
    
    
    
    int testInt = 0;
    int s = -1;
    //testInt = testInt + 0.5;
    bool booltest = false;
    cout <<  "test int: " << booltest << endl;
    
    //cin >> testInt;
    //EventHandling.cpp
    initEventQueue();
    //set up textures and game
    GLuint fieldTex = glTexImageTGAFile("images/soccer.tga");
    
    GamePlay gamePlay(&layout, fieldTex);
    
    bool playing = true;
    
    
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
    
    //gamePlay.setUpThreads();
    
    int wait;
    //cout << "input something to continue " << endl;
    //cin >> wait;
    
    
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
        
        
        gamePlay.NextMove();
        gamePlay.move();
        
        //quit = true;
        //cout << "jfdkjfdljfsllsfjls" << endl;
        
        
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