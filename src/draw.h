#ifndef __DRAW_HEADER__
#define __DRAW_HEADER__


#include "stdint.h"


typedef struct{
	uint32_t*	pix;
	int			h, w;
}Img;

typedef struct{
	int			zoom;
	int			x, y;
}View;


void	drawRect	(Img, int, int, int, int, uint32_t);
void	drawVLine	(Img, int, int, int, uint32_t);
void	drawHLine	(Img, int, int, int, uint32_t);

void	drawView	(View, Img, Img);



#endif
