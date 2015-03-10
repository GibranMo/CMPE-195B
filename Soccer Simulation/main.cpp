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

using namespace std;

int screenW = 700;
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
    
    //EventHandling.cpp
    initEventQueue();
    //set up textures and game

    GLuint fieldTex;

    int outWidth = 0;
    int outHeight = 0;
    fieldTex = glTexImageTGAFile("images/soccer.tga", &outWidth, &outHeight);

    
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
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        if (playing){
            // start the game draw graphics (players & ball & gameplay background)
            glDrawSprite(fieldTex, 0, 0, 700, 500);
            glDrawSprite2(glTexImageTGAFile("images/1.tga", 0, 0), screenW/2, screenH/2, 100, 100);
        }
        
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
        
        //MOVEMENT and ANIMATION
        if (playing){
            //Ball movement & PLAYER movements, update positions

            
        }
        
        //end game logic
        
        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}