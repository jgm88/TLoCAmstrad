#include "enemy2.h"

void search2(Tenemy* enemy)
{
	drawSP(&enemy->base);
	
	moveCone[enemy->lookAt](enemy);

	++enemy->searchDelay;
	if(enemy->searchDelay> MAXTIMESEARCH2)
	{
		cleanCone(enemy->coneDir);
		drawSP(&enemy->base);
		enemy->searchDelay=0;
		enemy->lookAt+=enemy->coneRestrictions;
		if(enemy->lookAt>3)
		{
			enemy->lookAt=0;			
		}
	}
}
void alert(Tenemy* enemy,unsigned char x, unsigned char y){
	vector2 destiny = {x,y};
	enemy->enemyHelper->pathObjective=1;
	doPathfinding(enemy->enemyHelper, &destiny);
	enemy->waitTimer = 0;
	enemy->currentState = 2;
	doSound(1,1);
	doSound(1,3);
}
void wait(Tenemy* enemy){
	++enemy->waitTimer;	
	if(enemy->waitTimer > MAXWAITTIME)
		enemy->currentState = 0;
}
void enemyAI2(Tenemy *enemy, Tplayer *player)
{

	switch(enemy->currentState)
	{
		case 0: search2(enemy);
			break;
		case 1: alert(enemy,player->base.cx,player->base.cy);
			break;
		case 2: wait(enemy);
			break;
	}
}

