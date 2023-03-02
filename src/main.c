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
	for(int i = 0; i < 16777216; i++) disp.pix[i] = 0x1f1f1f;
	
	View v = (View){0, 2048, 2048};


	SDL_Event e;
	int cont = 1;
	
	int drag = 0;
	int mx   = 0;
	int my   = 0;
	int dx   = 0;
	int dy   = 0;
	while(cont){
		while(SDL_PollEvent(&e)){
			switch(e.type){
				case SDL_QUIT : cont = 0; break;
				case SDL_MOUSEMOTION : {
					if(drag){
						// This is a rough approximation, particularly with zoom
						// Ideally we want to handle zoom scaling much better
						dx   = e.motion.xrel >> v.zoom;
						dy   = e.motion.yrel >> v.zoom;
						
						v.x -= dx;
						v.y -= dy;
					}else{
						dx = 0;
						dy = 0;
						
						int x = ((e.motion.x - 1600) >> v.zoom) + v.x;
						int y = ((e.motion.y -  900) >> v.zoom) + v.y;
						if((x >= 0) && (x < disp.w) && (y >= 0) && (y < disp.h))
							disp.pix[(y * disp.w) + x] = 0xffffff;
					}
				}break;
				
				case SDL_MOUSEBUTTONDOWN : {
					drag = 1;
					mx   = e.button.x - (v.x >> v.zoom) + 800;
					my   = e.button.y - (v.y >> v.zoom) + 450;
					dx   = 0;
					dy   = 0;
				}break;
				
				case SDL_MOUSEBUTTONUP   : {
					drag = 0;
				}break;
				
				case SDL_MOUSEWHEEL : {
					v.zoom += e.wheel.y;
					v.zoom  = (v.zoom < 0)? 0 : v.zoom;
				}break;
			}
		}
		
		drawView(v, img, disp);
		
		SDL_UpdateWindowSurface(window);
		SDL_Delay(16);
	}
	SDL_Quit();
}
