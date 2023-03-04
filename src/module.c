#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "module.h"



void drawModule(Img img, Module mod){
	drawRect(img, mod.pos.x, mod.pos.y, mod.size.y, mod.size.x, 0x7f7f7f);
	
	for(int i = 0; i < mod.gatect; i++){
		int x = mod.pos.x + mod.gatepos[i].x;
		int y = mod.pos.y + mod.gatepos[i].y;
		
		int n = (y * img.w) + x;
		img.pix[n] = 0xcf00cf;
	}
}
