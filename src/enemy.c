#include "enemy.h"

void cleanCone(Tcone* cone)
{
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[0].cx,cone[0].cy)],getPosVideo(cone[0].cx,cone[0].cy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[1].cx,cone[1].cy)],getPosVideo(cone[1].cx,cone[1].cy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[2].cx,cone[2].cy)],getPosVideo(cone[2].cx,cone[2].cy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[3].cx,cone[3].cy)],getPosVideo(cone[3].cx,cone[3].cy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[4].cx,cone[4].cy)],getPosVideo(cone[4].cx,cone[4].cy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[5].cx,cone[5].cy)],getPosVideo(cone[5].cx,cone[5].cy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[6].cx,cone[6].cy)],getPosVideo(cone[6].cx,cone[6].cy));

	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[0].ox,cone[0].oy)],getPosVideo(cone[0].ox,cone[0].oy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[1].ox,cone[1].oy)],getPosVideo(cone[1].ox,cone[1].oy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[2].ox,cone[2].oy)],getPosVideo(cone[2].ox,cone[2].oy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[3].ox,cone[3].oy)],getPosVideo(cone[3].ox,cone[3].oy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[4].ox,cone[4].oy)],getPosVideo(cone[4].ox,cone[4].oy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[5].ox,cone[5].oy)],getPosVideo(cone[5].ox,cone[5].oy));
	cpct_drawSprite4x8_aligned(vTiles[getPosWorld(cone[6].ox,cone[6].oy)],getPosVideo(cone[6].ox,cone[6].oy));
}
unsigned char detectPlayer(unsigned char blockTipe, Tenemy* enemy, unsigned char *detectPlayer)
{
	if(blockTipe==TYPEPLAYER)
	{
		(*detectPlayer)=1;
		if(enemy->currentState!=3)
		{
			enemy->currentState=1;
		}
		cleanCone(enemy->coneDir);
	}
	return blockTipe;	
}

void drawCone(Tcone* cone,unsigned char currentBloc)
{
	if(currentBloc==0)
	{
		cpct_drawSprite4x8_aligned(spGround,getPosVideo(cone[0].ox,cone[0].oy));
		cpct_drawSprite4x8_aligned(spVision,getPosVideo(cone[0].cx,cone[0].cy));
	}
	else
	{
		cpct_drawSprite4x8_aligned(spGround,getPosVideo(cone[currentBloc].ox,cone[currentBloc].oy));
		cpct_drawSprite4x8_aligned(spVision,getPosVideo(cone[currentBloc].cx,cone[currentBloc].cy));
		drawCone(cone,--currentBloc);
	}
}
void updateCone(Tcone* cone)
{
	cone[0].ox=cone[0].cx;
	cone[0].oy=cone[0].cy;
	cone[1].ox=cone[1].cx;
	cone[1].oy=cone[1].cy;
	cone[2].ox=cone[2].cx;
	cone[2].oy=cone[2].cy;
	cone[3].ox=cone[3].cx;
	cone[3].oy=cone[3].cy;
	cone[4].ox=cone[4].cx;
	cone[4].oy=cone[4].cy;
	cone[5].ox=cone[5].cx;
	cone[5].oy=cone[5].cy;
	cone[6].ox=cone[6].cx;
	cone[6].oy=cone[6].cy;
}

