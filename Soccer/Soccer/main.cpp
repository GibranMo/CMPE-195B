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
#include "Operations.h"
#include "EventHandling.h"

using namespace std;

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
    //Operations.cpp
	setUpTextures();
	setUp();

	
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

		//Start the game
		if (kbState[SDL_SCANCODE_SPACE]){
			playing = true;
			help = false;
		}
        
		if (kbState[SDL_SCANCODE_H]){
			help = true;
		}
		if (player1.lives == 0 || player2.lives == 0){
			playing = false;
			if (kbState[SDL_SCANCODE_Y]){
				setUp();
				playing = true;
			}
			if (kbState[SDL_SCANCODE_N]){
				quit = 1;
			}
		}


		// throttle framerate
		int tick = SDL_GetTicks();
		do {
			SDL_Delay(max(0, ticksPerFrame - (tick - prevTick)));//changed from MAX
			tick = SDL_GetTicks();

		} while (ticksPerFrame - (tick - prevTick) > 0);
		prevTick = tick;

        
		// Game logic

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		//DRAWING
		drawBackground(playing);

		if (playing){
			glDrawSprite(player1.tex, player1.x, player1.y, player1.w, player1.h);
			glDrawSprite(player2.tex, player2.x, player2.y, player2.w, player2.h);
			glDrawSprite(ball.tex, ball.x, ball.y, ball.w, ball.h);
		}

		//PHYSICS
		char player1Dir = 'n';
		while (tick > prevPhysicsTick + ticksPerPhysics) {
			//update physics

			if (playing){
				//ball collision with ceiling and floor
				Event ev;
				ev.actor1 = &ball;
				if ((ball.y + ball.velY) >= (screenH - ball.h) || ball.y + ball.velY <= 0){
					ev.et = ET_BALL_TOPBOTTOM_COLLISION;
					queueEvent(&ev);
				}
				//ball collision with walls
				if (ball.x + ball.w < 0 || ball.x > screenW){
					ev.et = ET_BALL_WALL_COLLISION;
					if (ball.x > screenW)
						ev.actor2 = &player2;
					else{
						ev.actor2 = &player1;
					}

					queueEvent(&ev);
					setUp();
				}
				//ball collision with p1 & p2
				int collisionDirP1 = collides(&ball, &player1);
				int collisionDirP2 = collides(&ball, &player2);
				if (collisionDirP1 == 1 || collisionDirP2 == 1){
					ev.et = ET_BALLPLAYER_SIDE_COLLISION;
					queueEvent(&ev);
				}
				else if (collisionDirP1 == 2 || collisionDirP2 == 2){
					ev.et = ET_BALLPLAYER_TOP_COLLISION;
					queueEvent(&ev);
				}
				//Player1 movement
				if (kbState[SDL_SCANCODE_UP]) 
					player1Dir = 'u';
				if (kbState[SDL_SCANCODE_DOWN]) 
					player1Dir = 'd';
				if (kbState[SDL_SCANCODE_LEFT]) 
					player1Dir = 'l';
				if (kbState[SDL_SCANCODE_RIGHT]) 
					player1Dir = 'r';
				
			}
			prevPhysicsTick += ticksPerPhysics;
		}

		//EVENT HANLDLING
		updateEventQueue();

		//MOVEMENT and ANIMATION
		if (playing){
			ball.x += ball.velX;
			ball.y += ball.velY;
			//PLAYER
			if (player1Dir != 'n'){
				animPlayer(&player1, player1Dir, timeSinceLastFrame);
			}

			//PC MOVEMENT
			if (ball.velX < 0 && ball.velY > 0 && ball.y <= player2.y && player2.y + player2.velY + player2.h < screenH)
				animPlayer(&player2, 'd', timeSinceLastFrame);
			if (ball.velX < 0 && ball.velY < 0 && ball.y >= player2.y &&  player2.y + player2.velY > 0)
				animPlayer(&player2, 'u', timeSinceLastFrame);
			if (ball.velX < 0 && ball.velY > 0 && ball.y >= player2.y && player2.y + player2.velY + player2.h < screenH)
				animPlayer(&player2, 'd', timeSinceLastFrame);
			if (ball.velX < 0 && ball.velY < 0 && ball.y <= player2.y &&  player2.y + player2.velY > 0)
				animPlayer(&player2, 'u', timeSinceLastFrame);

			if (ball.velX > 0 && ball.velY > 0 && ball.y <= player2.y && player2.y + player2.velY + player2.h < screenH)
				animPlayer(&player2, 'd', timeSinceLastFrame);
			if (ball.velX > 0 && ball.velY < 0 && ball.y >= player2.y &&  player2.y + player2.velY > 0)
				animPlayer(&player2, 'u', timeSinceLastFrame);
			if (ball.velX > 0 && ball.velY > 0 && ball.y >= player2.y && player2.y + player2.velY + player2.h < screenH)
				animPlayer(&player2, 'd', timeSinceLastFrame);
			if (ball.velX > 0 && ball.velY < 0 && ball.y <= player2.y &&  player2.y + player2.velY > 0)
				animPlayer(&player2, 'u', timeSinceLastFrame);

		}
		//end game logic

		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
	return 0;
}