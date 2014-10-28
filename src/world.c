#include "world.h"

unsigned char worldMatrix[25][20];
unsigned char* vTiles[40];

const unsigned char TYPEGROUND 	= 1;
const unsigned char TYPEBRICK 	= 2;
const unsigned char TYPEKEY 	= 3;
const unsigned char TYPEPLAYER 	= 5;
const unsigned char TYPEFIRE 	= 6;
const unsigned char TYPEENEMY1 	= 7;
const unsigned char TYPEENEMY2 	= 8;
const unsigned char TYPEEXIT 	= 9;


void drawMap()
{
	unsigned char i, j;	

	vTiles[0] = spBlack;
	vTiles[1] = spGround;
	vTiles[2] = spBrick;
	vTiles[3] = spKey;
	vTiles[4] = spDoorR;
	vTiles[5] = spHeroR;
	vTiles[6] = spFireR;
	vTiles[7] = spEnemy1R;	

	////PASAR A POKES////

	vTiles[9] = spHeart;
	vTiles[10] = spW;
	vTiles[11] = spA;
	vTiles[12] = spS;
	vTiles[13] = spD;
	vTiles[14] = spC;
	vTiles[15] = spO;
	vTiles[16] = spN;
	vTiles[17] = spT;
	vTiles[18] = spR;
	vTiles[19] = spL;
	vTiles[20] = spUpArrow;
	vTiles[21] = spDownArrow;
	vTiles[22] = spRigthArrow;
	vTiles[23] = spLeftArrow;
	vTiles[24] = spE;
	vTiles[25] = spH;
	vTiles[26] = spG;
	vTiles[27] = spF;
	vTiles[28] = spP;
	vTiles[29] = spM;
	vTiles[30] = spV;
	vTiles[31] = spK;

	///FIN POKES /////


	for (j=0; j<25; ++j){
		for (i=0; i<20; ++i){					
			cpct_drawSprite4x8_aligned(vTiles[worldMatrix[j][i]],videoMapMatrix[j][i]);	
		}
	}	
}


unsigned char getPosWorld(unsigned char x, unsigned char y){
	return worldMatrix[y][x];
	//mirar la matriz mundo para entender pk es es [y][x]
	//
}

unsigned char canMoveWorld(unsigned char x, unsigned char y){		
	if(getPosWorld(x,y) == 1)
		return 1;
	return 0;
}
void moveSP(unsigned char x, unsigned char y, Tsprite *tSprite){
	tSprite->ox = tSprite->cx;
	tSprite->oy = tSprite->cy;
	worldMatrix[tSprite->oy][tSprite->ox] = 1;

	tSprite->cx = x;
	tSprite->cy = y;
	worldMatrix[y][x] = tSprite->type;		
	drawSP(tSprite);
}
unsigned char updatePosition(unsigned char x, unsigned char y, Tsprite *tSprite){

	unsigned char newPosWorld = getPosWorld(x,y);

	if(newPosWorld == TYPEGROUND){		
		moveSP(x,y,tSprite);			
		return 1;
	}
	else if(tSprite->type == TYPEENEMY1){
		if (newPosWorld == TYPEFIRE){
			worldMatrix[y][x] = 1;
			cpct_drawSprite4x8_aligned(spGround,videoMapMatrix[y][x]);			
			//Devolvemos 2 para que la IA sepa que debe entrar en stunned
			return 2;	
		}		
		else if(newPosWorld == TYPEPLAYER){
			// inidica que debe pasar a Attack
			return 3;
		}
	}	
	else if(tSprite->type == TYPEPLAYER){
		if(newPosWorld == TYPEEXIT){
			endGame=3;
			return 1;
		}		
		if(newPosWorld == TYPEKEY){
			moveSP(x,y,tSprite);			
			pickUpKey();
			return 1;
		}
		if(newPosWorld == TYPEFIRE){
			moveSP(x,y,tSprite);			
			return 1;
		}
	}
	
	return 0;

}

void drawSP(Tsprite *pj)
{
	cpct_drawSprite4x8_aligned(pj->sp0,getPosVideo(pj->cx,pj->cy));
	cpct_drawSprite4x8_aligned(spGround,getPosVideo(pj->ox,pj->oy));
}

//Vector de puertas con coordenadas asociadas, que el metodo reciba la puerta que debe abrir
void openDoor(){
	worldMatrix[5][19] = TYPEEXIT;
	worldMatrix[6][19] = TYPEEXIT;

	cpct_drawSprite4x8_aligned(spOpenDoor,videoMapMatrix[5][19]);
	cpct_drawSprite4x8_aligned(spOpenDoor,videoMapMatrix[6][19]);	

}

