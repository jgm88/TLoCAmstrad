#include "game.h"

unsigned char life;
unsigned char keys;


//TODO crear vector de Spawn Points para el deductLife segun mapa
//TODO abrir puertas con openDoor segun el numero de la llave key=1 --> openDoor(1)

void deductLife(Tplayer *player){
    if(life>1){
        cpct_drawSprite4x8_aligned(spNoHeart,getPosVideo(life, 1));
        --life;
        updatePosition(1, 4, &player->base);
        doSound(1,1);
    }else
        endGame=2;
    
    
}
void addLife(){
	if(life<4){		
		++life;
		cpct_drawSprite4x8_aligned(spHeart,getPosVideo(life, 1));
	}
}
void initGame(){
	life = 4;
	cpct_drawSprite4x8_aligned(spHeart,getPosVideo(1, 1));
	cpct_drawSprite4x8_aligned(spHeart,getPosVideo(2, 1));
	cpct_drawSprite4x8_aligned(spHeart,getPosVideo(3, 1));
	cpct_drawSprite4x8_aligned(spHeart,getPosVideo(4, 1));	

	keys = 0;
	cpct_drawSprite4x8_aligned(spNoKey,getPosVideo(15, 1));
	cpct_drawSprite4x8_aligned(spNoKey,getPosVideo(16, 1));
	cpct_drawSprite4x8_aligned(spNoKey,getPosVideo(17, 1));
	cpct_drawSprite4x8_aligned(spNoKey,getPosVideo(18, 1));
}


void pickUpKey(){
    if(keys<4){
        ++keys;
        cpct_drawSprite4x8_aligned(spCollectedKey,getPosVideo(keys+14, 1)); 
        doSound(2,2);
    }
    if(keys==4)
        openDoor();
}
