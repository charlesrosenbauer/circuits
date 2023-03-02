#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "circuit.h"
#include "draw.h"

#include "SDL2/SDL.h"



int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window*	 window;
	SDL_Surface* screen;	
	window = SDL_CreateWindow("Circuit sim",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				1600, 900, SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface(window);
	
	SDL_Surface* gateSurface = SDL_LoadBMP("gates.bmp");
	gateSurface = SDL_ConvertSurfaceFormat(gateSurface, SDL_PIXELFORMAT_ABGR8888, 0);

	Img img = (Img){.pix=screen->pixels, .h=900, .w=1600};


	Circuit c = makeCircuit(512, 192);
	
	int as = circMakeWires(&c, 64);
	int bs = circMakeWires(&c, 64);
	int qs = circMakeWires(&c, 64);
	
	circMakeGate(&c, G_NAND, as, bs, qs, 64);
	
	printCircuit(c);
	
	Img disp = (Img){
		.pix	= malloc(sizeof(uint32_t) * 4096 * 4096),
		.h		= 4096,
		.w		= 4096
	};
	for(int i = 0; i < 4096; i++){
		for(int j = 0; j < 4096; j++){
			int m = (i * 781931) - 531789 + (j * 7785931);
			int n = (j * 387911) ^ 445181 ^ (i * 3751891);
			uint32_t c = (((m ^ n) + (m - n)) & 0x800)? 0xcf3f3f : 0x3f7f7f; 
		
			disp.pix[(i * 4096) + j] = c;
		}
	}
	
	View v = (View){0, 2048, 2048};


	SDL_Event e;
	int cont = 1;
	
	int mx   = 0;
	int my   = 0;
	while(cont){
		while(SDL_PollEvent(&e))
			switch(e.type){
				case SDL_QUIT : cont = 0; break;
				case SDL_MOUSEMOTION : {
				
				}break;
				
				case SDL_MOUSEBUTTONDOWN : {
				
				}break;
				
				case SDL_MOUSEBUTTONUP   : {
				
				}break;
			}
		
		drawRect(img, 16, 16, 64, 128, 0xcfcfcf);
		
		drawView(v, img, disp);
		
		SDL_UpdateWindowSurface(window);
		SDL_Delay(16);
	}
	SDL_Quit();
}
