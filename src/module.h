#ifndef __MODULE_HEADER__
#define __MODULE_HEADER__


#include "stdint.h"



typedef struct{
	uint16_t	x, y, h, w;
	uint32_t	portct;
	uint32_t	gatect;
	
	void*		ports;
	void*		gates;
}Module;



#endif
