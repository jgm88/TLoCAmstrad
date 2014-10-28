#include <cpcrslib.h>
#include "cpcr2_all.h"
#include "cpcwyzlib.h"
#include "sound.h"

#define INSTRUCTIONS    0
#define GAME            1
#define GAMEOVER        2
#define CREDITS         3

#define PLAYERSPEED     13

Tplayer player;
Tenemy enemy1, enemy2, enemy3, enemy4, enemy5, enemy6;
Tsprite fire;

unsigned char endGame;
unsigned char gameState;

void setPaletteCPCr2(){
    // 0, 26, 25, 13, 6, 3, 7, 17, 16, 15, 14, 10, 18, 4, 23, 19
    cpc_SetInk(0,0);
    cpc_SetInk(1,26);
    cpc_SetInk(2,25);
    cpc_SetInk(3,13);
    cpc_SetInk(4,6);
    cpc_SetInk(5,3);
    cpc_SetInk(6,7);
    cpc_SetInk(7,17);
    cpc_SetInk(8,16);
    cpc_SetInk(9,15);
    cpc_SetInk(10,14);
    cpc_SetInk(11,10);
    cpc_SetInk(12,18);
    cpc_SetInk(13,4);
    cpc_SetInk(14,23);
    cpc_SetInk(15,19);
}

void scr_waitVSYNC(){

    __asm
        raster:
            push bc
            ld b,#0xF5
        wait:   
            in a,(c)
            rra
            jr nc,wait
            pop bc
    __endasm;
}

vector2 *patrolTpointsEnemy1[11];
vector2 *patrolTpointsEnemy2[11];
vector2 p0Enemy1, p1Enemy1, p2Enemy1, p3Enemy1, p4Enemy1, p5Enemy1, p6Enemy1, p7Enemy1, p8Enemy1, p9Enemy1, pAnkorEnemy1;
vector2 p0Enemy2, p1Enemy2, p2Enemy2, p3Enemy2, p4Enemy2, p5Enemy2, p6Enemy2, p7Enemy2, pAnkorEnemy2;

