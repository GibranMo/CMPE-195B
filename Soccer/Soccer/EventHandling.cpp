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
#include "EventHandling.h"
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
		case ET_BALL_TOPBOTTOM_COLLISION:
			ev->actor1->velY *= -1;
			break;
		case ET_BALL_WALL_COLLISION:
			ev->actor2->lives--;
			break;
		case ET_BALLPLAYER_TOP_COLLISION:
			ev->actor1->velY *= -1;
			if (ev->actor1->velY < 0 && ev->actor1->velY > -10)
				ev->actor1->velY -= 0.6;
			else if(ev->actor1->velY < 10)
				ev->actor1->velY += 0.6;
			break;
		case ET_BALLPLAYER_SIDE_COLLISION:
			ev->actor1->velX *= -1;
			if (ev->actor1->velX < 0 && ev->actor1->velX > -10)
				ev->actor1->velX -= 0.6;
			else if (ev->actor1->velX < 10)
				ev->actor1->velX += 0.6;
			break;
	}
}

void updateEventQueue(void){
	for (int i = 0; i < eventQueue.size(); ++i){
		handleEvent(&eventQueue[i]);
	}
	eventQueue.clear();
}