void instructionScene() {
	unsigned char i, j;
	 worldMatrix[0][0] = 2;  worldMatrix[0][1] = 2;  worldMatrix[0][2] = 2;  worldMatrix[0][3] = 2;  worldMatrix[0][4] = 2;  worldMatrix[0][5] = 2;  worldMatrix[0][6] = 2;  worldMatrix[0][7] = 2;  worldMatrix[0][8] = 2;  worldMatrix[0][9] = 2;  worldMatrix[0][10] = 2;  worldMatrix[0][11] = 2;  worldMatrix[0][12] = 2;  worldMatrix[0][13] = 2;  worldMatrix[0][14] = 2;  worldMatrix[0][15] = 2;  worldMatrix[0][16] = 2;  worldMatrix[0][17] = 2;  worldMatrix[0][18] = 2;  worldMatrix[0][19] = 2; 
	 worldMatrix[1][0] = 2;  worldMatrix[1][1] = 9;  worldMatrix[1][2] = 9;  worldMatrix[1][3] = 9;  worldMatrix[1][4] = 9;  worldMatrix[1][5] = 2;  worldMatrix[1][6] = 2;  worldMatrix[1][7] = 2;  worldMatrix[1][8] = 2;  worldMatrix[1][9] = 2;  worldMatrix[1][10] = 2;  worldMatrix[1][11] = 2;  worldMatrix[1][12] = 2;  worldMatrix[1][13] = 2;  worldMatrix[1][14] = 2;  worldMatrix[1][15] = 9;  worldMatrix[1][16] = 9;  worldMatrix[1][17] = 9;  worldMatrix[1][18] = 9;  worldMatrix[1][19] = 2; 
	 worldMatrix[2][0] = 2;  worldMatrix[2][1] = 2;  worldMatrix[2][2] = 2;  worldMatrix[2][3] = 2;  worldMatrix[2][4] = 2;  worldMatrix[2][5] = 2;  worldMatrix[2][6] = 2;  worldMatrix[2][7] = 2;  worldMatrix[2][8] = 2;  worldMatrix[2][9] = 2;  worldMatrix[2][10] = 2;  worldMatrix[2][11] = 2;  worldMatrix[2][12] = 2;  worldMatrix[2][13] = 2;  worldMatrix[2][14] = 2;  worldMatrix[2][15] = 2;  worldMatrix[2][16] = 2;  worldMatrix[2][17] = 2;  worldMatrix[2][18] = 2;  worldMatrix[2][19] = 2; 
	 worldMatrix[3][0] = 2;  worldMatrix[3][1] = 0;  worldMatrix[3][2] = 0;  worldMatrix[3][3] = 0;  worldMatrix[3][4] = 0;  worldMatrix[3][5] = 0;  worldMatrix[3][6] = 0;  worldMatrix[3][7] = 0;  worldMatrix[3][8] = 0;  worldMatrix[3][9] = 0;  worldMatrix[3][10] = 0;  worldMatrix[3][11] = 0;  worldMatrix[3][12] = 0;  worldMatrix[3][13] = 0;  worldMatrix[3][14] = 0;  worldMatrix[3][15] = 0;  worldMatrix[3][16] = 0;  worldMatrix[3][17] = 0;  worldMatrix[3][18] = 0;  worldMatrix[3][19] = 2; 
	 worldMatrix[4][0] = 2;  worldMatrix[4][1] = 0;  worldMatrix[4][2] = 0;  worldMatrix[4][3] = 0;  worldMatrix[4][4] = 0;  worldMatrix[4][5] = 0;  worldMatrix[4][6] = 0;  worldMatrix[4][7] = 0;  worldMatrix[4][8] = 0;  worldMatrix[4][9] = 0;  worldMatrix[4][10] = 0;  worldMatrix[4][11] = 0;  worldMatrix[4][12] = 0;  worldMatrix[4][13] = 0;  worldMatrix[4][14] = 0;  worldMatrix[4][15] = 0;  worldMatrix[4][16] = 0;  worldMatrix[4][17] = 0;  worldMatrix[4][18] = 0;  worldMatrix[4][19] = 2; 
	 worldMatrix[5][0] = 2;  worldMatrix[5][1] = 0;  worldMatrix[5][2] = 0;  worldMatrix[5][3] = 0;  worldMatrix[5][4] = 0;  worldMatrix[5][5] = 0;  worldMatrix[5][6] = 0;  worldMatrix[5][7] = 0;  worldMatrix[5][8] = 0;  worldMatrix[5][9] = 17; worldMatrix[5][10] = 25; worldMatrix[5][11] = 24; worldMatrix[5][12] = 0;  worldMatrix[5][13] = 0;  worldMatrix[5][14] = 0;  worldMatrix[5][15] = 0;  worldMatrix[5][16] = 0;  worldMatrix[5][17] = 0;  worldMatrix[5][18] = 0;  worldMatrix[5][19] = 2; 
	 worldMatrix[6][0] = 2;  worldMatrix[6][1] = 0;  worldMatrix[6][2] = 0;  worldMatrix[6][3] = 0;  worldMatrix[6][4] = 0;  worldMatrix[6][5] = 0;  worldMatrix[6][6] = 0;  worldMatrix[6][7] = 19; worldMatrix[6][8] = 24; worldMatrix[6][9] = 26; worldMatrix[6][10] = 24; worldMatrix[6][11] = 16; worldMatrix[6][12] = 13; worldMatrix[6][13] = 0;  worldMatrix[6][14] = 0;  worldMatrix[6][15] = 0;  worldMatrix[6][16] = 0;  worldMatrix[6][17] = 0;  worldMatrix[6][18] = 0;  worldMatrix[6][19] = 2; 
	 worldMatrix[7][0] = 2;  worldMatrix[7][1] = 0;  worldMatrix[7][2] = 0;  worldMatrix[7][3] = 0;  worldMatrix[7][4] = 0;  worldMatrix[7][5] = 0;  worldMatrix[7][6] = 0;  worldMatrix[7][7] = 0;  worldMatrix[7][8] = 0;  worldMatrix[7][9] = 15; worldMatrix[7][10] = 27; worldMatrix[7][11] = 0;  worldMatrix[7][12] = 0;  worldMatrix[7][13] = 0;  worldMatrix[7][14] = 0;  worldMatrix[7][15] = 0;  worldMatrix[7][16] = 0;  worldMatrix[7][17] = 0;  worldMatrix[7][18] = 0;  worldMatrix[7][19] = 2; 
	 worldMatrix[8][0] = 2;  worldMatrix[8][1] = 0;  worldMatrix[8][2] = 0;  worldMatrix[8][3] = 0;  worldMatrix[8][4] = 0;  worldMatrix[8][5] = 0;  worldMatrix[8][6] = 0;  worldMatrix[8][7] = 14; worldMatrix[8][8] = 28; worldMatrix[8][9] = 14; worldMatrix[8][10] = 24; worldMatrix[8][11] = 18; worldMatrix[8][12] = 13; worldMatrix[8][13] = 15; worldMatrix[8][14] = 0;  worldMatrix[8][15] = 0;  worldMatrix[8][16] = 0;  worldMatrix[8][17] = 0;  worldMatrix[8][18] = 0;  worldMatrix[8][19] = 2; 
	 worldMatrix[9][0] = 2;  worldMatrix[9][1] = 0;  worldMatrix[9][2] = 0;  worldMatrix[9][3] = 0;  worldMatrix[9][4] = 0;  worldMatrix[9][5] = 0;  worldMatrix[9][6] = 0;  worldMatrix[9][7] = 0;  worldMatrix[9][8] = 0;  worldMatrix[9][9] = 0;  worldMatrix[9][10] = 0;  worldMatrix[9][11] = 0;  worldMatrix[9][12] = 0;  worldMatrix[9][13] = 0;  worldMatrix[9][14] = 0;  worldMatrix[9][15] = 0;  worldMatrix[9][16] = 0;  worldMatrix[9][17] = 0;  worldMatrix[9][18] = 0;  worldMatrix[9][19] = 2; 
	worldMatrix[10][0] = 2; worldMatrix[10][1] = 0; worldMatrix[10][2] = 0; worldMatrix[10][3] = 0; worldMatrix[10][4] = 0; worldMatrix[10][5] = 29;worldMatrix[10][6] = 15;worldMatrix[10][7] = 30;worldMatrix[10][8] = 24;worldMatrix[10][9] = 0; worldMatrix[10][10] = 11;worldMatrix[10][11] = 17;worldMatrix[10][12] = 17;worldMatrix[10][13] = 11;worldMatrix[10][14] = 14;worldMatrix[10][15] = 31; worldMatrix[10][16] = 0; worldMatrix[10][17] = 0; worldMatrix[10][18] = 0; worldMatrix[10][19] = 2; 
	worldMatrix[11][0] = 2; worldMatrix[11][1] = 0; worldMatrix[11][2] = 0; worldMatrix[11][3] = 0; worldMatrix[11][4] = 0; worldMatrix[11][5] = 0; worldMatrix[11][6] = 0; worldMatrix[11][7] = 0; worldMatrix[11][8] = 0; worldMatrix[11][9] = 0; worldMatrix[11][10] = 0; worldMatrix[11][11] = 0; worldMatrix[11][12] = 0; worldMatrix[11][13] = 0; worldMatrix[11][14] = 0; worldMatrix[11][15] = 0; worldMatrix[11][16] = 0; worldMatrix[11][17] = 0; worldMatrix[11][18] = 0; worldMatrix[11][19] = 2; 
	worldMatrix[12][0] = 2; worldMatrix[12][1] = 0; worldMatrix[12][2] = 0; worldMatrix[12][3] = 0; worldMatrix[12][4] = 0; worldMatrix[12][5] = 0; worldMatrix[12][6] = 0; worldMatrix[12][7] = 10;worldMatrix[12][8] = 0; worldMatrix[12][9] = 0; worldMatrix[12][10] = 0; worldMatrix[12][11] = 0; worldMatrix[12][12] = 20;worldMatrix[12][13] = 0; worldMatrix[12][14] = 0; worldMatrix[12][15] = 0; worldMatrix[12][16] = 0; worldMatrix[12][17] = 0; worldMatrix[12][18] = 0; worldMatrix[12][19] = 2; 
	worldMatrix[13][0] = 2; worldMatrix[13][1] = 0; worldMatrix[13][2] = 0; worldMatrix[13][3] = 0; worldMatrix[13][4] = 0; worldMatrix[13][5] = 0; worldMatrix[13][6] = 11;worldMatrix[13][7] = 0; worldMatrix[13][8] = 13;worldMatrix[13][9] = 0; worldMatrix[13][10] = 0; worldMatrix[13][11] = 23;worldMatrix[13][12] = 0; worldMatrix[13][13] = 22;worldMatrix[13][14] = 0; worldMatrix[13][15] = 0; worldMatrix[13][16] = 0; worldMatrix[13][17] = 0; worldMatrix[13][18] = 0; worldMatrix[13][19] = 2; 
	worldMatrix[14][0] = 2; worldMatrix[14][1] = 0; worldMatrix[14][2] = 0; worldMatrix[14][3] = 0; worldMatrix[14][4] = 0; worldMatrix[14][5] = 0; worldMatrix[14][6] = 0; worldMatrix[14][7] = 12;worldMatrix[14][8] = 0; worldMatrix[14][9] = 0; worldMatrix[14][10] = 0; worldMatrix[14][11] = 0; worldMatrix[14][12] = 21;worldMatrix[14][13] = 0; worldMatrix[14][14] = 0; worldMatrix[14][15] = 0; worldMatrix[14][16] = 0; worldMatrix[14][17] = 0; worldMatrix[14][18] = 0; worldMatrix[14][19] = 2; 
	worldMatrix[15][0] = 2; worldMatrix[15][1] = 0; worldMatrix[15][2] = 0; worldMatrix[15][3] = 0; worldMatrix[15][4] = 0; worldMatrix[15][5] = 0; worldMatrix[15][6] = 0; worldMatrix[15][7] = 0; worldMatrix[15][8] = 0; worldMatrix[15][9] = 0; worldMatrix[15][10] = 0; worldMatrix[15][11] = 0; worldMatrix[15][12] = 0; worldMatrix[15][13] = 0; worldMatrix[15][14] = 0; worldMatrix[15][15] = 0; worldMatrix[15][16] = 0; worldMatrix[15][17] = 0; worldMatrix[15][18] = 0; worldMatrix[15][19] = 2; 
	worldMatrix[16][0] = 2; worldMatrix[16][1] = 0; worldMatrix[16][2] = 0; worldMatrix[16][3] = 0; worldMatrix[16][4] = 0; worldMatrix[16][5] = 0; worldMatrix[16][6] = 18;worldMatrix[16][7] = 0; worldMatrix[16][8] = 0; worldMatrix[16][9] = 18;worldMatrix[16][10] = 24;worldMatrix[16][11] = 12;worldMatrix[16][12] = 24;worldMatrix[16][13] = 17;worldMatrix[16][14] = 0; worldMatrix[16][15] = 0; worldMatrix[16][16] = 0; worldMatrix[16][17] = 0; worldMatrix[16][18] = 0; worldMatrix[16][19] = 2; 
	worldMatrix[17][0] = 2; worldMatrix[17][1] = 0; worldMatrix[17][2] = 0; worldMatrix[17][3] = 0; worldMatrix[17][4] = 0; worldMatrix[17][5] = 0; worldMatrix[17][6] = 0; worldMatrix[17][7] = 0; worldMatrix[17][8] = 0; worldMatrix[17][9] = 0; worldMatrix[17][10] = 0; worldMatrix[17][11] = 0; worldMatrix[17][12] = 0; worldMatrix[17][13] = 0; worldMatrix[17][14] = 0; worldMatrix[17][15] = 0; worldMatrix[17][16] = 0; worldMatrix[17][17] = 0; worldMatrix[17][18] = 0; worldMatrix[17][19] = 2; 
	worldMatrix[18][0] = 2; worldMatrix[18][1] = 2; worldMatrix[18][2] = 2; worldMatrix[18][3] = 2; worldMatrix[18][4] = 2; worldMatrix[18][5] = 2; worldMatrix[18][6] = 2; worldMatrix[18][7] = 2; worldMatrix[18][8] = 2; worldMatrix[18][9] = 2; worldMatrix[18][10] = 2; worldMatrix[18][11] = 2; worldMatrix[18][12] = 2; worldMatrix[18][13] = 2; worldMatrix[18][14] = 2; worldMatrix[18][15] = 2; worldMatrix[18][16] = 2; worldMatrix[18][17] = 2; worldMatrix[18][18] = 2; worldMatrix[18][19] = 2; 
	worldMatrix[19][0] = 2; worldMatrix[19][1] = 0; worldMatrix[19][2] = 0; worldMatrix[19][3] = 0; worldMatrix[19][4] = 0; worldMatrix[19][5] = 0; worldMatrix[19][6] = 0; worldMatrix[19][7] = 0; worldMatrix[19][8] = 0; worldMatrix[19][9] = 0; worldMatrix[19][10] = 0; worldMatrix[19][11] = 0; worldMatrix[19][12] = 0; worldMatrix[19][13] = 0; worldMatrix[19][14] = 0; worldMatrix[19][15] = 0; worldMatrix[19][16] = 0; worldMatrix[19][17] = 0; worldMatrix[19][18] = 0; worldMatrix[19][19] = 2; 
	worldMatrix[20][0] = 2; worldMatrix[20][1] = 0; worldMatrix[20][2] = 0; worldMatrix[20][3] = 0; worldMatrix[20][4] = 0; worldMatrix[20][5] = 0; worldMatrix[20][6] = 0; worldMatrix[20][7] = 0; worldMatrix[20][8] = 0; worldMatrix[20][9] = 0; worldMatrix[20][10] = 0; worldMatrix[20][11] = 0; worldMatrix[20][12] = 0; worldMatrix[20][13] = 0; worldMatrix[20][14] = 0; worldMatrix[20][15] = 0; worldMatrix[20][16] = 0; worldMatrix[20][17] = 0; worldMatrix[20][18] = 0; worldMatrix[20][19] = 2; 
	worldMatrix[21][0] = 2; worldMatrix[21][1] = 0; worldMatrix[21][2] = 0; worldMatrix[21][3] = 0; worldMatrix[21][4] = 0; worldMatrix[21][5] = 0; worldMatrix[21][6] = 0; worldMatrix[21][7] = 0; worldMatrix[21][8] = 0; worldMatrix[21][9] = 0; worldMatrix[21][10] = 0; worldMatrix[21][11] = 0; worldMatrix[21][12] = 0; worldMatrix[21][13] = 0; worldMatrix[21][14] = 0; worldMatrix[21][15] = 0; worldMatrix[21][16] = 0; worldMatrix[21][17] = 0; worldMatrix[21][18] = 0; worldMatrix[21][19] = 2; 
	worldMatrix[22][0] = 2; worldMatrix[22][1] = 0; worldMatrix[22][2] = 0; worldMatrix[22][3] = 0; worldMatrix[22][4] = 0; worldMatrix[22][5] = 0; worldMatrix[22][6] = 0; worldMatrix[22][7] = 0; worldMatrix[22][8] = 0; worldMatrix[22][9] = 0; worldMatrix[22][10] = 0; worldMatrix[22][11] = 0; worldMatrix[22][12] = 0; worldMatrix[22][13] = 0; worldMatrix[22][14] = 0; worldMatrix[22][15] = 0; worldMatrix[22][16] = 0; worldMatrix[22][17] = 0; worldMatrix[22][18] = 0; worldMatrix[22][19] = 2; 
	worldMatrix[23][0] = 2; worldMatrix[23][1] = 0; worldMatrix[23][2] = 0; worldMatrix[23][3] = 0; worldMatrix[23][4] = 0; worldMatrix[23][5] = 0; worldMatrix[23][6] = 0; worldMatrix[23][7] = 0; worldMatrix[23][8] = 0; worldMatrix[23][9] = 0; worldMatrix[23][10] = 0; worldMatrix[23][11] = 0; worldMatrix[23][12] = 0; worldMatrix[23][13] = 0; worldMatrix[23][14] = 0; worldMatrix[23][15] = 0; worldMatrix[23][16] = 0; worldMatrix[23][17] = 0; worldMatrix[23][18] = 0; worldMatrix[23][19] = 2; 
	worldMatrix[24][0] = 2; worldMatrix[24][1] = 2; worldMatrix[24][2] = 2; worldMatrix[24][3] = 2; worldMatrix[24][4] = 2; worldMatrix[24][5] = 2; worldMatrix[24][6] = 2; worldMatrix[24][7] = 2; worldMatrix[24][8] = 2; worldMatrix[24][9] = 2; worldMatrix[24][10] = 2; worldMatrix[24][11] = 2; worldMatrix[24][12] = 2; worldMatrix[24][13] = 2; worldMatrix[24][14] = 2; worldMatrix[24][15] = 2; worldMatrix[24][16] = 2; worldMatrix[24][17] = 2; worldMatrix[24][18] = 2; worldMatrix[24][19] = 2;
	
	drawMap();

	i= 19;
	j = 1;
	//COLLECT ALL KEYS	
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+7]);	
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+10]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spK,videoMapMatrix[i][j+13]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+14]);
	cpct_drawSprite4x8_aligned(spY,videoMapMatrix[i][j+15]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+16]);

	++i;
	//AVOID ENEMIES
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spV,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spD,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+7]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spM,videoMapMatrix[i][j+10]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+13]);

	++i;
	// GO TO THE DOOR
	cpct_drawSprite4x8_aligned(spG,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+2]);	
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+7]);
	cpct_drawSprite4x8_aligned(spH,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spD,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+13]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+14]);

	++i;
	++i;
	++j;
	//PRESS C TO START
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+4]);	
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+13]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+14]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+15]);
}

