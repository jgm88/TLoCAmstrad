#ifndef _VIDEOMAP_H
#define _VIDEOMAP_H

//
//	Matriz de 4x8, en total tenemos una matriz de 20x25 (20 de ancho y 25 de alto) para tiles de 4x8 
//
extern char * videoMapMatrix[25][20];
void initialiteMap();
char* getPosVideo(char x, char y);


#endif