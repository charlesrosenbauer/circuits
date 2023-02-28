#ifndef __DRAW_HEADER__
#define __DRAW_HEADER__


#include "stdint.h"


typedef struct{
	uint32_t*	pix;
	int			h, w;
}Img;


void	drawRect	(Img, int, int, int, int, uint32_t);
void	drawVLine	(Img, int, int, int, uint32_t);
void	drawHLine	(Img, int, int, int, uint32_t);



#endif