void winScene(){
	unsigned char i,j;

	for (j=0; j<25; ++j){
		for (i=0; i<20; ++i){					
			cpct_drawSprite4x8_aligned(spBlack,videoMapMatrix[j][i]);	
		}
	}

	i=4;
	j=6;
	//YOU WIN
	cpct_drawSprite4x8_aligned(spY,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spU,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spW,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+7]);
	cpct_drawSprite4x8_aligned(spBlack,videoMapMatrix[i][j+8]);


	// Heart
	i=9;
	j=9;	

	cpct_drawSprite4x8_aligned(spHeartWin0,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spHeartWin1,videoMapMatrix[i][j+1]);
	++i;
	cpct_drawSprite4x8_aligned(spHeartWin2,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spHeartWin3,videoMapMatrix[i][j+1]);
	++i;
	++i;
	cpct_drawSprite4x8_aligned(spHeroWin,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spGirlWin,videoMapMatrix[i][j+1]);

	i=24;
	j=0;
	// PRESS C TO CONTINUE
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+4]);	
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+13]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+14]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+15]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+16]);
	cpct_drawSprite4x8_aligned(spU,videoMapMatrix[i][j+17]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+18]);

	i=1;
	while(i){
        cpct_scanKeyboardFast();
        if(cpct_isKeyPressed(Key_C))
            i = 0;
    }
	
}

