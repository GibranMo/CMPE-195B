
#ifndef Definitions_H
#define Definitions_H

#include <vector>
#include<SDL2/SDL.h>
#include<GL/glew.h>
using namespace std;

//animation


// Runtime state for an animation
struct ActorData {
	int curFrame;
	float timeToNextFrame;
	int x;
	int y;
	int w;
	int h;
	int lives;
	float velX;
	float velY;
	int isPlaying;
    float frameTime;
    GLuint tex;
};

enum Event_Type{
    ET_BALL_TOPBOTTOM_COLLISION,
    ET_BALL_WALL_COLLISION,
    ET_BALLPLAYER_TOP_COLLISION,
    ET_BALLPLAYER_SIDE_COLLISION,
};

struct Event{
    Event_Type et;
    ActorData* actor1;
    ActorData* actor2;
};


#endif