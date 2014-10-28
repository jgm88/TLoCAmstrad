#ifndef _WORLD_H
#define _WORLD_H

#include "sprites.h"
#include "keyboard.h"
#include "videomap.h"
#include "tiles.h"
#include "structs.h"
#include "game.h"

extern const unsigned char TYPEGROUND;
extern const unsigned char TYPEBRICK;
extern const unsigned char TYPEKEY;
extern const unsigned char TYPEPLAYER;
extern const unsigned char TYPEFIRE;
extern const unsigned char TYPEENEMY1;
extern const unsigned char TYPEENEMY2;
extern const unsigned char TYPEEXIT;

/*El mundo es de 20 x 25*/
extern unsigned char worldMatrix[25][20];
extern unsigned char* vTiles[40];

void drawMap();
void drawSP(Tsprite*);
void loadLevel();
unsigned char canMoveWorld(unsigned char, unsigned char);
unsigned char updatePosition(unsigned char, unsigned char, Tsprite*);
unsigned char getPosWorld(unsigned char x, unsigned char y);

//Scenes
void instructionScene();
void openDoor();

void gameOverScene();
void creditsScene();
void winScene();

#endif