void gameOverScene(){
	unsigned char i,j;

	for (j=0; j<25; ++j){
		for (i=0; i<20; ++i){					
			cpct_drawSprite4x8_aligned(spBlack,videoMapMatrix[j][i]);	
		}
	}

	//Sad CPCerdo
	i=7;
	j=6;

	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j+7]);

	++i;
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spGameOver01,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spGameOver02,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spGameOver02,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spGameOver02,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spGameOver02,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spGameOver02,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spGameOver02,videoMapMatrix[i][j+7]);

	++i;
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spGameOver03,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+7]);

	++i;
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spGameOver03,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spGameOver05,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spGameOver06,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spGameOver07,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spGameOver08,videoMapMatrix[i][j+7]);

	++i;
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spGameOver03,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spGameOver09,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spBlack,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spGameOver11,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spBlack,videoMapMatrix[i][j+7]);

	++i;
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spGameOver03,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spGameOver12,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spGameOver13,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spGameOver14,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spGameOver15,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spGameOver16,videoMapMatrix[i][j+7]);

	++i;
	cpct_drawSprite4x8_aligned(spGameOver00,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spGameOver03,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spGameOver17,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spGameOver18,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spGameOver19,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spGameOver04,videoMapMatrix[i][j+7]);

	++i;
	cpct_drawSprite4x8_aligned(spGameOver20,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spGameOver20,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spGameOver20,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spGameOver20,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spGameOver20,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spGameOver20,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spGameOver20,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spGameOver20,videoMapMatrix[i][j+7]);
	

	//Game Over
	i+=2;
	--j;
	cpct_drawSprite4x8_aligned(spG,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spM,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+3]);	
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spV,videoMapMatrix[i][j+7]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+9]);

	i+=5;
	j=0;