void init(){
     

    loadLevel();
    drawMap();
    initGame();
    initWayPoints();

    moveCone[0]=coneUp;
    moveCone[1]=coneDown;
    moveCone[2]=coneRight;
    moveCone[3]=coneLeft;
    
    player.base.sp0= spHeroR;
    player.base.type = TYPEPLAYER;    
    player.base.cx=2;
    player.base.cy=4;
    player.base.ox=1;  //Hay que poner de origen un ground
    player.base.oy=3;  //para la primera vez que carga el mapa
    player.speedMove=PLAYERSPEED;
    worldMatrix[4][2]=29;	
    drawSP(&player.base); 
	
    fire.type = TYPEFIRE;
    fire.sp0 = spFireR;
    fire.ox = 3;
    fire.oy = 3;
    fire.cx = 1;
    fire.cy = 4;
    
/////Enemy 1 
/////////////
    p0Enemy1.y=10; p0Enemy1.x=4;
    p1Enemy1.y=16; p1Enemy1.x=4;
    p2Enemy1.y=16; p2Enemy1.x=2;
    p3Enemy1.y=9;  p3Enemy1.x=2;
    p4Enemy1.y=9;  p4Enemy1.x=7;
    p5Enemy1.y=5;  p5Enemy1.x=7;
    p6Enemy1.y=5;  p6Enemy1.x=10;
    p7Enemy1.y=8;  p7Enemy1.x=10;
    p8Enemy1.y=8;  p8Enemy1.x=15;
    p9Enemy1.y=10; p9Enemy1.x=15;

    
    patrolTpointsEnemy1[0]= &p0Enemy1;
    patrolTpointsEnemy1[1]= &p1Enemy1;
    patrolTpointsEnemy1[2]= &p2Enemy1;
    patrolTpointsEnemy1[3]= &p3Enemy1;
    patrolTpointsEnemy1[4]= &p4Enemy1;
    patrolTpointsEnemy1[5]= &p5Enemy1;
    patrolTpointsEnemy1[6]= &p6Enemy1;
    patrolTpointsEnemy1[7]= &p7Enemy1;
    patrolTpointsEnemy1[8]= &p8Enemy1;
    patrolTpointsEnemy1[9]= &p9Enemy1;

    patrolTpointsEnemy1[10]->x = 10; //tam de patrolTpointsEnemy1
    patrolTpointsEnemy1[10]->y = 9;

    pAnkorEnemy1.x=4;
    pAnkorEnemy1.y=10;
//////////////////////
    initializeEnemy(&enemy1, patrolTpointsEnemy1, 4, 10, 3, 3, &pAnkorEnemy1, 5);

/////Enemy 2 
/////////////
    p0Enemy2.y=17;  p0Enemy2.x=10;
    p1Enemy2.y=20;  p1Enemy2.x=10;
    p2Enemy2.y=20;  p2Enemy2.x=6;
    p3Enemy2.y=17;  p3Enemy2.x=6;
    p4Enemy2.y=17;  p4Enemy2.x=8;
    p5Enemy2.y=14;  p5Enemy2.x=8;
    p6Enemy2.y=14;  p6Enemy2.x=14;
    p7Enemy2.y=17;  p7Enemy2.x=14;

    patrolTpointsEnemy2[0]= &p0Enemy2;
    patrolTpointsEnemy2[1]= &p1Enemy2;
    patrolTpointsEnemy2[2]= &p2Enemy2;
    patrolTpointsEnemy2[3]= &p3Enemy2;
    patrolTpointsEnemy2[4]= &p4Enemy2;
    patrolTpointsEnemy2[5]= &p5Enemy2;
    patrolTpointsEnemy2[6]= &p6Enemy2;
    patrolTpointsEnemy2[7]= &p7Enemy2;

    patrolTpointsEnemy2[10]->x = 8; //tam de patrolTpointsEnemy2
    patrolTpointsEnemy2[10]->y = 7;

    pAnkorEnemy2.x=9;
    pAnkorEnemy2.y=16;
    initializeEnemy(&enemy2, patrolTpointsEnemy2, 10, 16, 3, 3, &pAnkorEnemy2, 5);
//////////////////////

/////Enemy 3 
/////////////    
    initializeEnemy(&enemy3, patrolTpointsEnemy2, 8, 22, 3, 3, &pAnkorEnemy2, 5);
    enemy3.base.sp0 = spEnemy2L;
    enemy3.coneRestrictions = 3;   
    enemy3.base.type = TYPEENEMY2;    
    worldMatrix[22][8] = TYPEENEMY2;
    drawSP(&enemy3.base);
    enemy3.enemyHelper = &enemy2;
    
//////////////////////

/////Enemy 4 
/////////////    
    initializeEnemy(&enemy4, patrolTpointsEnemy2, 15, 21, 3, 3, &pAnkorEnemy2, 5);
    enemy4.base.sp0 = spEnemy2L;
    enemy4.coneRestrictions = 3;   
    enemy4.base.type = TYPEENEMY2;    
    worldMatrix[21][15] = TYPEENEMY2;
    drawSP(&enemy4.base);
    enemy4.enemyHelper = &enemy2;
    
//////////////////////

/////Enemy 5 
/////////////    
    initializeEnemy(&enemy5, patrolTpointsEnemy2, 16, 10, 3, 3, &pAnkorEnemy2, 5);
    enemy5.base.sp0 = spEnemy2L;
    enemy5.coneRestrictions = 3;   
    enemy5.base.type = TYPEENEMY2;    
    worldMatrix[10][16] = TYPEENEMY2;
    drawSP(&enemy5.base);
    enemy5.enemyHelper = &enemy1;
    
//////////////////////

/////Enemy 6 
/////////////    
    initializeEnemy(&enemy6, patrolTpointsEnemy2, 1, 9, 3, 3, &pAnkorEnemy2, 5);
    enemy6.base.sp0 = spEnemy2R;
    enemy6.coneRestrictions = 1;   
    enemy6.base.type = TYPEENEMY2;    
    worldMatrix[9][1] = TYPEENEMY2;
    drawSP(&enemy6.base);
    enemy6.enemyHelper = &enemy1;
    
//////////////////////
}


void doSound(unsigned char a, unsigned char b){
    cpc_WyzStartEffect(a,b);
}
void endMusic()
{
    cpc_WyzSetPlayerOff();
}