void coneRight(Tenemy *enemy)
{
	unsigned char tempX, tempY,isdetected=0;
	
	tempX= enemy->base.cx+1;
	tempY= enemy->base.cy;
	/// 1º columna
	if(detectPlayer(getPosWorld(tempX,tempY),enemy,&isdetected)==1)
	{	//
		// primer cuadrado E X
		// igualamos todos los cuadrados del cono a la posicion del 1º
		enemy->coneDir[1].cx=enemy->coneDir[2].cx=enemy->coneDir[3].cx=enemy->coneDir[4].cx=enemy->coneDir[5].cx=enemy->coneDir[6].cx=enemy->coneDir[0].cx= tempX;
		enemy->coneDir[1].cy=enemy->coneDir[2].cy=enemy->coneDir[3].cy=enemy->coneDir[4].cy=enemy->coneDir[5].cy=enemy->coneDir[6].cy=enemy->coneDir[0].cy= tempY;
		
		++tempX;
		if(detectPlayer(getPosWorld(tempX,tempY),enemy,&isdetected)==1)
		{
			///
			///	cuadrado central E X X
			/// incrementamos el los dos bloques que estan en linea recta de forma q los dos quedan en el mismo lugar
			++enemy->coneDir[5].cx;
			++enemy->coneDir[2].cx;
			
			if(detectPlayer(getPosWorld(tempX+1,tempY),enemy,&isdetected)==1 )
			{
				///
				///	cuadrado central E X X X
				/// finalmente avanzamos el bloque que esta en el extremo del cono
				++enemy->coneDir[5].cx;
				
			}
			
		}
		if(detectPlayer(getPosWorld(tempX,tempY-1),enemy,&isdetected)==1)
		{
		//						  X
		//	cuadrado superiro E X X X
		//	colocamos el bloque del cono arriba de la 2º columna e igualamos el siguiente cuadrado a esta posicion
			enemy->coneDir[4].cx=++enemy->coneDir[1].cx;
			enemy->coneDir[4].cy=--enemy->coneDir[1].cy; // arriba
			
			if( detectPlayer(getPosWorld(tempX+1,enemy->coneDir[1].cy),enemy,&isdetected)==1)
			{
				//   					 X X
				// cuadrado superior E X X X
				// finalmente avanza el ultimo cuadrado
				
				++enemy->coneDir[4].cx;
			}
		}
		
		if(detectPlayer(getPosWorld(tempX,tempY+1),enemy,&isdetected)==1)
		{
				//						 X X
				// cuadrado inferior E X X X
				//						 X
				// igual que el caso anterior solo q poniendo el cuadro abajo
				enemy->coneDir[6].cx=++enemy->coneDir[3].cx;
				enemy->coneDir[6].cy=++enemy->coneDir[3].cy; // abajo
				
				if(detectPlayer(getPosWorld(tempX+1,enemy->coneDir[3].cy),enemy,&isdetected)==1)
				{
					//						 X X
					// cuadrado inferior E X X X
					//	   					 X X
					// igual que el caso anterior pero poniendo el cuadro abajo
					++enemy->coneDir[6].cx;
					
				}
		}
	}

	if(isdetected==0)
	{
		drawCone(enemy->coneDir,6);		
	}
	updateCone(enemy->coneDir);
		
}
void coneUp(Tenemy *enemy)
{
	unsigned char tempX, tempY,isdetected=0;
	
	tempX= enemy->base.cx;
	tempY= enemy->base.cy-1;
	/// 1º columna
	if(detectPlayer(getPosWorld(tempX,tempY),enemy,&isdetected)==1)
	{	//
		// primer cuadrado E X
		// igualamos todos los cuadrados del cono a la posicion del 1º
		enemy->coneDir[1].cx=enemy->coneDir[2].cx=enemy->coneDir[3].cx=enemy->coneDir[4].cx=enemy->coneDir[5].cx=enemy->coneDir[6].cx=enemy->coneDir[0].cx= tempX;
		enemy->coneDir[1].cy=enemy->coneDir[2].cy=enemy->coneDir[3].cy=enemy->coneDir[4].cy=enemy->coneDir[5].cy=enemy->coneDir[6].cy=enemy->coneDir[0].cy= tempY;
		
		--tempY;
		if(detectPlayer(getPosWorld(tempX,tempY),enemy,&isdetected)==1)
		{
			///
			///	cuadrado central E X X
			/// incrementamos el los dos bloques que estan en linea recta de forma q los dos quedan en el mismo lugar
			--enemy->coneDir[5].cy;
			--enemy->coneDir[2].cy;
			
			if(detectPlayer(getPosWorld(tempX,tempY-1),enemy,&isdetected)==1 )
			{
				///
				///	cuadrado central E X X X
				/// finalmente avanzamos el bloque que esta en el extremo del cono
				--enemy->coneDir[5].cy;
				
			}
			
		}
		if(detectPlayer(getPosWorld(tempX-1,tempY),enemy,&isdetected)==1)
		{
		//						  X
		//	cuadrado superiro E X X X
		//	colocamos el bloque del cono arriba de la 2º columna e igualamos el siguiente cuadrado a esta posicion
			enemy->coneDir[4].cy=--enemy->coneDir[1].cy;
			enemy->coneDir[4].cx=--enemy->coneDir[1].cx; // arriba
			
			if(detectPlayer(getPosWorld(enemy->coneDir[1].cx,tempY-1),enemy,&isdetected)==1)
			{
				//   					 X X
				// cuadrado superior E X X X
				// finalmente avanza el ultimo cuadrado
				--enemy->coneDir[4].cy;
				
			}
		}
		
		if(detectPlayer(getPosWorld(tempX+1,tempY),enemy,&isdetected)==1)
		{
			//						 X X
			// cuadrado inferior E X X X
			//						 X
			// igual que el caso anterior solo q poniendo el cuadro abajo
			enemy->coneDir[6].cy=--enemy->coneDir[3].cy;
			enemy->coneDir[6].cx=++enemy->coneDir[3].cx; // abajo
			
			if(detectPlayer(getPosWorld(enemy->coneDir[3].cx,tempY-1),enemy,&isdetected)==1)
			{
				//						 X X
				// cuadrado inferior E X X X
				//	   					 X X
				// igual que el caso anterior pero poniendo el cuadro abajo
				--enemy->coneDir[6].cy;
				
			}
		}
	}

	if (isdetected==0)
 	{
		
		drawCone(enemy->coneDir,6);
	}
	updateCone(enemy->coneDir);
}
void coneDown(Tenemy *enemy)
{
	unsigned char tempX, tempY,isdetected=0;
	
	tempX= enemy->base.cx;
	tempY= enemy->base.cy+1;
	/// 1º columna
	if(detectPlayer(getPosWorld(tempX,tempY),enemy,&isdetected)==1)
	{	//
		// primer cuadrado E X
		// igualamos todos los cuadrados del cono a la posicion del 1º
		enemy->coneDir[1].cx=enemy->coneDir[2].cx=enemy->coneDir[3].cx=enemy->coneDir[4].cx=enemy->coneDir[5].cx=enemy->coneDir[6].cx=enemy->coneDir[0].cx= tempX;
		enemy->coneDir[1].cy=enemy->coneDir[2].cy=enemy->coneDir[3].cy=enemy->coneDir[4].cy=enemy->coneDir[5].cy=enemy->coneDir[6].cy=enemy->coneDir[0].cy= tempY;
		
		++tempY;
		
		if(detectPlayer(getPosWorld(tempX,tempY),enemy,&isdetected)==1)
		{
			///
			///	cuadrado central E X X
			/// incrementamos el los dos bloques que estan en linea recta de forma q los dos quedan en el mismo lugar
			++enemy->coneDir[5].cy;
			++enemy->coneDir[2].cy;
			
			if(detectPlayer(getPosWorld(tempX,tempY+1),enemy,&isdetected)==1 )
			{
				///
				///	cuadrado central E X X X
				/// finalmente avanzamos el bloque que esta en el extremo del cono
				++enemy->coneDir[5].cy;
				
			}
			
		}
		if(detectPlayer(getPosWorld(tempX-1,tempY),enemy,&isdetected)==1)
		{
		//						  X
		//	cuadrado superiro E X X X
		//	colocamos el bloque del cono arriba de la 2º columna e igualamos el siguiente cuadrado a esta posicion
			enemy->coneDir[4].cy=++enemy->coneDir[1].cy;
			enemy->coneDir[4].cx=--enemy->coneDir[1].cx; // arriba
			
			if(detectPlayer(getPosWorld(enemy->coneDir[1].cx,tempY+1),enemy,&isdetected)==1)
			{
				//   					 X X
				// cuadrado superior E X X X
				// finalmente avanza el ultimo cuadrado
				++enemy->coneDir[4].cy;
				
			}
		}
		
		if(detectPlayer(getPosWorld(tempX+1,tempY),enemy,&isdetected)==1)
		{
				//						 X X
				// cuadrado inferior E X X X
				//						 X
				// igual que el caso anterior solo q poniendo el cuadro abajo
				enemy->coneDir[6].cy=++enemy->coneDir[3].cy;
				enemy->coneDir[6].cx=++enemy->coneDir[3].cx; // abajo
				
				if(detectPlayer(getPosWorld(enemy->coneDir[3].cx,tempY+1),enemy,&isdetected)==1)
				{
					//						 X X
					// cuadrado inferior E X X X
					//	   					 X X
					// igual que el caso anterior pero poniendo el cuadro abajo
					++enemy->coneDir[6].cy;
					
				}
		}
	}

	if(isdetected==0)
		drawCone(enemy->coneDir,6);

	updateCone(enemy->coneDir);
}
void coneLeft(Tenemy *enemy)
{
	unsigned char tempX, tempY,isdetected=0;	
	tempX= enemy->base.cx-1;
	tempY= enemy->base.cy;
	/// 1º columna
	if(detectPlayer(getPosWorld(tempX,tempY),enemy,&isdetected)==1)
	{	//
		// primer cuadrado E X
		// igualamos todos los cuadrados del cono a la posicion del 1º
		enemy->coneDir[1].cx=enemy->coneDir[2].cx=enemy->coneDir[3].cx=enemy->coneDir[4].cx=enemy->coneDir[5].cx=enemy->coneDir[6].cx=enemy->coneDir[0].cx= tempX;
		enemy->coneDir[1].cy=enemy->coneDir[2].cy=enemy->coneDir[3].cy=enemy->coneDir[4].cy=enemy->coneDir[5].cy=enemy->coneDir[6].cy=enemy->coneDir[0].cy= tempY;
		
		--tempX;
		if(detectPlayer(getPosWorld(tempX,tempY),enemy,&isdetected)==1)
		{
			///
			///	cuadrado central E X X
			/// incrementamos el los dos bloques que estan en linea recta de forma q los dos quedan en el mismo lugar
			--enemy->coneDir[5].cx;
			--enemy->coneDir[2].cx;
			
			if(detectPlayer(getPosWorld(tempX-1,tempY),enemy,&isdetected)==1 )
			{
				///
				///	cuadrado central E X X X
				/// finalmente avanzamos el bloque que esta en el extremo del cono
				--enemy->coneDir[5].cx;
				
			}
			
		}
		if(detectPlayer(getPosWorld(tempX,tempY-1),enemy,&isdetected)==1)
		{
		//						  X
		//	cuadrado superiro E X X X
		//	colocamos el bloque del cono arriba de la 2º columna e igualamos el siguiente cuadrado a esta posicion
			enemy->coneDir[4].cx=--enemy->coneDir[1].cx;
			enemy->coneDir[4].cy=--enemy->coneDir[1].cy; // arriba
			
			if(detectPlayer(getPosWorld(tempX-1,enemy->coneDir[1].cy),enemy,&isdetected)==1)
			{
				//   					 X X
				// cuadrado superior E X X X
				// finalmente avanza el ultimo cuadrado
				--enemy->coneDir[4].cx;
				
			}
		}
		
		if(detectPlayer(getPosWorld(tempX,tempY+1),enemy,&isdetected)==1)
		{
				//						 X X
				// cuadrado inferior E X X X
				//						 X
				// igual que el caso anterior solo q poniendo el cuadro abajo
				enemy->coneDir[6].cx=--enemy->coneDir[3].cx;
				enemy->coneDir[6].cy=++enemy->coneDir[3].cy; // abajo
				
				if(detectPlayer(getPosWorld(tempX-1,enemy->coneDir[3].cy),enemy,&isdetected)==1)
				{
					//						 X X
					// cuadrado inferior E X X X
					//	   					 X X
					// igual que el caso anterior pero poniendo el cuadro abajo
					--enemy->coneDir[6].cx;
					
				}
		}
	}

	if(isdetected==0 )
		drawCone(enemy->coneDir,6);
	updateCone(enemy->coneDir);

}
void (*moveCone[4])(Tenemy*);

