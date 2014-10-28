#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include "enemy.h"

#define MAXWAYPOINTS 9

extern TwayPoint* vectorWayPoints[MAXWAYPOINTS];
void pathfinding(Tenemy*);
void initWayPoints();
void doPathfinding(Tenemy* ,vector2*);

#endif