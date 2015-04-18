//
//  EventHandler.cpp
//  Soccer Simulation
//
//  Created by Carlos Toledo on 2/10/15.
//  Copyright (c) 2015 Carlos Toledo. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <ctime>
#include "EventHandler.h"
using namespace std;

vector<Event> eventQueue;

void initEventQueue(void){
    eventQueue.reserve(16);
    
}

void queueEvent(Event* ev){
    eventQueue.push_back(*ev);
}

void handleEvent(Event* ev){
    switch (ev->et) {
            //		case ET_BALL_TOPBOTTOM_COLLISION:
            //			ev->actor1->velY *= -1;
            //			break;
    }
}

void updateEventQueue(void){
    for (int i = 0; i < eventQueue.size(); ++i){
        handleEvent(&eventQueue[i]);
    }
    eventQueue.clear();
}