// PRESS C TO PLAY AGAIN
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spAndPersian,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j+10]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spY,videoMapMatrix[i][j+13]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+15]);
	cpct_drawSprite4x8_aligned(spG,videoMapMatrix[i][j+16]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+17]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+18]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+19]);
}

void creditsScene(){

	unsigned char i,j;

	winScene();

	for (j=0; j<25; ++j){
		for (i=0; i<20; ++i){					
			cpct_drawSprite4x8_aligned(spBlack,videoMapMatrix[j][i]);	
		}
	}

	i=0;
	j=6;
	// CREDITS
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spD,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+6]);

	++i;
	++i;
	++i; 
	j=5;;
	// DEVELOPERS
	cpct_drawSprite4x8_aligned(spD,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spV,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+7]);	
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+9]);

	++i;
	++i;
	--j;
	// JAVIER AKIRA
	cpct_drawSprite4x8_aligned(spJ,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spV,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+7]);
	cpct_drawSprite4x8_aligned(spK,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+10]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+11]);

	++i;
	++i;
// SALVA FAEROX
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spV,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spF,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+7]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+10]);
	cpct_drawSprite4x8_aligned(spX,videoMapMatrix[i][j+11]);

	++i;
	++i;
// CESAR_SNAKE
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spDownBar,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+7]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spK,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+10]);

	++i;
	++i;
	
// ALBERTO REALES
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spB,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+10]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+13]);

	++i;
	++i;	
	++i;

	j=3;
// SPECIAL THANKS:
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spH,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+10]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spK,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+13]);

	++i;
	++i;
	j=0;;
// LRonaldo
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spD,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+7]);
//    &
	cpct_drawSprite4x8_aligned(spAndPersian,videoMapMatrix[i][j+9]);
// CPCTELERA
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+13]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+14]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+15]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+16]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+17]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+18]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+19]);

	++i;
	++i;
// Artaburu
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spB,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spU,videoMapMatrix[i][j+5]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spU,videoMapMatrix[i][j+7]);
//    &
	cpct_drawSprite4x8_aligned(spAndPersian,videoMapMatrix[i][j+9]);
// CPCRSLIB 
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+13]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+14]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+15]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+16]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+17]);
	cpct_drawSprite4x8_aligned(spB,videoMapMatrix[i][j+18]);

	++i;
	++i;
//   Wyz
	cpct_drawSprite4x8_aligned(spW,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spY,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spZ,videoMapMatrix[i][j+4]);
//    &
	cpct_drawSprite4x8_aligned(spAndPersian,videoMapMatrix[i][j+6]);
// WyzPlayer 
	cpct_drawSprite4x8_aligned(spW,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spY,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spZ,videoMapMatrix[i][j+10]);
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spL,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spA,videoMapMatrix[i][j+13]);
	cpct_drawSprite4x8_aligned(spY,videoMapMatrix[i][j+14]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+15]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+16]);

	i=24;
	j=0;
// PRESS C TO CONTINUE
	cpct_drawSprite4x8_aligned(spP,videoMapMatrix[i][j]);
	cpct_drawSprite4x8_aligned(spR,videoMapMatrix[i][j+1]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+2]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+3]);
	cpct_drawSprite4x8_aligned(spS,videoMapMatrix[i][j+4]);
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+6]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+8]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+9]);
	cpct_drawSprite4x8_aligned(spC,videoMapMatrix[i][j+11]);
	cpct_drawSprite4x8_aligned(spO,videoMapMatrix[i][j+12]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+13]);
	cpct_drawSprite4x8_aligned(spT,videoMapMatrix[i][j+14]);
	cpct_drawSprite4x8_aligned(spI,videoMapMatrix[i][j+15]);
	cpct_drawSprite4x8_aligned(spN,videoMapMatrix[i][j+16]);
	cpct_drawSprite4x8_aligned(spU,videoMapMatrix[i][j+17]);
	cpct_drawSprite4x8_aligned(spE,videoMapMatrix[i][j+18]);
}

