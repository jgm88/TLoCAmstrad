#ifndef _GAME_H
#define _GAME_H

#include "world.h"

extern unsigned char life;
extern unsigned char keys;
extern unsigned char endGame;

void deductLife(Tplayer *);
void addLife();
void initGame();
void pickUpKey();
void doSound(unsigned char, unsigned char);
void instructions();
void endMusic();
void reset();
void gameOver();
void credits();
void game();
// void alertEnemies(vector2*);

#endif