/**
* Return a vector for going from the enemy to the player
*/
void distance(vector2* distance,vector2 *punto2D, Tenemy *enemy)
{
	// vector2 dist;
	distance->x= punto2D->x -  enemy->base.cx;
	distance->y= punto2D->y -  enemy->base.cy;
}

unsigned char move(Tenemy *enemy,vector2 *point2D)
{

	char absX, absY, movex=1, movey=1;
	unsigned char canMove;
	vector2 dist;
	distance(&dist,point2D,enemy);
	absX= dist.x;
	absY= dist.y;

	if(absX<0)
	{
		absX*=(-1); 
		movex=-1;

	}
	if(absY<0){
		absY*=(-1);
		movey=-1;

	}
	
	if(absY>absX)
	{			
		movex = enemy->base.cx;	
		movey = enemy->base.cy + movey;		
	}
	else
	{
		movex = enemy->base.cx + movex;
		movey = enemy->base.cy;			
	}		
	//Via de escape: si no se mueve entonces devuelve 9
	if(absX ==0 && absY==0)
		return 9;
	canMove= updatePosition(movex, movey, &enemy->base);
	if(canMove == 3){
		enemy->currentState=2;
	}
	else if(canMove == 2){
		getStunned(enemy);
	}
	return canMove;
}

