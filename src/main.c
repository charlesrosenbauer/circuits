#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "circuit.h"

#include "SDL2/SDL.h"



int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window*	 window;
	SDL_Surface* screen;	
	window = SDL_CreateWindow("Circuit sim",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				1280, 720, SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface(window);
	
	SDL_Surface* gateSurface = SDL_LoadBMP("gates.bmp");
	gateSurface = SDL_ConvertSurfaceFormat(gateSurface, SDL_PIXELFORMAT_ABGR8888, 0);


	Circuit c = makeCircuit(512, 192);
	
	int as = circMakeWires(&c, 64);
	int bs = circMakeWires(&c, 64);
	int qs = circMakeWires(&c, 64);
	
	circMakeGate(&c, G_NAND, as, bs, qs, 64);
	
	printCircuit(c);


	SDL_Event e;
	int cont = 1;
	while(cont){
		while(SDL_PollEvent(&e))
			if(e.type == SDL_QUIT) cont = 0;
		
		SDL_UpdateWindowSurface(window);
		SDL_Delay(16);
	}
	SDL_Quit();
}