void playerAttack(unsigned char x, unsigned char y){
    fire.sp0 = spFireR;
    updatePosition(x, y, &fire);    
    doSound(1,3);
}
void keyHandler(){

	if(cpct_isKeyPressed(Key_D)){        	
        if(updatePosition(player.base.cx+1, player.base.cy, &player.base)!=0)
            cpc_WyzStartEffect(0,0);
	}
	else if(cpct_isKeyPressed(Key_A)){        
		if(updatePosition(player.base.cx-1, player.base.cy, &player.base)!=0)
		  cpc_WyzStartEffect(0,0);
	} 
	else if(cpct_isKeyPressed(Key_W)){        
		if(updatePosition(player.base.cx, player.base.cy-1, &player.base)!=0)
		  cpc_WyzStartEffect(0,0);
	}
	else if(cpct_isKeyPressed(Key_S)){			
		if(updatePosition(player.base.cx, player.base.cy+1, &player.base)!=0)
		  cpc_WyzStartEffect(0,0);
	}
    else if(cpct_isKeyPressed(Key_CursorUp)){
        playerAttack(player.base.cx, player.base.cy-1);
    }     
    else if(cpct_isKeyPressed(Key_CursorRight)){
        playerAttack(player.base.cx+1, player.base.cy);
    }  
    else if(cpct_isKeyPressed(Key_CursorDown)){
        playerAttack(player.base.cx, player.base.cy+1);
    }  
    else if(cpct_isKeyPressed(Key_CursorLeft)){
        playerAttack(player.base.cx-1, player.base.cy);
    } 
    
    if(cpct_isKeyPressed(Key_R))
    {   
        reset();
    }
}
void soundInstructions(){
	cpc_WyzInitPlayer(SOUND_TABLE_2, RULE_TABLE_2, EFFECT_TABLE, SONG_TABLE_2);
	cpc_WyzLoadSong(0);	//Select song to play (uncompress it and the start to play)
	cpc_WyzSetPlayerOn();		//start music and sound effects (SFX)
}

void soundLevel(){
    cpc_WyzInitPlayer(SOUND_TABLE_4, RULE_TABLE_4, EFFECT_TABLE, SONG_TABLE_4);
    cpc_WyzLoadSong(0);
    cpc_WyzSetPlayerOn();
    //Necesito un cafe
}
void soundWin(){
    cpc_WyzInitPlayer(SOUND_TABLE_1, RULE_TABLE_1, EFFECT_TABLE, SONG_TABLE_1);
    cpc_WyzLoadSong(0);
    cpc_WyzSetPlayerOn();
    //Necesito un cafe
}

void reset(){
    endGame=GAME;
}

void game(){
    // TODO: intentar usar unsigned char
    unsigned short nextMove=0, nextIAMove=0;
    endGame=0;
    soundLevel();
    init();
 
    while(endGame==0){
          
        scr_waitVSYNC();
        ++nextIAMove;
        ++nextMove;
       
        if(nextIAMove>enemy1.speedMove){
            nextIAMove=0;
            enemyAI(&enemy1, &player); 
            enemyAI(&enemy2, &player);
            enemyAI2(&enemy3, &player);
            enemyAI2(&enemy4, &player);
            enemyAI2(&enemy5, &player);
            enemyAI2(&enemy6, &player);
        }
        if(nextMove> player.speedMove){
            nextMove=0;
            cpct_scanKeyboardFast();
            keyHandler();       
        }
        
    }       
    // 2 -> GameOver
    // 3 -> Credits
   gameState=endGame;
   cpc_WyzSetPlayerOff();
}

void instructions(){
    unsigned char salida = 1;
    gameState=GAME;
    
    instructionScene();
    soundInstructions();
    
    while(salida){
        cpct_scanKeyboardFast();
        if(cpct_isKeyPressed(Key_C))
            salida = 0;
    }
    cpc_WyzSetPlayerOff(); 
}
void gameOver(){

    unsigned char salida = 1;
    gameOverScene();
    soundInstructions();
    gameState=INSTRUCTIONS;
    
    while(salida){
        cpct_scanKeyboardFast();
        if(cpct_isKeyPressed(Key_C))
            salida = 0;        
    }    
    cpc_WyzSetPlayerOff(); 
}

void credits(){

    unsigned char salida = 1;
    soundWin();
    creditsScene();
    gameState=INSTRUCTIONS;
    
    while(salida){
        cpct_scanKeyboardFast();
        if(cpct_isKeyPressed(Key_C))
            salida = 0;
    }    
    cpc_WyzSetPlayerOff(); 

}



void main(void){

    setPaletteCPCr2();
    initialiteMap();
    cpc_SetBorder(0);
    cpc_SetModo(0);
    cpct_disableFirmware();    
    gameState=INSTRUCTIONS;
    
    while(1)
    {
        switch(gameState)
        {
            case INSTRUCTIONS: instructions();
                break;
            case GAME: game();
                break;
            case GAMEOVER: gameOver();
                break;
            case CREDITS: credits();
                break;
        }   
        
    }    
    cpct_reenableFirmware();
}