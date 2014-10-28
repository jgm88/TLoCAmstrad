#include "pathfinding.h"
#include "enemy.h"
#include <stdio.h>


TwayPoint* vectorWayPoints[MAXWAYPOINTS];
TwayPoint wp1,wp2,wp3,wp4,wp5,wp6,wp7,wp8, wp9;

void initWayPoints(){

	 wp1.point2D.x=15; wp1.point2D.y=9; // 1
	 wp2.point2D.x=9; wp2.point2D.y=8; // 2
	 wp3.point2D.x=2; wp3.point2D.y=11; // 3
	 wp4.point2D.x=3; wp4.point2D.y=17; // 4
	 wp5.point2D.x=7; wp5.point2D.y=19; //5
	 wp6.point2D.x=11; wp6.point2D.y=15; //6
	 wp7.point2D.x=16; wp7.point2D.y=15; //7
	 wp8.point2D.x=16; wp8.point2D.y=18; //8
	 wp9.point2D.x=13; wp9.point2D.y=22; //9

	 wp1.prev= &wp1; wp1.next=&wp2; wp1.number=1;
	 wp2.prev= &wp1; wp2.next=&wp3; wp2.number=2;
	 wp3.prev= &wp2; wp3.next=&wp4; wp3.number=3;
	 wp4.prev= &wp3; wp4.next=&wp5; wp4.number=4;
	 wp5.prev= &wp4; wp5.next=&wp6; wp5.number=5;
	 wp6.prev= &wp5; wp6.next=&wp7; wp6.number=6;
	 wp7.prev= &wp6; wp7.next=&wp8; wp7.number=7;
	 wp8.prev= &wp7; wp8.next=&wp9; wp8.number=8;
	 wp9.prev= &wp8; wp9.next=&wp9; wp9.number=9;

	 vectorWayPoints[0]=&wp1;
	 vectorWayPoints[1]=&wp2;
	 vectorWayPoints[2]=&wp3;
	 vectorWayPoints[3]=&wp4;
	 vectorWayPoints[4]=&wp5;
	 vectorWayPoints[5]=&wp6;
	 vectorWayPoints[6]=&wp7;
	 vectorWayPoints[7]=&wp8;
	 vectorWayPoints[8]=&wp9;
}

unsigned char abs(char n) { return n < 0 ? -n : n; }

unsigned char manhattanDistance(vector2* origin, vector2* destiny)
{
	char x = destiny->x - origin->x;
	char y = destiny->y - origin->y;

	return abs(x) + abs(y);
}
void calculatePathFinding(Tenemy* enemy ,vector2* destiny)
{
	unsigned char i=0, lowDistE=255,lowDistO=255,lowDist;
	vector2 enemyPosition={enemy->base.cx, enemy->base.cy};

	for(;i<MAXWAYPOINTS; ++i)
	{
		lowDist = manhattanDistance(&enemyPosition ,&vectorWayPoints[i]->point2D);
		if(lowDist<lowDistE)
		{
			lowDistE = lowDist;
			enemy->nearEnemy2 = enemy->nearEnemy;
			enemy->nearEnemy = vectorWayPoints[i];
		}
		lowDist = manhattanDistance(destiny ,&vectorWayPoints[i]->point2D);
		if(lowDist<lowDistO)
		{
			lowDistO = lowDist;
			enemy->nearDestiny = vectorWayPoints[i];
		}
	}
	if(i==0){		
		enemy->nearEnemy2 = vectorWayPoints[i];
	}
}
void doPathfinding(Tenemy* enemy ,vector2* destiny)
{
	cleanCone(enemy->coneDir);
	
	calculatePathFinding(enemy,destiny);
	//cambia estado pathfinding y comienzo el camino	
	enemy->currentState=4;
	// printf("Escojo W = %d\n", enemy->nearEnemy->number);
}


/// Recibe el enemigo y el punto a donde se quiere dirigir
void pathfinding(Tenemy* enemy){	

	enemy->canMovePathF = move(enemy, &enemy->nearEnemy->point2D);	
	if(enemy->canMovePathF == 9){
						
		//Si el destino es anterior construyo con prev
		if(enemy->nearDestiny->number < enemy->nearEnemy->number){
			enemy->nearEnemy = enemy->nearEnemy->prev;
			
		}
		//Si el destino es posterior construyo con next
		else if(enemy->nearDestiny->number > enemy->nearEnemy->number){
			enemy->nearEnemy = enemy->nearEnemy->next;
		}
		//Si ya ha llegado al WayPoint destino
		else if(enemy->nearDestiny->number == enemy->nearEnemy->number){
			//Vuelta al anchor
			if(enemy->pathObjective==0){
				enemy->pointPatrol=0;
				enemy->currentState = 0;	
			}	
			//Va a por player
			else if(enemy->pathObjective==1){
				enemy->pointPatrol=0;
				enemy->pathObjective=0;
				enemy->currentState = 1;
			}				
		}
	}
	// si se encuentra un muro haciendo PathFinding escoge otro nodo
	else if(enemy->canMovePathF == 0){			
		enemy->nearEnemy = enemy->nearEnemy2;
	}
}


