//
//  Dot.h
//  Soccer1
//
//  Created by Gibran Morales on 2/11/15.
//  Copyright (c) 2015 Gibran Morales. All rights reserved.
//

#ifndef Soccer1_Dot_h
#define Soccer1_Dot_h
//The dot that will move around on the screen
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <GL/glew.h>
#include <stdio.h>

class Dot
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    
    //Maximum axis velocity of the dot
    static const int DOT_VEL = 10;
    
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    
    //Initializes the variables
    Dot();
    
    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the dot
    void move();
    
    //Shows the dot on the screen
    void render();
    
private:
    //The X and Y offsets of the dot
    int mPosX, mPosY;
    
    //The velocity of the dot
    int mVelX, mVelY;
};



#endif