/**
* Patrol state of the enemy
*/
void doSearch(Tenemy* enemy)
{
	updateCone(enemy->coneDir);
	cleanCone(enemy->coneDir);
	enemy->searchDelay = 0;
	enemy->currentState = 5;
	enemy->lookAt=0;

}
void follow(Tenemy *enemy, unsigned char pointX, unsigned char pointY)
{
	unsigned char canMove;
	vector2 destiny= {pointX,pointY};

	canMove = move(enemy,&destiny);
	if(canMove == 0 ){
		doSearch(enemy);
	}
}

void patrol(Tenemy *enemy)
{
	unsigned char inPatrolPoint;
	
	vector2 point;
	point.x=enemy->vectorPatrolPoints[enemy->pointPatrol].x; 
	point.y=enemy->vectorPatrolPoints[enemy->pointPatrol].y;
	
	inPatrolPoint=move(enemy,&point);
	moveCone[enemy->lookAt](enemy);          
	
	drawSP(&enemy->base);
	
	if(inPatrolPoint==9)
	{
		++enemy->pointPatrol;
		if(enemy->pointPatrol > enemy->vectorPatrolPoints[10].y)
			enemy->pointPatrol=0;

		if(enemy->vectorPatrolPoints[enemy->pointPatrol].y - enemy->base.cy < 0 )
			enemy->lookAt=0;
		else if(enemy->vectorPatrolPoints[enemy->pointPatrol].x - enemy->base.cx > 0 )
			enemy->lookAt=2;
		else if(enemy->vectorPatrolPoints[enemy->pointPatrol].y - enemy->base.cy > 0 )
			enemy->lookAt=1;
		else if(enemy->vectorPatrolPoints[enemy->pointPatrol].x - enemy->base.cx < 0 )
			enemy->lookAt=3;
	}

}

