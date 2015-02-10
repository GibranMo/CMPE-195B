#define _CRT_SECURE_NO_WARNINGS
#include<SDL2/SDL.h>
#include<GL/glew.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <math.h>  
#include "Operations.h"
using namespace std;

//Background def
int tileLength = 32;
int outWidth = 0;
int outHeight = 0;

//world def
int const screenW = 896;
int const screenH = 640;
bool help = false;

//Main character def
ActorData player1;
ActorData player2;
ActorData ball;

GLuint fieldTex;
GLuint startBackTex;
GLuint winBackTex;
GLuint loseBackTex;
GLuint helpBackTex;
GLuint livesTex;

void setUpTextures(){

	startBackTex = glTexImageTGAFile("back/start.tga", &outWidth, &outHeight);
	winBackTex = glTexImageTGAFile("back/win.tga", &outWidth, &outHeight);
	loseBackTex = glTexImageTGAFile("back/lose.tga", &outWidth, &outHeight);
	helpBackTex = glTexImageTGAFile("back/help.tga", &outWidth, &outHeight);
	livesTex = glTexImageTGAFile("dbz/3.tga", &outWidth, &outHeight);
    fieldTex = glTexImageTGAFile("back/soccer.tga", &outWidth, &outHeight);

    player1.frameTime = 60;
    player2.frameTime = 60;
    ball.frameTime = 60;
    ball.tex = glTexImageTGAFile("back/ball.tga", &outWidth, &outHeight);
    player1.tex = glTexImageTGAFile("dbz/1.tga", 0, 0);
    player2.tex = glTexImageTGAFile("dbz/2.tga", 0, 0);

}

void setData(ActorData* data, int x, int y, int width, int height, int lives, int velX, int velY, int isPLaying) {
	data->x = x;
	data->y = y;
	data->w = width;
	data->h = height;
	data->curFrame = 0;
	data->timeToNextFrame = 0;
	data->lives = lives;
	data->velX = velX;
	data->velY = velY;

}

void drawBackground(bool playing){
	int x = 0;
	int y = 0;
	if (!playing){
		if (help)
			glDrawSprite(helpBackTex, x, y, screenW, screenH);
		else if (player1.lives == 3 && player2.lives == 3)
			glDrawSprite(startBackTex, x, y, screenW, screenH);
		else if (player2.lives == 0)
			glDrawSprite(winBackTex, x, y, screenW, screenH);
		else if (player1.lives == 0)
			glDrawSprite(loseBackTex, x, y, screenW, screenH);

	}

	else {
		glDrawSprite(fieldTex, x, y, screenW, screenH);
        
		for (int i = 0; i < player1.lives; i++){
			glDrawSprite(livesTex, 0 + (i * 30) , 0, 25, 25);
		}
		for (int i = 0; i < player2.lives; i++){
			glDrawSprite(livesTex, screenW - 25  - (i * 35), 0, 25, 25);
		}
	}
}

void setUp(){
	int w = 35;
	int h = 100;
	int x = 0;
	int y = (screenH / 2) - (h / 2);
	int velX = 8;
	int velY = 8;
	bool isPlaying = true;
    int lives = 3;
	if (player1.lives < lives && player1.lives > 0)
        lives = player1.lives;
    setData(&player1, x, y, w, h, lives, velX, velY, isPlaying);
	x = screenW - w;
    if (player2.lives < lives && player2.lives > 0)
        lives = player2.lives;
	setData(&player2, x, y, w, h, lives, velX, velY, isPlaying);
	w = 20;
	h = 20;
	isPlaying = false;
	x = screenW / 2;
	y = screenH / 2;
	velX = 2;
	velY = 2;
	isPlaying = true;
	setData(&ball, x, y, w, h, lives, velX, velY, isPlaying);


}

//0 = no collisoion. 1 = side collision. 2 = top/bottom collision
int collides(ActorData* object1, ActorData* object2) {
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;
	left1 = object1->x;
	left2 = object2->x;
	right1 = object1->x + object1->w;
	right2 = object2->x + object2->w;
	top1 = object1->y;
	top2 = object2->y;
	bottom1 = object1->y + object1->h;
	bottom2 = object2->y + object2->h;
	//moving right
	if (object1->velX > 0){
		//if object2 is to the right
		if ((right1 - left2 <= object2->w / 2) && (right1 + object1->velX >= left2 && left1 <= left2) &&
			((top1 + object1->velY <= bottom2 && top1 + object1->velY >= top2) || 
			(bottom1 + object1->velY >= top2 && bottom1 + object1->velY <= bottom2)))
			return 1;
	}
	//moving left
	if (object1->velX < 0){
		//if obect2 is to the left
		if ((right2 - left1 <= object2->w / 2) && (left1 + object1->velX <= right2 && right1 >= right2) &&
			((top1 + object1->velY <= bottom2 && top1 + object1->velY >= top2) || 
			(bottom1 + object1->velY >= top2 && bottom1 + object1->velY <= bottom2)))
			return 1;
	}
	//moving up
	if (object1->velY < 0){
		if ((top1 + object1->velY <= bottom2 && bottom1 >= bottom2) &&
			((left1 + object1->velX <= right2 && left1 + object1->velX >= left2) || 
			(right1 + object1->velX >= left2 && right1 + object1->velX <= right2)))
			return 2;
	}
	//moving down
	if (object1->velY > 0){
		if ((bottom1 + object1->velY >= top2 && top1 <= top2) &&
			((left1 + object1->velX <= right2 && left1 + object1->velX >= left2) || 
			(right1 + object1->velX >= left2 && right1 + object1->velX <= right2)))
			return 2;
	}
	return 0;
}

// Update the main character frame and position
void animPlayer(ActorData* data, char direction, int dt) {
	data->timeToNextFrame -= dt;
	if (data->timeToNextFrame > 0)
		return;
    else if (direction == 'u') {
        if (data->y > 0)
            data->y -= data->velY;
        else
            data->y = 0;
    }
    else if (direction == 'd') {
        if (data->y < screenH - data->h)
            data->y += data->velY;
        else
            data->y = screenH - data->h;
    }
    else if (direction == 'l') {
        if (data->x > 0)
            data->x -= data->velX;
        else
            data->x = 0;
    }
    else if (direction == 'r') {
        if (data->x < (screenW - data->w))
            data->x += data->velX;
        else
            data->x = screenW - data->w;	
    }
	data->timeToNextFrame = data->frameTime;
}