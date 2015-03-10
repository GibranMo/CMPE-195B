
#ifndef Operations_H

#define Operations_H

#include "Definitions.h"
#include "DrawUtils.h"


//world def
extern int const screenW;
extern int const screenH;

extern bool help;

//Main character def
extern ActorData player1;
extern ActorData player2;
extern ActorData ball;
extern ActorData someName;

void setUpTextures();

void drawBackground(bool playing);

void setUp();

void resetLevel();

bool backCollision(ActorData* data, char dir);

int collides(ActorData* object1, ActorData* object2);

void animPlayer(ActorData* data, char direction, int dt);

#endif