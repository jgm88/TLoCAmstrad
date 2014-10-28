#ifndef _ENEMY_H
#define _ENEMY_H

#include "world.h"
#include "pathfinding.h"

#define MAXTIMESTUNNED 10
#define MAXTIMESEARCH 3
#define ENEMYSPEED 11

extern void (*moveCone[4])(Tenemy*);

void coneUp(Tenemy*);
void coneDown(Tenemy*);
void coneRight(Tenemy*);
void coneLeft(Tenemy*);

void cleanCone(Tcone*);

void drawCone(Tcone*,unsigned char);
void updateCone(Tcone*);
unsigned char detectPlayer(unsigned char, Tenemy*,unsigned char*);

void initializeEnemy(Tenemy* enemy, vector2 *patrolTpoints[11], unsigned char cx, unsigned char cy, unsigned char ox, unsigned char oy, vector2 *anchor, unsigned char anchorDistance);
void enemyAI(Tenemy*, Tplayer*);
void patrol(Tenemy*);
void follow(Tenemy*,unsigned char, unsigned char);
void attack(Tenemy*,Tplayer*);
void search(Tenemy*);


unsigned char inRange(Tenemy*, Tplayer*);
void distance(vector2*,vector2*,Tenemy*);
unsigned char move(Tenemy *,vector2 *);

void stunned(Tenemy*);
void getStunned(Tenemy *enemy);

void initWayPoints();

#endif