void attack(Tenemy *enemy, Tplayer *player){

	deductLife(player);
	doPathfinding(enemy, &enemy->anchorPoint);
}
void getStunned(Tenemy *enemy){

	updateCone(enemy->coneDir);	
	doSound(1,1);
	enemy->stunTimer=0;
	enemy->base.sp0 = SpEnemyStunned;
	enemy->currentState = 3;
	drawSP(&enemy->base);	
}
void stunned(Tenemy *enemy){
	if(enemy->stunTimer < MAXTIMESTUNNED){
		++enemy->stunTimer;	
		cleanCone(enemy->coneDir);
		drawSP(&enemy->base);		
	}
	else{
		enemy->base.sp0 = spEnemy1R;
		enemy->currentState = 1;
	}
}


void initializeEnemy(Tenemy* enemy, vector2 *patrolTpoints[11], unsigned char cx, unsigned char cy, unsigned char ox, unsigned char oy, vector2 *anchor, unsigned char anchorDistance)
{
	unsigned char i;
	enemy->pointPatrol = 0;
	enemy->base.sp0= spEnemy1R;

    enemy->base.cx = cx;
    enemy->base.cy = cy;
    enemy->base.ox = ox;
    enemy->base.oy = oy;

    enemy->base.type=TYPEENEMY1;
    enemy->speedMove=ENEMYSPEED;
    enemy->pathObjective=0;

    enemy->currentState=0;
    enemy->lookAt= 2;
    drawSP(&enemy->base);
    enemy->coneDir[0].ox=enemy->coneDir[0].oy=enemy->coneDir[0].cx=enemy->coneDir[0].cy=3;
    enemy->coneDir[1].ox=enemy->coneDir[1].oy=enemy->coneDir[1].cx=enemy->coneDir[1].cy=3;
    enemy->coneDir[2].ox=enemy->coneDir[2].oy=enemy->coneDir[2].cx=enemy->coneDir[2].cy=3;
    enemy->coneDir[3].ox=enemy->coneDir[3].oy=enemy->coneDir[3].cx=enemy->coneDir[3].cy=3;
    enemy->coneDir[4].ox=enemy->coneDir[4].oy=enemy->coneDir[4].cx=enemy->coneDir[4].cy=3;
    enemy->coneDir[5].ox=enemy->coneDir[5].oy=enemy->coneDir[5].cx=enemy->coneDir[5].cy=3;
    enemy->coneDir[6].ox=enemy->coneDir[6].oy=enemy->coneDir[6].cx=enemy->coneDir[6].cy=3;

    // puntos de patrol
    for(i = 0; i < patrolTpoints[10]->x; ++i){
    	enemy->vectorPatrolPoints[i].x = patrolTpoints[i]->x;
    	enemy->vectorPatrolPoints[i].y = patrolTpoints[i]->y;
    }
    enemy->vectorPatrolPoints[10].x = patrolTpoints[10]->x; //posiciones ocupadas del vector
    enemy->vectorPatrolPoints[10].y = patrolTpoints[10]->y;

    enemy->anchorPoint.x = anchor->x;
    enemy->anchorPoint.y = anchor->y;
    enemy->anchorDistance = anchorDistance; //ANKOR

}



void search(Tenemy* enemy)
{
	drawSP(&enemy->base);
	// if(enemy->searchDelay==0)
	moveCone[enemy->lookAt](enemy);

	++enemy->searchDelay;
	if(enemy->searchDelay> MAXTIMESEARCH)
	{
		// cleanCone(enemy->coneDir);
		drawSP(&enemy->base);
		enemy->searchDelay=0;
		++enemy->lookAt;
		if(enemy->lookAt>3)
		{
			enemy->lookAt=0;
			enemy->pointPatrol=0;
			doPathfinding(enemy, &enemy->anchorPoint);
		}
	}
}


void enemyAI(Tenemy *enemy, Tplayer *player)
{

	switch(enemy->currentState)
	{
		case 0: patrol(enemy);
			break;
		case 1:follow(enemy,player->base.cx,player->base.cy);
			break;
		case 2:	attack(enemy, player);
			break;
		case 3: stunned(enemy);
			break;
		case 4: pathfinding(enemy);
			break;
		case 5: search(enemy);
			break;
	}
}
