#ifndef _STRUCTS_H
#define _STRUCTS_H

typedef struct
{
	char x;
	char y;
	
}vector2;

typedef struct TwayPoint TwayPoint;

struct TwayPoint 
{
	vector2 point2D;
	TwayPoint *next;
	TwayPoint *prev;
	unsigned char number;

};

typedef struct   		// minimun sprite structure
{
    char *sp0;		//sprite 1
    unsigned char cx, cy;	//2 bytes 89 	current coordinates
    unsigned char ox, oy;	//2 bytes 1011  old coordinates
    unsigned char type;     //Numero asociado a su tipo    
	
}Tsprite;

typedef struct 
{    
    Tsprite base;        
    unsigned short speedMove;
 
}Tplayer;

/// Hablar sobre refactorizar cone
typedef struct 
{
    unsigned char cx, cy;	// current coordinates
    unsigned char ox, oy;	// old coordinates
}Tcone;

typedef struct Tenemy Tenemy;

struct Tenemy
{
	Tsprite base;
	Tcone coneDir[7];
	vector2 anchorPoint;
	vector2 vectorPatrolPoints[11]; //el ultimo espacio.x es para decir cuantas posiciones tiene ocupadas
	unsigned char currentState;
	unsigned char lookAt; // 0-> UP, 1-> DOWN, 2->RIGTH, 3->LEFT
	unsigned short speedMove;
	unsigned char stunTimer; 
	unsigned char searchDelay;
	unsigned char anchorDistance;
	unsigned char pointPatrol;

	unsigned char pathObjective; // si es 0 vuelve al Anchor, si es 1 su objetivo es el player
	unsigned char canMovePathF;
	TwayPoint* nearEnemy; // distancia del enemigo al waypoint mas cercano
	TwayPoint* nearEnemy2; // distancia del enemigo al segundo waypoint mas cercano
	TwayPoint* nearDestiny; // distancia del objetivo al waypoint mas cercano 	

	// Variables para Enemy2
	unsigned char waitTimer;
	unsigned char coneRestrictions;
	Tenemy *enemyHelper;

};

#endif