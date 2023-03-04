#ifndef __MODULE_HEADER__
#define __MODULE_HEADER__


#include "stdint.h"

#include "draw.h"


typedef struct{
	uint16_t	x, y;
}P2;

typedef struct{
	P2			pos, size;
	uint32_t	portct;
	uint32_t	gatect;
	
	void*		ports;
	void*		gates;
	
	P2*			portpos;
	P2*			gatepos;
}Module;


void	drawModule	(Img, Module);



#endif