void loadLevel(){

	//NIVEL FINAL
	worldMatrix[0][0] = 2; worldMatrix[0][1] = 2; worldMatrix[0][2] = 2; worldMatrix[0][3] = 2; worldMatrix[0][4] = 2; worldMatrix[0][5] = 2; worldMatrix[0][6] = 2; worldMatrix[0][7] = 2; worldMatrix[0][8] = 2; worldMatrix[0][9] = 2; worldMatrix[0][10] = 2; worldMatrix[0][11] = 2; worldMatrix[0][12] = 2; worldMatrix[0][13] = 2; worldMatrix[0][14] = 2; worldMatrix[0][15] = 2; worldMatrix[0][16] = 2; worldMatrix[0][17] = 2; worldMatrix[0][18] = 2; worldMatrix[0][19] = 2; 
	worldMatrix[1][0] = 2; worldMatrix[1][1] = 1; worldMatrix[1][2] = 1; worldMatrix[1][3] = 1; worldMatrix[1][4] = 1; worldMatrix[1][5] = 2; worldMatrix[1][6] = 2; worldMatrix[1][7] = 2; worldMatrix[1][8] = 2; worldMatrix[1][9] = 2; worldMatrix[1][10] = 2; worldMatrix[1][11] = 2; worldMatrix[1][12] = 2; worldMatrix[1][13] = 2; worldMatrix[1][14] = 2; worldMatrix[1][15] = 1; worldMatrix[1][16] = 1; worldMatrix[1][17] = 1; worldMatrix[1][18] = 1; worldMatrix[1][19] = 2; 
	worldMatrix[2][0] = 2; worldMatrix[2][1] = 2; worldMatrix[2][2] = 2; worldMatrix[2][3] = 2; worldMatrix[2][4] = 2; worldMatrix[2][5] = 2; worldMatrix[2][6] = 2; worldMatrix[2][7] = 2; worldMatrix[2][8] = 2; worldMatrix[2][9] = 2; worldMatrix[2][10] = 2; worldMatrix[2][11] = 2; worldMatrix[2][12] = 2; worldMatrix[2][13] = 2; worldMatrix[2][14] = 2; worldMatrix[2][15] = 2; worldMatrix[2][16] = 2; worldMatrix[2][17] = 2; worldMatrix[2][18] = 2; worldMatrix[2][19] = 2; 
	worldMatrix[3][0] = 2; worldMatrix[3][1] = 1; worldMatrix[3][2] = 1; worldMatrix[3][3] = 1; worldMatrix[3][4] = 1; worldMatrix[3][5] = 1; worldMatrix[3][6] = 2; worldMatrix[3][7] = 2; worldMatrix[3][8] = 1; worldMatrix[3][9] = 1; worldMatrix[3][10] = 1; worldMatrix[3][11] = 1; worldMatrix[3][12] = 2; worldMatrix[3][13] = 2; worldMatrix[3][14] = 2; worldMatrix[3][15] = 1; worldMatrix[3][16] = 1; worldMatrix[3][17] = 1; worldMatrix[3][18] = 3; worldMatrix[3][19] = 2; 
	worldMatrix[4][0] = 2; worldMatrix[4][1] = 1; worldMatrix[4][2] = 1; worldMatrix[4][3] = 1; worldMatrix[4][4] = 1; worldMatrix[4][5] = 1; worldMatrix[4][6] = 1; worldMatrix[4][7] = 1; worldMatrix[4][8] = 1; worldMatrix[4][9] = 1; worldMatrix[4][10] = 1; worldMatrix[4][11] = 1; worldMatrix[4][12] = 1; worldMatrix[4][13] = 1; worldMatrix[4][14] = 2; worldMatrix[4][15] = 1; worldMatrix[4][16] = 1; worldMatrix[4][17] = 2; worldMatrix[4][18] = 2; worldMatrix[4][19] = 2; 
	worldMatrix[5][0] = 2; worldMatrix[5][1] = 2; worldMatrix[5][2] = 2; worldMatrix[5][3] = 1; worldMatrix[5][4] = 1; worldMatrix[5][5] = 1; worldMatrix[5][6] = 1; worldMatrix[5][7] = 1; worldMatrix[5][8] = 1; worldMatrix[5][9] = 1; worldMatrix[5][10] = 1; worldMatrix[5][11] = 1; worldMatrix[5][12] = 1; worldMatrix[5][13] = 1; worldMatrix[5][14] = 2; worldMatrix[5][15] = 1; worldMatrix[5][16] = 1; worldMatrix[5][17] = 1; worldMatrix[5][18] = 1; worldMatrix[5][19] = 4; 
	worldMatrix[6][0] = 2; worldMatrix[6][1] = 2; worldMatrix[6][2] = 2; worldMatrix[6][3] = 2; worldMatrix[6][4] = 1; worldMatrix[6][5] = 1; worldMatrix[6][6] = 1; worldMatrix[6][7] = 1; worldMatrix[6][8] = 1; worldMatrix[6][9] = 1; worldMatrix[6][10] = 1; worldMatrix[6][11] = 1; worldMatrix[6][12] = 1; worldMatrix[6][13] = 2; worldMatrix[6][14] = 2; worldMatrix[6][15] = 1; worldMatrix[6][16] = 1; worldMatrix[6][17] = 1; worldMatrix[6][18] = 1; worldMatrix[6][19] = 4; 
	worldMatrix[7][0] = 2; worldMatrix[7][1] = 2; worldMatrix[7][2] = 2; worldMatrix[7][3] = 2; worldMatrix[7][4] = 2; worldMatrix[7][5] = 2; worldMatrix[7][6] = 2; worldMatrix[7][7] = 1; worldMatrix[7][8] = 1; worldMatrix[7][9] = 1; worldMatrix[7][10] = 1; worldMatrix[7][11] = 2; worldMatrix[7][12] = 2; worldMatrix[7][13] = 2; worldMatrix[7][14] = 1; worldMatrix[7][15] = 1; worldMatrix[7][16] = 1; worldMatrix[7][17] = 1; worldMatrix[7][18] = 1; worldMatrix[7][19] = 2; 
	worldMatrix[8][0] = 2; worldMatrix[8][1] = 2; worldMatrix[8][2] = 1; worldMatrix[8][3] = 1; worldMatrix[8][4] = 1; worldMatrix[8][5] = 1; worldMatrix[8][6] = 1; worldMatrix[8][7] = 1; worldMatrix[8][8] = 1; worldMatrix[8][9] = 1; worldMatrix[8][10] = 1; worldMatrix[8][11] = 1; worldMatrix[8][12] = 1; worldMatrix[8][13] = 1; worldMatrix[8][14] = 1; worldMatrix[8][15] = 1; worldMatrix[8][16] = 1; worldMatrix[8][17] = 1; worldMatrix[8][18] = 1; worldMatrix[8][19] = 2; 
	worldMatrix[9][0] = 2; worldMatrix[9][1] = 1; worldMatrix[9][2] = 1; worldMatrix[9][3] = 1; worldMatrix[9][4] = 1; worldMatrix[9][5] = 1; worldMatrix[9][6] = 1; worldMatrix[9][7] = 1; worldMatrix[9][8] = 1; worldMatrix[9][9] = 1; worldMatrix[9][10] = 1; worldMatrix[9][11] = 1; worldMatrix[9][12] = 1; worldMatrix[9][13] = 1; worldMatrix[9][14] = 1; worldMatrix[9][15] = 1; worldMatrix[9][16] = 1; worldMatrix[9][17] = 1; worldMatrix[9][18] = 1; worldMatrix[9][19] = 2; 
	worldMatrix[10][0] = 2; worldMatrix[10][1] = 1; worldMatrix[10][2] = 1; worldMatrix[10][3] = 1; worldMatrix[10][4] = 1; worldMatrix[10][5] = 1; worldMatrix[10][6] = 1; worldMatrix[10][7] = 1; worldMatrix[10][8] = 1; worldMatrix[10][9] = 1; worldMatrix[10][10] = 1; worldMatrix[10][11] = 1; worldMatrix[10][12] = 1; worldMatrix[10][13] = 1; worldMatrix[10][14] = 1; worldMatrix[10][15] = 1; worldMatrix[10][16] = 1; worldMatrix[10][17] = 1; worldMatrix[10][18] = 2; worldMatrix[10][19] = 2; 
	worldMatrix[11][0] = 2; worldMatrix[11][1] = 1; worldMatrix[11][2] = 1; worldMatrix[11][3] = 1; worldMatrix[11][4] = 1; worldMatrix[11][5] = 1; worldMatrix[11][6] = 1; worldMatrix[11][7] = 1; worldMatrix[11][8] = 1; worldMatrix[11][9] = 1; worldMatrix[11][10] = 1; worldMatrix[11][11] = 1; worldMatrix[11][12] = 1; worldMatrix[11][13] = 1; worldMatrix[11][14] = 1; worldMatrix[11][15] = 1; worldMatrix[11][16] = 2; worldMatrix[11][17] = 2; worldMatrix[11][18] = 2; worldMatrix[11][19] = 2; 
	worldMatrix[12][0] = 2; worldMatrix[12][1] = 1; worldMatrix[12][2] = 1; worldMatrix[12][3] = 1; worldMatrix[12][4] = 1; worldMatrix[12][5] = 1; worldMatrix[12][6] = 2; worldMatrix[12][7] = 2; worldMatrix[12][8] = 2; worldMatrix[12][9] = 2; worldMatrix[12][10] = 2; worldMatrix[12][11] = 2; worldMatrix[12][12] = 2; worldMatrix[12][13] = 2; worldMatrix[12][14] = 2; worldMatrix[12][15] = 2; worldMatrix[12][16] = 2; worldMatrix[12][17] = 2; worldMatrix[12][18] = 2; worldMatrix[12][19] = 2; 
	worldMatrix[13][0] = 2; worldMatrix[13][1] = 1; worldMatrix[13][2] = 1; worldMatrix[13][3] = 1; worldMatrix[13][4] = 1; worldMatrix[13][5] = 2; worldMatrix[13][6] = 2; worldMatrix[13][7] = 1; worldMatrix[13][8] = 1; worldMatrix[13][9] = 1; worldMatrix[13][10] = 1; worldMatrix[13][11] = 1; worldMatrix[13][12] = 1; worldMatrix[13][13] = 1; worldMatrix[13][14] = 1; worldMatrix[13][15] = 1; worldMatrix[13][16] = 1; worldMatrix[13][17] = 1; worldMatrix[13][18] = 3; worldMatrix[13][19] = 2; 
	worldMatrix[14][0] = 2; worldMatrix[14][1] = 1; worldMatrix[14][2] = 1; worldMatrix[14][3] = 1; worldMatrix[14][4] = 1; worldMatrix[14][5] = 2; worldMatrix[14][6] = 2; worldMatrix[14][7] = 1; worldMatrix[14][8] = 1; worldMatrix[14][9] = 1; worldMatrix[14][10] = 1; worldMatrix[14][11] = 1; worldMatrix[14][12] = 1; worldMatrix[14][13] = 1; worldMatrix[14][14] = 1; worldMatrix[14][15] = 1; worldMatrix[14][16] = 1; worldMatrix[14][17] = 2; worldMatrix[14][18] = 1; worldMatrix[14][19] = 2; 
	worldMatrix[15][0] = 2; worldMatrix[15][1] = 1; worldMatrix[15][2] = 1; worldMatrix[15][3] = 1; worldMatrix[15][4] = 1; worldMatrix[15][5] = 2; worldMatrix[15][6] = 2; worldMatrix[15][7] = 1; worldMatrix[15][8] = 1; worldMatrix[15][9] = 1; worldMatrix[15][10] = 1; worldMatrix[15][11] = 1; worldMatrix[15][12] = 1; worldMatrix[15][13] = 1; worldMatrix[15][14] = 1; worldMatrix[15][15] = 1; worldMatrix[15][16] = 1; worldMatrix[15][17] = 1; worldMatrix[15][18] = 1; worldMatrix[15][19] = 2; 
	worldMatrix[16][0] = 2; worldMatrix[16][1] = 1; worldMatrix[16][2] = 1; worldMatrix[16][3] = 1; worldMatrix[16][4] = 1; worldMatrix[16][5] = 1; worldMatrix[16][6] = 1; worldMatrix[16][7] = 1; worldMatrix[16][8] = 1; worldMatrix[16][9] = 1; worldMatrix[16][10] = 1; worldMatrix[16][11] = 1; worldMatrix[16][12] = 1; worldMatrix[16][13] = 1; worldMatrix[16][14] = 1; worldMatrix[16][15] = 1; worldMatrix[16][16] = 1; worldMatrix[16][17] = 1; worldMatrix[16][18] = 1; worldMatrix[16][19] = 2; 
	worldMatrix[17][0] = 2; worldMatrix[17][1] = 1; worldMatrix[17][2] = 1; worldMatrix[17][3] = 1; worldMatrix[17][4] = 1; worldMatrix[17][5] = 1; worldMatrix[17][6] = 1; worldMatrix[17][7] = 1; worldMatrix[17][8] = 1; worldMatrix[17][9] = 1; worldMatrix[17][10] = 1; worldMatrix[17][11] = 1; worldMatrix[17][12] = 1; worldMatrix[17][13] = 1; worldMatrix[17][14] = 1; worldMatrix[17][15] = 1; worldMatrix[17][16] = 1; worldMatrix[17][17] = 1; worldMatrix[17][18] = 1; worldMatrix[17][19] = 2; 
	worldMatrix[18][0] = 2; worldMatrix[18][1] = 1; worldMatrix[18][2] = 1; worldMatrix[18][3] = 1; worldMatrix[18][4] = 1; worldMatrix[18][5] = 1; worldMatrix[18][6] = 1; worldMatrix[18][7] = 1; worldMatrix[18][8] = 1; worldMatrix[18][9] = 1; worldMatrix[18][10] = 1; worldMatrix[18][11] = 2; worldMatrix[18][12] = 2; worldMatrix[18][13] = 1; worldMatrix[18][14] = 1; worldMatrix[18][15] = 1; worldMatrix[18][16] = 1; worldMatrix[18][17] = 1; worldMatrix[18][18] = 1; worldMatrix[18][19] = 2; 
	worldMatrix[19][0] = 2; worldMatrix[19][1] = 2; worldMatrix[19][2] = 1; worldMatrix[19][3] = 1; worldMatrix[19][4] = 1; worldMatrix[19][5] = 1; worldMatrix[19][6] = 1; worldMatrix[19][7] = 1; worldMatrix[19][8] = 1; worldMatrix[19][9] = 1; worldMatrix[19][10] = 1; worldMatrix[19][11] = 2; worldMatrix[19][12] = 1; worldMatrix[19][13] = 1; worldMatrix[19][14] = 1; worldMatrix[19][15] = 1; worldMatrix[19][16] = 1; worldMatrix[19][17] = 1; worldMatrix[19][18] = 1; worldMatrix[19][19] = 2; 
	worldMatrix[20][0] = 2; worldMatrix[20][1] = 2; worldMatrix[20][2] = 2; worldMatrix[20][3] = 2; worldMatrix[20][4] = 1; worldMatrix[20][5] = 1; worldMatrix[20][6] = 1; worldMatrix[20][7] = 1; worldMatrix[20][8] = 1; worldMatrix[20][9] = 1; worldMatrix[20][10] = 1; worldMatrix[20][11] = 2; worldMatrix[20][12] = 1; worldMatrix[20][13] = 1; worldMatrix[20][14] = 1; worldMatrix[20][15] = 1; worldMatrix[20][16] = 1; worldMatrix[20][17] = 1; worldMatrix[20][18] = 1; worldMatrix[20][19] = 2; 
	worldMatrix[21][0] = 2; worldMatrix[21][1] = 1; worldMatrix[21][2] = 1; worldMatrix[21][3] = 2; worldMatrix[21][4] = 2; worldMatrix[21][5] = 1; worldMatrix[21][6] = 1; worldMatrix[21][7] = 1; worldMatrix[21][8] = 1; worldMatrix[21][9] = 1; worldMatrix[21][10] = 1; worldMatrix[21][11] = 2; worldMatrix[21][12] = 1; worldMatrix[21][13] = 1; worldMatrix[21][14] = 1; worldMatrix[21][15] = 1; worldMatrix[21][16] = 2; worldMatrix[21][17] = 2; worldMatrix[21][18] = 2; worldMatrix[21][19] = 2; 
	worldMatrix[22][0] = 2; worldMatrix[22][1] = 1; worldMatrix[22][2] = 3; worldMatrix[22][3] = 1; worldMatrix[22][4] = 2; worldMatrix[22][5] = 1; worldMatrix[22][6] = 1; worldMatrix[22][7] = 1; worldMatrix[22][8] = 1; worldMatrix[22][9] = 1; worldMatrix[22][10] = 2; worldMatrix[22][11] = 2; worldMatrix[22][12] = 1; worldMatrix[22][13] = 1; worldMatrix[22][14] = 1; worldMatrix[22][15] = 1; worldMatrix[22][16] = 1; worldMatrix[22][17] = 1; worldMatrix[22][18] = 1; worldMatrix[22][19] = 2; 
	worldMatrix[23][0] = 2; worldMatrix[23][1] = 1; worldMatrix[23][2] = 1; worldMatrix[23][3] = 1; worldMatrix[23][4] = 1; worldMatrix[23][5] = 1; worldMatrix[23][6] = 1; worldMatrix[23][7] = 1; worldMatrix[23][8] = 1; worldMatrix[23][9] = 2; worldMatrix[23][10] = 2; worldMatrix[23][11] = 2; worldMatrix[23][12] = 1; worldMatrix[23][13] = 1; worldMatrix[23][14] = 1; worldMatrix[23][15] = 1; worldMatrix[23][16] = 2; worldMatrix[23][17] = 1; worldMatrix[23][18] = 3; worldMatrix[23][19] = 2; 
	worldMatrix[24][0] = 2; worldMatrix[24][1] = 2; worldMatrix[24][2] = 2; worldMatrix[24][3] = 2; worldMatrix[24][4] = 2; worldMatrix[24][5] = 2; worldMatrix[24][6] = 2; worldMatrix[24][7] = 2; worldMatrix[24][8] = 2; worldMatrix[24][9] = 2; worldMatrix[24][10] = 2; worldMatrix[24][11] = 2; worldMatrix[24][12] = 2; worldMatrix[24][13] = 2; worldMatrix[24][14] = 2; worldMatrix[24][15] = 2; worldMatrix[24][16] = 2; worldMatrix[24][17] = 2; worldMatrix[24][18] = 2; worldMatrix[24][19] = 2;
	 
}
